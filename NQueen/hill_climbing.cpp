#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

void forward(int row,int i0,int i1);
void backward(int row,int i0,int i1);
void judge();
void output();
void restart();
void compute();
void hill_climbing();
void test();

int N;	//皇后规模 
int X,Y; //障碍位置 

//int *row; //记录行冲突 
int *col; //记录列冲突 
int *left;//坐斜线冲突 
int *right ;//右斜线冲突 

int *res;
//int **state;

int next_i,next_j;
clock_t start,finish;
double Time;
int min;
int flag;
FILE *input;
FILE *result;
int *attack;
int num_atk;
int count=0;
int main(){
	
	input=fopen("input.txt","r");
	result=fopen("output_hill_climbing.txt","w");
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
	col=(int*)malloc((N+1)*sizeof(int)); 
	res=(int*)malloc((N+1)*sizeof(int));
	attack=(int*)malloc((N+1)*sizeof(int));
	for(i=0;i<N+1;i++){
		res[i]=attack[i]=col[i]=0;
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
	//judge();//printf("%d\n",flag);
	restart();//return 0; 
	//compute();	//计算冲突
	start=clock();//printf("%ld\n",start);
	hill_climbing();
	finish=clock();//printf("%ld\n",finish);
	
	Time=(double)(finish-start)/CLOCKS_PER_SEC;
	output();
	fprintf(result,"%lf\n",Time);
	//printf("%lf\n",Time);
	//judge();
	//test();
	//printf("flag:%d\n",flag);
	//printf("%d\n",count);
	//system("pause");
	fclose(input);
	fclose(result);
	/*
	for(i=1;i<=N;i++){
		for(j=1;j<=N;j++){
			if(j==res[i]){
				printf("X ");
			}
			else
				printf("* ");
		}
		printf("\n");
	}
	*/
	return 0;
}
//O(nlgn)~O(n^2) 
void hill_climbing(){
	
	int i,j,k,l,m;
	int temp;
	double q;
	while(1){
		compute();	//计算冲突
		judge();	//判断当前状态
		min=flag;
		while(flag==0){	
			if(res[X]!=Y)		
				return;
			else{
				//printf("zz\n");
				restart();
				compute();
				min=flag;
			}
		}
		for(i=1;i<N;i++){
			//printf("atk:%d i:%d\n",num_atk,i);
			//fprintf(result,"atk:%d\n",num_atk);
			for(j=0;j<num_atk;j++){
				for(m=1;m<20;m++){
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
							//printf("yy\n");
							restart();
							min=flag;
							j=N+1;
							m=20;
							continue;
						}
						
					}
					else if(flag<min){
						
						min=flag;
						temp=res[l];
						res[l]=res[k];
						res[k]=temp;
						break;
					}
					else{
						backward(l,res[k],res[l]);
						backward(k,res[l],res[k]);
					}
				}
			}
			compute();
		}			
		restart();
		//compute();	//计算冲突
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
//O(n)
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
	//double q;
	for(i=1;i<=N;i++){
		j=rand()%N;
		j++; 
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
//O(n)
void test(){
	
	int i,j,l,r;
	flag=0;
	for(i=0;i<N+1;i++){
		col[i]=0;
	}
	for(i=0;i<2*N;i++){
		left[i]=right[i]=0;
	}
	for(i=1;i<=N;i++){
		j=res[i];
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
}
