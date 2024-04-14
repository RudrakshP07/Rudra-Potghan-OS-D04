#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Structure to represent a process
struct Process {
  string name;
  int burstTime;
  int waitingTime;
  int turnaroundTime;
  int arrivalTime; // Arrival time is needed for varying arrival time scheduling
  int completionTime;
  int remainingTime; // Used for Round Robin
};

// Function to perform FCFS scheduling for 0 Arrival Time
void FCFS_0ArrivalTime(vector<Process> &processes) {
  int currentTime = 0;
  for (int i = 0; i < processes.size(); i++) {
    // Update waiting time
    processes[i].waitingTime = currentTime;
    // Update turnaround time
    processes[i].turnaroundTime =
        processes[i].waitingTime + processes[i].burstTime;
    // Update completion time
    processes[i].completionTime = currentTime + processes[i].burstTime;
    // Update current time
    currentTime = processes[i].completionTime;
  }
}

// Comparator function for sorting processes based on arrival time
bool compareArrivalTime(const Process &a, const Process &b) {
  return a.arrivalTime < b.arrivalTime;
}

// Function to perform LJF scheduling
void LJF(vector<Process> &processes) {
  sort(processes.begin(), processes.end(),
       [](const Process &a, const Process &b) {
         return a.burstTime > b.burstTime;
       });

  FCFS_0ArrivalTime(
      processes); // LJF is essentially FCFS after sorting by burst time
}

// Function to perform SJF scheduling
void SJF(vector<Process> &processes) {
  sort(processes.begin(), processes.end(),
       [](const Process &a, const Process &b) {
         return a.burstTime < b.burstTime;
       });

  FCFS_0ArrivalTime(
      processes); // SJF is essentially FCFS after sorting by burst time
}

// Function to perform Round Robin scheduling
void RoundRobin(vector<Process> &processes, int timeQuantum) {
  int currentTime = 0;
  while (!processes.empty()) {
    bool allProcessesCompleted = true;
    for (auto &process : processes) {
      if (process.remainingTime > 0) {
        allProcessesCompleted = false;
        int executeTime = min(process.remainingTime, timeQuantum);
        process.remainingTime -= executeTime;
        currentTime += executeTime;
        process.completionTime = currentTime;
        if (process.remainingTime == 0) {
          // Calculate waiting time and turnaround time
          process.waitingTime =
              process.completionTime - process.arrivalTime - process.burstTime;
          process.turnaroundTime = process.completionTime - process.arrivalTime;
        }
      }
    }
    if (allProcessesCompleted)
      break;
  }
}

