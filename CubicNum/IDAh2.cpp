#include<stdio.h>
#include<stdlib.h>
#include<time.h> 
//#include<windows.h>
#include<queue>
#include<vector>
#include<functional>
#include<math.h>

using namespace std;

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define FORWARD 5
#define BACK 6
#define INFINITY_ 100000000
void h2();
short Judge();
void PRshort();
void Move();//移动 
void Back();//回溯 
void Insert(short C);
void h2_initial();
void newstate();

short S[4][4][4];//存放初始状态
short D[4][4][4];//存放目标状态

short S0[4][4][4];
short D0[4][4][4];
short X0,Y0,Z0;
struct Node{  
	short f;
	short g;
	short h;
	short c;
	short xx;
	short yy;
	short zz;
	short state[4][4][4];
	short sq[128];
	friend bool operator< (Node n1, Node n2){  
        return n1.f > n2.f;  
    } 
	Node *next;
};
/*
struct cmp{
	bool operator()(Node *a,Node *b){
		return a->f<b->f;
	}
};
*/
short X,Y,Z;
short X1,Y1,Z1;
int limit,next_limit;
short Step[128];
short GN;//表示g(n)的值，即开始节点到目前的代价 
short HN,HN1;//表示h(n)的值 
short C[7];
short Choice,LastC,Min,temp;
//Node *Head=(Node*)malloc(sizeof(Node));
Node p;
Node q;
priority_queue<Node>Que;//最小值优先
FILE *output;
int main(){
	
	FILE *source=fopen("source.txt","r");
	FILE *target=fopen("target.txt","r"); 
	output=fopen("output_IDAh2.txt","w");
	if(!source||!target||!output){
		printf("Error:can't open object fiel.\n'");
		exit(1);
	}
	
	short x,y,z;
	for(x=1;x<4;x++){
		for(z=1;z<4;z++){
			for(y=1;y<4;y++){
				fscanf(source,"%hd",&S[x][y][z]);
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
				fscanf(target,"%hd",&D[x][y][z]);
				D0[x][y][z]=D[x][y][z];
			}
		}
	}

	short i;
	GN=0;
	clock_t start,finish;    
    double Time;
    start=clock();
    h2_initial();
    limit=HN;
    //limit=INFINITY;
	GN=-1;
	next_limit=INFINITY_;
	HN1=HN;
    Insert(0);//插入初始状态 	
    GN=0; 
	while(1){
		while(Que.size()!=0){
			for(x=1;x<4;x++){
				for(y=1;y<4;y++){
					for(z=1;z<4;z++){
						S[x][y][z]=Que.top().state[x][y][z];
					}
				}
			}
			GN=Que.top().g;
			X=Que.top().xx;
			Y=Que.top().yy;
			Z=Que.top().zz;
			for(i=0;i<GN;i++)
				Step[i]=Que.top().sq[i];
		
			LastC=Que.top().c;
			HN=Que.top().h;//printf("%d\n",HN);
			Que.pop();	
			if(Judge()==1) {
				finish=clock();
    			Time=(double)(finish-start)/CLOCKS_PER_SEC;
    			printf("Time:%lf\n",Time);
				fprintf(output,"Time:%lf\n",Time);
				PRshort();
				printf("Total step:%d\n",GN);
				fprintf(output,"Total step:%d\n",GN);
			
				return 0;
			}
			else{
				newstate();
			}
			
		}
		limit=next_limit;
		next_limit=INFINITY_;
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
		h2_initial();
		GN=-1;
		HN1=HN;
    	Insert(0);//插入初始状态 	
    	GN=0; 
	
	}

	system("pause"); 
	return 0;
}

void h2(){
	
	short x,y,z;
	for(x=1;x<4;x++){
		for(y=1;y<4;y++){
			for(z=1;z<4;z++){
				if(S[X1][Y1][Z1]==D[x][y][z]){
					HN1=HN-abs(X-x)-abs(Y-y)-abs(Z-z);
					HN1=HN1+abs(X1-x)+abs(Y1-y)+abs(Z1-z);
					//printf("%d\n",HN1);
					return;	
				}		
			}
		}
	}
	

}

void h2_initial(){
	HN=0;
	short x1,x2,y1,y2,z1,z2;
	for(x1=1;x1<4;x1++){
		for(y1=1;y1<4;y1++){
			for(z1=1;z1<4;z1++){
				if(x1==X&&y1==Y&&z1==Z)
					continue;
				if(S[x1][y1][z1]==-1)
					continue;
				for(x2=1;x2<4;x2++){
					for(y2=1;y2<4;y2++){
						for(z2=1;z2<4;z2++){
							if(S[x1][y1][z1]==D[x2][y2][z2])
								HN=HN+abs(x1-x2)+abs(y1-y2)+abs(z1-z2);
						}
					}
				}
			}
		}
	}
}

short Judge(){//判断是否到达目标状态 
	short x,y,z;
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
	
	short i;
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
						h2();
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
						h2();							
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
						h2();
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
						h2();
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
						h2();
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
						h2();
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

void PRshort(){
	short i;
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

void Insert(short C){
	
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
	short F=GN+HN1+1;
	if(F>limit){		
		if(F<next_limit)
			next_limit=F;
		return ;	 
	}
	/*
	if(Que.size()!=0){
		if((GN+HN1)>(Que.top().f+1))
			return;
	}
	*/
	//if(s>s1) return;
	short x,y,z;
	short i;
	Node ptr;
	ptr.g=GN+1;
	ptr.h=HN1;
	ptr.f=F;
	ptr.xx=X;
	ptr.yy=Y;
	ptr.zz=Z;
	ptr.c=C;
	for(x=1;x<4;x++){
		for(y=1;y<4;y++){
			for(z=1;z<4;z++){
				ptr.state[x][y][z]=S[x][y][z];
			}
		}
	}
	for(i=0;i<GN;i++){
		ptr.sq[i]=Step[i];		
	}
	ptr.sq[i]=C;
	
	Que.push(ptr);
}

	
