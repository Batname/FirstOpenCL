#include "ParallelExecuter.hpp"

ParallelExecuter::ParallelExecuter(KernelFile kFile) :
    Executer(kFile)
{
    AllocationSize = 4*4*sizeof(float);
    A = (float*) malloc(AllocationSize);
    B = (float*) malloc(AllocationSize);
    C = (float*) malloc(AllocationSize);
    
    // Init input data
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            A[i*4+j] = i*4+j+1;
            B[i*4+j] = j*4+i+1;
        }
    }
    
    // Create buffer object
    AMem = clCreateBuffer(Context, CL_MEM_READ_WRITE, AllocationSize, NULL, &ErrRet);
    CheckStatus("clCreateBuffer AMem", &ErrRet);
    BMem = clCreateBuffer(Context, CL_MEM_READ_WRITE, AllocationSize, NULL, &ErrRet);
    CheckStatus("clCreateBuffer BMem", &ErrRet);
    CMem = clCreateBuffer(Context, CL_MEM_READ_WRITE, AllocationSize, NULL, &ErrRet);
    CheckStatus("clCreateBuffer CMem", &ErrRet);
    
    // copy Data of A and B to Memory
    ErrRet |= clEnqueueWriteBuffer(CommandQueue, AMem, CL_TRUE, 0, AllocationSize, A, 0, nullptr, nullptr);
    ErrRet |= clEnqueueWriteBuffer(CommandQueue, BMem, CL_TRUE, 0, AllocationSize, B, 0, nullptr, nullptr);
    CheckStatus("clEnqueueWriteBuffer", &ErrRet);
    
    Kernel = clCreateKernel(Program, "dataParallel", &ErrRet);
    CheckStatus("dataParallel", &ErrRet);
    
    // Set kernel arguments
    ErrRet |= clSetKernelArg(Kernel, 0, sizeof(cl_mem), (void*)&AMem);
    ErrRet |= clSetKernelArg(Kernel, 1, sizeof(cl_mem), (void*)&BMem);
    ErrRet |= clSetKernelArg(Kernel, 2, sizeof(cl_mem), (void*)&CMem);
    CheckStatus("clSetKernelArg", &ErrRet);

    size_t global_item_size = 4;
    size_t local_item_size = 1;
    
    // Execute kernel as parallel
    ErrRet = clEnqueueNDRangeKernel(CommandQueue, Kernel, 1, nullptr, &global_item_size, &local_item_size, 0, NULL, NULL);
    CheckStatus("clEnqueueNDRangeKernel", &ErrRet);
}

void ParallelExecuter::PrintResult()
{
    // Transfer results to host
    ErrRet = clEnqueueReadBuffer(CommandQueue, CMem, CL_TRUE, 0, AllocationSize, C, 0, nullptr, nullptr);
    CheckStatus("clEnqueueReadBuffer", &ErrRet);

    /* Display Results */
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%7.2f ", C[i*4+j]);
        }
        printf("\n");
    }
}

ParallelExecuter::~ParallelExecuter()
{
    free(A);
    free(B);
    free(C);
    
    clReleaseMemObject(AMem);
    clReleaseMemObject(BMem);
    clReleaseMemObject(CMem);
}
