#pragma once
#include <CommonTypesAPI.h>
#include <windows.h>
#include <pqxx/pqxx>  
#include <string>
class ConnectToSQL
{
public:
    void Update(std::string message, int messageID);
    void UpdateBluFor(std::string message, int messageID);
    void UpdateOpFor(std::string message, int messageID);
    std::string ReadandRemove();
    static ConnectToSQL& Get()
    {
        static ConnectToSQL instance;
        return instance;
    }
};