#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include "Bug.h"
#include "Person.h"
#include "Administrator.h"
#include "Faculty.h"
#include "Guest.h"
#include "mysql_connection.h"

//FOR THE INITIALIZATION OF THE APPLICATION
void init();

//FOR THE SETTING OF BUG TIME CREATION
std::tm localtime_xp(std::time_t timer);
std::string time_stamp(const std::string& fmt = "%F %T");

//FOR THE CREATION OF ACCOUNTS
void create_account(std::string& response, std::shared_ptr<sql::Connection> con);

//FOR LOGGING INTO THE APPLICATION

bool login(std::string& email, std::string& password);

//FOR ENTERING THE APPLICATION

void enter_application(bool login_bool, std::string& email, std::string& password, std::shared_ptr<sql::Connection> con);

void guest_application(bool login_bool, std::string& first_name, std::string& last_name);

//FOR DISPLAYING THE ENTIRE LIST OF BUGS

void displayBug(std::list<Bug>& bug_list);

//FOR DISPLAYING THE ACCOUNTS IN A MAP
void displayAccounts(std::map<int, std::string>& account_map);

//FOR DISPLAYING THE CURRENT BUG

void display_current_bug(const Bug& bug);

//FOR DISPLAYING THE MENU FOR UPDATING BUGS
void display_menu();