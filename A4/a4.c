#include<stdio.h>
#include <stdlib.h>
#include<string.h>


typedef struct Process
{
	char pid[2];
	int at;
	int bt;
	int tt;
	int wt;
	int rt;
	int pr;
	int flag;
	int visit;
	
}process;

void priority_schedulingNP();
void priority_schedulingP();
void round_robin();
void get_priority();
int remaining_visit(process *p[20]);

process *p[20];
int n;
int gantt_time[20];

void main()
{
	
	int ch,i;
	

	for(i=0;i<20;i++)
	{
	
		p[i]=(process*)malloc(sizeof(process));
		p[i]->flag=0;
		p[i]->visit=0;
	}


	printf("MENU\n");
	printf("1.Priority NP\n");
	printf("2.Priority P\n");
	printf("3.Round Robin\n");
	printf("Enter choice:");
	scanf("%d",&ch);

	

	printf("\nEnter the no. of processes:");
	scanf("%d",&n);

	for(i=0;i<n;i++)
	{
		printf("\nEnter Process ID:");
		scanf("%s",p[i]->pid);
		printf("Enter arrival time:");
		scanf("%d",&p[i]->at);
		printf("Enter burst time:");
		scanf("%d",&p[i]->bt);

		p[i]->rt=0;
		p[i]->tt=0;
		p[i]->wt=0;

	}
		
	
	switch(ch)
	{
		case 1:
				get_priority();
				priority_schedulingNP();
				break;

		case 2: 
				get_priority();
				priority_schedulingP();
				break;
				
		case 3:round_robin();
				break;
	}	

}

void get_priority()
{
	int i;
	printf("Enter the priority for each process:\n");
	for(i=0;i<n;i++)
	{
		printf("%s:",p[i]->pid);
		scanf("%d",&p[i]->pr);
	}
}
		
	
	
process* shortest_at()
{
	
	int i,j;
	process *temp;
	process *p1[20];
	
	for(i=0;i<n;i++)
	{
		p1[i]=p[i];
	}

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p1[i]->at>p1[j]->at)
			{
				temp=p1[i];
				p1[i]=p1[j];
				p1[j]=temp;
			}
		}
	}
	
	i=0;
	
	while(p1[i]->flag!=0)
	{
		i++;
	}

	return p1[i];
}

int remaining_process()
{
	int i;
	for(i=0;i<n;i++)
	{
		if(p[i]->flag==0)
			return 1;
	}
	return 0;
}		

void printChart(process *p[20])
{
	
	int i,t;
	int time=0,total_time=0;

	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}
	printf("--------------------------------------------------------\n");
	for(i=0;remaining_process()!=0;i++)
	{
		
		if(time<p[i]->at)
		{
			printf("   %s    ","idle");
			t=(p[i]->at-time);
			time+=t;
			continue;
		}
			
		printf("   %s    ",p[i]->pid);
		time+=p[i]->bt;
		p[i]->flag=1;
	} 
	printf("\n");
	printf("--------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}
	time=0;

	for(i=0;remaining_process()!=0;i++)
	{
		if(time<p[i]->at)
		{
			t=(p[i]->at-time);
			time+=t;
		}
		printf("%d       ",time);
		time+=p[i]->bt;
		p[i]->flag=1;
	}  
	printf("%d",time);
}

void wait_time(process *p[20])
{
	int i,time=0,t;

	for(i=0;i<n;i++)
	{
	
		p[i]->flag=0;
		
	}

	for(i=0;remaining_process()!=0;i++)
	{
		p[i]->wt=time-p[i]->at;
		if(time<p[i]->at)
		{
			t=(p[i]->at-time);
			time+=t;
		}
		
		time+=p[i]->bt;
		p[i]->flag=1;
	}  
}

void turaround_time(process *p[20])
{
	int i,time=0;

	for(i=0;i<n;i++)
	{
		p[i]->tt=p[i]->wt+p[i]->bt;
	} 

}

