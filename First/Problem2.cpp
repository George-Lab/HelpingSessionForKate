#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

// http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html

//Random string generator
const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
std::string random_string(std::size_t length)
{
    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::string random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}
//ENd /////////////////////////////////////


template < typename T >
void hash_combine(std::size_t & seed, const T & value) noexcept
{
	seed ^= std::hash < T > ()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t & seed, const T & value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t & seed, const T & value, const Types & ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}


struct Customer 
{
    std::string m_name;
    std::size_t m_mark;
};

int main(int argc, char ** argv)
{
    
    unsigned int Number_of_structs; 
    std::cout << "How many structs to create?\n> ";
    std::cin >> Number_of_structs;

	Customer cus;
    std::set<size_t> set_of_hashes;
    // Generating random numbers WITHOUT repetition - START ////////////////////////////
    // https://studiofreya.com/2014/11/17/random-number-generator-in-cpp11-without-repetition/
    vector<unsigned int> vector_for_rand_nums;
    vector<unsigned int>::iterator it;
    // Our Random Generator
    mt19937 eng{random_device{}()};
 
    for (int i = 0; i != Number_of_structs; i++) {
        unsigned int q = uniform_int_distribution<unsigned int>{0, Number_of_structs}(eng);
 
        do {
            q = uniform_int_distribution<unsigned int>{0, Number_of_structs}(eng);
            it = find(vector_for_rand_nums.begin(), vector_for_rand_nums.end(), q);
        } while (it != vector_for_rand_nums.end());
 
        vector_for_rand_nums.push_back(q);
    }
    // END //////////////////////////////////////////////////////////

    std::cout << "Generating " << Number_of_structs << " random structures\n";
	for (int i = 0; i < Number_of_structs; i++) {
        srand((unsigned) time(0)); // for generating random string length with rand() function
        cus.m_name = random_string(rand() % 10 + 1);
        cus.m_mark = vector_for_rand_nums[i];
        set_of_hashes.insert(hash_value(cus.m_name, cus.m_mark));
    }
	
    std::cout << "Number of elements in set of hashes " << set_of_hashes.size() << "\n";
    if (set_of_hashes.size() == Number_of_structs) {
        std::cout << "No hash collisions happened\n";
    } else {
        std::cout << Number_of_structs - set_of_hashes.size() << " collision happened\n";
    }

	
	//system("pause");

	return EXIT_SUCCESS;
}
