#include <iostream>
#include <random>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

void print_list(list<int>& l) {
    if (l.size() > 0) {
        list <int> :: iterator it; 
        for (it = l.begin(); it != l.end(); it++) { 
            cout << (*it) << " ";
        }
        cout << endl;
    } else 
        cout << "No elements in sequence\n";
}

void generate_random_list(list<int>& l, int list_size, int max_num) {
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> distrib1{1, max_num};
    for(int i = 0; i < list_size; i++) 
        l.push_back(distrib1(gen));
}

void input_list(list<int>& l) {
    int num, list_size;
    cout << "Enter number of elements in sequence\n>> ";
    cin >> list_size;
    
    if (list_size > 0)
        cout << "Enter numbers: ";
    
    //insert numbers into list from cin
    for(int i = 0; i < list_size; i++) {
        cin >> num;
        l.push_back(num);
    }
}

void add_to_list(list<int>& l) {
    int num, input_size;
    cout << "Adding numbers to sequence\nHow many numbers do you want to add? \n>> ";
    cin >> input_size;
    if (input_size > 0)
        cout << "Enter Numbers: ";
    for(int i = 0; i < input_size; i++) {
        cin >> num;
        l.push_back(num);
    }
}

void shuffle_list(list<int>& l) {
    //  Fisher–Yates shuffle
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> distrib1{1, (int)l.size()};
    list <int> :: iterator it = l.end(); it--; 
    int j;
    for (int i = l.size() - 1; i > 0; i--, it--) { 
        j = distrib1(gen) % (i + 1);
        int temp = (*it);
        (*it) = (*std::next(l.begin(), j));
        (*std::next(l.begin(), j)) = temp;
    }
}

unsigned int count_odd(list<int>& l) {
    unsigned int res = 0;
    list <int> :: iterator it; 
    for (it = l.begin(); it != l.end(); it++) { 
        if ((*it) % 2 == 1) 
            res++;
    }
    return res;
}

int max_element(list <int>& l) {
    int max = (*l.begin());
    list <int> :: iterator it; 
    for (it = l.begin(); it != l.end(); it++) { 
        if ((*it) > max) 
            max = (*it); 
    }
    return max;
}

int min_element(list <int>& l) {
    int min = (*l.begin());
    list <int> :: iterator it; 
    for (it = l.begin(); it != l.end(); it++) { 
        if ((*it) < min) 
            min = (*it); 
    }
    return min;
}

int number_is_prime(int number) {
  for (int i = 2; i < number; i++) {
    if (number % i == 0) {
      return 0;
    }
    if ((i == number) || (i > sqrt(number))) {
      return 1;
    }
  }
  return 1;
}

void print3largest(list<int>& l)
{
    int first, second, third;
 
    // There should be atleast three elements
    if (l.size() < 3)
    {
        cout << " Sequence has less than 3 elements ";
        return;
    }
 
    third = first = second = -10000;
    for(auto it = l.begin(); it != l.end(); it++) {
         
        // If current element is
        // greater than first
        if ((*it) > first) {
            third = second;
            second = first;
            first = (*it);
        }
 
        // If (*it) is in between first
        // and second then update second
        else if ((*it) > second) {
            third = second;
            second = (*it);
        } else if ((*it) > third)
            third = (*it);
    }
 
    cout << "Three largest elements are "
        << first << " " << second << " "
        << third << endl;
}
 

