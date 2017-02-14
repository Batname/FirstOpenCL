#include "Informer.hpp"
#include <string.h>
#include <stdio.h>

Informer::Informer()
{
    // 1. Define platform info to print
    const char* platformAttributeNames[] =
    {
        "Name", "Vendor",
        "Version", "Profile", "Extensions"
    };
    PlatformAttributeNames = (char**)malloc(sizeof(platformAttributeNames));
    memcpy(PlatformAttributeNames, platformAttributeNames, sizeof(platformAttributeNames));
    
    cl_platform_info platformAttributeTypes[] =
    {
        CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
        CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS
    };
    PlatformAttributeTypes = (cl_platform_info*)malloc(sizeof(platformAttributeTypes));
    memcpy(PlatformAttributeTypes, platformAttributeTypes, sizeof(platformAttributeTypes));

    PlatformAttributeCount = sizeof(platformAttributeNames) / sizeof(char*);
    
    // 2. Define devices info to print
    const char* deviceAttributeNames[] =
    {
        "Name", "Device Version", "Driver Version", "OpenCL C Version"
    };
    DeviceAttributeNames = (char**)malloc(sizeof(deviceAttributeNames));
    memcpy(DeviceAttributeNames, deviceAttributeNames, sizeof(deviceAttributeNames));
    
    cl_device_info deviceAttributeTypes[] =
    {
        CL_DEVICE_NAME, CL_DEVICE_VERSION, CL_DRIVER_VERSION,
        CL_DEVICE_OPENCL_C_VERSION
    };
    DeviceAttributeTypes = (cl_device_info*)malloc(sizeof(deviceAttributeTypes));
    memcpy(DeviceAttributeTypes, deviceAttributeTypes, sizeof(deviceAttributeTypes));
    
    DeviceAttributeCount = sizeof(deviceAttributeNames) / sizeof(char*);
}

Informer::~Informer()
{
    free(PlatformAttributeNames);
    free(PlatformAttributeTypes);
    free(DeviceAttributeNames);
    free(DeviceAttributeTypes);
//    free(Devices);
//    free(Platforms);
}

void Informer::PrintPlatformCount() const
{
}

void Informer::PrintDeviceCount() const
{
}

void Informer::PrintPlatfromsInfo()
{
}

void Informer::PrintDevicesInfo()
{
}
