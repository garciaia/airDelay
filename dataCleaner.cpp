#include <iostream>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int nthOccurrence(const std::string& str, const std::string& findMe, int nth)
{
    size_t  pos = 0;
    int     cnt = 0;

    while( cnt != nth )
    {
        pos+=1;
        pos = str.find(findMe, pos);
        if ( pos == std::string::npos )
            return -1;
        cnt++;
    }
    return pos;
}

int main() {
    string line;
    string colname;
    vector <string> output;
    fstream myFile ("/Users/savaglisic/Desktop/flights.csv");

    int i = 0;
    while(i < 120000){
        myFile >> line;
        int airline1 = nthOccurrence(line, ",", 4);
        string currair = line.substr(airline1+1,2);

        int origin1 = nthOccurrence(line, ",", 7);
        string currorigin = line.substr(origin1+1,3);

        int dest1 = nthOccurrence(line, ",", 8);
        string currdest = line.substr(dest1+1,3);

        int ddelay1 = nthOccurrence(line, ",", 11);
        int ddelay2 = nthOccurrence(line, ",", 12);
        int diff = ddelay2 - ddelay1;
        string ddelay = line.substr(ddelay1+1,diff-1);

        int adelay1 = nthOccurrence(line, ",", 22);
        int adelay2 = nthOccurrence(line, ",", 23);
        int diff2 = adelay2 - adelay1;
        string adelay = line.substr(adelay1+1,diff2-1);

        int cancel1 = nthOccurrence(line, ",", 24);
        string cancel = line.substr(cancel1+1,1);

        if(cancel == "1"){
            adelay = "-200";
            ddelay = "-200";
        }

        string output1 = currair + "," + currorigin + "," + currdest + "," + ddelay + "," + adelay + "," + cancel;
        output.push_back(output1);

        cout << i << endl;
        //cout << currair << "," << currorigin << "," << currdest << "," << ddelay << "," << adelay << "," << cancel;
        cout << output1;
        cout << endl;
        i++;
        if (myFile.fail() || myFile.eof())
            break;
    }
    myFile.close();
    fstream cleanfile ("cleanflights.csv");
    for(int i = 0; i<output.size(); i++){
        cleanfile << output[i] << endl;
    }

}
