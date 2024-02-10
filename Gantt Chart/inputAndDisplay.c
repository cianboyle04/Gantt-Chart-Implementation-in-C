#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "inputAndDisplay.h"

//some global variables used in display functions and modified in the getChartDimensions fucntion to have the chart's dimensions adjust based on user input
//default values are based on test data
int max_name_len=23, total_chart_width=183;


/*
    function which will use taskInput to input all tasks and info into struct
--- takes in 1 argument: the array into which to read tasks (taskArray)
--- returns the number of tasks read

*/

int ganttInput(struct task taskArray[])
{
    int i;
    int num_tasks;
    puts("How many tasks would you like to add ? (1-10)");

    //loop entered to ensure valid number is inputted
    do {
        scanf("%d", &num_tasks);

        if(num_tasks<1 || num_tasks>10)
        {
            printf("Please enter a valid number between 1 and 10\n");
        }

    }while(num_tasks<1 || num_tasks>10);

    fflush(stdin); //this is to clean buffer after scanf so that fgets can read in stuff

    for(i=0; i<num_tasks; i++)
    {
        printf("Please enter task %d\n", i+1);
        printf("Enter task name:\n");
        //function which is used to take in an individual task
        taskInput(taskArray, i, num_tasks);
    }

    getChartDimensions(taskArray, num_tasks, &max_name_len, &total_chart_width); //recalculate chart dimensions
    return num_tasks;
}

/*
 * function which takes in a struct array and a variable for which index, information is to be inputted into in struct
 */

void taskInput(struct task taskArray[], int i, int num_of_tasks)
{

    fgets(taskArray[i].name, 50, stdin);
    taskArray[i].name[strlen(taskArray[i].name) - 1] = '\0'; //removing newline that was read by fgets
    fflush(stdin);

    printf("Start month(1-12): ");
    do
    {
        scanf("%d", &taskArray[i].start_month);

        if(taskArray[i].start_month<JANUARY || taskArray[i].start_month>DECEMBER)
        {
            printf("Invalid number entered. Please enter a number between 1 and 12\n");
        }

    }while(taskArray[i].start_month<JANUARY || taskArray[i].start_month>DECEMBER);


    //enter do while loop to ensure valid month is entered
    printf("End month(1-12): ");
    do
    {
        scanf("%d", &taskArray[i].end_month);
        if(taskArray[i].end_month<taskArray[i].start_month || taskArray[i].end_month<JANUARY || taskArray[i].end_month>DECEMBER)
        {
            printf("Invalid number entered. Please enter a number which is greater than or equal to start month\n");
            printf("Please also ensure that number entered is between 1 and 12\n");
        }
    }while(taskArray[i].end_month<taskArray[i].start_month || taskArray[i].end_month<JANUARY || taskArray[i].end_month>DECEMBER);

    //get dependencies for task
    printf("Enter how many dependencies this task has: ");
    do {
        scanf("%d", &taskArray[i].num_dependent_tasks);

        if(taskArray[i].num_dependent_tasks>10)
        {
            printf("Invalid input. Cannot have more than 10 dependent tasks. Please enter correct number\n");
        }

    }while(taskArray[i].num_dependent_tasks>10);

    for(int j=0; j<taskArray[i].num_dependent_tasks; j++)
    {
        do{
            printf("Enter dependent task number: ");
            scanf("%d", &taskArray[i].dependent_tasks[j]);

            if(taskArray[i].dependent_tasks[j]>num_of_tasks || taskArray[i].dependent_tasks[j]<1)
            {
                printf("Invalid input. Please ensure dependent task number is between 1 and the number of tasks in your chart\n");
            }

        }while(taskArray[i].dependent_tasks[j]>num_of_tasks || taskArray[i].dependent_tasks[j]<1);

    }

    fflush(stdin); //this is to clean buffer after scanf so that fgets can read in stuff
}

/*
 * Helper function which is used in the "editInput" function.
 * function takes in the struct array and the number of tasks in that array
 * function cycles through the struct array and tries to find the index of the task user wants to edit
 * when index is found, function returns this index
*/

