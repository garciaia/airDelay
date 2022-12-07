#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <tuple>
using namespace std;
using namespace std::chrono;

//Adj List Class
//cite: edugator programming quiz 6.1: not so simple graph for adjacency list skeleton
class AdjList
{

private:
    unordered_map<string, vector<tuple<string,double,int>>> list;

public:
    void insertEdge(string, string, double, int);
    bool isEdge(string, string);
    int sumEdge(string, string);
    vector<int> getWeight(string, string);
    double getWeight1(string, string);
    double getWeight2(string, string);
    vector<string> getAdjacent(string);
    void printGraph();
    void sumCancel(AdjList);
    void sumDelays(AdjList);
    void perFlights(AdjList);
    void avgDelays(AdjList);
    void adjustEdge(AdjList&, string, string, double, int);
};

void AdjList::insertEdge(string from, string to, double weight1, int weight2)
{
    /*
         insertEdge() adds a new edge between the from
         and to vertex.
    */
    list[from].push_back(make_tuple(to,weight1, weight2));
}

bool AdjList::isEdge(string from, string to)
{
    /*
        isEdge() returns a boolean indicating true
        if there is an edge between the from and to vertex
    */
    for (auto& member: list[from]) {
        if (get<0>(member) == to) {
            return true;
        }
    }
    return false;
}

int AdjList::sumEdge(string from, string to)
{
    /*
        sumEdge() returns the sum of weights of all edges
        connecting the from and to vertex. Returns 0 if no edges
        connect the two vertices.
    */
    int tot = 0;
    for (auto& member: list[from]) {//sort thru AdjList at from key
        if (get<0>(member) == to) {//if edge connects from to to
            tot += get<1>(member);
        }
    }
    return tot;
}

vector<int> AdjList::getWeight(string from, string to)
{
    /*
        getWeight() returns a sorted vector containing all
        weights of the edges connecting the from and to vertex
    */
    vector<int>weights;
    for (auto& member: list[from]) {
        if (get<0>(member) == to) {//if edge connects from to to
            weights.push_back(get<1>(member));
        }
    }
    return weights;
}

double AdjList::getWeight1(string from, string to)
{
    //returns weight1 of edge connecting from to to (for lists w/ no duplicates)
    double weight1 = 0;
    for (auto& member: list[from]) {
        if (get<0>(member) == to) {//if edge connects from to to
            weight1 = get<1>(member);
        }
    }
    return weight1;
}

double AdjList::getWeight2(string from, string to)
{
    //returns weight2 of edge connecting from to to (for lists w/ no duplicates)
    double weight2 = 0;
    for (auto& member: list[from]) {
        if (get<0>(member) == to) {//if edge connects from to to
            weight2 = get<2>(member);
        }
    }
    return weight2;
}


vector<string> AdjList::getAdjacent(string vertex)
{
    /*
        getAdjacent() returns a sorted vector of all vertices
        that are connected to a vertex
    */
    vector<string>adjs;
    for (auto& member: list[vertex]){
        adjs.push_back(get<0>(member));
    }
    return adjs;
}

void AdjList::printGraph(){
    //TODO: printGraph() prints the graph in a format sorted by ascending vertex matrix of weights
    for (auto& member: list){
        cout << member.first << ": ";
        for (auto& member2: member.second){
            cout << get<0>(member2) << " " << get<1>(member2) << " " << get<2>(member2) << '\t';
        }
        cout << endl;
    }
}

void AdjList::sumCancel(AdjList adj){ //create list 2 w/ flight sums
    AdjList temp;
    int weight1 = 0, weight2 = 0;
    for(auto itr = adj.list.begin(); itr != adj.list.end(); ++itr){
        for (const auto& vec: itr -> second){//iterates thru vector of tuples
            if(temp.list.find(itr->first) == list.end()){//if key not in temp
                temp.insertEdge(itr->first, get<0>(vec), get<1>(vec), 1);
            }
            else{//if key is in temp
                //first check if from-destination is in temp
                if(temp.isEdge(itr->first, get<0>(vec))){
                    //if so, access from-to pair and increment total and maybe cancelled
                    weight1 = temp.getWeight1(itr->first, get<0>(vec));
                    weight2 = temp.getWeight2(itr->first, get<0>(vec));
                    if(get<1>(vec) == 1){
                        temp.adjustEdge(temp, itr->first, get<0>(vec), weight1+1, weight2+1);
                    }
                    else{
                        temp.adjustEdge(temp, itr->first, get<0>(vec), weight1, weight2+1);
                    }
                }
                else{//if not, add to temp
                    temp.insertEdge(itr->first, get<0>(vec), get<1>(vec), 1);
                }
            }
        }
        for(auto itr2 = temp.list.begin(); itr2 != temp.list.end(); ++itr2){
            for (const auto& vec2: itr2 -> second){
                if(!isEdge(itr2->first, get<0>(vec2)))
                    insertEdge(itr2->first, get<0>(vec2), get<1>(vec2), get<2>(vec2));
            }
        }
    }
}

