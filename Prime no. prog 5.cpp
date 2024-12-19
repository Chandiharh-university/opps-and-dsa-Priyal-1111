#include <iostream>
using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num <= 1) {
        return false; // Numbers less than or equal to 1 are not prime
    }
    
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return false; // Number is divisible by i, so it is not prime
        }
    }
    return true; // If no divisor is found, the number is prime
}

int main() {
    int number;

    cout << "Enter a positive integer: ";
    cin >> number;

    if (isPrime(number)) {
        cout << number << " is a prime number." << endl;
    } else {
        cout << number << " is not a prime number." << endl;
    }

    return 0;
}
