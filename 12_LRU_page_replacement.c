#include <stdio.h>

int main(void)
{
    int string[20], frames[20], recent[20];
    int no_pages, no_frames;
    int i, j, k;

    int page_hits = 0, page_faults = 0;
    int time = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < no_pages; i++)
        scanf("%d", &string[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_frames);

    for (i = 0; i < no_frames; i++)
    {
        frames[i] = -1;
        recent[i] = 0;
    }

    for (i = 0; i < no_pages; i++)
    {
        int symbol = string[i];
        int flag = 0;

        for (j = 0; j < no_frames; j++)
        {
            if (frames[j] == symbol)
            {
                flag = 1;
                page_hits++;
                recent[j] = ++time; // Update recent time
                break;
            }
        }

        printf("\nPage: %d  Frame: ", symbol);

        if (flag == 0)
        {
            int lru = 0;
            for (j = 1; j < no_frames; j++)
            {
                if (recent[j] < recent[lru]) // Find least recently used page
                    lru = j; // Update LRU index
            }
            frames[lru] = symbol;
            recent[lru] = ++time; // Update recent time for replaced page
            page_faults++;
        }

        for (j = 0; j < no_frames; j++)
            printf("%d ", frames[j]);
    }

    printf("\n\nPage Hits: %d", page_hits);
    printf("\nPage Faults: %d", page_faults);
    printf("\nHit Ratio: %.2f", (float)page_hits / no_pages);
    printf("\nPage Fault Ratio: %.2f\n", (float)page_faults / no_pages);

    return 0;
}