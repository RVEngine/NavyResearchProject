#pragma once
#pragma once
#include <CommonTypesAPI.h>
#include <string>
class ClientToSocket2
{
public:
    void Connect();
    void sendMessage(std::string);
    void recieveMessage();
    void Disconnect();
    static ClientToSocket2& Get()
    {
        static ClientToSocket2 instance;
        return instance;
    }



};