void response_time(process *p[20])
{
	int i;
	for(i=0;i<n;i++)
	{
		p[i]->rt=p[i]->wt;
	}
}
void print_Table(process *p[20])
{

	int i;
	float avg_wt=0,avg_rt=0,avg_tt=0;

	
	
	turaround_time(p);
	


	printf("\n\n---------------------------------------------------------------------------------------------\n");
	printf("Process ID	Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time\n");
	printf("---------------------------------------------------------------------------------------------\n");
	for(i=0;i<n;i++)
	{
		printf("%-11s%14d%13d%17d%15d%13d\n",p[i]->pid,p[i]->at,p[i]->bt,p[i]->tt,p[i]->wt,p[i]->rt);         
		avg_wt+=p[i]->wt;
		avg_rt+=p[i]->rt;
		avg_tt+=p[i]->tt;	
	}
	avg_wt/=n;
	avg_rt/=n;
	avg_tt/=n;
	printf("---------------------------------------------------------------------------------------------\n");
	printf("                              Average            %.2f              %.2f          %.2f\n",avg_tt,avg_wt,avg_rt);
}	
	
void priority_schedulingNP()
{
	
	
	
	int time=0,j=0,i,k,t;
	process *ptr[20];


	process *temp;

	printf("PRIORITY NON PREEMPTIVE SCHEDULING\n");

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->pr>p[j]->pr)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}
	
	for(i=0;i<20;i++)
	{
	
		ptr[i]=(process*)malloc(sizeof(process));
		ptr[i]->flag=0;
		
	}

	j=0;
	
	
	
	for(i=0;remaining_process()!=0;)
	{
		
		if(time<p[i]->at)
		{	
			
			ptr[j]=shortest_at(p,n);
			
			
			for(k=0;k<n;k++)
			{
				if(strcmp(ptr[j]->pid,p[k]->pid)==0)
				{
					p[k]->flag=1;
					break;
				}
			}

			time+=ptr[j]->bt;

			if(time<ptr[j]->at)
			{
				t=(ptr[j]->at-time);
				time+=t;
			
			}
				
				
			j++;
		}
			
		else 
		{
		
			if(p[i]->flag==0)
			{
				
				ptr[j++]=p[i];
				p[i]->flag=1;
				time+=p[i]->bt;
				
			}
			i++;
		}
	}
		
	wait_time(ptr);
	response_time(ptr);
	printChart(ptr);
	print_Table(ptr);
}

void priority_schedulingP()
{

	int priority[n]; 
	int gantt_time[30];
	int i,j,time=0,k=0,x,gt=0,y;
	int bt[20];

	process *ptr[20];
	process *temp;
	process *ptemp[20];

  	for(i=0;i<20;i++)
	{
	
		ptemp[i]=(process*)malloc(sizeof(process));
		ptemp[i]=p[i];
		bt[i]=p[i]->bt;
		
	}
    // Copy the burst time into priority[] 
    for (i = 0; i < n; i++) 
        priority[i] = p[i]->pr; 

	for(i=0;i<20;i++)
	{
	
		ptr[i]=(process*)malloc(sizeof(process));
		ptr[i]->visit=0;
		
	}
  
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->pr>p[j]->pr)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}

	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->pr==p[j]->pr && p[i]->at>p[j]->at)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}

	gantt_time[gt++]=0;
	
	for(i=0;remaining_process()!=0;k++)
	{
		if(p[i]->at>time)
		{
			
			ptr[k]=shortest_at(p,n);
			while(p[i]->at>time)
			{
				time+=1;
			}
			for(x=0;x<n;x++)
			{
				if(strcmp(ptr[k]->pid,p[x]->pid)==0)
				{
					p[x]->bt-=time;
					break;
				}
			}
			

			gantt_time[gt++]=time;
		}
		else
		{
			if(p[i]->flag==1)
			{
				i++;
			}
			ptr[k]=p[i];
			time=time+p[i]->bt;
			gantt_time[gt++]=time;
			p[i]->bt=0;
			
		}

		if(p[i]->bt==0)
		{
			p[i]->flag=1;
		}
	}

    


	int index;
	printf("PREEMPTIVE PRIORITY SCHEDULING\n");
	printf("--------------------------------------------------------\n");

	for(i=0;i<k;i++)
	{
		printf("   %s    ",ptr[i]->pid);
	}
	printf("\n");
	printf("--------------------------------------------------------\n");
	for(i=0;i<gt;i++)
	{
		printf("%d       ",gantt_time[i]);
	}

	int at,t=0;

	for(i=0;i<n;i++)
	{
		ptemp[i]->visit=0;
		ptemp[i]->bt=bt[i];
	}

	
	for(i=0;i<k;i++)
	{
		at=ptr[i]->at;
		for(j=0;j<n;j++)
		{
			if(strcmp(ptr[i]->pid,ptemp[j]->pid)==0 && ptemp[j]->visit==0)
			{	
				break;
			}
		}
		
		
		if(remaining_visit(ptemp)!=0)
		{
			
			ptemp[j]->wt=gantt_time[i]-at;
			ptemp[j]->rt=ptemp[j]->wt;
			t=gantt_time[i+1];
			for(y=i+1;y<k;y++)
			{
				if(strcmp(ptr[i]->pid,ptr[y]->pid)==0)
				{
					ptemp[j]->wt+=gantt_time[y]-t;
					t=gantt_time[y+1];
				}
			}	
			ptemp[j]->tt=ptemp[j]->wt+ptemp[j]->bt;
			ptemp[j]->visit=1;

		}
		else
		{
			break;
		}

		t=0;
		at=0;

	}

	print_Table(ptemp);

}

