// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Priority based sheduling with preemption
#include<iostream>
    using namespace std;

class Process
{
public:
    int id, at, bt, ct, tat, wt, rt, priority;

    void operator=(const Process &temp)
    {
        id  = temp.id ;
        priority  = temp.priority ;
        at  = temp.at ;
        bt  = temp.bt ;
        ct  = temp.ct ;
        tat = temp.tat;
        wt  = temp.wt ;
        rt  = temp.rt ;
    }
};

int getPriorityProcess(Process P[], int size, int timE)
{
    int a = -1, max = -10000;
    for(int i=0; i<size; ++i)
        if(P[i].at <= timE && P[i].rt>0 && P[i].priority>max)
        {
            a = i;
            max = P[i].priority;
        }
    return a;
}

bool isProcessRemaining(Process P[], int size)
{
    for(int i=0; i<size; ++i)
        if(P[i].rt)
            return true;
    return false;
}

void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT  | BT | Priority | CT | TAT   | WT   |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<P[i].id<<"    "
            <<P[i].at<<"     "
            <<P[i].bt<<"     "
            <<P[i].priority<<"         "
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
    Process P[N], temp;
    //Input
    for(int i=0; i<N; ++i)
    {
        cout<<"Enter arrival and burst time and priority for proceess with pid as "
            <<i+1<<" :";
        cin>>P[i].at>>P[i].bt>>P[i].priority;
        P[i].id = i+1;
        P[i].rt = P[i].bt;
        P[i].ct = P[i].tat = P[i].wt = 0;
    }
    //Processing
    //Sort according to arrival time
    for(int i=0; i<(N-1); ++i)
        for(int j=0; j<(N-i-1); ++j)
            if(P[j].at > P[j+1].at)
            {
                temp = P[j];
                P[j] = P[j+1];
                P[j+1] = temp;
            }
    cout<<"\nGantt chart:\n| ";
    do
    {
        pid = getPriorityProcess(P, N, timE);
        ++timE;
        if(pid == -1)
        {
            cout<<timE<<" | ";
            continue ;
        }
        cout<<"P"<<P[pid].id<<" | ";
        --P[pid].rt;
        if(P[pid].rt == 0)
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