#include <iostream>
#include <random>
#include <iterator>
#include <list>

using namespace std;

void print_list(list<int>& l) {
    list <int> :: iterator it; 
    for (it = l.begin(); it != l.end(); it++) { 
    cout << (*it) << " ";
  }
    cout << endl;
}

void shuffle_list(list<int>& l) {
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

int main() {
    
    int num, list_size;
    std::list<int> sequence1;

    cout << "Enter number of elements in list\n>> ";
    cin >> list_size;
    
    cout << "Enter numbers: ";
    
    //insert numbers into list from cin
    for(int i = 0; i < list_size; i++) {
        cin >> num;
        sequence1.push_back(num);
    }
    
    cout << "Elements in list: " << endl;
    print_list(sequence1);

    // cout << "Deleting dublicates in list...\n";
    // sequence1.unique();

    // cout << "Elements into list: " << endl;
    // print_list(sequence1);
    cout << "Shuffle list...\n";
    shuffle_list(sequence1);

    cout << "Elements in list: " << endl;
    print_list(sequence1);
    
    return 0;
}