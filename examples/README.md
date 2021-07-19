# MCU-Driver-HAL examples
The MCU-Driver-HAL examples demonstrate the usage of the APIs. They give a starting point on top of which more complex logic can be built.  
The examples are categorised by API and can be found in this directory.

## Required tools
- [CMake](https://cmake.org/install/), ensure you select a version that fulfills the minimum requirement in the main [`CMakeLists.txt`](../CMakeLists.txt) file.
- [Mbed-tools](https://github.com/ARMmbed/mbed-tools) version `7.16.0`.

CMake uses the `Make` build automation by default, however, [`Ninja`](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) is also supported.
`Ninja` can optionally be used to build faster.

## Configuration
The examples can be configured to be built for any hardware platform that implements the API. The configuration involves providing a CMake module which must contain CMake variables that define C language macros and other CMake variables that are expected by the MCU-Driver-HAL. See [here](../docs/porting/api/cmake.md) for more information.

Additionally, the `CMakeLists.txt` file that defines the example CMake executable must also define the following CMake variables:
* `MBED_PATH`: Sets the path to the `MCU-Driver-HAL` directory in the project
* `MBED_CONFIG_PATH`: Sets the path to the configuration CMake module.

The configuration file can be generated using `mbed-tools` from an Mbed OS project if a board is already supported. You can use the  [`mbed-os-example-blinky`](https://github.com/ARMmbed/mbed-os-example-blinky) and run the following command:
```
mbed-tools configure -m <TARGET> -t <TOOLCHAIN>
```

**Note:** `mbed-tools` generates a board configuration CMake module using information from Mbed OS's`targets.json` and `mbed_lib.json` configuration files. `mbed-tools` cannot run in a non-Mbed project. This limitation is expected to be resolved in the future. Alternatively, you can manually create a board configuration CMake module from a supported board.

Place the generated `mbed_config.cmake` file in the directory specified by `MBED_CONFIG_PATH`. The file must be renamed `mbed_config_arm.cmake` or `mbed_config_gcc.cmake` depending on the selected toolchain (`ARM` or `GCC_ARM` respectively) when it was generated.


## Provided Examples

The following table details the currently supported MCU-Driver-HAL examples.

|     API       |   Description    |
|---            |---                       |
| analogin      |   Reads an analog input pin and reports the voltage with a trace  |
| flash         |   Erases, reads, writes the flash at various locations     |
| gpio          |   Blinks two LEDs in alternation using a loop as a delay   |
| pwm           |   Ramps two LEDs in alternation using a loop as a delay    |
| serial        |   Prints some text to the console     |
| spi           |   Initialises the SPI interface and write a byte     |
| trace         |   Prints traces for the supported tracing levels     |
| trng          |   Gets random data from the true random number generator     |
| us_ticker_delay |   Blinks two LEDs in alteration using the microsecond ticker as a delay     |
| us_ticker_interrupt |   Blinks an LED in a callback     |

## Build

1. From a terminal, navigate to the directory containing the `CMakeLists.txt` file to build the example executable.
1. From the directory in the previous step, run the following comand to configure the target and generate the build directory:
    ```
    cmake -S . -B cmake_build -GNinja -DCMAKE_BUILD_TYPE=debug -DMBED_TOOLCHAIN=<TOOLCHAIN>
    ```
1. Run the following command to build the artefacts:
    ```
    cmake --build cmake_build
    ```

Expected configuration output:
```
-- The C compiler identification is GNU 9.2.1
-- The ASM compiler identification is GNU
-- Found assembler: /usr/local/bin/arm-none-eabi-gcc
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/local/bin/arm-none-eabi-gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found Python3: /usr/local/Frameworks/Python.framework/Versions/3.9/bin/python3.9 (found version "3.9.1") found components: Interpreter
-- Checking for Python package prettytable -- found
-- Checking for Python package future -- found
-- Checking for Python package jinja2 -- found
-- Checking for Python package intelhex -- found
-- The CXX compiler identification is GNU 9.2.1
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - failed
-- Check for working CXX compiler: /usr/local/bin/arm-none-eabi-g++
-- Check for working CXX compiler: /usr/local/bin/arm-none-eabi-g++ - works
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: /path/to/cmake_build
```

Expected build output:
```
[ 99%] Built target <EXAMPLE_LIBRARY_CMAKE_NAME>
Scanning dependencies of target <EXAMPLE_EXECUTABLE_CMAKE_NAME>
[100%] Linking C executable <~EXAMPLE_EXECUTABLE_CMAKE_NAME>.elf
executable:
-- built: /path/to/cmake_build/<EXAMPLE_EXECUTABLE_CMAKE_NAME>.bin
-- built: /path/to/cmake_build/<EXAMPLE_EXECUTABLE_CMAKE_NAME>.hex
Displaying memory map for <EXAMPLE_EXECUTABLE_CMAKE_NAME>
[100%] Built target <EXAMPLE_EXECUTABLE_CMAKE_NAME>
```
