#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // assign the name of the input memory file to memory
    char *memory = argv[1];
    // size of the block that will be read and written
    const int BLOCK_SIZE = 512;
    // open memory card files
    FILE *input = fopen(memory, "r");
    if (input == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }
    // unsigned char buffer[BLOCK_SIZE];
    BYTE buffer[BLOCK_SIZE];
    // pointer to output file
    FILE *output = NULL;
    // fileName variable
    char image[8];
    // number of image files created
    int count = 0;

    // search until the start of a jpg file is found
    // while(fread(buffer, BLOCK_SIZE, 1, input) == 1)
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // find the beginning of an jpg if it starts with oxff then oxd8 then oxff and then from oxeo-oxef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close image file if one images bytes are done and the file has been created
            if (count > 0)
            {
                fclose(output);
            }
            // make name for nth image starting from 000 and adding 1
            sprintf(image, "%03i.jpg", count);

            // open nth image file
            output = fopen(image, "w");
            // if cannot open the output file
            if (output == NULL)
            {
                printf("Could not create.\n");
                return 3;
            }
            // increment number of image files already created
            count++;
        }
        // write to image file if one exists
        if (output != NULL)
        {
            // write to image file
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    // close image file
    fclose(output);
    // close input file
    fclose(input);
    return 0;
}