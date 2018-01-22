#include "mex.h"
#include "class_handle.hpp"
#include <stdio.h>
#include <iostream>

#include "myTCPserver.hpp"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{	
    // Get the command string
    char cmd[64];
	if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
		mexErrMsgTxt("First input should be a command string less than 64 characters long.");
        
    // New
    if (!strcmp("new", cmd)) {
        // Check parameters
        if (nlhs != 1)
            mexErrMsgTxt("New: One output expected.");
        // Return a handle to a new C++ instance
        mexPrintf("Input:%d\n",mxGetScalar(prhs[1]));
        plhs[0] = convertPtr2Mat<MyTCPServer>(new MyTCPServer((int)mxGetScalar(prhs[1])));
        return;
    }
    
    // Check there is a second input, which should be the class instance handle
    if (nrhs < 2)
		mexErrMsgTxt("Second input should be a class instance handle.");
    
    // Delete
    if (!strcmp("delete", cmd)) {
        // Destroy the C++ object
        destroyObject<MyTCPServer>(prhs[1]);
        // Warn if other commands were ignored
        if (nlhs != 0 || nrhs != 2)
            mexWarnMsgTxt("Delete: Unexpected arguments ignored.");
        return;
    }
    
    // Get the class instance pointer from the second input
    //dummy *dummy_instance = convertMat2Ptr<dummy>(prhs[1]);
    MyTCPServer *tcp_instance = convertMat2Ptr<MyTCPServer>(prhs[1]);
    
    // Call the various class methods
    // wait    
    if (!strcmp("wait", cmd)) {
        // Check parameters
        if (nlhs < 0 || nrhs > 3)
            mexErrMsgTxt("wait: Unexpected arguments.");
         
        // Call the method
		tcp_instance->wait();        
        return;
    }
    // waitFlag    
    if (!strcmp("waitFlag", cmd)) {
        // Check parameters
        if (nlhs < 0 || nrhs > 3)
            mexErrMsgTxt("wait: Unexpected arguments.");
         
        // Call the method
		tcp_instance->waitFlag();        
        return;
    }    
    // init    
    if (!strcmp("init", cmd)) {
        // Check parameters
        if (nlhs < 0 || nrhs < 3)
            mexErrMsgTxt("init: Unexpected arguments.");
        
        int height = (int)mxGetScalar(prhs[2]);
        int width = (int)mxGetScalar(prhs[3]);
        mexPrintf("height = %d, width = %d\n", height, width);  
        // Call the method
		plhs[0] = mxCreateDoubleScalar(tcp_instance->init(height, width));        
        return;
    }
    // sendImg    
    if (!strcmp("sendImg", cmd)) {
        // Check parameters
        if (nlhs < 0 || nrhs < 2)
            mexErrMsgTxt("sendImg: Unexpected arguments.");
        int len;
        // Call the method
		plhs[0] = mxCreateDoubleScalar(tcp_instance->sendImg(prhs[2]));        
        return;
    }
    
    // Got here, so command not recognized
    mexErrMsgTxt("Command not recognized.");
}
