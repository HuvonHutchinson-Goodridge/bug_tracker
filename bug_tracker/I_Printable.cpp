#include "I_Printable.h"

std::ostream& operator<<(std::ostream& os, const I_Printable& printer) {
    printer.print(os);
    return os;
}

