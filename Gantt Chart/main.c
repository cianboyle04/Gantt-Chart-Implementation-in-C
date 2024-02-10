#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "inputAndDisplay.h"
#include "criticalPath.h"

//struct task and enum months data types are defined inside "inputAndDisplay.h"

//initializing test data
struct task test_taskList[10] = {{"Get a PC", JANUARY, JANUARY, 0, {}}, {"Learn programming", JANUARY, APRIL, 1, {1}}, {"Set up LinkedIn", FEBRUARY, FEBRUARY, 1, {1}},
                                 {"Practice for interviews", FEBRUARY, APRIL, 1, {2}}, {"Search for jobs", MARCH, MAY, 3, {2,3,6}}, {"Make CV", MAY, JUNE, 2, {3,7}},
                                 {"Apply for jobs", JUNE, SEPTEMBER, 2, {5,6}}, {"Hustle some more", JULY, OCTOBER, 0, {}}, {"Get rejected", SEPTEMBER, OCTOBER, 1, {7}},
                                 {"Give up", NOVEMBER, DECEMBER, 1, {9}}};


int main(void)
{

//clear screen from previous charts if ran before
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    puts("Welcome to the Gantt Generator");
    puts("Would you like to use the test example or create your on Gantt from scratch ? (Yes for test example, anything else for your own data) ");

    //variable to hold user initial choice
    char user_choice[5];
    size_t i;

    //initialize array of structs to hold all information
    //set max size to 10, (defined in .h file)
    //also initialize variable which holds amount of tasks user wishes to enter
    //num_of_tasks will be given value returned by input function
    struct task taskList[MAXSTRUCT_LENGTH];
    int num_of_tasks;

    //take in user choice
    scanf("%3s", user_choice);
    fflush(stdin); //flushing the input buffer
    for(i=0; i<strlen(user_choice); i++) //converting input to lowercase
        user_choice[i] = tolower(user_choice[i]);


    //if user enters "yes", test gantt chart is used
    if(strcmp(user_choice, "yes")==0)
    {
        for(i=0; i<10; i++)
            taskList[i] = test_taskList[i]; //filling taskList with the test data
        num_of_tasks = 10;
    }

    //else, user must enter their own data which is taken in from "get_input" function
    else
    {
        //set num_of_tasks to number which was taken in from user during the functions execution
        num_of_tasks = ganttInput(taskList);
    }


    display_Gantt(taskList, num_of_tasks); //displaying the chart


    //enter do while loop to allow user to continue editing or testing until they enter "quit"
    do{

        //give user choice to either edit, test or exit program
        printf("If you wish to edit the Gantt please type ''edit'' / If you wish to run a test, type ''test'' or to "
               "exit, type ''quit'' and then press enter to execute your option.\n");

        //take in choice and convert all characters to lower
        scanf("%4s", user_choice);
        fflush(stdin); //flushing the input buffer
        for(i=0; i<strlen(user_choice); i++) //converting input to lowercase
            user_choice[i] = tolower(user_choice[i]);

        //allow user to edit
        if(strcmp(user_choice, "edit")==0)
        {
            //editInput function takes in task name in function and also takes in new task and task componenets
            editInput(taskList, num_of_tasks);

            //clear previous gantt chart
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif

            //display new gantt
            display_Gantt(taskList, num_of_tasks);

        }

            //allow user to test dependencies
        else if(strcmp(user_choice, "test")==0)
        {
            test(taskList, num_of_tasks);
        }

            //if quit inputted by user, program ends

    }while(strcmp(user_choice, "quit")!=0);

    return 0;
}
/*

                                 ,µ∞∞═*MMM═*════∞ww,
                           ¿═$▓╨"`'`    -""ⁿ∞▄        `ⁿ═,
                      ,æ²,∞"                   "N          "¥▄
                   ,M` e"                         ▀,           N,
                 æ"  Æ                              N            ╙╖
              ,P   ,▀                                ▓             █▄
             P     ▀                                  µ            ▐ ▀
           ╓"     ▓                                   ▌             ▌ ╙▄
          ƒ       ▌                                   ▌             ▐  ╙w
         Æ        ▓                                   M              ▌  ▐
        á         ▐                                  █               ▐   ▌
        `          ▓                                ▓                 ▌  ]
       ▐            ▌                             ,▀                  ╘µ  ▌
       █             ▀▄                         ,@`                    ▐  ▌
       █▀              ▀▄                     ▄▀                        ▀ ▌
       █ ▌                ╙h▄,           ,▄m"'                           %▌
       ▐  ▄                    '`""""""'                                  ▌
        ▌  ▄                                                             ]
        ▐  ╙,                                                            ▌
         █  ▐                                                           ▀
          ▌  ▌                              ,▄▄mKM²ⁿ▀▀▀²═∞∞╖,         ╓▀
           ▌  ▌                      ,▄mⁿ"'        ,,        ▀      ,M
            █, ▌                 ,▄╜▀             ▐█▀█        ▓   ,Æ
             "▌▓               ╓╜   ,▄▄           ▐███▌        ▌m"   M¥  ,M"L
               '▀▄           ,P     █▌█▌           ▀███        ▐    ▐  ªM  ▄P"`
                  ▀▀▄        ▌      ▐███                        ▌   ▐        ╨╨"L
                      ▀N▄,   ▓       ▀█▀                        `  ,▀         @`
                           '"▀▌                      ,▄        ╝  ╝          ,,▄Å
                              ▀▄              ,▄▄▄████▌       Å,P       ¿═ⁿ`
                               ╙▄       ▐███████▀▀▀▀██      ╓▓Ñ       ▄'
                                 ▀▄       "██▀     ╓▀     ╓▓▓`       ╝
                                   ▀¥,       "ⁿⁿ²"▀   ,▄ⁿ▓@        ,╜
                                      'ⁿ▄w,,,,,,,▄▄M"▓  j█        Æ
                                      ▄▀ P           ▌  j "N▄   ╓╝
                                    Æ▓' ▀            ▓   ▌   ""▀,
                                 ,@"█  ▌             ▐   █      ▀▄
                               ▄▀  █  █               ▌   ▌      ╙▄
                      ,∞∞═ⁿ"""    █  █═════∞∞∞∞∞∞∞∞═══█   ▐       "▌
                    ,Ñ           ▓  ▐                  ▌   ▀       ,█▄
                     "══∞═╗    a5▌  ▌                  "▄   ╙ⁿ*""`    ▓
                         ╔',╓═"  ▌ ▐                     ▄         ,m▌
                                 ▐"╜                      ª∞∞MM²▀▀   ▓
                                 ▐                                   ▌
                                  ▌                                  ▌
                               ,╓w▓                                ╓▀
                            ,@'    "╗                             ▄▌
                           ╓▀        ╙N▄                       ▄M"  N
                           ▌             ╙═w,,          ,,▄∞*"'      ╙▄
                           ▌                    ▐▀`▐▀                  ▌
                           ▀▄                 ╓Æ▀   ▌                  ▐
                             ▀N▄,      ,▄▄M"`       ▐                   ▌
                                  `  `               ▀                 ▐`
                                                      ▀▄              ╓▀
                                                        ▀▄,        ,▄M
                                                           `"*ⁿⁿ*╙`

*/
