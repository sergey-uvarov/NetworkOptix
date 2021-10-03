To build MinMaxQueue projects on Linux:
1. Create (if not yet) a directory called "build" in the same directory where this file lies. Clean it, if there are some left-overs.
2. Enter this directory (e.g. via "cd") and run a command "cmake ..".
3. Once done, run the next command - "make". This will create a new directory called "bin", in which the built binaries will be placed.
4. Enter the "bin" directory and you will see three files - "MinMaxQueue", "MinMaxQueue.a" and "MinMaxQueueUT".
If it's not so, recheck that you have CMake and a C++ compiler installed and retry from point 1.
5. To run unit tests and ensure everything works as expected, just run the following command (from the "bin" directory): "./MinMaxQueueUT".
This will run all the unit tests and you should see all them PASSED.

Requirements:
gcc 9.3.0+
clang 12.0+