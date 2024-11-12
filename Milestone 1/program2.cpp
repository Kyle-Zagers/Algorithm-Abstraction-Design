#include <iostream>
#include <vector>
#include <tuple>
#include <chrono>
/* Solution to program 2
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total height, and the number of paintings on each platform
*/
std::tuple<int, int, std::vector<int>> program2(int n, int W, std::vector<int> heights, std::vector<int> widths){
    
    std::vector<int> vtr;   // final vector
    if (n == 0)
    {
        return std::make_tuple(0, 0, vtr);
    }
    int numPlatforms = 2;   // total number of platforms
    int optHeight = heights[0]; // optimal total height, initialized to first painting
    int width = 0;  // used to calculate total width of paintings within a platform
    int paintCount = 0; // count for number of paintings on current platforms
    std::vector<int> vtr1;   // vector containing number of paintings on a platform i from first loop
    std::vector<int> vtr2;   // vector containing number of paintings on a platform i from second loop
    int totalWidth = 0;

    // Used to determine whether local minumum should be placed on the platform before, after, or on a new platform
    int widthBeforeMinimum = 0;
    int widthAfterMinimum = 0;
    int minIndex;
    
    int i = 0;
    while (heights[i] >= heights[i+1])  // stops at local minimum
    {
        totalWidth += widths[i];
        width += widths[i];
        if (width > W)  // checks to see if it exceeds max width
        {
            // if exceeds, put painting on next platform
            width = widths[i];
            optHeight += heights[i];
            numPlatforms++;
            vtr1.push_back(paintCount);
            paintCount = 1;
        }
        else
        {
            paintCount++; // if width does not exceed, add painting to that platform
        }

        i++;
    }
    vtr1.push_back(paintCount); // push last platform paintings count
    widthBeforeMinimum = width; // keep track of width from last platform


    // reset all variables used in loop
    width = 0;
    minIndex = i;   // local minimum
    i = n - 1;
    paintCount = 0;


    optHeight += heights[i];
    while (heights[i] >= heights[i-1])
    {
        totalWidth += widths[i];
        width += widths[i];
        if (width > W)  // checks to see if it exceeds max width
        {
            // if exceeds, put painting on next platform
            width = widths[i];
            optHeight += heights[i];
            numPlatforms++;
            vtr2.push_back(paintCount);
            paintCount = 1;
        }
        else
        {
            paintCount++; // if width does not exceed, add painting to that platform
        }

        i--;
    }
    vtr2.push_back(paintCount); // push back last platform painting count
    widthAfterMinimum = width;  // keep track of width of last platform

    // case if all can fit on one platform
    if (totalWidth + widths[minIndex] <= W)
    {
        numPlatforms = 1;
        optHeight = std::max(heights[0], heights[n-1]);
        vtr.push_back(n);
    }
    else
    {
        // check if local minimum can fit in the platforms before or after, if not create new platform
        if (widthBeforeMinimum + widths[minIndex] <= W)
        {
            vtr1[vtr1.size()-1]++;
        }
        else if (widthAfterMinimum + widths[minIndex] <= W)
        {
            vtr2[vtr2.size()-1]++;
        }
        else
        {
            optHeight += heights[minIndex];
            vtr1.push_back(1);
            numPlatforms++;
        }

        vtr = vtr1;
        // append second half vector to full vector, vtr2 is reverse
        for (int j = vtr2.size()-1; j >= 0; j--)
        {
            vtr.push_back(vtr2[j]);
        }
    }

    
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
    auto result = program2(n, W, heights, widths);
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