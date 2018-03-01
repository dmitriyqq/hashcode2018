#include <bits/stdc++.h>

using std::cout;
using std::endl;


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
        int dist  = std::abs(r.y1 - r.y2) + std::abs(r.x1 -  r.x2);
        os<<"dist = "<<dist<<" delta time: "<<(r.f-r.s);
        return os;
    }
};


struct Car{
    int x = 0, y = 0;
    int avail = 0;
    int id = -1;

    Car(){
        id = -1;
    }

    Car(int id, int x = 0, int y = 0 ) :
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

using std::vector;

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
    std::set <int> free;
    std::sort(v.begin(), v.end());
    std::vector < std::vector <int> > vr (n, std::vector <int>());
    vector<Car> avto;

    for(int i = 0; i < n; i++){
        avto.emplace_back(i+1);
        free.insert(i+1);
    }

    for(int i =0 ; i< f; i++){
        vector <Car> avaible;
        int cs = v[i].s;
        int cf = v[i].f;
        cout<<"going to "<<v[i]<<endl;
        using std::abs;

        Ride& dest = v[i];
        int toDest = abs(dest.x2 - dest.x1) + abs(dest.y2 - dest.y1);
        for(auto &e : avto){

            int toStart = abs(e.x - dest.x1) + abs(e.y - dest.y1);
            int a = std::max(cs + toDest, e.avail +  toStart + toDest);

            if(toStart + e.avail <= cf){
               // cout<<"car good adding"<<endl;
                avaible.push_back(e);
                continue;
            }else {
              //  cout << "car:  " << e;
              //  cout << "tostart:  " << toStart;
              //  cout << "  arrive: " << a << endl;
            }
        }

        Car best;
        int nearest = INT_MAX;
        cout<<"availble: "<<avaible.size()<<endl;
        for(auto &e : avaible){
            //cout<<e<<endl;
            int toStart = abs(e.x - dest.x1) + abs(e.y - dest.y1)+e.avail;

            if(nearest > toStart){
                nearest = toStart;
                best = e;
            }
        }

        cout<<"nearest = "<<nearest<<endl;

        if(best.id != -1){
            cout<<"best car = "<<endl<<best<<endl;
            vr[best.id-1].push_back(i);
            int toStart = abs(best.x - dest.x1) + abs(best.y - dest.y1);
            int a = best.avail +  toStart + toDest;
            int id = best.id;
            avto[id-1].update(dest.x2, dest.y2, a);


        }else{
            cout<<"Noto possible to service best -1" <<endl;
            int minj = 0;
            int mm = 0;
            for(int i = 0; i < vr.size(); i++)
                if(mm > vr[i].size()){
                    mm = vr[i].size();
                    minj = i;
                }
            free.remove()
            vr[minj].push_back(i);
            int toStart = abs(best.x - dest.x1) + abs(best.y - dest.y1);
            int a = avto[minj-1].avail +  toStart + toDest;
            avto[minj].update(dest.x2, dest.y2, a);
        }

    }

    for(int i = 0; i< vr.size(); i++){
        out<<vr[i].size()<<" ";
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