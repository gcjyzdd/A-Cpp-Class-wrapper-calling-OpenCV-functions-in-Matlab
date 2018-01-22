#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <string>

#include <chrono>  // for high_resolution_clock
#include <thread>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#include "mex.h"

#define DB_PRINT 1

using namespace cv;

class MyTCPServer
{
public:
    MyTCPServer(int port);
    ~MyTCPServer()
    {
        closesocket(s);
        WSACleanup();
    }
    
    //int init(int port);
    
    int sendImg(const mxArray* input);        
    
    int init(int height, int width);
    
    void encodeImg(Mat& input);
    
    void wait();
    
    void waitFlag();
    
private:
    WSADATA wsa;
    SOCKET s, new_socket;
    struct sockaddr_in server, client;
    Mat imgBuff_;
    std::vector<uchar> buff_;
    std::vector<int> param_;
    
    int sendImg_(char *ptr, size_t len);
    
    bool recvFlag;
};


#include "myTCPserver.cpp"
#endif