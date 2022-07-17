
#include "Info.h"
#include "InfoManager.h"
#include "Tool.h"
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 100

string GetMenu(int &sock,sockaddr_in &servAddr,sockaddr &fromAddr,socklen_t &addrLen){
    string get_menu = "Get_menu";
    sendto(sock, get_menu.c_str(), get_menu.size(), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));

    char menu_c[BUF_SIZE] = {0};
    recvfrom(sock, menu_c, BUF_SIZE, 0, &fromAddr, &addrLen);
    string menu(menu_c);
    return menu;
}

void SendChoose(string choose,int &sock,sockaddr_in &servAddr,sockaddr &fromAddr,socklen_t &addrLen){
    sendto(sock, choose.c_str(), choose.size(), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
}

string FindInfo(int &sock,sockaddr_in &servAddr,sockaddr &fromAddr,socklen_t &addrLen){

    char notic_c[BUF_SIZE] = {0};
    recvfrom(sock, notic_c, BUF_SIZE, 0, &fromAddr, &addrLen);
    string notic(notic_c);
    cout << notic;

    string webname;
    cin >> webname;

    sendto(sock, webname.c_str(), webname.size(), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));

    char find_resul_c[BUF_SIZE] = {0};
    recvfrom(sock, find_resul_c, BUF_SIZE, 0, &fromAddr, &addrLen);

    string find_resul(find_resul_c);
    return find_resul;
}

void AddInfo(int &sock,sockaddr_in &servAddr,sockaddr &fromAddr,socklen_t &addrLen){
    string webname,account,password,email;
    
    cout << "webname:";
    cin >> webname;
    cout << "account:";
    cin >> account;
    cout << "password:";
    cin >> password;
    cout << "email:";
    cin >> email;

    Info info(webname,account,password,email);
    string info_s = info.to_string();
    cout << "info_s:" << info_s << endl;
    cout << "<<:" << info << endl;
    sendto(sock, info_s.c_str(), info_s.size(), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));

}

void Exit(int &sock,sockaddr_in &servAddr,sockaddr &fromAddr,socklen_t &addrLen){
    string exit = "exit";
    sendto(sock, exit.c_str(), exit.size(), 0, (struct sockaddr*)&servAddr, sizeof(servAddr));
}

int main(){
    //初始化DLL
    //创建套接字
    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    //服务器地址信息
    sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));  //每个字节都用0填充
    servAddr.sin_family = PF_INET;
    servAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servAddr.sin_port = htons(1234);

    //不断获取用户输入并发送给服务器，然后接受服务器数据
    sockaddr fromAddr;
    socklen_t addrLen = sizeof(fromAddr);
    cout << "输入 get or menu 可以获取菜单" << endl;
    while(1){

        string choose;
        cin >> choose;

        if(choose == "1"){
            SendChoose(choose, sock, servAddr, fromAddr, addrLen);
            string find_resul = FindInfo(sock, servAddr, fromAddr, addrLen);
            if(find_resul == "")
                cout << "未找到相关信息" << endl;
            else
                cout << find_resul << endl;

            cout << GetMenu(sock, servAddr, fromAddr, addrLen) << endl;

        }
        else if(choose == "2"){
            SendChoose(choose, sock, servAddr, fromAddr, addrLen);
            AddInfo(sock, servAddr, fromAddr, addrLen);
            cout << GetMenu(sock, servAddr, fromAddr, addrLen) << endl;
        }
        else if(choose == "3"){

            cout << GetMenu(sock, servAddr, fromAddr, addrLen) << endl;
        }
        else if(choose == "4" || choose == "quit" || choose == "exit" || choose == "q"){
            Exit(sock, servAddr, fromAddr, addrLen);
            return 0;
        }
        else if(choose == "get" || choose == "menu"){
            cout << GetMenu(sock, servAddr, fromAddr, addrLen) << endl;
        }
        else{
            cout << "没有这个选项" << endl;
            cout << GetMenu(sock, servAddr, fromAddr, addrLen) << endl;
        }

    }

    return 0;
}

