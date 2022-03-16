#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main () 
{
    const std::string s = "Lorem ipsum dolor sit 2002.03.22 amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna 13:27:18 aliqua. Ut enim ad 2030.12.37 minim veniam, quis nostrud exercitation 2015.07.20 ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute 23:15:75 irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla 10:11:59 pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
 
    std::regex time_regex(
        "(2[0-3]|[01][0-9]):([0-5][0-9]):([0-5][0-9])"
        );
    auto time_begin = 
        std::sregex_iterator(s.begin(), s.end(), time_regex);
    auto time_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(time_begin, time_end) 
              << " time stamps:\n";
 
    std::string match_str;
    for (std::sregex_iterator i = time_begin; i != time_end; ++i) {
        std::smatch match = *i;                                                 
        match_str = match[0]; 
        std::cout << match_str << '\n';
    }   



    std::regex date_regex(
        "\\d{4}.(0[1-9]|1[0-2]).(0[1-9]|[12][0-9]|3[01])"
        );
    auto date_begin = 
        std::sregex_iterator(s.begin(), s.end(), date_regex);
    auto date_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(date_begin, date_end) 
              << " dates:\n";
 
    for (std::sregex_iterator i = date_begin; i != date_end; ++i) {
        std::smatch match = *i;                                                 
        match_str = match[0]; 
        std::cout << match_str << '\n';
    }   


    return 0;
}