#include <iostream>
#include <vector>
using namespace std;

/*

as we move closer to the center increase chance of certain blocks generating

BLOCKS :

    ? BORDER
    ~ WATER
     * SAND
    # PLAINS
    ¥ FOREST
    ^ MOUNTAIN    

A border is pre defined, we have a border and then atleast 4 spaces in we have water
Once we move past water, each "circle" we move closer twoards the middle, the chance of certain blocks spawning increases

we can define a cube shaped map as having "rings" or consisting of many squares

Example : a 3x3 map has 2 rings, 1 outer ring and 1 center
X X X
X # X  <--- CENTER RING IN ROW 2 = 3/2 = 1,5^ = 2
X X X

Example : a 9x9 map has 5 rings
X X X X X X X X X   
X # # # # # # # X   
X # X X X X X # X   
X # X # # # X # X   
X # X # X # X # X   <--- CENTER RING IN ROW 5 = 9/2 = 4.5^ = 5
X # X # # # X # X   
X # X X X X X # X   
X # # # # # # # X   
X X X X X X X X X   

rings can be counted by dividing the map heigth by 2 if number is even, if number is odd then round up (9/2 = 4.5^ = 5)

By knowing how many rings a map contains, we can create a way to calculate the needed probabilities of different blocks generating
This method initially only creates a single island on the map, but we can also split the map into multiple cubes to get multiple islands

WATER

Water has 100% probability generating next to a border
Water has 80% probability generating next to land (LAND NEEDS TO BE GENERATED)
Water has 60 then 40, then 20, then bottoms out at 5% generating inside land

SAND

Sand has 0 probability generating next to a border
For each block outside border we increase chances of sand spawning by 5%+(5%*howmany_blocks_away_from_border)
If there is sand in an adjecent block, each time this happens, we decrease the chance
If sand is x blocks away from border, set probability to 0, so that we don't get sand inside the island, only on the edges

PLAINS

Once we have triggered the probability of sand to 0, set the probability of plains to 100%
For each block past the first plains block we increase chances of forest spawning by 10%+(5%*howmany_blocks_away_from_border?)
The closer we move to the center drastically decrease the chance of plains spawning (at least 1-8 circles need to be left for a mountain(relative to map size))

FOREST

Once plains chance is below a certain number, increase chance of forest spawning
Drastically increase chance of forest spawning, until we reach the reserved circles in the middle of the suqare for mountains
Once we are 1-8 circles outside the reserved for mountains, decrease by each cirlce the chance of forests spawning to 50% if 1 or 2, 33% if 3, 25% if 4, 20% if 5, 15% if 6, ect

MOUNTAIN

Once we have reached the reserved circles for mountains, set forest chance to 0 and mountain to 100%


Generate the map in a spiral, this way you have some way of dynamically reading what is happening

14x11 MAP BEING GENERATED, 1 SPIRAL IS NEEDED
A map starts out with filler blocks 'X'
WHEN GENERATING A MAP :

Find the bottom left corner (fill with water)
Go up until you hit the end (fill with water)
Go right until you hit the end (fill with water)
Go down until you hit the end (fill with water)
Go down left until you hit the first water block (fill with water)

repeat until relative to map size, this has been done x times
once this has been done x times, start increasing sand chance
todo : figure out how to follow up with other blocks



X X X X X X X X X X X X X X 
# # # # # # # # # # # # # X
# X X X X X X X X X X X # X
# X # # # # # # # # # X # X
# X # X X X X X X X # X # X
# X # X # # # # # X # X # X
# X # X # X X X X X # X # X
# X # X # # # # # # # X # X
# X # X X X X X X X X X # X
# X # # # # # # # # # # # X
# X X X X X X X X X X X X X




*/


vector<vector<char>> GenerateMapWithBorder(int map_w, int map_h, int border_w) {
    std::vector<std::vector<char>> map;
    if (border_w < 1) border_w = 1;

    map.resize(map_h, std::vector<char>(map_w, 'x'));

    // Add border to map
    for (int k = 0; k < border_w; k++) {
        int i = k;
        int j = k;
        int end_i = map_h - k;
        int end_j = map_w - k;

        if (i >= end_i || j >= end_j) {
            break;}

        // Fill the top row
        for (; j < end_j; ++j) {
            map[i][j] = 'B';}
        j--;

        // Fill the right column
        for (i = k + 1; i < end_i; ++i) {
            map[i][j] = 'B';}
        i--;

        // Fill the bottom row
        for (j = end_j - 2; j >= k; --j) {
            map[i][j] = 'B';}
        j++;

        // Fill the left column
        for (i = end_i - 2; i > k; --i) {
            map[i][j] = 'B';}
    }

    return map;
}


void OutputMapWithBorder(const vector<vector<char>>& map) {
    int map_w = 0, map_h = 0;

    if (!map.empty()) {
        map_h = static_cast<int>(map.size()); // Height of the map (number of rows)
        // Width of the map (number of columns in the first row)
        if (!map[0].empty()) {
            map_w = static_cast<int>(map[0].size());
        }
    }
    // Output the map dimensions
    cout << "Map Width: " << map_w << endl;
    cout << "Map Height: " << map_h << endl;

    // Output the map content with borders
    for (int i = 0; i < map_w - 10; i++) {
        cout << '-';
    }
    cout << "MAP START" << endl << endl;

    for (const auto& row : map) {
        for (char cell : row) {
            cout << cell << "";
        }
        cout << endl;
    }
    cout << endl;

    for (int i = 0; i < map_w - 8; i++) {
        cout << '-';
    }
    cout << "MAP END" << std::endl;
}


int main(){

    
    vector<vector<char>> map = GenerateMapWithBorder(50,20,1); // generate a map 50 wide, 20 tall and 1 border

    OutputMapWithBorder(map);

    cout << "Press Enter to continue . . . ";
    cin.get();

    return 0;

}