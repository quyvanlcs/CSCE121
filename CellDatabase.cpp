#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include <fstream>

using namespace std;

// Default constructor/destructor. Modify them if you need to.
CellDatabase::CellDatabase() {}
CellDatabase::~CellDatabase() {}

bool isValidLine(string line, string& id, int& fov, double& volume, 
                        double& center_x, double& center_y, 
                        double& min_x, double& max_x, 
                        double& min_y, double& max_y) {
    int numIndicator = 1;
    for (size_t i = 0; i < line.size(); ++i) {
        if (line[i] == ',') {
            numIndicator++;
            line[i] = ' ';
        }
    }
    if (numIndicator != 9) {
        return false;
    }
    istringstream inSS(line);
    inSS >> id;
    if (inSS.fail()) {
        return false;
    }
    for (size_t i =0; i < id.size(); ++i) {
        if (int(id[i]) < 48 || int(id[i]) > 57) {
            return false;
        } 
    }

    inSS >> fov;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> volume;
    if (inSS.fail() || volume <= 0) {
        return false;
    } 
    inSS >> center_x;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> center_y;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> min_x;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> max_x;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> min_y;
    if (inSS.fail()) {
        return false;
    } 
    inSS >> max_y;
    if (inSS.fail()) {
        return false;
    }
    string test;
    inSS >> test;
    if (test != "") {
        return false;
    }
    return true;
}

void CellDatabase::loadData(const string& filename) 
{
    string id;
    int fov;
    double volume;
    double center_x;
    double center_y;
    double min_x;
    double max_x;
    double min_y;
    double max_y;
    string newLine;
    int countValid = 0, countInvalid = 0;
    // Implement this function
    ifstream inFS(filename);
    if (!inFS.is_open()) {
        cout << "Error: Unable to open" << endl;
    }
    getline(inFS,newLine);
    newLine = "";
    while (!inFS.eof()) {
        getline(inFS, newLine);
        // cout << newLine << endl;
        if (newLine == "\r" || newLine.empty()) {
            continue;
        }
        bool checkValid = isValidLine(newLine,id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);
        if (!checkValid) {
            cout << "Error, Invalid input: " << newLine << endl;
            countInvalid++;
            continue;
        }
        records.insert(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);
        countValid++;
    }
    // cout << "Valid: " << countValid << "\t" << "Invalid: " << countInvalid << endl;
    inFS.close();
}

// Do not modify
void CellDatabase::outputData(const string& filename) {
    ofstream dataout("sorted." + filename);

    if (!dataout.is_open()) 
    {
        cout << "Error: Unable to open " << filename << endl;
        exit(1);
    }
    dataout << records.print();
}

void CellDatabase::performQuery(const string& filename) 
{
    // Implement this function

    ifstream inFS(filename);
    ostringstream outSS;
    string indicator;
    string newLine;
    string test;
    int k;
    int j;
    int N;
    
    
    if (!inFS.is_open()) {
        cout << "Error: Unable to open" << endl;
    }
    while(!inFS.eof()) {
        newLine = "";
        indicator = "";
        getline(inFS, newLine);
        if (newLine == "\r" || newLine.empty()) {
            continue;
        }
        istringstream inSS(newLine);
        inSS >> indicator;
        if (inSS.fail()) {
            outSS << "Error, Invalid input: " << newLine << endl;
            continue;
        }
        inSS >> k;
        if (inSS.fail() || k <= 0) {
            outSS << "Error, Invalid input: " << newLine << endl;
            continue;
        }
        if (indicator != "OUTLIER") {
            test = "";
            inSS >> test;
            if (test[0] != '\0') {
                outSS << "Error, Invalid input: " << newLine << endl;
                continue;
            }
        }
        if (indicator == "AVG") {
            outSS << indicator << " " << k << ": " << records.average(k) << endl;
        }
        else if (indicator == "VAR") {
            outSS << indicator << " " << k << ": " << records.variance(k) << endl;
        }
        else if (indicator == "COUNT") {
            outSS << indicator << " " << k << ": " << records.countN(k) << endl;
        }
        else if (indicator == "OUTLIER") {
            inSS >> j;
            if (inSS.fail()) {
                outSS << "Error, Invalid input: " << newLine << endl;
                continue;
            }
            inSS >> N;
            if (inSS.fail() || N <= 0) {
                outSS << "Error, Invalid input: " << newLine << endl;
                continue;
            }
            test =  "";
            inSS >> test;
            if (test[0] != '\0') {
                outSS << "Error, Invalid input: " << newLine << endl;
                continue;
            }
            outSS << indicator << " " << k << " " << j << " " << N << ": " << records.outliers(k,j,N) << endl;
        }
        else {
            outSS << "Error, Invalid input: " << newLine << endl;
        }
    }
    // cout << outSS.str() << endl;
    inFS.close();
    ofstream ofSS("result.data");
    string outString = outSS.str();
    ofSS << outString;
    ofSS.close();
}
