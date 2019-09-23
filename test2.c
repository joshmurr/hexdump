#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i, c, offset;
    
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
    
    char line[18];

    i = offset = 0;

    c = getc(inputFile);
    while (c != EOF) {

        //Print initial offset
        // printf("%08x  ", i);
        line[i]  = (char)offset;

        for (i=1; i<18; ++i){
           //End of line
            if (i == 17) {
                // printf("%c", c);
                //Print offset as start of new line
                line[i] = '\n';
            } else {
                line[i] = c;
                c = getc(inputFile);
                if(c == EOF){
                    line[i] = ' ';
                }
            }
            offset++;
        } 
        int j=0;
        do {
            printf("%02x ", line[j]);
            j++;
        } while(j<18);
        printf("%s", "  |");
        int k=0;
        do {
            printf("%c", line[k]);
            k++;
        } while(k<18); 

    };


    fclose(inputFile);

    return 0;
}


/*
*            //Print char in hex
*            printf("%02x", c);
*            //End of line
*            if (i % 16 == 15) {
*                printf("%c", c);
*                //Print offset as start of new line
*                printf("\n%08x  ", i+1);
*            } else if (i % 8 == 7) {
*                //Print double space after 8 bytes
*                printf("%*c", 2, ' ');
*            } else {
*                //Space between each byte
*                putchar(' ');
*            }
*/
