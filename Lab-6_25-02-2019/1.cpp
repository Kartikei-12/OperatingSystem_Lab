// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Sortest Remaining Time First
#include<iostream>
    using namespace std;

struct Process { int at, bt, ct, tat, wt, rt; };

int getShortestRemainingTimeProcess(Process P[], int size, int timE)
{
    int a = -1, min=32000;
    for(int i=0; i<size; ++i)
        if(P[i].rt<min && P[i].rt>0 && P[i].at<=timE)
        {
            a = i;
            min = P[i].rt;
        }
    return a;
}

bool isProcessRemaining(Process P[], int size)
{
    for(int i=0; i<size; ++i)
        if(P[i].rt>0)
            return true;
    return false;
}

void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT   | BT | CT | TAT   | WT   |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<i+1<<"      "
            <<P[i].at<<"    "
            <<P[i].bt<<"     "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
}

int main()
{
    int N=0, timE=0, pid=0;
    double atat=0.0, awt=0.0;
    
    cout<<"\n\nEnter number of process: ";
    cin>>N;
    Process P[N];
    //Input
    for(int i=0; i<N; ++i)
    {
        cout<<"Enter arrival and burst time for proceess with pid as "<<i+1<<" :";
        cin>>P[i].at>>P[i].bt;
        P[i].rt = P[i].bt;
        P[i].ct = P[i].tat = P[i].wt = 0;
    }
    //Processing
    cout<<"\nGantt chart:\n| ";
    do
    {
        pid = getShortestRemainingTimeProcess(P, N, timE);
        ++timE;
        if(pid==-1) {  
            cout<<timE<<" | "; continue;
        }
        --P[pid].rt;
        cout<<"P"<<pid+1<<" | ";
        if(P[pid].rt)
            P[pid].ct = timE;
        
    }while(isProcessRemaining(P, N));
    
    //Compiling Result
    for(int i=0; i<N; ++i)
    {
        P[i].tat = P[i].ct - P[i].at;
        P[i].wt = P[i].tat - P[i].bt;
        atat += P[i].tat;
        awt += P[i].wt;
    }
    awt /= N;
    atat /= N;

    //Output
    showProcessTab(P, N);
    cout<<"\nAverage turaroung time: "<<atat
        <<"\nAverage Waiting time: "<<awt<<endl;
    return 0;
}