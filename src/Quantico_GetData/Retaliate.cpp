
//#include "ClientToSocket.h"
#include "Gears.h"
#include "Utility.h"
#include <pqxx/pqxx>
#include <iostream>  
#include<sstream> 
#include <string>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "ConnectToSQL.h"
#include <Retaliate.h>
//#include <ComponentDirector.h>

//ConnectToSQL s;
void Retaliate::CreateWaypoint()
{
//    std::string readCommand = s.ReadandRemoveWaypoint();
//    OutputDebugString(readCommand.c_str());
//    OutputDebugString("\n");
//    std::size_t pos = readCommand.find(",");
//    std::string command = readCommand.substr(0, pos);
//
//    std::size_t found = readCommand.find(",", pos + 1);
//    std::string x = readCommand.substr(pos + 1, found - (pos + 1));
//
//    std::size_t found2 = readCommand.find(",", found + 1);
//    std::string y = readCommand.substr(found + 1, found2 - (found + 1));
//
//    std::size_t found3 = readCommand.find(",", found2 + 1);
//    std::string z = readCommand.substr(found2 + 1, found3 - (found2 + 1));
//
//    std::size_t found4 = readCommand.find(",", found3 + 1);
//    std::string unit1 = readCommand.substr(found3 + 1, found4 - (found3 + 1));
//
//    std::size_t found5 = readCommand.find(",", found4 + 1);
//    std::string unit2 = readCommand.substr(found4 + 1, found5 - (found4 + 1));
//
//    std::size_t found6 = readCommand.find(",", found5 + 1);
//    std::string unit3 = readCommand.substr(found5 + 1, found6 - (found5 + 1));
//
//    std::size_t found7 = readCommand.find(",", found6 + 1);
//    std::string unit4 = readCommand.substr(found6 + 1, found7 - (found6 + 1));
//    if (unit1.length() > 1)
//    {
//        auto it = soldierMap.find(unit1);
//        ObjectHandle_v3 soldier = kNullObjectHandle;
//        if (it != soldierMap.end())
//            soldier = it->second;
//        ObjectHandle_v3 grp = kNullObjectHandle;
//        Gears::API::WorldAPIv6()->CreateGroup(kFaction_blufor, &grp);
//        Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
//        it = soldierMap.find(unit2);
//        if (it != soldierMap.end())
//            soldier = it->second;
//        Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
//        it = soldierMap.find(unit3);
//        if (it != soldierMap.end())
//            soldier = it->second;
//        Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
//        it = soldierMap.find(unit4);
//        if (it != soldierMap.end())
//            soldier = it->second;
//        Gears::API::ORBATAPIv2()->SetSuperiorGroup(soldier, grp);
//        ObjectHandle_v3 waypoint;
//        Gears::API::WorldAPIv6()->CreateWaypoint(&waypoint);
//        Gears::API::WaypointAspectAPIv2()->SetType(waypoint, kWaypointType_hold);
//        GeoPosition_v5 position = {};
//        Gears::API::TransformationAspectAPIv5()->GetPosition(soldier, &position);
//        Vector3f64_v3 soldierMaposition = {};
//        // x,y,z in vbs3 coordinates are shown in x,z,y
//        Vector3f64_v3 mapposition = { std::stod(x),std::stod(y),std::stod(z) };
//        Gears::API::WorldAPIv6()->GeoPositionToMapPosition(position, &soldierMaposition);
//        Gears::API::WorldAPIv6()->MapPositionToGeoPosition(mapposition, &position);
//
//        Gears::API::TransformationAspectAPIv5()->SetPosition(waypoint, position);
//
//        Gears::API::WaypointAspectAPIv2()->SetAssignedTo(waypoint, grp, -1);
//    }
}

