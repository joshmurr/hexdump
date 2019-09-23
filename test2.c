#include <stdio.h>
#include <stdint.h>

#include "bmp.h"

int main(int argc, char *argv[]){
    int c, max, counter;
    int i=0;

    if(argc != 2){
        fprintf(stderr, "Usage view_bytes FILE.ext\n");
        return 1;
    }

    char *infile = argv[1];

    // "rb" when opening non-text files
    FILE *inputFile = fopen(infile, "rb");
    if (inputFile == NULL){
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    fseek(inputFile, 0L, SEEK_END);
    int size = ftell(inputFile);
    fseek(inputFile, 0L, SEEK_SET);
    // int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    printf("%08x  ", i);
    for (max=size; i<max && (c = getc(inputFile)) != EOF; ++i){
        printf("%x", c);
        if (i % 16 == 15) {
            putchar('\n');
            printf("%08x  ", i);
        } else if (i % 2 == 1) {
            putchar(' ');
        }
    } 
    if (i % 16 != 0) putchar('\n');

    fclose(inputFile);

    return 0;
}
