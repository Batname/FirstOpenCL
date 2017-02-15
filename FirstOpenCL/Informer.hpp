#ifndef Informer_hpp
#define Informer_hpp

#include <stdio.h>
#include <OpenCL/opencl.h>

class Informer
{
public:
    enum Status
    {
        I_DEBUG, I_RELEASE
    };
    
    explicit Informer(Status status);
    ~Informer();
    
    void PrintPlatformCount() const;
    void PrintDeviceCount() const;
    
    void PrintPlatfromsInfo();
    void PrintDevicesInfo();
    
    static void PrintExecuterInfo(class Executer* executer);
    
protected:
private:
    cl_uint PlatformCount;
    cl_platform_id* Platforms;
    cl_uint* DevicesCount;
    cl_device_id** Devices;
    
    char** PlatformAttributeNames;
    cl_platform_info* PlatformAttributeTypes;
    int PlatformAttributeCount;
    char** DeviceAttributeNames;
    cl_device_info* DeviceAttributeTypes;
    int DeviceAttributeCount;
    
    Status status;
};

#endif /* Informer_hpp */
