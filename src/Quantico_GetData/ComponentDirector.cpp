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



ConnectToSQL s;
//char Buffer2[256] = { '\0' };
//std::thread bluThread;
//std::thread opThread;
//std::thread cthread;
void ComponentDirector::OnBeforeSimulation(_In_ float32_t delta)
{
   
    
}

void ComponentDirector::OnRenderMainWindow()
{
    //creates start ambush mission button in the debug window
    bool32_t pressed = FALSE;
    SDKCheck(Gears::API::IMGuiAPIv1()->Button("Start Ambush Mission", { 180.0f, 30.0f }, &pressed));
    if (pressed != FALSE)
    {
        _sample_started = true;

        SDKCheck(Gears::API::MissionAPIv4()->StartMission("Ambush_At_Dusk.map_tropicalgeotypical25km", TRUE));
    }
}

void ComponentDirector::OnRenderCustomWindow()
{
    //bool32_t windowOpen = TRUE;
    //Gears::API::IMGuiAPIv1()->Begin("Quantico_GetDataSample", ImGuiWindowFlags_v1::kImGuiWindowFlags_ShowBorders, nullptr, &windowOpen);
    //if (windowOpen != FALSE)
    //{
    //   /* bool32_t pressed = FALSE;
    //    SDKCheck(Gears::API::IMGuiAPIv1()->Button("Run", { 180.0f, 30.0f }, &pressed));
    //    if (pressed != FALSE)
    //    {
    //        makeSoldierRun();
    //    }
    //    Gears::API::IMGuiAPIv1()->End();*/
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
void ComponentDirector::waypointCommandThread()
{    
        std::string readCommand = s.ReadandRemoveWaypoint();
        OutputDebugString(readCommand.c_str());
        OutputDebugString("\n");
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
        if (unit1.length() > 1)
        {
            auto it = soldierMap.find(unit1);
            ObjectHandle_v3 soldier = kNullObjectHandle;
            if (it != soldierMap.end())
                soldier = it->second;
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
            Gears::API::TransformationAspectAPIv5()->GetPosition(soldier, &position);
            Vector3f64_v3 soldierMaposition = {};
            // x,y,z in vbs3 coordinates are shown in x,z,y
            Vector3f64_v3 mapposition = { std::stod(x),std::stod(y),std::stod(z) };
            Gears::API::WorldAPIv6()->GeoPositionToMapPosition(position, &soldierMaposition);
            Gears::API::WorldAPIv6()->MapPositionToGeoPosition(mapposition, &position);

            Gears::API::TransformationAspectAPIv5()->SetPosition(waypoint, position);

            Gears::API::WaypointAspectAPIv2()->SetAssignedTo(waypoint, grp, -1);
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
            s.UpdateBluFor(send, messageID + 1);
            send = getSoldierInfo("l3");
            s.UpdateBluFor(send, messageID + 2);
            send = getSoldierInfo("l4");
            s.UpdateBluFor(send, messageID + 3);
            send = getSoldierInfo("mlead");
            s.UpdateBluFor(send, messageID + 4);
            send = getSoldierInfo("mgunner");
            s.UpdateBluFor(send, messageID + 5);
            send = getSoldierInfo("m3");
            s.UpdateBluFor(send, messageID + 6);
            send = getSoldierInfo("m4");
            s.UpdateBluFor(send, messageID + 7);
            send = getSoldierInfo("rightlead");
            s.UpdateBluFor(send, messageID + 8);
            send = getSoldierInfo("rightgunner");
            s.UpdateBluFor(send, messageID + 9);
            send = getSoldierInfo("r3");
            s.UpdateBluFor(send, messageID + 10);
            send = getSoldierInfo("r4");
            s.UpdateBluFor(send, messageID + 11);
            Sleep(10000);
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
    send = std::string(soldierName) + ";" + damageStream.str() + ";" + ammoStream.str() + "; unit_type; " + posX.str() + ";" + posY.str() + ";" + posZ.str() + ";" + orientStream.str() + ";" + veloStream.str();
    OutputDebugString(send.c_str());
    OutputDebugString("\n");
    return send;
}
void ComponentDirector::OnObjectCreation(ObjectHandle_v3 object)
{
    char name[256];
    int32_t size = 256;
    Gears::API::ScriptAPIv3()->GetVariableName(object, name, &size);
    soldierMap.insert(std::pair<std::string, ObjectHandle_v3>(name, object));
    OutputDebugString("Soldier inserted in map ");
    OutputDebugString(name);
    OutputDebugString("\n");
    
}

void ComponentDirector::OnEnemyFire()
{
    int messageID = 0;
    bluForThread(messageID);
    waypointCommandThread();
    
}
void ComponentDirector::OnMissionStart(_In_ bool32_t restart)
{
    if (_sample_started == true)
    {
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



