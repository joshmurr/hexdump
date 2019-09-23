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
    char line[lineLen];
    int i, c, offset = 0;

    c = getc(inputFile);
    while (c != EOF) {
        i = 0;
        line[i]  = (char)offset;

        for (i=1; i<lineLen; ++i){
            line[i] = c;
            c = getc(inputFile);
            if(c == EOF){
                line[i] = '\0';
            }
            offset++;
        } 
        int j=0;
        printf("%08x ", line[j]);
        j++;
        do {
            printf("%02x ", line[j]);
            j++;
        } while(j<9);
        printf("%*c", 2, ' ');
        do {
            printf("%02x ", line[j]);
            j++;
        } while(j<lineLen);
        printf("%s", "  |");
        int k=0;
        do {
            if(line[k] == '\n') printf("%c", ' ');
            else printf("%c", line[k]);
            k++;
        } while(k<lineLen); 
        printf("%s", "|\n");

    };
    fclose(inputFile);

    return 0;
}
