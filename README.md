## program

```

Lab Assignment - 9

Write a C Program to implement FCFS process scheduling algorithm.

Code: 
#include <stdio.h>

struct Process {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int rt;
    int start_time;
};

void sortByArrival(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void findCompletionTimes(struct Process p[], int n) {
    int current_time = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_time < p[i].at) {
            current_time = p[i].at;
        }
        
        p[i].start_time = current_time;
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        p[i].rt = p[i].wt;
        
        current_time = p[i].ct;
    }
}

void displayProcesses(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0, total_rt = 0;
    int schedule_length = p[n - 1].ct;
    float throughput = (float)n / schedule_length; 

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].start_time,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);

        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].rt;
    }

    printf("\nAverage Waiting Time (AWT) : %.2f", total_wt / n);
    printf("\nAverage Turnaround Time (ATAT): %.2f", total_tat / n);
    printf("\nAverage Response Time (ART) : %.2f", total_rt / n);
    printf("\nSchedule Length (SL) : %d", schedule_length);
    printf("\nThroughput : %.2f processes/unit time\n", throughput);
}

void drawGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("--------");
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
        if (i < n - 1 && p[i].ct < p[i + 1].at) {
            printf(" Ideal |");
        }
    }
    
    printf("\n ");
    
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("--------");
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("    %d", p[i].ct);
        if (i < n - 1 && p[i].ct < p[i + 1].at) {
            printf("       %d", p[i + 1].at);
        }
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("\nEnter Process ID, Arrival Time & Burst Time for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].pid, &p[i].at, &p[i].bt);
    }

    sortByArrival(p, n);

    findCompletionTimes(p, n);

    displayProcesses(p, n);

    drawGanttChart(p, n);

    return 0;
}



Lab Assignment - 10

Write C Program to implement Round Robin Process Scheduling Algorithm.

Code: 

#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt, rt, rem_bt, start_time;
};

void roundRobin(struct Process p[], int n, int quantum) {
    int time = 0, completed = 0;
    
    for (int i = 0; i < n; i++) 
        p[i].rem_bt = p[i].bt;

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].rem_bt > 0 && p[i].at <= time) {
                executed = 1;
                
                if (p[i].rem_bt == p[i].bt)
                    p[i].start_time = time; 

                if (p[i].rem_bt > quantum) {
                    time += quantum;
                    p[i].rem_bt -= quantum;
                } else {
                    time += p[i].rem_bt;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    p[i].rt = p[i].start_time - p[i].at;
                    p[i].rem_bt = 0;
                    completed++;
                }
            }
        }

        if (!executed) 
            time++;
    }
}

void display(struct Process p[], int n) {
    float total_wt = 0, total_tat = 0, total_rt = 0;
    int schedule_length = p[n - 1].ct;
    float throughput = (float)n / schedule_length; 

    printf("\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
            p[i].id, p[i].at, p[i].bt, p[i].start_time,
            p[i].ct, p[i].tat, p[i].wt, p[i].rt);
        
        total_wt += p[i].wt;
        total_tat += p[i].tat;
        total_rt += p[i].rt;
    }

    printf("\nAverage Waiting Time (AWT) : %.2f", total_wt / n);
    printf("\nAverage Turnaround Time (ATAT): %.2f", total_tat / n);
    printf("\nAverage Response Time (ART) : %.2f", total_rt / n);
    printf("\nSchedule Length (SL) : %d", schedule_length);
    printf("\nThroughput : %.2f processes/unit time\n", throughput);
}

void drawGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");
    
    printf(" ");
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("--------");
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].id);
        if (i < n - 1 && p[i].ct < p[i + 1].at) {
            printf(" Ideal |");
        }
    }
    
    printf("\n ");
    
    for (int i = 0; i < n; i++) {
        printf("--------");
    }
    printf("--------");
    printf("\n");

    printf("0");
    for (int i = 0; i < n; i++) {
        printf("    %d", p[i].ct);
        if (i < n - 1 && p[i].ct < p[i + 1].at) {
            printf("       %d", p[i + 1].at);
        }
    }
    printf("\n");
}

int main() {
    int n, quantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter AT and BT for P%d: ", i + 1);
        scanf("%d%d", &p[i].at, &p[i].bt);
        p[i].id = i + 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobin(p, n, quantum);
    display(p, n);
    drawGanttChart(p, n);

    return 0;
}


Lab Assignment - 11

Write a C program to simulate  Priority Scheduling Algorithm.(Non Pre-emptive)

Code: 
#include <stdio.h>

struct Process {
    int pid;        
    int at;         
    int bt;        
    int priority;   
    int wt;        
    int tat;        
};

void sortProcesses(struct Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at || (p[i].at == p[j].at && p[i].priority > p[j].priority)) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n) {
    int completion_time = 0;
    p[0].wt = 0; 
    for (int i = 0; i < n; i++) {
        if (completion_time < p[i].at) {
            completion_time = p[i].at; 
        }
        p[i].wt = completion_time - p[i].at;
        completion_time += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
}

void printProcesses(struct Process p[], int n) {
    printf("\nProcess Details:\n");
    printf("PID\tAT\tBT\tPriority\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].priority, p[i].wt, p[i].tat);
    }
}

void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt - 1; j++) printf(" ");
        printf("P%d", p[i].pid);
        for (int j = 0; j < p[i].bt - 1; j++) printf(" ");
        printf("|");
    }

    printf("\n ");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p[i].bt; j++) printf("--");
        printf(" ");
    }
    printf("\n0");

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].bt;
        printf("%*d", p[i].bt * 2, time);
    }
    printf("\n");
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time, Burst Time and Priority for Process %d: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].pid = i + 1;
    }

    sortProcesses(p, n);
    calculateTimes(p, n);
    printProcesses(p, n);
    printGanttChart(p, n);

    return 0;      }



Lab Assignment - 12


Write a C++ program to simulate Worst fit memory allocation strategies.

Code: 
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int nb, np;

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> p(np);

    for (int i = 0; i < np; i++) {
        cout << "\nEnter size of process " << (i + 1) << ": ";
        cin >> p[i];
    }

    cout << "\nEnter number of blocks: ";
    cin >> nb;
    vector<int> b(nb), bf(nb, 0), bn(np, -1), frag(np);

    for (int i = 0; i < nb; i++) {
        cout << "\nEnter size of block " << (i + 1) << ": ";
        cin >> b[i];
    }

    for (int i = 0; i < np; i++) {
        int largest = 0;  
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {  
                if (b[j] > largest) {  
                    bn[i] = j;
                    largest = b[j];
                }
            }
        }
       
        frag[i] = largest - p[i];  
        if (bn[i] != -1) {  
            bf[bn[i]] = 1;
        }
    }

    cout << "\nProcess No. Process Size Block No. Block Size Fragmentation\n";
    for (int i = 0; i < np; i++) {
        if (bn[i] != -1)
            cout << (i + 1) << "          " << p[i]
                 << "          " << (bn[i] + 1) << "         " << b[bn[i]]
                 << "         " << frag[i] << endl;
        else
            cout << (i + 1) << "          " << p[i]
                 << "          Not Allocated" << endl;
    }

    return 0;
}






 
Lab Assignment - 13


Write a C++ program to simulate first fit memory allocation strategies.

Code: 
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int nb, np;

    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> p(np);

    for (int i = 0; i < np; i++) {
        cout << "\nEnter size of process " << (i + 1) << ": ";
        cin >> p[i];
    }

    cout << "\nEnter number of blocks: ";
    cin >> nb;
    vector<int> b(nb), bf(nb, 0), bn(np, -1), frag(np);

    for (int i = 0; i < nb; i++) {
        cout << "\nEnter size of block " << (i + 1) << ": ";
        cin >> b[i];
    }

    for (int i = 0; i < np; i++) {
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                bn[i] = j;
                frag[i] = b[j] - p[i];
                bf[j] = 1;
                break;
            }
        }
    }

    cout << "\nProcess No. Process Size Block No. Block Size Fragmentation\n";
    for (int i = 0; i < np; i++) {
        if (bn[i] != -1)
            cout << (i + 1) << "          " << p[i]
                 << "          " << (bn[i] + 1) << "         " << b[bn[i]]
                 << "         " << frag[i] << endl;
        else
            cout << (i + 1) << "          " << p[i]
                 << "          Not Allocated" << endl;
    }

    return 0;
}


 
Lab Assignment - 14


Write a C++ program to simulate best  fit memory allocation strategies.

Code: 
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int nb, np;
 
    cout << "Enter number of processes: ";
    cin >> np;
    vector<int> p(np);

    for (int i = 0; i < np; i++) {
        cout << "\nEnter size of process " << (i + 1) << ": ";
        cin >> p[i];
    }

    cout << "\nEnter number of blocks: ";
    cin >> nb;
    vector<int> b(nb), bf(nb, 0), bn(np, -1), frag(np);
   
    for (int i = 0; i < nb; i++) {
        cout << "\nEnter size of block " << (i + 1) << ": ";
        cin >> b[i];
    }

    for (int i = 0; i < np; i++) {
        int smallest = 1000;
        for (int j = 0; j < nb; j++) {
            if (bf[j] == 0 && b[j] >= p[i]) {
                if (b[j] < smallest) {
                    bn[i] = j;
                    smallest = b[j];
                }
            }
        }
       
         frag[i] = smallest - p[i];
        if (bn[i] != -1) {
            bf[bn[i]] = 1;
        }
    }
 cout << "\nProcess No. Process Size Block No. Block Size Fragmentation\n";
    for (int i = 0; i < np; i++) {
        if (bn[i] != -1)
            cout << (i + 1) << "          " << p[i]
                 << "          " << (bn[i] + 1) << "         " << b[bn[i]]
                 << "         " << frag[i] << endl;
        else
            cout << (i + 1) << "          " << p[i]
                 << "          Not Allocated" << endl;
    }

    return 0;
}
 
 


Lab Assignment - 15

Write a C program to simulate LRU Page Replacement Algorithm.

Code: 

#include <stdio.h>

int main() {
    int nf, np;
    int f[10], p[30], time[10];
    int hit = 0, fault = 0;
    int flag1 = 0, flag2 = 0;
    int cnt = 0, loc = 0, minimum;

    printf("Enter number of pages: ");
    scanf("%d", &np);

    printf("Enter the page sequence: ");
    for (int i = 0; i < np; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    for (int i = 0; i < nf; i++) {
        f[i] = -1;
        time[i] = 0;
    }

    printf("\nPage Replacement Process:\n");

    for (int i = 0; i < np; i++) {
        flag1 = flag2 = 0;

        for (int j = 0; j < nf; j++) {
            if (f[j] == p[i]) {
                cnt++;
                time[j] = cnt;
                hit++;
                flag1 = flag2 = 1;
                break;
            }
        }

        if (flag1 == 0) {
            for (int j = 0; j < nf; j++) {
                if (f[j] == -1) {
                    cnt++;
                    fault++;
                    f[j] = p[i];
                    time[j] = cnt;
                    flag2 = 1;
                    break;
                }
            }
        }

        if (flag2 == 0) {
            minimum = time[0];
            loc = 0;
            for (int j = 1; j < nf; j++) {
                if (time[j] < minimum) {
                    minimum = time[j];
                    loc = j;
                }
            }
            cnt++;
            fault++;
            f[loc] = p[i];
            time[loc] = cnt;
        }

        printf("%d : ", p[i]);
        for (int j = 0; j < nf; j++) {
            if (f[j] != -1)
                printf("%d ", f[j]);
            else
                printf("-1 ");
        }
        printf("\n");
    }

    float total = (float)(hit + fault);
    float hitRatio = (hit / total) * 100;
    float faultRatio = (fault / total) * 100;

    printf("\nTotal Hits: %d", hit);
    printf("\nTotal Faults: %d", fault);
    printf("\nHit Ratio: %.2f", hitRatio);
    printf("\nFault Ratio: %.2f\n", faultRatio);

    return 0;
}





Lab Assignment - 16

Write a C program to simulate FIFO Page Replacement Algorithm.

Code: 

#include <stdio.h>

int main() {
    int nf, np;
    int f[10], p[30];
    int hit = 0, fault = 0, flag = 0, position = 0;

    printf("Enter number of pages: ");
    scanf("%d", &np);

    printf("Enter the page sequence: ");
    for (int i = 0; i < np; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &nf);

    for (int i = 0; i < nf; i++) {
        f[i] = -1;
    }

    printf("\nPage Replacement Process:\n");

    for (int i = 0; i < np; i++) {
        flag = 0;

        for (int j = 0; j < nf; j++) {
            if (f[j] == p[i]) {
                hit++;
                flag = 1;
                break;
            }
        }

        if (flag == 0) {
            f[position] = p[i];
            fault++;
            position++;

            if (position == nf)
                position = 0;
        }

        printf("%d : ", p[i]);
        for (int j = 0; j < nf; j++) {
            if (f[j] != -1)
                printf("%d ", f[j]);
            else
                printf("-1 ");
        }
        printf("\n");
    }

    float total = (float)(hit + fault);
    float hitRatio = (hit / total) * 100;
    float faultRatio = (fault / total) * 100;

    printf("\nTotal Hits: %d", hit);
    printf("\nTotal Faults: %d", fault);
    printf("\nHit Ratio: %.2f", hitRatio);
    printf("\nFault Ratio: %.2f\n", faultRatio);

    return 0;
}





 

Lab Assignment - 17


Write a C program to simulate Bankers  Algorithm to avoid the deadlock.

Code: 

#include <stdio.h>
int main() {
    int np, nr;
    int allocation[10][10], max[10][10], need[10][10];
    int available[10], finish[10], flag = 0;
    int safeseq[10], i, j, k = 0;

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resources: ");
    scanf("%d", &nr);

    printf("Enter Allocation matrix:\n");
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available resources:\n");
    for (j = 0; j < nr; j++) {
        scanf("%d", &available[j]);
    }

    for (i = 0; i < np; i++) {
        finish[i] = 0;
    }

    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    printf("Need Matrix:\n");
    for (i = 0; i < np; i++) {
        for (j = 0; j < nr; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    for (i = 0; i < np; i++) {
        flag = 0;
        if (finish[i] == 0) {
            for (j = 0; j < nr; j++) {
                if (need[i][j] > available[j]) {
                    flag = 1;
                    break;
                }
            }
            if (flag == 0) {
                finish[i] = 1;
                for (j = 0; j < nr; j++) {
                    available[j] += allocation[i][j];
                }
                safeseq[k++] = i;
                i = -1;
            }
        }
    }

    int deadlock = 0;
    for (i = 0; i < np; i++) {
        if (finish[i] == 0) {
            deadlock = 1;
            break;
        }
    }

    if (deadlock) {
        printf("System is in Deadlock.\n");
    } else {
        printf("System is in Safe State.\n");
        printf("Safe sequence: ");
        for (i = 0; i < np; i++) {
            printf("P%d ", safeseq[i]);
        }
        printf("\n");
    }

    return 0;
}



Lab Assignment - 18


Write a C program to simulate FCFS disk scheduling algorithm.

Code: 

#include<stdio.h>
#include<stdlib.h>

int main(){
    int n;
    int disc_req[200];
    int head;
    int tracks;
    int THM =0;

    printf("Enter total number of requests : ");
    scanf("%d",&n);

    printf("Enter disc requests : ");
    for(int i=0;i<n;i++){
        scanf("%d",&disc_req[i]);
    }

    printf("Enter head position : ");
    scanf("%d",&head);

    printf("Enter number of tracks : ");
    scanf("%d",&tracks);

    printf("\nSeek Sequnce : %d",head);

    for(int i=0;i<n;i++){
        THM+= abs(head -disc_req[i]);
        head = disc_req[i];
        printf("-> %d",head);
    }
    printf("\nTotal head movement : %d\n",THM);
    return 0;

}





Lab Assignment - 19


Write a C program to simulate SSTF disk scheduling algorithm.

Code: 

#include<stdio.h>
#include<stdlib.h> 

int main()
{
    int n;
    int disc_req[200];
    int head;
    int tracks;
    int pending;
    int diff;
    int min;
    int index;
    int thm = 0;
    int finish[200] = {0}; 

    printf("Enter total number of requests: ");
    scanf("%d", &n);
    
    printf("Enter number of disc requests: ");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &disc_req[i]);
    }

    printf("Enter head position: ");
    scanf("%d", &head);
    
    printf("Enter number of tracks: ");
    scanf("%d", &tracks);
    
    pending = n;
    
    printf("\nSeek Sequence: %d", head);

    while(pending > 0) 
    {
        min = 1000; 
        
        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                diff = abs(head - disc_req[i]);
                if(diff < min)
                {
                    min = diff;
                    index = i;
                }
            }
        }

        thm = thm + abs(head - disc_req[index]);
        finish[index] = 1;
        pending--;
        head = disc_req[index];
        printf(" -> %d", head); 
    }
    
    printf("\nTotal head movement: %d\n", thm);
    
    return 0;
}




Lab Assignment - 20


Write C program to convert logical adderss into physical address in paging.Use addressmapping function.

Code: 

#include <stdio.h>

int main() {
    int n;
    int pageTable[10];
    int pageNum, frameNum, offset, logicalAddress, physicalAddress, pageSize;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    if (n > 10) {
        printf("Error: Maximum number of pages is 10.\n");
        return -1;
    }

    printf("Enter the frame numbers for the page table:\n");
    for (int i = 0; i < n; i++) {
        printf("Frame number for page %d: ", i);
        scanf("%d", &pageTable[i]);
    }

    printf("Enter the page size: ");
    scanf("%d", &pageSize);

    printf("Enter the logical address: ");
    scanf("%d", &logicalAddress);

    pageNum = logicalAddress / pageSize;
    offset = logicalAddress % pageSize;

    if (pageNum >= n) {
        printf("Invalid logical address! Page number exceeds the number of pages.\n");
        return -1;
    }

    frameNum = pageTable[pageNum];

    physicalAddress = (frameNum * pageSize) + offset;

    printf("\nLogical Address: %d\n", logicalAddress);
    printf("Page Number: %d\n", pageNum);
    printf("Offset: %d\n", offset);
    printf("Frame Number: %d\n", frameNum);
    printf("Physical Address: %d\n", physicalAddress);

    return 0;
}


```

