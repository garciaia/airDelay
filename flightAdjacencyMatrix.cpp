#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>  
#include <fstream>
#include <sstream>
using namespace std;

// read the "cleanflights.csv" file to store data about flight delays
// the cleanflights file has 6 columns for the following variables: airline, origin airport, destination airport, departure delay, arrival delay, and cancellation
// the only data that matters for this project is each tuple is the origin airport, destination airport, and departure delay
// create an adjacency matrix to represent the data as a graph with origin airport being a from node and destination airport being a to node, and the weight being the departure delay
// the adjacency matrix is a 2D vector of vectors of pairs of integers
// the first vector is the from node, the second vector is the to node, the first value of the pair is the total departure delay, and the second value of the pair is how many times that flight occurs
// in the class are functions that inserts an edge into the adjacency matrix and prints the adjacency matrix
class Graph {
    private:
        vector<vector<pair <double, int> > > adjMatrix;
        unordered_map<string, int> airportMap;
        vector<string> airportList;
        int numAirports;
    public:
        // reads the "cleanflights.csv" file and store the data for origin airport, destination airport, and departure delay in the adjacency matrix, where origin airport is the row, destination airport is the column, total departure delay is the weight of the edge in the first value of the pair, and the number of times that flight occurs is the second value of the pair
        void departureDelays() {
            ifstream file("cleanflights1.csv");
            string line;
            int row = 0;
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                int col = 0;
                while (getline(ss, item, ',')) {
                    if (col == 1) {
                        if (airportMap.find(item) == airportMap.end()) {
                            airportMap[item] = row;
                            airportList.push_back(item);
                            row++;
                        }
                    }
                    if (col == 2) {
                        if (airportMap.find(item) == airportMap.end()) {
                            airportMap[item] = row;
                            airportList.push_back(item);
                            row++;
                        }
                    }
                    col++;
                }
            }
            numAirports = airportList.size();
            adjMatrix.resize(numAirports, vector<pair<double, int> >(numAirports, make_pair(0, 0)));
            file.close();
            file.open("cleanflights1.csv");
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                int col = 0;
                int from;
                int to;
                double weight;
                while (getline(ss, item, ',')) {
                    if (col == 1) 
                        from = airportMap[item];
                    if (col == 2) 
                        to = airportMap[item];
                    if (col == 3) {
                        try {
                            weight = stod(item);
                        }
                        catch(...) {
                            weight = 0;
                        }
                    }
                    col++;
                }
                adjMatrix[from][to].first += weight;
                adjMatrix[from][to].second++;
            }
            file.close();
            // go through the adjacency list and divide each weight by the number of times that flight occurs
            for (int i = 0; i < numAirports; i++) 
                for (int j = 0; j < numAirports; j++) 
                    if (adjMatrix[i][j].second != 0) 
                        adjMatrix[i][j].first /= adjMatrix[i][j].second;
                    
                
        }

        // function similar to the previous, but for arrival delays which are located in column 4 of the "cleanflights.csv" file
        void arrivalDelays() {
            ifstream file("cleanflights1.csv");
            string line;
            int row = 0;
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                int col = 0;
                while (getline(ss, item, ',')) {
                    if (col == 1) {
                        if (airportMap.find(item) == airportMap.end()) {
                            airportMap[item] = row;
                            airportList.push_back(item);
                            row++;
                        }
                    }
                    if (col == 2) {
                        if (airportMap.find(item) == airportMap.end()) {
                            airportMap[item] = row;
                            airportList.push_back(item);
                            row++;
                        }
                    }
                    col++;
                }
            }
            numAirports = airportList.size();
            adjMatrix.resize(numAirports, vector<pair<double, int> >(numAirports, make_pair(0, 0)));
            file.close();
            file.open("cleanflights1.csv");
            while (getline(file, line)) {
                stringstream ss(line);
                string item;
                int col = 0;
                int from;
                int to;
                double weight;
                while (getline(ss, item, ',')) {
                    if (col == 1) 
                        from = airportMap[item];
                    if (col == 2) 
                        to = airportMap[item];
                    if (col == 4) {
                        try {
                            weight = stod(item);
                        }
                        catch(...) {
                            weight = 0;
                        }
                    }
                    col++;
                }
                adjMatrix[from][to].first += weight;
                adjMatrix[from][to].second++;
            }
            file.close();
            // go through the adjacency list and divide each weight by the number of times that flight occurs
            for (int i = 0; i < numAirports; i++) 
                for (int j = 0; j < numAirports; j++) 
                    if (adjMatrix[i][j].second != 0) 
                        adjMatrix[i][j].first /= adjMatrix[i][j].second;
                    
        }

        // function to print the adjacency matrix in the format "from node, to node, weight"
        void printAdjMatrix() {
            for (int i = 0; i < numAirports; i++) 
                for (int j = 0; j < numAirports; j++) 
                    if (adjMatrix[i][j].second != 0) 
                        cout << airportList[i] << ", " << airportList[j] << ", " << adjMatrix[i][j].first << ", " << adjMatrix[i][j].second << endl;
        }
};

int main() {
    Graph depart;
    depart.departureDelays();
    depart.printAdjMatrix();
    cout << "-----------------------------" << endl;
    Graph arrive;
    arrive.arrivalDelays();
    arrive.printAdjMatrix();
    return 0;
}