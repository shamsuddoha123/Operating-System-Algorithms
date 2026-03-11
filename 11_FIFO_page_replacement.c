#include <stdio.h>

int main(void)
{
    int string[20], frames[20];
    int no_pages, no_frames;
    int i, j;

    int index = -1;
    int page_hits = 0, page_miss = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < no_pages; i++)
        scanf("%d", &string[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_frames);

    /* Initialize frames */
    for (i = 0; i < no_frames; i++)
        frames[i] = -1;

    /* FIFO Logic */
    for (i = 0; i < no_pages; i++)
    {
        int symbol = string[i];
        int flag = 0;

        for (j = 0; j < no_frames; j++)
        {
            if (symbol == frames[j])
            {
                flag = 1;
                break;
            }
        }

        printf("\nPage: %d  Frame: ", symbol);

        if (flag == 1)
        {
            page_hits++;
        }
        else
        {
            index = (index + 1) % no_frames; // FIFO replacement
            frames[index] = symbol;
            page_miss++;
        }

        for (j = 0; j < no_frames; j++)
            printf("%d ", frames[j]);
    }

    printf("\n\nPage Hits: %d", page_hits);
    printf("\nPage Faults: %d", page_miss);
    printf("\nHit Ratio: %.2f%%", ((float)page_hits*100) / no_pages);
    printf("\nPage Fault Ratio: %.2f%%\n", ((float)page_miss*100) / no_pages);

    return 0;
}