#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <random>
#include <algorithm>

using namespace std;

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
    std::string m_gender;
    unsigned int m_id;
};

int main(int argc, char ** argv)
{
    unsigned int Number_of_structs; 
    std::cout << "How many structs to create?\n> ";
    std::cin >> Number_of_structs;
	Customer cus;
    std::set<size_t> set_of_hashes;

    // // Generating random numbers WITHOUT repetition - START ////////////////////////////
    std::set<unsigned int> set_of_random_numbers;
    typedef std::mt19937 MyRNG;  // the Mersenne Twister with a popular choice of parameters
    uint32_t seed_val;           // populate somehow

    MyRNG rng;                   // e.g. keep one global instance (per thread)
    rng.seed(seed_val);
    
    std::uniform_int_distribution<uint32_t> uint_dist;         // by default range [0, MAX]
    std::uniform_int_distribution<uint32_t> uint_dist4(1,4000000000); // range [1,4000000000]
    std::uniform_int_distribution<uint32_t> uint_dist2(0,1);

    for (int i = 0; i != Number_of_structs; i++) {
        set_of_random_numbers.insert(uint_dist4(rng));
    }
    while (set_of_random_numbers.size() < Number_of_structs) {
        set_of_random_numbers.insert(uint_dist4(rng));
    }
    //Printing elemnts from set_of_random_numbers for debugging
    // cout << "The elements in set are: ";
    // for (auto i = set_of_random_numbers.begin(); i != set_of_random_numbers.end(); i++)
    //     cout << *i << " ";
    // cout << "\n";
    // // END /////////////////////////////////////////////////////////////////////////////

    std::cout << "Generating " << Number_of_structs << " random structures\n";
	for (auto i = set_of_random_numbers.begin(); i != set_of_random_numbers.end(); i++) {
        if (uint_dist2(rng) == 0) {
            cus.m_gender = "male";
        } else {
            cus.m_gender = "female";
        }
        cus.m_id = *i;
        set_of_hashes.insert(hash_value(cus.m_gender, cus.m_id));
        //std::cout << "Struct " << "" << ":\ngenger: " << cus.m_gender << "\nid: " << cus.m_id << "\n"; 
        //std::cout << "Hash: " << hash_value(cus.m_gender, cus.m_id) << "\n";
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