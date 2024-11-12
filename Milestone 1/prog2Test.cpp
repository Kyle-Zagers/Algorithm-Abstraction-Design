#include <iostream>
#include <vector>
#include <algorithm> // for sort
#include <random>    // for random number generation
#include <ctime>     // for seeding the random number generator
#include <fstream>


using namespace std;

void saveTest(int n, int w) {
    ofstream file("test.txt");
    file << n << endl;
    file << w << endl;

    // Create a random number generator
    std::mt19937 rng(static_cast<unsigned>(time(0)));  // Seed the generator with current time
    std::uniform_int_distribution<int> dist(1, 12000);  // Random numbers between 1 and 1000

    std::vector<int> numbers;

    // Generate unique random numbers
    while (numbers.size() < n) {
        int num = dist(rng);
        // Ensure uniqueness
        if (std::find(numbers.begin(), numbers.end(), num) == numbers.end()) {
            numbers.push_back(num);
        }
    }

    // Sort the first half in decreasing order
    int midpoint = n / 2;
    std::sort(numbers.begin(), numbers.begin() + midpoint, std::greater<int>());

    // Sort the second half in increasing order
    std::sort(numbers.begin() + midpoint, numbers.end());

    // Print the numbers
    for (int i = 0; i < n; ++i) {
        file << numbers[i] << endl;
    }

    for (int i = 0; i < n; i++) {
        file << rand() % w << endl;
    }
}


int main() {
    saveTest(5000, 88);
}