int remaining_visit(process *p[20])
{
	int i;

	for(i=0;i<n;i++)
	{
		if(p[i]->visit==0)
			return 1;
	}

	return 0;
}

void round_robin()
{
	

    char RQ[30][5];
	int bt[20];
    int front=0,rear=0,time=0,j=0,k=0,flag=0,i,x,q;
    process *temp;
    int gt=0;

    process *ptr[20];
	process *ptemp[20];

    printf("Enter the time quantum:");
    scanf("%d",&q);
    
    printf("ROUND ROBIN SCHEDULING\n");

	for(i=0;i<20;i++)
	{
	
		ptr[i]=(process*)malloc(sizeof(process));
		ptr[i]->visit=0;
		
	}

	for(i=0;i<20;i++)
	{
	
		ptemp[i]=(process*)malloc(sizeof(process));
		ptemp[i]=p[i];
		bt[i]=p[i]->bt;
		
	}

	
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(p[i]->at>p[j]->at)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
	}
    int y=0;
    strcpy(RQ[rear],p[0]->pid);
    gantt_time[gt++]=0;

    for(i=0;remaining_process()!=0;)
	{
	
        for(x=0;x<n;x++)
        {
			
            if(strcmp(RQ[front],p[x]->pid)==0)
            {
				
                ptr[y]=p[x];
				p[x]->visit=1;
				//p[x]->rt=time-at
				
                if(p[x]->bt<=q)
                {
					
					time+=p[x]->bt;
                    ptr[y]->bt=0;
                    p[x]->flag=1;
					//p[x]->wt=time-at-bt
                  
                }
                else
                {
					
                    flag=1;
                    p[x]->bt-=q;
                    time+=q;
                }
                
                gantt_time[gt++]=time;
                break;
   
            }
        }

        for(j=0;j<n;j++)
        {
            if(p[j]->at<=time && p[j]->bt!=0 && strcmp(p[j]->pid,RQ[front])!=0 && remaining_visit(p)!=0)
            {
                strcpy(RQ[++rear],p[j]->pid);
				p[j]->visit=1;
            }
        }

        if(flag==1)
        {
            strcpy(RQ[++rear],ptr[y]->pid);       
        }

        front++;
        y++;
		flag=0;
    }

    printf("-------------------------------------------------------------------------\n");
    for(i=0;i<y;i++)
    {
        printf("    %s    ",ptr[i]->pid);
    }
    printf("\n");
    printf("-------------------------------------------------------------------------\n");

	for(i=0;i<gt;i++)
	{
		printf(" %d       ",gantt_time[i]);
	}
	int at,t;

	for(i=0;i<n;i++)
	{
		ptemp[i]->visit=0;
		ptemp[i]->bt=bt[i];
	}

	
	for(i=0;i<y;i++)
	{
		at=ptr[i]->at;
		for(j=0;j<n;j++)
		{
			if(strcmp(ptr[i]->pid,ptemp[j]->pid)==0 && ptemp[j]->visit==0)
			{	
				break;
			}
		}
		
		
		if(remaining_visit(ptemp)!=0)
		{
			
			ptemp[j]->wt=gantt_time[i]-at;
			ptemp[j]->rt=ptemp[j]->wt;
			t=gantt_time[i+1];
			for(k=i+1;k<y;k++)
			{
				if(strcmp(ptr[i]->pid,ptr[k]->pid)==0)
				{
					ptemp[j]->wt+=gantt_time[k]-t;
					t=gantt_time[k+1];
				}
			}	
			ptemp[j]->tt=ptemp[j]->wt+ptemp[j]->bt;
			ptemp[j]->visit=1;

		}
		else
		{
			break;
		}

		t=0;
		at=0;

	}
	print_Table(ptemp);

}
      



