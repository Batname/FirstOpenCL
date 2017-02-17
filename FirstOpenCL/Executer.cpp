#include "Executer.hpp"

#include <stdlib.h>
#include <assert.h>

Executer::Executer(KernelFile kFile)
{

    // 1. Open the source file
    FILE* fp;
    fp = fopen(kFile.fileName, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(EXIT_FAILURE);
    }
    SourceBuffer = (unsigned char*) malloc(MAX_BINARY_SIZE);
    SourceSize = fread(SourceBuffer, 1, MAX_BINARY_SIZE, fp);
    fclose(fp);
    
    // 2. Get Platform and Device Info
    clGetPlatformIDs(1, &PlatformID, &PlatformCount);
    clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_DEFAULT, 1, &DeviceID, &DevicesCount);

    // 3. Create OpenCL Context
    Context = clCreateContext(nullptr, 1, &DeviceID, nullptr, nullptr, &ErrRet);
    CheckStatus("clCreateContext", &ErrRet);

    
    // 4. Create command Queue
    CommandQueue = clCreateCommandQueue(Context, DeviceID, 0, &ErrRet);
    CheckStatus("clCreateCommandQueue", &ErrRet);
    
    if (kFile.type == FileType::EText)
    {
        // 5. Create kernel program from source
        Program = clCreateProgramWithSource(Context, 1, (const char**)&SourceBuffer, (const size_t*)&SourceSize, &ErrRet);
        CheckStatus("clCreateProgramWithSource", &ErrRet);
    }
    else if (kFile.type == FileType::EBinary)
    {
        // 5. Create kernel program from binary
        Program = clCreateProgramWithBinary(Context, 1, &DeviceID, (const size_t*)&SourceSize, (const unsigned char **)&SourceBuffer, &BinaryStatus, &ErrRet);
        CheckStatus("clCreateProgramWithBinary", &ErrRet);
    }
    
    // 6. Build kernel program
    ErrRet = clBuildProgram(Program, 1, &DeviceID, nullptr, nullptr, nullptr);
    CheckStatus("clBuildProgram", &ErrRet);
}

void Executer::CheckStatus(const char* Msg, cl_int* Err) const
{
    if (*Err != CL_SUCCESS) {
        fprintf(stderr, "%s failed. Error: %d\n", Msg, *Err);
    }
}

Executer::~Executer()
{
    free(SourceBuffer);
    
    clFlush(CommandQueue);
    clFinish(CommandQueue);
    clReleaseKernel(Kernel);
    clReleaseProgram(Program);
    clReleaseCommandQueue(CommandQueue);
    clReleaseContext(Context);
}
