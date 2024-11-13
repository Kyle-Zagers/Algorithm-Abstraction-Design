#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
/* Solution to program 4
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
using namespace std;

std::tuple<int, int, std::vector<int>> program4(int n, int W, std::vector<int> heights, std::vector<int> widths){
    vector<int> opt(n+1, INT_MAX); // stores the optimal height for the first i paintings
    vector<int> platformStart(n+1, 0); // stores the starting index of the platform for the ith painting
    opt[0] = 0; // the optimal height for 0 paintings is 0

    for (int i = 1; i <= n; i++){ // loop through the paintings
        for (int j = i; j > 0; j--) { // loop through the paintings from i to 1
            int width = 0; // the total width of the paintings from j to i
            int maxHeight = 0; // the maximum height of the paintings from j to i

            for (int k = j; k <= i; k++) { // loop through the paintings from j to i
                width += widths[k-1]; // add the width of the kth painting
                if (width > W) { // if the width exceeds W, break
                    break;
                }
                maxHeight = max(maxHeight, heights[k-1]); // else update the maximum height
            }

            if (width <= W) { // if the width does not exceed W
                opt[i] = min(opt[i], opt[j-1] + maxHeight); // update the optimal height
                if (opt[i] == opt[j-1] + maxHeight) { // if the optimal height is updated, then update the starting index of the platform for the ith painting
                    platformStart[i] = j;
                }
            }
        }
    }

    int numPlatforms = 0;
    vector<int> platformSizes;
    // loop backwards through the platform starting indices by going to the starting index of the current platform - 1
    // skips paintings between platforms that may have incorrect starting indices
    for (int i = n; i > 0; i = platformStart[i] - 1) {
        numPlatforms++;
        platformSizes.insert(platformSizes.begin(), i - platformStart[i] + 1); // inserts at the beginning because we are going backwards
    }

    return std::make_tuple(numPlatforms, opt[n], platformSizes);
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
    auto result = program4(n, W, heights, widths);

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0; 
}