#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 100 // Maximum allowed buffer size

int buffer[MAX_BUFFER];
int BUFFER_SIZE;   // User-defined buffer size
int in = 0;        // Index for producer
int out = 0;       // Index for consumer

// Semaphores
int mutex = 1; // Controls access to the critical section (buffer)
int full = 0;  // Counts the number of filled slots in the buffer
int empty;     // Counts the number of empty slots in the buffer

// wait() and signal() functions for semaphores
int wait(int s) {
    while (s <= 0); // Busy-wait if semaphore value is not positive
    return --s;
}

int signal(int s) {
    return ++s;
}

void producer() {
    int item;
    printf("Enter item to produce: ");
    scanf("%d", &item);

    // detect buffer overflow
    if (empty == 0) {
        printf("Buffer OVERFLOW! Cannot produce because buffer is full.\n");
        return;
    }

    empty = wait(empty); // Decrement empty count
    mutex = wait(mutex); // Acquire lock

    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    printf("Producer produced item %d\n", item);

    mutex = signal(mutex); // Release lock
    full = signal(full);   // Increment full count
}

void consumer() {
    int item;

    // detect buffer underflow
    if (full == 0) {
        printf("Buffer UNDERFLOW! Cannot consume because buffer is empty.\n");
        return;
    }

    full = wait(full);   // Decrement full count
    mutex = wait(mutex); // Acquire lock

    item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    printf("Consumer consumed item %d\n", item);

    mutex = signal(mutex); // Release lock
    empty = signal(empty); // Increment empty count
}

int main() {
    int choice;

    printf("Enter custom buffer size (1 to %d): ", MAX_BUFFER);
    scanf("%d", &BUFFER_SIZE);

    empty = BUFFER_SIZE; // Initialize empty slots

    printf("Producer-Consumer Problem using Semaphores\n");
    while (1) {
        printf("\n1. Produce\n2. Consume\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                producer();
                break;
            case 2:
                consumer();
                break;
            case 3:
                exit(0);// Exit the program
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}