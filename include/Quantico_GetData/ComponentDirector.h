#pragma once

#include <CommonTypesAPI.h>
#include <string>
#include <map>
#include <vector>

class ComponentDirector
{
public:
    static ComponentDirector& Get()
    {
        static ComponentDirector instance;
        return instance;
    }
    std::map<std::string, ObjectHandle_v3> soldierMap;
    double elapsed_time = 0;
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
    void ElapsedTime();
    std::string myVisibility(ObjectHandle_v3 object);
    void enemyVisiblity();
    void OnFire(ObjectHandle_v3 object, int messageID, DateTime_v3 time);
    std::string getSoldierInfo(char* soldierName);
    void moveUnits();
    //! Function to tell a unit to follow another unit.
    //@param  unitToGiveCommand - Unit to tell to follow.
    //@param  unitToFollow - Unit to follow.
    void OrderFollowCommand(const ObjectHandle_v3& unitToGiveCommand, const ObjectHandle_v3& unitToFollow);
    //! Function to move a ControlAI object to.
    //@param  unitToGiveCommand - ObjectHandle to a unit (or group) that should move.
    //@param  movePosition - VBS Map Position to move to.
    void OrderMoveCommand(const ObjectHandle_v3& unitToGiveCommand, const Vector3f64_v3& movePosition);
    //! Function to move a whole group to a given VBS Map Position. This function gets the whole group of any given unit, and tells the group to move as a whole.
    //@param  teamMember - ObjectHandle to a unit that is a part of the group that should move.
    //@param  movePosition - VBS Map Position to tell the group to move to.
    void TeamOrderMoveCommand(const ObjectHandle_v3& teamMember, const Vector3f64_v3& movePosition);
    //! Function to set the Rule of Engagement value on a ControlAI Brain.
    //@param  controlAIObject - The object handle of either a ControlAI unit or Group
    //@param  ruleValue - Value of the ROE (as defined by the bahavior itself)  
    void SetRuleOfEngagement(const ObjectHandle_v3& controlAIObject, int32_t ruleValue);

private:
    ComponentDirector() { }
    ~ComponentDirector() { }
    void makeSoldierRun(Vector3f32_v3 velocity);
    void makeSoldierStop();
    bool _sample_started = false;
    bool _end_mission = false;
    
    //ObjectHandle_v3 _camera;
    ObjectHandle_v3 _soldier;

    // *Note:* These functions are just for testing/debugging of the ControlAI Commands
    void DisplayMoveToUI();
    void DisplayGroupMoveToUI();
    void DisplayRuleOfEngagementUI();

    // *Note:* This variable is just for testing/debugging and is used by the `DisplayRuleOfEngagementUI` function
    std::vector<const char*> _soldierNames;
};