void AdjList::sumDelays(AdjList adj){
    AdjList temp;
    double weight1 = 0, weight2 = 0;
    for(auto itr = adj.list.begin(); itr != adj.list.end(); ++itr){
        for (const auto& vec: itr -> second){//iterates thru vector of tuples
            if(temp.list.find(itr->first) == list.end()){//if key not in temp
                temp.insertEdge(itr->first, get<0>(vec), get<1>(vec), 1);
            }
            else{//if key is in temp
                //first check if from-destination is in temp
                if(temp.isEdge(itr->first, get<0>(vec))){
                    //if so, access from-to pair and increment total and maybe cancelled
                    weight1 = temp.getWeight1(itr->first, get<0>(vec)); //gets dep delay
                    weight2 = temp.getWeight2(itr->first, get<0>(vec)); //gets counter
                    temp.adjustEdge(temp, itr->first, get<0>(vec), weight1+get<1>(vec), weight2+1);//add to sum and increment counter
                }
                else{//if not, add to temp
                    temp.insertEdge(itr->first, get<0>(vec), get<1>(vec), 1);
                }
            }
        }
        for(auto itr2 = temp.list.begin(); itr2 != temp.list.end(); ++itr2){
            for (const auto& vec2: itr2 -> second){
                if(!isEdge(itr2->first, get<0>(vec2))){
                    //cout << "from: " << itr2->first << " to: " << get<0>(vec2) << " sum delay: " << get<1>(vec2) << " total: " << get<2>(vec2) << endl;
                    insertEdge(itr2->first, get<0>(vec2), get<1>(vec2), get<2>(vec2)); //makes list of sums & totals
                }
            }
        }
    }
}

void AdjList::perFlights(AdjList adj){
    double percent = 0.0;
    for(auto itr = adj.list.begin(); itr != adj.list.end(); ++itr){
        for (const auto& vec: itr -> second){
            if(get<2>(vec) != 0){
                percent = (double)get<1>(vec)/(double)get<2>(vec);
            }
            insertEdge(itr->first, get<0>(vec), percent, -200);
        }
    }
}


void AdjList::adjustEdge(AdjList& adj, string from, string to, double weight1, int weight2){
    //grab from-to edge and change weights
    for (auto& member: adj.list[from]) {
        if (get<0>(member) == to) {//if edge connects from to
            get<1>(member) = weight1;
            get<2>(member) = weight2;
        }
    }
}


//Adj Matrix class
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

    string printOutput(string beg, string end){
        string output = "null";
        for (int i = 0; i < numAirports; i++)
            for (int j = 0; j < numAirports; j++)
                if (adjMatrix[i][j].second != 0) {
                    if(airportList[i] == beg && airportList[j] == end) {
                        output = airportList[i] + "," + airportList[j] + "," + to_string(adjMatrix[i][j].first) + "," +
                                 to_string(adjMatrix[i][j].second);
                    }
                }
        return output;
    }


};


