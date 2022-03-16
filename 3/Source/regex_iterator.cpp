#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char ** argv)
{
	std::string data = "abc 1234 def 5678 hij";

	std::regex pattern(R"(\d{4})");

	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;

	std::for_each(begin, end, [](const std::smatch & m)
	{
		std::cout << m[0] << std::endl;
	});

	system("pause");

	return EXIT_SUCCESS;
}