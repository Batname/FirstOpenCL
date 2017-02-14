// include C libs
#include <stdio.h>
#include <stdlib.h>

// Include OpenCL lib
#include <OpenCL/opencl.h>

// custiom libs
#include "Informer.hpp"

// Constant
enum Constants
{
    MEM_SIZE = 128,
    MAX_SOURCE_SIZE = 0x10000
};

int main(int argc, const char * argv[]) {
    Informer informer;
    informer.PrintPlatformCount();
    informer.PrintDeviceCount();
    informer.PrintPlatfromsInfo();
    informer.PrintDevicesInfo();
    
    return 0;
}
