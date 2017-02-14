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
    
    // 3. Get all platforms
    clGetPlatformIDs(0, nullptr, &PlatformCount);
    Platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * PlatformCount);
    clGetPlatformIDs(PlatformCount, Platforms, nullptr);
    
    // 4. Get all devices
    cl_uint TotalDevices = 0;
    for(size_t i = 0; i < PlatformCount; i++)
    {
        cl_uint devicesCount;
        // Get all devices
        clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &devicesCount);
        TotalDevices += devicesCount;
    }

    Devices = (cl_device_id**)malloc(sizeof(cl_device_info) * TotalDevices);
    DevicesCount = (cl_uint*)malloc(sizeof(cl_uint) * TotalDevices);

    for(size_t i = 0; i < PlatformCount; i++)
    {
        clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &DevicesCount[i]);
        Devices[i] = (cl_device_id*)malloc(sizeof(cl_device_info) * DevicesCount[i]);
        clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, DevicesCount[i], Devices[i], nullptr);
    }
}

Informer::~Informer()
{
    free(PlatformAttributeNames);
    free(PlatformAttributeTypes);
    free(DeviceAttributeNames);
    free(DeviceAttributeTypes);
    free(Platforms);
    free(DevicesCount);
    for(size_t i = 0; i < PlatformCount; i++) free(Devices[i]);
    free(Devices);
}

void Informer::PrintPlatformCount() const
{
    printf(">> Platform Count is: %i\n", PlatformCount);
    printf("\n");
}

void Informer::PrintDeviceCount() const
{
    for(size_t i = 0; i < PlatformCount; i++)
    {
        printf(">> Platform #%i\n", PlatformCount);
        printf(">> Devices count #%i\n", DevicesCount[i]);
    }
    printf("\n");
}

void Informer::PrintPlatfromsInfo()
{
    size_t InfoSize;
    char* Info;
    
    for(size_t i = 0; i < PlatformCount; i++)
    {
        printf(">> Platform %lu info\n", i + 1);
        // Print platform data
        for (size_t j = 0; j < PlatformAttributeCount; j++) {
            // Get value size
            clGetPlatformInfo(Platforms[i], PlatformAttributeTypes[j], 0, nullptr, &InfoSize);
            Info = (char*) malloc(InfoSize);
            
            // Get platform attribute value
            clGetPlatformInfo(Platforms[i], PlatformAttributeTypes[j], InfoSize, Info, nullptr);
            
            printf(">> %lu.%lu %-11s: %s\n", i + 1, j + 1, PlatformAttributeNames[j], Info);
            
            // Deallocate
            free(Info);
        }
        printf("\n");
    }
}

void Informer::PrintDevicesInfo()
{
    size_t InfoSize;
    char* Info;
    cl_uint MaxComputeUnits;
    
    // Loop through all platforms
    for(size_t i = 0; i < PlatformCount; i++)
    {
        
        for(size_t m = 0; m < DevicesCount[i]; m++)
        {
            printf(">> Platform %lu, Device %lu info\n", i + 1, m + 1);
            
            for(size_t t = 0; t < DeviceAttributeCount; t++)
            {
                clGetDeviceInfo(Devices[i][m], DeviceAttributeTypes[t], 0, nullptr, &InfoSize);
                Info = (char*) malloc(InfoSize);
                clGetDeviceInfo(Devices[i][m], DeviceAttributeTypes[t], InfoSize, Info, nullptr);

                printf(">> %lu. %s: %s\n", t + 1, DeviceAttributeNames[t], Info);

                // Deallocate
                free(Info);
            }


            // Print parallel compute units
            clGetDeviceInfo(Devices[i][m], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(MaxComputeUnits), &MaxComputeUnits, nullptr);
            printf(">> %d. Parallel compute units: %d\n", DeviceAttributeCount + 1, MaxComputeUnits);

            printf("\n");
        }
    }
}
