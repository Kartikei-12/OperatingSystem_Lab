// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Round Robin Sheduling Algorithm
#include<iostream>
#include<queue>
    using namespace std;

class Process
{
public:
    int at, bt, ct, tat, wt, rt;

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


bool isProcessRemaining(Process P[], int size)
{
    for(int i=0; i<size; ++i)
        if(P[i].rt>0)
            return true;
    return false;
}

void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT  | BT | CT | TAT   | WT   |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<i+1<<"    "
            <<P[i].at<<"     "
            <<P[i].bt<<"    "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "<<endl;
}

void loadNewProcess(
    Process P[],
    int size,
    queue<int> &process_queue,
    int time_point,
    int timE
) {
    for(int i=0; i<size; ++i)
        if(P[i].rt>0 && P[i].at>time_point && P[i].at<=timE)
            process_queue.push(i);
}

int main()
{
    int N=0, timE=0, pid=0, time_quanta=0;
    double atat=0.0, awt=0.0;
    queue<int> process_queue;

    cout<<"\n\nEnter number of process: ";
    cin>>N;
    cout<<"\nEnter time quanta: ";
    cin>>time_quanta;
    Process P[N], temp;
    //Input
    for(int i=0; i<N; ++i)
    {
        cout<<"Enter arrival and burst time for proceess with pid as "<<i+1<<" :";
        cin>>P[i].at>>P[i].bt;
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
    loadNewProcess(P, N, process_queue, timE-time_quanta, timE);
    cout<<"\nGantt chart:\n| ";
    do
    {
        
        if(!process_queue.size())
        {
            ++timE;
            cout<<timE<<" | ";
            continue ;
        }
        
        pid = process_queue.front();
        process_queue.pop();
        
        if(P[pid].rt < time_quanta)
        {
            timE += P[pid].rt;
            P[pid].rt = 0;
        }
        else
        {
            timE += time_quanta;
            P[pid].rt -= time_quanta;
        }
        cout<<"P"<<pid+1<<" | ";
        loadNewProcess(P, N, process_queue, timE-time_quanta, timE);
        if(P[pid].rt == 0)
            P[pid].ct = timE;
        else
            process_queue.push(pid);
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