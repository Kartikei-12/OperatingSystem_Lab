// @author: Kartikei Mittal
// ID: 2017KUCP1032
// 
#include<iostream>
#include<windows.h>
#include<pthread.h>
    using namespace std;

int readcount;

class Semaphore
{
private:
    int s;
public:
    Semaphore(): s(1) {;}
    friend void wait(Semaphore &s);
    friend void signal(Semaphore &s);
} wrt, mutex;

void wait(Semaphore &s) {
    // cout<<"wait"<<endl;
    while(s.s == 0);
    --s.s;
}

void signal(Semaphore &s) {
    // cout<<"signal"<<endl;
    ++s.s;
}

void* reader(void *d)
{
    Sleep(1);
    wait(mutex);
    ++readcount;
    if(readcount == 1)
        wait(wrt);
    signal(mutex);
    // Sleep(1);
    cout<<"Reader: "<<(int)d<<endl;
    Sleep(1);
    wait(mutex);
    --readcount;
    if(readcount == 0)
        signal(wrt);
    signal(mutex);
    Sleep(1);
}

void* writer(void *d)
{
    Sleep(1);
    wait(wrt);
    Sleep(1);
    cout<<"Writer:"<<(int)d<<endl;
    Sleep(1);
    signal(wrt);
    Sleep(1);
}

int main(int argc, char const *argv[])
{
    // system("clear");
    // wait(wrt);
    // signal(wrt);
    pthread_t r[3], w[3];
    for(int i=1; i<=3; ++i)
        pthread_create(&r[i-1], NULL, reader, (void*)i);
    for(int i=1; i<=3; ++i)
        pthread_create(&w[i-1], NULL, writer, (void*)i);
    pthread_join(w[0], NULL);
    pthread_join(r[0], NULL);
    pthread_join(w[1], NULL);
    pthread_join(w[2], NULL);
    pthread_join(r[1], NULL);
    pthread_join(r[2], NULL);
    
    cout<<"Terminate"<<endl;
    return 0;
}
