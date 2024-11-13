#include <iostream>
#include <vector>
#include <tuple>
#include <cmath>
#include <bitset>
#include <climits>
/* Solution to program 3
* @param n the number of paintings
* @param W the maximum width of the platform
* @param heights the heights of the paintings
* @param widths the widths of the paintings
* @return a tuple containing the number of platforms used, the optimal total
height, and the number of paintings on each platform
*/

using namespace std;



std::tuple<int, int, std::vector<int>> program3(int n, int W, std::vector<int>heights, std::vector<int> widths)
{
    vector<string> vtr(pow(2,n-1));
    // LOOP IS O(n * 2^(n-1))
    // CREATES EVERY POSSIBLE PAINTING ROUTE IN BINARY
    for (int i = 0; i < (1 << n-1); i++)
    {
        bitset<32> b(i);
        vtr[i] = b.to_string().substr(32-n+1);
    }

    int minimumHeight = INT_MAX;
    int numOfPlatforms = 0;
    vector<int> platformSizes;
    // RUN THROUGH EVERY COMBINATION OF ROUTES
    for (int k=0; k<vtr.size(); k++)
    {
        int width = widths[0];
        int totalHeight = 0;
        int currentPlatformHeight = heights[0];
        bool broke = false;
        int holdPlatformCount = 1;
        string x = vtr[k];
        vector<int> holdPlatformSizes;
        int hold = 1;
        
        // RUN THROUGH EACH BINARY, 1 MEANS ADD TO CURRENT PLATFORM, 0 MEANS ADD TO NEW PLATFORM
        for (int i=0; i<x.length(); i++)
        {
            if (x[i] == '1')
            {
                width += widths[i+1];
                if (width > W)
                {
                    broke = true; // TO NOTIFY THAT ROUTE HAS A PLATFORM WHERE WIDTH OF PAINTINGS EXCEEDS W
                    break;
                }
                hold++;
                currentPlatformHeight = max(heights[i+1], currentPlatformHeight);
            }
            else
            {
                holdPlatformSizes.push_back(hold);
                hold = 1;
                totalHeight += currentPlatformHeight;
                currentPlatformHeight = heights[i+1];
                width = widths[i+1];
                holdPlatformCount++;
            }
        }
        totalHeight += currentPlatformHeight;
        holdPlatformSizes.push_back(hold);

        if (!broke) 
        {
            // IF THIS WAS A MORE OPTIMAL SELECTION, UPDATE
            if (totalHeight < minimumHeight)
            {
                minimumHeight = totalHeight;
                numOfPlatforms = holdPlatformCount;
                platformSizes = holdPlatformSizes;
            }
        }
    }

    return make_tuple(numOfPlatforms, minimumHeight, platformSizes);
}

int main()
{
    int n, W;
    std::cin >> n >> W;
    std::vector<int> heights(n);
    std::vector<int> widths(n);
    for(int i = 0; i < n; i++)
    {
        std::cin >> heights[i];
    }
    for(int i = 0; i < n; i++)
    {
        std::cin >> widths[i];
    }
    auto result = program3(n, W, heights, widths); 
    std::cout << std::get<0>(result) << std::endl;
    std::cout << std::get<1>(result) << std::endl;
    for(int i = 0; i < std::get<0>(result); i++)
    {
        std::cout << std::get<2>(result)[i] << std::endl;
    }
    return 0;
}
