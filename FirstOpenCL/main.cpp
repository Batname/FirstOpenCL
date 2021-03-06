// include C lib
#include <stdio.h>
#include <stdlib.h>

// include std libs
#include <vector>

// Include OpenCL lib
#include <OpenCL/opencl.h>

// custiom libs
#include "Informer.hpp"
#include "Executer.hpp"
#include "ParallelExecuter.hpp"

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
    Executer::KernelFile kFile = {
        "./dataParallel.clbin",
        Executer::FileType::EBinary
    };
    
    ParallelExecuter executer(kFile);
    executer.PrintResult();
    
    // Print Executer log
    Informer::PrintExecuterInfo(&executer);    
    
    // EXIT
    return 0;
}
