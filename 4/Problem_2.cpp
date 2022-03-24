#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

#define N 22
#define string_length 17

int main () {
    system("chcp 1251");

    std::ifstream is ("Lines_for_problem_2.txt", std::ifstream::binary);
    if (is.fail()) {
        std::cerr << "Could not open Lines_for_problem_2.txt\n";
        exit(1); // 1 indicates an error occurred
    }

    // get length of file:
    is.seekg (0, is.end);
    int length = is.tellg();
    is.seekg (0, is.beg);

    char * buffer = new char [string_length];

    int line_number;
    std::cout << "Choose a line to display: ";
    std::cin >> line_number;
    is.seekg (N * (line_number - 1) + 1, is.beg);
    std::cout << "Reading " << string_length << " characters... ";
    // read data as a block:
    is.read (buffer, string_length);

    if (is) {
        std::cout << "all characters read successfully." << std::endl;
        // ...buffer contains the entire line...
        for (int i = 0; i < string_length; i++) 
            std::cout << *(buffer + i);
        std::cout << std::endl;
    } else
        std::cerr << "error: only " << (length + 3) / N << " lines could be read" << std::endl;
    is.close();

    delete[] buffer;
  
  return 0;
}