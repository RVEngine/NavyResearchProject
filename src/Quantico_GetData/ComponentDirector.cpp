#include "ComponentDirector.h"
//#include "ClientToSocket.h"
#include "Gears.h"
#include "Utility.h"
#include "ConnectToSQL.h"
#include <pqxx/pqxx>
#include <iostream>  
#include<sstream> 
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include "Utilities/StructuredDataWrapper.hpp"


ConnectToSQL s;
std::chrono::steady_clock::time_point begin;
//char Buffer2[256] = { '\0' };
//std::thread bluThread;
//std::thread opThread;
//std::thread cthread;
double recordTime = 0;
std::thread timeThread;
int posID = 0;
int bluforID = 0;
bool test = false;

void ComponentDirector::OnBeforeSimulation(_In_ float32_t delta)
{   
    bool _auto_restart_mission = true;
    if (_auto_restart_mission)
    {
        Vbs3ApplicationState_v1 current_state = Vbs3ApplicationState_v1::kVbs3ApplicationState_unknown;
        Gears::API::VBS3ApplicationAPIv2()->GetCurrentState(&current_state);

        if (current_state == Vbs3ApplicationState_v1::kVbs3ApplicationState_debriefing)
        {
            _auto_restart_mission = false;

            Gears::API::MissionAPIv4()->StartMission("Ambush_At_Dusk_ControlAI_Far.map_tropicalgeotypical25km", TRUE);
           
        }
    }
}

