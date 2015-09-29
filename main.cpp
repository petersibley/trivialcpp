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
#pragma once
#include <array>

namespace fiftythree 
{
namespace elm
{
class CLASSNAMEDIMENSIONSHORTSCALARNAME
{
    public:
    // Aliases
    using ScalarT = SCALAR;
    static constexpr size_t Dimension = DIMENSION;


    // Ctors Dtors etc.
    CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME(std::initializer_list<ScalarT> list);
    CLASSNAMEDIMENSIONSHORTSCALARNAME(const CLASSNAMEDIMENSIONSHORTSCALARNAME & ) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(const CLASSNAMEDIMENSIONSHORTSCALARNAME & ) = default;
    CLASSNAMEDIMENSIONSHORTSCALARNAME& operator=(CLASSNAMEDIMENSIONSHORTSCALARNAME&&) = default;   
    ~CLASSNAMEDIMENSIONSHORTSCALARNAME() = default;

    // pointer getters.
    ScalarT* data(); 
    explicit CLASSNAMEDIMENSIONSHORTSCALARNAME(const ScalarT * data);

    // subscripting.
    ScalarT& operator[](size_t);
    const ScalarT& operator[](size_t) const;



    private:
    // Storage
    std::array<ScalarT, Dimension> _data;
    public:
)";
const char *header_footer = R"(
    public:
    static CLASSNAMEDIMENSIONSHORTSCALARNAME Zero();
    static CLASSNAMEDIMENSIONSHORTSCALARNAME Ones();
};
}
}
)";


const char* cpp_header = R"(
#include "CLASSNAMEDIMENSIONSHORTSCALARNAME.h"
#include <cassert>

using namespace std;
namespace fiftythree 
{
namespace elm
{
CLASSNAMEDIMENSIONSHORTSCALARNAME::CLASSNAMEDIMENSIONSHORTSCALARNAME(std::initializer_list<ScalarT> list)
{
    // TODO be nice to move this to constexpr or expression?
    assert(list.size() == DIMENSION);
    copy(begin(list), end(list), begin(_data));
}

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

CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::operator[](size_t pos)
{
    // TODO add debug asserts for checks builds.
    return _data[pos];
}
const CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::operator[](size_t pos) const
{
    // TODO add debug asserts for checks builds.
    return _data[pos];
}
)";

const char *header_getter_decl = R"(
    ScalarT& GETTERNAME();
    const ScalarT& GETTERNAME() const;
)";

const char *header_unit_decl = R"(
    static CLASSNAMEDIMENSIONSHORTSCALARNAME UNITGETTER();
)";


const char *cpp_getter_decl = R"(
CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::GETTERNAME() {
return _data[DIM];
}
const CLASSNAMEDIMENSIONSHORTSCALARNAME::ScalarT& CLASSNAMEDIMENSIONSHORTSCALARNAME::GETTERNAME() const{
return _data[DIM];
}
)";


const char *cpp_unitgetter_decl = R"(
CLASSNAMEDIMENSIONSHORTSCALARNAME CLASSNAMEDIMENSIONSHORTSCALARNAME::UNITGETTER() {
auto result = Zero();
result._data[DIM] = 1;
return result;
}
)";

const char* cpp_footer = R"(
CLASSNAMEDIMENSIONSHORTSCALARNAME CLASSNAMEDIMENSIONSHORTSCALARNAME::Zero() {
    auto result = CLASSNAMEDIMENSIONSHORTSCALARNAME();
    fill(begin(result._data), end(result._data), 0); 
    return result;
}

CLASSNAMEDIMENSIONSHORTSCALARNAME CLASSNAMEDIMENSIONSHORTSCALARNAME::Ones() {
    auto result = CLASSNAMEDIMENSIONSHORTSCALARNAME();
    fill(begin(result._data), end(result._data), 1); 
    return result;
}
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
        auto unitMethods = std::vector<std::vector<std::string>>{{{"UnitX"},{"UnitX","UnitY"},{"UnitX","UnitY","UnitZ"},{"UnitX","UnitY","UnitZ","UnitW"}}};
        auto pathPrefix = std::string{"elm/"};
        for (auto & name : classname) {
                for (auto &pair : scalar) {
            for (auto &d : dimensions) {
                    auto scalarType = pair.first;
                    auto scalarShortname = pair.second;

                    auto headerPath = pathPrefix + name + to_string(d) + scalarShortname + ".h";
                    ofstream headerOut;
                    headerOut.open(headerPath);
                    auto cppPath = pathPrefix + name + to_string(d) + scalarShortname + ".cpp";
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
                   auto & l2  = unitMethods[d -1];
                   for(int i = 0 ; i < l.size(); ++i) {
                       auto entry = l[i];
                        auto gg = find_all_replace(header_getter_decl, "GETTERNAME",entry);
                        headerOut << gg;
                   }

                   for(int i = 0 ; i < l2.size(); ++i) {
                       auto entry = l2[i];
                        auto gg = find_all_replace(header_unit_decl,"UNITGETTER",entry);
                        gg = find_all_replace(gg, "CLASSNAME", name);
                        gg = find_all_replace(gg, "DIMENSION",to_string(d));
                        gg = find_all_replace(gg, "SHORTSCALARNAME",scalarShortname);
                        gg = find_all_replace(gg, "DIM", to_string(i));
                        headerOut << gg;
                   }
                
                   apply(header_footer, headerOut);
                   headerOut.close();
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

                   for(int i = 0 ; i < l2.size(); ++i) {
                       auto entry = l2[i];
                        auto gg = find_all_replace(cpp_unitgetter_decl,"UNITGETTER",entry);
                        gg = find_all_replace(gg, "CLASSNAME", name);
                        gg = find_all_replace(gg, "DIMENSION",to_string(d));
                        gg = find_all_replace(gg, "SHORTSCALARNAME",scalarShortname);
                        gg = find_all_replace(gg, "DIM", to_string(i));
                        cppOut << gg;
                   }
                


                   apply(cpp_footer, cppOut);
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
