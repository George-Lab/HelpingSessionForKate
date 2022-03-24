#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>


std::vector<std::string> removeComments(std::vector<std::string>& source) {
    std::vector<std::string> ans;
    bool commenting = false;
    bool inside_string = false;
    std::string modified;

    for (const std::string& line : source) {
      for (int i = 0; i < line.length();) {
        if (i + 1 == line.length()) {
          if (!commenting)
            modified += line[i];
          ++i;
          break;
        }
        if (!inside_string) {
            if (line[i] == '\"') {
                inside_string = true;
                modified += line[i];
                ++i;
                continue;
            }

            const std::string& twoChars = line.substr(i, 2);
            if (twoChars == "/*" && !commenting) {
                commenting = true;
                i += 2;
            } else if (twoChars == "*/" && commenting) {
                commenting = false;
                i += 2;
            } else if (twoChars == "//") {
                if (!commenting)
                    break;
                else
                    i += 2;
            } else {
                if (!commenting)
                    modified += line[i];
                ++i;
            }
        } else {
            if (line[i] == '\\') {
                modified += line[i];
                modified += line[i + 1];
                i += 2;
                continue;
            } else if (line[i] == '\"') {
                inside_string = false;
            }
            modified += line[i];
            ++i;
        }
        
      }
      if (modified.length() > 0 && !commenting) {
        ans.push_back(modified);
        modified = "";
      }
    }

    return ans;
  }

int main() {
    system("chcp 1251");
    
    std::ifstream fin;
    std::ofstream fout; 
    fin.open("test.txt");
    fout.open("output.txt");
    if (fin.fail()) {
        std::cerr << "Could not open test.txt\n";
        exit(1); // 1 indicates an error occurred
    }

    
    std::vector<std::string> file;
    std::string file_line;
    while(getline(fin, file_line)) {
        if(file_line.size() > 0)
            file.emplace_back(file_line);
    }

    file = removeComments(file);

    for(std::string & line : file) {
            fout << line << std::endl;
    }

    return 0;
}