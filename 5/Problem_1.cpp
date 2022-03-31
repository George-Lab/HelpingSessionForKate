#include <chrono>
#include <execution>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <vector>
#include <random>
#include <future>

#define INTERVAL 10000

double circle(double x, double radius) 
{ 
    double y = radius * radius - x * x; 
    return y; 
}

long double compute_pi() 
{
    std::random_device rd;   
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distrib{0.0, 1};

    int interval, i;
    double rand_x, rand_y, origin_dist, pi;
    int circle_points = 0, square_points = 0;
  
    // Total Random numbers generated = possible x
    // values * possible y values
    for (i = 0; i < (INTERVAL * INTERVAL); i++) {
  
        // Randomly generated x and y values
        rand_x = distrib(gen);
        rand_y = distrib(gen);
  
        // Distance between (x, y) from the origin
        origin_dist = rand_x * rand_x + rand_y * rand_y;
  
        // Checking if (x, y) lies inside the define
        // circle with R=1
        if (origin_dist <= 1)
            circle_points++;
  
        // Total number of points generated
        square_points++;
  
        // estimated pi after this iteration
        pi = double(4 * circle_points) / square_points;
  
        // For visual understanding (Optional)
        // std::cout << rand_x << " " << rand_y << " " << circle_points
        //      << " " << square_points << " - " << pi << std::endl;
  
    }
  
    // Final Estimated Value
    return pi;
    
}

long random_circle_sampling(long n_samples){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> distrib(0.0, 1.0);
    
    long circle_points = 0;
    for (long i = 0; i < n_samples; ++i) {
        double rand_x = distrib(gen);
        double rand_y = distrib(gen);
        double origin_dist = rand_x * rand_x + rand_y * rand_y;

        if(origin_dist <= 1.0)
            ++circle_points;
    }
    return circle_points;
}

long double parallel_compute_pi(long n_samples, int n_threads) 
{
    long samples_per_thread = n_samples / n_threads;

    // Used to store the future results
    std::vector<std::future<long>> futures;
    for(int t = 0; t < n_threads; ++t){
        // Start a new asynchronous task
        futures.emplace_back(std::async(std::launch::async, random_circle_sampling, samples_per_thread));
    }

    long square_points = 0;
    for(std::future<long>& f : futures){
        // Wait for the result to be ready
        square_points += f.get();
    }

    double pi = (double)(4 * square_points) /n_samples;
    return pi;
}



int main(int argc, char ** argv)
{
	std::vector < double > v(10'000'007, 0.5);

	{
		auto t1 = std::chrono::high_resolution_clock::now();

		double computed_pi = compute_pi();

		auto t2 = std::chrono::high_resolution_clock::now();


		std::cout << std::setw(16) << std::left << std::fixed << "compute_pi: " << computed_pi <<
			" took " << std::chrono::duration_cast < std::chrono::milliseconds > (t2 - t1).count() << " (ms)\n";
	}

	{
		auto t1 = std::chrono::high_resolution_clock::now();

		double computed_pi = parallel_compute_pi(INTERVAL * INTERVAL, 8);

		auto t2 = std::chrono::high_resolution_clock::now();

		std::cout << std::setw(16) << std::left << std::fixed << "parallel_compute_pi " << computed_pi << 
			" took " << std::chrono::duration_cast <std::chrono::milliseconds> (t2 - t1).count() << " (ms)\n";
	}

	system("pause");

	return EXIT_SUCCESS;
}