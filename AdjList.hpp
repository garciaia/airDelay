#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
using namespace std;

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
        if (get<0>(member) == to) {//if edge connects from to to
            get<1>(member) = weight1;
            get<2>(member) = weight2;
        }
    }
}