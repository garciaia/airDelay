#include "AdjList.hpp"
#include <fstream>
#include <sstream>

int main(){
    AdjList all, sum, per;
    //Lists list;
    ifstream myFile;
    myFile.open("flightsTemp.csv");
    string from, to, cancel, ignore, temp, word;
    vector<string>line;
    int cancelled = 0;
    while(myFile.good()){
        getline(myFile,ignore); //ignore first line
        while(!myFile.eof()){
            for(int i=0; i<7; i++)
                getline(myFile, ignore, ','); //skip over irrelevant columns
            getline(myFile, from, ','); //csv files are comma separated
            getline(myFile, to, ',');
            for(int i=0; i<15; i++)
                getline(myFile, ignore, ',');
            getline(myFile, cancel, ',');  
            for(int i=0; i<5; i++)//ignore last 5 columns
                getline(myFile, ignore, ',');
            if(cancel.empty())
                cancelled = 0;
            else
                cancelled = stoi(cancel);
            if(!isdigit(from[0]) || !isdigit(to[0])) //if from or to is a number, skip
                all.insertEdge(from, to, cancelled, -200);
            //cout << "from: " << from << " to: " << to << " cancel: " << cancelled << endl;
        }
    }
    //cout << "list 1:" << endl;
    //all.printGraph();
    //cout << endl << "list 2:" << endl;
    sum.sumFlights(all);
    //sum.printGraph();
    //cout << endl << "list 3:" << endl;
    per.perFlights(sum);
    per.printGraph();
    myFile.close();
}
