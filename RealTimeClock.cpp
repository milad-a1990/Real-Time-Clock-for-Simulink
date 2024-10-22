// Define the S-Function Name and Level
#define S_FUNCTION_NAME  RealTimeTimer3
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"
#include <chrono>
#include <thread>

std::chrono::steady_clock::time_point start;  // Declare global start time
std::chrono::microseconds clock_step;         // Declare the clock step in microseconds

// Function to initialize the S-Function
static void mdlInitializeSizes(SimStruct* S)
{
    ssSetNumSFcnParams(S, 1);
    // to check the number of parameters entered by the user
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; // Parameter mismatch will be reported by Simulink
    }

    if (!ssSetNumInputPorts(S, 0)) return;
    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 1);
    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);
    ssSetNumSampleTimes(S, 1);
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

// Function to initialize the sample times
static void mdlInitializeSampleTimes(SimStruct* S)
{
    // Set the sample time from the solver
    ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);

    // Initialize start time
    start = std::chrono::steady_clock::now();
}

// Function for parameter checking (if needed)
#define MDL_CHECK_PARAMETERS
static void mdlCheckParameters(SimStruct* S)
{
    const real_T* param = mxGetPr(ssGetSFcnParam(S, 0)); // Get parameter
    if (*param <= 0) {
        ssSetErrorStatus(S, "Parameter must be positive.");
        return;
    }
}

#define MDL_START
#if defined(MDL_START)
static void mdlStart(SimStruct* S)
{
    const real_T* param = mxGetPr(ssGetSFcnParam(S, 0)); // Get the input parameter (Simulink step size)

    // Calculate the clock step in microseconds
    real_T step = (*param) * 0.1;
    auto step_us = step * 1e5;  // Multiply by 1e5 to convert to microseconds

    // Set the clock step using the calculated step size in microseconds
    clock_step = std::chrono::microseconds(static_cast<int>(step_us));
}
#endif

// Function that calculates output at each time step
static void mdlOutputs(SimStruct* S, int_T tid)
{
    // Get the current time
    auto now = std::chrono::steady_clock::now();

    // Calculate elapsed time in microseconds
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(now - start).count();

    // Convert the elapsed time into seconds
    real_T elapsed_seconds = elapsed_time / 1e6;

    // Get simulation time from Simulink
    real_T simulation_time = ssGetT(S);

    // Calculate the next target real time to synchronize with the Simulink solver step
    auto next_time = start + std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::duration<real_T>(simulation_time));

    // Sleep until the next scheduled time
    std::this_thread::sleep_until(next_time);

    // Output the elapsed time at the output port
    real_T* Simulation_Time = ssGetOutputPortRealSignal(S, 0);
    *Simulation_Time = elapsed_seconds;
}

// Function to terminate the S-Function (cleanup)
static void mdlTerminate(SimStruct* S)
{
    UNUSED_ARG(S);
}

// Required S-function trailer
#ifdef MATLAB_MEX_FILE
#include "simulink.c"
#else
#include "cg_sfun.h"
#endif
