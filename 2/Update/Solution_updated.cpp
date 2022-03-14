#include <iostream>
#include <random>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>

using namespace std;

void print_vector(vector<int>& v) {
    if (v.size() > 0) {
        std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
        cout << "\n";
    } else 
        cout << "No elements in sequence\n";
}

void print_list(list<int>& l) {
    if (l.size() > 0) {
        std::copy(l.begin(), l.end(), std::ostream_iterator<int>(std::cout, " "));
        cout << "\n";
    } else 
        cout << "No elements in sequence\n";
}


void add_to_sequence(vector<int>& v, int input_size) {
    if (input_size > 0) {
        cout << "Enter Numbers: ";
        std::istream_iterator<int> iit (std::cin);
        v.emplace_back(*iit);
        for(int i = 1; i < input_size; i++) {
            iit++;
            v.emplace_back(*iit);
        }
    }
}

void removeDuplicates(std::vector<int>& v) {
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
}

bool isOdd(int i) {
    if (i % 2 != 0)
        return true;
    else
        return false;
}

bool isPrime(int n) { 
  	if(n < 2) return false;
	for(int i = 2; i * i <= n; i++) { 
    	if(n % i == 0)  return false; 
    } 
	return true; 
}

int computeSquare(int n) {
    return n * n;
}

int change_to_1(int n) { 
    n = 1;
    return n; 
    }

bool isNegative (int n) {
    if(n < 0) 
        return 1;
    return 0;
}

// Function to find the k'th largest element in an array
int findKthLargest(vector<int>& ints, int k)
{
    // Case: less than 3 elemnets
    if ((int)ints.size() < k) {
        exit(-1);
    }
 
    nth_element(ints.begin(), ints.begin() + k - 1, ints.end(), less<int>());
    return k - 1;
}



