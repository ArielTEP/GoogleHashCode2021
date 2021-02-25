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
    string streetName;
    
    void read(){
        cin >> B >> E;
        cin >> streetName;
        cin >> L;
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
    void approachA(unordered_map<int, unordered_map<string, int>>& intersections)
    {
        printIntersections(intersections);
    }


    void solve( vector<car_t>& cars, vector<street_t>& streets,  
        unordered_map<int, unordered_map<string, int>>& intersections)
    {
        // TODO
    }

private:

    void printIntersections(
        unordered_map<int, unordered_map<string, int>>& intersections)
    {
        // traverse the map to print it
        cout << (int) intersections.size() << endl;
        for ( auto& [id, umapStreetTime] : intersections )
        {
            cout << id << endl;
            cout << (int) umapStreetTime.size() << endl;
            for ( auto& [streetName, timeInGreen] : umapStreetTime )
            {
                cout << streetName << " " << timeInGreen << endl;
            }
        }
    }
};

int main ()
{
    freopen("inputs/f.txt", "r", stdin);
    freopen("outputs/f.txt", "w", stdout);

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
        intersections[street.E][street.streetName] = 1;
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
    // t = 5
    sol.approachA(intersections);

    return 0;
}