void ComponentDirector::OnRenderMainWindow()
{
    //creates start ambush mission button in the debug window
    bool32_t pressed = FALSE;
    SDKCheck(Gears::API::IMGuiAPIv1()->Button("Start Ambush Mission", { 180.0f, 30.0f }, &pressed));
    if (pressed != FALSE)
    {
        _sample_started = true;
        begin = std::chrono::steady_clock::now();
        SDKCheck(Gears::API::MissionAPIv4()->StartMission("Ambush_At_Dusk_ControlAI_Far.map_tropicalgeotypical25km", TRUE));
        timeThread = std::thread(&ComponentDirector::ElapsedTime, this);
    }
}
void ComponentDirector::ElapsedTime()
{
    while (true)
    {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        elapsed_time = (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) / 1000000.0;
        std::string unitArray[] = { "rightlead","rightgunner","r3","r4", "mlead","mgunner","m3","m4", "leftlead","leftgunner","l3","l4","erightlead","eright2","eright3","eright4", "emlead","em2","em3","em4", "eleftlead","eleft2","eleft3","eleft4" };
        if (elapsed_time > recordTime)
        {
            
            for (std::string unit : unitArray)
            {
               
                DateTime_v3 time;
                Gears::API::EnvironmentAPIv3()->GetTime(&time);
                ObjectHandle_v3 _Soldier;
                _Soldier = kNullObjectHandle;
                auto it = soldierMap.find(unit);
                if (it != soldierMap.end())
                    _Soldier = it->second;
                std::stringstream stream;
                stream << time.hour << ":" << time.minute << ":" << time.second;
                std::string visibleEnemies = myVisibility(_Soldier);
                char* cstr = new char[unit.length() + 1];
                strcpy(cstr, unit.c_str());
                std::string send = getSoldierInfo(cstr) + ";" + visibleEnemies;
                s.sendPosition(send, posID, stream.str());
                posID++;
            }
            recordTime += 5;
        }

    }
}
void ComponentDirector::OnRenderCustomWindow()
{
  /*bool32_t windowOpen = TRUE;
  Gears::API::IMGuiAPIv1()->Begin("Quantico_GetDataSample", ImGuiWindowFlags_v1::kImGuiWindowFlags_ShowBorders, nullptr, &windowOpen);
  if (windowOpen != FALSE)
  {
      if (soldierMap.empty() == false) {
          DisplayMoveToUI();

          DisplayGroupMoveToUI();

          DisplayRuleOfEngagementUI();
      }
    Gears::API::IMGuiAPIv1()->End();

  }*/


    //bool32_t windowOpen = TRUE;
    //Gears::API::IMGuiAPIv1()->Begin("Quantico_GetDataSample", ImGuiWindowFlags_v1::kImGuiWindowFlags_ShowBorders, nullptr, &windowOpen);
    //if (windowOpen != FALSE)
    //{
    //    bool32_t pressed = FALSE;
    //    SDKCheck(Gears::API::IMGuiAPIv1()->Button("Change Current Weapon", { 180.0f, 30.0f }, &pressed));
    //    if (pressed != FALSE)
    //    {
    //        auto it = soldierMap.find("rightlead");
    //        ObjectHandle_v3 soldier = kNullObjectHandle;
    //        if (it != soldierMap.end())
    //        {
    //            soldier = it->second;
    //            
    //            //Gears::API::WeaponSystemAspectAPIv6()->SetActiveWeaponType(soldier, kWeaponType_Special);
    //            Gears::API::WeaponSystemAspectAPIv6()->SetActiveWeapon(soldier, 2, kWeaponAspectAutoSelectValue, kWeaponAspectAutoSelectValue, kWeaponAspectAutoSelectValue);
    //        }
    //    }
    //    Gears::API::IMGuiAPIv1()->End();
    //}
    //    
    //    //bool32_t pressed = FALSE;
    //    bool32_t pressed2 = FALSE;
    //    bool32_t wayPointPressed = FALSE;
    //    //bool32_t textEntered = FALSE;
    //    //char Buffer[256];
    //    //SDKCheck(Gears::API::IMGuiAPIv1()->Button("recieveCommand", { 180.0f, 30.0f }, &pressed));
    //    //if (pressed != FALSE)
    //    //{
    //    //    
    //    //    //cthread = std::thread(&ComponentDirector::commandThread, this);
    //    //}
    //    //clock_t this_time = clock();
    //    int messageID = 0;
    //    SDKCheck(Gears::API::IMGuiAPIv1()->Button("sendData", { 180.0f, 30.0f }, &pressed2));
    //    if (pressed2 != FALSE)
    //    {
    //        //std::string send = getBluForSoldierInfo("RS3");
    //       bluThread= std::thread (&ComponentDirector::bluForThread, this, messageID + 1);   
    //       //opThread = std::thread(&ComponentDirector::opForThread, this, messageID + 1);
    //        //s.sendMessage(send);
    //       // s.recieveMessage();
    //    }
    //    SDKCheck(Gears::API::IMGuiAPIv1()->Button("Create Waypoint", { 180.0f, 30.0f }, &wayPointPressed));
    //    if (wayPointPressed != FALSE)
    //    {
    //        cthread = std::thread(&ComponentDirector::waypointCommandThread, this);           
    //    }
      // IMGui_ImGuiTextEditCallback_Func_v1 callback;
        //SDKCheck(Gears::API::IMGuiAPIv1()->InputText("Query", (int)_countof(Buffer2), (ImGuiInputTextFlags_v1::kImGuiInputTextFlags_EnterReturnsTrue),  NULL, NULL, Buffer2, &textEntered));
        //if (textEntered != FALSE)
        //{
        //    if (strcmp(Buffer2,"getDate")==0)
        //    {
        //        wsprintf(Buffer, send.c_str());
        //        char* output = ("Requested Result:\n", Buffer);
        //        OutputDebugString(output);
        //        OutputDebugString("\n");
        //    }
        //    if (strcmp(Buffer2, "moveLeft") == 0)
        //    {
        //        // Get Soldier By Name
        //        if (_sample_started == true)
        //        {
        //            SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName("sniper2",  &_soldier));
        //            makeSoldierRun({ -5.0f, 0.0f, 0.0f });
        //            OutputDebugString("Sniper Moving Left\n");
        //        }
        //        else
        //        {
        //            OutputDebugString("Load Sniper Mission\n");
        //        }
        //    }
        //    if (strcmp(Buffer2, "moveRight") == 0)
        //    {
        //        // Get Soldier By Name
        //        if (_sample_started == true)
        //        {
        //            SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName("sniper2", &_soldier));
        //            makeSoldierRun({ 5.0f, 0.0f, 0.0f });
        //            OutputDebugString("Sniper Moving Right\n");
        //        }
        //        else
        //        {
        //            OutputDebugString("Load Sniper Mission\n");
        //        }
        //    }
        //    if (strcmp(Buffer2, "moveForward") == 0)
        //    {
        //        // Get Soldier By Name
        //        if (_sample_started == true)
        //        {
        //            SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName("sniper2", &_soldier));
        //            makeSoldierRun({ 0.0f, 0.0f, 5.0f });
        //            OutputDebugString("Sniper Moving Forward\n");
        //        }
        //        else
        //        {
        //            OutputDebugString("Load Sniper Mission\n");
        //        }
        //    }

        //    if (strcmp(Buffer2, "getLocation") == 0)
        //    {

        //        if (_sample_started == true)
        //        {
        //            GeoPosition_v5* position = new GeoPosition_v5;
        //            SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName("sniper2", &_soldier));
        //            Gears::API::TransformationAspectAPIv5()->GetPosition(_soldier, position);
        //            
        //            std::string sendPos;
        //            std::stringstream posstream;
        //            posstream << "[" << position->altitude << ", " << position->latitude << ", " << position->longitude << "]";
        //            posstream >> sendPos;
        //            wsprintf(Buffer, sendPos.c_str());
        //            char* output = ("Requested Result:\n", Buffer);
        //            OutputDebugString(output);
        //            OutputDebugString("\n");
        //        }
        //        else
        //        {
        //            OutputDebugString("Load Sniper Mission\n");
        //        }
        //    }
        //}
      //  Gears::API::IMGuiAPIv1()->End();
   // }
    
}

