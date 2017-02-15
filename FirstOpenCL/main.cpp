// include C lib
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
    Informer informer(Informer::I_RELEASE);
    informer.PrintPlatformCount();
    informer.PrintDeviceCount();
    informer.PrintPlatfromsInfo();
    informer.PrintDevicesInfo();
    
    
    // Execute kernel
    cl_device_id DeviceID = NULL;
    cl_context Context = NULL;
    cl_command_queue CommandQueue = NULL;
    cl_mem MemObject = NULL;
    cl_program Program = NULL;
    cl_kernel Kernel = NULL;
    cl_platform_id PlatformID = NULL;
    cl_uint RetNumDevices;
    cl_uint RetNumPlatforms;
    cl_int Ret;
    
    char* StringResult[MEM_SIZE];
    
    // 1. Open the source file
    FILE* fp;
    const char* FileName = "./hello.cl";
    char* SourceString;
    size_t SourceSize;
    
    fp = fopen(FileName, "r");
    if (!fp)
    {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(EXIT_FAILURE);
    }
    SourceString = (char*) malloc(MAX_SOURCE_SIZE);
    SourceSize = fread(SourceString, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    
    // 2. Get Platform and Device Info
    Ret = clGetPlatformIDs(1, &PlatformID, &RetNumPlatforms);
    Ret = clGetDeviceIDs(PlatformID, CL_DEVICE_TYPE_DEFAULT, 1, &DeviceID, &RetNumDevices);
    
    // 3. Create OpenCL Context
    Context = clCreateContext(nullptr, 1, &DeviceID, nullptr, nullptr, &Ret);
    
    // 4. Create command Queue
    CommandQueue = clCreateCommandQueue(Context, DeviceID, 0, &Ret);
    
    // 5. Create memory buffer
    MemObject = clCreateBuffer(Context, CL_MEM_READ_WRITE, MEM_SIZE * sizeof(char), nullptr, &Ret);
    
    // 6. Create kernel program from source
    Program = clCreateProgramWithSource(Context, 1, (const char**)&SourceString, (const size_t*)&SourceSize, &Ret);
    
    // 7. Build kernel program
    Ret = clBuildProgram(Program, 1, &DeviceID, nullptr, nullptr, nullptr);
    
    // 8. Create OpenCL kernel
    Kernel = clCreateKernel(Program, "hello", &Ret);
    
    // 9. Set OpenCl kernel parametrs
    Ret = clSetKernelArg(Kernel, 0, sizeof(cl_mem), (void *)&MemObject);
    
    // 10. Execute OpenCL Kernel
    Ret = clEnqueueTask(CommandQueue, Kernel, 0, nullptr, nullptr);
    
    // 11. Copy result from memory Buffer
    Ret = clEnqueueReadBuffer(CommandQueue, MemObject, CL_TRUE, 0, MEM_SIZE * sizeof(char), StringResult, 0, nullptr, nullptr);
    
    // 12. Display results
    printf(">> %s\n", StringResult);
    
    // 13. Finalisation
    clFlush(CommandQueue);
    clFinish(CommandQueue);
    clReleaseKernel(Kernel);
    clReleaseProgram(Program);
    clReleaseMemObject(MemObject);
    clReleaseCommandQueue(CommandQueue);
    clReleaseContext(Context);
    
    // 13. Free RAM
    free(SourceString);
    
    // EXIT
    return 0;
}
