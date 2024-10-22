# RealTimeClock.cpp

This repository contains the **RealTimeClock.cpp** file, along with the precompiled **RealTimeClock.mexw64** file and a Simulink test model **RealTimeClock_test.slx** to evaluate its performance. The code provides a real-time clock functionality, designed for integration into Simulink via an S-Function.

## Features
- Implements a real-time clock using C++ libraries: `simstruc.h`, `chrono`, and `thread`.
- Includes both the source code and the precompiled `.mexw64` file for immediate use in Simulink.
- Provides a test Simulink model (**RealTimeClock_test.slx**) to verify the performance of the real-time clock in a simulation environment.

## Files Included
- `RealTimeClock.cpp`: The C++ source code for the real-time clock.
- `RealTimeClock.mexw64`: Precompiled `.mexw64` file (64-bit), ready for use in Simulink.
- `RealTimeClock_test.slx`: Simulink test file to evaluate the performance of the real-time clock.

## Usage in Simulink

1. Add the `RealTimeClock.mexw64` file to your MATLAB path or project folder.
2. Open the **RealTimeClock_test.slx** Simulink model to test the performance of the real-time clock implementation.
3. The `.mexw64` file can be used directly in Simulink via an S-Function block.

## System Requirements
- 64-bit versions of MATLAB for Simulink integration.
- A 64-bit Windows operating system.
- Visual Studio or MinGW is needed to recompile the `.cpp` file into a `.mexw64` file if desired.
- Any IDE or text editor can be used for editing the C++ source code. (for those who wish to recompile the source).

## Contributors

- [Milad Ahmadzadeh](https://github.com/milad-a1990) - Main Developer
- [Morteza Ali Tehrani](https://github.com/morteza-ali-tehrani) - Co-developer

## Acknowledgements

This project was developed in collaboration with Real-Time Laboratory of Amirkabir University of Technology (Tehran Polytechnic).

## License

...