## phase1

```
CP 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_memory_block();
void print_instruction_register();
void print_general_purpose_register();
void Load();
void INIT();
void START_EXECUTION();
void EXECUTE_USER_PROGRAM();
void MOS();
void GD();
void PD();
void H();
void BT();
void SR();
void LR();
void CR();

int flag = 0;
int currentLine;

char M[100][4];  
char IR[4];      
char R[4];       
char buffer[40]; 
int IC;          
int C;           
int SI;

void print_memory_block()
{
    printf("Memory block is:\n\n");
    int i, j;
    for (i = 0; i < 100; i++)
    {
        if (i >= 10)
            printf("%d  ", i);
        else
            printf("%d   ", i);
        for (j = 0; j < 4; j++)
        {
            printf("|%c", M[i][j]);
        }
        printf("|\n");
    }
}

void print_instruction_register()
{
    for (int i = 0; i < 4; i++)
    {
        printf("%c", IR[i]);
    }
    printf("\n");
}

void print_general_purpose_register()
{
    for (int i = 0; i < 4; i++)
    {
        printf("%c", R[i]);
    }
    printf("\n");
}

void Load()
{
    int i = 0;
    FILE *fp = NULL;
    char ch;
    fp = fopen("input.txt", "r");
    char str[100];
    while (fgets(str, 41, fp) != NULL)
    {
        if (str[0] == '$' && str[1] == 'A' && str[2] == 'M' && str[3] == 'J')
        {
            printf("AMJ instruction found\n");
            getchar();
            int row = 0;
            int col = 0;

            while (1)
            {
                fgets(str, 100, fp);

                if ((str[0] == '$' && str[1] == 'D' && str[2] == 'T' && str[3] == 'A'))
                    break;

                for (int i = 0; i < strlen(str) - 1; i++)
                {
                    if (str[i] == ' ')
                        break;
                    M[row][col] = str[i];
                    col++;
                    if (col == 4)
                    {
                        row++;
                        col = 0;
                    }
                }
            }

            currentLine = ftell(fp);
            printf("Loading is completed\n");
        }
        if ((str[0] == '$' && str[1] == 'D' && str[2] == 'T' && str[3] == 'A'))
        {
            START_EXECUTION();
        }
        if ((str[0] == '$' && str[1] == 'E' && str[2] == 'N' && str[3] == 'D'))
        {
            i++;
            print_memory_block();
            printf("\n\n\nEND OF JOB no. %d\n\n\n", i);
            printf("Press Enter to load another job:\n");
            getchar();
            INIT();
        }
    }
}

void INIT()
{
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = ' ';  
        }
    }
    for (int i = 0; i < 4; i++)
    {
        IR[i] = ' ';  
        R[i] = ' ';   
    }
    IC = 0;
    SI = 0;
    C = 0;
    currentLine = 0;
}

void START_EXECUTION()
{
    IC = 0;
    EXECUTE_USER_PROGRAM();
}

void EXECUTE_USER_PROGRAM()
{
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            IR[i] = M[IC][i];
        }

        printf("\n\nInstruction register has:\n\n");
        print_instruction_register();

        if (IR[0] == ' ' && IR[1] == ' ')
        {
            printf("Error: Instruction register contains invalid data.\n");
            break;
        }

        IC++;

        if (IR[0] == 'G' && IR[1] == 'D')
        {
            SI = 1;
            MOS();
        }
        else if (IR[0] == 'P' && IR[1] == 'D')
        {
            SI = 2;
            MOS();
        }
        else if (IR[0] == 'H' && IR[1] == '*')
        {
            SI = 3;
            MOS();
            break;  
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            LR();
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            SR();
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            BT();
        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            CR();
        }
        else
        {
            printf("Unknown instruction encountered.\n");
            break;
        }
    }
}


void MOS()
{
    if (SI == 1)
    {
        GD();
    }
    else if (SI == 2)
    {
        PD();
    }
    else if (SI == 3)
    {
        H();
    }
}

void GD()
{
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    int col = 0;
    char str[100];
    FILE *fp = NULL;
    fp = fopen("input.txt", "r");

    fseek(fp, currentLine, SEEK_SET);
    fgets(str, 100, fp);
    for (int i = 0; i < strlen(str) - 1; i++)
    {
        M[row][col] = str[i];
        col++;
        if (col == 4)
        {
            row++;
            col = 0;
        }
    }
    currentLine = ftell(fp);
}

void PD()
{
    FILE *fp = NULL;
    fp = fopen("output.txt", "a");
    if (flag == 0)
        flag++;
    else
        fprintf(fp, "\n");

    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    int col = 0;
    for (int i = row; i < row + 10; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (M[i][j] == '_')
                break;
            fputc(M[i][j], fp);
        }
    }
}

void H()
{
    FILE *fp = NULL;
    fp = fopen("output.txt", "a");
    fputc('\n', fp);
    fputc('\n', fp);
}

void LR()
{
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = 0; i < 4; i++)
    {
        R[i] = M[row][i];
    }
}

void SR()
{
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');
    for (int i = 0; i < 4; i++)
    {
        M[row][i] = R[i];
    }
}

void CR()
{
    int row = (IR[2] - '0') * 10 + (IR[3] - '0');

    for (int i = 0; i < 4; i++)
    {
        if (R[i] != M[row][i])
        {
            C = 0;
            break;
        }
        else
        {
            C = 1;
        }
    }
}

void BT()
{
    if (C == 1)
    {
        IC = (IR[2] - '0') * 10 + (IR[3] - '0');
        C = 0;
    }
}

int main()
{
    printf("implementation of OS phase 1 by group 9\n");
    printf(" input.txt is:\n");

    FILE *f = NULL;
    char ch;
    f = fopen("input.txt", "r");
    if (f == NULL)
    {
        printf("File not found");
        exit(1);
    }
    while ((ch = fgetc(f)) != EOF)
    {
        printf("%c", ch);
    }
    fclose(f);

    printf("\n\n\nPress Enter to continue\n\n");

    INIT();
    Load();

    return 0;
}




Lab Assignment 6

1.	Assume Hello Students SY B Div  Welcome to OS Lab  placed in input.txt file. Write a C++ program to read the file line by line and display output on screen.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.txt"); 
    string line;

    while (getline(inputFile, line)) {
        cout << line << endl;
    }

    inputFile.close();
    return 0;
}


2.	Assume buffer is holding temporary data. Write a C++ program to store line from input.txt file into buffer. Also display buffer output on screen.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("input.txt"); 
    string line;
    vector<string> buffer;

    while (getline(inputFile, line)) {
        buffer.push_back(line);
    }
    inputFile.close();  

    for (const string& bufferedLine : buffer) {
        cout << bufferedLine << endl;
    }

    return 0;
}

3.	Assume external memory is 100 by 4. Write a C++ Program to store buffer content into external memory location 00.


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
    ifstream inputFile("input.txt"); 
    string line, fullText;
    vector<string> buffer;

    while (getline(inputFile, line)) {
        buffer.push_back(line);
    }
    inputFile.close();

    for (const string& text : buffer) {
        fullText += text + " ";
    }

    string externalMemory[100][4];
    int externalRow = 0, externalCol = 0, currentCharIndex = 0, textLength = fullText.length();

    while (currentCharIndex < textLength && externalRow < 100) {
        externalMemory[externalRow][externalCol] = fullText.substr(currentCharIndex, 4);
        currentCharIndex += 4;
        externalCol = (externalCol + 1) % 4;
        if (externalCol == 0) externalRow++;
    }

    for (int r = 0; r < 100; ++r) {
        for (int c = 0; c < 4; ++c) {
            cout << "Memory Location [" << r << "][" << c << "]: " 
                 << (externalMemory[r][c].empty() ? "****" : externalMemory[r][c]) << endl;
        }
    }

    return 0;
}


4.	Write C++ Program to write content into output.txt file from external memory. Memory block 0 consist Hello Students SY B Div   data.


#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream inputFile("input.txt");  
    string buffer;

    getline(inputFile, buffer);  
    inputFile.close();  

    string externalMemory[100][4];  
    int externalRow = 0, externalCol = 0, currentCharIndex = 0;

    for (char ch : buffer) {
        if (externalRow >= 100) break;
        externalMemory[externalRow][externalCol] += ch;
        currentCharIndex++;

        if (currentCharIndex % 4 == 0) {
            externalCol++;
            if (externalCol == 4) {
                externalCol = 0;
                externalRow++;
            }
        }
    }

    ofstream outputFile("output.txt");
    for (int r = 0; r <= externalRow; ++r) { 
        for (int c = 0; c < 4; ++c) {
            if (!externalMemory[r][c].empty()) {
                outputFile << externalMemory[r][c];
            }
        }
    }
    outputFile.close();  

    cout << "Content written to output.txt successfully." << endl;
    return 0;
}




Lab Assignment 7


Q. Write a program to Load job  in external memory. Assume size of external memory is 100 by 4 and starting address of program is 00.

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#define MAX_MEMORY 100 
#define MAX_REG 4 
#define MAX_BUFFER 40

char M[MAX_MEMORY][MAX_REG]; 
char IR[MAX_REG]; 
char R[MAX_REG]; 
int IC; 
int C; 
int SI;

void init() {

    for (int i = 0; i < MAX_MEMORY; i++) { 
        memset(M[i], '*', MAX_REG); }

    memset(IR, '*', MAX_REG); 
    memset(R, '*', MAX_REG); 
    IC = 0; 
    SI = 0;
    C = 0;

    printf("IR: "); 
    for (int i = 0; i < MAX_REG; i++) { 
        printf("%c", IR[i]); } printf("\n");
        printf("R: "); 
        for (int i = 0; i < MAX_REG; i++) { 
            printf("%c", R[i]); } 
            printf("\n");

    printf("T: ");
    printf("%d\n", IC); 
    printf("SI: "); 
    printf("%d\n", SI); 
    printf("C: "); 
    printf("%d\n", C); }

void printMemory() {

for (int i = 0; i < MAX_MEMORY; i++) { 
    printf("M[%02d]: ", i); 
    for (int j = 0; j < MAX_REG; j++) { 
        printf("%c", M[i][j]); } 
        printf("\n"); } }

void load() { 
    FILE *fileReader = fopen("input_main.txt", "r"); 
    if (fileReader == NULL) { 
        printf("Error: Could not open input fi le.\n"); 
        return; }

int row = 0;
char line[100]; 

while (fgets(line, sizeof(line), fileReader)) {

    line[strcspn(line, "\n")] = 0;

    if (strncmp(line, "$AMJ", 4) == 0) { 
        init(); 
        while (fgets(line, sizeof(line), fileReader)) {

    line[strcspn(line, "\n")] = 0;

    if (strncmp(line, "$DTA", 4) == 0 || strncmp(line, "$END", 4) == 0) { 
        break; }

    for (int i = 0; i < strlen(line); i += 4) { 
        if (row >= MAX_MEMORY) { break; }

    for (int j = 0; j < 4 && (i + j) < strlen(line); j++) { 
        M[row][j] = line[i + j]; }

    if (strlen(line) - i < 4) { 
        for (int k = strlen(line) - i; k < 4; k++) {
            M[row][k] = '*'; } }

row++; } } } }

fclose(fileReader); 
printMemory(); }

int main() { 
    load(); 
    return 0; }



Lab Assignment - 8


1.	Write a C program to write a Start_Execution()  module  to execute LR,SR,CR,BT ,GD,PD,H instruction.

Code: 
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_MEMORY 100
#define MAX_REG 4
#define MAX_BUFFER 42

char Memory[MAX_MEMORY][MAX_REG];   
char R[MAX_REG];                    
char IR[MAX_REG];                   
unsigned int IC;                    
bool C;                             
int SI;                             
char buffer[MAX_BUFFER];            

FILE *inputfile, *outputfile;

void INIT();
void LOAD();
void EXECUTE();
void MOS();
void Start();
int OppAdd();
void READ();
void WRITE();
void HALT();

void INIT() {
    for (int i = 0; i < MAX_MEMORY; i++) {
        for (int j = 0; j < MAX_REG; j++) {
            Memory[i][j] = '*';
        }
    }

    for (int i = 0; i < MAX_REG; i++) {
        IR[i] = '*';
        R[i] = '*';
    }

    C = false;
    IC = 0;
}

void LOAD() {
    printf("Reading Data...\n");
    int x = 0;
    
    for (int i = 0; i < MAX_MEMORY; i++) {
        for (int j = 0; j < MAX_REG; j++) {
            Memory[i][j] = '*';
        }
    }

    while (fgets(buffer, MAX_BUFFER, inputfile)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (strncmp(buffer, "$AMJ", 4) == 0) {
            INIT();
        } else if (strncmp(buffer, "$DTA", 4) == 0) {
            Start();
        } else if (strncmp(buffer, "$END", 4) == 0) {
            for (int i = 0; i < MAX_MEMORY; i++) {
                printf("M[%02d]: ", i);
                for (int j = 0; j < MAX_REG; j++) {
                    printf("%c", Memory[i][j]);
                }
                printf("\n");
                if (i % 10 == 9) {
                    printf("\n");
                }
            }
            continue;
        } else {
            int k = 0;
            int limit = x + 10;

            for (; x < limit; ++x) {
                for (int j = 0; j < MAX_REG; ++j) {
                    if (buffer[k] != '\n' && k < strlen(buffer)) {
                        Memory[x][j] = buffer[k++];
                    } else {
                        break;
                    }
                }
            }
        }
    }
}

int OppAdd() {
    int add = IR[2] - '0';
    add = add * 10 + (IR[3] - '0');
    return add;
}

void Start() {
    IC = 0;
    EXECUTE();
}

void EXECUTE() {
    while (1) {
        for (int i = 0; i < MAX_REG; i++) {
            IR[i] = Memory[IC][i];
        }
        IC++;

        int loc = OppAdd();

        if (IR[0] == 'G' && IR[1] == 'D') {
            SI = 1;
            MOS();
        } else if (IR[0] == 'P' && IR[1] == 'D') {
            SI = 2;
            MOS();
        } else if (IR[0] == 'H') {
            SI = 3;
            MOS();
            break;
        } else if (IR[0] == 'L' && IR[1] == 'R') {
            for (int j = 0; j < MAX_REG; j++) {
                R[j] = Memory[loc][j];
            }
        } else if (IR[0] == 'S' && IR[1] == 'R') {
            for (int j = 0; j < MAX_REG; j++) {
                Memory[loc][j] = R[j];
            }
        } else if (IR[0] == 'C' && IR[1] == 'R') {
            int count = 0;
            for (int j = 0; j < MAX_REG; j++) {
                if (Memory[loc][j] == R[j]) {
                    count++;
                }
            }
            C = (count == MAX_REG);
        } else if (IR[0] == 'B' && IR[1] == 'T') {
            if (C) {
                IC = loc;
                C = false;
            }
        }
    }
}

void MOS() {
    switch (SI) {
        case 1:
            for (int i = 0; i < MAX_BUFFER; i++) {
                buffer[i] = 0;
            }
            READ();
            break;
        case 2:
            WRITE();
            break;
        case 3:
            HALT();
            break;
        default:
            break;
    }
}

void READ() {
    fgets(buffer, MAX_BUFFER, inputfile);
    int k = 0;
    int loc = OppAdd();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < MAX_REG; ++j) {
            if (buffer[k] == '\0' || k >= strlen(buffer)) {
                return;  
            }
            Memory[loc][j] = buffer[k++];
        }
        loc++;
    }
}

void WRITE() {
    int loc = OppAdd();

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < MAX_REG; ++j) {
            if (Memory[loc][j] == '*') {
                break;  
            }
            fprintf(outputfile, "%c", Memory[loc][j]);
        }
        loc++;
    }
    fprintf(outputfile, "\n");
}

void HALT() {
    fprintf(outputfile, "\n\n");
}

int main() {
    printf("\t\tSY CS B Group 27\n\n\n");
    printf("Press any key to continue...\n");
    getchar();

    inputfile = fopen("input.txt", "r");
    outputfile = fopen("output.txt", "w");

    if (!inputfile) {
        printf("File doesn't exist\n");
    } else {
        printf("File Exists\n");
    }

    LOAD();

    fclose(inputfile);
    fclose(outputfile);
    return 0;
}




```

