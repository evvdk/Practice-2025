#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

template <typename T> struct Point {
    T t;
    T f;
};

int main(){
    srand(time(0));

    const int recordsCount = 1000;
    std::vector <Point<float>> data(recordsCount, Point<float>{0,1.25});
    for(int i = 0; i<recordsCount; i++){
        data[i].t = 0.1 * i;
        if(i < 200) data[i].f = 8 + (float)(rand()%50)/100;
        else if(i<=250) {
            float range = (float)(i-200)/50;
            float value = cos(range*15)*(1-range)*6+4;
            data[i].f = value;
        }
        else data[i].f = 4 + (float)(rand()%50)/100; 
    }

    std::ofstream file("data.txt");
    if(!file.is_open()){
        return -1;
    }
    for(int i = 0; i<recordsCount; i++){
        file << data[i].t << "\t" << data[i].f;
        if(i != recordsCount-1) file << "\n";
    }
}