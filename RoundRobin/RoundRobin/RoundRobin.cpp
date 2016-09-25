// RoundRobin.cpp : Defines the entry point for the console application.
//


// Program to stimulate round robin scheduling algorithm 

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//These are the constant used for timeQuantum, context switch and the current time is taken as 0

int timeQuantum;
int contextSwitch = 2;
int currentTime = 0;
int noOfProcess;
int timeBurst;

//Structure to represent the process

struct PCB
{
	int pid;
	int timeNeeded;
	int burstTime;
	int sIndicator;
	int s;
	int f;
	struct PCB *next;
	struct PCB *prev;
};

//Structure to represent the execution time for each process

struct executionTime
{
	int pid;
	int timeTaken;
	struct executionTime *next;
	struct executionTime *prev;
};

//Method to add a new Execution time node to the existing execution double linked list using Malloc

void addExe(struct executionTime** exeStart, int p)
{
	struct executionTime * temp = (struct executionTime*)malloc(sizeof(struct executionTime));
	temp->pid = p;

	temp->next = (*exeStart);
	temp->prev = NULL;

	if ((*exeStart) != NULL)
		(*exeStart)->prev = temp;

	(*exeStart) = temp;

}

//Method to add a new process (PCB) node to the existing list of processes

void addFront(struct PCB** head_ref, int new_pid, int burst,int time,int sIndi)
{
	struct PCB *temp = (struct PCB*)malloc(sizeof(struct PCB));

	temp->pid = new_pid;
	temp->burstTime = burst;
	temp->timeNeeded = time;
	temp->sIndicator = sIndi;

	temp->next = (*head_ref);
	temp->prev = NULL;

	if ((*head_ref) != NULL)
		(*head_ref)->prev = temp;

	(*head_ref) = temp;
}

//Method to display the processes

void displayPCB(struct PCB* head_ref)
{
	struct PCB *temp;
	while (head_ref != NULL)
	{
		printf("PID is %d \n", head_ref->pid);
		printf("burst time is %d \n", head_ref->burstTime);
		printf("time required is %d\n", head_ref->timeNeeded);
		printf("starting time is %d\n", head_ref->s);
		printf("end time is %d\n", head_ref->f);
		head_ref = head_ref->next;
	}
}

//Method to display the execution times

void displayExe(struct executionTime* head_ref)
{
	while (head_ref != NULL)
	{
		printf("pid is %d\n", head_ref->pid);
		printf("time taken is %d\n", head_ref->timeTaken);
		head_ref = head_ref->prev;
	}

}


/*Method to simulate the process execution.
First,the context switch is added to the current time.The time required to switch to new process
Secondly,in the method,its checking whether the process is entering for the first time or not using the sIndicator
If the process is entering for the first time,the start indicator is changed to 0,and the start time of the process is set.
The,the time quantum decreases,the process is in execution.After every decrease,its checked whether the process is completely executed.
If the process is over,the end time of the process is set,and the execution time node is created for the process and
the start and end time details are inserted in the execution node.
If the process execution is not over,even if the time quantum is over,we return from the method*/
int processExecution(struct PCB *process, struct executionTime **et,int time)
{
	int label;
	currentTime = currentTime + contextSwitch;
	//printf("entering pid %d", process->pid);
	while (timeQuantum != 0)
	{
		if (process->sIndicator == 1)
		{
			process->s = currentTime;
			process->sIndicator = 0;
		}
		
		process->timeNeeded--;
		timeQuantum--;
		currentTime++;

		if (process->timeNeeded == 0)
		{
			process->f = currentTime;
			/*process is over.create exectuion time object */
			//printf("the current time and PID is %d and %d \n", currentTime, process->pid);
			(*et)->pid = process->pid;
			(*et)->timeTaken = process->f - process->s;
			struct executionTime  *newet = (struct executionTime*)malloc(sizeof(struct executionTime));
			(*et)->next = newet;
			newet->prev = (*et);
			newet->next = NULL;
			(*et) = newet;
			//printf("pid is %d \n", process->pid);
			process->next = NULL;
			timeQuantum = time;
			goto label;
		}

	}

	timeQuantum = time;

	//process->timeNeeded = process->timeNeeded - timeQuantum;
	//et->pid = process->pid;

	
	/*et->next=process->next;
	et->prev=process->prev; */
	return 1;

	label:return 0;
}


