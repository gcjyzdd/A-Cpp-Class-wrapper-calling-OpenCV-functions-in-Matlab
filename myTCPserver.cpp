
#include "myTCPserver.hpp"

using namespace cv;

MyTCPServer::MyTCPServer(int port): recvFlag(true)
{
    printf("Port No = %d\n", port);
    
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
    }
    
    printf("Initialised.\n");
    
    //Create a socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d", WSAGetLastError());
    }
    
    printf("Socket created.\n");
    
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
    
    //Bind
    if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d", WSAGetLastError());
    }
    
    printf("Bind done\n");
    
    //Listen to incoming connections
    listen(s, 3);
    
    //Accept and incoming connection
    printf("Waiting for incoming connections...\n");
    
    return;
    
}

void MyTCPServer::wait()
{
    int c;
    
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s, (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d", WSAGetLastError());
    }
    recvFlag = true;
    printf("Connection accepted\n");
}

void MyTCPServer::waitFlag()
{
    recvFlag = false;
    int size, read_size, stat, packet_index;    
    char read_buffer[256];
    
    //Send Picture as Byte Array
    if (DB_PRINT) { printf("Sending Picture as Byte Array\n"); }
    
    int flag;
    do { //Read while we get errors that are due to signals.
        stat = recv(new_socket, (char*)&flag, sizeof(int), 0);
        if (DB_PRINT) { printf("Bytes read: %i\n", stat); }
    } while (stat < 0);
    
    if(flag == 1)
    {
        recvFlag=true;
    }
    if (DB_PRINT) {
        printf("Received data in socket\n");
        //std::cout << "received: "<<read_buffer << std::endl;
        printf("Socket data: %d\n", read_buffer);
    }
    
}

void MyTCPServer::encodeImg(Mat& input)
{
    cv::imencode(".jpeg", input, buff_, param_);
}

int MyTCPServer::init(int height, int width)
{
    // Set encoding parameters
    if(!param_.empty())
    {
        param_.push_back( cv::IMWRITE_JPEG_QUALITY);
        param_.push_back( 80);//default(95) 0-100
    }
    // Allocate Mat buffer
    imgBuff_ = Mat::zeros(height, width, CV_8UC3);
    
    return 0;
}

int MyTCPServer::sendImg(const mxArray* input)
{
    imgBuff_ = cv::Mat(960, 1280, CV_8UC3, (uchar*)mxGetPr(input));
    encodeImg( imgBuff_ );
    size_t len = buff_.size();
    if (recvFlag)
    {
        return sendImg_(reinterpret_cast<char*>(buff_.data()), len);
    }
    else
    {
        return 1;
    }
}

int MyTCPServer::sendImg_(char * ptr, size_t len)
{
    recvFlag = false;
    int size, read_size, stat, packet_index;
    const int batch = 10240;
    char read_buffer[256];
    packet_index = 1;
    
    size = len;
    //Send Picture Size
    if (DB_PRINT) { printf("Sending Picture Size %d\n", len); }
    send(new_socket, (char *)&size, sizeof(int), 0);
    
    //return 0;
    
    //Send Picture as Byte Array
    if (DB_PRINT) { printf("Sending Picture as Byte Array\n"); }
    
    do { //Read while we get errors that are due to signals.
        stat = recv(new_socket, read_buffer, 255, 0);
        if (DB_PRINT) { printf("Bytes read: %i\n", stat); }
    } while (stat < 0);
    
    if (DB_PRINT) {
        printf("Received data in socket\n");
        //std::cout << "received: "<<read_buffer << std::endl;
        printf("Socket data: %s\n", read_buffer);
    }
    int n = len / (batch);
    int rem = len % (batch);
    
    int total = 0;
    for (int ii = 0;ii < n;ii++)
    {
        read_size = batch;
        do {
            stat = send(new_socket, ptr, read_size, 0);
        } while (stat < 0);
        ptr += batch;
        total += batch;
        
        if (DB_PRINT) {
            printf("Packet Number: %i\n", packet_index);
            printf("Packet Size Sent: %i\n", read_size);
            printf(" \n");
            printf(" \n");
            packet_index++;
        }
    }
    if (rem > 0) {
        read_size = rem;
        do {
            stat = send(new_socket, ptr, read_size, 0);
        } while (stat < 0);
        if (DB_PRINT) {
            printf("Packet Number: %i\n", packet_index);
            printf("Packet Size Sent: %i\n", read_size);
            printf(" \n");
            printf(" \n");
            packet_index++;
            total += read_size;
        }
        ptr += read_size;
    }
    printf("Image successfully Sent! Total Size = %d\n", total);
    ptr -= total;
    return 0;
}
