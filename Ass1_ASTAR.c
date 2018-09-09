#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Functions.c"
int main(int argc, char** argv) {

    int u=0;
    //If any args
    //printf("\nTRY PRINT ARG");
    while(u<argc){
    //printf("\n ARGV[%d]:%s\n",u,argv[u]);
    u++;
    }
    //argv[5] is env file.... can include or not...
    
    int i1,i2,g1,g2; 
        if(argc>4){
	i1 = atoi(argv[1]);
        i2 = atoi(argv[2]);
   	g1 = atoi(argv[3]);
    	g2 = atoi(argv[4]);
   	}
    //return 0;

    int FileCount = 0;

    while(FileCount<1){
    FILE* S = NULL;
    IsGoal=0;	
    if(argc<5){
    S = fopen("/home/maury/prx_core_ws/src/prx_core/prx/utilities/applications/maze","r");
    }
    else{
    S = fopen(argv[5],"r");
    //printf("\nENV FILE OPENEN:%s",argv[5]);
    //GIVEN ENV
    }
    //return 0;
    if(S==NULL){
    printf("Open Error");
    exit(-1);
    } 
    
    //Q = (Queue_of_Paths*)malloc(sizeof(Queue_of_Paths*));
    //Insert(Qn)... USE Q FOR THE LIST OF File Descriptors!!! [StartR].....

    //CRUCIAL PART, IMPLEMENT IN SCOPE OF FUNC GIVEN... 
    
    char* c = GetNextValue(S);
    Boundr = atoi(c);
    free(c);
    c=NULL; 
    //printf("Rows:%d",Boundr);
    
    char* d = GetNextValue(S);
    Boundc = atoi(d);
    free(d);
    d = NULL;
    //printf("Columns:%d\n\n",Boundr); 

    //CHECK VALUES FOR BOARD     
    if(Boundc<=0||Boundr<=0){

    printf("\nError, BOUNDC or BOUNDR Data Lost");

    return -1;

    }
    //printf("\nBOUNDC:%d\nBOUNDR:%d\n",Boundc,Boundr);
    ////////////////////////////

    //Important if want to always find current player position and keep track of goal node in the space!!!!!!!
    char** _BOARD_=(char**)malloc(Boundr*sizeof(char*));
    int i=0;
    while(i<Boundr){
   _BOARD_[i]=(char*)malloc(Boundc*sizeof(char));
    i++;
    }
    
    //Malloc the space once given the coordinate
    SetUpBoard(S,_BOARD_);
  
    //return 0; 
    //PrintBoard(_BOARD_);
  
    GetDensity(_BOARD_);

    //printf("\n DENSITY: %lf",Density);

    char* C = NULL;

    if(argc>4){
    _BOARD_[i1][i2] = 'X';
    _BOARD_[g1][g2]='.';

    InsertStart(i1);
    InsertStart(i2);
    
    //G2-1 because need to be left of the goal position!!!!
    C = Path(i1,i2,g1,g2,NULL,_BOARD_);

    }
    else{
    _BOARD_[35][1] = '.';
    _BOARD_[1][35]='X';
   
    InsertStart(1);
    InsertStart(35);
    
    C = Path(1,35,35,1,NULL,_BOARD_);
    PrintBoard(_BOARD_);
    }

    if(C==NULL){
    if(IsGoal==1){
    //printf("\nGoal Found, but no Path Required\n");
    }
    else{
    //printf("\nNo Path Found\n"); 
    }
    }
    else{
    //printf("\n\nCOMPLETE AND OPTIMAL PATH FOUND: %s \n\n",C);
    //printf("\nGood\n");
    printf("%s\n",C);
    }
   
    //int* I = SequenceGen(AllStarts[ASize-2],AllStarts[ASize-1],C); 
  
    //printf("\nVector Seq first node: [%d,%d]\n",I[0],I[1]);

    if(remove("OUT.txt")<0){
    perror("file");
    //exit(-1);
    }
    
    FILE* New = fopen("OUT.txt","ab+");
    if(New==NULL){
    perror("OUT");
    exit(-1);
    }
    if(C!=NULL){
    fwrite(C,sizeof(char),strlen(C),New);
    }
/*
    if(New!=NULL){

    //int u=0;
    //while(u<ISize){
    printf("ISIZE:%d\n",ISize);
    //fwrite(I,1,ISize,New);
    //char B[ISize];
    char str[1000];
    bzero(str,1000);
    //str[1]='\0';
    int q=0;
    while(q<ISize){
    sprintf(str,"%d",I[q]);
    char*Bb=str;
    q++;
    //}
    fwrite(Bb,sizeof(char),strlen(Bb),New);
    fwrite(" ",sizeof(char),1,New);
    }
    }
    else{

    printf("\nCREATE FILE FAILED!\n");

    exit(-2);
    }

    //}    
    if(I!=NULL){
    free(I);
    I=NULL;
    }

 */
    ISize=0;
    
    //Delete ENV
    //DeleteBoard(_BOARD_);   
    //Close File
    fclose(S);
    //
    //return 0;
    FileCount++;
    //if(FileCount==10){
    DeleteBoard(_BOARD_);
    //}
    fclose(New);
    }
    //Free All Queues if created
    Free();
    //Free All FrontierList
    DeleteL();
    //Close File 
    //fclose(S);

    DeleteStarts();

    return 0;
}