/*
[csec159@sel-19 ~]$ gcc -o a a4.c 
[csec159@sel-19 ~]$ ./a
MENU
1.Priority
2.Round Robin
Enter choice:1

Enter the no. of processes:5

Enter Process ID:p1
Enter arrival time:0
Enter burst time:6

Enter Process ID:p2
Enter arrival time:1
Enter burst time:2

Enter Process ID:p3
Enter arrival time:1
Enter burst time:3

Enter Process ID:p4
Enter arrival time:2
Enter burst time:1

Enter Process ID:p5
Enter arrival time:2
Enter burst time:2
Enter the priority for each process:
p1:2
p2:2
p3:4
p4:1
p5:3
PRIORITY NON PREEMPTIVE SCHEDULING
--------------------------------------------------------
   p1       p4       p2       p5       p3    
--------------------------------------------------------
0       6       7       9       11       14

---------------------------------------------------------------------------------------------
Process ID	Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time
---------------------------------------------------------------------------------------------
p1                      0            6                6              0            0
p4                      2            1                5              4            4
p2                      1            2                8              6            6
p5                      2            2                9              7            7
p3                      1            3               13             10           10
---------------------------------------------------------------------------------------------
                              Average            8.20              5.40          5.40



C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A4>gcc -o a a4.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A4>a
MENU
1.Priority
2.Round Robin
Enter choice:2

Enter the no. of processes:5

Enter Process ID:p1
Enter arrival time:0
Enter burst time:6

Enter Process ID:p2
Enter arrival time:1
Enter burst time:2

Enter Process ID:p3
Enter arrival time:1
Enter burst time:3

Enter Process ID:p4
Enter arrival time:2
Enter burst time:1

Enter Process ID:p5
Enter arrival time:2
Enter burst time:2
Enter the time quantum:2
ROUND ROBIN SCHEDULING
-------------------------------------------------------------------------
    p1        p2        p3        p4        p5        p1        p3        p1
-------------------------------------------------------------------------
 0        2        4        6        7        9        11        12        14

---------------------------------------------------------------------------------------------
Process ID      Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time
---------------------------------------------------------------------------------------------
p1                      0            6               14              8            0
p2                      1            2                3              1            1
p3                      1            3               11              8            3
p4                      2            1                5              4            4
p5                      2            2                7              5            5
---------------------------------------------------------------------------------------------
                              Average            8.00              5.20          2.60

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A4>gcc -o a a4.c

C:\Users\Sowmya\Desktop\Sowmya\Lab\OS\A4>a
MENU
1.Priority NP
2.Priority P
3.Round Robin
Enter choice:2

Enter the no. of processes:5

Enter Process ID:p1
Enter arrival time:0
Enter burst time:6

Enter Process ID:p2
Enter arrival time:1
Enter burst time:2

Enter Process ID:p3
Enter arrival time:1
Enter burst time:3

Enter Process ID:p4
Enter arrival time:2
Enter burst time:1

Enter Process ID:p5
Enter arrival time:2
Enter burst time:2
Enter the priority for each process:
p1:2
p2:2
p3:4
p4:1
p5:3
PREEMPTIVE PRIORITY SCHEDULING
--------------------------------------------------------
   p1       p4       p1       p2       p5       p3
--------------------------------------------------------
0       2       3       7       9       11       14

---------------------------------------------------------------------------------------------
Process ID      Arrival Time  Burst Time   TurnaroundTime   Waiting Time   Response Time
---------------------------------------------------------------------------------------------
p1                      0            6                7              1            0
p2                      1            2                8              6            6
p3                      1            3               13             10           10
p4                      2            1                1              0            0
p5                      2            2                9              7            7
---------------------------------------------------------------------------------------------
                              Average            7.60              4.80          4.60
*/


























	

