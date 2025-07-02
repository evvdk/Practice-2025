#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

# define M_PI 3.14159265358979323846

template <typename T> struct Point {
    T t;
    T f;
};

int main(){
    srand(time(0));

    const int recordsCount = 2000;
    std::vector <Point<float>> data(recordsCount, Point<float>{0,1.25});
    int k = 1;
    for(int i = 0; i<recordsCount; i++){
        data[i].t = 0.1 * i;
        float y;
        float q1 = 1 / (1+exp(-k * (i - 500) * 0.1));
        float q2 = 1 / (1+exp(-k * (i - 1500) * 0.1));
        y = (1-q1) * (-1) + q1 * (sin(i*0.1*M_PI/30 + M_PI*1.5)) * (i - 1500);
        y = (1-q2) * y + q2 * (-1);
        data[i].f = y;
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