int main() {
  while (true) {
    // Prompt for scheduling technique choice
    int choice;
    cout << endl;
    cout << "Choose scheduling technique:\n";
    cout << "1. FCFS for Processes with 0 Arrival Time\n";
    cout << "2. Processes with Varying Arrival Time\n";
    cout << "Enter your choice (Enter 0 to exit): ";
    cin >> choice;

    switch (choice) {
    case 0:
      cout << endl;
      cout << "Exiting the program.\n";
      return 0;
    case 1: {
      // Prompt for scheduling algorithm for 0 arrival time
      int schedulingChoice;
      cout << endl;
      cout << "Choose scheduling algorithm for 0 Arrival Time:\n";
      cout << "1. FCFS\n";
      cout << "2. LJF\n";
      cout << "3. SJF\n";
      cout << "4. Round Robin\n";
      cout << endl;
      cout << "Enter your choice: ";
      cin >> schedulingChoice;

      // Create a vector to store the processes
      int numProcess;
      cout << "\nEnter the number of processes: ";
      cin >> numProcess;
      vector<Process> processes(numProcess);

      // Input process details (No need to ask for arrival time for 0 arrival
      // time scheduling)
      cout << endl;
      cout << "Enter Burst Time for each process:\n";
      for (int i = 0; i < numProcess; i++) {
        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].name = "P" + to_string(i + 1);
        processes[i].remainingTime =
            processes[i].burstTime; // Initialize remaining time
      }

      // Perform scheduling for 0 Arrival Time based on the chosen algorithm
      cout << endl;
      cout << "\nScheduling for 0 Arrival Time:\n";
      switch (schedulingChoice) {
      case 1:
        cout << "\nScheduling for 0 Arrival Time (FCFS):\n";
        FCFS_0ArrivalTime(processes);
        break;
      case 2:
        cout << "\nScheduling for 0 Arrival Time (LJF):\n";
        LJF(processes);
        break;
      case 3:
        cout << "\nScheduling for 0 Arrival Time (SJF):\n";
        SJF(processes);
        break;
      case 4:
        int timeQuantum;
        cout << "\nEnter the time quantum for Round Robin: ";
        cin >> timeQuantum;
        RoundRobin(processes, timeQuantum);
        break;
      default:
        cout << "Invalid choice!";
        return 1;
      }

      // Print the results (No need to display arrival time for 0 arrival time
      // scheduling)
      cout << "|\tProcess\t|\tBT\t|\tWT\t|\tTAT\t|\n";
      for (int i = 0; i < numProcess; i++) {
        cout << "|\t" << processes[i].name << "\t\t|\t"
             << processes[i].burstTime << "\t|\t" << processes[i].waitingTime
             << "\t|\t" << processes[i].turnaroundTime << "\t|\n";
      }

      // Print the Gantt chart
      cout << endl;
      cout << "\nGantt Chart:\n";
      int prevCompletionTime = 0;
      for (const auto &process : processes) {
        cout << "|";
        for (int i = 0; i < process.completionTime - prevCompletionTime; ++i) {
          cout << " " << process.name << " ";
        }
        prevCompletionTime = process.completionTime;
      }
      cout << "|" << endl;

      break;
    }
    case 2: {
      // Create a vector to store the processes
      int numProcess;
      cout << endl;
      cout << "\nEnter the number of processes: ";
      cin >> numProcess;
      vector<Process> processes(numProcess);

      // Input process details
      cout << endl;
      cout << "Enter Arrival Time and Burst Time for each process:\n";
      for (int i = 0; i < numProcess; i++) {
        cout << "Enter Arrival Time for Process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;

        cout << "Enter Burst Time for Process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        processes[i].name = "P" + to_string(i + 1);
        processes[i].remainingTime =
            processes[i].burstTime; // Initialize remaining time
      }

      // Sort processes based on arrival time for varying arrival time
      sort(processes.begin(), processes.end(), compareArrivalTime);

      // Perform scheduling for Varying Arrival Time (Ask user for scheduling
      // algorithm)
      cout << endl;
      cout << "\nScheduling for Varying Arrival Time:\n";
      cout << endl;
      cout << "Choose scheduling algorithm:\n";
      cout << "1. FCFS\n2. LJF\n3. SJF\n4. Round Robin\n";
      cout << endl;
      cout << "Enter your choice: ";
      cin >> choice;

      switch (choice) {
      case 1:
        FCFS_0ArrivalTime(processes);
        break;
      case 2:
        LJF(processes);
        break;
      case 3:
        SJF(processes);
        break;
      case 4:
        int timeQuantum;
        cout << "\nEnter the time quantum for Round Robin: ";
        cin >> timeQuantum;
        RoundRobin(processes, timeQuantum);
        break;
      default:
        cout << "Invalid choice!";
      }

      // Print the results for varying arrival time
      cout << endl;
      cout << "|\tProcess\t|\tAT\t|\tBT\t|\tWT\t|\tTAT\t|\n";
      for (int i = 0; i < numProcess; i++) {
        cout << "|\t" << processes[i].name << "\t\t|\t"
             << processes[i].arrivalTime << "\t|\t" << processes[i].burstTime
             << "\t|\t" << processes[i].waitingTime << "\t|\t"
             << processes[i].turnaroundTime << "\t|\n";
      }

      // Print the Gantt chart
      cout << endl;
      cout << "\nGantt Chart:\n";
      int prevCompletionTime = 0;
      for (const auto &process : processes) {
        cout << "|";
        for (int i = 0; i < process.completionTime - prevCompletionTime; ++i) {
          cout << " " << process.name << " ";
        }
        prevCompletionTime = process.completionTime;
      }
      cout << "|" << endl;

      break;
    }
    default:
      cout << "Invalid choice!";
    }
  }

  return 0;
}
