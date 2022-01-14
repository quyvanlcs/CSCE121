#include <iostream>
#include "CellDatabase.h"

using namespace std;

int main(int argc, char** argv) 
{
    if (argc < 3) 
    {
        cout << "Usage: " << argv[0] << " data_file query_file" << endl;
		    return 1;
    } 
    else 
    {
        CellDatabase database;
        database.loadData(argv[1]);
		    database.performQuery(argv[2]); 
	  	  database.outputData(argv[1]); 
    }

    return 0;


    // string filename = "cellsInfo.csv";
    // CellDatabase newData;
    // newData.loadData(filename);
    
        // CellDatabase database;
        // database.loadData("cellsInfo.csv");
		// database.performQuery("queries.data"); 
	    // database.outputData("cellsInfo.csv"); 
        // cout << "Outliners" << endl;
        // cout << database.records.outliers(20,1,20) << endl;

    // Node* walk = database.records.getHead();
    // int count = 1;
    // while(walk != nullptr) {
    //     cout << count << ": " << walk->data.id << endl;
    //     walk = walk->next;
    //     count++;
    // }

    // LinkedList ldata(newData.records);
    // cout << "ldata" << endl;
    // cout << ldata.print() << endl;



    // LinkedList l1;
    // l1.insert("316185979531189382876779845289900450466",16,811.054,374.512,3610.28,368.183,380.84,3603.63,3616.93);
    // l1.insert("6152311778354223852005374274263046189",15,545.334,316.245,3478.28,307.864,324.625,3472.54,3484.01);
    // l1.insert("259824986546725149761276003661126817431",13,1214.56,413.095,5910.62,405.097,421.092,5901,5920.25);
    // l1.insert("80719596629301901340444638136238672607",12,297.298,416.34,6078.29,412.765,419.915,6074.23,6082.35);
    // l1.insert("248517492611370834464009662840236881305",12,1489.93,410.022,6045.08,401.209,418.835,6033.63,6056.54);
    // l1.insert("102664563492900048462363937849459428087",12,825.112,416.767,6086.12,412.441,421.092,6076.72,6095.53);
    // l1.insert("248024456595654429600598295124535343200",12,460.431,416.983,6039.9,412.873,421.092,6033.95,6045.85);
    // l1.insert("248517492611370834464009662840236881305",12,1489.93,410.022,6045.08,401.209,418.835,6033.63,6056.54);
    // cout << "Let see list 1" << endl;
    // cout << l1.print() << endl;
    // cout << "Average: " << l1.average(12) << endl;
    // cout << "Outliers: " << l1.outliers(20, 1, 0) << endl;
    // // cout << "###############################################################" << endl;
    // cout << "" << endl;
    // // Unit test copy operator
    // LinkedList l2;
    // l2 = l1;
    // cout << "Let see list 2" << endl;
    // cout << l2.print() << endl;


    //Unit test copy constructor
    // LinkedList l3(l1);
    // cout << "Let see list 3" << endl;
    // cout << "l3 head: " << endl;
    // cout << l3.getHead()->data.id << endl;
    // cout << "l3 head next" << endl;
    // cout << l3.getHead()->next->data.id << endl;
    // cout << l3.print() << endl;   




}
