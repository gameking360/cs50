// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


typedef uint8_t BYTE;
// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{

    uint8_t header[HEADER_SIZE];


    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

        fread(header,sizeof(uint8_t),HEADER_SIZE,input);
        fwrite(header,sizeof(uint8_t),HEADER_SIZE,output);


    // TODO: Read samples from input file and write updated data to output file

    int16_t buff;

    while(fread(&buff,sizeof(int16_t),1,input) == 1){
        buff = (int16_t) (buff * factor);

        fwrite(&buff,sizeof(int16_t),1,output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
