#include "Bug.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

Bug::Bug(int bug_id,std::string bug, std::string bug_time, int bug_creator_id, std::string bug_creator_name, std::string bug_status)
    :bug_id{ bug_id }, bug{ bug }, bug_time{ bug_time }, bug_creator_id{ bug_creator_id }, bug_creator_name{bug_creator_name}, bug_status{bug_status}
{
//sql::Driver* driver {nullptr};
//std::unique_ptr<sql::Connection> con {nullptr};
//std::unique_ptr<sql::Statement> stmt {nullptr};
//std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO bugs(bug, bug_date, bug_creator) VALUES(?,?,?)"));
//
//
//try
//{
//    driver = get_driver_instance();
//    std::unique_ptr<sql::Connection> con (driver->connect(server, username, server_password));
//}
//catch (sql::SQLException e)
//{
//    std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
//    system("pause");
//    exit(1);
//}
//
//
//con->setSchema("bug_tracker");
////std::cout << "Connected to bug_tracker" << std::endl;
////stmt = con->createStatement();
////stmt->execute("DROP TABLE IF EXISTS bugs");
////std::cout << "Finished dropping table" << std::endl;
////stmt->execute("CREATE TABLE bugs(bug_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, bug_date VARCHAR(30) NOT NULL, bug VARCHAR(225) NOT NULL, bug_creator INT NOT NULL, bug_creator_name VARCHAR(25), FOREIGN KEY (bug_creator) REFERENCES accounts(id) ON DELETE CASCADE);");
////std::cout << "Finished creating table" << std::endl;
////delete stmt;
//
//pstmt->setString(1, bug);
//pstmt->setString(2, bug_time);
//pstmt->setInt(3, stoi(bug_creator));
//pstmt->execute();
//std::cout << "One row inserted." << std::endl;
}

int Bug::get_bug_id() const {
    return bug_id;
}

void Bug::print(std::ostream& os) const {
    os << "[" << bug_id << ": " << bug << " is currently: " << bug_status<< ". This bug was reported by " << bug_creator_name << " at " << bug_time << " ]";
}