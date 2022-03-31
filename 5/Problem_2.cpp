#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include <chrono>
#include <iomanip>

class Threads_Guard
{
public:

	explicit Threads_Guard(std::vector < std::thread > & threads) :
		m_threads(threads)
	{}

	Threads_Guard			(Threads_Guard const&) = delete;

	Threads_Guard& operator=(Threads_Guard const&) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::vector < std::thread > & m_threads;
};

template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int num_threads)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T > ()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}

int main(int argc, char ** argv)
{
	std::vector < int > v(100'000'000);

	std::iota(v.begin(), v.end(), 1);

	std::cout << parallel_accumulate(v.begin(), v.end(), 0, 8) << std::endl;

    for (int i = 1; i <= std::thread::hardware_concurrency(); i++) {
        auto t1 = std::chrono::high_resolution_clock::now();

		int res = parallel_accumulate(v.begin(), v.end(), 0, i);

		auto t2 = std::chrono::high_resolution_clock::now();


		std::cout << std::setw(16) << std::left << std::fixed << "number of threads: " << i <<
			" took " << std::chrono::duration_cast < std::chrono::milliseconds > (t2 - t1).count() << " (ms)\n";
    }

// С увеличением количества потоков увеличивается количество операций, выполняемых за единицу времени => 
// уменьшается время выполнения задачи

	system("pause");

	return EXIT_SUCCESS;
}