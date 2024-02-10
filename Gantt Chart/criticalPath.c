#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "inputAndDisplay.h"
#include "criticalPath.h"

//function that deals with testing for circular dependencies, calling other helper functions in the process
void test(struct task taskArray[], int num_of_tasks)
{
    int test_index = findTest(taskArray, num_of_tasks); //find index to be tested

    int visitedTasks[MAXSTRUCT_LENGTH]={}; //initialize a list of visited tasks to 0
    int status; //this will take one of 2 values: 1 for circular dependency and 0 for no circular dependency

    status = printDependentTasks(taskArray, test_index, visitedTasks);

    if(status == 1)
    {
        printf("!!!!Circular dependency found: your task is impossible to complete!!!!\n");
    }
    else
    {
        printf("end of critical path: your task is possible\n");
    }

}

//adapted function findEdit which prompts for the name of a task and returns its index
int findTest(struct task taskArray[] ,int num_of_tasks)
{
    //initialize variables
    int i;
    bool notFound=true;
    char toTest[50];

    printf("Please enter the task name you wish to test exactly\n");


    //enter a do-while loop to successfully find a task in original struct array
    do {

        //task user wants to test is taken in
        fgets(toTest, 50, stdin);
        toTest[strlen(toTest)-1] = '\0';

        //boolean is used to ensure that the user enters a valid task
        //only turns false once a valid task is entered and ultimately exits loop
        notFound=true;

        //cycle through all tasks
        for(i=0; i<num_of_tasks; i++)
        {
            //use strcmp to find correct task
            if((strcmp(toTest, taskArray[i].name))==0)
            {
                //if found, loop breaks and the "i" index is returned
                notFound=false;
                break;
            }
        }

        //user prompted to make sure they correctly enter a task name
        if(notFound)
        {
            printf("Task not found. Please try again and ensure task name entered is valid\n");

        }
    }while(notFound);

    //index of task to edit is returned
    return i;
}

//function that prints recursively dependent tasks of a given task whose id is given as an argument
//it also returns 1 in the case of a circular dependency, 0 otherwise
int printDependentTasks(struct task taskArray[], int taskId, int visitedTasks[])
{
    printf("%d -> ", taskId+1);
    visitedTasks[taskId] = 1; //mark the task as visited

    for(int i=0; i<taskArray[taskId].num_dependent_tasks; i++) //iterate over task's dependencies
    {
        int dependentTaskId = taskArray[taskId].dependent_tasks[i] - 1;

        //if dependent task has not yet been visited we can recursively call the function again to print all its dependencies as well
        if(visitedTasks[dependentTaskId] == 0)
        {
            if(printDependentTasks(taskArray, dependentTaskId, visitedTasks) == 1)
            {
                return 1; //a circular dependency was found somewhere so no reason to continue
            }
        }
        else //if it has been visited we might find a circular dependency so we call function checkCircular to check for that
        {
            printf("\n!!!!Warning: potential circular dependency!!!!\n");

            if(checkCircular(taskArray, dependentTaskId, dependentTaskId) == 1)
            {
                return 1; //if circular dependency was found we immediately return 1 else we just continue
            }
            else
            {
                printf("~~~~No circular dependency found: continuing to print critical path~~~~\n-> ");
            }
        }
    }
    return 0;
}

//function that checks for a potential circular dependency starting from a given task
//if it returns 1 that means it has found a circular dependency
//if it returns 0 that means no circular dependency was found
int checkCircular(struct task taskArray[], int taskId, int start_point)
{
    for(int i=0; i<taskArray[taskId].num_dependent_tasks; i++)
    {
        int dependentTaskId = taskArray[taskId].dependent_tasks[i] - 1;
        if(dependentTaskId == start_point) //this means we're back where we started checking
        {
            return 1; //base case 1: circular dependency found so we return 1
        }
        else if(checkCircular(taskArray, dependentTaskId, start_point) == 1) //recursive call here
        {
            return 1; //if recursive call returns 1 we have found a circular dependency somewhere so we return 1
        }
    }
    return 0; //base case 2: no circular dependency found, as we got out of the loop without returning so we return 0
}
