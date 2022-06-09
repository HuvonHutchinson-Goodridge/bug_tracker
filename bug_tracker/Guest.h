#pragma once
#include "I_Printable.h"

class Guest : public I_Printable {
private:
    static constexpr const char* def_first_name = "Unnamed Guest";
    static constexpr const char* def_last_name = "Unnamed Guest";
protected:
    std::string first_name;
    std::string last_name;
public:
    Guest(std::string first_name = def_first_name, std::string last_name = def_last_name);
    virtual void print(std::ostream& os) const;
    ~Guest();
};
