#pragma once
#include <iostream>
#include "Person.h"

class Faculty : public Person {
private:
    static constexpr const char* def_first_name = "Unnamed Faculty";
    static constexpr const char* def_last_name = "Unnamed Faculty";
    static constexpr const char* def_password = "123456789";
    static constexpr const char* def_email = "JaneDoe@gmail.com";
    static constexpr const char* def_account_version{ "faculty" };
    static const int def_account_id{ 0 };
protected:
    std::string account_version;
public:
    Faculty(std::string first_name = def_first_name,
        std::string last_name = def_last_name,
        std::string password = def_password,
        std::string email = def_email,
        std::string account_version = def_account_version,
        int account_id = def_account_id);
    virtual void addBug() override;
    virtual void deleteBug() override;
    virtual void updateBug() override;
    virtual void deleteAccount() override;
    virtual void print(std::ostream& os) const override;
    virtual ~Faculty() = default;

};