int main() {
    std::list<int> sequence1, sequence2, sequence3, sequence4;
    int list_size;
    cout << "Enter the size of sequence of random integers to be generated\n>> ";
    cin >> list_size;
    cout << "Generating sequence of random integers with " << list_size << " elements\n";
    generate_random_list(sequence1, list_size, 10);
    cout << "Elements in sequence: " << endl;
    print_list(sequence1);

    add_to_list(sequence1);
    cout << "New sequence: " << endl;
    print_list(sequence1);

   
    sequence1.sort();
    sequence1.unique();
    cout << "\n--------------Unique elements in sequence: " << endl;
    print_list(sequence1);
    

    cout << "\n--------------Shuffle sequence...\n";
    shuffle_list(sequence1);
    cout << "Sequence after shuffling: " << endl;
    print_list(sequence1);

    
    cout << "\nNumber of odd elements in sequence: " << count_odd(sequence1) << endl;

    cout << "Max element in sequence: " << max_element(sequence1) << endl;
    cout << "Min element in sequence: " << min_element(sequence1) << endl;

    //Prime Number Search
    cout << "\n--------------Searching for prime number\n";
    int prime_found = 0;
    list <int> :: iterator it = sequence1.begin();
    while (prime_found == 0 && it != sequence1.end()) {
        if (number_is_prime(*it) == 1) {
            prime_found = 1;
            cout << (*it) << " is prime number in sequence\n";
        }
        it++;
    }

    cout << "\n--------------Squaring all elemnts in sequence\n";
    for (it = sequence1.begin(); it != sequence1.end(); it++) { 
            (*it) = (*it) * (*it);
    }
    cout << "Elements in sequence after squaring: " << endl;
    print_list(sequence1);


    //////////////////////////////////////// SEQUENCE 2
    cout << "\n//////////////////////////////////////// SEQUENCE 2\n";
    cout << "Enter the length of sequence-2 of random integers to be generated\n>> ";
    cin >> list_size;
    cout << "Generating sequence of random integers with " << list_size << " elements\n";
    generate_random_list(sequence2, list_size, 1000);
    cout << "Elements in sequence-2: " << endl;
    print_list(sequence2);

    //Find sum of elements in sequence-2
    long long int sum = 0;
    for (it = sequence2.begin(); it != sequence2.end(); it++)
        sum += (*it);
    cout << "\n--------------Sum of elements in sequence-2: "<< sum << endl;

    //Changing some leading elements in sequence-2 to 1
    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> distrib1{1, (int)sequence2.size()};
    int num_elements_to_change_to_1 = distrib1(gen);
    cout << "\n--------------Changing " << num_elements_to_change_to_1 << " first elements of sequence-2 to 1\n";
    for (it = sequence2.begin(); it != next(sequence2.begin(), num_elements_to_change_to_1); it++)
        (*it) = 1;
    cout << "Elements in sequence after change: " << endl;
    print_list(sequence2);

    it = sequence1.begin();
    list <int> :: iterator it2 = sequence2.begin(); 
    //////////////////////////////////////// SEQUENCE 3
    cout << "\n--------------Generating sequence-3 as difference between sequence-1 and sequence-2\n";
    if (sequence1.size() > sequence2.size()) {
        for (int i = 0; i < sequence2.size(); i++) {
            sequence3.push_back((*it) - (*it2));
            it++; it2++;
        }
        for (int i = 0; i < sequence1.size() - sequence2.size(); i++) {
            sequence3.push_back((*it));
            it++;
        }
    } else {
        for (int i = 0; i < sequence1.size(); i++) {
            sequence3.push_back((*it) - (*it2));
            it++; it2++;
        }
        for (int i = 0; i < sequence2.size() - sequence1.size(); i++) {
            sequence3.push_back(-(*it2));
            it2++;
        }
    }
    cout << "Elements in sequence-3: " << endl;
    print_list(sequence3);

//////////////////////////////////////// Changing every negative element of SEQUENCE 3 to 0
    cout << "\n--------------Changing negative elements of sequence-3 to 0\n";
    for (it = sequence3.begin(); it != sequence3.end(); it++) { 
            if ((*it) < 0)
                (*it) = 0;
        }
    cout << "Elements in sequence-3: " << endl;
    print_list(sequence3);

    sequence3.remove(0);
    cout << "\n--------------Elements in sequence-3 after deleting all '0':" << endl;
    print_list(sequence3);

    sequence3.reverse();
    cout << "\n--------------Elements in sequence-3 after reversing:" << endl;
    print_list(sequence3);

    //Top 3 elements in sequence-3
    cout << "\n--------------Searching for top 3 elements in sequence-3\n";
    print3largest(sequence3);

    //Sorting sequence-1 and sequence-2 
    cout << "\n--------------Sorting elements in sequence-1 and sequence-2" << endl;
    sequence1.sort();
    sequence2.sort();
    cout << "Elements after sorting:" << endl;
    cout << "sequence 1: "; print_list(sequence1);
    cout << "sequence 2: "; print_list(sequence2);

    //////////////////////////////////////// SEQUENCE 4
    cout << "\n--------------Generating sequence-4 by merging sequence-1 and sequence-2" << endl; 
    for (it = sequence1.begin(); it != sequence1.end(); it++) { 
            sequence4.push_back(*it);
    }
    sequence4.merge(sequence2);
    cout << "Elements in sequence-4:" << endl;
    print_list(sequence4);

    //////////////////////////////////////// Defining Positions to insert '1'
    cout << "\n--------------Defining Positions to insert '1'" << endl; 
    int starting_pos = 1, ending_pos = 1;
    for (it = sequence4.begin(); it != sequence4.end(); it++) {
        if (*it < 1) {
            starting_pos++;
        }
        if (*it <= 1) {
            ending_pos++;
        }
    }
    cout << "'1' can be inserted in range: ["<< starting_pos << ", " << ending_pos << "]\n";

    //Printing all Sequences
    cout << "Elements in sequence-1: "; print_list(sequence1);
    cout << "Elements in sequence-2: "; print_list(sequence2);
    cout << "Elements in sequence-3: "; print_list(sequence3);
    cout << "Elements in sequence-4: "; print_list(sequence4);



    
    return 0;
}