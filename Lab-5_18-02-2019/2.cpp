// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Sortest Job First Scheduling Algorithm
// with burst time prediction
#include<iostream>
    using namespace std;

struct Process {
    bool isCompleted;
    int at, bt, ct, tat, wt;
    double pbt;
};

int getShotestArrivedProcess(Process P[], int size, int timE)
{
    int a = -1, min=32000;
    for(int i=0; i<size; ++i)
        if(P[i].pbt<min && !P[i].isCompleted && P[i].at<=timE)
        {
            a = i;
            min = P[i].pbt;
        }
    return a;
}

bool isProcessRemaining(Process P[], int size)
{
    for(int i=0; i<size; ++i)
        if(!P[i].isCompleted)
            return true;
    return false;
}

void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT   | BT | PBT | CT | TAT   | WT   |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<i+1<<"      "
            <<P[i].at<<"    "
            <<P[i].bt<<"     "
            <<P[i].pbt<<"    "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
}

int main()
{
    int N=0, timE=0, a=0, pid=0;
    double atat=0.0, awt=0.0, alpha=0.5;
    
    cout<<"\n\nEnter alpha: ";
    cin>>alpha;
    cout<<"\n\nEnter number of process: ";
    cin>>N;
    Process P[N], temp;
    
    for(int i=0; i<N; ++i)
    {
        cout<<"Enter arrival and burst time for proceess with pid as "<<i+1<<" :";
        cin>>P[i].at>>P[i].bt;
        P[i].ct = P[i].tat = P[i].wt = 0;
        P[i].isCompleted = false;
    }
    
    //Sort according to arrival time
    for(int i=0; i<N; ++i)
        for(int j=i; j<N; ++j)
            if(P[j].at > P[j+1].at)
            {
                temp = P[j];
                P[j] = P[j+1];
                P[j+1] = temp;
            }
    
    //Setting predicted burst time
    P[0].pbt = P[0].bt*1.0;
    for(int i=1; i<N; ++i)
        P[i].pbt = alpha*(P[i-1].bt-P[i-1].pbt) + P[i-1].pbt;
    
    cout<<"\nGantt chart:\n| ";
    do
    {
        pid = getShotestArrivedProcess(P, N, timE);
        if(pid != -1) timE += P[pid].bt;
        else
        {  
            cout<<++timE<<" | ";
            continue;
        }
        P[pid].ct = timE;
        P[pid].isCompleted = true;
        P[pid].tat = P[pid].ct - P[pid].at;
        P[pid].wt = P[pid].tat - P[pid].bt;
        atat += P[pid].tat;
        awt += P[pid].wt;
        cout<<"P"<<pid+1<<" | ";
    }while(isProcessRemaining(P, N));
    
    showProcessTab(P, N);
    cout<<"\nAverage turaroung time: "<<atat/N
        <<"\nAverage Waiting time: "<<awt/N<<endl;
    return 0;
}