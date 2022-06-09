#pragma once
#include "Helper.h"
#include "database.h"
#include "Administrator.h"
#include "database.h"
#include <string>
#include <list>
#include <map>
#include <iterator>
#include <algorithm>
#include <iostream>

//FOR THE CREATION OF ACCOUNT OBJECTS
void create_account(std::string& response) {

    if (response == "YES") {

    sql::Driver* driver{ nullptr };
    std::string first_name;
    std::string last_name;
    std::string email;
    std::string password;
    std::string account_version;
    

    try
    {
        driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO accounts(access_level, first_name, last_name, email, password) VALUES(?,?,?,?,?)"));

        std::cout << "What kind of account will you make?" << std::endl;
        std::cout << "Admin, Faculty, or Guest" << std::endl;
        std::cin >> account_version;

        if (account_version == "Admin") {
            std::cout << "Please enter your first name" << std::endl;
            std::cin >> first_name;
            std::cout << "Please enter your last name" << std::endl;
            std::cin >> last_name;
            std::cout << "Please enter your email" << std::endl;
            std::cin >> email;
            std::cout << "Please enter your password" << std::endl;
            std::cin >> password;
        }
        else if (account_version == "Faculty") {
            std::cout << "Please enter your first name" << std::endl;
            std::cin >> first_name;
            std::cout << "Please enter your last name" << std::endl;
            std::cin >> last_name;
            std::cout << "Please enter your email" << std::endl;
            std::cin >> email;
            std::cout << "Please enter your password" << std::endl;
            std::cin >> password;
        }
        else {
            std::cout << "Please enter your first name" << std::endl;
            std::cin >> first_name;
            std::cout << "Please enter your last name" << std::endl;
            std::cin >> last_name;
        }
        pstmt->setString(1, account_version);
        pstmt->setString(2, first_name);
        pstmt->setString(3, last_name);
        pstmt->setString(4, email);
        pstmt->setString(5, password);
        pstmt->execute();
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        /*std::cout << "I connected to the bug_tracker database";
        stmt = con->createStatement();
        stmt->execute("DROP TABLE IF EXISTS accounts");
        std::cout << "Finished dropping table" << std::endl;
        stmt->execute("CREATE TABLE accounts(id INT NOT NULL AUTO_INCREMENT, access_level VARCHAR(10) NOT NULL, first_name VARCHAR(25) NOT NULL, last_name VARCHAR(25) NOT NULL, email VARCHAR(50) NOT NULL, password VARCHAR(10) NOT NULL, PRIMARY KEY (id));");
        std::cout << "Finished creating table" << std::endl;
        delete stmt;*/
    }
    else {
        std::cout << "" << std::endl;
    }
};

//FOR THE CREATION OF TIME FOR BUGS
std::tm localtime_xp(std::time_t timer)
{
    std::tm bt{};
#if defined(__unix__)
    localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &timer);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&timer);
#endif
    return bt;
}

std::string time_stamp(const std::string& fmt)
{
    auto bt = localtime_xp(std::time(0));
    char buf[64];
    return { buf, std::strftime(buf, sizeof(buf), fmt.c_str(), &bt) };
}

//FOR LOGGING INTO YOUR ACCOUNT
bool login(std::string& email, std::string& password) {

    sql::Driver* driver{ nullptr };

    try
    {
        driver = get_driver_instance();
        std::unique_ptr <sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);
        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT email, password FROM accounts WHERE email = ?"));
        pstmt->setString(1, email);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            if (res->getString(1) == email && res->getString(2) == password) {
                std::cout << "You have logged in" << std::endl;
                return true;
            }
        }
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    return false;
}

