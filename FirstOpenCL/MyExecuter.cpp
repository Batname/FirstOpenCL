//
//  MyExecuter.cpp
//  FirstOpenCL
//
//  Created by bat on 2/15/17.
//  Copyright © 2017 batlab. All rights reserved.
//

#include "MyExecuter.hpp"

#include <assert.h>

MyExecuter::MyExecuter(const char* fileName, int memSize) :
    Executer(fileName, memSize)
{
    // 8. Create OpenCL kernel
    Kernel = clCreateKernel(Program, "hello", &TempRet);
    assert(TempRet == 0 && "Error clCreateKernel");

    
    // 9. Set OpenCl kernel parametrs
    TempRet = clSetKernelArg(Kernel, 0, sizeof(cl_mem), (void *)&MemObject);
    assert(TempRet == 0 && "Error clSetKernelArg");
    
    // 10. Execute OpenCL Kernel
    TempRet = clEnqueueTask(CommandQueue, Kernel, 0, nullptr, nullptr);
    assert(TempRet == 0 && "Error clEnqueueTask");
}

void MyExecuter::PrintResult()
{
    char* StringResult[MemSize];
    // 11. Copy result from memory Buffer
    TempRet = clEnqueueReadBuffer(CommandQueue, MemObject, CL_TRUE, 0, MemSize, StringResult, 0, nullptr, nullptr);
    assert(TempRet == 0 && "Error clEnqueueReadBuffer");
    
    // 12. Display results
    printf(">> %s\n", StringResult);
}

MyExecuter::~MyExecuter()
{

}
