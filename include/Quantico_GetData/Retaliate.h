#pragma once
#include <CommonTypesAPI.h>
#include <windows.h>
#include <pqxx/pqxx>  
#include <string>
class Retaliate
{
public:
    void CreateWaypoint();
    static Retaliate& Get()
    {
        static Retaliate instance;
        return instance;
    }
};