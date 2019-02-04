// Checking scanf() in fork()

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
    int a, b;
    fork();
    scanf("%d", &a);
    printf("%d", a);
    // scanf("%d", &b);
    // printf("%d", b);
    return 0;
}