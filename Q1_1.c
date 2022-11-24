#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <time.h>

static void* Acount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	diff=diff/1000000000;
	printf("Elapsed Time FIFO =%lf seconds\n",diff);
	return NULL;
}


static void* Bcount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	diff = diff/1000000000;
	printf("Elapsed Time RR=%lf seconds\n",diff);
	return NULL;
}


static void* Ccount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double diff = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	diff = diff/1000000000;
	printf("Elapsed Time OTHER=%lf seconds\n",diff);
	return NULL;
}

int main(int argc, char argv[]){
	pthread_t threadA, threadB, threadC;
	pthread_attr_t attr1,attr2,attr3;
	pthread_attr_t *attrp1,*attrp2,*attrp3;

	int S;
	attrp1 = &attr1;
	attrp2 = &attr2;
	attrp3 = &attr3;

	S = pthread_attr_init(&attr1);	
	S = pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
	S = pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamFIFO;
	schedParamFIFO.sched_priority = 1;
	S = pthread_attr_setschedparam(&attr1, &schedParamFIFO);
	S = pthread_create(&threadA, attrp1, &Acount, NULL);
	
	S = pthread_attr_init(&attr2);
	S = pthread_attr_setschedpolicy(&attr2,SCHED_RR);
	S = pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamRR;
	schedParamRR.sched_priority = 1;
	S = pthread_attr_setschedparam(&attr2, &schedParamRR);
	S = pthread_create(&threadB, attrp2, &Bcount, NULL);
	
	S = pthread_attr_init(&attr3);
	S = pthread_attr_setschedpolicy(&attr3,SCHED_OTHER);
	S = pthread_attr_setinheritsched(&attr3,PTHREAD_EXPLICIT_SCHED);
	struct sched_param schedParamOTHER;
	schedParamOTHER.sched_priority = 0;
	S = pthread_attr_setschedparam(&attr3, &schedParamOTHER);
	S = pthread_create(&threadC, attrp3, &Ccount, NULL);

	if(attrp1 != NULL){ S= pthread_attr_destroy(attrp1);}
	if(attrp2 != NULL){ S= pthread_attr_destroy(attrp2);}
	if(attrp3 != NULL){ S= pthread_attr_destroy(attrp3);}

	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);
	pthread_join(threadC, NULL);

	return 0;
}
