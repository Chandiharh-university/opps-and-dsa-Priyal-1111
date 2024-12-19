#include <iostream>
#include <string>
using namespace std;

// Function to check if a string is a palindrome
bool isPalindrome(const string& str) {
    int start = 0;               // Start pointer
    int end = str.length() - 1;  // End pointer

    while (start < end) {
        if (str[start] != str[end]) {
            return false; // Characters don't match, not a palindrome
        }
        start++;
        end--;
    }
    return true; // If all characters match, it's a palindrome
}

int main() {
    string input;

    cout << "Enter a string: ";
    cin >> input;

    if (isPalindrome(input)) {
        cout << input << " is a palindrome." << endl;
    } else {
        cout << input << " is not a palindrome." << endl;
    }

    return 0;
}
