#include <iostream>
#include <fstream>

using namespace std;

struct processes
{
public: 
	int id, arrivTime, lifeTime, memPieces, totalMem;
	
};


int main()
{
    int memorySize = 0, pageSize = 0;
    int pageSizeChoice, processAmt;
    int tempInt = 0;
    int currTime = 0;

    string workloadFilename;

    cout << "Enter memory size (Kbytes): ";
    cin >> memorySize;
    cout << "Enter page size (1: 100, 2: 200, 3: 300): ";
    cin >> pageSizeChoice;
    cout << "Enter workload filename: ";
    cin >> workloadFilename;

    if (pageSizeChoice <= 1)
        pageSize = 100;
    else if (pageSizeChoice == 2)
        pageSize = 200;
    else
        pageSize = 300;


/*******************************************************************************************
Read in all the data from the text file and then store it all into a struct

********************************************************************************************/
    ifstream inFile(workloadFilename);
    if (inFile.is_open())
    {
        // TODO
        //First Integer in the file is the Number of defined Processes
    	inFile >> processAmt;

    	// Create an array of the struct to store all processes information
    	processes process[processAmt];

    	// Load all info from txt into the struct
    	for(int i = 0; i < processAmt; i++)
    	{
    		inFile >> process[i].id >> process[i].arrivTime >> process[i].lifeTime >>process[i].memPieces;
    		process[i].totalMem = 0;
    		for (int j = 0; j < process[i].memPieces; j++)
    		{
    			tempInt = 0;
    			inFile >> tempInt;
    			process[i].totalMem += tempInt;
    		}
    	}
    	
   
        inFile.close();
    }
    else
    {
        cerr << "failed to open " << workloadFilename << " for reading!" << endl;
        return 1;
    }

/*******************************************************************************************
Memory Queue & Manager 
Will do the processes until completed or time reaches 100,000
********************************************************************************************/


do 
{

currTime++;
}
while((processAmt != 0) && (currTime < 100001));


    return 0;
}

