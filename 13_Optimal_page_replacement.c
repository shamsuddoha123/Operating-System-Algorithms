#include <stdio.h>

int main(void)
{
    int string[20], frames[20];
    int no_pages, no_frames;
    int i, j, k;

    int page_hits = 0, page_faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &no_pages);

    printf("Enter page reference string:\n");
    for (i = 0; i < no_pages; i++)
        scanf("%d", &string[i]);

    printf("Enter number of frames: ");
    scanf("%d", &no_frames);

    for (i = 0; i < no_frames; i++)
        frames[i] = -1;

    for (i = 0; i < no_pages; i++)
    {
        int symbol = string[i];
        int flag = 0; // Check if page is already in frame. If yes, set flag=1

        for (j = 0; j < no_frames; j++)
        {
            if (frames[j] == symbol)// Page is already in frame
            {
                flag = 1;
                page_hits++;
                break;
            }
        }

        printf("\nPage: %d  Frame: ", symbol);

        if (flag == 0)
        {
            int pos = -1, farthest = i + 1; // To find the page to replace

            for (j = 0; j < no_frames; j++)
            {
                for (k = i + 1; k < no_pages; k++)// Look for next use of frame[j]
                {
                    if (frames[j] == string[k])
                        break;
                }

                if (k == no_pages)
                {
                    pos = j;
                    break;
                }

                if (k > farthest)
                {
                    farthest = k;
                    pos = j;
                }
            }

            if (pos == -1)
                pos = 0; // If no page is found to replace, replace the first one

            frames[pos] = symbol;
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