#include <iostream>
#include <iterator>
#include <string>
#include <regex>

int main () 
{
    const std::string s = "-----Original Message----- From: \"Tom Archer\" <tom@ArcherConsultingGroup.com> To: <chris@showprogramming.com>; <john.doe@duck=mail.com>; \"Erik\" <erik@function2form.net>; \"Krista Crawley-Archer\" <kristalinsky@yahoo.com>; <tmacg@mail.com> \"Essam\" <essam.ahmed@sympatica.ca>; <tburhop@cinci.rr.com> Sent: Monday, June 30, 20211 6:42 AM, Subject: Book is done!!";
 
    std::regex words_regex(
        "([\\w-.]+)"
        "(@)"
        "([\\w-]+)"
        "(\\.)"
        "([a-z]{2,5})"
        );
    auto words_begin = 
        std::sregex_iterator(s.begin(), s.end(), words_regex);
    auto words_end = std::sregex_iterator();
 
    std::cout << "Found " 
              << std::distance(words_begin, words_end) 
              << " emails:\n";
 
    std::string match_str;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;                                                 
        match_str = match[0]; 
        std::cout << match_str << " Domain: " << match[3] << '\n';
    }   


    return 0;
}