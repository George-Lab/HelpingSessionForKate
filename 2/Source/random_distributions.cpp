#include <random>
#include <iostream>

int main()
{
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
                        // replace the call to rd() with a
                        // constant value to get repeatable
                        // results.
    std::uniform_int_distribution<> distrib1{1, 6};
    std::uniform_real_distribution<> distrib2{1.0, 2.0};
    std::binomial_distribution<> distrib3{4, 0.5};
    std::poisson_distribution<> distrib4{4};
    std::normal_distribution<> distrib5{5, 2};

    std::cout << "std::random_device results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << rd() << " ";
    }
    std::cout << std::endl;

    std::cout << "std::mt19937 results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << gen() << " ";
    }
    std::cout << std::endl;

    std::cout << "std::uniform_int_distribution [1, 6], results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << distrib1(gen) << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::uniform_real_distribution [1.0, 2.0], results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << distrib2(gen) << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::binomial_distribution B(4, 0.5), results : ";
    for (int i = 0; i < 5; ++i) {
        std::cout << distrib3(gen) << ' ';
    }
    std::cout << std::endl;

    std::cout << "poisson_distribution P(4), results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << distrib4(gen) << ' ';
    }
    std::cout << std::endl;

    std::cout << "std::normal_distribution N(5, 2), results: ";
    for (int i = 0; i < 5; ++i) {
        std::cout << distrib5(gen) << ' ';
    }
    std::cout << std::endl;

    return 0;
}
