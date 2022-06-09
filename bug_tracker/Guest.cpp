#include "Guest.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

const std::string server = "localhost";
const std::string username = "admin";
const std::string server_password = "Z938udi19*m#9";

Guest::Guest(std::string first_name, std::string last_name)
    :first_name{ first_name }, last_name{ last_name }
{
}

void Guest::print(std::ostream& os) const {
    os << "[Guest: " << first_name << " " << last_name << "]";
}

Guest::~Guest()
{
}

