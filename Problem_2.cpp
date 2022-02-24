#include <iostream>
#include <random>
#include <set>

//Random string generator
// const std::string CHARACTERS = "abcdefghijklmnopqrstuvwxyz";
// std::string random_string(std::size_t length)
// {
//     std::random_device random_device;
//     std::mt19937 generator(random_device());
//     std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

//     std::string random_string;

//     for (std::size_t i = 0; i < length; ++i)
//     {
//         random_string += CHARACTERS[distribution(generator)];
//     }

//     return random_string;
// }

///////////// Hash functions
unsigned int RSHash(const char* str, unsigned int length)
{
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = hash * a + (*str);
      a    = a * b;
   }

   return hash;
}

unsigned int JSHash(const char* str, unsigned int length)
{
   unsigned int hash = 1315423911;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int PJWHash(const char* str, unsigned int length)
{
   const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
   const unsigned int ThreeQuarters     = (unsigned int)((BitsInUnsignedInt  * 3) / 4);
   const unsigned int OneEighth         = (unsigned int)(BitsInUnsignedInt / 8);
   const unsigned int HighBits          =
                      (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
   unsigned int hash = 0;
   unsigned int test = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << OneEighth) + (*str);

      if ((test = hash & HighBits) != 0)
      {
         hash = (( hash ^ (test >> ThreeQuarters)) & (~HighBits));
      }
   }

   return hash;
}

unsigned int ELFHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int x    = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash << 4) + (*str);

      if ((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }

      hash &= ~x;
   }

   return hash;
}

unsigned int BKDRHash(const char* str, unsigned int length)
{
   unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (hash * seed) + (*str);
   }

   return hash;
}

unsigned int SDBMHash(const char* str, unsigned int length)
{
   unsigned int hash = 0;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = (*str) + (hash << 6) + (hash << 16) - hash;
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length)
{
   unsigned int hash = 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int DEKHash(const char* str, unsigned int length)
{
   unsigned int hash = length;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}







int main() {
    std::set<unsigned int> set_hash;
    //int Number_of_lines;
    //std::cin >> Number_of_lines;
    int choice; 
    std::cout << "Enter which function to use (Enter number)\n1 - RSHash\n2 - JSHash\n3 - PJWHash\n4 - ELFHash\n5 - BKDRHash\n6 - SDBMHash\n7 - DJBHash\n8 - DEKHash\n9 - APHash\n> "; 
    std::cin >> choice;
    char a[6];
    for (int i1 = 97; i1 <= 122; i1++)
        for (int i2 = 97; i2 <= 122; i2++)
            for (int i3 = 97; i3 <= 122; i3++)
                for (int i4 = 97; i4 <= 122; i4++)
                    for (int i5 = 97; i5 <= 122; i5++) {
                            a[0] = i1;
                            a[1] = i2;
                            a[2] = i3;
                            a[3] = i4;
                            a[4] = i5;
                            switch (choice)
                            {
                            case 1:
                                set_hash.insert(RSHash(a, 5));
                                break;
                            case 2:
                                set_hash.insert(JSHash(a, 5));
                                break;
                            case 3:
                                set_hash.insert(PJWHash(a, 5));
                                break;
                            case 4:
                                set_hash.insert(ELFHash(a, 5));
                                break;
                            case 5:
                                set_hash.insert(BKDRHash(a, 5));
                                break;
                            case 6:
                                set_hash.insert(SDBMHash(a, 5));
                                break;
                            case 7:
                                set_hash.insert(DJBHash(a, 5));
                                break;
                            case 8:
                                set_hash.insert(DEKHash(a, 5));
                                break;
                            case 9:
                                set_hash.insert(APHash(a, 5));
                                break;
                            default:
                                break;
                            }
                        }

    // set1.insert(RSHash("tailgate", 8));
    // set1.insert(RSHash("roundup", 7));

    std::cout << "Number of elements if set of hashes: " << set_hash.size() << "\n";
    std::cout << "Number of collisions: " << (26 * 26 * 26 * 26 * 26) - set_hash.size() << "\n";



    return 0;
}