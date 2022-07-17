//
// Created by yongheng on 22-7-15.
//

#ifndef INFOMANAGER_H
#define INFOMANAGER_H

#include "Tool.h"
#include "Info.h"

class InfoManager{
    string _database_filename;

    vector<Info> _records;

public:

    InfoManager(){
        // _database_filename = "";
    }

    InfoManager(string database_file){
        _database_filename = database_file;
        InitInfoManager();
    }

    void InitInfoManager(){
        if(_database_filename == ""){
            cout << "没有指定DataBaseFile" << endl;
        }
        else{
            fstream file(_database_filename.c_str(),ios::in | ios::out);
            Info info;
            while(file >> info){


                _records.push_back(info);
            }
            file.close();
        }
        return;
    }


    void AddInfo(Info info){
        _records.push_back(info);
        OutputToFIle(info);
    }

    size_t Size(){
        return _records.size();
    }

    Info GetInfoByPos(size_t pos){
        return _records[pos];
    }


    void DelInfo(Info info){
        for(auto it = _records.begin();it != _records.end(); ){
            if(*it == info){
                it = _records.erase(it);
            }
            else{
                ++ it;
            }
        }
    }

    string FindInfo(string webname){
        string ret;
        for(auto info : _records){
            if(info.GetWebName() == webname){
                ret += info.to_string();
            }
        }
        return ret;
    }

    string ShowMenu(){
        string ret = "";
        ret = ret 
            + "1.Find a info\n"
            + "2.Add a info\n"
            + "3.Del a info\n"
            + "4.exit";
        return ret;
    }
    void ShowInfo(){
        for(auto info : _records){
            cout << info << endl;
        }
    }

    void OutputToFIle(Info info){
        fstream file(_database_filename.c_str(),ios::in | ios::out | ios::ate);

        cout << info << endl;

        file << info.GetWebName() << endl
             << info.GetAccount() << endl
             << info.GetPassWord() << endl
             << info.GetEmail() << endl;

        file.close();
    }

};

#endif

