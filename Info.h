//
// Created by yongheng on 22-7-15.
//

#ifndef INFO_H
#define INFO_H

#include "Tool.h"
#include <cstdio>

class Info{
    string _webname;
    string _account;
    string _password;
    string _email;

public:
    Info(){  }
    Info(string info_s){
        string webname,account,password,email;
        int pos = 0;
        while(info_s[pos] != '\n'){
            webname += info_s[pos];
            pos ++;
        }
        pos ++;
        while(info_s[pos] != '\n'){
            account += info_s[pos];
            pos ++;
        }
        pos ++;
        while(info_s[pos] != '\n'){
            password += info_s[pos];
            pos ++;
        }
        pos ++;
        while(pos < info_s.size()){
            email += info_s[pos];
            pos ++;
        }

        _webname = webname;
        _account = account;
        _password = password;
        _email = email;
    }
    Info(string webname,string account,string password){
        _webname = webname;
        _account = account;
        _password = password;
    }
    Info(string webname,string account,string password,string email){
        _webname = webname;
        _account = account;
        _password = password;
        _email = email;
    }


    void SetWebName(string web){
        _webname = web;
    }
    void SetAccount(string account){
        _account = account;
    }
    void SetPassword(string password){
        _password = password;
    }
    void SetEmail(string email){
        _email = email;
    }


    string GetWebName(){
        return _webname;
    }
    string GetAccount(){
        return _account;
    }
    string GetPassWord(){
        return _password;
    }
    string GetEmail(){
        return _email;
    }

    string to_string(){
        // char buffer[1024] = {0};
        // sprintf(buffer,"%s\n%s\n%s\n%s\n", _webname.c_str(),_account.c_str(),_password.c_str(),_email.c_str());
//
        // string str(buffer);
        // cout << "str" << str << endl;
//
        return _webname + "\n"
               + _account + "\n"
               + _password + "\n"
               + _email ;
    }

    bool operator == (Info r_info){
        if(this->_webname == r_info._webname
           || this->_account == r_info._account
           || this->_password == r_info._password
           || this->_email == r_info._email
                ){
            return true;
        }
        else
            return false;
    }

    bool operator != (Info r_info){
        return !(*this == r_info);
    }

    friend istream &operator >>(istream &in,Info &info){
        string webname,account,password,email;
        in >> webname >> account >> password >> email;
        Info temp_info(webname,account,password,email);
        info = temp_info;
        return in;
    }

    friend ostream &operator <<(ostream &out,Info info){

        // string str = info.to_string();
        // out << str;

        string str;
        str = str + "WebName:" + info.GetWebName() + "\n"
            + "Account:" + info.GetAccount() + "\n"
            + "PassWord:" + info.GetPassWord() + "\n"
            + "Email:" + info.GetEmail();
        out << str;

        return out;
    }



};


#endif