void ComponentDirector::moveUnits()
{
    std::string readCommand = s.ReadandRemoveMovementCommand();
    //OutputDebugString(readCommand.c_str());
    //OutputDebugString("\n");
    if (readCommand.size() > 4)
    {
        //split readcommand into substrings of needed items
        std::size_t pos = readCommand.find(",");
        std::string solo = readCommand.substr(0, pos);

        std::size_t found = readCommand.find(",", pos + 1);
        std::string x = readCommand.substr(pos + 1, found - (pos + 1));

        std::size_t found2 = readCommand.find(",", found + 1);
        std::string y = readCommand.substr(found + 1, found2 - (found + 1));
    
        std::size_t found3 = readCommand.find(",", found2 + 1);
        std::string z = readCommand.substr(found2 + 1, found3 - (found2 + 1));

        std::size_t found4 = readCommand.find(",", found3 + 1);
        std::string unit1 = readCommand.substr(found3 + 1, found4 - (found3 + 1));

        std::size_t found5 = readCommand.find(",", found4 + 1);
        std::string roe = readCommand.substr(found4 + 1, found5 - (found4 + 1));

        auto it = soldierMap.find(unit1);
        ObjectHandle_v3 soldier = kNullObjectHandle;
        if (it != soldierMap.end())
            soldier = it->second;
        int32_t ruleValue = 0;
        if (roe.compare("2") == 0)
        {
            ruleValue = 2;
        }
        SetRuleOfEngagement(soldier, ruleValue);
        Vector3f64_v3 mapposition = { std::stod(x),std::stod(y),std::stod(z) };
        if (solo.compare("yes") == 0)
        {
            OrderMoveCommand(soldier, mapposition);
        }
        else
        {
            TeamOrderMoveCommand(soldier, mapposition);
        }
    }
}
void ComponentDirector::waypointCommandThread()
{    
        std::string readCommand = s.ReadandRemoveWaypoint();
        //OutputDebugString(readCommand.c_str());
        //OutputDebugString("\n");
        if (readCommand.size() > 10)
        {
            //split readcommand into substrings of needed items
            std::size_t pos = readCommand.find(",");
            std::string command = readCommand.substr(0, pos);

            std::size_t found = readCommand.find(",", pos + 1);
            std::string x = readCommand.substr(pos + 1, found - (pos + 1));

            std::size_t found2 = readCommand.find(",", found + 1);
            std::string y = readCommand.substr(found + 1, found2 - (found + 1));

            std::size_t found3 = readCommand.find(",", found2 + 1);
            std::string z = readCommand.substr(found2 + 1, found3 - (found2 + 1));

            std::size_t found4 = readCommand.find(",", found3 + 1);
            std::string unit1 = readCommand.substr(found3 + 1, found4 - (found3 + 1));

            std::size_t found5 = readCommand.find(",", found4 + 1);
            std::string unit2 = readCommand.substr(found4 + 1, found5 - (found4 + 1));

            std::size_t found6 = readCommand.find(",", found5 + 1);
            std::string unit3 = readCommand.substr(found5 + 1, found6 - (found5 + 1));

            std::size_t found7 = readCommand.find(",", found6 + 1);
            std::string unit4 = readCommand.substr(found6 + 1, found7 - (found6 + 1));

            std::size_t found8 = readCommand.find(",", found7 + 1);
            std::string combatmode = readCommand.substr(found7 + 1, found8 - (found7 + 1));

            std::size_t found9 = readCommand.find(",", found8 + 1);
            std::string behavior = readCommand.substr(found8 + 1, found9 - (found8 + 1));

            if (unit1.length() > 1)
            {
                auto it = soldierMap.find(unit1);
                ObjectHandle_v3 soldier = kNullObjectHandle;
                if (it != soldierMap.end())
                    soldier = it->second;
                //find soldier from map add to group
                ObjectHandle_v3 grp = kNullObjectHandle;
                Gears::API::WorldAPIv6()->CreateGroup(kFaction_blufor, &grp);
                Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
                it = soldierMap.find(unit2);
                if (it != soldierMap.end())
                    soldier = it->second;
                Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
                it = soldierMap.find(unit3);
                if (it != soldierMap.end())
                    soldier = it->second;
                Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
                it = soldierMap.find(unit4);
                if (it != soldierMap.end())
                    soldier = it->second;
                Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
                ObjectHandle_v3 waypoint;
                Gears::API::WorldAPIv6()->CreateWaypoint(&waypoint);
                Gears::API::WaypointAspectAPIv2()->SetType(waypoint, kWaypointType_hold);
                GeoPosition_v5 position = {};
                //Gears::API::TransformationAspectAPIv5()->GetPosition(soldier, &position);
                Vector3f64_v3 soldierMaposition = {};
                // x,y,z in vbs3 coordinates are shown in x,z,y
                Vector3f64_v3 mapposition = { std::stod(x),std::stod(y),std::stod(z) };
                //Gears::API::WorldAPIv6()->GeoPositionToMapPosition(position, &soldierMaposition);
                Gears::API::WorldAPIv6()->MapPositionToGeoPosition(mapposition, &position);
                Gears::API::TransformationAspectAPIv5()->SetPosition(waypoint, position);
                Gears::API::WorldAPIv6()->CreateObject("vbs2_visual_arrow_green", position, nullptr);
                Gears::API::WaypointAspectAPIv2()->SetAssignedTo(waypoint, grp, -1);
                CombatMode_v2 mode;
                //Never fire
                mode = kCombatMode_blue;
                if (combatmode.compare("green") == 0)
                {
                    //Hold fire, defend only
                    mode = kCombatMode_green;
                }
                if (combatmode.compare("white") == 0)
                {
                    //Hold fire, engage at will
                    mode = kCombatMode_white;
                }
                if (combatmode.compare("yellow") == 0)
                {
                    //Fire at will
                    mode = kCombatMode_yellow;
                }
                if (combatmode.compare("red") == 0)
                {
                    //Fire at will, engage at will
                    mode = kCombatMode_red;
                }
                
                BehaviorMode_v2 behaviormode;

                //Never fire
                behaviormode = kBehaviorMode_unchanged;

                if (behavior.compare("careless") == 0)
                {
                    //Units try to stay on roads, not caring about any cover.
                    behaviormode = kBehaviorMode_careless;
                }
                if (behavior.compare("safe") == 0)
                {
                    //Units try to stay on roads, not caring about any cover, similar to careless.
                    behaviormode = kBehaviorMode_safe;
                }
                if (behavior.compare("aware") == 0)
                {
                    //Units try to stay on roads, ocassionally using cover.Units kneel down ocassionally.
                    behaviormode = kBehaviorMode_aware;
                }
                if (combatmode.compare("combat") == 0)
                {
                    //Units try to utilize cover whenever possible. Units kneel down ocassionally. Driving lights are off (except aircraft marker lights).
                    behaviormode = kBehaviorMode_combat;
                }
                if (combatmode.compare("stealth") == 0)
                {
                    //Units try to utilize cover whenever possible. Units prone most of the time. Driving lights are off (except aircraft marker lights).
                    behaviormode = kBehaviorMode_stealth;
                }

                Gears::API::VBS3AIAspectAPIv2()->SetBehavior(grp, behaviormode);
                Gears::API::VBS3AIAspectAPIv2()->SetCombatMode(grp, mode);
                CombatMode_v2 setCombat;
                Gears::API::VBS3AIAspectAPIv2()->GetCombatMode(grp, &setCombat);
                std::stringstream combatStream;
                combatStream << setCombat;
                OutputDebugString(combatStream.str().c_str());
            }
        }
}
void ComponentDirector::commandThread()
{
    
    while (true) {
        std::string readCommand = s.ReadandRemove();
        if (readCommand.find(",") != std::string::npos)
        {
            std::size_t pos = readCommand.find(",");
            std::string unitToCommand = readCommand.substr(0, pos);
            std::size_t found = readCommand.find(",", pos+1);
            //OutputDebugString(unitToCommand.c_str());
            //OutputDebugString("\n");
            //std::size_t found2 = readCommand.find(arr, found + 1);
            std::string command = readCommand.substr(pos+1,found-4);
            //std::string timeofTravel = readCommand.substr(found);
            //OutputDebugString(command.c_str());
            //OutputDebugString("\n");
            if (command.compare("moveleft") == 0)
            {
                // Get Soldier By Name
                if (_sample_started == true)
                {
                     //_soldier = kNullObjectHandle;
                    /*auto it = soldierMap.find("tez");
                    if (it != soldierMap.end())
                        _soldier = it->second;*/
                    SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName(unitToCommand.c_str(), &_soldier));
                    makeSoldierRun({ -5.0f, 0.0f, 0.0f });
                    OutputDebugString(unitToCommand.c_str());
                    OutputDebugString(" Moving Left\n");
                }
                else
                {
                    OutputDebugString("Load RS Mission\n");
                }
            }
            if (command.compare("moveright") == 0)
            {
                // Get Soldier By Name
                if (_sample_started == true)
                {
                    SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName(unitToCommand.c_str(), &_soldier));
                    makeSoldierRun({ 5.0f, 0.0f, 0.0f });
                    OutputDebugString(unitToCommand.c_str());
                    OutputDebugString(" Moving Right\n");
                }
                else
                {
                    OutputDebugString("Load RS Mission\n");
                }
            }
            if (command.compare("moveforward") == 0)
            {
                // Get Soldier By Name
                if (_sample_started == true)
                {
                    SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName(unitToCommand.c_str(), &_soldier));
                    makeSoldierRun({ 0.0f, 0.0f, 5.0f });
                    OutputDebugString(unitToCommand.c_str());
                    OutputDebugString(" Moving Forward\n");
                    
                }
                else
                {
                    OutputDebugString("Load RS Mission\n");
                }
            }
            if (command.compare("stop") == 0)
            {
                // Get Soldier By Name
                if (_sample_started == true)
                {
                    SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName(unitToCommand.c_str(), &_soldier));
                    OutputDebugString(unitToCommand.c_str());
                    makeSoldierStop();
                    OutputDebugString(" Stopped\n");
                }
                else
                {
                    OutputDebugString("Load RS Mission\n");
                }
            }
        }
        Sleep(10000);
    }
}
void ComponentDirector::dateTimeThread(int messageID)
{
    while (true)
    {
        std::string send;
        DateTime_v3 time;
        Gears::API::EnvironmentAPIv3()->GetTime(&time);
        std::string date;
        std::string currenttime;
        //" DateTime: " + time.month + time.day + time.year  + time.hour  + time.minute;
        std::stringstream datestream;
        datestream << time.month << "\\" << time.day << "\\" << time.year;
        datestream >> date;
        std::stringstream timestream;
        timestream << time.hour << ":" << time.minute << ":" << time.second;
        timestream >> currenttime;
        send = date + "  " + currenttime;
        s.Update(send, messageID);
        Sleep(10000);
    }
}
void ComponentDirector::bluForThread(int messageID)
{
    // 4 units rs1, rs2, rs3, rs4
    
        if (_sample_started == true)
        {
            std::string send = getSoldierInfo("leftlead");
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("leftgunner");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("l3");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("l4");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("mlead");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("mgunner");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("m3");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("m4");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("rightlead");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("rightgunner");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("r3");
            messageID++;
            s.UpdateBluFor(send, messageID);
            send = getSoldierInfo("r4");
            messageID++;
            s.UpdateBluFor(send, messageID);
            bluforID = messageID;
        }
        else
        {
            OutputDebugString("Load RS Mission\n");
        }
    
}

