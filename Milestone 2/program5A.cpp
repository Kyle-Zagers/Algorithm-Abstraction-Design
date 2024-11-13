#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
/* Solution to program 5A
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
using namespace std;

int minCost(int i, int W, vector<int> heights, vector<int> widths, vector<int> &opt, vector<int> &platformStart){
    if (i == 0) {
        return 0;
    }

    if (opt[i] != -1) {
        return opt[i];
    }

    int width = 0;
    int maxHeight = 0;
    int currentMinCost = INT_MAX;

    for (int j = i; j > 0; j--) {
        width += widths[j-1];

        if (width > W) {
            break;
        }

        maxHeight = max(maxHeight, heights[j-1]);
        
        int prevCost = minCost(j-1, W, heights, widths, opt, platformStart);
        if (prevCost + maxHeight < currentMinCost) {
            currentMinCost = prevCost + maxHeight;
            platformStart[i] = j;
        }
    }

    opt[i] = currentMinCost;
    return opt[i];
}

std::tuple<int, int, std::vector<int>> program5A(int n, int W, std::vector<int> heights, std::vector<int> widths){
    vector<int> opt(n+1, -1);
    vector<int> platformStart(n+1, 0);

    int result = minCost(n, W, heights, widths, opt, platformStart);

    int numPlatforms = 0;
    vector<int> platformSizes;

    for(int i = n; i > 0; i = platformStart[i]-1){
        numPlatforms++;
        platformSizes.push_back(i - platformStart[i] + 1);
    }
    reverse(platformSizes.begin(), platformSizes.end());

    return std::make_tuple(numPlatforms, result, platformSizes);
//    return std::make_tuple(0, 0, std::vector<int>()); // replace with your own result.
    // return std::make_tuple(n, 0, heights);
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