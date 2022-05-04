#include <sstream>

std::string to_string(int a){
    std::ostringstream s;
    s << a;
    return s.str();
}

