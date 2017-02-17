#ifndef ParallelExecuter_hpp
#define ParallelExecuter_hpp

#include <stdio.h>
#include <OpenCL/OpenCL.h>
#include "Executer.hpp"

class ParallelExecuter : public Executer
{
public:
    explicit ParallelExecuter(KernelFile kFile);
    ~ParallelExecuter();
    
    void PrintResult();
protected:
private:
    cl_mem AMem;
    cl_mem BMem;
    cl_mem CMem;
    
    float* A; // passed var
    float* B; // passed var
    float* C; // For store result
    
    int AllocationSize;
};

#endif /* ParallelExecuter_hpp */