//FOR ENTERING DIFFERENT VERSIONS OF THE APPLICATION
void enter_application(bool login_bool, std::string& email, std::string& password) {
    std::string first_name;
    std::string last_name;
    std::string account_version;
    int account_id{ 0 };
    sql::Driver* driver{ nullptr };

    try
    {
        driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);
        while (login_bool) {
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT access_level, first_name, last_name, email, password, id  FROM accounts WHERE email = ?"));
            pstmt->setString(1, email);
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
            while (res->next()) {
                account_version = res->getString(1);
                first_name = res->getString(2);
                last_name = res->getString(3);
                email = res->getString(4);
                password = res->getString(5);
                account_id = res->getInt(6);
            };

            if (account_version == "Admin") {
                std::unique_ptr<Person> admin = std::make_unique<Administrator>(first_name, last_name, email, password, account_version, account_id);
                std::cout << *admin << std::endl;

                char response;
                do {
                std::cout << std::endl;
                std::cout << "What would you like to do?" << std::endl;
                std::cout << "Press A to add a bug to the database" << std::endl;
                std::cout << "Press D to delete a bug from the database" << std::endl;
                std::cout << "Press U to update a bug in the database" << std::endl;
                std::cout << "Press J to delete an account in the database" << std::endl;
                std::cout << "Press Q to quit the application" << std::endl;
                std::cin >> response;

                switch (response) {
                case 'A':
                case 'a':
                    admin->addBug();
                    break;
                case 'D':
                case 'd': 
                    admin->deleteBug();
                    break;
                case 'U':
                case 'u':
                    admin->updateBug();
                    break;
                case 'J':
                case 'j':
                    admin->deleteAccount();
                    break;
                case 'Q':
                case 'q':
                    std::cout << "You are leaving the application" << std::endl;
                    break;
                default:
                    std::cout << "You have entered the wrong input try again" << std::endl;
                }
                }while (response != 'Q' && response != 'q');

                admin->addBug();
                break;
            }
            else if (account_version == "Faculty") {
                std::unique_ptr<Person> faculty = std::make_unique<Faculty>(first_name, last_name, email, password, account_version);
                std::cout << *faculty << std::endl;
                faculty->addBug();
                break;
            }
            else if (account_version == "Guest") {
                std::unique_ptr<Guest> guest = std::make_unique<Guest>(first_name, last_name);
                std::cout << *guest << std::endl;
                break;
            }
        }

    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
};

void guest_application(bool login_bool, std::string& first_name, std::string& last_name) {
    const std::string server = "localhost";
    const std::string username = "admin";
    const std::string server_password = "Z938udi19*m#9";
    std::string account_version;
    std::string email = "UnnamedGuest@gmail.com";

    sql::Driver* driver{ nullptr };

    try
    {
        driver = get_driver_instance();
        std::unique_ptr<sql::Connection> con(driver->connect(server, username, server_password));
        std::cout << "I connected to the server" << std::endl;
        con->setSchema("bug_tracker");
        while (login_bool) {
            std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT access_level, first_name, last_name, email, FROM accounts WHERE email = ?"));
            pstmt->setString(1, email);
            std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
            while (res->next()) {
                account_version = res->getString(1);
                first_name = res->getString(2);
                last_name = res->getString(3);
                email = res->getString(4);
            };
            if (account_version == "Guest") {
                std::unique_ptr<Guest> guest = std::make_unique<Guest>(first_name, last_name);
                std::cout << *guest << std::endl;
                break;
            }
        }

    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

//FOR DISPLAYING THE BUGS IN A LIST

void displayBug(std::list<Bug>& bug_list) {
    std::list<Bug>::iterator it;
    for (it = bug_list.begin(); it != bug_list.end(); it++) {
        std::cout << *it << std::endl;
    }
}

//FOR DISPLAYING THE ACCOUNTS IN A MAP
void displayAccounts(std::map<int, std::string>& account_map) {
    std::map<int, std::string>::iterator it;
    for (it = account_map.begin(); it != account_map.end(); it++) {
        std::cout << it->first 
                  << ':' 
                  << it->second
                  << std::endl;
    }
};

//FOR DISPLAYING CURRENT BUG IN LIST
void display_current_bug(const Bug& bug) {
    std::cout << bug << std::endl;
}

//FOR DISPLAYING THE MENU FOR MANIPULATING BUGS IN THE DATABASE
void display_menu() {
    std::cout << "Press N for next bug" << std::endl;
    std::cout << "Press P for previous bug" << std::endl;
    std::cout << "Press Q to exit" << std::endl;
    std::cout << "Press C to display the current bug" << std::endl;
    std::cout << "Press S to select the current bug" << std::endl;
}