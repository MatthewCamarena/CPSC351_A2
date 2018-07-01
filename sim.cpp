#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;

struct processes
{
public: 
	int id, arrivTime, lifeTime, memPieces, totalMem, entrdMemTime;
	
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

class MemoryClass
{
	public:

	MemoryClass()
	{
		turnaroundTime = 0;
	}

	
	~MemoryClass()
	{
		delete[] mainMemoryPro;
		delete[] mainMemoryPge;
	}

	void addSizes(int memSize, int pgeSize)
	{
		memorySize = memSize;
		pageSize = pgeSize;
		pageTotal = memSize/pgeSize;
		mainMemoryPro = new int[pageTotal];
		mainMemoryPge = new int[pageTotal];
		currMemSize = memSize;
		for(int i = 0; i < pageTotal; i++)
		{
			mainMemoryPro[i] = 0;
			mainMemoryPge[i] = 0;
		}

	}

	bool checkFit(int neededSize)
	{
		if (currMemSize >= neededSize)
			return true;
		else
			return false;
	}

	void insertMem(int memSize, int id, int currTime)
	{
		
		int proMemory = memSize;
		int pgeCounter = 1;
		
		for(int i = 0; i < pageTotal; i++)
		{
			if(proMemory > 0)
			{
				if(mainMemoryPro[i] == 0)
				{
					mainMemoryPro[i] = id;
					mainMemoryPge[i] = pgeCounter;
					pgeCounter++;
					proMemory -= pageSize;
					currMemSize -= pageSize;
					
				}
			}
			else 
			{
				break;
			}
		}
		
		processInMem.push_back(id);
		turnaroundTime -= currTime;
		

	}
	void removeFromMem(int id, int currTime)
	{
		for(int i = 0; i < pageTotal; i++)
		{
			if(mainMemoryPro[i] == id)
			{
				mainMemoryPro[i] = 0;
				mainMemoryPge[i] = 0;
				currMemSize += pageSize;
			}
		}
		turnaroundTime += currTime;
	}

	void printMemoryMap()
	{
		int tempIndex = 0;

		if (currMemSize == memorySize)
		{
			cout << "		0-" << (memorySize-1) << ":  Free frame(s)" << endl;
		}
		else
		{

		for(int i = 0; i < pageTotal; i++)
		{
			if(mainMemoryPro[i] == 0)
			{
				tempIndex = i;
				do
				{
					i++;
				}
				while(mainMemoryPro[i+1] == 0 && i+1 < pageTotal);

				cout << "		" << (tempIndex * pageSize) <<  "-" << (((i+1)*pageSize)-1) << ": Free frame(s)" << endl;
			}
			else 
			{
				cout << "		" << (i* pageSize) << "-" << ((i* pageSize) + pageSize - 1);
				cout << ": Process" << mainMemoryPro[i] << ", " << "Page " << mainMemoryPge[i] << endl;

			}
		}


		}
	}

	
	bool checkTime(int currTime, int processTime, int entrdTime)
	{
		if (currTime == (entrdTime + processTime))
			return true;
		else
			return false;
	}

	void checkStatus(int currTime, processes process[])
	{
		
		bool first = true;
		
		
		for(it = processInMem.begin(); it != processInMem.end(); it++)
		{
			
			if(checkTime(currTime, process[(*it)-1].lifeTime, process[(*it)-1].entrdMemTime))
			{
				
				if (first == true)
				{
					cout << "t = " << currTime << ": Process " << *it << " completes" << endl;
					cout << "Memory Map: \n";
					removeFromMem(*it, currTime);
					printMemoryMap();
					cout << endl;
					first = false;
					
				}
				else 
				{
					cout << "		" << "Process " << *it << " completes"  << endl;
					cout << "Memory Map: \n";
					removeFromMem(*it, currTime);
					printMemoryMap();
					cout << endl;
					
				}
			

			}
		}

	}
	
	int getTurnTime()
	{
		return turnaroundTime;
	}

	int turnaroundTime;
	int memorySize;
	int pageSize;
	int pageTotal;
	int currMemSize; // fix in remove
	vector<int> processInMem;
	vector<int> :: iterator it;
	int *mainMemoryPro;
	int *mainMemoryPge;

};





int main()
{
    int memorySize = 0, pageSize = 0;
    int pageSizeChoice, processAmt;
    int tempInt = 0;
    int currTime = 0;

    queue <int> processQ;
    MemoryClass mainMemory;

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

    mainMemory.addSizes(memorySize, pageSize);
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
		/*******************************************************************************************
		Queue

		********************************************************************************************/
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
				processQ.push(processIndex+1);
				cout << "       " <<  "Process " << (processIndex+1) << " arrives" << endl;
				cout << "       " << "Input Queue: " << "[";
				showQ(processQ);
				cout << "]" << endl;
				processIndex++;
			}
			else 
			{
				tempBool = false;
			}	
	
		}
		tempBool = true;
	}

	    /*******************************************************************************************
		Memory Manager
		
		********************************************************************************************/

	if(!processQ.empty())
	{

		//Check if room for first process in Q
		
		if(mainMemory.checkFit(process[processQ.front()].totalMem))
		{
			

			mainMemory.insertMem(process[processQ.front()-1].totalMem, processQ.front(), currTime);
			process[processQ.front()-1].entrdMemTime = currTime;

			cout << "	MM moves Process " << processQ.front() << " to memory" << endl;
			processQ.pop();
			cout << "       " << "Input Queue: " << "[";
			showQ(processQ);
			cout << "]" << endl;
			cout << "	Memory Map: \n";
			mainMemory.printMemoryMap(); 
			cout << endl;
			
		}




	}
	
	
	

	// I need to check if a process is complete

	mainMemory.checkStatus(currTime, process);

	




		currTime++;
	}
	while((processAmt != 0) && (currTime < 100001));
   
	double turnTime = mainMemory.getTurnTime()/8;
	cout << "Turnaround Time: " << turnTime << endl;
        inFile.close();
    }


    else
    {
        cerr << "failed to open " << workloadFilename << " for reading!" << endl;
        return 1;
    }




    return 0;
}