void ComponentDirector::opForThread(int messageID)
{
    // opfor units 
    while (true)
    {
        if (_sample_started == true)
        {
            std::string send = getSoldierInfo("qrf2");
            s.UpdateOpFor(send, messageID);
            send = getSoldierInfo("patrol_d");
            s.UpdateOpFor(send, messageID + 1);
            send = getSoldierInfo("patrol_g");
            s.UpdateOpFor(send, messageID + 2);
            send = getSoldierInfo("qrfs1");
            s.UpdateOpFor(send, messageID + 3);
            send = getSoldierInfo("qrfs2");
            s.UpdateOpFor(send, messageID + 3);
            send = getSoldierInfo("qrfs3");
            s.UpdateOpFor(send, messageID + 3);
            send = getSoldierInfo("patrol_3");
            s.UpdateOpFor(send, messageID + 3);
            send = getSoldierInfo("patrol_3");
            s.UpdateOpFor(send, messageID + 3);
            Sleep(10000);
        }
        else
        {
            OutputDebugString("Load RS Mission\n");
        }
    }
}
std::string ComponentDirector::getSoldierInfo(char* soldierName)
{
    ObjectHandle_v3 _bluForSoldier;
    //unit_name
    //char* soldChar="";
    //strcpy(soldChar,soldierName.c_str());
    //Gears::API::MissionAPIv4()->GetPlayer(&_bluForSoldier);
    //char name[256];
    //int32_t size = 256;
    //Gears::API::ScriptAPIv3()->GetVariableName(_bluForSoldier, name, &size);
    _bluForSoldier = kNullObjectHandle;
    //SDKCheck(Gears::API::ScriptAPIv3()->GetObjectHandleFromVariableName(name, &_bluForSoldier));
    std::string send;
    auto it = soldierMap.find(soldierName);
    if (it != soldierMap.end())
        _bluForSoldier = it->second;
    //unit_health
    float32_t damage=0;
    Gears::API::DamageAspectAPIv4()->GetDamage(_bluForSoldier, &damage);
    std::stringstream damageStream;
    damageStream << damage;

    //unit_ammo    
    int32_t weapon_index=0;
    int32_t magazine_index=0;
    int32_t ammo_count = 0;
    Gears::API::WeaponSystemAspectAPIv6()->GetActiveWeapon(_bluForSoldier, &weapon_index, NULL, &magazine_index ,NULL);
    Gears::API::WeaponSystemAspectAPIv6()->GetMagazineAmmoCount(_bluForSoldier, magazine_index, &ammo_count);
    std::stringstream ammoStream;
    ammoStream << ammo_count;

    //unit_type
    Faction_v3 faction;
    Gears::API::ORBATAPIv2()->GetFaction(_bluForSoldier, &faction);
    std::stringstream typeStream;
    typeStream << faction;

    //unit_position
    GeoPosition_v5 position = {};
    Gears::API::TransformationAspectAPIv5()->GetPosition(_bluForSoldier, &position);
    std::stringstream posX;
    std::stringstream posY;
    std::stringstream posZ;
    Vector3f64_v3 mapposition = {};
    Gears::API::WorldAPIv6()->GeoPositionToMapPosition(position, &mapposition);
    posX << mapposition.x;
    posY << mapposition.y;
    posZ << mapposition.z;

    //unit_orientation
    RotationalAngles_v3 orientation = {};
    Gears::API::TransformationAspectAPIv5()->GetOrientation(_bluForSoldier, &orientation);
    std::stringstream orientStream;
    orientStream << orientation.yaw << ", " << orientation.pitch << ", " << orientation.roll;
 

    //unit_velocity
    Vector3f32_v3 velocity = {};
    Gears::API::TransformationAspectAPIv5()->GetVelocity(_bluForSoldier, &velocity);
    std::stringstream veloStream;
    veloStream << "{" << velocity.x << "," << velocity.y << "," << velocity.z << "}";
    
    //send string
    send = std::string(soldierName) + ";" + damageStream.str() + ";" + ammoStream.str() + ";" + typeStream.str() + ";" + posX.str() + ";" + posY.str() + ";" + posZ.str() + ";" + orientStream.str() + ";" + veloStream.str();
    //OutputDebugString(send.c_str());
    //OutputDebugString("\n");
    return send;
}
void ComponentDirector::OnObjectCreation(ObjectHandle_v3 object)
{
    char name[256];
    int32_t size = 256;
    Gears::API::ScriptAPIv3()->GetVariableName(object, name, &size);
    auto result = soldierMap.insert(std::pair<std::string, ObjectHandle_v3>(name, object));
    
    // *Note:* Save the name of the soldier in a vector. This is for Testing / Debugging only.
    _soldierNames.push_back(result.first->first.c_str());
    //OutputDebugString("Soldier inserted in map");

}

