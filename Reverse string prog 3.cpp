#include <iostream>
#include <string>
using namespace std;

// Function to reverse a string
string reverseString(const string& str) {
    string reversed = str; // Create a copy of the string
    int n = str.length();
    
    // Reverse the string using two-pointer approach
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        swap(reversed[i], reversed[j]); // Swap characters at positions i and j
    }
    
    return reversed;
}

int main() {
    string input;

    cout << "Enter a string: ";
    cin >> input; // Read input (single word)

    string reversed = reverseString(input);
    cout << "Reversed string: " << reversed << endl;

    return 0;
}