int findEdit(struct task taskArray[] ,int num_of_tasks)
{
    //initialize variables
    int i;
    bool notFound=true;
    char toEdit[50];

    printf("Please enter the task name you which to change exactly\n");


    //enter a do-while loop to successfully find a task in original struct array
    do {

        //task user wants to edit is taken in
        fgets(toEdit, 50, stdin);
        toEdit[strlen(toEdit)-1] = '\0';

        //boolean is used to ensure that the user enters a valid task
        //only turns false once a valid task is entered and ultimately exits loop
        notFound=true;

        //cycle through all tasks
        for(i=0; i<num_of_tasks; i++)
        {
            //use strcmp to find correct task
            if((strcmp(toEdit, taskArray[i].name))==0)
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

/*
 * function which simply overrides previous input at a given index
 * (index found using findEdit function
 */

void editInput(struct task taskArray[], int num_of_tasks)
{
    //index of task user wishes to edit is found using "findEdit"
    int index = findEdit(taskArray, num_of_tasks);

    //once index which will be overridden is found, all details of new task are taken in
    printf("Please enter the new task name or write its old one\n");
    taskInput(taskArray, index, num_of_tasks);

    getChartDimensions(taskArray, num_of_tasks, &max_name_len, &total_chart_width); //recalculate chart dimensions
}

/*
 * Function prints appropriate header including all months and correct spacing
 */

void printHeader(void)
{
    //initial top line above gantt chart
    for(int i=0; i<total_chart_width; i++)
    {
        printf("_");
    }
    printf("\n");

    //correct spacing before months are printed
    for(int i=0; i<(4+max_name_len+2); i++)
    {
        printf(" ");
    }

    //print months
    printf("| January  ");
    printf("| February ");
    printf("|  March   ");
    printf("|  April   ");
    printf("|   May    ");
    printf("|   June   ");
    printf("|   July   ");
    printf("|  August  ");
    printf("| September");
    printf("| October  ");
    printf("| November ");
    printf("| December ");
    printf("|    Dependencies     \n");

    //line printed under months to separate
    printLine();
}

/*
 * function which prints a straight dotted line under each line of gantt chart to separate
 */
void printLine(void)
{
    for(int i=0; i<total_chart_width; i++)
    {
        printf("-");
    }
    printf("\n");

}

/*
 * function which prints for a month of which is not between start and end months of a task
 */
void printEmpty(void)
{
    printf("|          ");
}

/*
 * function which prints for a month of which is inclusive of the start and end month
 */
void printMarked(void)
{
    printf("|   XXX    ");
}

/*
 * function which prints the contents of each row of the gantt chart
 */
void printRow(struct task taskItem, int row_number)
{
    //print task name and white spaces to allow for correct presentation
    printf("%2d. %-*s", row_number, max_name_len+2, taskItem.name);


    //for loop which iterates 12 times, for each month
    for(int i=0; i<DECEMBER; i++)
    {
        //if "i" is within start and end month, task is ongoing
        //therefore we print a marked box
        if((i+1)>=taskItem.start_month && (i+1)<=taskItem.end_month)
        {
            printMarked();
        }

        //else we print an empty box as "i" is not between start or end months
        else
        {
            printEmpty();
        }
    }
    //line printed after month of Decemeber
    printf("|");

    //print each of the dependencies which are stored in an array of size num_dependent_tasks
    for(int i=0; i<taskItem.num_dependent_tasks; i++)
    {
        printf(" %d", taskItem.dependent_tasks[i]);
    }

    //finally print a new line and the print the dotted line to separate each task from previous task
    printf("\n");
    printLine();
}

/*
    Function to display the Gantt chart
--- takes in 2 arguments: the array of tasks to display in the chart(taskArray) and the number of tasks in the array(num_tasks)

*/

void display_Gantt(struct task taskArray[], int num_tasks)
{

    //header printed first
    printHeader();

    //loop which prints each correct row of gantt
    for(int i=0; i<num_tasks; i++)
    {
        printRow(taskArray[i], i+1);
    }
}

/*
    Function that is going to be called each time the chart is modified to recalculate the chart dimensions.
    Takes 4 arguments:

--- the array of tasks after being modified
--- the number of tasks in the array
--- 2 pointers to the global variables used by the display functions (they get passed by reference so that their actual values change)

*/

void getChartDimensions(struct task taskArray[], int num_tasks, int *max_name, int *total_width)
{
    int max=0;
    for(int i=0; i<num_tasks; i++)
    {
        if(strlen(taskArray[i].name)>max)
        {
            max = strlen(taskArray[i].name);
        }
    }
    (*max_name) = max; //the new maximum length of a task name after the array is modified
    (*total_width) = 4 + (*max_name) + 2 + 11*12 + 22; //4 for row numbering, 2 for some spacing after the names, 11*12 for the months columns
                                                       //and 22 for dependencies column
}
