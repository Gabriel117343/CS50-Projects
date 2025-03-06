#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Check for proper usage: exactly one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card file (e.g., card.raw)
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Buffer for a block of data (512 bytes)
    uint8_t buffer[BLOCK_SIZE];

    // File pointer for output JPEG files
    FILE *outptr = NULL;

    // Filename for JPEG file (ej: "000.jpg")
    char filename[8];
    int file_count = 0;

    // Read 512-byte blocks until end-of-file
    while (fread(buffer, sizeof(uint8_t), BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        // Check if the block is the start of a new JPEG >
        // A JPEG block begins with: 0xff 0xd8 0xff and a fourth byte starting with 0xe (ej, 0xe0 to
        // 0xef)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If already found a JPEG, close the previous filee
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Create a new filename for the JPEG (example: 000.jpg, 001.jpg, etc.)
            sprintf(filename, "%03i.jpg", file_count);
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", filename);
                fclose(inptr);
                return 3;
            }
            file_count++;
        }

        // If we have an open output file, write this block to it
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), BLOCK_SIZE, outptr);
        }
    }

    // Close any open file pointers
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    fclose(inptr);

    return 0;
}
