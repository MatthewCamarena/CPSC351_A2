#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

struct processes
{
public: 
	int id, arrivTime, lifeTime, memPieces, totalMem;
	
};

void showQ(queue <int> tempQ)
{
    queue <int> que = tempQ;
    while (!que.empty())
    {
        cout << " " << que.front();
        que.pop();
    }

}

int main()
{
    int memorySize = 0, pageSize = 0;
    int pageSizeChoice, processAmt;
    int tempInt = 0;
    int currTime = 0;

    queue <int> processQ;

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
    	
    	/*******************************************************************************************
		Memory Queue & Manager 
		Will do the manage the memory of the processes until completed or time reaches 100,000
		********************************************************************************************/
	int processIndex = 0;
	bool tempBool = true;
	do 
	{
	
	
	if (currTime == process[processIndex].arrivTime)
	{
		cout << "t = " << currTime << ": " <<  "Process " << (processIndex+1) << " arrives" << endl;
		//TODO: insert into queue
		processQ.push(processIndex+1);
		cout << "       " << "Input Queue: " << "[";
		showQ(processQ);
		cout << "]" << endl;
		processIndex++;
		while (tempBool)
		{
			if (currTime == process[processIndex].arrivTime)
			{
				cout << "       " <<  "Process " << (processIndex+1) << " arrives" << endl;
				cout << "       " << "Input Queue: " << "[]" << endl;
				processIndex++;
			}
			else 
			{
				tempBool = false;
			}	
	
		}
		tempBool = true;
	}

		currTime++;
	}
	while((processAmt != 0) && (currTime < 100001));
   

        inFile.close();
    }


    else
    {
        cerr << "failed to open " << workloadFilename << " for reading!" << endl;
        return 1;
    }




    return 0;
}

