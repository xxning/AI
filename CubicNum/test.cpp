#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define FORWARD 5
#define BACK 6

void h1();
void h1_intial();
int Judge();
void PRINT();
void Move();//移动 
void Back();//回溯 
void Insert(int C);

int S[4][4][4];//存放初始状态
int D[4][4][4];//存放目标状态

struct Node{  
	int f;
	int g;
	int h;
	int c;
	int xx;
	int yy;
	int zz;
	int state[4][4][4];
	int sq[128];
	Node *next;
};
int X,Y,Z;
int X1,Y1,Z1;
int Step[128];
int GN;//表示g(n)的值，即开始节点到目前的代价 
int HN,HN1;//表示h(n)的值 
int C[7];
int Choice,LastC,Min,temp;
Node *Head=(Node*)malloc(sizeof(Node));
Node *p=(Node*)malloc(sizeof(Node));
Node *q=(Node*)malloc(sizeof(Node));
int L;
int main(int argc,char *argv[]){
	
	FILE *source=fopen("source.txt","r");
	FILE *target=fopen("target.txt","r"); 
	//FILE *output=fopen("output_Ah1.txt","w");
	if(!source||!target){
		printf("Error:can't open object fiel.\n'");
		exit(1);
	}
	int x,y,z;
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				fscanf(source,"%d",&S[x][y][z]);
				if(S[x][y][z]==0){
					X=x;
					Y=y;
					Z=z;
				}
					 
			}
		}
	}
	//printf("%d %d %d \n",X,Y,Z);
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				fscanf(target,"%d",&D[x][y][z]);
			}
		}
	}
/*	
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				printf("%d ",S[x][y][z]);
			}
		}
	}
*/	FILE *fp=fopen(argv[1],"r");
	if(!fp){
		printf("Error:can't open object fiel.\n'");
		exit(1);
	}
	int i=0;
	char c;
	double s;
	fscanf(fp,"%c",&c);
	while(c!='\n')
		fscanf(fp,"%c",&c);
	fscanf(fp,"%c",&c);
	while(c!='\n'){
		switch(c){
			case 'U':{
				Step[i]=1;
				i++;
				break;
			}
			case 'D':{
				Step[i]=2;
				i++;
				break;
			}
			case 'L':{
				Step[i]=3;
				i++;
				break;
			}
			case 'R':{
				Step[i]=4;
				i++;
				break;
			}
			case 'F':{
				Step[i]=5;
				i++;
				break;
			}
			case 'B':{
				Step[i]=6;
				i++;
				break;
			}
			default:printf("error!\n");break;
		}
		fscanf(fp,"%c",&c);
	}
	int j;
	
    for(j=0;j<i;j++){
    	switch(Step[j]){
    		case 1:{
    			if(S[X][Y][Z-1]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X][Y][Z-1];
					S[X][Y][Z-1]=temp;	
					Z--;				
				}			
    			break;
    		}
    		case 2:{
    			if(S[X][Y][Z+1]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X][Y][Z+1];
					S[X][Y][Z+1]=temp;			
					Z++;
				}
    			break;
    		}
    		case 3:{
    			if(S[X][Y-1][Z]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X][Y-1][Z];
					S[X][Y-1][Z]=temp;			
					Y--;
				}
    			break;
    		}
    		case 4:{
    			if(S[X][Y+1][Z]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X][Y+1][Z];
					S[X][Y+1][Z]=temp;
					Y++;
				}
    			break;
    		}
    		case 5:{
    			if(S[X-1][Y][Z]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X-1][Y][Z];
					S[X-1][Y][Z]=temp;						
					X--;
				}
    			break;
    		}
    		case 6:{
    			if(S[X+1][Y][Z]==-1)
					break;
				else{
					temp=S[X][Y][Z];
					S[X][Y][Z]=S[X+1][Y][Z];
					S[X+1][Y][Z]=temp;
					X++;
				}
    			break;
    		}
    		default:printf("Error!\n");break;
    	}
    }
	
    if(Judge()==1){
    	printf("YES\n");
    }
    else{
    	printf("NO\n");
    }

	//PRINT();
	//printf("%d\n",GN);
	//system("pause"); 
	return 0;
}

int Judge(){//判断是否到达目标状态 
	int x,y,z;
	for(x=1;x<4;x++){
		for(y=1;y<4;y++){
			for(z=1;z<4;z++){
				if(S[x][y][z]==D[x][y][z])
					continue;
				else
					return 0;
			}
		}
	}
	return 1;
}




