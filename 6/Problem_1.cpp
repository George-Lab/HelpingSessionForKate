#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <future>
#include <atomic>

void random_circle_sampling(long n_samples, std::atomic <unsigned long long> & circle_points)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    
    long _circle_points = 0;
    for (long i = 0; i < n_samples; ++i) {
        double rand_x = distrib(gen);
        double rand_y = distrib(gen);
        double origin_dist = rand_x * rand_x + rand_y * rand_y;

        if(origin_dist <= 1.0)
            ++_circle_points;
    }
    
    circle_points.fetch_add(_circle_points);
}

long double parallel_compute_pi(long n_samples, int num_threads) 
{
    const std::size_t samples_per_thread = n_samples / num_threads;
    const std::size_t samples_in_last_thread = samples_per_thread + n_samples % num_threads;

    std::atomic <unsigned long long> circle_points { 0 };

    // Used to store the future results
    for(int t = 0; t < num_threads - 1; ++t){
        // Start a new asynchronous task
        std::async(std::launch::async, random_circle_sampling, samples_per_thread, std::ref(circle_points));
    }
    // Last thread
    std::async(std::launch::async, random_circle_sampling, samples_in_last_thread, std::ref(circle_points));

    long double pi = (long double)(4 * circle_points) / n_samples;
    return pi;
}


int main() 
{
    const unsigned long long n_samples = 1'000'000;

    const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(n_samples + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 1, max_threads);

    std::cout << "Computing Pi: " << parallel_compute_pi(n_samples, num_threads) << std::endl; 

    return EXIT_SUCCESS;
}