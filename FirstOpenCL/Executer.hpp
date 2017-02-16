#ifndef Executer_hpp
#define Executer_hpp

#include <stdio.h>
#include <OpenCL/opencl.h>

class Executer
{
private:
    enum Constants
    {
        MAX_SOURCE_SIZE = 0x10000
    };
    
public:
    explicit Executer(const char* fileName, int memSize);
    ~Executer();
protected:
    cl_int TempRet;
    
    char* SourceString;
    size_t SourceSize;
    
    cl_platform_id PlatformID = nullptr;
    cl_uint PlatformCount;
    
    cl_device_id DeviceID = nullptr;
    cl_uint DevicesCount;
    
    cl_context Context = nullptr;
    cl_command_queue CommandQueue = nullptr;
    cl_mem MemObject = nullptr;
    cl_program Program = nullptr;
    
    cl_kernel Kernel = nullptr;
    
    int MemSize;
        
private:
    friend class Informer;
};

#endif /* Executer_hpp */