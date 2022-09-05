#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// A lot of this code was copied from maingetopts, I have modified parts as needed
// I have made a reference to a source that covered printing out FILE contents

#define FN_LEN 256

struct Options {
    bool using_h; // -h, human readable
    bool using_f; // -f, has a file optarg

    bool using_0; // added this line to account for a proccess id
    bool using_1; // added this line to account for a proccess id
    bool using_2; // added this line to account for a proccess id
    bool using_3; // added this line to account for a proccess id
    bool using_4; // added this line to account for a proccess id
    bool using_5; // added this line to account for a proccess id
    bool using_6; // added this line to account for a proccess id
    bool using_7; // added this line to account for a proccess id
    bool using_8; // added this line to account for a proccess id
    bool using_9; // added this line to account for a proccess id

    char filename[FN_LEN]; // -f optarg
};

static void init_opts(struct Options* opts) {
    opts->using_h = false;
    opts->using_f = false;

    opts->using_0 = false;
    opts->using_1 = false;
    opts->using_2 = false;
    opts->using_3 = false;
    opts->using_4 = false;
    opts->using_5 = false;
    opts->using_6 = false;
    opts->using_7 = false;
    opts->using_8 = false;
    opts->using_9 = false;

    for (int i = 0; i < FN_LEN; i++)
        opts->filename[i] = 0;
}

struct Options opts;

struct Options get_opts(int count, char* args[]) {

    init_opts(&opts);
    int opt;

    //*** 04Sep the issue at the moment is that you must use the - then the integer and not just 1234
    // rethinking this approach but at the moment the current code works with input -h -f
    // if you type -0123456789 it will print the number that is pressed but otherwise I am getting additional new lines printed coming from main function

    while ((opt = getopt(count, args, ":if:hf0123456789")) != -1) { // the optional string before was ":f:had"
        switch (opt) {
            case 'h': opts.using_h = true; break;

            case 'f': 
                      opts.using_f = true; 
                      strcpy(opts.filename, optarg);
                      break;

            case '0': opts.using_0 = true; break;
            case '1': opts.using_1 = true; break;
            case '2': opts.using_2 = true; break;
            case '3': opts.using_3 = true; break;
            case '4': opts.using_4 = true; break;
            case '5': opts.using_5 = true; break;
            case '6': opts.using_6 = true; break;
            case '7': opts.using_7 = true; break;
            case '8': opts.using_8 = true; break;
            case '9': opts.using_9 = true; break;

            case ':': 
                      printf("-f needs a value\n");
                      break;
            case '?': 
                      printf("Unknown option\n");
                      exit(-1);
        }
    }

    return opts;
}

//***

int main(int argc, char *argv[]) {

    FILE *fptr;

    struct Options o = get_opts(argc, argv);
    printf("%s\n", opts.using_h ? "Hello World" : "" /* print an empty string */ );
    
    printf("%c\n", opts.using_0 ? '0' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_1 ? '1' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_2 ? '2' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_3 ? '3' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_4 ? '4' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_5 ? '5' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_6 ? '6' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_7 ? '7' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_8 ? '8' : ' ' /* print a space char */ );
    printf("%c\n", opts.using_9 ? '9' : ' ' /* print a space char */ );
    
    if (opts.using_f) {
        //printf("-f: %s\n", opts.filename);

        // ** Added this code to get_opts source: https://www.geeksforgeeks.org/c-program-print-contents-file/

        // Open file
        fptr = fopen(opts.filename, "r");
        if (fptr == NULL)
        {
            printf("Cannot open file \n");
            exit(0);
        }

        // Read contents from file
        char c = fgetc(fptr);
        while (c != EOF)
        {
            printf ("%c", c);
            c = fgetc(fptr);
        }

        fclose(fptr);
        // **
    }

    //for (int i = 0; i < 25; i++)
    //    sleep(5);
    return 0;
}