void ComponentDirector::OnFire(ObjectHandle_v3 object, int messageID, DateTime_v3 time)
{
    char name[256];
    int32_t size = 256;
    Gears::API::ScriptAPIv3()->GetVariableName(object, name, &size);
    std::stringstream stream;
    stream << time.hour << ":" << time.minute << ":" << time.second;
    std::string visibleEnemies = myVisibility(object);
    std::string send =  getSoldierInfo(name) + ";" + visibleEnemies;
    s.sendFireData(send, messageID, stream.str());
}

void ComponentDirector::OnEnemyFire()
{
    bluForThread(bluforID);
    moveUnits();
    bluforID=0;    
}
void ComponentDirector::OnMissionStart(_In_ bool32_t restart)
{
    if (_sample_started == true && test == false)
    {
        enemyVisiblity();
        bluForThread(bluforID);
        //14400 16100
        auto it = soldierMap.find("rightlead");
        ObjectHandle_v3 soldier = kNullObjectHandle;
        if (it != soldierMap.end())
            soldier = it->second;
        Vector3f64_v3 mapposition = { 14400,0,16100 };
        TeamOrderMoveCommand(soldier, mapposition);
        it = soldierMap.find("mlead");
        if (it != soldierMap.end())
            soldier = it->second;;
        TeamOrderMoveCommand(soldier, mapposition);
        it = soldierMap.find("leftlead");
        if (it != soldierMap.end())
            soldier = it->second;
        TeamOrderMoveCommand(soldier, mapposition);
        test = true;
      

        //Gears::API::WorldListenerAPIv2()->OnObjectCreation(_soldier);
       /* GeoPosition_v5 position;
        position.latitude = 39.58247;
        position.longitude = -40.13518;
        position.altitude = 16;
        position.altitude_reference = kAltitudeReference_geoid;*/

        //// Create a camera
        //Gears::API::WorldAPIv6()->CreateCamera(&_camera);
        //SDKCheck(Gears::API::TransformationAspectAPIv5()->SetPosition(_camera, position));
        //SDKCheck(Gears::API::WorldAPIv6()->SetMainCamera(_camera));

        //GeoPosition_v5 soldier_position = {};
        //Vector3f64_v3 model_offset = { 0.0, 0.0, 5.0 };
        //SDKCheck(Gears::API::TransformationAspectAPIv5()->ModelToWorld(_camera, model_offset, &soldier_position));        
        
        //Create Soldier
        //Gears::API::WorldAPIv6()->CreateObject("vbs_cz_army_rifleman_wdl_m_medium_none_none_cz805a1_none", soldier_position, &_soldier);
        //SDKCheck(Gears::API::EnvironmentAPIv3()->AlignToTerrain(_soldier));

        // Switch to externally
        /*SDKCheck(Gears::API::SimulationAspectAPIv1()->SetSimulationMode(_soldier, SimulationState_v1::kSimulationState_interop));

        SDKCheck(Gears::API::TransformationAspectAPIv5()->SetGroundClamping(_soldier, GroundClampingMode_v1::kGroundClampingMode_position, TRUE));
        SDKCheck(Gears::API::TransformationAspectAPIv5()->SetGroundClamping(_soldier, GroundClampingMode_v1::kGroundClampingMode_orientation, TRUE));

        SDKCheck(Gears::API::TransformationAspectAPIv5()->SetInterpolation(_soldier, TRUE));
        SDKCheck(Gears::API::TransformationAspectAPIv5()->SetExtrapolation(_soldier, ExtrapolationMode_v1::kExtrapolationMode_position, TRUE));*/

        // Move the Soldier
        //SDKCheck(Gears::API::TransformationAspectAPIv5()->SetModelVelocity(_soldier, { 0.0f, 0.0f, 1.0f }));

        //SDKCheck(Gears::API::LifeformAspectAPIv3()->SetMovementType(_soldier, kMovementType_walk));

        // Attach the camera to the soldier
        //SDKCheck(Gears::API::TransformationAspectAPIv5()->SetAttachedTo(_camera, _soldier));
      
       
       
    }

}

