#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

template < typename C >
void print_clock_data()
{
	cout << "precision: " << setprecision(12) << fixed << 
		1.0 * C::period::num / C::period::den << " (seconds)" << endl;

	cout << "is_steady: " << boolalpha << C::is_steady << endl;
}

int main()
{
    unsigned int Number_of_random_nums;
    cout << "Enter number of random numbers: ";
    cin >> Number_of_random_nums;
    cout << "\n";

    // Generating random numbers WITHOUT repetition - START ////////////////////////////
    // https://studiofreya.com/2014/11/17/random-number-generator-in-cpp11-without-repetition/
    vector<unsigned int> vector_for_rand_nums;
    vector<unsigned int>::iterator it;
    // Our Random Generator
    mt19937 eng{random_device{}()};
 
    for (int i = 0; i != Number_of_random_nums; i++) {
        unsigned int q = uniform_int_distribution<unsigned int>{0, Number_of_random_nums}(eng);
 
        do {
            q = uniform_int_distribution<unsigned int>{0, Number_of_random_nums}(eng);
            it = find(vector_for_rand_nums.begin(), vector_for_rand_nums.end(), q);
        } while (it != vector_for_rand_nums.end());
 
        vector_for_rand_nums.push_back(q);
    }
    // END //////////////////////////////////////////////////////////
    
    // for (auto i = 0; i != Number_of_random_nums; i++)
    //     cout << vector_for_rand_nums[i] << " ";

    set<int> set_container;
    // Function to insert elements
    // in the set container
    cout << "Starting inserting elements into set container" <<  std::endl;
	chrono::steady_clock::time_point start1 = std::chrono::steady_clock::now();

    for (int i = 0; i != Number_of_random_nums; i++)
        set_container.insert(vector_for_rand_nums[i]);

    std::cout << "Finished inserting elements into set container" <<  std::endl;
	auto end1 = std::chrono::steady_clock::now();
	
	std::cout << "Time spent filling set container (milliseconds): ";
	auto elapsed1 = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1);

    std::cout << elapsed1.count() << std::endl;
    cout << ".\n.\n.\n";


    vector<int> vector_container;
    // Inserting same random numbers into vector container
    cout << "Starting inser & sort process for vector container" <<  std::endl;
	chrono::steady_clock::time_point start2 = std::chrono::steady_clock::now();

    for (int i = 0; i != Number_of_random_nums; i++)
        vector_container.push_back(vector_for_rand_nums[i]);
    // Sorting vector container
    sort(vector_container.begin(), vector_container.end());
    std::cout << "Finished inserting & sorting for vector container" <<  std::endl;
	auto end2 = std::chrono::steady_clock::now();

	std::cout << "Time spent filling & sorting for vector container (milliseconds): ";
	auto elapsed2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << elapsed2.count() << "\n\n";


    if (elapsed1 < elapsed2) {
        cout << "RESULT: Set container is faster\n";
    } else if (elapsed1 == elapsed2) {
        cout << "RESULT: Set container is as fast as vector container\n";
    } else {
        cout << "RESULT: Vector container is faster\n";
    }

    // Printing for debugging
    // cout << "The elements in set are: ";
    // for (auto i = set_container.begin(); i != set_container.end(); i++)
    //     cout << *i << " ";
    // cout << "\n";

    // cout << "The elements in vector are: ";
    // for (auto i = 0; i != Number_of_random_nums; i++)
    //     cout << vector_container[i] << " ";
    // cout << "\n";

    return 0;
}