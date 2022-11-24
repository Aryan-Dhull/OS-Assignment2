#define _GNU_SOURCE
#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdlib.h>

#define SYS_kernel_2d_memcpy 451

int main(int argc, char **argv)
{
	int r=2;
	int c=2;
	float mat1[2][2]={{1.2,2.3},{3.4,4.5}};
	float mat2[2][2]={{0,0},{0,0}};
	
	printf("This is the matrix to be copied:\n");

	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			printf("%lf ",mat1[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("This is the initial matrix:\n");

	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			printf("%lf ",mat2[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	int res = syscall(SYS_kernel_2d_memcpy, &mat1, &mat2);

	if(res<0){
		perror("ERROR! \n");
		exit(1);
	}
	else if(res == 0) printf("syscall successfull\n");
	
	printf("This is the given matrix after copying:\n");

	for(int i=0;i<r;i++){
		for(int j=0;j<r;j++){
			printf("%lf ",mati[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	printf("This is the matrix copied\n");

	for(int i=0;i<r;i++){
		for(int j=0;j<c;j++){
			printf("%lf ",mat2[i][j]);
		}
		printf("\n");
	}

	return 0;
}
