#include <stdio.h>
#include <stdbool.h>

#define SIZE 3
int buffer[SIZE];
int in = 0, out = 0, count = 0;

// Peterson's variables
bool flag[2] = {false, false};  // flag[0] = producer, flag[1] = consumer
int turn;                       // whose turn to enter

// ---- Critical Section controlled produce ----
void produce(int item)
{
    // Entry Section for producer (process 0)
    flag[0] = true;
    turn = 1;
    while (flag[1] && turn == 1);

    // Critical Section
    if (in == SIZE)   // no circular buffer, just stops when full
    {
        printf("Buffer Full!\n");
    }
    else
    {
        buffer[in] = item;
        in++;
        count++;
        printf("Produced: %d\n", item);
    }

    // Exit Section
    flag[0] = false;
}

// ---- Critical Section controlled consume ----
void consume()
{
    // Entry Section for consumer (process 1)
    flag[1] = true;
    turn = 0;
    while (flag[0] && turn == 0);

    // Critical Section
    if (out == in)   // means nothing left to consume
    {
        printf("Buffer Empty!\n");
    }
    else
    {
        int item = buffer[out];
        out++;
        count--;
        printf("Consumed: %d\n", item);
    }

    // Exit Section
    flag[1] = false;
}

int main()
{
    produce(10);
    produce(20);
    consume();
    produce(30);
    produce(40);  // should trigger "Buffer Full!"
    consume();
    consume();
    consume();    // should trigger "Buffer Empty!"
    return 0;
}