#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
//#include<windows.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define FORWARD 5
#define BACK 6
#define INFINITY 10000000

void h1();
int Judge();
void PRINT();
void Move();//移动 
void Back();//回溯 
void Insert(int C);
void newstate();

int S[4][4][4];//存放初始状态
int D[4][4][4];//存放目标状态

int S0[4][4][4];
int D0[4][4][4];
int X0,Y0,Z0;

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
int Step[128];
int limit,next_limit;
int GN;//表示g(n)的值，即开始节点到目前的代价 
int HN;//表示h(n)的值 
int C[7];
int Choice,LastC,Min,temp;
Node *Head=(Node*)malloc(sizeof(Node));
Node *p=(Node*)malloc(sizeof(Node));
Node *q=(Node*)malloc(sizeof(Node));
int L;
FILE *output;
int main(){
	
	FILE *source=fopen("source.txt","r");
	FILE *target=fopen("target.txt","r"); 
	output=fopen("output_IDAh1.txt","w");
	if(!source||!target||!output){
		printf("Error:can't open object fiel.\n'");
		exit(1);
	}
	int x,y,z;
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				fscanf(source,"%d",&S[x][y][z]);
				S0[x][y][z]=S[x][y][z];
				if(S[x][y][z]==0){
					X0=X=x;
					Y0=Y=y;
					Z0=Z=z;
				}
					 
			}
		}
	}
	//printf("%d %d %d \n",X,Y,Z);
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				fscanf(target,"%d",&D[x][y][z]);
				D0[x][y][z]=D[x][y][z];
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
*/	
	
	Head->next=NULL; 
	int i;
	GN=0;
	clock_t start,finish;  
    double Time;
    h1();
    next_limit=INFINITY;
    limit=HN;
    GN=-1;
    Insert(0);//插入初始状态 	
    GN=0; 
    p=Head->next;
	start=clock();
	while(1){
		
		//弹出队首 
		while(p){
			for(x=1;x<4;x++){
				for(y=1;y<4;y++){
					for(z=1;z<4;z++){
						S[x][y][z]=p->state[x][y][z];
					}
				}
			}
			GN=p->g;
			X=p->xx;
			Y=p->yy;
			Z=p->zz;
			for(i=0;i<GN;i++)
				Step[i]=p->sq[i];
			LastC=p->c;
			Head->next=p->next;
			free(p); 		
			if(Judge()==1) {
				finish=clock();
    			Time=(double)(finish-start)/CLOCKS_PER_SEC;
				printf("Time:%lf\n",1000*Time);
				fprintf(output,"Time:%lf\n",1000*Time);
				PRINT();
				printf("Total step:%d\n",GN);
				fprintf(output,"Total step:%d\n",GN);
				return 0;
			}
			else{
				newstate();
			}
			p=Head->next;		
		}
		limit=next_limit;
		next_limit=INFINITY;	
		for(x=1;x<4;x++){
			for(z=1;z<4;z++){
				for(y=1;y<4;y++){
					S[x][y][z]=S0[x][y][z];
				}
			}
		}
		X=X0;
		Y=Y0;
		Z=Z0;
		h1();
		GN=-1;
    	Insert(0);//插入初始状态 	
    	GN=0; 
    	p=Head->next;
	}
	//system("pause"); 
	return 0;
}