int main() {
    int vector_size;

    std::random_device rd;   // non-deterministic generator
    std::mt19937 gen(rd());  // to seed mersenne twister.
    std::uniform_int_distribution<> distrib10{1, 10};
    std::uniform_int_distribution<> distrib100{1, 100};
    auto generator10 = [&distrib10, &gen](){
        return distrib10(gen);
    };
    auto generator100 = [&distrib100, &gen](){
        return distrib100(gen);
    };

    //////////////////////////////////////// GENERATING SEQUENCE OF RANDOM INTEGERS
    cout << "1) Enter the size of sequence of random integers to be generated\n>> ";
    cin >> vector_size;
    cout << "Generating sequence of random integers with " << vector_size << " elements\n";
    vector<int> sequence1(vector_size);
    generate(sequence1.begin(), sequence1.end(), generator10);
    cout << "Elements in sequence: ";
    print_vector(sequence1);


    //////////////////////////////////////// ADDING NUMBERS TO SEQUENCE 
    cout << "\n2) Adding numbers to sequence\nHow many numbers do you want to add? \n>> ";
    int input_size;
    cin >> input_size;
    add_to_sequence(sequence1, input_size);
    if (input_size > 0) {
        cout << "New sequence: " << endl;
        print_vector(sequence1);
    }

    //////////////////////////////////////// DELETING DUPLICATES 
    removeDuplicates(sequence1);
    cout << "\n3) Unique elements in sequence: ";
    print_vector(sequence1);
    
    //////////////////////////////////////// RANDOM SHUFFLE
    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(sequence1), std::end(sequence1), rng);
    cout << "\n4) Shuffled Sequence: ";
    print_vector(sequence1);

    //////////////////////////////////////// COUNTING ODD NUMBERS
    if (sequence1.size() > 0) {
        cout << "\n5) Number of Odd Elements in Sequence: " << count_if(sequence1.begin(), sequence1.end(), isOdd) << endl;
    }

    //////////////////////////////////////// Find the max, min element
    if (sequence1.size() > 0) {
        cout << "\n6) Max Element = "<< *max_element(sequence1.begin(), sequence1.end()) << endl;
        cout << "   Min Element = "<< *min_element(sequence1.begin(), sequence1.end()) << endl;
    }

    //////////////////////////////////////// FIND PRIME
    
    if (sequence1.size() > 0) {
        cout << "\n7) Prime Number in Sequence: ";
        std::vector<int>::iterator it = std::find_if (sequence1.begin(), sequence1.end(), isPrime);
        if (it == sequence1.end()) {
            cout << "No Primes";
        } else {
            cout << *it << endl;
        }
    }

    //////////////////////////////////////// SQUARING ELEMENTS IN SEQUENCE
    cout << "\n8) Squaring elements in sequence: ";
    std::transform(sequence1.begin(), sequence1.end(), sequence1.begin(), computeSquare);
    print_vector(sequence1);
    
    //////////////////////////////////////// SEQUENCE 2
    cout << "\n9) Generating Sequence-2: ";
    vector<int> sequence2( (int)sequence1.size() );
    generate(sequence2.begin(), sequence2.end(), generator100);
    print_vector(sequence2);

    //////////////////////////////////////// SUM OF ELEMENTS IN SEQUENCE 2
    cout << "\n10) Sum of elements in sequence-2: " << accumulate(sequence2.begin(), sequence2.end(), 0) << endl;

    //////////////////////////////////////// Changing first elements to 1
    vector <int> :: iterator it = next(sequence2.begin(), distrib10(gen) % (int)sequence2.size());
    std::transform(sequence2.begin(), it, sequence2.begin(), change_to_1);
    cout << "\n11) Sequence-2 after changing some leading elements to 1: ";
    print_vector(sequence2);

    //////////////////////////////////////// SEQUENCE 3 AS DIFFERENCE BETWEEN SEQUENCE 1 AND SEQUENCE 2
    std::vector<int> sequence3( sequence1.size() );
    for (int i = 0; i < (int)sequence1.size(); i++) 
        sequence3[i] = sequence1[i] - sequence2[i];
    cout << "\n12) Sequence-3 as difference between sequence-1 and sequence-2: ";
    print_vector(sequence3);

    //////////////////////////////////////// REPLACING NEGATIVE ELEMENTS IN SEQUENCE 3 WITH 0
    replace_if (sequence3.begin(), sequence3.end(), isNegative, 0);
    cout << "\n13) Replacing negative elements in sequence-3 with 0: ";
    print_vector(sequence3);

    //////////////////////////////////////// DELETING 0 ELEMENTS
    sequence3.erase(std::remove(sequence3.begin(), sequence3.end(), 0), sequence3.end());
    cout << "\n14) Elements in sequence-3 after deleting all '0': ";
    print_vector(sequence3);

    //////////////////////////////////////// REVERSING SEQUENCE 3
    reverse(sequence3.begin(), sequence3.end());
    cout << "\n15) Elements in sequence-3 after reversing: ";
    print_vector(sequence3);

    //////////////////////////////////////// FIND TOP 3 ELEMENTS
    nth_element(sequence3.begin(), sequence3.begin() + 3 - 1, sequence3.end(), greater<int>());
    cout << "\n16) Top 3 elements in sequence 3: ";
    if ((int)sequence3.size() < 3) {
        cout << "not enough elements in sequence\n";
    } else {
        for (int i = 2; i >= 0; i--)
            cout << sequence3[i] << " "; 
        cout << endl;
    }

    //////////////////////////////////////// SORTING SEQUENCES 1 AND 2 
    sort(sequence1.begin(), sequence1.end());
    sort(sequence2.begin(), sequence2.end());
    cout << "\n17) Sorting sequences 1 and 2 :\nsequence 1: "; print_vector(sequence1);
    cout <<"sequence 2: "; print_vector(sequence2);

    //////////////////////////////////////// SEQUENCE 4 AS SEQUENCE 1 MERGED WITH SEQUENCE 2
    vector<int> sequence4(sequence1.size() + sequence2.size());
    merge(  sequence1.begin(),
            sequence1.end(),
            sequence2.begin(),
            sequence2.end(),
            sequence4.begin());
    cout << "\n18) Sequence 4 as sequence 1 merged with sequence 2: "; print_vector(sequence4);

    //////////////////////////////////////// RANGE FOR ORDERED INSERT OF NUMBER 1
    cout << "\n19) Range for ordered insert of 1: [" << lower_bound(sequence4.begin(), sequence4.end(), 1) - sequence4.begin()
    << ", " << upper_bound(sequence4.begin(), sequence4.end(), 1) - sequence4.begin() << "]\n";

    cout << "\n20) Printing all Sequences\n";
    cout << "Elements in sequence-1: "; print_vector(sequence1);
    cout << "Elements in sequence-2: "; print_vector(sequence2);
    cout << "Elements in sequence-3: "; print_vector(sequence3);
    cout << "Elements in sequence-4: "; print_vector(sequence4);

    return 0;
}