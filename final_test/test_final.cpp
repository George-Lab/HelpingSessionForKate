#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main () 
{
    const std::string s = "Lorem ipsum dolor sit 12.34.56.78 amet, consectetur adipiscing elit, \
    sed do eiusmod tempor incididunt ut labore et dolore magna 12.34.56.78 aliqua. Ut enim ad 2030.12.37 \
    minim veniam, quis nostrud exercitation 12.34.56.78 ullamco laboris nisi ut aliquip ex ea commodo\
     consequat. Duis aute 23:15:75 irure dolor in reprehenderit in 192.168.1.1 voluptate velit esse cillum dolore\
      eu fugiat nulla 10:11:59 pariatur. Excepteur sint 192.168.1.255 occaecat cupidatat non proident, sunt in culpa\
       qui officia deserunt mollit anim id est laborum.";
 
    std::regex address_regex(
        "(192)\\.(168)\\.(1)\\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])"
        //(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0- 9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])
        );
    auto address_begin = 
        std::sregex_iterator(s.begin(), s.end(), address_regex);
    auto address_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(address_begin, address_end) 
              << " valid ip addresses:\n";
 
    std::string match_str;
    for (std::sregex_iterator i = address_begin; i != address_end; ++i) {
        std::smatch match = *i;                                                 
        match_str = match[0]; 
        std::cout << match_str << '\n';
    }   

    return 0;
}