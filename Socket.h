//
// Created by yongheng on 22-7-15.
//

#ifndef SOCKET_H
#define SOCKET_H

#include "Tool.h"
#include "Info.h"
#include <cstdio>
#include <sys/socket.h>

class Socket{
    int _sock;
    struct sockaddr_in _sockadd;
    string _ip;
    int _port;
    struct sockaddr_in _clnt_addr;
    int _client_sock;
public:

    // Socket(string ip,int port){
        // _ip = ip;
        // _sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        // memset(&_sockadd, 0,sizeof(_sockadd));
        // _sockadd.sin_family = AF_INET;
        // _sockadd.sin_addr.s_addr = inet_addr(_ip.c_str());
        // _sockadd.sin_port = htons(_port);
    // }

    Socket(string ip,int port){
        _sock = socket(PF_INET, SOCK_DGRAM, 0);
        memset(&_sockadd, 0,sizeof(_sockadd));
        _sockadd.sin_family = AF_INET;
        _sockadd.sin_addr.s_addr = inet_addr(_ip.c_str());
        _sockadd.sin_port = htons(_port);
    }

    // void InitClient(){
//
    // }

    // void InitClient(){
        // connect(_sock,(struct sockaddr *)&_sockadd,sizeof(_sockadd));
        // _client_sock = _sock;
    // }
    // void InitServer(){
        // bind(_sock,(struct sockaddr *)&_sockadd,sizeof(struct sockaddr));
        // listen(_sock, 20);
        // socklen_t clnt_addr_size = sizeof(_clnt_addr);
        // _client_sock = accept(_sock, (struct sockaddr*)&_clnt_addr, &clnt_addr_size);
        // cout << _client_sock << endl;
    // }
    // int GetSock(){
        // return _sock;
    // }


    // void Wirte(string str){
        // string size = GetMessageSize(str.size());
        // string message = size + str;
        // write(_client_sock, message.c_str(), message.size());
    // }
//
    // string Read(){
//
        // char size[4] = {0};
        // read(_client_sock, size, 4);
        // int message_size = GetMessageSize(size);
//
        // char buffer[512] = {0};
        // read(_client_sock, buffer, message_size);
        // return string(buffer);
    // }

    string GetMessageSize(int num){
        unsigned char mask = 0xff;
        string ret = "";
        ret += (char)(num & mask);
        num >>= 8;
        ret += (num & mask);
        num >>= 8;
        ret += (num & mask);
        num >>= 8;
        ret += (num & mask);

        char temp;
        temp = ret[0];
        ret[0] = ret[3];
        ret[3] = temp;
        temp = ret[1];
        ret[1] = ret[2];
        ret[2] = temp;
        return ret;
    }
    int GetMessageSize(char str[4]){
        int ret = 0;
        ret |= str[0];
        ret <<= 8;
        ret |= str[1];
        ret <<= 8;
        ret |= str[2];
        ret <<= 8;
        ret |= str[3];
        return ret;
    }

};

#endif

