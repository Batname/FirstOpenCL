// include C lib
#include <stdio.h>
#include <stdlib.h>

// include std libs
#include <vector>

// Include OpenCL lib
#include <OpenCL/opencl.h>

// custiom libs
#include "Informer.hpp"
#include "MyExecuter.hpp"

// Constant
enum Constants
{
    MEM_SIZE = 128,
    MAX_SOURCE_SIZE = 0x10000
};

int main(int argc, const char * argv[]) {
    Informer informer(Informer::I_RELEASE);
    informer.PrintPlatformCount();
    informer.PrintDeviceCount();
    informer.PrintPlatfromsInfo();
    informer.PrintDevicesInfo();
    
    // Execute
    MyExecuter::KernelFile kFile = {
        "./hello.clbin",
        MyExecuter::FileType::EBinary
    };
    
    MyExecuter executer(kFile, 128 * sizeof(char));
    executer.PrintResult();
    
    // Print Executer log
    Informer::PrintExecuterInfo(&executer);    
    
    // EXIT
    return 0;
}
