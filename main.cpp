#include <iostream>
#include <vector>
#include <exception>
#include <boost/foreach.hpp>
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
namespace fiftythree 
{
namespace el
{
class CLASSNAMEDIMENSIONSHORTSCALARNAME
{
    // Aliases
    using ScalarT = SCALAR;
    constexpr size_t Dimension = DIMENSION;

    // Storage
    std::array<ScalarT, Dimension> _data;

    // Ctors Dtors etc.
    CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME(const & CLASSNAMEDIMENSIONSHORTSCALARNAME) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(const & CLASSNAMEDIMENSIONSHORTSCALARNAME) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(CLASSNAMEDIMENSIONSHORTSCALARNAME&&) = default;   
    ~CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;

    T* data(); 
    explicit CLASSNAMEDIMENSIONSHORTSCALARNAME(const ScalarT * data);
)";
const char *header_footer = R"(
};
}
}
)";


const char* cpp_header = R"(
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





int main(int argc, char** argv)
{
    try
    {

        auto classname = {"Vector"};
        auto dimensions = {1,2,3,4};
        auto scalar = std::map<std::string, std::string>{{{"float", "f"}, {"double","d"}, {"int", "i"}}};
        auto methods = std::vector<std::vector<std::string>>{{{"x"},{"x","y"},{"x","y","z"},{"x","y","z","w"}}};


        for (auto & name : classname) {
            for (auto &d : dimensions) {
                for (auto &pair : scalar) {
                    auto scalarType = pair.first;
                    auto scalarShortname = pair.second;

                    auto apply = [=](const auto & s)  {
                        auto pp = find_all_replace(s, "CLASSNAME", name); 
                        pp = find_all_replace(pp, "DIMENSION",to_string(d));
                        pp = find_all_replace(pp, "SHORTSCALARNAME",scalarShortname);
                        pp = find_all_replace(pp, "SCALAR",scalarType);
                        cout << pp;
                   };
                   apply(header_header);
                   for(auto i = 0; i < dimensions.size(); ++i) {
                        
                   }
                   apply(header_footer);
                   apply(cpp_header);
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
