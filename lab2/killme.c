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
                  //bool using_a; // -a, print all
                  //bool using_d; // -d, list dirs only
    bool using_f; // -f, has a file optarg
    char filename[FN_LEN]; // -f optarg
};

static void init_opts(struct Options* opts) {
    opts->using_h = false;
    //opts->using_a = false;
    //opts->using_d = false;
    opts->using_f = false;
    for (int i = 0; i < FN_LEN; i++)
        opts->filename[i] = 0;
}

struct Options opts;

struct Options get_opts(int count, char* args[]) {

    init_opts(&opts);
    int opt;

    while ((opt = getopt(count, args, ":f:had")) != -1) {
        switch (opt) {
            case 'h': opts.using_h = true; break;
                      //case 'a': opts.using_a = true; break;
                      //case 'd': opts.using_d = true; break;
            case 'f': 
                      opts.using_f = true; 
                      strcpy(opts.filename, optarg);
                      break;
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
    //printf("-a: %s\n", opts.using_a ? "true" : "false");
    //printf("-d: %s\n", opts.using_d ? "true" : "false");
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
