//declare enums
enum months {JANUARY=1, FEBRUARY, MARCH, APRIL, MAY, JUNE, JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER};

//number which is the max amount of tasks a user can enter
#define MAXSTRUCT_LENGTH 10

//define "task" struct which holds all necessary information
struct task
{
    char name[50];
    enum months start_month, end_month;
    int num_dependent_tasks;
    int dependent_tasks[10];
};

//prototype for all input and editing functions
int ganttInput(struct task taskArray[]);

void taskInput(struct task taskArray[], int i, int num_of_tasks);

int findEdit(struct task taskArray[] ,int num_of_tasks);

void editInput(struct task taskArray[], int num_of_tasks);

//prototype for all various display functions
void printLine(void);

void printEmpty(void);

void printMarked(void);

void printRow(struct task taskItem, int row_number);

//prototype for display function
void display_Gantt(struct task taskArray[], int num_tasks);

//prototype for getChartDimensions function
void getChartDimensions(struct task taskArray[], int num_tasks, int *max_name, int *total_width);
