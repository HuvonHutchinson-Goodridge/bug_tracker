#pragma once
#include <iostream>
class I_Printable
{
    friend std::ostream& operator<<(std::ostream& os, const I_Printable& printer);
public:
    virtual void print(std::ostream& os) const = 0;
};