void h1(){
	int x,y,z;
	HN=0; 
	for(x=1;x<4;x++){
		for(y=1;y<4;y++){
			for(z=1;z<4;z++){
				if(S[x][y][z]!=D[x][y][z])
					HN++;
			}
		}
	}
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

void newstate(){
	int i;
	for(i=1;i<7;i++)
		C[i]=1;
	if(X==1)
		C[5]=0;
	if(X==3)
		C[6]=0;
	if(Y==1)
		C[3]=0;
	if(Y==3)
		C[4]=0;
	if(Z==1)
		C[1]=0;
	if(Z==3)
		C[2]=0;
	//Min=1000;
	//Choice=0;
	for(i=1;i<7;i++){
		if(C[i]==1){
			switch(i){
				case 1:{
					if(S[X][Y][Z-1]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y][Z-1];
						S[X][Y][Z-1]=temp;
						h1();
						Z--;
						Insert(1);
						Z++;
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y][Z-1];
						S[X][Y][Z-1]=temp;
						break;
					}					
				}
				case 2:{
					if(S[X][Y][Z+1]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y][Z+1];
						S[X][Y][Z+1]=temp;
						h1();
						Z++;
						Insert(2);
						Z--;
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y][Z+1];
						S[X][Y][Z+1]=temp;
						break;
					}										
				}
				case 3:{
					if(S[X][Y-1][Z]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y-1][Z];
						S[X][Y-1][Z]=temp;
						h1();
						Y--;
						Insert(3);
						Y++;
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y-1][Z];
						S[X][Y-1][Z]=temp;
						break;
					}					
				}
				case 4:{
					if(S[X][Y+1][Z]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y+1][Z];
						S[X][Y+1][Z]=temp;
						h1();
						Y++;
						Insert(4);
						Y--;
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X][Y+1][Z];
						S[X][Y+1][Z]=temp;
						break;
					}
				}
				case 5:{
					if(S[X-1][Y][Z]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X-1][Y][Z];
						S[X-1][Y][Z]=temp;
						h1();
						X--;
						Insert(5);
						X++; 
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X-1][Y][Z];
						S[X-1][Y][Z]=temp;
						break;
					}
				}
				case 6:{
					if(S[X+1][Y][Z]==-1)
						break;
					else{
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X+1][Y][Z];
						S[X+1][Y][Z]=temp;
						h1();
						X++;
						Insert(6);
						X--;
						temp=S[X][Y][Z];
						S[X][Y][Z]=S[X+1][Y][Z];
						S[X+1][Y][Z]=temp;
						break;
					}
				}
				default:printf("Error1!\n");break;
			}
		}
	}
}

void PRINT(){
	int i;
	for(i=0;i<GN;i++){
		switch(Step[i]){
			case 1:printf("U");fprintf(output,"U");break;
			case 2:printf("D");fprintf(output,"D");break;	
			case 3:printf("L");fprintf(output,"L");break;	
			case 4:printf("R");fprintf(output,"R");break;
			case 5:printf("F");fprintf(output,"F");break;
			case 6:printf("B");fprintf(output,"B");break;	
			default:printf("\nError3!  %d\n",Step[i]);
		}
	}
	printf("\n");
	fprintf(output,"\n");
}

void Insert(int C){
	
	switch(C){
		case 0:break;
		case 1:if(LastC==2) return; break;
		case 2:if(LastC==1) return; break;
		case 3:if(LastC==4) return; break;
		case 4:if(LastC==3) return; break;
		case 5:if(LastC==6) return; break;
		case 6:if(LastC==5) return; break;
		default:printf("Error!\n");return;break;
		
	}
	
	int F=GN+HN+1;
	if(C==0)
	//printf("F=%d,limt=%d\n",F,limit);
	if(F>limit){	 
		if(F<next_limit)
			next_limit=F;
		return ;	 
	}
	int x,y,z;
	int i;
	Node *ptr=(Node*)malloc(sizeof(Node));
	ptr->g=GN+1;
	ptr->h=HN;
	ptr->f=F;
	ptr->xx=X;
	ptr->yy=Y;
	ptr->zz=Z;
	ptr->c=C;
	for(x=1;x<4;x++){
		for(y=1;y<4;y++){
			for(z=1;z<4;z++){
				ptr->state[x][y][z]=S[x][y][z];
			}
		}
	}
	for(i=0;i<GN;i++){
		ptr->sq[i]=Step[i];		
	}
	if(GN>=0)
		ptr->sq[i]=C;
	
	if(Head->next==NULL){
		Head->next=ptr;
		ptr->next=NULL;
	}
	else{
		p=Head->next;
		q=NULL;
		while((p!=NULL)&&(p->f<ptr->f)){
			q=p;
			p=p->next; 
		}
		if(p==NULL){
				q->next=ptr;
				ptr->next=NULL;
		}
		else if(q==NULL){   
			Head->next=ptr;
			ptr->next=p; 
		}
		else{
			
			q->next=ptr;
			ptr->next=p; 
		}	
	}
}


