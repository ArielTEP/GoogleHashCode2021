#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include <climits>
#include <iterator>

// bits/stdc++.h

#define endl "\n"
#define DEBUG

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

int main ()
{
    freopen("inputs/a.txt", "r", stdin);
    freopen("outputs/output.txt", "w", stdout);

    int D, I, S, V, F;
    cin >> D >> I >> S >> V >> F;
    vector<street_t> streets(S);
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

    return 0;
}
