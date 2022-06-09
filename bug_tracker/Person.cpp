#include "Person.h"
Person::Person(std::string first_name, std::string last_name, std::string email, std::string password, std::string account_version, int account_id)
    :first_name{ first_name }, last_name{ last_name }, email{ email }, password{ password }, account_version{account_version}, account_id{account_id}
{
}

void Person::addBug() {
}

void Person::deleteBug() {
    
}

void Person::updateBug() {
   
}

void Person::deleteAccount() {

}

void Person::print(std::ostream& os) const {
    os << first_name << " " << last_name << " " << email;
}
