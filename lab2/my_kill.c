#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h> // must include this for kill()

#include<string.h> // added to use the strcat() function

// A lot of this code was copied from maingetopts, I have modified parts as needed
// I have made a reference to a source that covered printing out FILE contents

#define FN_LEN 256

struct Options {
    bool using_h; // -h, human readable
    bool using_f; // -f, has a file optarg

    //bool using_1; // added this line to account for a proccess id
    //bool using_2; // added this line to account for a proccess id
    //bool using_3; // added this line to account for a proccess id
    //bool using_4; // added this line to account for a proccess id
    //bool using_5; // added this line to account for a proccess id
    //bool using_6; // added this line to account for a proccess id
    //bool using_7; // added this line to account for a proccess id
    //bool using_8; // added this line to account for a proccess id
    //bool using_9; // added this line to account for a proccess id

    char filename[FN_LEN]; // -f optarg

    // *** VERY IMPORTANT, if you declare a "flexible string i.e. []" you must put it at the end of the struct object!
    char process_id[128]; // This is a string used for the pid I am giving is a random size of 128
};

static void init_opts(struct Options* opts) {
    opts->using_h = false;
    opts->using_f = false;

    //char empty_string[] = "\0";

    //opts->using_1 = false;
    //opts->using_2 = false;
    //opts->using_3 = false;
    //opts->using_4 = false;
    //opts->using_5 = false;
    //opts->using_6 = false;
    //opts->using_7 = false;
    //opts->using_8 = false;
    //opts->using_9 = false;

    for (int i = 0; i < FN_LEN; i++)
        opts->filename[i] = 0;

    // setting the process_id string to null just like the filename above
    for (int i = 0; i < 128; i++)
        opts->process_id[i] = 0;

}

struct Options opts;

struct Options get_opts(int count, char* args[]) {

    init_opts(&opts);
    int opt; 

    // variables used in the for loop below
    int count_temp = count;
    char ** args_temp = args;

    //*** 04Sep the issue at the moment is that you must use the - then the integer and not just 1234
    // rethinking this approach but at the moment the current code works with input -h -f
    // if you type -0123456789 it will print the number that is pressed but otherwise I am getting additional new lines printed coming from main function

    while ((opt = getopt(count, args, ":f:had")) != -1) { // the optional string before was ":f:had"

        switch (opt) {
            case 'h': opts.using_h = true; break;

            case 'f': 
                      opts.using_f = true; 
                      strcpy(opts.filename, optarg);
                      break;

                      //case atoi(args): opts.using_0 = true; break;
                      //case "1": opts.using_1 = true; break;
                      //case "2": opts.using_2 = true; break;
                      //case "3": opts.using_3 = true; break;
                      //case "4": opts.using_4 = true; break;
                      //case "5": opts.using_5 = true; break;
                      //case "6": opts.using_6 = true; break;
                      //case "7": opts.using_7 = true; break;
                      //case "8": opts.using_8 = true; break;
                      //case "9": opts.using_9 = true; break;

            case ':': 
                      printf("-f needs a value\n");
                      break;
            case '?': 
                      printf("Unknown option\n");

                      // **** DO NOT DELETE, uncomment after testing ****
                      //exit(-1);
        }
    }
    //TEST
    //printf("I am outside the for loop\n");

    // copied and modified from mainargs.c

    //int c = 0;
    //while(&args_temp[1][c] != NULL) {

