#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file)
    {
        printf("Can't open file\n");
        return 1;
    }

    BYTE *c = malloc(512);  // Read 512 bytes at a time
    int qtd = 0;

    while (fread(c, sizeof(BYTE), 512, file) == 512)
    {
            char filename[8];
        if (c[0] == 0xff && c[1] == 0xd8 && c[2] == 0xff && (c[3] & 0xf0) == 0xe0)
        {
            // Start of a new JPEG file
            sprintf(filename, "%03i.jpg", qtd);
            qtd++;

            FILE *img = fopen(filename, "wb");
            if (!img)
            {
                fclose(file);
                free(c);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 2;
            }

            fwrite(c, sizeof(BYTE), 512, img);
            fclose(img);
        }
        else if (qtd > 0)
        {
            // Continue writing to the current JPEG file
            FILE *img = fopen(filename, "ab");
            if (!img)
            {
                fclose(file);
                free(c);
                fprintf(stderr, "Could not open %s.\n", filename);
                return 3;
            }

            fwrite(c, sizeof(BYTE), 512, img);
            fclose(img);
        }

    }

    fclose(file);
    free(c);

    return 0;
}
