#include "Administrator.h"
#include "Helper.h"
#include "database.h"



Administrator::Administrator(std::string first_name, std::string last_name, std::string email, std::string password, std::string account_version, int account_id)
    :Faculty{ first_name, last_name, email, password, account_version, account_id}
{
}

void Administrator::addBug() {

    std::string bug;
    std::string bug_date = time_stamp();
    std::string bug_creator_name{ first_name };
    std::string status{ "Pending"};
    int bug_creator_id {account_id};
    
    std::cout << "Please add a bug to the database" << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::getline(std::cin, bug);

    sql::Driver* driver{ nullptr };
    
    try
    {
        driver = get_driver_instance();

        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("INSERT INTO bugs(bug, bug_date, bug_creator, bug_creator_name, status) VALUES(?,?,?,?,?)"));
        pstmt->setString(1, bug);
        pstmt->setString(2, bug_date);
        pstmt->setInt(3, bug_creator_id);
        pstmt->setString(4, bug_creator_name);
        pstmt->setString(5, status);
        pstmt->execute();

    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }


    
    //std::cout << "Connected to bug_tracker" << std::endl;
    //stmt = con->createStatement();
    //stmt->execute("DROP TABLE IF EXISTS bugs");
    //std::cout << "Finished dropping table" << std::endl;
    //stmt->execute("CREATE TABLE bugs(bug_id INT NOT NULL AUTO_INCREMENT PRIMARY KEY, bug_date VARCHAR(30) NOT NULL, bug VARCHAR(225) NOT NULL, bug_creator INT NOT NULL, access VARCHAR(10), FOREIGN KEY (bug_creator) REFERENCES accounts(id));");
    //std::cout << "Finished creating table" << std::endl;
    //delete stmt;
    
}

