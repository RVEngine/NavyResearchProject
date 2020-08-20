#pragma once
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
    std::string ReadandRemoveWaypoint();
    void ConnectToSQL::UpdateFireTable(std::string message, int messageID);
    static ConnectToSQL& Get()
    {
        static ConnectToSQL instance;
        return instance;
    }
};