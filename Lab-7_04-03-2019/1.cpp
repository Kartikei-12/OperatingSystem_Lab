// @author: Kartikei Mittal
// ID: 2017KUCP1032
// Implemented Round Robin Sheduling Algorithm
#include<bits/stdc++.h>
    using namespace std;

class Process
{
public:
    int id, at, bt, ct, tat, wt, rt;

    Process() { at = bt = wt = ct = tat = rt = 0; }
    void operator=(const Process &temp)
    {
        id  = temp.id ;
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
        if(P[i].rt)
            return true;
    return false;
}

void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT  | BT | CT | TAT   | WT  | RT |"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<P[i].id<<"    "
            <<P[i].at<<"     "
            <<P[i].bt<<"    "
            <<P[i].ct<<"      "
            <<P[i].tat<<"     "
            <<P[i].wt<<"    "
            <<P[i].rt<<"    "<<endl;
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

int main(int argc, char const *argv[]) try
{
    int N=0, timE=0, pid=0, time_quanta=0;
    double atat=0.0, awt=0.0;
    queue<int> process_queue;
    Process P[100], temp;

    if(argc != 2)
    {
        cerr<<"Invalid argument.";
        return 0;
    }
    if(*argv[1] == '2')
    {
        cout<<"\n\nEnter number of process: "; cin>>N;
        cout<<"\nEnter time quanta: "; cin>>time_quanta;
        for(int i=0; i<N; ++i)
        {
            cout<<"Enter arrival and burst time for proceess with pid as "
                <<i+1<<" :";
            cin>>P[i].at>>P[i].bt;
            P[i].rt = P[i].bt;
            P[i].id = i + 1;
        }
    }
    else if(*argv[1] == '1')
    {
        ifstream file("Lab-7_04-03-2019/input.txt"); 
        N = count(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), '\n');
        file.close();
        ifstream file1("Lab-7_04-03-2019/input.txt");
        file1>>time_quanta;
        for(int i=0; i<N; ++i)
        {
            file1>>P[i].at>>P[i].bt;
            P[i].id = i + 1;
            P[i].rt = P[i].bt;
        }
        file1.close();
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
        cout<<"P"<<P[pid].id<<" | ";
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
catch(exception &e) {
    cerr<<"FAILURE: "<<e.what();
}