#include <iostream>
#include <fstream>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <map>

using namespace std;


std::string find_all_replace(const std::string & temp, const std::string & key, const std::string & value) 
{
    auto result = temp; 
    auto prevPos = 0;
    auto pos = 0;
    while(std::string::npos != (pos = result.find(key, prevPos))) {
        result = result.replace(pos, key.length(), value);
        prevPos = pos;
    }
    return result;
}

const char *header_header = R"(
#include <array>

namespace fiftythree 
{
namespace el
{
class CLASSNAMEDIMENSIONSHORTSCALARNAME
{
    // Aliases
    using ScalarT = SCALAR;
    static constexpr size_t Dimension = DIMENSION;

    // Storage
    std::array<ScalarT, Dimension> _data;

    // Ctors Dtors etc.
    CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME(const CLASSNAMEDIMENSIONSHORTSCALARNAME & ) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(const CLASSNAMEDIMENSIONSHORTSCALARNAME & ) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(CLASSNAMEDIMENSIONSHORTSCALARNAME&&) = default;   
    ~CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;

    ScalarT* data(); 
    explicit CLASSNAMEDIMENSIONSHORTSCALARNAME(const ScalarT * data);

)";
const char *header_footer = R"(
};
}
}
)";


const char* cpp_header = R"(
#include "CLASSNAMEDIMENSIONSHORTSCALARNAME.h"

namespace fiftythree 
{
namespace el
{
CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT* CLASSNAMEDIMENSIONSHORTSCALARNAME::data() 
{
    return _data.data();
}
CLASSNAMEDIMENSIONSHORTSCALARNAME::CLASSNAMEDIMENSIONSHORTSCALARNAME(const CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT * d) 
{
    for(size_t i = 0; i < Dimension; ++i) {
        _data[i] = *(d+i);
    }
}    
)";

const char *header_getter_decl = R"(
    ScalarT& GETTERNAME();
    const ScalarT& GETTERNAME() const;
)";

const char *cpp_getter_decl = R"(
CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::GETTERNAME() {
return _data[DIM];
}
const CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::GETTERNAME() const{
return _data[DIM];
}
)";

const char* cpp_footer = R"(
}
}    
)";







int main(int argc, char** argv)
{
    try
    {

        auto classname = {"Vector"};
        auto dimensions = {1,2,3,4};
        auto scalar = std::map<std::string, std::string>{{{"float", "f"}, {"double","d"}, {"int", "i"}}};
        auto methods = std::vector<std::vector<std::string>>{{{"x"},{"x","y"},{"x","y","z"},{"x","y","z","w"}}};

        for (auto & name : classname) {
                for (auto &pair : scalar) {
            for (auto &d : dimensions) {
                    auto scalarType = pair.first;
                    auto scalarShortname = pair.second;

                    auto headerPath = name + to_string(d) + scalarShortname + ".h";
                    ofstream headerOut;
                    headerOut.open(headerPath);
                    auto cppPath = name + to_string(d) + scalarShortname + ".cpp";
                    ofstream cppOut;
                    cppOut.open(cppPath);

                    cout << "HEADER : " << headerPath << " CPP : " << cppPath << "\n";
                    auto apply = [=](const auto & s, auto & ss)  {
                        auto pp = find_all_replace(s, "CLASSNAME", name); 
                        pp = find_all_replace(pp, "DIMENSION",to_string(d));
                        pp = find_all_replace(pp, "SHORTSCALARNAME",scalarShortname);
                        pp = find_all_replace(pp, "SCALAR",scalarType);
                        ss << pp;
                   };

                   apply(header_header, headerOut);
                   auto & l  = methods[d - 1];
                   for(int i = 0 ; i < l.size(); ++i) {
                       auto entry = l[i];
                        auto gg = find_all_replace(header_getter_decl, "GETTERNAME",entry);
                        headerOut << gg;
                   }
                   apply(header_footer, headerOut);
                   apply(cpp_header, cppOut);
                   for(int i = 0 ; i < l.size(); ++i) {
                       auto entry = l[i];
                        auto gg = find_all_replace(cpp_getter_decl,"GETTERNAME",entry);
                        gg = find_all_replace(gg, "CLASSNAME", name);
                        gg = find_all_replace(gg, "DIMENSION",to_string(d));
                        gg = find_all_replace(gg, "SHORTSCALARNAME",scalarShortname);
                        gg = find_all_replace(gg, "DIM", to_string(i));
                        cppOut << gg;
                   }
                   headerOut.close();
                   cppOut << cpp_footer;
                   cppOut.close();
                }
            }
        }
    }
    catch (std::exception & e)
    {
        cerr << "unexpected exception:" << e.what() << endl;
    }
    

    return 0;
}