//This method moves the process to the end of the double linked list

struct PCB* moveLast(struct PCB **head_ref, struct PCB *process)
{
	
	if ((*head_ref) != process)
	{
		struct PCB* temp;
		process->next = (*head_ref);
		temp = process->prev;
		process->prev = NULL;
		//printf("head ref previous is %d \n", (*head_ref)->pid);

		(*head_ref)->prev = process;
		(*head_ref) = process;
		//printf("head ref is %d \n", head_ref->pid);
		return temp;
	}
	else
	{
		return process;
	}
}

//This method is to generate the number of processes

void generateProcess(int max, int min)
{
	noOfProcess = rand() % max + min;

}

//This method is to generate time quantum

void generateTimeQuantum(int max,int min)
{
	timeQuantum = rand() % max + min;
}

//This method is to generate CPU burst time for each process

void generateTimeBurst(int max)
{
	timeBurst = rand() % max + 1;
}

//Main Method

int main()
{
	int i;
	int avgBurstTime1=0;
	int avgExecutionTime1 = 0;
	struct PCB *head1 = NULL;
	struct PCB *head2 = NULL;
	struct PCB *head3 = NULL;
	struct PCB *head4 = NULL;
	

	//FOR THE 1ST DATA SET,WE ARE GENERATING THE PROCESSES AND TIME QUANTUM

	generateTimeQuantum(10,1);
	generateProcess(2, 20);

	//printf("time quantum is %d\n", timeQuantum);
	//printf("no.of processes is %d\n", noOfProcess);

	//CREATING PROCESS DOUBLE LINKED LIST

	for (i = 1; i <= noOfProcess; i++)
	{
		generateTimeBurst(15);
		addFront(&head1, i, timeBurst, timeBurst, 1);
		
	}

	

	//displayPCB(head);

	struct PCB *starting1=NULL;
	struct PCB *headTemp1 = head1;
	int check;

	struct executionTime *exeTime1 = (struct executionTime*)malloc(sizeof(struct executionTime));
	exeTime1->next = NULL;
	exeTime1->prev = NULL;
	/*addExe(&exeTime, 5);
	addExe(&exeTime, 4);
	addExe(&exeTime, 3);
	addExe(&exeTime, 2);
	addExe(&exeTime, 1);

	struct executionTime *exeHead = exeTime;
	displayExe(exeTime);*/

	while (head1 != NULL)
	{
		avgBurstTime1 += head1->burstTime;
		starting1 = head1;
		head1 = head1->next;
	}

	//CALCUATING THE AVERAGE BURST TIME

	avgBurstTime1 = avgBurstTime1 / noOfProcess;

	//printf("the average burst time is %d\n", avgBurstTime1);


	//printf("head content is %d", starting->pid);

	/*This loop checks if the processes in the list are over or not
	If the process execution is not over,the current process is pushed to end of list and next process goes for execution.
	If the processes are over,we go into the execution loop one more time for the last remaining process and then we break from the loop*/

	while (headTemp1 != NULL)
	{
		
		//printf("before check process");
		check=processExecution(starting1, &exeTime1,timeQuantum);
		//printf("the check value is %d \n", check);
		
		

		if (check == 0 && (starting1->prev != NULL))
		{
			//printf("starting prev is %d", starting->pid);
			//printf("exe pid is %d \n", exeTime->pid);
			starting1 = starting1->prev;
			
		}
		else
		{
			//printf("exe pid in check not zero is %d \n", exeTime->pid);
			starting1 = moveLast(&headTemp1, starting1);
			
			//printf("the headtemp pid is %d \n", headTemp->pid);
			//printf("the starting pid is %d \n", starting->pid);

			if (headTemp1->timeNeeded == 0)
			{
				exeTime1 = exeTime1->prev;
				break;
			}

			if (headTemp1 == starting1)
			{
				//printf("head temp pid is %d and time needed is %d", headTemp->pid, headTemp->timeNeeded);
				check=processExecution(headTemp1, &exeTime1,timeQuantum);
				//printf("check value last one is %d", check);
				exeTime1 = exeTime1->prev;
				break;
			}
		}
	
	}
		//printf("strting value now is %d", starting->pid);
	//displayExe(exeTime1); 

	struct executionTime *headExe1 = exeTime1;

	while (headExe1 != NULL)
	{
		avgExecutionTime1 += headExe1->timeTaken;
		
		headExe1 = headExe1->prev;
	}

	avgExecutionTime1 = avgExecutionTime1 / noOfProcess;

	//printf("average execution time is %d\n", avgExecutionTime1);

	//printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	//displayPCB(headTemp1);

	//THE ABOVE PROCESS IS REPEATED FOR ALL THE 4 DIFFERENT DATA SETS

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("DATA SET 1-SMALL TIME QUANTUM AND SMALL CPU BURST TIME\n");
	printf("DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime\n");
	printf("%d %d %s %d %d\n", noOfProcess, timeQuantum, "0-15", avgBurstTime1, avgExecutionTime1);


	//END OF FIRST DATA SET

	//START OF SECOND DATA SET

	int avgBurstTime2 = 0;
	int avgExecutionTime2 = 0;

	generateTimeQuantum(50,20);
	generateProcess(2, 20);

	//printf("time quantum is %d\n", timeQuantum);
	//printf("no.of processes is %d\n", noOfProcess);


	for (i = 1; i <= noOfProcess; i++)
	{
		generateTimeBurst(20);
		addFront(&head2, i, timeBurst, timeBurst, 1);

	}



	//displayPCB(head);

	struct PCB *starting2 = NULL;
	struct PCB *headTemp2 = head2;
	

	struct executionTime *exeTime2 = (struct executionTime*)malloc(sizeof(struct executionTime));
	exeTime2->next = NULL;
	exeTime2->prev = NULL;
	/*addExe(&exeTime, 5);
	addExe(&exeTime, 4);
	addExe(&exeTime, 3);
	addExe(&exeTime, 2);
	addExe(&exeTime, 1);

	struct executionTime *exeHead = exeTime;
	displayExe(exeTime);*/

	while (head2 != NULL)
	{
		avgBurstTime2 += head2->burstTime;
		starting2 = head2;
		head2 = head2->next;
	}

	avgBurstTime2 = avgBurstTime2 / noOfProcess;

	//printf("the average burst time is %d\n", avgBurstTime2);


	//printf("head content is %d", starting->pid);

	while (headTemp2 != NULL)
	{

		//printf("before check process");
		check = processExecution(starting2, &exeTime2,timeQuantum);
		//printf("the check value is %d \n", check);



		if (check == 0 && (starting2->prev != NULL))
		{
			//printf("starting prev is %d", starting->pid);
			//printf("exe pid is %d \n", exeTime->pid);
			starting2 = starting2->prev;

		}
		else
		{
			//printf("exe pid in check not zero is %d \n", exeTime->pid);
			starting2 = moveLast(&headTemp2, starting2);

			//printf("the headtemp pid is %d \n", headTemp->pid);
			//printf("the starting pid is %d \n", starting->pid);

			if (headTemp2->timeNeeded == 0)
			{
				exeTime2 = exeTime2->prev;
				break;
			}

			if (headTemp2 == starting2)
			{
				//printf("head temp pid is %d and time needed is %d", headTemp->pid, headTemp->timeNeeded);
				check = processExecution(headTemp2, &exeTime2,timeQuantum);
				//printf("check value last one is %d", check);
				exeTime2 = exeTime2->prev;
				break;
			}
		}

	}
	//printf("strting value now is %d", starting->pid);
	//displayExe(exeTime2);

	struct executionTime *headExe2 = exeTime2;

	while (headExe2 != NULL)
	{
		avgExecutionTime2 += headExe2->timeTaken;

		headExe2 = headExe2->prev;
	}

	avgExecutionTime2 = avgExecutionTime2 / noOfProcess;

	//printf("average execution time is %d\n", avgExecutionTime2);

	//printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	//displayPCB(headTemp2);

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("DATA SET 2-LARGE TIME QUANTUM AND SMALL CPU BURST TIME\n");
	printf("DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime\n");
	printf("%d %d %s %d %d\n", noOfProcess, timeQuantum, "0-20", avgBurstTime2, avgExecutionTime2);

	//END OF SECOND DATA SET


	//START OF THIRD DATA SET


	int avgBurstTime3 = 0;
	int avgExecutionTime3 = 0;

	generateTimeQuantum(10,1);
	generateProcess(2, 20);

	//printf("time quantum is %d\n", timeQuantum);
	//printf("no.of processes is %d\n", noOfProcess);


	for (i = 1; i <= noOfProcess; i++)
	{
		generateTimeBurst(35);
		addFront(&head3, i, timeBurst, timeBurst, 1);

	}



	//displayPCB(head);

	struct PCB *starting3 = NULL;
	struct PCB *headTemp3 = head3;


	struct executionTime *exeTime3 = (struct executionTime*)malloc(sizeof(struct executionTime));
	exeTime3->next = NULL;
	exeTime3->prev = NULL;
	/*addExe(&exeTime, 5);
	addExe(&exeTime, 4);
	addExe(&exeTime, 3);
	addExe(&exeTime, 2);
	addExe(&exeTime, 1);

	struct executionTime *exeHead = exeTime;
	displayExe(exeTime);*/

	while (head3 != NULL)
	{
		avgBurstTime3 += head3->burstTime;
		starting3 = head3;
		head3 = head3->next;
	}

	avgBurstTime3 = avgBurstTime3 / noOfProcess;

	//printf("the average burst time is %d\n", avgBurstTime3);


	//printf("head content is %d", starting->pid);

	while (headTemp3 != NULL)
	{

		//printf("before check process");
		check = processExecution(starting3, &exeTime3, timeQuantum);
		//printf("the check value is %d \n", check);



		if (check == 0 && (starting3->prev != NULL))
		{
			//printf("starting prev is %d", starting->pid);
			//printf("exe pid is %d \n", exeTime->pid);
			starting3 = starting3->prev;

		}
		else
		{
			//printf("exe pid in check not zero is %d \n", exeTime->pid);
			starting3 = moveLast(&headTemp3, starting3);

			//printf("the headtemp pid is %d \n", headTemp->pid);
			//printf("the starting pid is %d \n", starting->pid);

			if (headTemp3->timeNeeded == 0)
			{
				exeTime3 = exeTime3->prev;
				break;
			}

			if (headTemp3 == starting3)
			{
				//printf("head temp pid is %d and time needed is %d", headTemp->pid, headTemp->timeNeeded);
				check = processExecution(headTemp3, &exeTime3, timeQuantum);
				//printf("check value last one is %d", check);
				exeTime3 = exeTime3->prev;
				break;
			}
		}

	}
	//printf("strting value now is %d", starting->pid);
	//displayExe(exeTime3);

	struct executionTime *headExe3 = exeTime3;

	while (headExe3 != NULL)
	{
		avgExecutionTime3 += headExe3->timeTaken;

		headExe3 = headExe3->prev;
	}

	avgExecutionTime3 = avgExecutionTime3 / noOfProcess;

	//printf("average execution time is %d\n", avgExecutionTime3);

	//printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	//displayPCB(headTemp3);

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("DATA SET 3-SMALL TIME QUANTUM AND LARGE CPU BURST TIME\n");
	printf("DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime\n");
	printf("%d %d %s %d %d\n", noOfProcess, timeQuantum, "0-35", avgBurstTime3, avgExecutionTime3);


	//END OF DATA  SET 3

	//START OF DATA SET 4

	
	int avgBurstTime4 = 0;
	int avgExecutionTime4 = 0;

	generateTimeQuantum(50,30);
	generateProcess(2, 20);

	//printf("time quantum is %d\n", timeQuantum);
	//printf("no.of processes is %d\n", noOfProcess);


	for (i = 1; i <= noOfProcess; i++)
	{
		generateTimeBurst(40);
		addFront(&head4, i, timeBurst, timeBurst, 1);

	}



	//displayPCB(head);

	struct PCB *starting4 = NULL;
	struct PCB *headTemp4 = head4;


	struct executionTime *exeTime4 = (struct executionTime*)malloc(sizeof(struct executionTime));
	exeTime4->next = NULL;
	exeTime4->prev = NULL;
	/*addExe(&exeTime, 5);
	addExe(&exeTime, 4);
	addExe(&exeTime, 3);
	addExe(&exeTime, 2);
	addExe(&exeTime, 1);

	struct executionTime *exeHead = exeTime;
	displayExe(exeTime);*/

	while (head4 != NULL)
	{
		avgBurstTime4 += head4->burstTime;
		starting4 = head4;
		head4 = head4->next;
	}

	avgBurstTime4 = avgBurstTime4 / noOfProcess;

	//printf("the average burst time is %d\n", avgBurstTime4);


	//printf("head content is %d", starting->pid);

	while (headTemp4 != NULL)
	{

		//printf("before check process");
		check = processExecution(starting4, &exeTime4, timeQuantum);
		//printf("the check value is %d \n", check);



		if (check == 0 && (starting4->prev != NULL))
		{
			//printf("starting prev is %d", starting->pid);
			//printf("exe pid is %d \n", exeTime->pid);
			starting4 = starting4->prev;

		}
		else
		{
			//printf("exe pid in check not zero is %d \n", exeTime->pid);
			starting4 = moveLast(&headTemp4, starting4);

			//printf("the headtemp pid is %d \n", headTemp->pid);
			//printf("the starting pid is %d \n", starting->pid);

			if (headTemp4->timeNeeded == 0)
			{
				exeTime4 = exeTime4->prev;
				break;
			}

			if (headTemp4 == starting4)
			{
				//printf("head temp pid is %d and time needed is %d", headTemp->pid, headTemp->timeNeeded);
				check = processExecution(headTemp4, &exeTime4, timeQuantum);
				//printf("check value last one is %d", check);
				exeTime4 = exeTime4->prev;
				break;
			}
		}

	}
	//printf("strting value now is %d", starting->pid);
	//displayExe(exeTime3);

	struct executionTime *headExe4 = exeTime4;

	while (headExe4 != NULL)
	{
		avgExecutionTime4 += headExe4->timeTaken;

		headExe4 = headExe4->prev;
	}

	avgExecutionTime4 = avgExecutionTime4 / noOfProcess;

	//printf("average execution time is %d\n", avgExecutionTime4);

	//printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n");
	//displayPCB(headTemp3);

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("DATA SET 4-LARGE TIME QUANTUM AND LARGE CPU BURST TIME\n");
	printf("DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime\n");
	printf("%d %d %s %d %d\n", noOfProcess, timeQuantum, "0-40", avgBurstTime4, avgExecutionTime4);


	return 0;
}

/*OUTPUT*/

/*
DATA SET 1-SMALL TIME QUANTUM AND SMALL CPU BURST TIME
DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime
21			2			0-15				7					175
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
DATA SET 2-LARGE TIME QUANTUM AND SMALL CPU BURST TIME
DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime
20			 23			0-20				11						11
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
DATA SET 3-SMALL TIME QUANTUM AND LARGE CPU BURST TIME
DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime
21			5			0-35				16						256
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
DATA SET 4-LARGE TIME QUANTUM AND LARGE CPU BURST TIME
DATASET  TimeQuantum RangEofCPUBurstTime AverageCPUBurstTime AverageTotalExecutionTime
20			 44			0-40				18						18

*/
