#pragma once

#include <CommonTypesAPI.h>
#include <string>
#include <map>

class ComponentDirector
{
public:
    static ComponentDirector& Get()
    {
        static ComponentDirector instance;
        return instance;
    }
    std::map<std::string, ObjectHandle_v3> soldierMap;
    void OnBeforeSimulation(_In_ float32_t delta);
    void OnRenderMainWindow();
    void OnRenderCustomWindow();
    void OnObjectCreation(ObjectHandle_v3 object);
    void OnEnemyFire();
    void OnMissionStart(_In_ bool32_t restart);
    void OnMissionEnd(_In_ bool32_t restart);
    void dateTimeThread(int messageID);
    void bluForThread(int messageID);
    void opForThread(int messageID);
    void waypointCommandThread();
    void commandThread();
    std::string getSoldierInfo(char* soldierName);
private:
    ComponentDirector() { }
    ~ComponentDirector() { }
    void makeSoldierRun(Vector3f32_v3 velocity);
    void makeSoldierStop();
    bool _sample_started = false;
    
    //ObjectHandle_v3 _camera;
    ObjectHandle_v3 _soldier;
};
