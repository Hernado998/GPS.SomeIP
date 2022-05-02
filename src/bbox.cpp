#include "bbox.h"

using namespace bbox;
using namespace std;
string black_box::getTrackingFile(){
    ifstream my_file;
    string myLine;
    my_file.open("bbox.txt");
    string s="";
    if(my_file.is_open())
    {
        // Keep reading the file
        while(getline(my_file, myLine))
        {
            // print the line on the standard output
            cout << myLine << endl;
            s+=myLine+"\n";
        }
        my_file.close();    
    }
    else
    {
        cout << "Unable to open the history file!"<<endl;
    }
    return s;
}
void black_box::addToTrackingFile(string data){
    ofstream outfile ("bbox.txt", ios_base::app);
    outfile << data << endl;
}

void black_box::cleanTrackingFile(){
    int status;
    status = remove("bbox.txt");
    if(status==0)
        cout<<"\nFile Deleted Successfully!";
    else
        cout<<"\nError Occurred!";
    cout<<endl;
    ofstream MyFile("bbox.txt");
}

