# cppGPIO #

cppGPIO is as library for writing and reading the Raspberry Pi GPIO, writen in C++14.

### How to compile. ###
 * Update apt-get
```sudo apt-get update```
* Install build essential tools (wich includes g++)
```sudo apt-get install build-essential```
 * Install CMake
  ```sudo apt-get install cmake```
 * create build directory and go into it
```
mkdir build
cd build
```
 * run cmake and build
 ```
cmake -G 'Unix Makefiles' -DCMAKE_BUILD_TYPE=Release ..
make -j 8
```

### generated files ###
* libcppGPIO.a - Static library
* example1 - Example executable

### run ###

```sh
$ sudo example1
```
### usage example ###

```c++
#include <chrono>
#include <thread>
#include "GPIO.h"
...
    GPIO gpio18("18", GPIODirection::output);
    GPIO gpio17("17", GPIODirection::input);
    if (gpio18.isStreamGood() && gpio17.isStreamGood()) {
        gpio18.setValue(gpio17.getValue());
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
```
>Programing is moving zeros and ones for one place to another.
