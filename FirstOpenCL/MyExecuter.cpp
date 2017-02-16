//
//  MyExecuter.cpp
//  FirstOpenCL
//
//  Created by bat on 2/15/17.
//  Copyright © 2017 batlab. All rights reserved.
//
// https://developer.apple.com/library/content/samplecode/OpenCLOfflineCompilation/Listings/main_c.html#//apple_ref/doc/uid/DTS40011196-main_c-DontLinkElementID_5

#include "MyExecuter.hpp"

#include <assert.h>

MyExecuter::MyExecuter(KernelFile kFile, int memSize) :
    Executer(kFile, memSize)
{
    // 8. Create OpenCL kernel
    Kernel = clCreateKernel(Program, "hello", &ErrRet);
    CheckStatus("clCreateKernel", &ErrRet);

    
    // 9. Set OpenCl kernel parametrs
    ErrRet |= clSetKernelArg(Kernel, 0, sizeof(cl_mem), (void *)&MemObject);
    CheckStatus("clSetKernelArg", &ErrRet);
    
    // 10. Execute OpenCL Kernel
    ErrRet = clEnqueueTask(CommandQueue, Kernel, 0, nullptr, nullptr);
    CheckStatus("clEnqueueTask", &ErrRet);
}

void MyExecuter::PrintResult()
{
    char* StringResult[MemSize];
    // 11. Copy result from memory Buffer
    ErrRet = clEnqueueReadBuffer(CommandQueue, MemObject, CL_TRUE, 0, MemSize, StringResult, 0, nullptr, nullptr);
    CheckStatus("clEnqueueReadBuffer", &ErrRet);
    
    // 12. Display results
    printf(">> %s\n", StringResult);
}

MyExecuter::~MyExecuter()
{

}
