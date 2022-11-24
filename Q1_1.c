#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <time.h>

double t1,t2,t3;

static void* Acount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t1= 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	t1=t1/1000000000;
	printf("Elapsed Time FIFO =%lf seconds\n",t1);
	return NULL;
}


static void* Bcount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t2 = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	t2 = t2/1000000000;
	printf("Elapsed Time RR=%lf seconds\n",t2);
	return NULL;
}


static void* Ccount(){
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);
	long long int i=0;
	for(;i<pow(2,32);i++){}
	clock_gettime(CLOCK_MONOTONIC, &end);
	t3 = 1000000000 * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;
	t3 = t3/1000000000;
	printf("Elapsed Time OTHER=%lf seconds\n",t3);
	return NULL;
}

int main(int argc, char argv[]){
	int p=1;
	for(int i=0;i<10;i++){
		FILE *fptr;
		fptr = open ("histogram.data","a");
		printf("Priority :%d\n",p);
		pthread_t threadA, threadB, threadC;
		pthread_attr_t attr1,attr2,attr3;
		pthread_attr_t *attrp1,*attrp2,*attrp3;

		int S;

		S = pthread_attr_init(&attr1);	
		S = pthread_attr_setschedpolicy(&attr1,SCHED_FIFO);
		S = pthread_attr_setinheritsched(&attr1,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamFIFO;
		schedParamFIFO.sched_priority = 1;
		S = pthread_attr_setschedparam(&attr1, &schedParamFIFO);
		S = pthread_create(&threadA, &attr1, &Acount, NULL);

		S = pthread_attr_init(&attr2);
		S = pthread_attr_setschedpolicy(&attr2,SCHED_RR);
		S = pthread_attr_setinheritsched(&attr2,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamRR;
		schedParamRR.sched_priority = 1;
		S = pthread_attr_setschedparam(&attr2, &schedParamRR);
		S = pthread_create(&threadB, &attr2, &Bcount, NULL);

		S = pthread_attr_init(&attr3);
		S = pthread_attr_setschedpolicy(&attr3,SCHED_OTHER);
		S = pthread_attr_setinheritsched(&attr3,PTHREAD_EXPLICIT_SCHED);
		struct sched_param schedParamOTHER;
		schedParamOTHER.sched_priority = 0;
		S = pthread_attr_setschedparam(&attr3, &schedParamOTHER);
		S = pthread_create(&threadC, &attr3, &Ccount, NULL);

		pthread_join(threadA, NULL);
		pthread_join(threadB, NULL);
		pthread_join(threadC, NULL);
		fprintf(fptr,"%d %lf %lf %lf",p,t1,t2,t3);
		p++;
	}
	fptr.close();
	return 0;
}
