// include C libs
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
    Informer informer;
    return 0;
    
    
    // Define variables
    cl_uint PlatformCount;
    cl_platform_id* Platforms;
    cl_uint DevicesCount;
    cl_device_id* Devices;
    
    size_t InfoSize;
    char* Info;
    
    const char* PlatformAttributeNames[] =
    {
        "Name", "Vendor",
        "Version", "Profile", "Extensions"
    };
    const cl_platform_info PlatformAttributeTypes[] =
    {
        CL_PLATFORM_NAME, CL_PLATFORM_VENDOR,
        CL_PLATFORM_VERSION, CL_PLATFORM_PROFILE, CL_PLATFORM_EXTENSIONS
    };
    const int PlatformAttributeCount = sizeof(PlatformAttributeNames) / sizeof(char*);
    
    const char* DeviceAttributeNames[] =
    {
        "Name", "Device Version", "Driver Version", "OpenCL C Version"
    };
    const cl_device_info DeviceAttributeTypes[]
    {
        CL_DEVICE_NAME, CL_DEVICE_VERSION, CL_DRIVER_VERSION,
        CL_DEVICE_OPENCL_C_VERSION
    };
    const int DeviceAttributeCount = sizeof(DeviceAttributeNames) / sizeof(char*);
    
    cl_uint MaxComputeUnits;
    
    
    
    // Get allPlatforms
    clGetPlatformIDs(0, nullptr, &PlatformCount);
    Platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * PlatformCount);
    clGetPlatformIDs(PlatformCount, Platforms, nullptr);
    printf(">> Platform Count is: %i\n", PlatformCount);
    printf("\n");
    
    // Loop through all platforms
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
        
        
        // Get all devices
        clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, 0, nullptr, &DevicesCount);
        Devices = (cl_device_id*) malloc(sizeof(cl_device_id) * DevicesCount);
        clGetDeviceIDs(Platforms[i], CL_DEVICE_TYPE_ALL, DevicesCount, Devices, nullptr);
        
        for(size_t m = 0; m < DevicesCount; m++)
        {
            printf(">> Device %lu info\n", m + 1);
            
            for(size_t t = 0; t < DeviceAttributeCount; t++)
            {
                clGetDeviceInfo(Devices[m], DeviceAttributeTypes[t], 0, nullptr, &InfoSize);
                Info = (char*) malloc(InfoSize);
                clGetDeviceInfo(Devices[m], DeviceAttributeTypes[t], InfoSize, Info, nullptr);
                
                printf(">> %lu. %s: %s\n", t + 1, DeviceAttributeNames[t], Info);
                
                // Deallocate
                free(Info);
            }
            

            // Print parallel compute units
            clGetDeviceInfo(Devices[m], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(MaxComputeUnits), &MaxComputeUnits, nullptr);
            printf(">> %d. Parallel compute units: %d\n", DeviceAttributeCount + 1, MaxComputeUnits);
            
            printf("\n");
        }
        
        // Deallocate
        free(Devices);
    }
    
    // Deallocate resources
    free(Platforms);
    
    return 0;
}
