//
//  MyExecuter.hpp
//  FirstOpenCL
//
//  Created by bat on 2/15/17.
//  Copyright © 2017 batlab. All rights reserved.
//

#ifndef MyExecuter_hpp
#define MyExecuter_hpp

#include <stdio.h>
#include "Executer.hpp"

class MyExecuter : public Executer
{
public:
    explicit MyExecuter(const char* fileName, int memSize);
    ~MyExecuter();
    
    void PrintResult();
    
protected:
private:
};


#endif /* MyExecuter_hpp */
