#include<iostream>
    using namespace std;

struct Process {
    bool isCompleted;
    int at, bt, ct, tat, wt;
};

int getEarlistProcess(Process P[], int size)
{
    int a = -1, min=32000;
    for(int i=0; i<size; ++i)
        if(P[i].at < min && !P[i].isCompleted)
        {
            a = i;
            min = P[i].at;
        }
    return a;
}

int main()
{
    int N=0, time=0, a=0, pid=0;
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
        pid = getEarlistProcess(P, N);
        
        if(time >= P[pid].at)
            time += P[pid].bt;
        else
        {
            a = P[pid].at-time;
            time += a;
            cout<<a<<" | ";
            continue;
        }
        P[pid].ct = time;
        P[pid].isCompleted = true;
        P[pid].tat = P[pid].ct - P[pid].at;
        P[pid].wt = P[pid].tat - P[pid].bt;
        atat += P[pid].tat;
        awt += P[pid].wt;
        cout<<"P"<<pid+1<<" | ";
    }while(getEarlistProcess(P, N) != -1);
    
    cout<<"\n\nProcess Id | AT   | BT   | CT   | TAT   | WT   |"<<endl;
    for(int i=0; i<N; ++i)
        cout<<"\t"
            <<i+1<<"      "
            <<P[i].at<<"    "
            <<P[i].bt<<"      "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
    cout<<"\nAverage turaroung time: "<<atat/N
        <<"\nAverage Waiting time: "<<awt/N<<endl;
    return 0;
}