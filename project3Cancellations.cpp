#include "AdjList.hpp"
#include <fstream>
#include <sstream>

int main(){
    //AdjList alldep, sumdep, perdep, allarr, sumarr, perarr;
    AdjList all, sum, per;
    ifstream myFile;
    myFile.open("tempdelays.csv");
    string from, to, cancel, line, ignore, departure, arrival;
    int cancelled = 0, depdelay = 0, arrdelay = 0;
    while(myFile.good()){
        getline(myFile,ignore); //ignore first line
        while(getline(myFile,line)){
            stringstream ss(line);
            getline(ss, ignore, ','); //skip over irrelevant columns
            getline(ss, from, ','); //csv files are comma separated
            getline(ss, to, ',');
            getline(ss, departure, ',');
            getline(ss, arrival, ',');
            getline(ss, cancel, ',');
            try{
                cancelled = stoi(cancel);
                //depdelay = stoi(departure);
                //arrdelay = stoi(arrival);
            }
            catch(...){
                cancelled = 0;
                //depdelay = 0;
                //arrdelay = 0;
            }
            if(!isdigit(from[0]) || !isdigit(to[0])){ //if from or to is a number, skip
                all.insertEdge(from, to, cancelled, -200);
                //alldep.insertEdge(from, to, depdelay, -200);
                //allarr.insertEdge(from, to, arrdelay, -200);
            }
        }
    }
    sum.sumCancel(all);
    //sumdep.sumDelays(alldep);
    //sumarr.sumDelays(allarr);
    per.perFlights(sum);
    //perdep.perFlights(sumdep);
    //perarr.perFlights(sumarr);
    //perarr.printGraph();
    //per contains all our cancellation percentages in decimal format
    //perdep contains all our departure delay averages
    //perarr contains all our arrival delay averages
    myFile.close();
}
