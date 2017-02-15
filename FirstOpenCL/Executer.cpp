#include "Executer.hpp"

#include <stdlib.h>
#include <assert.h>

Executer::Executer(const char* fileName, int memSize) :
    MemSize(memSize)
{

    // 1. Open the source file
    FILE* fp;
    fp = fopen(fileName, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(EXIT_FAILURE);
    }
    SourceString = (char*) malloc(MAX_SOURCE_SIZE);
    SourceSize = fread(SourceString, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    
    // 2. Get Platform and Device Info
    clGetPlatformIDs(1, &PlatformID, &PlatformCount);
    assert(PlatformCount && "No platforms");
    clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_DEFAULT, 1, &DeviceID, &DevicesCount);
    assert(DevicesCount && "No Devices");

    // 3. Create OpenCL Context
    Context = clCreateContext(nullptr, 1, &DeviceID, nullptr, nullptr, &TempRet);
    assert(TempRet == 0 && "Error while creation context");
    
    // 4. Create command Queue
    CommandQueue = clCreateCommandQueue(Context, DeviceID, 0, &TempRet);
    assert(TempRet == 0 && "Error while creation CommandQueue");
    
    // 5. Create memory buffer
    MemObject = clCreateBuffer(Context, CL_MEM_READ_WRITE, MemSize, nullptr, &TempRet);
    assert(TempRet == 0 && "Error while allocation MemObject");
    
    // 6. Create kernel program from source
    Program = clCreateProgramWithSource(Context, 1, (const char**)&SourceString, (const size_t*)&SourceSize, &TempRet);
    assert(TempRet == 0 && "Error while Kernel program creation");
    
    // 7. Build kernel program
    TempRet = clBuildProgram(Program, 1, &DeviceID, nullptr, nullptr, nullptr);
    assert(TempRet == 0 && "Error while Build the program");
}

Executer::~Executer()
{
    free(SourceString);
    
    clFlush(CommandQueue);
    clFinish(CommandQueue);
    clReleaseKernel(Kernel);
    clReleaseProgram(Program);
    clReleaseMemObject(MemObject);
    clReleaseCommandQueue(CommandQueue);
    clReleaseContext(Context);
}
