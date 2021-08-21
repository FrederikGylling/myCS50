#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE; // define BYTE as a data type
    int cnt = 0; // counter of created jpg files
    FILE *img = NULL; // initialize a variable for the jpg file
    BYTE buffer[512];


    // only allow proper command-line usage
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // check if file can be opened
    FILE *infile = fopen(argv[1], "r");
    if (infile == NULL)
    {
        printf("Can't open %s", argv[1]);
        return 1;
    }

    // fyi: could be allcoated as stack as well
    char *filename = malloc(8 * sizeof(char));
    if(filename == NULL)
    {
        printf("Malloc unable to allocate heap memory");
        free(filename);
        return 1;
    }

    // reading blocks of 512 BYTE
    // fread returns amount of elements read. Thus 0 == false and stops loop
    while (fread(buffer, sizeof(BYTE), 512, infile))
    {
        if( buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0) // start of new jpeg
        {
            if (cnt) // if not the first jpg
            {
                fclose(img);
            }
            sprintf(filename, "%03i.jpg", cnt);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                printf("Can't open %s", filename);
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), 512, img);
            cnt += 1;
        }
        else if (cnt) //if different than 0 (aka has been incremented)
        {
            fwrite(buffer, sizeof(BYTE), 512, img);
        }
    }

    // free memeory and close files
    free(filename);
    fclose(infile);
    fclose(img);
    return 0;
}
