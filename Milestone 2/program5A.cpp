#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
/* Solution to program 5A
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
using namespace std;

int minCost(int i, int W, vector<int> heights, vector<int> widths, vector<int> &opt, vector<int> &platformStart){
    if (i == 0) { // if there are no paintings, return 0
        return 0;
    }

    if (opt[i] != -1) { // if the optimal height for the first i paintings is already computed, return it
        return opt[i];
    }

    int width = 0; // the total width of the paintings from j to i
    int maxHeight = 0; // the maximum height of the paintings from j to i
    int currentMinCost = INT_MAX; // the current minimum cost

    for (int j = i; j > 0; j--) { // loop through the paintings from i to 1
        width += widths[j-1]; // add the width of the jth painting

        if (width > W) { // if the width exceeds W, break
            break;
        }

        maxHeight = max(maxHeight, heights[j-1]); // else update the maximum height
        
        int prevCost = minCost(j-1, W, heights, widths, opt, platformStart); // compute the optimal height for the first j-1 paintings
        if (prevCost + maxHeight < currentMinCost) { // if this platform is better than the current optimal height, update the optimal height and the starting index of the platform for the ith painting
            currentMinCost = prevCost + maxHeight;
            platformStart[i] = j;
        }
    }

    opt[i] = currentMinCost; // store the optimal height for the first i paintings
    return opt[i];
}

std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    vector<int> opt(n+1, -1); // stores the optimal height for the first i paintings, initialized to -1 to represent not yet computed
    vector<int> platformStart(n+1, 0); // stores the starting index of the platform for the ith painting

    int result = minCost(n, W, heights, widths, opt, platformStart); // compute the optimal height for the first n paintings (solution)

    int numPlatforms = 0;
    vector<int> platformSizes;
    // loop backwards through the platform starting indices by going to the starting index of the current platform - 1
    // skips paintings between platforms that may have incorrect starting indices
    for (int i = n; i > 0; i = platformStart[i] - 1) {
        numPlatforms++;
        platformSizes.insert(platformSizes.begin(), i - platformStart[i] + 1); // inserts at the beginning because we are going backwards
    }

    return std::make_tuple(numPlatforms, result, platformSizes);
}
int main(){
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);
    for(int i = 0; i < n; i++){
        std::cin >> heights[i];
    }
    for(int i = 0; i < n; i++){
        std::cin >> widths[i];
    }
    auto result = program5A(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}