#include <windows.h>
#include <iostream>
#include <pqxx/pqxx>  
#include<sstream> 
#include <debugapi.h>
#include <ConnectToSQL.h>




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
    std::string unit_position = message.substr(found3+1, found4-(found3+1));

    std::size_t found5 = message.find(";", found4 + 1);
    std::string unit_orientation = message.substr(found4+1, found5-(found4+1));

    std::size_t found6 = message.find(";", found5 + 1);
    std::string unit_velocity = message.substr(found5+1, found6-(found5+1));

    C.prepare("remove_previous", "delete from blufor where unit_name=$1;");
    C.prepare("insert_to_blufor",
        "insert into blufor (unit_id, unit_name, unit_health, unit_ammo, unit_type, unit_position, unit_orientation, unit_velocity) values ($1, $2, $3, $4, $5, $6, $7, $8);");
    try {

        //connection C("dbname = units user = postgres password = ichigo \      hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            OutputDebugString("Opened database successfully!\n");
            work txn(C);
            txn.exec_prepared("remove_previous",unit_name);
            OutputDebugString("Previous Rows Removed\n");
            txn.commit();
            txn.exec_prepared("insert_to_blufor", messageID, unit_name, unit_health, unit_ammo, unit_type, unit_position, unit_orientation, unit_velocity);
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