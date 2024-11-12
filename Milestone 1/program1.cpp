#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
/* Solution to program 1
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program1(int n, int W, std::vector<int> heights, std::vector<int> widths){
    // MY CODE
    std::vector<int> vtr;   // vector containing number of paintings on a platform i
    if (n == 0)
    {
        return std::make_tuple(0, 0, vtr);
    }
    int numPlatforms = 1;   // total number of platforms
    int optHeight = heights[0]; // optimal total height, initialized to first painting
    int width = 0;  // used to calculate total width of paintings within a platform
    int paintCount = 0; // count for number of paintings on current platforms

    

    for (int i=0; i < n; i++)
    {
        width += widths[i]; // add width of current painting
        if (width > W)  // checks to see if it exceeds max width
        {
            // if exceeds, put painting on next platform
            width = widths[i];
            optHeight += heights[i];
            numPlatforms++;
            vtr.push_back(paintCount);
            paintCount = 1;
        }
        else
        {
            paintCount++; // if width does not exceed, add painting to that platform
        }
    }

    vtr.push_back(paintCount);  // for number of paintings on last platform
    return std::make_tuple(numPlatforms, optHeight, vtr); // return tuple
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
    auto start = std::chrono::high_resolution_clock::now();
    auto result = program1(n, W, heights, widths);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++){
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    std::cout << "Duration: " << duration << " microseconds" << std::endl;
    return 0; 
}