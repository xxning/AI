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
FILE *output;
int main(){
	
	FILE *source=fopen("source.txt","r");
	FILE *target=fopen("target.txt","r"); 
	output=fopen("output_Ah1.txt","w");
	if(!source||!target||!output){
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
*/	
	
	Head->next=NULL; 
	int i;
	GN=0;
	clock_t start,finish;  
    double Time;
	start=clock();
	//printf("%ld\n",start);
	while(1){
		if(Judge()==1) break;
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
							X1=X;Y1=Y;Z1=Z;
							Z--;
							h1();		
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
							X1=X;Y1=Y;Z1=Z;
							Z++;
							h1();
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
							X1=X;Y1=Y;Z1=Z;
							Y--;
							h1();
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
							X1=X;Y1=Y;Z1=Z;
							Y++;
							h1();
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
							X1=X;Y1=Y;Z1=Z;
							X--;
							h1();
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
							X1=X;Y1=Y;Z1=Z;
							X++;
							h1();
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
		p=Head->next;
		if(p==NULL){
			printf("Error2!\n");
			exit(1);
		}
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
		//Choice=p->c;
	//	if(p->g==GN){
		//	Move();
		//}
	//	else{
	//		Back();
	//		Move();
	//	}
		//printf("F:%d H:%d C:%d GN:%d\n",p->f,p->h,p->c,GN);
		LastC=p->c;
		Head->next=p->next;
		free(p); 
		p=Head->next;
		/*
		L=0;
		while(p){
			L++;
			p=p->next;
		}
		printf("%d\n",L);
		*/
	} 
	p=Head->next;
	/*
	while(p!=NULL){
		printf("F:%d H:%d C:%d\n",p->f,p->h,p->c);
		p=p->next;
	}
	*/
	finish=clock();
	//printf("%ld\n",finish-start);
	Time=(double)(finish-start)/CLOCKS_PER_SEC;
	//printf("%ld\n",CLOCKS_PER_SEC); 
	printf("Time:%lf\n",Time);
	fprintf(output,"Time:%lf\n",Time);
	PRINT();
	printf("Total step:%d\n",GN);
	fprintf(output,"Total step:%d\n",GN);
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

void h1_intial(){
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
		case 1:if(LastC==2) return; break;
		case 2:if(LastC==1) return; break;
		case 3:if(LastC==4) return; break;
		case 4:if(LastC==3) return; break;
		case 5:if(LastC==6) return; break;
		case 6:if(LastC==5) return; break;
		default:printf("Error!\n");return;break;
		
	}
	
	int x,y,z;
	int i;
	Node *ptr=(Node*)malloc(sizeof(Node));
	ptr->g=GN+1;
	ptr->h=HN;
	ptr->f=GN+HN+1;
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