void ComponentDirector::OnMissionEnd(_In_ bool32_t restart)
{
    _sample_started = false;

    // Clear out the maps
    soldierMap.clear();
    _soldierNames.clear();
}

void ComponentDirector::makeSoldierRun(Vector3f32_v3 velocity)
{
    Gears::API::SimulationAspectAPIv1()->SetSimulationMode(_soldier, kSimulationState_interop);
    Gears::API::LifeformAspectAPIv3()->SetStance(_soldier, kStance_stand);
    //Gears::API::LifeformAspectAPIv3()->PlayAnimation(_soldier, "translation", true);
    Gears::API::TransformationAspectAPIv5()->SetModelVelocity(_soldier, velocity);
    Gears::API::LifeformAspectAPIv3()->SetMovementType(_soldier, MovementType_v1::kMovementType_run);
}
void ComponentDirector::makeSoldierStop()
{
    Gears::API::LifeformAspectAPIv3()->SetMovementType(_soldier, MovementType_v1::kMovementType_stop);
    Gears::API::LifeformAspectAPIv3()->SetStance(_soldier, kStance_crouch);
    Gears::API::TransformationAspectAPIv5()->SetModelVelocity(_soldier, { 0.0f,0.0f,0.0f });
}

std::string ComponentDirector::myVisibility(ObjectHandle_v3 object)
{
//check faction and get visibility
    std::string bluForArray[] = { "rightlead","rightgunner","r3","r4", "mlead","mgunner","m3","m4", "leftlead","leftgunner","l3","l4" };
    std::string opForArray[] = { "erightlead","eright2","eright3","eright4", "emlead","em2","em3","em4", "eleftlead","eleft2","eleft3","eleft4"};
    Faction_v3 faction;
    std::stringstream visbilitystream;
    Gears::API::ORBATAPIv2()->GetFaction(object, &faction);
    if (faction == kFaction_blufor)
    {
        for (std::string opFor : opForArray)
        {
            float32_t visibility = 0;
            ObjectHandle_v3 opForsoldier = kNullObjectHandle;
            auto it = soldierMap.find(opFor);
            if (it != soldierMap.end())
                opForsoldier = it->second;
            Gears::API::WorldAPIv6()->CalculateVisibility(object, opForsoldier, &visibility);
            float32_t damage = 0;
            Gears::API::DamageAspectAPIv4()->GetDamage(opForsoldier, &damage);
            if (visibility > 0 && damage < 1)
            {
                visbilitystream << opFor << ",";
               
            }
        }
        return visbilitystream.str();
    }
    else if (faction == kFaction_opfor)
    {
        for (std::string bluFor : bluForArray)
        {
            float32_t visibility = 0;
            ObjectHandle_v3 bluForsoldier = kNullObjectHandle;
            auto it = soldierMap.find(bluFor);
            if (it != soldierMap.end())
                bluForsoldier = it->second;
            Gears::API::WorldAPIv6()->CalculateVisibility(object, bluForsoldier, &visibility);
            float32_t damage = 0;
            Gears::API::DamageAspectAPIv4()->GetDamage(bluForsoldier, &damage);
            if (visibility > 0 && damage < 1)
            {
                visbilitystream << bluFor << ",";

            }
        }
        return visbilitystream.str();
    }
    return "";
}

