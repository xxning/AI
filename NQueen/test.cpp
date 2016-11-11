#include<stdio.h>
#include<stdlib.h>
void test();

int *col;
int *right;
int *left;
int *res;
int N,X,Y;
FILE *input;
FILE *check;
int flag;
int main(int argc,char *argv[]){
	
	input=fopen(argv[1],"r");
	check=fopen(argv[2],"r");
	if(!input||!check){
		printf("can't open object file!\n");
		exit(1);
	}
	fscanf(input,"%d %d %d",&N,&X,&Y);
	col=(int*)malloc((N+1)*sizeof(int));
	res=(int*)malloc((N+1)*sizeof(int));
	int i;
	for(i=0;i<N+1;i++){
		res[i]=col[i]=0;
	}
	left=(int*)malloc((2*N)*sizeof(int));
	right=(int*)malloc((2*N)*sizeof(int));
	for(i=0;i<2*N;i++){
		left[i]=right[i]=0;
	}
	for(i=1;i<N+1;i++){
		fscanf(check,"%d",&res[i]);
	}
	test();
	if(flag==0)
		printf("correct!\n");
	else
		printf("error!\n");

	return 0;
}

void test(){
	
	int i,j,l,r;
	flag=0;
	for(i=1;i<=N;i++){
		j=res[i];
		if(j>N||j<1){
			flag=1;
			return;
		}
		if(col[j]==0){
			col[j]=1;
		}
		else{
			flag=1;
			return;
		}
		l=i+j-1;
		r=i+N-j;
		if(left[l]==0){
			left[l]=1;
		}
		else{
			flag=1;
			return;
		}
		if(right[r]==0){
			right[r]=1; 
		}
		else{
			flag=1;
			return;
		}
	}
	if(res[X]==Y)
		flag=1;
}
