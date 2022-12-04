#include "AdjList.hpp"
#include <fstream>
#include <sstream>

int main(){
    AdjList all, sum, per;
    ifstream myFile;
    myFile.open("cleanflights.csv");
    string from, to, cancel, line, ignore;
    int cancelled = 0;
    while(myFile.good()){
        getline(myFile,ignore); //ignore first line
        while(getline(myFile,line)){
            stringstream ss(line);
            getline(ss, ignore, ','); //skip over irrelevant columns
            getline(ss, from, ','); //csv files are comma separated
            getline(ss, to, ',');
            getline(ss, ignore, ',');
            getline(ss, ignore, ',');
            getline(ss, cancel, ',');
            try{
                cancelled = stoi(cancel);
            }
            catch(...){
                cancelled = 0;
            }
            if(!isdigit(from[0]) || !isdigit(to[0])) //if from or to is a number, skip
                all.insertEdge(from, to, cancelled, -200);
        }
    }
    sum.sumFlights(all);
    per.perFlights(sum);
    //per.printGraph();
    //per contains all our cancellation percentages in decimal format
    myFile.close();
}
