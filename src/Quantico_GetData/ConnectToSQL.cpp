#include <windows.h>
#include <iostream>
#include <pqxx/pqxx>  
#include<sstream> 
#include <debugapi.h>
#include <ConnectToSQL.h>
#include <process.h>




using namespace std;
using namespace pqxx;
void ConnectToSQL::Update(std::string message, int messageID)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");
   
    std::size_t pos = message.find(" ");
    std::string date = message.substr(0, pos);
    std::string time = message.substr(pos);
    C.prepare("remove_previous", "delete from datetime;");
    C.prepare("insert_to_dateTime", "insert into datetime (messageid, date, time) values ($1, $2, $3);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("remove_previous");
            OutputDebugString("Previous Rows Removed\n");
            txn.commit();
            txn.exec_prepared("insert_to_dateTime", messageID, date, time);
            txn.commit();
            OutputDebugString("New Row Added\n");
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
void ConnectToSQL::UpdateBluFor(std::string message, int messageID)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string unit_name = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string unit_health = message.substr(pos +1,found-(pos+1));

    std::size_t found2 = message.find(";", found + 1);
    std::string unit_ammo = message.substr(found+1, found2-(found+1));

    std::size_t found3 = message.find(";", found2 + 1);
    std::string unit_type = message.substr(found2+1, found3-(found2+1));

    std::size_t found4 = message.find(";", found3 + 1);
    std::string px = message.substr(found3+1, found4-(found3+1));

    std::size_t found5 = message.find(";", found4 + 1);
    std::string py = message.substr(found4+1, found5-(found4+1));

    std::size_t found6 = message.find(";", found5 + 1);
    std::string pz = message.substr(found5+1, found6-(found5+1));

    std::size_t found7 = message.find(";", found6 + 1);
    std::string unit_orientation = message.substr(found6 + 1, found7 - (found6 + 1));

    std::size_t found8 = message.find(";", found5 + 1);
    std::string unit_velocity = message.substr(found7 + 1, found8 - (found7 + 1));

    C.prepare("remove_previous", "delete from blufor where unit_name=$1;");
    C.prepare("count", "select count(*) from blufor where unit_name=$1;;");
    C.prepare("insert_to_blufor",
        "insert into blufor (unit_id, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity) values ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            //OutputDebugString("Opened database successfully!\n");
            work txn(C);
            result R = txn.exec_prepared("count",unit_name);
            auto const counter = R[0]["count"];
            std::stringstream counts;
            counts << counter;
            int bluforCount = 0;
            counts >> bluforCount;
            if (bluforCount > 0) {
                txn.exec_prepared("remove_previous", unit_name);
                //OutputDebugString("Previous Rows Removed\n");
                txn.commit();
            }
            txn.exec_prepared("insert_to_blufor", messageID, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity);
            txn.commit();
                //OutputDebugString("New Row Added\n");
            
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
void ConnectToSQL::UpdateOpFor(std::string message, int messageID)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string unit_name = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string unit_health = message.substr(pos + 1, found - (pos + 1));

    std::size_t found2 = message.find(";", found + 1);
    std::string unit_ammo = message.substr(found + 1, found2 - (found + 1));

    std::size_t found3 = message.find(";", found2 + 1);
    std::string unit_type = message.substr(found2 + 1, found3 - (found2 + 1));

    std::size_t found4 = message.find(";", found3 + 1);
    std::string unit_position = message.substr(found3 + 1, found4 - (found3 + 1));

    std::size_t found5 = message.find(";", found4 + 1);
    std::string unit_orientation = message.substr(found4 + 1, found5 - (found4 + 1));

    std::size_t found6 = message.find(";", found5 + 1);
    std::string unit_velocity = message.substr(found5 + 1, found6 - (found5 + 1));

    C.prepare("remove_previous", "delete from opfor where unit_name=$1;");
    C.prepare("insert_to_opfor",
        "insert into opfor (unit_id, unit_name, unit_health, unit_ammo, unit_type, unit_position, unit_orientation, unit_velocity) values ($1, $2, $3, $4, $5, $6, $7, $8);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("remove_previous", unit_name);
            OutputDebugString("Previous Rows Removed\n");
            txn.commit();
            txn.exec_prepared("insert_to_opfor", messageID, unit_name, unit_health, unit_ammo, unit_type, unit_position, unit_orientation, unit_velocity);
            txn.commit();
            OutputDebugString("New Row Added\n");
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
string ConnectToSQL::ReadandRemove()
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    C.prepare("read", "select * from commands limit 1;");
    C.prepare("delete", "delete from commands;");
    std::string command;
    try {
        if (C.is_open()) {
            work txn(C);
            row r = txn.exec_prepared1("read");
            if (!r.empty())
            {
                txn.commit();
                OutputDebugString("Row Read\n");
                const field field1 = r[0];
                const field field2 = r[1];
                const field field3 = r[2];
                const field field4 = r[3];
                std::stringstream commandstream;
                commandstream << field2 << "," << field3 << "," << field4;
                commandstream >> command;
                const char* cstr = command.c_str();
                OutputDebugString(cstr);
                OutputDebugString("\n");
                txn.exec_prepared("delete");
                txn.commit();
            }
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
    return command;
}
string ConnectToSQL::ReadandRemoveWaypoint()
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");
    //C.prepare("count", "select count(*) from waypointcommands2;");
    C.prepare("read", "select * from waypointcommands2 limit 1;");
    C.prepare("delete", "delete from waypointcommands2 where ctid in (select ctid from waypointcommands2 limit 1);");
    std::string command;
    try {
        if (C.is_open()) {
            work txn(C);
            result R = txn.exec("select count(*) from waypointcommands2;");
            auto const counter =R[0]["count"];
            std::stringstream counts;
            counts << counter;
            int waypointCount = 0;
            counts >> waypointCount;
            if (waypointCount > 0) {
                row r = txn.exec_prepared1("read");
                txn.commit();
                OutputDebugString("Row Read\n");
                const field cID = r[0];
                const field cmnd = r[1];
                const field x = r[2];
                const field y = r[3];
                const field z = r[4];
                const field u1 = r[5];
                const field u2 = r[6];
                const field u3 = r[7];
                const field u4 = r[8];
                const field combatmode = r[9];
                const field behavior = r[10];
                std::stringstream commandstream;
                commandstream << cmnd << "," << x << "," << y << "," << z << "," << u1 << "," << u2 << "," << u3 << "," << u4 << "," << combatmode << "," << behavior;
                commandstream >> command;
                //const char* cstr = command.c_str();
                //OutputDebugString(cstr);
                //OutputDebugString("\n");
                txn.exec_prepared("delete");
                txn.commit();
            }
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
    return command;
}
void ConnectToSQL::UpdateFireTable(std::string message, int messageID) {
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string unit_name = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string time = message.substr(pos + 1, found - (pos + 1));


    C.prepare("remove_previous", "delete from enemyfire;");
    C.prepare("insert_to_enemyfire",
        "insert into enemyfire (unit_id, unit_name, time) values ($1, $2, $3);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            //OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("remove_previous", unit_name);
            //OutputDebugString("Previous Rows Removed\n");
            txn.commit();
            txn.exec_prepared("insert_to_enemyfire", messageID, unit_name, time);
            txn.commit();
            //OutputDebugString("New Row Added\n");
            
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
void ConnectToSQL::setEnemyVisbility(std::string message, int messageID)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string opfor = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string seenblufor = message.substr(pos + 1, found - (pos + 1));

    std::size_t found2 = message.find(";", found + 1);
    std::string visibility = message.substr(found + 1, found2 - (found + 1));

    C.prepare("insert_to_eVis",
        "insert into enemyVisibility(visibility_id, opfor, seenblufor, visiblity_amount) values ($1, $2, $3, $4);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            //OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("insert_to_eVis", messageID, opfor, seenblufor, visibility);
            txn.commit();
            //OutputDebugString("New Row Added\n");
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
void ConnectToSQL::removeEnemyVisbility()
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");
    C.prepare("remove_previous", "delete from enemyVisibility;");
    try {
        if (C.is_open())
        {
            work txn(C);
            txn.exec_prepared("remove_previous");
            txn.commit();
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }

}
void ConnectToSQL::sendFireData(std::string message, int messageID, std::string time)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string unit_name = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string unit_health = message.substr(pos + 1, found - (pos + 1));

    std::size_t found2 = message.find(";", found + 1);
    std::string unit_ammo = message.substr(found + 1, found2 - (found + 1));

    std::size_t found3 = message.find(";", found2 + 1);
    std::string unit_type = message.substr(found2 + 1, found3 - (found2 + 1));

    std::size_t found4 = message.find(";", found3 + 1);
    std::string px = message.substr(found3 + 1, found4 - (found3 + 1));

    std::size_t found5 = message.find(";", found4 + 1);
    std::string py = message.substr(found4 + 1, found5 - (found4 + 1));

    std::size_t found6 = message.find(";", found5 + 1);
    std::string pz = message.substr(found5 + 1, found6 - (found5 + 1));

    std::size_t found7 = message.find(";", found6 + 1);
    std::string unit_orientation = message.substr(found6 + 1, found7 - (found6 + 1));

    std::size_t found8 = message.find(";", found7 + 1);
    std::string unit_velocity = message.substr(found7 + 1, found8 - (found7 + 1));

    std::size_t found9 = message.find(";", found8 + 1);
    std::string visibleEnemies = message.substr(found8 + 1, found9 - (found8 + 1));



    C.prepare("insert_to_firedata",
        "insert into firedata (fireid, timestamp, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity, visibleenemies) values ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            //OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("insert_to_firedata", messageID, time, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity, visibleEnemies);
            txn.commit();
            //OutputDebugString("New Row Added to firedata\n");
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
void ConnectToSQL::sendPosition(std::string message, int messageID, std::string time)
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");

    std::size_t pos = message.find(";");
    std::string unit_name = message.substr(0, pos);

    std::size_t found = message.find(";", pos + 1);
    std::string unit_health = message.substr(pos + 1, found - (pos + 1));

    std::size_t found2 = message.find(";", found + 1);
    std::string unit_ammo = message.substr(found + 1, found2 - (found + 1));

    std::size_t found3 = message.find(";", found2 + 1);
    std::string unit_type = message.substr(found2 + 1, found3 - (found2 + 1));

    std::size_t found4 = message.find(";", found3 + 1);
    std::string px = message.substr(found3 + 1, found4 - (found3 + 1));

    std::size_t found5 = message.find(";", found4 + 1);
    std::string py = message.substr(found4 + 1, found5 - (found4 + 1));

    std::size_t found6 = message.find(";", found5 + 1);
    std::string pz = message.substr(found5 + 1, found6 - (found5 + 1));

    std::size_t found7 = message.find(";", found6 + 1);
    std::string unit_orientation = message.substr(found6 + 1, found7 - (found6 + 1));

    std::size_t found8 = message.find(";", found7 + 1);
    std::string unit_velocity = message.substr(found7 + 1, found8 - (found7 + 1));

    std::size_t found9 = message.find(";", found8 + 1);
    std::string visibleEnemies = message.substr(found8 + 1, found9 - (found8 + 1));



    C.prepare("insert_to_posdata",
        "insert into positiondata (posid, timestamp, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity, visibleenemies) values ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            //OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("insert_to_posdata", messageID, time, unit_name, unit_health, unit_ammo, unit_type, px, py, pz, unit_orientation, unit_velocity, visibleEnemies);
            txn.commit();
            //OutputDebugString("New Row Added to positiondata\n");
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
}
string ConnectToSQL::ReadandRemoveMovementCommand()
{
    connection C("dbname = units user = postgres password = ichigo \
        hostaddr = 127.0.0.1 port = 5432");
    //C.prepare("count", "select count(*) from waypointcommands2;");
    C.prepare("read", "select * from moveCommand limit 1;");
    C.prepare("delete", "delete from moveCommand where ctid in (select ctid from moveCommand limit 1);");
    std::string command;
    try {
        if (C.is_open()) {
            work txn(C);
            result R = txn.exec("select count(*) from moveCommand;");
            auto const counter = R[0]["count"];
            std::stringstream counts;
            counts << counter;
            int waypointCount = 0;
            counts >> waypointCount;
            if (waypointCount > 0) {
                row r = txn.exec_prepared1("read");
                txn.commit();
                OutputDebugString("Row Read\n");
                const field cID = r[0];
                const field cmnd = r[1];
                const field x = r[2];
                const field y = r[3];
                const field z = r[4];
                const field u1 = r[5]; 
                const field roe = r[6];
                std::stringstream commandstream;
                commandstream << cmnd << "," << x << "," << y << "," << z << "," << u1 << "," << roe;
                commandstream >> command;
                //const char* cstr = command.c_str();
                //OutputDebugString(cstr);
                //OutputDebugString("\n");
                txn.exec_prepared("delete");
                txn.commit();
            }
        }
        else {
            OutputDebugString("Can't open database");
        }
        C.disconnect();
    }
    catch (const std::exception& e) {
        OutputDebugString(e.what());
    }
    return command;
}