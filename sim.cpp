#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int memorySize = 0, pageSize = 0;
    int pageSizeChoice;
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

    ifstream inFile(workloadFilename);
    if (inFile.is_open())
    {
        // TODO
        inFile.close();
    }
    else
    {
        cerr << "failed to open " << workloadFilename << " for reading!" << endl;
        return 1;
    }

    return 0;
}