#pragma once
#include <CommonTypesAPI.h>
class ClientToSocket
{
public:
    bool Connect();
    static ClientToSocket& Get()
    {
        static ClientToSocket instance;
        return instance;
    }

    

};