// std::string
#include <iostream>
#include <string>
#include <string_view>
using namespace std::string_literals;

std::string_view extract_extension(std::string_view str)
{
    // & is not required
    // std::string_view keeps only the address and the lenght of the string
    return str.substr(str.rfind('.'));
}

int main(int argc, char const *argv[])
{
    // Raw literal
    std::string raw_str = R"--(Hell"O" Wor\nld)--"; // [R"(-starts] [)"-ends]
    std::cout << raw_str << '\n';

    auto str1 = "hello.ps"; // type is const char*
    auto str2 = "hello.lib"s; // type is std::string

    std::cout << extract_extension(str1) << '\n';
    std::cout << extract_extension(str2) << '\n';

    // C++11 convert between integers and strings
    int num = 123'456'789;
    auto str_num = std::to_string(num); // convert to a std::string
    str_num += str_num; // concatenate itself to get a long string
    unsigned long long long_num = std::stoull(str_num); // convert to long integer
    std::cout << "long integer: " << long_num << '\n';


    return EXIT_SUCCESS;
}
