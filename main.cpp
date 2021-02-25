#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <climits>
#include <iterator>
#include <unordered_map>

// bits/stdc++.h

#define endl "\n"
// #define DEBUG

using namespace std;


typedef struct Street
{
    int B, E, L;
    // frequency of the street in a path
    int freqInPath;
    string streetName;
    
    void read(){
        cin >> B >> E;
        cin >> streetName;
        cin >> L;
        freqInPath = 0;
    }
}street_t;

typedef struct Car
{
    int P;
    vector<string> path;

    void read()
    {
        cin >> P;
        for ( int i = 0; i < P; i++)
        {
            string streetName;
            cin >> streetName;
            path.push_back(streetName);
        }
    }

}car_t;

class Solution
{
public:


    // all intersections with one
    void approachA(vector<street_t>& streets, 
        unordered_map<int, unordered_map<string, int>>& intersections)
    {
        
        printIntersections(intersections);
    }

    // Adding new integer memeber to streets structure
    // integer: number of times that the street appears in a path
    // 
    void approachB( vector<car_t>& cars, vector<street_t>& streets,
        unordered_map<int, unordered_map<string, int>>& intersections )
    {
        unordered_map<string,int> freqMap;
        // 0: street is never in the path of a car
        // 1: street is at least once in the path of a car
        // 2: street is the MOST frequent street in the path of a car
        for ( const car_t& car : cars )
        {
            fillStreetFreqInPath(car.path, freqMap);
        }

        #ifdef DEBUG
        // printing the frequency map
        for ( auto& [streetName, freq] : freqMap )
        {
            cout << streetName << " : " << freq << endl;
        }
        #endif

        // Fill the intersections with 0
        for ( const street_t& street: streets )
        {
            intersections[street.E][street.streetName] = 0;
        }

        // write some intersections
        for ( auto& [id, umapStreetTime] : intersections )
        {
            pair<string, int> best {"", 0};
            for ( auto& [streetName, timeInGreen] : umapStreetTime )
            {
                if ( freqMap.find(streetName) != freqMap.end() )
                {
                    intersections[id][streetName] = 1;
                }

                 if ( (freqMap.find(streetName) != freqMap.end()) 
                    && freqMap[streetName] > best.second )
                {
                    best.first = streetName;
                    best.second = freqMap[streetName];
                }
            }
            // at this point, best contains the best pair
            // cout << best.first << " : " << best.second << endl;
            intersections[id][best.first] = 2;
        }

        // delete elements which count is 0
        // if intersections[id][best.first] == 0, delete entry


        printIntersections(intersections);
    }

private:

    // count the number of streets in the paths
    void fillStreetFreqInPath(vector<string> path, unordered_map<string,int>& umap)
    {
        for ( const string& streetName : path ) umap[streetName]++;
    }

    void printIntersections(
        unordered_map<int, unordered_map<string, int>>& intersections)
    {
        // traverse the map to print it
        cout << (int) intersections.size() << endl;
        for ( auto& [id, umapStreetTime] : intersections )
        {
            cout << id << endl;
            int size = (int) umapStreetTime.size();
            unordered_map<string,int> stNameTimeMap;
            // cout << (int) umapStreetTime.size() << endl;
            for ( auto& [streetName, timeInGreen] : umapStreetTime )
            {
                if (timeInGreen == 0 ) size--;
                else
                {
                    stNameTimeMap[streetName] = timeInGreen;
                }
                // cout << streetName << " " << timeInGreen << endl;
            }

            cout << stNameTimeMap.size() << endl;

            for ( auto& [streetName, timeInGreen] : stNameTimeMap )
            {
                cout << streetName << " " << timeInGreen << endl;
            }
        }
    }
};

int main ()
{
    freopen("inputs/b.txt", "r", stdin);
    freopen("outputs/b.txt", "w", stdout);

    int D, I, S, V, F;
    cin >> D >> I >> S >> V >> F;
    vector<street_t> streets(S);
    // [ id, map<streetNames,timeInGreen> ]
    unordered_map<int, unordered_map<string, int>> intersections;

    for ( street_t& street: streets )
    {
        street.read();
        #ifdef DEBUG
        cout << street.B << " " << street.E << " " \
        << street.streetName << " " << street.L << endl;
        #endif
    }

    vector<car_t> cars(V);
    for ( car_t& car: cars )
    {
        car.read();
        #ifdef DEBUG
        cout << car.P << " ";
        // std::copy(car.path.begin(), car.path.end(), std::ostream_iterator<char>(std::cout, " "));
        for ( const string& pathName: car.path ) cout << pathName << " ";
        cout << endl;
        #endif
    }


    Solution sol;
    // sol.approachA(intersections);
    sol.approachB(cars, streets, intersections);

    return 0;
}
