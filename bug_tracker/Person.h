#pragma once
#include <string>
#include "I_Printable.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
class Person : public I_Printable {
private:
    static constexpr const char* def_first_name = "Unnamed Person";
    static constexpr const char* def_last_name = "Unnamed Person";
    static constexpr const char* def_password = "123456789";
    static constexpr const char* def_email = "JaneDoe@gmail.com";
    static constexpr const char* def_account_version = "Unknown Account";
    static const int def_account_id{ 0 };
protected:
    std::string first_name;
    std::string last_name;
    std::string password;
    std::string email;
    std::string account_version;
    int account_id;
public:
    Person(std::string first_name = def_first_name,
        std::string last_name = def_last_name,
        std::string password = def_password,
        std::string email = def_email,
        std::string account_version = def_account_version,
        int account_id = def_account_id);
    virtual void addBug() = 0;
    virtual void deleteAccount() = 0;
    virtual void deleteBug() = 0;
    virtual void updateBug() = 0;
    virtual void print(std::ostream& os) const override;
    virtual ~Person() = default;
};