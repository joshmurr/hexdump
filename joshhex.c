#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
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

    int lineLen = 17;
    int line[lineLen];
    int i, c, offset = 0;

    while (c != EOF) {
        i = 0;
        line[i]  = (char)offset;

        for (i=1; i<lineLen; ++i){
            c = getc(inputFile);
            line[i] = c;
            offset++;
        } 

        // PRINT LINES ::
        // --------------
        // OFFSET
        int j=0;
        printf("%08x  ", line[j]);

        // 8 BYTES
        j++;
        do {
            if(line[j] == EOF) printf("%*c", 3, ' ');
            else if(line[j] == '\0') printf("%s", "00 ");
            else printf("%02x ", line[j]);
            j++;
        } while(j<9);

        // DOUBLE SPACE
        printf("%c", ' ');

        // 8 BYTES
        do {
            if(line[j] == EOF) printf("%*c", 3, ' ');
            else if(line[j] == '\0') printf("%s", "00 ");
            else printf("%02x ", line[j]);
            j++;
        } while(j<lineLen);

        // PERUSAL
        printf("%s", " |");
        int k=1;
        do {
            // if CTRL-char print .
            if((line[k] >= 0 && line[k] <= 31) || line[k] >= 127) printf("%c", 46);
            else printf("%c", line[k]);
            k++;
        } while(k<lineLen); 
        printf("%s", "|\n");
    };

    printf("%08x\n", offset);
    fclose(inputFile);

    return 0;
}
