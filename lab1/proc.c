#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "proc.h"
#include "split.h"

/*
 * kernel_proc is the initial process
 * kernel_proc is created by the bootstrap function
 * kernel_proc is created by the following function call
 * kernel_proc = new_proc("kernel_process", 0, 0);
 * kernel_proc has a priority of 0 and will always be the first process in the queue
 */
struct proc *kernel_proc;

int justOnce1 = 0; // Sorry

/*
 * pid is used to allocate process ids.
 * The pid of kernel_process is 1024
 * pid is incremented as processes are created
 */
int pid = START_PID;

/*
 * state_to_string converts an enum procstate to a printable C string
 */
char *state_to_string(enum procstate ps)
{
    switch (ps)
    {
        case EMBRYO:
            return "EMBRYO";
        case SLEEPING:
            return "SLEEPING";
        case RUNNABLE:
            return "RUNNABLE";
        case RUNNING:
            return "RUNNING";
        case ZOMBIE:
            return "ZOMBIE";
        case UNUSED:
            return "UNUSED";
    }

    // adding to supress warning
    return 0;
}

/*
 * find_proc searches the linked list of procs and returns the struct proc with pid
 * find_proc returns NULL is pid is not in the linked list
 */
struct proc *find_proc(int pid)
{
    // design and implement this function

    // *** ADDED 24AUG ***
    // making a temp process
    struct proc *temp = kernel_proc; // im setting temp to be kernel_proc because it is the first process in the linkedList

    //TEST
    //printf("In find_proc\n");

    while (temp != NULL) //changed from temp->next THIS IS IMPORTANT!
    {
        //TEST
        //printf("inside the while find_proc\n");
        //printf("HEY, this is the current pid: %d and this is the argument: %d\n", temp->pid, pid);

        if (temp->pid == pid)
        {
            //TEST
            //printf("LOOK AT ME About to return a found proc from find_proc\n");

            return temp;
        }
        // else I need to go to the next process
        temp = temp->next;
    }

    //TEST
    //printf("About to return NULL =[\n");

    return NULL;
}

/*
 * print_proc prints to stdout a struc proc pointer
 */
void print_proc(struct proc *p)
{
    if (p == NULL) {

        //TEST
        //printf("In print_proc, p is NULL\n");

        return;
    }

    ////TEST
    //if(p->parent == NULL) {
    //    printf("Haha\n");
    //}
    ////TEST

    ////TEST
    //printf("inside print_proc, about to print a single proc\n");
    //printf("pname: %s\n", p->name);
    //printf("pid: %d\n", p->pid);
    //printf("ppid: %d\n", p->parent->pid); // *** There is a seg fault on this line of code when using input: fork Coletta 1 Jeremy
    //printf("priority: %d\n", p->priority);
    //printf("state: %s\n", state_to_string(p->state));
    ////TEST


    printf("pname: %s, pid: %d, ppid: %d, priority: %d, state: %s\n", p->name, p->pid, p->parent->pid, p->priority, state_to_string(p->state));
}

/*
 * print_pid prints to stdout the proc corresponding to pid
 */
void print_pid(int pid)
{
    struct proc *p = find_proc(pid);
    if (p != NULL)
        print_proc(p);
    else
        printf("pid: %d not found.\n", pid);
}

/*
 * print_procs prints the entire list of procs
 */
void print_procs()
{
    printf("procs in queue:\n");
    struct proc *p = kernel_proc;
    do
    {
        print_proc(p);
        p = p->next;

        //TEST
        //printf("In print_procSSS In the dooooooo\n");

    } while (p != NULL);
    printf("\n");

    //TEST
    //printf("In print_procSSS after while\n");
}

/*
 * new_proc constructs a struc proc from the heap and returns a pointer to it
 * new_proc has to malloc a struct context and a struct proc
 * Initializing most struct proc members is straight forward.
 * For kernel_proc, p->parent points to kernel_proc.
 * For other procs, you have to search for p->parent in the list.
 */
struct proc *new_proc(char name[], uint priority, int ppid)
{
    // design and implement this function

    //TEST
    //printf("Inside new_proc\n");

    // declaring new struct objects
    // instantiating the new process pointer
    struct proc *process_ptr = (struct proc *)malloc(sizeof(struct proc));

    struct context *context_ptr = (struct context *)malloc(sizeof(struct context));

    // adding the context part of a struct proc
    process_ptr->context = context_ptr;

    // *** Must instantiate kernel_proc first!
    // *** BUT ONLY ONCE!
    if(!justOnce1) {
        kernel_proc = process_ptr; // setting it to the newly instantiated process_ptr
        justOnce1++;
    }

    // I could use strcpy() instead of the code below
    strcpy(process_ptr->name, name);

    // assigning the priority and ppid
    process_ptr->priority = priority;

    process_ptr->prev = 0;    // same as NULL
    process_ptr->next = NULL; // this was added to catch an error with malloc

