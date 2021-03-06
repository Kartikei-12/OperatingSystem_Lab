// @author: Kartikei Mittal
// ID: 2017KUCP1032
//Predicting burst time
#include<iostream>
    using namespace std;

struct Process {
    bool isCompleted;
    int at, bt, ct, tat, wt;
    double pbt;
};
void showProcessTab(Process P[], int size)
{
    cout<<"\n\nProcess Id | AT   | BT   | PBT"<<endl;
    for(int i=0; i<size; ++i)
        cout<<"\t"
            <<i+1<<"       "
            <<P[i].at<<"    "
            <<P[i].bt<<"    "
            <<P[i].pbt<<endl;
}

int main()
{
    int N=0, timE=0, a=0, pid=0, sum=0;
    double atat=0.0, awt=0.0, alpha=0.5;
    
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
    
    P[0].pbt = 10;
    for(int i=1; i<N; ++i)
        P[i].pbt = alpha*P[i-1].bt + (1-alpha)*P[i-1].pbt;
    showProcessTab(P, N);
    return 0;
}