void ComponentDirector::enemyVisiblity()
{
    s.removeEnemyVisbility();
    std::string bluForArray[] = { "rightlead","rightgunner","r3","r4", "mlead","mgunner","m3","m4", "leftlead","leftgunner","l3","l4" };
    std::string opForArray[] = { "erightlead","eright2","eright3","eright4", "emlead","em2","em3","em4", "eleftlead","eleft2","eleft3","eleft4"};
    int messageID = 0;
    for (std::string opFor : opForArray)
    {
        for (std::string bluFor : bluForArray)
        {
            float32_t visibility = 0;
            ObjectHandle_v3 opForsoldier = kNullObjectHandle;
            auto it = soldierMap.find(opFor);
            if (it != soldierMap.end())
                opForsoldier = it->second;
            ObjectHandle_v3 bluForsoldier = kNullObjectHandle;
            it = soldierMap.find(opFor);
            if (it != soldierMap.end())
                bluForsoldier = it->second;
            Gears::API::WorldAPIv6()->CalculateVisibility(opForsoldier, bluForsoldier, &visibility);
            float32_t damage = 0;
            Gears::API::DamageAspectAPIv4()->GetDamage(bluForsoldier, &damage);
            if (visibility > 0 && damage<1)
            {
                
                std::stringstream visbilitystream;
                visbilitystream << opFor << ";" << bluFor << ";" << visibility;
                s.setEnemyVisbility(visbilitystream.str(), messageID);
                messageID++;
            }
        }

    }
}

//! Function to tell a unit to follow another unit.
//@param  unitToGiveCommand - Unit to tell to follow.
//@param  unitToFollow - Unit to follow.
void ComponentDirector::OrderFollowCommand(const ObjectHandle_v3& unitToGiveCommand, const ObjectHandle_v3& unitToFollow)
{
  BufferWriter writer(Gears::API::StructuredDataAPIv1());
  writer(CollectionStart());
  writer("behaviorName");
  writer("follow");
  writer("elementToFollow");
  writer(unitToFollow);
  writer(CollectionEnd());

  std::vector<char> messageBuffer = writer.Result();

  Gears::API::ControlAIAspectAPIv1()->ReceiveMessage(unitToGiveCommand, "NewOrder", messageBuffer.data(), static_cast<int32_t>(messageBuffer.size()));
}

//! Function to move a ControlAI object to.
//@param  unitToGiveCommand - ObjectHandle to a unit (or group) that should move.
//@param  movePosition - VBS Map Position to move to.
void ComponentDirector::OrderMoveCommand(const ObjectHandle_v3& unitToGiveCommand, const Vector3f64_v3& movePosition)
{
  BufferWriter writer(Gears::API::StructuredDataAPIv1());
  writer(CollectionStart());
  writer("behaviorName");
  writer("move");
  writer("position");
  writer(movePosition);
  writer(CollectionEnd());

  std::vector<char> messageBuffer = writer.Result();

  SDKCheck(Gears::API::ControlAIAspectAPIv1()->ReceiveMessage(unitToGiveCommand, "NewOrder", messageBuffer.data(), static_cast<int32_t>(messageBuffer.size())));
}

