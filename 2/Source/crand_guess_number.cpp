
/* rand example: guess the number */

#include <iostream>
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

int main ()
{
  int iSecret, iGuess;

  /* initialize random seed: */
  std::srand (std::time(nullptr));

  /* generate secret number between 1 and 10: */
  iSecret = rand() % 10 + 1;

  do {
    std::cout << "Guess the number (1 to 10): ";
    std::cin >> iGuess;
    if (iSecret<iGuess)
        std::cout << "The secret number is lower\n";
    else if (iSecret>iGuess)
        std::cout << "The secret number is higher\n";
  } while (iSecret!=iGuess);

  std::cout <<"Congratulations!\n";

  return 0;
}

/*
static unsigned long int next = 1;

int rand()
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) % 32768;
}
*/
