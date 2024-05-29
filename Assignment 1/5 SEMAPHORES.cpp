#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>
#include <chrono>

using namespace std;

// Shared buffer for Producer-Consumer problem
vector<int> buffer;
const int BUFFER_SIZE = 5;
binary_semaphore mutex(1);                // Mutex semaphore for mutual exclusion
counting_semaphore<BUFFER_SIZE> empty(BUFFER_SIZE); // Semaphore to count empty slots in buffer
counting_semaphore<0> full(0);            // Semaphore to count filled slots in buffer

// Producer function
void producer(int id) {
    while (true) {
        int item = rand() % 100;           // Produce an item
        empty.acquire();                   // Wait for empty slot
        mutex.acquire();                   // Enter critical section
        if (buffer.size() < BUFFER_SIZE) {
            buffer.push_back(item);        // Add item to buffer
            cout << "Producer " << id << " produced item " << item << endl;
        }
        mutex.release();                   // Exit critical section
        full.release();                    // Signal that buffer is not empty
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate production time
    }
}

// Consumer function
void consumer(int id) {
    while (true) {
        full.acquire();                    // Wait for filled slot
        mutex.acquire();                   // Enter critical section
        if (!buffer.empty()) {
            int item = buffer.back();      // Consume item from buffer
            buffer.pop_back();
            cout << "Consumer " << id << " consumed item " << item << endl;
        }
        mutex.release();                   // Exit critical section
        empty.release();                   // Signal that buffer has empty slot
        this_thread::sleep_for(chrono::milliseconds(150)); // Simulate consumption time
    }
}

// Shared resources for Reader-Writer problem
int sharedData = 0;                       // Shared data to be read and written
int readerCount = 0;                      // Number of readers currently reading
binary_semaphore rw_mutex(1);             // Semaphore for read-write mutual exclusion
binary_semaphore reader_mutex(1);         // Semaphore for reader count protection

// Reader function
void reader(int id) {
    while (true) {
        reader_mutex.acquire();            // Protect reader count modification
        readerCount++;
        if (readerCount == 1) {
            rw_mutex.acquire();            // If first reader, acquire rw_mutex
        }
        reader_mutex.release();

        cout << "Reader " << id << " read shared data " << sharedData << endl;

        reader_mutex.acquire();
        readerCount--;
        if (readerCount == 0) {
            rw_mutex.release();            // If last reader, release rw_mutex
        }
        reader_mutex.release();
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate reading time
    }
}

// Writer function
void writer(int id) {
    while (true) {
        rw_mutex.acquire();                // Acquire rw_mutex to write
        sharedData = rand() % 100;         // Write data
        cout << "Writer " << id << " wrote shared data " << sharedData << endl;
        rw_mutex.release();                // Release rw_mutex after writing
        this_thread::sleep_for(chrono::milliseconds(200)); // Simulate writing time
    }
}

// Shared resources for Dining Philosophers problem
const int NUM_PHILOSOPHERS = 5;
binary_semaphore chopsticks[NUM_PHILOSOPHERS] = {1, 1, 1, 1, 1}; // Semaphores for chopsticks

// Philosopher function
void philosopher(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    while (true) {
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate thinking time

        chopsticks[left].acquire();        // Acquire left chopstick
        chopsticks[right].acquire();       // Acquire right chopstick

        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); // Simulate eating time

        chopsticks[right].release();       // Release right chopstick
        chopsticks[left].release();        // Release left chopstick
    }
}

// Function to demonstrate Producer-Consumer problem
void demonstrateProducerConsumer() {
    thread producers[2], consumers[2];
    for (int i = 0; i < 2; i++) {
        producers[i] = thread(producer, i + 1);  // Create producer threads
        consumers[i] = thread(consumer, i + 1);  // Create consumer threads
    }
    for (int i = 0; i < 2; i++) {
        producers[i].join();                      // Wait for producer threads to finish
        consumers[i].join();                      // Wait for consumer threads to finish
    }
}

// Function to demonstrate Reader-Writer problem
void demonstrateReaderWriter() {
    thread readers[3], writers[2];
    for (int i = 0; i < 3; i++) {
        readers[i] = thread(reader, i + 1);       // Create reader threads
    }
    for (int i = 0; i < 2; i++) {
        writers[i] = thread(writer, i + 1);       // Create writer threads
    }
    for (int i = 0; i < 3; i++) {
        readers[i].join();                        // Wait for reader threads to finish
    }
    for (int i = 0; i < 2; i++) {
        writers[i].join();                        // Wait for writer threads to finish
    }
}

// Function to demonstrate Dining Philosophers problem
void demonstrateDiningPhilosophers() {
    thread philosophers[NUM_PHILOSOPHERS];
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i] = thread(philosopher, i + 1); // Create philosopher threads
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philosophers[i].join();                     // Wait for philosopher threads to finish
    }
}

int main() {
    int choice;
    cout << "Choose a problem to demonstrate:" << endl;
    cout << "1. Producer-Consumer" << endl;
    cout << "2. Reader-Writer" << endl;
    cout << "3. Dining Philosophers" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            demonstrateProducerConsumer();
            break;
        case 2:
            demonstrateReaderWriter();
            break;
        case 3:
            demonstrateDiningPhilosophers();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please choose a valid option." << endl;
    }

    return 0;
}
