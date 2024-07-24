

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *routine()
{
    printf("Test from thread\n");
    sleep(3);
     printf("All is ok for me\n");
    return(0);
}
void *routine_tow()
{
    printf("Test from thread_tow\n");
    sleep(3);
    printf("All is ok me too\n");
    return(0);
}

int main()
{
    pthread_t t1;
    pthread_t t2;
    pthread_create(&t1, NULL, &routine,NULL);
    pthread_create(&t2, NULL, &routine_tow,NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return(0);
}
