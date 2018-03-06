#include <bits/stdc++.h>

using std::cout;
using std::endl;
using std::vector;

struct Ride{
    int x1, x2;
    int y1, y2;
    int s, f;
    int id;

    static int counter;

    Ride() = default;

    Ride(int x1, int y1, int x2, int y2, int s, int f):
            x1(x1), x2(x2), y1(y1), y2(y2), s(s), f(f){

    }

    bool operator<(const Ride & o){
        return this->f < o.f;
    }

    friend std::istream& operator>>(std::istream &is, Ride & r){
        is>>r.x1>>r.y1>>r.x2>>r.y2>>r.s>>r.f;
        r.id = counter++;
        return is;
    }

    friend std::ostream& operator<<(std::ostream &os, Ride & r){
        int dist  = std::abs(r.y1 - r.y2) + std::abs(r.x1 -  r.x2);
        os<<"dist = "<<dist<<" delta time: "<<(r.f-r.s);
        return os;
    }
};

int Ride::counter = 0;


struct Car{
    int x = 0, y = 0;
    int avail = 0;
    int id = -1;

    Car() = default;

    explicit Car(int id, int x = 0, int y = 0):
            x(x), y(y), id(id){

    }

    Car& operator = (const Car & c) = default;
    
    friend std::ostream& operator<<(std::ostream &os, Car & r){
        os<<"id: "<<r.id<<" x="<<r.x<<" y="<<r.y<<" avail="<<r.avail;
        return os;
    }

    void update(int nx, int ny, int na){
        x = nx;
        y= ny;
        avail = na;
        cout<<"updateted: "<<*this<<endl;
    }
    
};



void solve(const std::string & input, const std::string & output){
    std::ifstream in(input);
    std::ofstream out(output);
    int r, c, n, f, b, t;
    
    in>>r; // number of rows of the grid
    in>>c; // number of columns of the grid
    in>>n; // number of vehicles in the fleet
    in>>f; // number of rides
    in>>b; // per-ride bonus for starting the ride on time
    in>>t; // number of steps in the simulation
    
    vector <Ride> rides(f, Ride());
    
    for(int i = 0; i < f; i++){
        in>>rides[i];
    }
    
    std::sort(rides.begin(), rides.end());
    
    vector < vector <int> > assigned_rides(n, vector <int>());
    
    vector<Car> cars;

    for(int i = 0; i < n; i++){
        cars.emplace_back(i);
    }

    for(int i = 0 ; i < f; i++){
        assigned_rides[i%n].push_back(rides[i].id);
    }

    for(int i = 0; i< assigned_rides.size(); i++){
        out<<assigned_rides[i].size()<<" ";
        for(auto &e: assigned_rides[i]){
            out<<e<<" ";
        }
        out<<std::endl;
    }



}

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout<<"No parameters"<<std::endl;
        return 1;
    }
    solve("./in/"+std::string(argv[1])+".in", "./out/"+std::string(argv[1])+".out");
    return 0;
}