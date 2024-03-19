#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

// Structure to represent a process
struct Process 
{
    string name;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int arrivalTime;
    int completionTime;
};

// Function to perform FCFS scheduling
void FCFS(vector<Process>& processes) 
{
    int currentTime = 0;
    for (int i = 0; i < processes.size(); i++) 
    {
        // If the current time is before the arrival time of the process, update the current time
        if (currentTime < processes[i].arrivalTime) 
        {
            currentTime = processes[i].arrivalTime;
        }
        // Update waiting time
        processes[i].waitingTime = currentTime - processes[i].arrivalTime;
        // Update turnaround time
        processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;
        // Update completion time
        processes[i].completionTime = currentTime + processes[i].burstTime;
        // Update current time
        currentTime = processes[i].completionTime;
    }
}

// Comparator function for sorting processes based on arrival time
bool compareArrivalTime(const Process& a, const Process& b) 
{
    return a.arrivalTime < b.arrivalTime;
}

int main() 
{
    // Create a vector to store the processes
    int numProcess;
    cout << "Enter the number of processes: ";
    cin >> numProcess;
    vector<Process> processes(numProcess);

    // Input process details
    for (int i = 0; i < numProcess; i++) {
        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;

        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;

        processes[i].name = "P" + to_string(i + 1);
    }

    // Sort processes based on arrival time
    sort(processes.begin(), processes.end(), compareArrivalTime);

    // Perform FCFS scheduling
    FCFS(processes);

  // Print the results
  cout << "Process\t AT\t\tBT\t\tWT\t\tTAT\n";
  for (int i = 0; i < numProcess; i++) {
      cout << processes[i].name << "\t\t" << processes[i].burstTime << "\t\t" << processes[i].arrivalTime << "\t\t" << processes[i].waitingTime << "\t\t" << processes[i].turnaroundTime << endl;
  }


    return 0;
}
