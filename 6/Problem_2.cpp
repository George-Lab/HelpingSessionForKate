#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <mutex>
#include <future>
#include <atomic>

template < typename T >
class Threadsafe_Vector
{
public: 
    
    Threadsafe_Vector() = default;

    Threadsafe_Vector& operator=(const Threadsafe_Vector &) = delete;

public: 

    void push (T value)
    {
        std::lock_guard < std::mutex > lock(data_lock);
        data.emplace_back(value);
    }

    void sort ()
    {
        std::lock_guard <std::mutex > lock(data_lock);
        sort(data.begin(), data.end());
    }

    void print()
    {
        for (auto element : data) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

private:
    
    std::vector < T > data;

    mutable std::mutex data_lock;

};

void find_Index(std::string str, std::string s, int i, Threadsafe_Vector < int > & vec)
{
    for (int j = i, k = 0; j < i + str.length(); j++, k++) {
        if (str.substr(k, s.length()) == s) {
            vec.push(j);
        }
    }
}

int main()
{
    Threadsafe_Vector < int > vec;
    std::vector <std::thread> threads;

    std::string DNA = 
        "TGGCAGCTACGTGAGCCTGACGAGCAGTGAAATGTCGGATGAGCGCCCCC"
        "CGGACCTAGTTCCGGGGCCCCATGGAGTGCTGATAACTACAGGTTCACCT"
        "GGGCCCGACCTCGTAAAGAAGGAAGCGGAGTAAGGGCCACGGGAACGTAT"
        "CAGGTGCCAACTTATAGTCAAGCACCCTAAACAGCCATGGCGTCACGAGT"
        "CAACGACTTTAGTACGGCTAGCACTTCATGACGGTTCGCTCCGGGCCGAG";
    std::string fragment;
    std::cin >> fragment; 

    std::size_t DNA_length = DNA.size();
    std::size_t fragment_length = fragment.size();

    const std::size_t min_per_thread = 2 * fragment_length - 1;
	const std::size_t max_threads = DNA_length / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 1, max_threads);
    
    const std::size_t thread_length = 
        DNA_length / num_threads + fragment_length - 1;
    const std::size_t last_thread_length = 
        (DNA_length / num_threads) + (DNA_length % num_threads);

    bool flag = false;
    for (int i = 0; i < num_threads - 1; i++) {
        std::string str = DNA.substr( i * (thread_length - fragment_length + 1), thread_length);
        threads.emplace_back(std::thread(
            find_Index, 
            str, 
            fragment, i * (thread_length - fragment_length + 1), 
            std::ref(vec)
        )
        );
    }

    std::string str = DNA.substr( (num_threads - 1) * (thread_length - fragment_length + 1), last_thread_length);
    threads.emplace_back(std::thread(
        find_Index, 
        str, 
        fragment, 
        (num_threads - 1) * (thread_length - fragment_length + 1), 
        std::ref(vec)
    )
    );

    for (auto& th : threads) 
        th.join();
    
    vec.print();



    return EXIT_SUCCESS;
}