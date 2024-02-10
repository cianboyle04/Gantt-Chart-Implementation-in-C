//prototypes for test functions
void test(struct task taskArray[], int num_of_tasks);

int findTest(struct task taskArray[], int num_of_tasks);

int printDependentTasks(struct task taskArray[], int taskId, int visitedTasks[]);

int checkCircular(struct task taskArray[], int taskId, int start_point);
