#ifndef Executer_hpp
#define Executer_hpp

#include <stdio.h>
#include <OpenCL/opencl.h>

class Executer
{
public:
    enum Constants
    {
        MAX_SOURCE_SIZE = 0x10000,
        MAX_BINARY_SIZE = 0x100000
    };
    
    enum class FileType
    {
        EBinary, EText
    };
    
    struct KernelFile
    {
        const char* fileName;
        FileType type;
        
    };
    
public:
    explicit Executer(KernelFile kFile);
    ~Executer();
protected:
    cl_int ErrRet;
    
    unsigned char* SourceBuffer;
    size_t SourceSize;
    
    cl_int BinaryStatus;
    
    cl_platform_id PlatformID = nullptr;
    cl_uint PlatformCount;
    
    cl_device_id DeviceID = nullptr;
    cl_uint DevicesCount;
    
    cl_context Context = nullptr;
    cl_command_queue CommandQueue = nullptr;
    cl_program Program = nullptr;
    
    cl_kernel Kernel = nullptr;
        
    virtual void CheckStatus(const char* Msg, cl_int* Err) const;
private:
    friend class Informer;
};

#endif /* Executer_hpp */
