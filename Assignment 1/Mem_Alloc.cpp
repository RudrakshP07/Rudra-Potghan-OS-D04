#include <iostream>
using namespace std;

// Function to perform First Fit memory allocation
void firstFit(int blockSize[], int blockNo, int processSize[], int processNo) {
    int allocation[10], flags[10];

    // Initialize allocation and flags arrays
    for(int i = 0; i < 10; i++) {
        flags[i] = 0;          // 0 indicates the block is free
        allocation[i] = -1;    // -1 indicates no process is allocated to the block
    }

    // Allocate memory to processes
    for(int i = 0; i < processNo; i++) {
        for(int j = 0; j < blockNo; j++) {
            if(flags[j] == 0 && blockSize[j] >= processSize[i]) {
                allocation[j] = i;   // Allocate block j to process i
                flags[j] = 1;        // Mark block j as allocated
                break;
            }
        }
    }

    // Display allocation result
    cout << "\nFirst Fit Allocation:";
    cout << "\nBlock no.\tSize\t\tProcess No.\t\tSize";
    for(int i = 0; i < blockNo; i++) {
        cout << "\n" << i+1 << "\t\t" << blockSize[i] << "\t\t";
        if(flags[i] == 1)
            cout << allocation[i] + 1 << "\t\t\t" << processSize[allocation[i]];
        else
            cout << "Not allocated\t\tN/A";
    }
    cout << endl;
}

// Function to perform Best Fit memory allocation
void bestFit(int blockSize[], int blockNo, int processSize[], int processNo) {
    int allocation[10], flags[10];

    // Initialize allocation and flags arrays
    for(int i = 0; i < 10; i++) {
        flags[i] = 0;
        allocation[i] = -1;
    }

    // Allocate memory to processes
    for(int i = 0; i < processNo; i++) {
        int bestIdx = -1;
        for(int j = 0; j < blockNo; j++) {
            if(flags[j] == 0 && blockSize[j] >= processSize[i]) {
                if(bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;   // Find the best fitting block
                }
            }
        }
        if(bestIdx != -1) {
            allocation[bestIdx] = i;
            flags[bestIdx] = 1;
        }
    }

    // Display allocation result
    cout << "\nBest Fit Allocation:";
    cout << "\nBlock no.\tSize\t\tProcess No.\t\tSize";
    for(int i = 0; i < blockNo; i++) {
        cout << "\n" << i+1 << "\t\t" << blockSize[i] << "\t\t";
        if(flags[i] == 1)
            cout << allocation[i] + 1 << "\t\t\t" << processSize[allocation[i]];
        else
            cout << "Not allocated\t\tN/A";
    }
    cout << endl;
}

// Function to perform Worst Fit memory allocation
void worstFit(int blockSize[], int blockNo, int processSize[], int processNo) {
    int allocation[10], flags[10];

    // Initialize allocation and flags arrays
    for(int i = 0; i < 10; i++) {
        flags[i] = 0;
        allocation[i] = -1;
    }

    // Allocate memory to processes
    for(int i = 0; i < processNo; i++) {
        int worstIdx = -1;
        for(int j = 0; j < blockNo; j++) {
            if(flags[j] == 0 && blockSize[j] >= processSize[i]) {
                if(worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;  // Find the worst fitting block
                }
            }
        }
        if(worstIdx != -1) {
            allocation[worstIdx] = i;
            flags[worstIdx] = 1;
        }
    }

    // Display allocation result
    cout << "\nWorst Fit Allocation:";
    cout << "\nBlock no.\tSize\t\tProcess No.\t\tSize";
    for(int i = 0; i < blockNo; i++) {
        cout << "\n" << i+1 << "\t\t" << blockSize[i] << "\t\t";
        if(flags[i] == 1)
            cout << allocation[i] + 1 << "\t\t\t" << processSize[allocation[i]];
        else
            cout << "Not allocated\t\tN/A";
    }
    cout << endl;
}

int main() {
    int blockSize[10], processSize[10], blockNo, processNo, choice;

    // Input number of blocks
    cout << "Enter no. of blocks: ";
    cin >> blockNo;

    // Input size of each block
    cout << "\nEnter size of each block: ";
    for(int i = 0; i < blockNo; i++)
        cin >> blockSize[i];

    // Input number of processes
    cout << "\nEnter no. of processes: ";
    cin >> processNo;

    // Input size of each process
    cout << "\nEnter size of each process: ";
    for(int i = 0; i < processNo; i++)
        cin >> processSize[i];

    // Display menu for memory allocation strategies
    cout << "\nMemory Allocation Strategies";
    cout << "\n1. First Fit";
    cout << "\n2. Best Fit";
    cout << "\n3. Worst Fit";
    cout << "\n4. Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;

    // Execute the chosen memory allocation strategy
    if (choice == 1) {
        firstFit(blockSize, blockNo, processSize, processNo);
    } else if (choice == 2) {
        bestFit(blockSize, blockNo, processSize, processNo);
    } else if (choice == 3) {
        worstFit(blockSize, blockNo, processSize, processNo);
    } else if (choice == 4) {
        cout << "Exiting...";
    } else {
        cout << "Invalid choice! Please choose a valid option.";
    }

    return 0;
}
