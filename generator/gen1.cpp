#include <vector>
#include <fstream>
#include <cmath>

template <typename T> struct Point {
    T t;
    T f;
};

int main(int argc, char *argv[]){
    srand(time(0));
    std::string out_file_path;
    if(argc == 2) out_file_path = std::string(argv[1]);
    else out_file_path = "data.txt";
    int recordsCount = 1000;
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

    std::ofstream file(out_file_path);
    if(!file.is_open()){
        return -1;
    }
    for(int i = 0; i<recordsCount; i++){
        file << data[i].t << "\t" << data[i].f;
        if(i != recordsCount-1) file << "\n";
    }

    printf("Создан файл %s для %d записей\n", out_file_path.c_str(), recordsCount);
}