int main(){
    string instruction;
    string datastruct = "null";
    vector <string> instruct;
    fstream inputfile ("input.txt");
    while(!inputfile.eof() ){
        inputfile >> instruction;
        instruct.push_back(instruction);
    }
    inputfile.close();
    int infosize = instruct.size() - 1;
    instruction = instruct[infosize];
    //cout << instruction << endl;
    int comma = instruction.find(",");
    datastruct  = instruction.substr(0, comma);
    instruction = instruction.substr(comma+1,instruction.length());
    comma = instruction.find(",");
    string beg = instruction.substr(0, comma);
    string end = instruction.substr(comma+1,instruction.length());
    string cancellation;
    string deptDelay;
    string arrDelay;
    string listDuration;
    string matrixDuration;

    //Generates cancellation data via adjacency list
    if(datastruct == "List") {
        //AdjList alldep, sumdep, perdep, allarr, sumarr, perarr;
        AdjList all, sum, per;
        ifstream myFile;
        myFile.open("cleanflights1.csv");
        string from, to, cancel, line, ignore, departure, arrival;
        int cancelled = 0, depdelay = 0, arrdelay = 0;
        while (myFile.good()) {
            getline(myFile, ignore); //ignore first line
            while (getline(myFile, line)) {
                stringstream ss(line);
                getline(ss, ignore, ','); //skip over irrelevant columns
                getline(ss, from, ','); //csv files are comma separated
                getline(ss, to, ',');
                getline(ss, departure, ',');
                getline(ss, arrival, ',');
                getline(ss, cancel, ',');
                try {
                    cancelled = stoi(cancel);
                    //depdelay = stoi(departure);
                    //arrdelay = stoi(arrival);
                }
                catch (...) {
                    cancelled = 0;
                    //depdelay = 0;
                    //arrdelay = 0;
                }
                if (!isdigit(from[0]) || !isdigit(to[0])) { //if from or to is a number, skip
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
        //perdep.printGraph();
        //per contains all our cancellation percentages in decimal format
        //perdep contains all our departure delay averages
        //perarr contains all our arrival delay averages

        cancellation = to_string(per.getWeight1(beg, end));
        //cout << per.getWeight2(beg, end) << endl;

        myFile.close();

    }
    // Creates adj list for calculating delay info both arrival and departure
    if (datastruct == "List"){
        auto start = high_resolution_clock::now();
        AdjList alldep, sumdep, perdep, allarr, sumarr, perarr;
        //AdjList all, sum, per;
        ifstream myFile;
        myFile.open("cleanflights1.csv");
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
                    //cancelled = stoi(cancel);
                    depdelay = stoi(departure);
                    arrdelay = stoi(arrival);
                }
                catch(...){
                    //cancelled = 0;
                    depdelay = 0;
                    arrdelay = 0;
                }
                if(!isdigit(from[0]) || !isdigit(to[0])){ //if from or to is a number, skip
                    //all.insertEdge(from, to, cancelled, -200);
                    alldep.insertEdge(from, to, depdelay, -200);
                    allarr.insertEdge(from, to, arrdelay, -200);
                }
            }
        }
        //sum.sumCancel(all);
        sumdep.sumDelays(alldep);
        sumarr.sumDelays(allarr);
        //per.perFlights(sum);
        perdep.perFlights(sumdep);
        perarr.perFlights(sumarr);
        //perdep.printGraph();
        //per contains all our cancellation percentages in decimal format
        //perdep contains all our departure delay averages
        //perarr contains all our arrival delay averages

        //perdep.printGraph();
        arrDelay = to_string(perarr.getWeight1(beg, end));
        deptDelay = to_string(perdep.getWeight1(beg, end));
        //cout << sumdep.getWeight2("SAV", "EWR");

        myFile.close();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        listDuration = to_string(duration.count());
        matrixDuration = "null";
    }

    if(datastruct == "Matrix"){
        auto start = high_resolution_clock::now();
        Graph depart;
        depart.departureDelays();
        //depart.printAdjMatrix();
        //cout << "-----------------------------" << endl;
        Graph arrive;
        arrive.arrivalDelays();
        //arrive.printAdjMatrix();
        arrDelay = arrive.printOutput(beg, end);
        deptDelay = depart.printOutput(beg, end);

        int point1 = arrDelay.find(",");
        arrDelay = arrDelay.substr(point1+1, arrDelay.length() - point1);
        point1 = arrDelay.find(",");
        arrDelay = arrDelay.substr(point1+1, arrDelay.length() - point1);
        point1 = arrDelay.find(",");
        arrDelay = arrDelay.substr(0, point1);

        point1 = deptDelay.find(",");
        deptDelay = deptDelay.substr(point1+1, deptDelay.length() - point1);
        point1 = deptDelay.find(",");
        deptDelay = deptDelay.substr(point1+1, deptDelay.length() - point1);
        point1 = deptDelay.find(",");
        deptDelay = deptDelay.substr(0, point1);

        cancellation = "null";
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        matrixDuration = to_string(duration.count());
        listDuration = "null";
    }
    string finalout = datastruct + "," + beg + "," + end + "," + cancellation + "," + arrDelay + "," + deptDelay + "," + listDuration + "," + matrixDuration;
    cout << "Calculated Using An Adjacency " << datastruct << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Your flight from " << beg << " to " << end << ":" << endl;
    if(stoi(deptDelay)>0){
    cout << "Will likely depart " << deptDelay << " minutes late." << endl;}
    else if(stoi(deptDelay)<0){
        cout << "Will likely depart " << deptDelay << " minutes early." << endl;}
    if(stoi(arrDelay)>0){
        cout << "Will likely arrive " << arrDelay << " minutes late." << endl;}
    else if(stoi(arrDelay)<0){
        cout << "Will likely arrive " << arrDelay << " minutes early." << endl;}
    if(datastruct == "List"){
        cout<< "It has a " << stoi(cancellation) * 100 << "% chance of being cancelled altogether." << endl;
    }
    cout << "-----------------------------------------------------" << endl;
    if(datastruct == "Matrix"){
        cout << "This information was generated in " << matrixDuration << " microseconds." <<endl;
    }
    if(datastruct == "List"){
        cout << "This information was generated in " << listDuration << " microseconds." <<endl;
    }

    cout << endl;


    fstream outfile ("output.txt");
    outfile << finalout << endl;
    outfile.close();
    //cout << finalout << endl;
    /*
    cout << datastruct << endl;
    cout << beg << endl;
    cout << end << endl;
    cout << cancellation << endl;
    cout << arrDelay << endl;
    cout << deptDelay << endl;
    cout << listDuration << endl;
    cout << matrixDuration << endl;
    */
}