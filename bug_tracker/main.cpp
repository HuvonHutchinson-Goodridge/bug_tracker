#include <iostream>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <chrono>
#include <jdbc.h>
#include "Helper.h"
#include "database.h"
#include "Bug.h"



using namespace std;

//for demonstration only. never save your password in the code!
int main()
{   
    sql::Driver* driver{ nullptr };

    try{
        driver = get_driver_instance();

        std::shared_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::string response;
        std::cout << "Would you like to create a new account? Reply YES or NO" << std::endl;
        getline(cin, response);
        create_account(response, con);

        bool login_bool{ false };
        std::string email;
        std::string password;

        while (!login_bool) {
            std::cout << "Please login to your account" << std::endl;
            std::cout << "What is your email?" << std::endl;
            getline(cin, email);
            std::cout << "What is your password?" << std::endl;
            getline(cin, password);

            if (login(email, password)) {
                std::cout << "It worked" << std::endl;
                login_bool = true;
            }
            else {
                std::cout << "Please enter email and password again" << std::endl;
            }
        }
        enter_application(login_bool, email, password, con);
    }
    catch (sql::SQLException e) {
        std::cout << "Could not connect to server. Error Message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
    return 0;
    
}
