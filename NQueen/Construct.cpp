#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void Construct();
void Output();
int N;
int X,Y;
int *res;
FILE *result;
clock_t begin,finish;
double Time;
int main(){
	
	FILE *source=fopen("input.txt","r");
	result=fopen("output_construct.txt","w");
	if(!result||!source){
		printf("can't open object file.\n");
		exit(1);
	}
	fscanf(source,"%d %d %d",&N,&X,&Y);
	res=(int*)malloc((N+1)*sizeof(int));
	begin=clock();
	Construct();
	finish=clock();
	Time=Time=(double)(finish-begin)/CLOCKS_PER_SEC;
	printf("Time:%lf\n",Time);
	Output();	

	return 0;
}

void Construct(){

	int m;
	int i,j,k;
	m=N%6;
	switch(m){

		case 2:
		case 3:{
			k=N/2;
			if(k%2==0&&N%2==0){
				for(i=1;i<=N;i++){
					res[i]=k+2*i-2;
					if(res[i]==N)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j);
					if(res[i]==k-2)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+k+1;
					if(res[i]==N-1)
						break;
				}
				i++;
				j=i;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+1;
				}
			}
			else if(k%2==0&&N%2!=0){
				for(i=1;i<=N;i++){
					res[i]=k+2*i-2;
					if(res[i]==N-1)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j);
					if(res[i]==k-2)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+k+1;
					if(res[i]==N-2)
						break;
				}
				i++;
				j=i;
				for(i;i<=N-1;i++){
					res[i]=2*(i-j)+1;
				}
				res[i]=N;
			}
			else if(k%2!=0&&N%2==0){
				for(i=1;i<=N;i++){
					res[i]=k+2*i-2;
					if(res[i]==N-1)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)-1;
					if(res[i]==k-2)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+k+1;
					if(res[i]==N)
						break;
				}
				i++;
				j=i;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+2;
				}
			}
			else{
				for(i=1;i<=N;i++){
					res[i]=k+2*i-2;
					if(res[i]==N-2)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)-1;
					if(res[i]==k-2)
						break;
				}
				i++;
				j=i-1;
				for(i;i<=N;i++){
					res[i]=2*(i-j)+k+1;
					if(res[i]==N-1)
						break;
				}
				i++;
				j=i;
				for(i;i<=N-1;i++){
					res[i]=2*(i-j)+1;
				}
				res[i]=N;
			}
			break;
		}
		default:{
			k=N/2;
			for(i=1;i<=k;i++){
				res[i]=2*i;
			}		
			for(i=k+1;i<=N;i++){
				res[i]=2*(i-k)-1;
			}
			break;
		}
	}
}

void Output(){
	
	int i;
	if(res[X]!=Y){
		for(i=1;i<=N;i++){
			fprintf(result,"%d\n",res[i]);
		}
	}
	else if(res[X]!=1){
		for(i=N;i>=1;i--){
			fprintf(result,"%d\n",res[i]);
		}
	}
	else{
		for(i=1;i<=N;i++){
			fprintf(result,"%d\n",N+1-res[i]);
		}
	}
}


