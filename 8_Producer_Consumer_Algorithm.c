#include <stdio.h>

#define SIZE 3
int buffer[SIZE];
int in=0, out=0, count=0;

void produce(int item)
{
    if(in == SIZE)
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
}

void consume()
{
    if(out == in)
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
}

int main()
{
    produce(10);
    produce(20);
    consume();
    produce(30);
    produce(40);
    consume();
    consume();
    consume();
    return 0;
}