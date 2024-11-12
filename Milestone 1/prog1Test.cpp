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
    std::uniform_int_distribution<int> dist(1, 14000);

    std::vector<int> numbers;

    // Generate unique random numbers
    while (numbers.size() < n) {
        int num = dist(rng);
        // Ensure uniqueness
        if (std::find(numbers.begin(), numbers.end(), num) == numbers.end()) {
            numbers.push_back(num);
        }
    }

    // Sort the numbers in decreasing order
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());

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