#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "DataPoint.h"

double convertCoord(std::string c){
    double coord = stod(c);
    char cardinal = c.back();
    if(cardinal == 'W' || cardinal == 'S')
        return -coord;
    else return coord;
}

void readFile(std::string filename, std::vector<DataPoint>& data){
    std::ifstream inputFile(filename);

    // Line Format: Date, Avg Temp, Uncertainty, City, Country, lat, long
    std::string line = "";
    getline(inputFile, line);
    while(getline(inputFile, line)){
        std::string date = "";
        double temperature = 0.0;
        double uncertainty = 0.0;
        double lat = 0.0;
        double lon = 0.0;
        std::string tempString;
        std::stringstream ss(line);

        // Date
        getline(ss, date, ',');
        // Temperature
        getline(ss, tempString, ',');
        if(!tempString.empty()) temperature = stod(tempString);
        // Uncertainty
        getline(ss, tempString, ',');
        if(!tempString.empty()) uncertainty = stod(tempString);

        // Country and City:
        getline(ss, tempString, ',');
        getline(ss, tempString, ',');

        // Latitude
        getline(ss, tempString, ',');
        if(!tempString.empty()) lat = convertCoord(tempString);
        // Longitude
        getline(ss, tempString, ',');
        if(!tempString.empty()) lon = convertCoord(tempString);
        std::pair<double, double> coordinate = {lat, lon}; // latitude always precedes longitude

        DataPoint dp(coordinate, date, temperature, uncertainty);

        data.push_back(dp);
    }
}

int main(){
    std::vector<DataPoint> data;

    readFile("city.csv", data);

    for(auto& dp : data){
        dp.Display();
    }
    std::cout<<data.size();

    return 0;
}