void Administrator::deleteBug() {
    int bug_id{ 0 };
    int bug_creator{ account_id };
    std::string bug;
    std::string bug_date = time_stamp();
    std::string bug_creator_name{ first_name };
    std::list<Bug> bug_list;
    std::list<Bug>::iterator it;
    
    std::cout << "Please delete a bug to the database" << std::endl;
    sql::Driver* driver{ nullptr };
    

    try
    {
        driver = get_driver_instance();

        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT bug_id, bug_date, bug, bug_creator, bug_creator_name FROM bugs;"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            bug_id = res->getInt(1);
            bug_date = res->getString(2);
            bug = res->getString(3);
            bug_creator = res->getInt(4);
            bug_creator_name = res->getString(5);
            Bug bug_obj = Bug(bug_id, bug, bug_date, bug_creator, bug_creator_name);
            bug_list.push_back(bug_obj);
        }
        if(bug_list.size() == 0){
            std::cout << "There are no bugs in the database" << std::endl;
        }
        else {
            char response;
            auto it = bug_list.begin();
            std::string delete_bool;
            do {
                std::cout << std::endl;
                displayBug(bug_list);
                std::cout << std::endl;
                std::cout << "Press N for next bug" << std::endl;
                std::cout << "Press P for previous bug" << std::endl;
                std::cout << "Press Q to exit" << std::endl;
                std::cout << "Press C to display the current bug" << std::endl;
                std::cin >> response;

                switch (response) {
                case 'c':
                case 'C':
                    std::cout << "Current bug: " << *it << std::endl;
                    break;
                case 'n':
                case 'N':
                    it++;
                    if (it == bug_list.end()) {
                        it = bug_list.begin();
                    }
                    std::cout << "Current bug: " << *it << std::endl;
                    std::cout << "Would you like to delete this bug?" << std::endl;
                    std::cout << "Respond YES OR NO" << std::endl;
                    std::cin >> delete_bool;
                    if (delete_bool == "YES") {
                        std::unique_ptr<sql::PreparedStatement>pstmt(con->prepareStatement("DELETE FROM bugs WHERE bug_id = ?"));
                        pstmt->setInt(1, it->get_bug_id());
                        pstmt->execute();
                        bug_list.erase(it);
                    }
                    break;
                case 'p':
                case 'P':
                    it--;
                    if (it == bug_list.begin()) {
                        it = bug_list.end();
                    }
                    std::cout << "Current bug: " << *it << std::endl;
                    std::cout << "Would you like to delete this bug?" << std::endl;
                    std::cin >> delete_bool;
                    if (delete_bool == "YES") {
                        std::unique_ptr<sql::PreparedStatement>pstmt(con->prepareStatement("DELETE FROM bugs WHERE bug_id = ?"));
                        pstmt->setInt(1, it->get_bug_id());
                        pstmt->execute();
                        bug_list.erase(it);
                    }
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Leaving the application" << std::endl;
                    break;
                default:
                    std::cout << "You have entered the wrong input try again" << std::endl;
                }
            } while (response != 'q' && response != 'Q');
        }
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

void Administrator::updateBug() {
    int bug_id{ 0 };
    int bug_creator{ account_id };
    std::string bug;
    std::string bug_date = time_stamp();
    std::string bug_creator_name{ first_name };
    std::string bug_status;
    std::list<Bug> bug_list;
    std::list<Bug>::iterator it;

    std::cout << "Which bug has been resolved?" << std::endl;
    sql::Driver* driver{ nullptr };


    try
    {
        driver = get_driver_instance();

        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT bug_id, bug_date, bug, bug_creator, bug_creator_name, status FROM bugs WHERE status = 'Pending';"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            bug_id = res->getInt(1);
            bug_date = res->getString(2);
            bug = res->getString(3);
            bug_creator = res->getInt(4);
            bug_creator_name = res->getString(5);
            bug_status = res->getString(6);
            Bug bug_obj = Bug(bug_id, bug, bug_date, bug_creator, bug_creator_name, bug_status);
            bug_list.push_back(bug_obj);
        }
        if (bug_list.size() == 0) {
            std::cout << "There are no pending bugs in the database" << std::endl;
        }
        else {
            char response;
            auto it = bug_list.begin();
            std::string update_bool;

            std::cout << std::endl;
            displayBug(bug_list);
            std::cout << std::endl;
            display_menu();
            std::cout << std::endl;

            do {
                if (bug_list.size() == 0) {
                    response = 'Q';
                }
                std::cin >> response;

                switch (response) {
                case 'c':
                case 'C':
                    std::cout << std::endl;
                    displayBug(bug_list);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current bug: " << *it << std::endl;
                    std::cout << std::endl;
                    break;
                case 'n':
                case 'N':
                    it++;
                    if (it == bug_list.end()) {
                        it = bug_list.begin();
                    }
                    std::cout << std::endl;
                    displayBug(bug_list);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current bug: " << *it << std::endl;
                    std::cout << std::endl;
                    break;
                case 'p':
                case 'P':
                    if (it == bug_list.begin()) {
                        std::advance(it, bug_list.size());
                    }
                    it--;
                    std::cout << std::endl;
                    displayBug(bug_list);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current bug: " << *it << std::endl;
                    std::cout << std::endl;
                    break;
                case 'S':
                case 's':
                    std::cout << "Would you like to update this bug? Respond YES or NO" << std::endl;
                    std::cin >> update_bool;
                    if (update_bool == "YES") {
                        std::unique_ptr<sql::PreparedStatement>pstmt(con->prepareStatement("UPDATE bugs SET status = 'Resolved' WHERE bug_id = ?;"));
                        pstmt->setInt(1, it->get_bug_id());
                        pstmt->execute();
                        bug_list.erase(it);
                        std::cout << std::endl;
                        std::cout << "The bug has been updated" << std::endl;
                    }
                    std::cout << std::endl;
                    displayBug(bug_list);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Leaving the application" << std::endl;
                    break;
                default:
                    std::cout << "You have entered the wrong input try again" << std::endl;
                }
            } while (response != 'q' && response != 'Q');
        }
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

void Administrator::deleteAccount() {

    int account_id{ 0 };
    std::string delete_email;
    std::string delete_first_name;
    std::string delete_last_name;
    std::map<int, std::string> account_map;
    std::map<int, std::string>::iterator it;

    sql::Driver* driver{ nullptr };

    try
    {
        driver = get_driver_instance();

        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT id, email, first_name FROM accounts"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            account_id = res->getInt(1);
            delete_email = res->getString(2);
            delete_first_name = res->getString(3);
            account_map.insert(std::pair<int, std::string>(account_id, delete_email));
        }
        if (account_map.size() == 0) {
            std::cout << "There are no bugs in the database" << std::endl;
        }else {
            char response;
            auto it = account_map.begin();
            std::string delete_bool;

            std::cout << std::endl;
            displayAccounts(account_map);
            std::cout << std::endl;
            display_menu();
            std::cout << std::endl;
            do {
                std::cin >> response;
                switch (response) {
                case 'c':
                case 'C':
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << (*it).second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'n':
                case 'N':
                    it++;
                    if (it == account_map.end()) {
                        it = account_map.begin();
                    }
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << it->second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'p':
                case 'P':
                    if (it == account_map.begin()) {
                        std::advance(it, account_map.size());
                    }
                    it--;
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << it->second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'S':
                case 's':
                    std::cout << "Would you like to delete this account?" << std::endl;
                    std::cout << "Respond YES OR NO" << std::endl;
                    std::cin >> delete_bool;
                    if (delete_bool == "YES") {
                        std::unique_ptr<sql::PreparedStatement>pstmt(con->prepareStatement("DELETE FROM accounts WHERE email = ?"));
                        pstmt->setString(1, it->second);
                        pstmt->execute();
                        account_map.erase(it);
                    }
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Leaving the application" << std::endl;
                    break;
                default:
                    std::cout << "You have entered the wrong input try again" << std::endl;
                }
            } while (response != 'q' && response != 'Q');

        }
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

void Administrator::updateAccount() {
    int account_id{ 0 };
    std::string delete_email;
    std::string delete_first_name;
    std::string delete_last_name;
    std::map<int, std::string> account_map;
    std::map<int, std::string>::iterator it;

    sql::Driver* driver{ nullptr };

    try
    {
        driver = get_driver_instance();

        std::unique_ptr<sql::Connection> con(driver->connect(MY_SERVER, MY_USER, MY_DB_PASSWORD));
        con->setSchema(MY_DB);

        std::unique_ptr<sql::PreparedStatement> pstmt(con->prepareStatement("SELECT id, email, first_name FROM accounts"));
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        while (res->next()) {
            account_id = res->getInt(1);
            delete_email = res->getString(2);
            delete_first_name = res->getString(3);
            account_map.insert(std::pair<int, std::string>(account_id, delete_email));
        }
        if (account_map.size() == 0) {
            std::cout << "There are no bugs in the database" << std::endl;
        }
        else {
            char response;
            auto it = account_map.begin();
            std::string delete_bool;

            std::cout << std::endl;
            displayAccounts(account_map);
            std::cout << std::endl;
            display_menu();
            std::cout << std::endl;
            do {
                std::cin >> response;
                switch (response) {
                case 'c':
                case 'C':
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << (*it).second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'n':
                case 'N':
                    it++;
                    if (it == account_map.end()) {
                        it = account_map.begin();
                    }
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << it->second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'p':
                case 'P':
                    if (it == account_map.begin()) {
                        std::advance(it, account_map.size());
                    }
                    it--;
                    std::cout << std::endl;
                    displayAccounts(account_map);
                    std::cout << std::endl;
                    display_menu();
                    std::cout << std::endl;
                    std::cout << "Current account: " << it->second << std::endl;
                    std::cout << std::endl;
                    break;
                case 'S':
                case 's':
                    std::cout << "Would you like to update this account?" << std::endl;
                    std::cout << "Respond YES OR NO" << std::endl;
                    std::cin >> delete_bool;
                    if (delete_bool == "YES") {
                        std::unique_ptr<sql::PreparedStatement>pstmt(con->prepareStatement("UPDATE accounts SET access_level = 'Faculty' WHERE email = ?"));
                        pstmt->setString(1, it->second);
                        pstmt->execute();
                        account_map.erase(it);
                    }
                    break;
                case 'Q':
                case 'q':
                    std::cout << "Leaving the application" << std::endl;
                    break;
                default:
                    std::cout << "You have entered the wrong input try again" << std::endl;
                }
            } while (response != 'q' && response != 'Q');

        }
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

void Administrator::print(std::ostream& os) const {
    os << "[Administrator: " << first_name << " " << last_name << "]";
}