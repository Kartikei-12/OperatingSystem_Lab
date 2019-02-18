// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Sortest Job First Scheduling Algorithm
#include<iostream>
    using namespace std;

struct Process {
    bool isCompleted;
    int at, bt, ct, tat, wt;
};

int getShotestArrivedProcess(Process P[], int size, int timE)
{
    int a = -1, min=32000;
    for(int i=0; i<size; ++i)
        if(P[i].bt<min && !P[i].isCompleted && P[i].at<=timE)
        {
            a = i;
            min = P[i].bt;
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
    cout<<"\n\nProcess Id | AT   | BT   | CT   | TAT   | WT   |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<i+1<<"      "
            <<P[i].at<<"    "
            <<P[i].bt<<"      "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
}

int main()
{
    int N=0, timE=0, a=0, pid=0;
    double atat=0.0, awt=0.0;
    
    cout<<"\n\nEnter number of process: ";
    cin>>N;
    Process P[N];
    
    for(int i=0; i<N; ++i)
    {
        cout<<"Enter arrival and burst time for proceess with pid as "<<i+1<<" :";
        cin>>P[i].at>>P[i].bt;
        P[i].ct = P[i].tat = P[i].wt = 0;
        P[i].isCompleted = false;
    }
 
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