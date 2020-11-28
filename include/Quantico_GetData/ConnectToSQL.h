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
    void setEnemyVisbility(std::string message, int messageID);
    void removeEnemyVisbility();
    void sendFireData(std::string message, int messageID, std::string time);
    void sendPosition(std::string message, int messageID, std::string time);
    void UpdateFireTable(std::string message, int messageID);
    std::string ConnectToSQL::ReadandRemoveMovementCommand();
    static ConnectToSQL& Get()
    {
        static ConnectToSQL instance;
        return instance;
    }
};