//! Function to move a whole group to a given VBS Map Position. This function gets the whole group of any given unit, and tells the group to move as a whole.
//@param  teamMember - ObjectHandle to a unit that is a part of the group that should move.
//@param  movePosition - VBS Map Position to tell the group to move to.
void ComponentDirector::TeamOrderMoveCommand(const ObjectHandle_v3& teamMember, const Vector3f64_v3& movePosition)
{
  // Get the group of the unit
  ObjectHandle_v3 teamGroup = kNullObjectHandle;
  if (APIRESULT_SUCCESS(Gears::API::ORBATAPIv2()->GetSuperiorGroup(teamMember, &teamGroup)) && teamGroup.id != kNullObjectHandle.id)
  {
    OrderMoveCommand(teamGroup, movePosition);
  }
}

//! Function to set the Rule of Engagement value on a ControlAI Brain.
//@param  controlAIObject - The object handle of either a ControlAI unit or Group
//@param  ruleValue - Value of the ROE (as defined by the bahavior itself)  
void ComponentDirector::SetRuleOfEngagement(const ObjectHandle_v3& controlAIObject, int32_t ruleValue)
{
  BufferWriter writer(Gears::API::StructuredDataAPIv1());
  writer(CollectionStart());
  writer("ruleName");
  writer("roe"); // Mandatory
  writer("ruleValue");
  writer(static_cast<float64_t>(ruleValue)); // StructuredDataAPI doesn't support int32_t, so store as a float64_t
  writer(CollectionEnd());

  std::vector<char> messageBuffer = writer.Result();

  SDKCheck(Gears::API::ControlAIAspectAPIv1()->ReceiveMessage(controlAIObject, "NewRule", messageBuffer.data(), static_cast<int32_t>(messageBuffer.size())));
}

void ComponentDirector::DisplayMoveToUI()
{
  // Let the user select which solider they want to move
  static int32_t currentlySelectedMoveSoldier = 0;
  SDKCheck(Gears::API::IMGuiAPIv1()->Combo("Soldier##Move", _soldierNames.data(), static_cast<int32_t>(_soldierNames.size()), 4, &currentlySelectedMoveSoldier, nullptr));

  bool32_t pressed = FALSE;
  SDKCheck(Gears::API::IMGuiAPIv1()->Button("Move Unit to Position", { 180.0f, 30.0f }, &pressed));
  if (pressed != FALSE)
  {
    // Get the player
    ObjectHandle_v3 player = kNullObjectHandle;
    SDKCheck(Gears::API::MissionAPIv4()->GetPlayer(&player));

    // Get the map position of the player
    GeoPosition_v5 playerPosition = {};
    SDKCheck(Gears::API::TransformationAspectAPIv5()->GetPosition(player, &playerPosition));
    Vector3f64_v3 vbsMapPosition = {};
    SDKCheck(Gears::API::WorldAPIv6()->GeoPositionToMapPosition(playerPosition, &vbsMapPosition));

    // Move the whole group to the player's position
    OrderMoveCommand(soldierMap[_soldierNames[currentlySelectedMoveSoldier]], vbsMapPosition);
  }

  SDKCheck(Gears::API::IMGuiAPIv1()->Separator());
}

void ComponentDirector::DisplayGroupMoveToUI()
{
  // Let the user select which solider they want to move
  static int32_t currentlySelectedGroupSoldier = 0;
  SDKCheck(Gears::API::IMGuiAPIv1()->Combo("Soldier##Group", _soldierNames.data(), static_cast<int32_t>(_soldierNames.size()), 4, &currentlySelectedGroupSoldier, nullptr));

  bool32_t pressed = FALSE;
  SDKCheck(Gears::API::IMGuiAPIv1()->Button("Move Group to Position", { 180.0f, 30.0f }, &pressed));
  if (pressed != FALSE)
  {
    // Get the player
    ObjectHandle_v3 player = kNullObjectHandle;
    SDKCheck(Gears::API::MissionAPIv4()->GetPlayer(&player));

    // Get the map position of the player
    GeoPosition_v5 playerPosition = {};
    SDKCheck(Gears::API::TransformationAspectAPIv5()->GetPosition(player, &playerPosition));
    Vector3f64_v3 vbsMapPosition = {};
    SDKCheck(Gears::API::WorldAPIv6()->GeoPositionToMapPosition(playerPosition, &vbsMapPosition));

    // Move the whole group to the player's position
    TeamOrderMoveCommand(soldierMap[_soldierNames[currentlySelectedGroupSoldier]], vbsMapPosition);
  }

  SDKCheck(Gears::API::IMGuiAPIv1()->Separator());
}

void ComponentDirector::DisplayRuleOfEngagementUI()
{
  // Let the user select which solider they want to set the ROE for
  static int32_t currentlySelectedROESoldier = 0;
  SDKCheck(Gears::API::IMGuiAPIv1()->Combo("Soldier##ROE", _soldierNames.data(), static_cast<int32_t>(_soldierNames.size()), 4, &currentlySelectedROESoldier, nullptr));

  bool32_t changed = FALSE;
  static int32_t currentROEValue = 0;
  SDKCheck(Gears::API::IMGuiAPIv1()->InputInt("Rule of Engagement Value", 1, 1, ImGuiInputTextFlags_v1::kImGuiInputTextFlags_AlwaysInsertMode, &currentROEValue, &changed));

  if (changed != FALSE)
  {
    SetRuleOfEngagement(soldierMap[_soldierNames[currentlySelectedROESoldier]], currentROEValue);
  }

  SDKCheck(Gears::API::IMGuiAPIv1()->Separator());
}
