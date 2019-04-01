// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Priority based sheduling without preemtion
#include<iostream>
#include<fstream>
    using namespace std;

class Process
{
public:
    int at, bt, ct, tat, wt, rt, priority;

    void operator=(const Process &temp)
    {
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
    int a = -1, min=32000;
    for(int i=0; i<size; ++i)
        if(P[i].at <= timE && P[i].rt>0 && P[i].priority<min)
        {
            a = i;
            min = P[i].priority;
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
            <<i+1<<"    "
            <<P[i].at<<"     "
            <<P[i].bt<<"    "
            <<P[i].priority<<"         "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
}

int main(int argc, char const *argv[])
{
    int N=0, timE=0, pid=0;
    double atat=0.0, awt=0.0;
    if(argc != 2)
    {
        cerr<<"Invalid argument.";
        return 0;
    }
    if(*argv[1] == '1')
    {
        N = ;
        fstream file("input.txt", ios::in);
    }
    else if(*argv[1] == '2')
    {
        cout<<"\n\nEnter number of process: ";
        cin>>N;
        Process P[N], temp;
        //Input
        for(int i=0; i<N; ++i)
        {
            cout<<"Enter arrival and burst time and priority for proceess with pid as "
                <<i+1<<" :";
            cin>>P[i].at>>P[i].bt>>P[i].priority;
            P[i].rt = P[i].bt;
            P[i].ct = P[i].tat = P[i].wt = 0;
        }
    }
    else
    {
        cerr<<"Invalid argument. 2";
        return 0;
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
        if(pid == -1)
        {
            ++timE;
            continue ;
        }
        cout<<"P"<<pid+1<<" | ";
        timE += P[pid].bt;
        P[pid].ct = timE;
        P[pid].rt = 0;
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