#include "Faculty.h"
#include "Helper.h"
#include "database.h"

Faculty::Faculty(std::string first_name, std::string last_name, std::string email, std::string password,  std::string account_version, int account_id)
    :Person{ first_name, last_name, email, password, account_version, account_id}
{
}

void Faculty::addBug(std::shared_ptr<sql::Connection> con) {
    std::string bug;
    std::string bug_date = time_stamp();
    int bug_creator{ account_id };
    std::cout << "Please delete a bug to the database" << std::endl;
    std::getline(std::cin, bug);
    sql::Driver* driver{ nullptr };

;
    std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement(" bugs(bug, bug_date, bug_creator) VALUES(?,?,?)"));
    pstmt->setString(1, bug);
    pstmt->setString(2, bug_date);
    pstmt->setInt(3, bug_creator);
    pstmt->execute();
}

void Faculty::deleteBug(std::shared_ptr<sql::Connection> con) {
    std::cout << "whore" << std::endl;
}

void Faculty::updateBug(std::shared_ptr<sql::Connection> con) {
    std::cout << "whore" << std::endl;
}

void Faculty::deleteAccount(std::shared_ptr<sql::Connection> con) {

}

void Faculty::print(std::ostream& os) const {
    os << "[Faculty: " << first_name << " " << last_name << "]";
}