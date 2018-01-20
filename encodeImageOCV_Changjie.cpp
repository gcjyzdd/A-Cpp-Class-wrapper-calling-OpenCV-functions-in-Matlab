/*==========================================================
 * encodeImage.cpp -an interface encoding image using OpenCV
 *
 *
 *
 * This is a MEX-file for MATLAB.
 * Author: Changjie Guan<changjie.guan@tassinternational.com>
 * Date: Jan 19, 2018
 *
 *========================================================*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<winsock2.h>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

#include <chrono>  // for high_resolution_clock
#include <thread>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "10.87.4.34"  //"127.0.0.1"  //ip address of udp server
#define BUFLEN 512  //Max length of buffer
#define PORT 3456   //The port on which to listen for incoming data

#define DB_PRINT 0

#include "mex.h"
 
using namespace cv;

/* The computational routine */
void arrayProduct(mxArray* input)
{
    Mat img = Mat(960, 1280, CV_8UC3, (uchar*)mxGetPr(input));
    
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    moveWindow("Original Image", 100, 100);
    imshow("Original Image", img );
    
    // wait for a key
    cvWaitKey(0);
 
}

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, mxArray *prhs[])
{
    /* check for proper number of arguments */
    if(nrhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","One inputs required.");
    }
    
    mexPrintf("Input size = %d", mxGetNumberOfElements(prhs[0]));      
    
    /* create a pointer to the real data in the input matrix  */
    //inMatrix = reinterpret_cast<uchar*>(mxGetPr(prhs[0]));
   
    /* call the computational routine */
    arrayProduct(prhs[0]);
}