        for(/*int d = 0*/; count_temp>1 /*&& &args_temp[1][0] != '-'*/; count_temp--,args_temp++/*, d++*/) { // changed from == '-' to != NULL
        // my thinking is that the numbers are not led by a - so as long as the string is not NULL it should enter this loop

            //TEST
            printf("I am in the for loop\n");
            printf("this is argc: %d this is args_temp[1][0]: %d\n",count_temp, atoi(&args_temp[1][0]));

            //strcat()
            //strncat() appends to the end with max size

            //switch(args_temp[1][0]) { // this should be args_temp[1][0]
            //    case '0': strncat(opts.process_id, "0", 127); break;
            //    case '1': // this must be a char because the args_temp[1][0] holds the ASCII value if the integer not the int itself
            //              //opts.using_1 = malloc(16*sizeof(char));

            //              //TEST
            //              //printf("inside switch\n");

            //              //char* one = "1";
            //              //opts.process_id = "1";
            //              strncat(opts.process_id, "1", 127);
            //              break;
            //    case '2': strncat(opts.process_id, "2", 127); break;
            //    case '3': strncat(opts.process_id, "3", 127); break;
            //    case '4': strncat(opts.process_id, "4", 127); break;
            //    case '5': strncat(opts.process_id, "5", 127); break;
            //    case '6': strncat(opts.process_id, "6", 127); break;
            //    case '7': strncat(opts.process_id, "7", 127); break;
            //    case '8': strncat(opts.process_id, "8", 127); break;
            //    case '9': strncat(opts.process_id, "9", 127); break;
            //}

            // If it equals a number then we know it is a pid so set it to the string
            if(args_temp[1][0] == '-') { // do nothing it will increment

                //TEST
                printf("I am in the '-' if block\n");
                
            } else {
                
                //TEST
                printf("I am in the else block\n");
                
                strstr(args_temp[1][0],'0') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'1') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'2') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'3') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'4') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'5') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'6') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'7') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'8') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                strstr(args_temp[1][0],'9') != NULL ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                
                //args_temp[1][0] == '0' ? strcat(opts.process_id, &args[1][0]/*"0"*/) : 0; 
                //args_temp[1][0] == '1' ? strcat(opts.process_id, &args[1][0]/*"1"*/) : 0; 
                //args_temp[1][0] == '2' ? strcat(opts.process_id, &args[1][0]/*"2"*/) : 0; 
                //args_temp[1][0] == '3' ? strcat(opts.process_id, &args[1][0]/*"3"*/) : 0; 
                //args_temp[1][0] == '4' ? strcat(opts.process_id, &args[1][0]/*"4"*/) : 0; 
                //args_temp[1][0] == '5' ? strcat(opts.process_id, &args[1][0]/*"5"*/) : 0; 
                //args_temp[1][0] == '6' ? strcat(opts.process_id, &args[1][0]/*"6"*/) : 0; 
                //args_temp[1][0] == '7' ? strcat(opts.process_id, &args[1][0]/*"7"*/) : 0; 
                //args_temp[1][0] == '8' ? strcat(opts.process_id, &args[1][0]/*"8"*/) : 0; 
                //args_temp[1][0] == '9' ? strcat(opts.process_id, &args[1][0]/*"9"*/) : 0; 
            }
            //break;
        }
        //c++;
    //}

    return opts;
}

//***

int main(int argc, char *argv[]) {

    FILE *fptr;

    struct Options o = get_opts(argc, argv);
    printf("%s", opts.using_h ? "Hello World\n" : "" /* print an empty string */ );

    //printf("%s\n", (strcmp(opts.process_id, "1") == 0) ? opts.process_id : "test" /* print an empty string */ );

    //printf("%s", opts.using_1 ? "1/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_2 ? "2/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_3 ? "3/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_4 ? "4/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_5 ? "5/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_6 ? "6/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_7 ? "7/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_8 ? "8/n" : "" /* print an empty string */ );
    //printf("%s", opts.using_9 ? "9/n" : "" /* print an empty string */ );

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

    //if (strlen(opts.process_id) != 0) { // if the string is not empty
    //    for (int i = 0; i < 128; i++) {
    //        printf("%c",opts.process_id[i]);
    //    }
    //    printf("\n");
    //}

    //for (int i = 0; i < 25; i++)
    //    sleep(5);

    if ((argc - optind) != 1) {
        printf("Error - command format is $ my_kill -options pid\n");
        exit(-1);
    }

    printf("my_kill pid: %d\n", getpid()); //get my_kill's pid

    // This block of code is for the case that you run the program with a flag, it does not account for the filename
    // The goal is that only valid process ids get past this point
    // This block only skips argument variable that start with '-'
    while (argv[1][0] == '-'){ 
        
        //TEST
        printf("argv[1][0] == '-'\n");
            
        argv++; // incrementing the pointer
    }

    //int min = 0, max = 9, num = atoi(&argv[1][0]), valid_num = 0; // this was min = 48, max = 57
    int min = 0, max = 9, num = atoi(opts.process_id), valid_num = 0; // this was min = 48, max = 57

    //TEST
    printf("This is the beginning of the proccess id: %d\n", num);

    // This part below where I see if argv[1][0] is within the range of ASCII 'ints' came from
    // https://www.techcrashcourse.com/2016/02/c-program-to-check-number-is-in-range-min-max.html
    // ((num - min)*(num - max) <= 0)
   
    //while (&argv[1][0] != NULL){ // if the arg variable is not NULL
        
        //TEST
        //printf("This is num: %d\n", num);
        
        //if ((num - min)*(num - max) <= 0){ // this statement evaluates if the argument starts with an integer
        //    
        //    valid_num = num;
        //    
        //    //TEST
        //    printf("I am in the valid_num loop, this is valid_num: %d\n", valid_num);
        //    
        //} else if(&argv[1][1] != NULL){ // the next variable is not NULL

        //    //TEST
        //    printf("About to increment argv\n");

        //    argv++; //increment the pointer
        //    num = atoi(&argv[1][0]);
        //}
    //}

    int status = kill(atoi(opts.process_id), SIGINT); //valid_num is the pid to kill
    int errnum = -1; // I don't understand what errno is supposed to be I am changing this to -1
    if (status == -1) {
        fprintf(stderr, "Value of errno: %d\n", -1);
        perror("Error printed by perror");
        fprintf(stderr, "Error killing process: %s\n", strerror( errnum));
    }
    return 0;
}