    if (!strcmp(name, "kernel_process")){// this will run if it is the kernel process 
        kernel_proc->parent = kernel_proc;

        //TEST
        //printf("HEYYYYY This should only appear once\n");
    } else { //making sure the parent is set right kernel_proc parent is set above and the others are below

        process_ptr->parent = find_proc(ppid);

        process_ptr->state = EMBRYO;
        //TEST
        //printf("This is the current process ppid: %d and the supplied argument: %d\n",process_ptr->parent->pid, ppid);
    }

    // now I am setting the other attributes of both the kernel_proc and the other procs

    ////TEST
    //printf("This is the parent of the current process\n");
    //print_proc(process_ptr->prev);
    //printf("Just made a new_proc this is the current pid pre increment: %d\n",pid);
    ////TEST

    process_ptr->pid = pid++; // must increment the pid

    //TEST
    //printf("Just made a new_proc this is the current pid post increment: %d\n",pid);

    // returning the pointer
    return process_ptr;
}

/*
 * enqueue_proc places a proc properly within the linked list of procs based upon the priority.
 */
bool enqueue_proc(struct proc *p)
{  

    //TEST
    //printf("inside enqeue_proc\n");

    struct proc* prevOfCurr = 0; // setting this to NULL
    struct proc* curr = kernel_proc;

    while(curr != NULL) {
        if(p->priority < curr->priority) {
            curr->prev->next = p;
            p->prev = curr->prev;
            p->next = curr;
            curr->prev = p;

            //TEST
            //printf("About to return enqeue_proc\n");

            return true;
        }
        prevOfCurr = curr;
        curr = curr->next;
    }

    // else the new proc gets enqeued to the end of the LL

    prevOfCurr->next = p;
    p->prev = prevOfCurr;
    p->next = 0;

    //TEST
    //printf("About to return enqeue_proc\n");

    return true; // it is either going to enqeue it to the middle or the end of the LL
}

// *** 26AUG In class Gusty said that this is mostly complete? What else do I need to add to this function?

/*
 * bootstrap is called to initialize the doubly linked list of procs
 */
void bootstrap()
{
    kernel_proc = new_proc("kernel_process", 0, 0);
    kernel_proc->parent = kernel_proc;
    kernel_proc->state = RUNNABLE;
}

/*
 * kill removes a proc from the double linked list based upon pid
 */
bool kill(int pid)
{
    // design and implement this function

    // Some of this is duplicate from find_pid

    // making a temp process
    struct proc *temp = kernel_proc; // im setting temp to be kernel_proc because it is the first process in the linkedList
    struct proc *prevOfTemp = 0;


    //TEST
    //printf("In kill\n");

    while (temp != NULL) //changed from temp->next THIS IS IMPORTANT!
    {
        //TEST
        //printf("inside the while kill\n");
        //printf("HEY, this is the current pid: %d and this is the argument: %d\n", temp->pid, pid);

        if (temp->pid == pid)
        {

            temp->next->prev = prevOfTemp;
            prevOfTemp->next = temp->next;

            //TEST
            //printf("LOOK AT ME About to kill a proc and return\n");

            return true;
        }
        // else I need to go to the next process
        prevOfTemp = temp; //important
        temp = temp->next;
    }

    //TEST
    //printf("About to return false from kill =[\n");

    return false; // could not find the pid
}

/*
 * get_pid returns the pid corresponding to a process name.
 * get_pid returns 0 if the process name is not in the doubly linked list
 */
int get_pid(char name[])
{
    struct proc* temp = kernel_proc;

    while(temp != NULL) {

        ////TEST
        //printf("Inside get_pid, this is the current pointer name: ");
        //int i = 0;
        //while(temp->name[i] != 0){
        //    printf("%c",temp->name[i]);
        //    i++;
        //}
        //printf("\n");
        ////TEST

        //TEST
        //printf("Am I stuck in the while loop? Yes =[\n");

        if (!strcmp(name, temp->name)){ 

            //TEST
            //printf("Found a pid in get_pid: %d\n", temp->pid);

            return temp->pid;
        } else if(temp->next != NULL){ // if it is not NULL then shift to the next node

            //TEST
            //printf("get_pid temp->next is not NULL\n");

            temp = temp->next;
            //break; // changed from break to continue
            //goto HERE; // must use break or label to repeat the loop
        } else {
            break; // temp->next was NULL and we are at the end of the LL without a name match
        }
    }

    return 0;
}

/*
 * fork creates a new process and enqueues it in the doubly linked list
 */
int fork(char name[], int priority, int ppid)
{   

    ////TEST
    //printf("These are the arguments supplied to fork: ");
    //int i = 0;
    //while(name[i] != 0){
    //    printf("%c",name[i]);
    //    i++;
    //}
    //printf(" priority: %d ppid: %d\n", priority, ppid);
    ////TEST

    if (priority <= 0)
        return 0;
    struct proc *p = new_proc(name, priority, ppid);
    if (p != NULL)
        if (enqueue_proc(p)) {

            //TEST
            //printf("returned from enqueue, inside fork\n");

            return p->pid;
        }
    return 0;
}
