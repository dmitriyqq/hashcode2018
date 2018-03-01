#include <bits/stdc++.h>

struct Ride{
    int x1, x2;
    int y1, y2;
    int s, f;

    Ride(){

    }

    Ride(int x1, int y1, int x2, int y2, int s, int f):
            x1(x1), x2(x2), y1(y1), y2(y2), s(s), f(f){

    }

    bool operator<(const Ride & o){
        return this->s < o.s;
    }

    friend std::istream& operator>>(std::istream &is, Ride & r){
        is>>r.x1>>r.y1>>r.x2>>r.y2>>r.s>>r.f;
        return is;
    }

    friend std::ostream& operator<<(std::ostream &os, Ride & r){
        os<<r.x1<<" "<<r.y1<<" "<<r.x2<<" "<<r.y2<<" "<<r.s<<" "<<r.f;
        return os;
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
    std::vector <Ride> v(f, Ride());
    for(int i = 0; i < f; i++){
        in>>v[i];
    }

    std::sort(v.begin(), v.end());
    std::vector < std::vector <int> > vr (n, std::vector <int>());
    std::cout<<"rides: "<<std::endl;

    int vehicle_counter = 0;
    for(int i =0 ; i< f; i++){
        vr[i%n].push_back(i);
    }

    for(int i = 0; i< vr.size(); i++){
        out<<(i+1)<<" ";
        for(auto &e: vr[i]){
            out<<e<<" ";
        }
        out<<std::endl;

    }



}

int main(int argc, char* argv[]) {
    if(argc < 2){
        std::cout<<"no parameters"<<std::endl;
        return 1;
    }
    solve("./in/"+std::string(argv[1])+".in", "./out/"+std::string(argv[1])+".out");
    return 0;
}