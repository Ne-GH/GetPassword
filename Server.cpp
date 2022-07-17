#include "Tool.h"
#include "Info.h"
#include "InfoManager.h"
#include <netinet/in.h>
#include <stdio.h>

#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 100


InfoManager im("./test.database");

void SendMenu(int &sock,sockaddr &clntAddr,socklen_t &nSize){
    // char temp[BUF_SIZE];
    // recvfrom(sock, temp, BUF_SIZE, 0, &clntAddr, &nSize);
    string menu = im.ShowMenu();
    sendto(sock, menu.c_str(),menu.size(), 0, &clntAddr, nSize);

}

string GetChoose(int &sock,sockaddr &clntAddr,socklen_t &nSize){
    char choose_c[BUF_SIZE] = {0};  //缓冲区
    recvfrom(sock, choose_c, BUF_SIZE, 0, &clntAddr, &nSize);
    string choose(choose_c);
    return choose;
}

void AddInfo(int &sock,sockaddr &clntAddr,socklen_t &nSize){
    char info_c[BUF_SIZE] = {0};  //缓冲区
    recvfrom(sock, info_c, BUF_SIZE, 0, &clntAddr, &nSize);


    string info_s(info_c);
    cout << "get_string:" << info_s << endl;
    Info info(info_s);
    
    string tostr = info.to_string();
    cout << "to_string:" << tostr << endl;
    im.AddInfo(Info(info_s));
}

int main(){

    //创建套接字
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    //绑定套接字
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;  //使用IPv4地址
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY); //自动获取IP地址
    servAddr.sin_port = htons(1234);  //端口
    bind(sock, (sockaddr*)&servAddr, sizeof(sockaddr));

    //接收客户端请求
    sockaddr clntAddr;  //客户端地址信息
    socklen_t nSize = sizeof(sockaddr);
                            
                            

    while(1){

        string choose = GetChoose(sock, clntAddr,nSize);
        cout << sock << ":" << choose << endl;
        if(choose == "1"){

            string notic = "WebName:";
            sendto(sock, notic.c_str(),notic.size(), 0, &clntAddr, nSize);

            char webname[BUF_SIZE] = {0};
            recvfrom(sock, webname, BUF_SIZE, 0, &clntAddr, &nSize);
            printf("%s\n",webname);

            string find_result = im.FindInfo(webname);
            cout << find_result << endl;
            sendto(sock, find_result.c_str(),find_result.size(), 0, &clntAddr, nSize);

        }
        else if(choose == "2"){
            AddInfo(sock, clntAddr, nSize);
        }
        else if(choose == "3"){
            string str = "还没写";
            sendto(sock, str.c_str(),str.size(), 0, &clntAddr, nSize);
        }
        else if(choose == "Get_menu" || choose == "menu" ){
            SendMenu(sock, clntAddr, nSize);
        }
        else if(choose == "quit" || choose == "exit" || choose == "q"){

        }
        else{

        }

    }



    return 0;
}

