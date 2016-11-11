#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//#define INFINITY_ 1000000000  //1 billion
void forward(int row,int i0,int i1);
void backward(int row,int i0,int i1);
void fward(int row,int i0,int i1);
void judge();
void output();
void restart();
void compute();
void simulated_annealing();

double E=2.71828;
int N;	//皇后规模 
int X,Y; //障碍位置 

//int *row; //记录行冲突 
//int *col; //记录列冲突 
int *left;//坐斜线冲突 
int *right ;//右斜线冲突 

int *res;
//int **state;

int next_i,next_j;
clock_t start,finish;
double Time;
int min;
int flag;
FILE *result;
FILE *input;
int *attack;
int num_atk;
int count=0;
int T;
int main(){
	
	input=fopen("input.txt","r");
	result=fopen("output_simulated_annealing.txt","w");	
	if(!input||!result){
		printf("can't open object file.\n");
		exit(1);
	}
	int i,j;
	fscanf(input,"%d %d %d",&N,&X,&Y);
	if(N<=3){
		printf("No answer,please input N>3.\n");
		return 0;
	}
	if(X<1||X>N||Y<1||Y>N){
		printf("Error:illegal coordinate of obstacle.\n");
		exit(1);
	}
	//row=(int*)malloc((N+1)*sizeof(int));
	//col=(int*)malloc((N+1)*sizeof(int)); 
	res=(int*)malloc((N+1)*sizeof(int));
	attack=(int*)malloc((N+1)*sizeof(int));
	for(i=0;i<N+1;i++){
		res[i]=attack[i]=0;
	}
	left=(int*)malloc((2*N)*sizeof(int));
	right=(int*)malloc((2*N)*sizeof(int));
	for(i=0;i<2*N;i++){
		left[i]=right[i]=0;
	}
//node(i,j),row:i;col:j;left:i+j-1;right:(i+N-j);
//h表示 形成相互攻击的皇后对的个数 
	srand((unsigned)time(NULL));
	
	//start=clock();
	for(i=1;i<=N;i++){
		res[i]=i;
	}
	right[N]=N;
	for(i=1;i<2*N;i=i+2){
		left[i]=1;
	} 
	restart();
	start=clock();//printf("%ld\n",start);
	simulated_annealing();
	finish=clock();//printf("%ld\n",finish);
	
	
	Time=(double)(finish-start)/CLOCKS_PER_SEC;	
	output();
	fprintf(result,"%lf\n",Time);
	//printf("%lf\n",Time);
	//judge();
	//printf("%d\n",flag);
	//printf("%d\n",count);
	//system("pause");
	fclose(input);
	fclose(result);
	return 0;
}
//O(n^2) 
void simulated_annealing(){
		
	int i,j,k,l,m;
	int temp;
	int current,next;
	double q1,q2;
	while(1){
		compute();	
		judge();
		current=flag;
		while(flag==0){	
			if(res[X]!=Y)		
				return;
			else{
				restart();
				compute();
				current=flag;
			}
		}
		//printf("%d\n",flag);
		//node(i,j),row:i;col:j;left:i+j-1;right:(i+N-j);
		
		//compute();
		//m=pow(N,1.5);
		for(i=1;i<N;i++){
			//printf("atk:%d i:%d\n",num_atk,i);
			//fprintf(result,"atk:%d\n",num_atk);
			for(j=0;j<num_atk;j++){
				for(m=1;m<9;m++){
				
					k=rand()%N;
					k++;
					l=attack[j];
					if(k==l)
						continue;					
					forward(l,res[l],res[k]);
					forward(k,res[k],res[l]);
					//judge();
					if(flag==0){
						temp=res[l];
						res[l]=res[k];
						res[k]=temp;
						//printf("i:%d\n",i);
						if(res[X]!=Y)
							return ;
						
						else{
							restart();
							current=flag;
							j=N+1;
							m=1;
							min=10;
							continue;
						}
						
					}
					else if(flag<current){
						current=flag;
						temp=res[l];
						res[l]=res[k];
						res[k]=temp;
						break;
					//break;//
					}
					else{
						
						q1=rand()/(RAND_MAX+1.0);
						T=flag/10;
						q2=pow(E,(1.0)*(min-flag)/T);
						//printf("%lf %lf\n",q1,q2);
						if(q1<q2){
							current=flag;
							temp=res[l];
							res[l]=res[k];
							res[k]=temp;
						}
						else{
							backward(l,res[k],res[l]);
							backward(k,res[l],res[k]);
						}
						
					}
				}
			}
			compute();
		}			
		restart();
		//count++;
	}

}

//node(i,j),row:i;col:j;left:i+j-1;right:(i+N-j);
//O(1)
void forward(int row,int i0,int i1){
	
	int l0,r0,l1,r1;
	l0=row+i0-1;
	r0=row+N-i0;
	l1=row+i1-1;
	r1=row+N-i1;
	//left[l0]
	flag-=left[l0]-1;
	left[l0]--;
	//right[r0]	
	flag-=right[r0]-1;		
	right[r0]--;
	//left[l1]
	flag+=left[l1];	
	left[l1]++;
	//right[r1]	
	flag+=right[r1];		
	right[r1]++;
} 
//O(1)
void backward(int row,int i0,int i1){
	
	int l0,r0,l1,r1;
	l0=row+i0-1;
	r0=row+N-i0;
	l1=row+i1-1;
	r1=row+N-i1;
	//left[l0]
	flag-=left[l0]-1;
	left[l0]--;
	//right[r0]	
	flag-=right[r0]-1;		
	right[r0]--;
	//left[l1]
	flag+=left[l1];	
	left[l1]++;
	//right[r1]	
	flag+=right[r1];		
	right[r1]++;
}

//O(n) 
void judge(){
	
	flag=0;
	int k,l;
	l=2*N-1;
	for(k=1;k<=l;k++){
		if(left[k]>=2)
			flag+=(left[k]*(left[k]-1))/2;
		if(right[k]>=2)
			flag+=(right[k]*(right[k]-1))/2; 			
	}
}

void output(){
	
	int i;
	for(i=1;i<=N;i++){
		fprintf(result,"%d\n",res[i]);
	}
}
//O(n)
void restart(){
	
	int i,j,k;
	int temp;
	for(i=1;i<=N;i++){
		j=rand()%N;
		j++;
		//k=rand()%N;
		//k++;
		if(j==i)
			continue;
		forward(j,res[j],res[i]);
		forward(i,res[i],res[j]);
		temp=res[j];
		res[j]=res[i];
		res[i]=temp;
	}
}
//node(i,j),row:i;col:j;left:i+j-1;right:(i+N-j);
//O(n) 
void compute(){
	
	int i;
	num_atk=0;
	for(i=1;i<=N;i++){
		if(left[i+res[i]-1]>1){
			attack[num_atk]=i;
			num_atk++;
		}			
		else if(right[N+i-res[i]]>1){
			attack[num_atk]=i;
			num_atk++;
		}
	}
}
