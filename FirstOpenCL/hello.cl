// https://developer.apple.com/library/content/samplecode/OpenCLOfflineCompilation/Listings/main_c.html#//apple_ref/doc/uid/DTS40011196-main_c-DontLinkElementID_5

/**
* The OpenCL C compilation commands for 32/64bit CPUs and GPUs:
*
* As an example, to compile for a 32bit GPU:
* openclc -emit-llvm -c -arch gpu_32 kernel.cl -o kernel.bc
*/

__kernel void hello(__global char* string)
{
    string[0] = 'H';
    string[1] = 'E';
    string[2] = 'L';
    string[3] = 'L';
    string[4] = 'O';
    string[5] = '-';
    string[6] = 'O';
    string[7] = 'P';
    string[8] = 'E';
    string[9] = 'N';
    string[10] = 'C';
    string[11] = 'L';
    string[12] = '\0';
}
