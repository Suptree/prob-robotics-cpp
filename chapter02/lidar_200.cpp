#define _USE_MATH_DEFINES
#include <cmath>
#include "matplotlibcpp.h"
#include <vector>
#include <fstream>
#include <sstream>

#include <string>
using namespace std;
namespace plt = matplotlibcpp;

int main() 
{
    vector<vector<int>> sensor_data;
    const char *inputfile = "../sensor_data_200.txt";
    std::ifstream ifs(inputfile);
    if( !ifs ) {
        std::cout << "cannot read file" << std::endl;
    }

    string line;
    for( int row = 0; getline(ifs, line); row++ ) {
        istringstream stream(line);
        int data;
        vector<int> n_data;
        for( int col = 0; stream >> data; col++ ) {
            n_data.emplace_back(data);
        }
        sensor_data.emplace_back(n_data);
    }

    std::vector<int> lidar_data;
    for( int i = 0; i < sensor_data.size(); i++ ) {
        lidar_data.emplace_back(sensor_data[i][3]);
    }
    int max = *max_element(lidar_data.begin(), lidar_data.end());
    int min = *min_element(lidar_data.begin(), lidar_data.end());
    plt::hist(lidar_data,max-min);
    plt::title("Lidar Sensor");
    plt::xlabel("sensor values");
    plt::ylabel("frequency");
    plt::show();

    return (0);
}