## shell

```
Lab Assignment 1

1.	Display Calendar of year 2025.
student@admins-iMac-4 ~ % cal
    January 2025      
Su Mo Tu We Th Fr Sa  
          1  2  3  4  
 5  6  7  8  9 10 11  
12 13 14 15 16 17 18  
19 20 21 22 23 24 25  
26 27 28 29 30 31                
student@admins-iMac-4 ~ %        

2. Display the system’s date.
student@admins-iMac-4 ~ % date
Tue Jan 21 12:22:42 IST 2025
student@admins-iMac-4 ~ % 

3. Count the number of lines in the /etc/passwd file.
student@admins-iMac-4 ~ % wc -l /etc/passwd
     120 /etc/passwd
student@admins-iMac-4 ~ % 

4. Find out who else is on the system.
tudent@admins-iMac-4 ~ % who
student  console  Jan 20 14:03 
student  ttys000  Jan 21 12:08 
student@admins-iMac-4 ~ % 

5. Direct the output of the man pages for the date command to a file named mydate.
student@admins-iMac-4 ~ % man date > mydate

6. Create a subdirectory called mydir.
student@admins-iMac-4 ~ % mkdir mydir

7. Move the file mydate into the new subdirectory.
student@admins-iMac-4 ~ % mv mydate mydir/

8. Go to the subdirectory mydir and copy the file mydate to a new file called ourdate
student@admins-iMac-4 ~ % cd mydir
student@admins-iMac-4 mydir % cp mydate ourdate

9. List the contents of mydir.
student@admins-iMac-4 mydir % cd ..
student@admins-iMac-4 ~ % ls mydir
mydate	ourdate

10. Do a long listing on the file ourdate and note the permissions.
student@admins-iMac-4 ~ % ls -l ourdate
-rw-r--r--  1 student  staff  12418 Jan 20 13:12 ourdate

11. Display the name of the current directory starting from the root.
student@admins-iMac-4 ~ % pwd
/Users/student

12. Move the files in the directory mydir back to your home directory.
       student@admins-iMac-4 mydir % mv mydate ourdate /Users/student/                             

13. Display the first 5 lines of mydate.
student@admins-iMac-4 ~ % head mydate
DATE(1)                   BSD General Commands Manual                  DATE(1)
NAME
     date -- display or set date and time
SYNOPSIS
     date [-jRu] [-r seconds | filename] [-v [+|-]val[ymwdHMS]] ...
          [+output_fmt]
     date [-jnu] [[[mm]dd]HH]MM[[cc]yy][.ss]
student@admins-iMac-4 ~ % 

14. Display the last 8 lines of mydate.
student@admins-iMac-4 ~ % tail -n 8  mydate
     The date utility is expected to be compatible with IEEE Std 1003.2
     (``POSIX.2'').  The -d, -f, -j, -n, -r, -t, and -v options are all exten-
     sions to the standard.
HISTORY
     A date command appeared in Version 1 AT&T UNIX.
BSD                               May 7, 2015  

15. Remove the directory mydir.
student@admins-iMac-4 ~ % rmdir mydir

16. Redirect the output of the long listing of files to a file named list.
student@admins-iMac-4 ~ % ls -l > list

17. Select any 5 capitals of states in India and enter them in a file named capitals1. Choose 5 more capitals and enter them in a file named capitals2. Choose 5 more capitals and enter them in a file named capitals3. Concatenate all 3 files and redirect the output to a file named capitals.
student@admins-iMac-4 ~ % cat > capitals1 
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
student@admins-iMac-4 ~ % cat >  capitals2
Bhopal
Ahemadabad
Guwahati 
Patna
Chandigarh
student@admins-iMac-4 ~ % cat > capitals3
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
student@admins-iMac-4 ~ % cat capitals1 capitals2 capitals3 > capitals

18. Concatenate the file capitals2 at the end of file capitals.
student@admins-iMac-4 ~ % cat capitals2 >> capitals
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh

19. Give read and write permissions to all users for the file capitals.
student@admins-iMac-4 ~ % chmod a+rw capitals
student@admins-iMac-4 ~ % ls -l capitals
-rw-rw-rw-  1 student  staff  175 Jan 21 13:28 capitals

20. Give read permissions only to the owner of the file capitals. Open the file, make some changes and try to save it. What happens ?
student@admins-iMac-4 ~ % chmod u-w capitals
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
student@admins-iMac-4 ~ % cat >> capitals 
zsh: permission denied: capitals

21. Create an alias to concatenate the 3 files capitals1, capitals2, capitals3 and redirect the output to a file named capitals. Activate the alias and make it run.

student@admins-iMac-4 ~ % alias al_cap='cat capitals1 capitals2 capitals3 > capitals' 
student@admins-iMac-4 ~ % al_cap
student@admins-iMac-4 ~ % cat capitals
Mumbai
Chennai
Haidrabad
Delhi 
Banglore
Bhopal
Ahemadabad
Guwahati
Patna
Chandigarh
Kolkata
Jaipur
Kochi
Thiruvanthapuram
Lucknow
student@admins-iMac-4 ~ % 

22. Find out the number of times the string “the” appears in the file mydate.
student@admins-iMac-4 ~ % grep -o "the" mydate | wc -l
     154

23. Find out the line numbers on which the string “date” exists in mydate.
student@admins-iMac-4 ~ % grep -n "date" mydate
5:     date -- display or set date and time
16:     date and time.  Otherwise, depending on the options specified, date will
17:     set the date and time or print it in a user-defined way.
19:     The date utility displays the date and time read from the kernel clock.
20:     When used to set the date and time, both the kernel clock and the hard-
21:     ware clock are updated.
23:     Only the superuser may set the date, and if the system securelevel (see
37:     -j      Do not try to set the date.  This allows you to use the -f flag
38:             in addition to the + option to convert one date format to
46:     -R      Use RFC 2822 date and time output format. This is equivalent to
51:             Print the date and time represented by seconds, where seconds is
57:             Print the date and time of the last modification of filename.
64:     -u      Display or set the date in UTC (Coordinated Universal) time.
66:     -v      Adjust (i.e., take the current date and display the result of the
67:             adjustment; not actually set the date) the second, minute, hour,
69:             preceded with a plus or minus sign, the date is adjusted forwards

24. Print all lines of mydate except those that have the letter “i” in them.
student@admins-iMac-4 ~ % grep -v "i" mydate
DATE(1)                   BSD General Commands Manual                  DATE(1)
NAME
SYNOPSIS
          [+output_fmt]
     date [-jnu] [[[mm]dd]HH]MM[[cc]yy][.ss]
DESCRIPTION
     ware clock are updated.
     than 1 second.
             another.
             the ``C'' locale .
     -r seconds
             hex.
             the current one.
             adjustment means that the clock goes forward at 01:00 to 02:00,
             essary to reach October 29, 2:30.
     ``+%+''.
                   year.
           dd      Day, a number from 1 to 31.
           HH      Hour, a number from 0 to 23.
                   leap seconds).
ENVIRONMENT
FILES
EXIT STATUS
EXAMPLES
     The command:
           date "+DATE: %Y-%m-%d%nTIME: %H:%M:%S"
           DATE: 1987-11-21
           TIME: 13:36:16
           date -v1m -v+1y
           Sun Jan  4 04:15:24 GMT 1998

25. List the words of 4 letters from the file mydate.

yash@yash-VirtualBox:~$ grep -o -w "\w\{4\}" mydate
DATE
User
DATE
NAME
date
date
time
date
date
date
time
With
with
date
time
long
date
time
date
warn
file
like
date
once
each
line
8601
date
time
8601
date
date
only
date
time
2006
date
time
5322
2006
0600
3339
date
time
3339
date
date
time
2006
FILE
last
time
FILE

26. List 5 states in north east India in a file mystates. List their corresponding capitals in a file mycapitals. Use the paste command to join the 2 files.
student@admins-iMac-4 ~ % cat > mystates
Arunachal Pradesh
Mizoram
Nagaland
Aasam 
Meghalay
student@admins-iMac-4 ~ % cat > mycapitals
Itanagar
Aizawl
Shillong
Dispur
Kohima
student@admins-iMac-4 ~ % paste mystates mycapitals
Arunachal Pradesh	Itanagar
Mizoram	Aizawl
Nagaland	Shillong
Aasam 	Dispur
Meghalay	Kohima

27. Use the cut command to print the 1 st and 3 rd columns of the /etc/passwd file for all students in this class.

student@admins-iMac-4 ~ % cut -d: -f 1,3 /etc/passwd
##
# User Database
# 
# Note that this file is consulted directly only when the system is running
# in single-user mode.  At other times this information is provided by
# Open Directory.
#
# See the opendirectoryd(8) man page for additional information about
# Open Directory.
##
nobody:-2
root:0
daemon:1
_uucp:4
_taskgated:13
_networkd:24
_installassistant:25
_lp:26
_postfix:27
_scsd:31
_ces:32
_appstore:33
_mcxalr:54
_appleevents:55
_geod:56
_devdocs:59
_sandbox:60
_mdnsresponder:65
_ard:67
_www:70
_eppc:71
_cvs:72
_svn:73
_mysql:74
_sshd:75
_qtss:76
_cyrus:77
_mailman:78
_appserver:79
_clamav:82
_amavisd:83
_jabber:84
_appowner:87
_windowserver:88
_spotlight:89
_tokend:91
_securityagent:92
_calendar:93
_teamsserver:94
_update_sharing:95
_installer:96
_atsserver:97
_ftp:98
_unknown:99
_softwareupdate:200
_coreaudiod:202
_screensaver:203
_locationd:205
_trustevaluationagent:208
_timezone:210
_lda:211
_cvmsroot:212
_usbmuxd:213
_dovecot:214
_dpaudio:215
_postgres:216
_krbtgt:217
_kadmin_admin:218
_kadmin_changepw:219
_devicemgr:220
_webauthserver:221
_netbios:222
_warmd:224
_dovenull:227
_netstatistics:228
_avbdeviced:229
_krb_krbtgt:230
_krb_kadmin:231
_krb_changepw:232
_krb_kerberos:233
_krb_anonymous:234
_assetcache:235
_coremediaiod:236
_launchservicesd:239
_iconservices:240
28. Count the number of people logged in and also trap the users in a file using the tee command.
student@admins-iMac-4 ~ % who | tee users.txt | wc -l
       2

29. Convert the contents of mystates into uppercase.
student@admins-iMac-4 ~ % tr 'a-z' 'A-Z' < mystates
ARUNACHAL PRADESH
MIZORAM
NAGALAND
AASAM 
MEGHALAY

30. Create any two files & display the common values between them.
yash@yash-VirtualBox:~$ cat > file1
OS 
CN
DS 
yash@yash-VirtualBox:~$ cat > file2
ML
AI
CN
yash@yash-VirtualBox:~$ sort file1 > file11
yash@yash-VirtualBox:~$ sort file2 > file22
yash@yash-VirtualBox:~$ comm file11 file22
	AI
		CN
DS
	ML
OS 





Lab Assignment 2


1.	Write shell script to execute command ls, date, pwd repetitively.
yash@yash-VirtualBox:~$ nano f1.sh
  GNU nano 7.2                                              f1.sh                                                       
ls
date
pwd
yash@yash-VirtualBox:~$ bash f1.sh
Btech	 Documents  Music     snap	 Student2  Student5  Student8	    SY	       TY
Btech11  Downloads  Pictures  Student1	 Student3  Student6  Student9	    SYTY       ufile
Desktop  f1.sh	    Public    Student11  Student4  Student7  Student_Names  Templates  Videos
Fri Jan 31 12:01:31 AM IST 2025
/home/yash

2.	Write a shell script to assign value to the variable?
Display value with $ and without $.
yash@yash-VirtualBox:~$ nano f2.sh
  GNU nano 7.2                                              f2.sh                                                       
num1=1
num2=2
echo "num1 is $num1"
echo "num2 is $num2"
echo "num1 is num1"
echo "num2 is num2"
yash@yash-VirtualBox:~$ bash f2.sh
num1 is 1
num2 is 2
num1 is num1
num2 is num2

3.	Variables are untyped in Shell Script.
Write a shell script to show variables are untyped.
yash@yash-VirtualBox:~$ nano f3.sh
  GNU nano 7.2                                              f3.sh                                                       
var1=10
var2=10.5
var3=VIT
var4="SY B DIV"
echo "var1 = $var1"
echo "var2 = $var2"
echo "var3 = $var3"
echo "var4 = $var4"
yash@yash-VirtualBox:~$ bash f3.sh
var1 = 10
var2 = 10.5
var3 = VIT
var4 = SY B DIV

4.	Write a shell script to accept numbers from user. (Keyboard)
yash@yash-VirtualBox:~$ nano f4.sh
  GNU nano 7.2                                              f4.sh                                                       
echo "Enter 5 Numbers: "

read num1
read num2
read num3
read num4
read num5

echo "Entered Numbers are "
echo "$num1, $num2, $num3, $num4, $num5"

yash@yash-VirtualBox:~$ bash f4.sh
Enter 5 Numbers: 
1
2
3
4
5
Entered Numbers are 
1, 2, 3, 4, 5

5.	Write a shell script to accept numbers from command line arguments.
yash@yash-VirtualBox:~$ nano f5.sh
  GNU nano 7.2                                              f5.sh                                                       
echo "Entered Numbers are $1, $2, $3"
yash@yash-VirtualBox:~$ bash f5.sh 10 20 30 
Entered Numbers are 10, 20, 30

6.	Write a shell script to show the contents of environmental variables SHELL,PATH,HOME. 
yash@yash-VirtualBox:~$ nano f6.sh
  GNU nano 7.2                          f6.sh                                   
echo "path is $PATH"
echo "shell is $SHELL"
echo "home is $HOME"
yash@yash-VirtualBox:~$ bash f6.sh
path is /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin
shell is /bin/bash
home is /home/yash

7.	Write a shell script to create two files. Accept file names from user. 
yash@yash-VirtualBox:~$ nano f7.sh
  GNU nano 7.2                          f7.sh                                   
echo "Enter the name for the first file:"
read file1
echo "Enter the name for the second file:"
read file2
touch "$file1"
touch "$file2"
echo "Files '$file1' and '$file2' have been created."
yash@yash-VirtualBox:~$ bash f7.sh
Enter the name for the first file:
File_1
Enter the name for the second file:
File_2
Files 'File_1' and 'File_2' have been created.

8.	Write a shell script to create two directories. Accept directories name from Command line.
yash@yash-VirtualBox:~$ nano f8.sh
  GNU nano 7.2                          f8.sh                                   
dir1=$1
dir2=$2
mkdir "$dir1"
mkdir "$dir2"
echo "Directories '$dir1' and '$dir2' have been created."
yash@yash-VirtualBox:~$ bash f8.sh R1 R2
Directories 'R1' and 'R2' have been created.

9.	Write a shell script to copy file content of one file to another file. Accept files names from command line argument.
 yash@yash-VirtualBox:~$ nano f9.sh
   GNU nano 7.2                          f9.sh                                   
file1=$1
file2=$2
echo "This is some content inside $file1." > "$file1"
cp "$file1" "$file2"
echo "Content of '$file1' has been copied to '$file2'."
yash@yash-VirtualBox:~$ bash f9.sh Yash_File_1 Yash_File_2
Content of 'Yash_File_1' has been copied to 'Yash_File_2'.

10.	Write a shell script to rename the file name. Accept old filename and new filename from command line argument. 
yash@yash-VirtualBox:~$ nano f10.sh
  GNU nano 7.2                         f10.sh                                   
old_name=$1
new_name=$2
mv "$old_name" "$new_name"
echo "File '$old_name' has been renamed to '$new_name'."
yash@yash-VirtualBox:~$ bash f10.sh Yash_File_1  fname_new
File 'Yash_File_1' has been renamed to 'fname_new'.

11.	Write a shell script to perform arithmetic operation of integer data.
yash@yash-VirtualBox:~$ nano f11.sh
  GNU nano 7.2                         f11.sh                                   
echo "Enter first integer:"
read num1
echo "Enter second integer:"
read num2
sum=$((num1 + num2))
difference=$((num1 - num2))
product=$((num1 * num2))
quotient=$((num1 / num2))
echo "Sum: $sum"
echo "Difference: $difference"
echo "Product: $product"
echo "Quotient: $quotient"
yash@yash-VirtualBox:~$ bash f11.sh
Enter first integer:
4
Enter second integer:
2
Sum: 6
Difference: 2
Product: 8
Quotient: 2

12.	Write a shell script to perform arithmetic operation of float  data.
yash@yash-VirtualBox:~$ nano f12.sh
      GNU nano 7.2                         f12.sh                                   
echo "Enter first float number:"
read num1
echo "Enter second float number:"
read num2
sum=$(echo "$num1 + $num2" | bc)
difference=$(echo "$num1 - $num2" | bc)
product=$(echo "$num1 * $num2" | bc)
quotient=$(echo "scale=2; $num1 / $num2" | bc)
echo "Sum: $sum"
echo "Difference: $difference"
echo "Product: $product"
echo "Quotient: $quotient"
yash@yash-VirtualBox:~$ bash f12.sh
Enter first float number:
10.5
Enter second float number:
3.6
Sum: 14.1
Difference: 6.9
Product: 37.8
Quotient: 2.91












Lab Assignment 3


1. Write a shell script to check number entered by the user is greater than 10.

student@admins-iMac ~ % nano s1.sh
  GNU nano 7.2                             s1.sh                                       
  GNU nano 2.0.6                                               File: s1.sh                                                                                                   
echo "Enter Number: "
read num1

if [ $num1 -gt 10 ]
then
echo "$num1 is greater than 10."
else
echo "$num1 is not greater than 10"
fi

student@admins-iMac ~ % bash s1.sh
Enter Number: 
2
2 is not greater than 10
student@admins-iMac ~ % bash s1.sh
Enter Number: 
12
12 is greater than 10.


2. Write a shell script to check if a file exists. If not, then create it.

student@admins-iMac ~ % nano s2.sh
  GNU nano 7.2                             s2.sh                                       
no 2.0.6                                               File: s2.sh                                                                                                  
echo "Enter the name of file: "
read file

if [ -f $file ]
then
echo "File exists"
else
echo "File does not exists"
fi

student@admins-iMac ~ % ls
8Puzzle.java	Downloads	Pictures	f1		f3.sh		filescount.sh	myfile.txt	q1.sh		s2.sh
Applications	Library		Public		f1.sh		f4.sh		list.txt	name.txt	q2.sh
Desktop		Movies		armstrong.sh	f1.sh.save	f5.sh		mydate		ourdate		q3.sh
Documents	Music		char_count.sh	f2.sh		f6.sh		mydir		prob1.sh	s1.sh

student@admins-iMac ~ % bash s2.sh
Enter the name of file: 
name.txt
File exists

student@admins-iMac ~ % bash s2.sh  
Enter the name of file: 
yourname.txt
File does not exists

3. Write a shell script that takes two command line arguments. Check whether the name passed as first argument is of a directory or not. If not ,create directory using name passed as second argument. 

student@admins-iMac ~ % nano s3.sh  G
  GNU nano 7.2                             s3.sh                                                                                File: s3.sh                                                                                 
dir1=$1
dir2=$2

if [ -d $dir1 ]
then
echo "$dir1 is present"
else
mkdir "$dir2"
echo "$dir2 is made"
fi

student@admins-iMac ~ % pwd
/Users/student
student@admins-iMac ~ % bash s3.sh /Users/student Y1
/Users/student is present
student@admins-iMac ~ % bash s3.sh Y1 Y2            
Y2 is made

4. Write a shell script which checks the total arguments passed. If the argument count is greater than 5, then display message “Too many arguments”

yash@yash-VirtualBox:~$ nano s4.sh

  GNU nano 7.2                             s4.sh                                       
if [ $# -gt 5 ]
then
echo "too many arguements"
else
echo "$# arguements are passed"
fi

yash@yash-VirtualBox:~$ bash s4.sh 1 2 3 4 
4 arguements are passed
yash@yash-VirtualBox:~$ bash s4.sh 1 2 3 4 5 6 7
too many arguments

5. Write a shell script to check arguments passed at command line is whether of a file or directory.

student@admins-iMac ~ % nano s5.sh
  GNU nano 7.2                             s5.sh                                       
GNU nano 2.0.6                                               File: s5.sh                                                                                                   
arg=$1

if [ -f $arg ]
then
echo "$arg is file"
elif [ -d $arg ]
then
echo "$arg is directory"
fi

student@admins-iMac ~ % bash s5.sh name.txt      
name.txt is file
student@admins-iMac ~ % bash s5.sh /Users/student
/Users/student is directory

6. Write a shell script to read a month name from the user. Check if the name entered is either August or October.

student@admins-iMac ~ % nano s6.sha
  GNU nano 7.2                             s6.sh                                       no 2.0.6                                               File: s6.sh                                                                                 
echo "Enter Month Name: "
read mon

if [ $mon =  August ]
then
echo "Month is August"
elif [ $mon = October ]
then
echo "Month is October"
else
echo "Month is neither August nor October"
fi

student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
August
Month is August
student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
October
Month is October
student@admins-iMac ~ % bash s6.sh
Enter Month Name: 
May
Month is neither August nor October

7. Write a shell script to check whether file or directory exists.
yash@yash-VirtualBox:~$ nano s7.sh

  GNU nano 7.2                             s7.sh *                                     
echo "Enter the name: "
read arg

if [ -f $arg ] 
then
echo "$arg is file and exists"

elif [ -d $arg ] 
then
echo "$arg is directory and exists"

else
echo "$arg does not exist"
fi

yash@yash-VirtualBox:~$ ls
Btech      f11.sh  f5.sh   File_2     R2         Student2  Student8       TY
Btech11    f12.sh  f6.sh   fname_new  s4.sh      Student3  Student9       ufile
Desktop    f1.sh   f7.sh   Music      s7.sh      Student4  Student_Names  Videos
Documents  f2.sh   f8.sh   Pictures   snap       Student5  SY             Yash_File_2
Downloads  f3.sh   f9.sh   Public     Student1   Student6  SYTY
f10.sh     f4.sh   File_1  R1         Student11  Student7  Templates
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Desktop
Desktop is directory and exists
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Btech
Btech is file and exists
yash@yash-VirtualBox:~$ bash s7.sh
Enter the name: 
Pokemon
Pokemon does not exist

8. Write a shell script to check whether file is exists and file is readable.

student@admins-iMac ~ % nano s8.sh
  GNU nano 7.2                             s8.sh                                       

echo "Enter File Name: "
read file

if [ -f $file ] && [ -r $file ]
then
echo "File exists and is readable as well"
elif [ -f $file ]
then
echo "File exists but is not readable"
else
echo "File does not exist"
fi

student@admins-iMac ~ % bash s8.sh
Enter File Name: 
name.txt
File exists and is readable as well

student@admins-iMac ~ % chmod 000 name.txt
student@admins-iMac ~ % bash s8.sh        
Enter File Name: 
name.txt
File exists but is not readable

student@admins-iMac ~ % bash s8.sh
Enter File Name: 
ok.txt
File does not exist

9. Write a shell script to check if the present month is August   or not. Use date command to get present month.U 

student@admins-iMac ~ % nano s9.sh
  GNU nano 7.2                             s9.sh                                       
nano 2.0.6                                               File: s9.sh                                                                                                  
x=$(date +"%m")

if [ $x = "August" ]
then
echo "Present month is August"
else
echo "Present month is not August"
fi

student@admins-iMac ~ % bash s9.sh
Present month is not August

10. Write a shell script to check if the current user is root or regular user.

yash@yash-VirtualBox:~$ nano s10.sh
  GNU nano 7.2                             s10.sh *                                    
if [ "$(id -u)" -eq 0 ] 
then
    echo "The current user is the root user."
else
    echo "The current user is the regular user."
fi
yash@yash-VirtualBox:~$ bash s10.sh
The current user is the regular user.

11. Write a shell script to check the total arguments passed at command line. If the arguments are more than 3 then list the argument else print “type more next time”
yash@yash-VirtualBox:~$ nano s11.sh
  GNU nano 7.2                         s11.sh                                   
if [ $# -gt 3 ]; then
    echo "Arguments passed: $@"
else
    echo "Type more next time"
fi

yash@yash-VirtualBox:~$ bash s11.sh 1 2
Type more next time
yash@yash-VirtualBox:~$ bash s11.sh 1 2 3 4
Arguments passed: 1 2 3 4









Lab Assignment 4


1.	Write a shell script to create three files.

student@admins-iMac ~ % nano m1.sh
  GNU nano 2.0.6                 File: m1.sh                                         
for x in file1 file2 file3
do
touch $x
echo "File is Created"
done

student@admins-iMac ~ % bash m1.sh
File is Created
File is Created
File is Created

2.	Write a shell script to print date and time 10 times, once after each second.


student@admins-iMac ~ % nano m2.sh
  GNU nano 2.0.6                 File: m2.sh                               Modified  
for (( i=0; i<10; i++))
do 
date
done

student@admins-iMac ~ % bash m2.sh      
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025
Tue Feb 11 13:27:47 IST 2025

3.	Write a shell script to create five directories. Accept the name of directories from command line.


student@admins-iMac ~ % nano m3.sh

  GNU nano 2.0.6                File: m3.sh                                         
mkdir1=$1
mkdir2=$2
mkdir3=$3
mkdir4=$4
mkdir5=$5
for x in $*
do
  mkdir $x
  echo "Directory is created"
done


student@admins-iMac ~ % bash m3.sh d1 d2 d3 d4 d5
Directory is created
Directory is created
Directory is created
Directory is created
Directory is created

4.	Write a shell script to print long list of all file’s names passed at command line.
yash@yash-VirtualBox:~/OS$ nano f1.sh
  GNU nano 7.2                                                                     f1.sh                                                                               
for file in "$@"
do
    if [ -e "$file" ]
    then
    ls "$file" 
    else
    echo "Error: $file does not exist."
  fi
done

yash@yash-VirtualBox:~/OS$ bash f1.sh s1.sh s4.sh
s1.sh
s4.sh
yash@yash-VirtualBox:~/OS$ ls
f1.sh  s1.sh  s2.sh  s3.sh  s4.sh

5.	Write a shell script to count the number of file names passed at command line.

yash@yash-VirtualBox:~/OS$ nano f2.sh
  GNU nano 7.2                                                                   f2.sh                                                                               
count=$#
echo "Number of files passed: $count"

yash@yash-VirtualBox:~/OS$ bash f2.sh s1.sh s4.sh s3.sh f1.sh
Number of files passed: 4

6.	Write a shell script to accept and display array. As-sume array consist 5 number.
yash@yash-VirtualBox:~/OS$ nano f3.sh
  GNU nano 7.2                                                                     f3.sh *                                                                             
echo "Enter 5 numbers"
for (( i=0; i<5; i++ ))
do
read a[i]
done

echo "Entered array is: "
for (( i=0; i<5; i++ ))
do
echo "${a[i]}"
done

yash@yash-VirtualBox:~/OS$ bash f3.sh
Enter 5 numbers
10
45
64
75
23
Entered array is: 
10
45
64
75
23

7.	Write Shell script to find out even and odd numbers from accepted array. Assume Array consists of 5 numbers. Also accept arrays from users.

yash@yash-VirtualBox:~/OS$ nano f4.sh
  GNU nano 7.2                                                                     f4.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i] 
done

echo "Even numbers:"
for (( i=0; i<5; i++ ))
do
  if (( arr[i] % 2 == 0 )); then
    echo "${arr[i]}"
  fi
done

echo "Odd numbers:"
for (( i=0; i<5; i++ ))
do
  if (( arr[i] % 2 != 0 )); then
    echo "${arr[i]}"
  fi
done
yash@yash-VirtualBox:~/OS$ bash f4.sh
Enter 5 numbers:
78
43
100
21
85
Even numbers:
78
100
Odd numbers:
43
21
85

8.	Write shell script to find out the reverse number of a given number. 
yash@yash-VirtualBox:~/OS$ nano f5.sh
  GNU nano 7.2                                                                     f5.sh *                                                                             
echo "Enter a number:"
read num

reverse=0

while [ $num -gt 0 ]
do
  remainder=$(( num % 10 ))    
  reverse=$(( reverse * 10 + remainder )) 
  num=$(( num / 10 ))           
done

echo "Reversed number: $reverse"

yash@yash-VirtualBox:~/OS$ bash f5.sh
Enter a number:
560946
Reversed number: 649065

9.	Write Shell script to sort array numbers ascending and descending order. Assume Array consists of 5 numbers. Also accept arrays from users. 	
yash@yash-VirtualBox:~/OS$ nano f6.sh
GNU nano 7.2                                                                     f6.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i] 
done

echo "Choose Sorting Order:"
echo "1) Ascending Order"
echo "2) Descending Order"
read choice

case $choice in    
for (( j=0; j<5-i-1; j++ ))
      do
        if (( arr[j] > arr[j+1] ))
         then
         temp=${arr[j]}
          arr[j]=${arr[j+1]}
          arr[j+1]=$temp
        fi
      done
    done
    echo "Sorted in Ascending Order: ${arr[*]}"
   ;;

  2) for (( i=0; i<5; i++ ))
    do
      for (( j=0; j<5-i-1; j++ ))
      do
        if (( arr[j] < arr[j+1] ))
          then
          temp=${arr[j]}
          arr[j]=${arr[j+1]}
          arr[j+1]=$temp
        fi
      done
    done
    echo "Sorted in Descending Order: ${arr[*]}"
    ;;

  *) 
    echo "Invalid choice! Please enter 1 or 2."
esac

yash@yash-VirtualBox:~/OS$ bash f6.sh
Enter 5 numbers:
7              
96
46
25
99
Choose Sorting Order:
1) Ascending Order
2) Descending Order
1
Sorted in Ascending Order: 7 25 46 96 99
yash@yash-VirtualBox:~/OS$ bash f6.sh
Enter 5 numbers:
58 
34
90
12
59
Choose Sorting Order:
1) Ascending Order
2) Descending Order
2
Sorted in Descending Order: 90 59 58 34 12


10.	Write Shell script to find out smallest number and largest number of given arrays. Assume Array consists of 5 numbers. Also accept arrays from users.
yash@yash-VirtualBox:~/OS$ nano f7.sh
  GNU nano 7.2                                                                     f7.sh                                                                               
echo "Enter 5 numbers:"
for (( i=0; i<5; i++ ))
do
  read arr[i]
done

min=${arr[0]}
max=${arr[0]}

for (( i=1; i<5; i++ ))
do
  if (( arr[i] < min ))
  then
    min=${arr[i]}
  fi

  if (( arr[i] > max ))
  then
    max=${arr[i]}
  fi
done

echo "Smallest Number: $min"
echo "Largest Number: $max"

yash@yash-VirtualBox:~/OS$ bash f7.sh
Enter 5 numbers:
87  
45
36
9
13
Smallest Number: 9
Largest Number: 87












Tutorial 2


1. Create Student record text file as “Student1” for given input student details.
yash@yash-VirtualBox:~$ cat > Student1
PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
2. Find out Btech student from “Student1” file and save the content into “Btech” file.
yash@yash-VirtualBox:~$ grep -i "btech" Student1 > Btech
yash@yash-VirtualBox:~$ cat Btech
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
3. Find out TY student from “Student1” file and save the content into “TY” file
yash@yash-VirtualBox:~$ grep -i "ty" Student1 > TY
yash@yash-VirtualBox:~$ cat TY
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
4. Find out SY student from “Student1” file and save the content into “SY” file.
yash@yash-VirtualBox:~$ grep -i "sy" Student1 > SY
yash@yash-VirtualBox:~$ cat SY
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
5.Combine SY and TY students from “Student1” file and save the content into “SYTY” file.
yash@yash-VirtualBox:~$ cat SY TY > SYTY
yash@yash-VirtualBox:~$ cat SYTY
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
6. Sort the file based on Roll No. and save content into “Student2” file.
yash@yash-VirtualBox:~$ sort -t'|' -k5,5n Student1 > Student2
yash@yash-VirtualBox:~$ cat Student2

PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
7. Compare “Student1” file with “Btech” file and save content into “Student2” file.
yash@yash-VirtualBox:~$ cmp Student1 Btech > Student2
yash@yash-VirtualBox:~$ cat Student2
Student1 Btech differ: byte 1, line 1
8. Find out PRN NO, Student Name, Year and Division field data from “Student1” file. And save into “Student3” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $1 "|" $2 "|" $3 "|" $4}' Student1 > Student3
yash@yash-VirtualBox:~$ cat Student3
PRN Number | Student Name | Year | Division 
12110382 | INGLE AKASH SWARUP | SY | CS-B 
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B 
12111284 | JOSHI PRANAV JAYANT | SY | CS-B 
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B 
12010017 | Pavan Kumar Sanjay | TY | CS-C 
12010870 | PAWAR OMKAR VIKAS | TY | CS-C 
12011408 | PRANITA PRASHANT MASKE | TY | CS-C 
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C 
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C 
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C 
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C 
12120033 | MUKTA PATIL | TY | CS-C 
11910490 | KOLPE SAKET PRADIP | BTech | CS-B 
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C 
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D 
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D 
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D 
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D 
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 
9. Find out Roll No., Email Id and Gender field date from “Student1” file and save into “Student4” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $5 "|" $6 "|" $7}' Student1 > Student4
yash@yash-VirtualBox:~$ cat Student4
 Roll No | Email Id | Gender
 32 | akash.ingle21@vit.edu | Male
 40 | atharva.jayappa21@vit.edu | Male
 43 | pranav.joshi21@vit.edu | Male
 56 | ojas.ketkar211@vit.edu | Male
 26 | pavan.sanjay20@vit.edu | Male
 28 | omkar.pawar20@vit.edu | Male
 41 | pranita.maske20@vit.edu | Female
 55 | akash.bhagwat21@vit.edu | Male
 62 | udayan.gaikwad21@vit.edu | Male
 64 | saniya.inamadar21@vit.edu | Female
 69 | shreyas.kapse21@vit.edu | Male
 72 | patil.mukta21@vit.edu | Male
 16 | saket.kolpe19@vit.edu | Male
 28 | gaurav.pawar20@vit.edu | Male
 2 | varun.ringnekar19@vit.edu | Male
 9 | harsh.satdeve19@vit.edu | Male
 7 | SAMARTH.GAWANDE19@vit.edu | Male
 13 | kirtish.surangalikar19@vit.edu | Male
 11 | pradyumn.patil19@vit.edu | Male└─$ cat Student4
10. Combine “Student3” and “Student4” file and save content into “Student5” file.
yash@yash-VirtualBox:~$ cat Student3 Student4 > Student5
yash@yash-VirtualBox:~$ cat Student5
PRN Number | Student Name | Year | Division 
12110382 | INGLE AKASH SWARUP | SY | CS-B 
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B 
12111284 | JOSHI PRANAV JAYANT | SY | CS-B 
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B 
12010017 | Pavan Kumar Sanjay | TY | CS-C 
12010870 | PAWAR OMKAR VIKAS | TY | CS-C 
12011408 | PRANITA PRASHANT MASKE | TY | CS-C 
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C 
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C 
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C 
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C 
12120033 | MUKTA PATIL | TY | CS-C 
11910490 | KOLPE SAKET PRADIP | BTech | CS-B 
12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C 
11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D 
11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D 
11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D 
11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D 
11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 
|||
 Roll No | Email Id | Gender
 32 | akash.ingle21@vit.edu | Male
 40 | atharva.jayappa21@vit.edu | Male
 43 | pranav.joshi21@vit.edu | Male
 56 | ojas.ketkar211@vit.edu | Male
 26 | pavan.sanjay20@vit.edu | Male
 28 | omkar.pawar20@vit.edu | Male
 41 | pranita.maske20@vit.edu | Female
 55 | akash.bhagwat21@vit.edu | Male
 62 | udayan.gaikwad21@vit.edu | Male
 64 | saniya.inamadar21@vit.edu | Female
 69 | shreyas.kapse21@vit.edu | Male
 72 | patil.mukta21@vit.edu | Male
 16 | saket.kolpe19@vit.edu | Male
 28 | gaurav.pawar20@vit.edu | Male
 2 | varun.ringnekar19@vit.edu | Male
 9 | harsh.satdeve19@vit.edu | Male
 7 | SAMARTH.GAWANDE19@vit.edu | Male
 13 | kirtish.surangalikar19@vit.edu | Male
 11 | pradyumn.patil19@vit.edu | Male
11. Convert “Student1” content into Uppercase Letter and save into “Student6” file.
yash@yash-VirtualBox:~$ tr 'a-z' 'A-Z' < Student1 > Student6
yash@yash-VirtualBox:~$ cat Student6
PRN NUMBER | STUDENT NAME | YEAR | DIVISION | ROLL NO | EMAIL ID | GENDER
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | AKASH.INGLE21@VIT.EDU | MALE
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | ATHARVA.JAYAPPA21@VIT.EDU | MALE
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | PRANAV.JOSHI21@VIT.EDU | MALE
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | OJAS.KETKAR211@VIT.EDU | MALE
12010017 | PAVAN KUMAR SANJAY | TY | CS-C | 26 | PAVAN.SANJAY20@VIT.EDU | MALE
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | OMKAR.PAWAR20@VIT.EDU | MALE
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | PRANITA.MASKE20@VIT.EDU | FEMALE
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | AKASH.BHAGWAT21@VIT.EDU | MALE
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | UDAYAN.GAIKWAD21@VIT.EDU | MALE
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | SANIYA.INAMADAR21@VIT.EDU | FEMALE
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | SHREYAS.KAPSE21@VIT.EDU | MALE
12120033 | MUKTA PATIL | TY | CS-C | 72 | PATIL.MUKTA21@VIT.EDU | MALE
11910490 | KOLPE SAKET PRADIP | BTECH | CS-B | 16 | SAKET.KOLPE19@VIT.EDU | MALE
12020233 | PAWAR GAURAV PRABHAKAR | BTECH | CS-C | 28 | GAURAV.PAWAR20@VIT.EDU | MALE
11910590 | RINGNEKAR VARUN DEEPAK | BTECH | CS-D | 2 | VARUN.RINGNEKAR19@VIT.EDU | MALE
11910541 | SATDEVE HARSH SHAILESH | BTECH | CS-D | 9 | HARSH.SATDEVE19@VIT.EDU | MALE
11910157 | SAMARTH GAJANAN GAWANDE | BTECH | CS-D | 7 | SAMARTH.GAWANDE19@VIT.EDU | MALE
11911020 | SURANGALIKAR KIRTISH NITIN | BTECH | CS-D | 13 | KIRTISH.SURANGALIKAR19@VIT.EDU | MALE
11911229 | PATIL PRADYUMN NARENDRA | BTECH | CS-C-3 | 11 | PRADYUMN.PATIL19@VIT.EDU | MALE
12.  Compare “Student1” and “BTech” file and save content into “Student7” file.
yash@yash-VirtualBox:~$ cmp Student1 Btech > Student7
yash@yash-VirtualBox:~$ cat Student7
Student1 Btech differ: byte 1, line 1
13. Find out difference between “Student1” and “Btech” file and Save into “Student 8” file.
yash@yash-VirtualBox:~$ diff Student1 Btech > Student8
yash@yash-VirtualBox:~$ cat Student8
1,13d0
< PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
< 12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
< 12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
< 12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
< 12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
< 12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
< 12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
< 12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
< 12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
< 12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
< 12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
< 12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
< 12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
21d7
< 
14.  Find out common between “Student1” and “Btech” file and save content into “Student9” file.
yash@yash-VirtualBox:~$ sort Student1 > Student11
yash@yash-VirtualBox:~$ sort Btech > Btech11
yash@yash-VirtualBox:~$ comm Student11 Btech11 > Student9
yash@yash-VirtualBox:~$ cat Student9

		11910157 | SAMARTH GAJANAN GAWANDE | BTech | CS-D | 7 | SAMARTH.GAWANDE19@vit.edu | Male
		11910490 | KOLPE SAKET PRADIP | BTech | CS-B | 16 | saket.kolpe19@vit.edu | Male
		11910541 | SATDEVE HARSH SHAILESH | BTech | CS-D | 9 | harsh.satdeve19@vit.edu | Male
		11910590 | RINGNEKAR VARUN DEEPAK | BTech | CS-D | 2 | varun.ringnekar19@vit.edu | Male
		11911020 | SURANGALIKAR KIRTISH NITIN | BTech | CS-D | 13 | kirtish.surangalikar19@vit.edu | Male
		11911229 | PATIL PRADYUMN NARENDRA | BTech | CS-C-3 | 11 | pradyumn.patil19@vit.edu | Male
12010017 | Pavan Kumar Sanjay | TY | CS-C | 26 | pavan.sanjay20@vit.edu | Male
12010870 | PAWAR OMKAR VIKAS | TY | CS-C | 28 | omkar.pawar20@vit.edu | Male
12011408 | PRANITA PRASHANT MASKE | TY | CS-C | 41 | pranita.maske20@vit.edu | Female
		12020233 | PAWAR GAURAV PRABHAKAR | BTech | CS-C | 28 | gaurav.pawar20@vit.edu | Male
12110382 | INGLE AKASH SWARUP | SY | CS-B | 32 | akash.ingle21@vit.edu | Male
12111281 | KETKAR OJAS DEVENDRA | SY | CS-B | 56 | ojas.ketkar211@vit.edu | Male
12111284 | JOSHI PRANAV JAYANT | SY | CS-B | 43 | pranav.joshi21@vit.edu | Male
12111286 | JAYAPPA ATHARVA VIJAY | SY | CS-B | 40 | atharva.jayappa21@vit.edu | Male
12120014 | INAMDAR SANIYA AJIJ | TY | CS-C | 64 | saniya.inamadar21@vit.edu | Female
12120031 | BHAGWAT AKASH DAULAT | TY | CS-C | 55 | akash.bhagwat21@vit.edu | Male
12120033 | MUKTA PATIL | TY | CS-C | 72 | patil.mukta21@vit.edu | Male
12120039 | GAIKWAD UDAYAN FATHESINGH | TY | CS-C | 62 | udayan.gaikwad21@vit.edu | Male
12120050 | KAPSE SHREYAS SANTOSH | TY | CS-C | 69 | shreyas.kapse21@vit.edu | Male
PRN Number | Student Name | Year | Division | Roll No | Email Id | Gender
15. Remove user and group of “SY” file read and write permission file.
yash@yash-VirtualBox:~$ ls -l SY
-rw-rw-r-- 1 yash yash 324 Jan 30 21:53 SY
yash@yash-VirtualBox:~$ chmod ug-rw SY
yash@yash-VirtualBox:~$ ls -l SY
-------r-- 1 yash yash 324 Jan 30 21:53 SY
16. Assign read, write, execute permission to user and others of “SY” file.
yash@yash-VirtualBox:~$ chmod 707 SY
yash@yash-VirtualBox:~$ ls -l SY
-rwx---rwx 1 yash yash 324 Jan 30 21:53 SY
17. Display count of male students from “Student1” file.
yash@yash-VirtualBox:~$ grep -c 'Male' Student1 
17
18. Find out Name of student field data from “Student1” file and redirect output to count  Number of students in “Student1” file.
yash@yash-VirtualBox:~$ awk -F'|' '{print $2}' Student1 | wc -l
20
19. Find out file and directory in current path and trap this output in userfile as “ufile”.Also Display count of number of directories and files in current path.
yash@yash-VirtualBox:~$ ls -l > ufile
yash@yash-VirtualBox:~$ ls -l | grep -v '^d' | wc -l
18
yash@yash-VirtualBox:~$ ls -l | grep '^d' | wc -l
9


So, the number of files is 18 and the directories are 9. 






Tutorial 3


1.	Write a shell script to display files in current directory /output of date command /present working directory. Accept choice from user. (Use case statement) .
student@admins-iMac ~ % nano y1.sh
  GNU nano 2.0.6                 File: y1.sh                                         
echo "Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command$
read choice
case $choice in
1) ls;;
2) date;;
3) pwd;;
*) echo "Wrong Input"
esac

student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
1
41		Y2		f1.sh		mydir		s5.sh
8Puzzle.java	a.sh		f1.sh.save	myfile.txt	s6.sh
Applications	aa		f2.sh		name.txt	s8.sh
Desktop		ap.sh		f3.sh		ourdate		s9.sh
Documents	armstrong.sh	f4.sh		prob1.sh	stud.sh
Downloads	array.sh	f5.sh		q1.sh		student.sh
Library		bb		f6.sh		q2.sh		unique.sh
Movies		cc		filescount.sh	q3.sh		ved.txt
Music		char_count.sh	kadane.sh	s1.sh		y1.sh
Pictures	diagonal.sh	list.txt	s2.sh		y2.sh
Public		f1		mydate		s3.sh
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
2
Tue Feb 11 12:34:21 IST 2025
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
3
/Users/student
student@admins-iMac ~ % bash y1.sh
Enter choice, 1: Display Files in Current Directory, 2: Output of Date Command, 3: Present Working Directory 
5
Wrong Input

2.	Write a shell script to perform arithmetic operation. Accept choice from user. (Use case statement).
student@admins-iMac ~ % nano y2.sh
  GNU nano 2.0.6                 File: y2.sh                                         
echo "Enter Two Numbers: "
read num1
read num2
echo "Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division"
read choice
case $choice in
1) add=$[ num1 + num2 ]
echo "Addition is $add";;
2) sub=$[ num1 - num2 ]
echo "Subtraction is $sub";;
3) mul=$[ num1 * num2 ]
echo "Multiplication is $mul";;
4) div=$[ num1 / num2 ]
echo "Division is $div";;
*) echo "Wrong Input"
esac

student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10  
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
1
Addition is 15
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
2
Subtraction is 5
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
3
Multiplication is 50
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
4
Division is 2
student@admins-iMac ~ % bash y2.sh
Enter Two Numbers: 
10
5
Enter choice, 1: Addition, 2: Subtraction, 3: Multiplication, 4: Division
5
Wrong Input

3.	Write a shell script to identify entered key is Uppercase/Lowercase /Number /Punctuation. (Use case statement).
student@admins-iMac ~ % nano y3.sh
  GNU nano 2.0.6                 File: y3.sh                                         
echo "Enter a Key: "
read key
case $key in
[A-Z]) echo "Entered key is Uppercase";;
[a-z]) echo "Entered key is Lowercase";;
[0-9]) echo "Entered key is Number";;
[[:punct:]]) echo "Entered key is Punctuation";;
*) echo "Invalid key"
esac

student@admins-iMac ~ % bash y3.sh
Enter a Key: 
Y
Entered key is Uppercase
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
g
Entered key is Lowercase
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
9
Entered key is Number
student@admins-iMac ~ % bash y3.sh
Enter a Key: 
$
Entered key is Punctuation












Tutorial 4


1.	Write a shell script to enter a name & 3 subject marks of a student & calculate total & percentage & print First class, second class, pass class & fail.
yash@yash-VirtualBox:~/OS$ nano s1.sh
GNU nano 7.2                                                                     s1.sh                                                                               
echo "Enter the name of student: "
read name
echo "Enter the names of three subjects: "
read sub1 sub2 sub3
echo "Enter the marks of three subjects respectively: "
read m1 m2 m3

total=$(($m1 + $m2 + $m3))
per=$(echo "scale=2; $total / 3" | bc)

echo "Total is $total"
echo "Percentage is $per"
echo "The result is: "

if [ $total -gt 270 ] 
then
echo "First Class"
elif [ $total -gt 240 ]
then
echo "Second Class"
elif [ $total -gt 120 ]
then
echo "Pass Class"
else
echo "Fail"
fi

yash@yash-VirtualBox:~/OS$ bash s1.sh
Enter the name of student: 
Yash
Enter the names of three subjects: 
OS MAM CGVR
Enter the marks of three subjects respectively: 
91 67 80
Name is Yash
OS=91, MAM=67, CGVR=80
Total is 238
Percentage is 79.33
The result is: 
Pass Class

2.	Write Shell program to convert given number from decimal to binary and binary to decimal.
yash@yash-VirtualBox:~/OS$ nano s2.sh
  GNU nano 7.2                                                                     s2.sh                                                                               
echo "Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal"
read choice

case $choice in
1) echo "Enter Decimal Number"
read deci

while [ $deci -gt 0 ]
do
  remainder=$(( deci % 2 ))  
  bin="$remainder$bin"    
  deci=$(( deci / 2 ))    
done
echo "Binary: $bin";;

2) echo "Enter Binary Number"
read bin
power=1

while [ -n "$bin" ]
do
  digit=${bin: -1} 
  deci=$(( deci + digit * power ))  
  power=$(( power * 2 ))
  bin=${bin:0:-1}  
done
echo "Decimal: $deci";;

*) echo "Wrong Choice"
esac

yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
1
Enter Decimal Number
12
Binary: 1100
yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
2
Enter Binary Number
1001
Decimal: 9
yash@yash-VirtualBox:~/OS$ bash s2.sh
Enter a choice, 1. Decimal to Binary, 2. Binary to Decimal
4
Wrong Choice

3.	Write a shell script that print the smallest digit of a given number.
yash@yash-VirtualBox:~/OS$ nano s3.sh
  GNU nano 7.2                                                                     s3.sh                                                                               
echo "Enter a number:"
read num

min_digit=9

while [ "$num" -gt 0 ]
do
  digit=$(( num % 10 ))  
  if [ "$digit" -lt "$min_digit" ]
  then
  min_digit=$digit  
  fi

  num=$(( num / 10 )) 
done

echo "Smallest digit: $min_digit"

yash@yash-VirtualBox:~/OS$ bash s3.sh 
Enter a number:
40973
Smallest digit: 0

4.	Write a shell program for printing Fibonacci Series.
yash@yash-VirtualBox:~/OS$ nano s4.sh
 GNU nano 7.2                                                                     s4.sh                                                                               
echo "Enter the number of terms:"
read n

a=0
b=1

echo "Fibonacci Series:"

for (( i=0; i<n; i++ ))
do
  echo -n "$a "  
  temp=$(( a + b ))  
  a=$b  
  b=$temp
done

echo  

yash@yash-VirtualBox:~/OS$ bash s4.sh
Enter the number of terms:
11
Fibonacci Series:
0 1 1 2 3 5 8 13 21 34 55 

````



