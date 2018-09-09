#include "Header.h"


int GET(char* F, char* H){
    
    if(F[GCOUNTER]!='\0'){
    
    H[0] = F[GCOUNTER];
        
    GCOUNTER=GCOUNTER+1;
    
        return 1;
        
    }
    else{
        
        return 0;
        
    }
}

char* GetNextValue(FILE* File){

int pos = 0;    
    
char op = ' ';  
  
char* cpy; 
cpy = (char*)malloc(2*sizeof(char));    

bzero(cpy,2);

cpy[0]='1';  
 
//int SIZE = fseek(File,0,SEEK_END);
 
while(fscanf(File,"%c",&op)!=EOF){
    //printf("%c",op); 
    
    if(op=='\n'){
        //Found space to next information
        //printf("\nExit Read \n");
        
	//fscanf(File,"%c",&op);
        
	break;   
    }
    
    else{
        
    cpy[pos]=op;
    
    cpy = (char*)realloc(cpy,(pos+2)*sizeof(char));    
         
    if (cpy==NULL){
        
        printf("MEM ERROR, EXITING");
        
        exit(0);
    }
    else{
            
        cpy[pos+1] = '\0';    
   
    }
        
    pos++;
 
    }
    
}   
    
    
    return cpy;
}

int STRLEN(char* s){
int Length = 0;    
    
    char t = *s;
    
    while(t!='\0'){
        Length=Length+1;
        t = (*s+Length);
    }
    
    
return Length;
}

void SetUpBoard(FILE* File, char ** _2DBOARD_){
    
//int pos = 0;    

int row = 0;
    
int column = 0;
    
char op = ' '; 
//char* cpy = malloc(sizeof(char));    
//bzero(cpy,1);
    
//TEST
/*
while(read(File,op,1)!=0){
    
    if(*op=='\n'){
        break;
    }
    
}  
 
printf("\n"); 
//_2DBOARD_[0][Boundc-1]='%';
*/
  
/////////////////IMPORTANT!!! P AND . ARE EXCLUSIVE CHARS!! USED TO INDICATE THE STARTING POSITION P AND GOAL POSITION . !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1

while(fscanf(File,"%c",&op)!=EOF){
    //printf("%c",*op);     
    if(op=='\n'){
        //Found next row
        if(row>Boundr)
	return;
	row = row+1;
        column = 0;
        //printf("\n");
    }
    ////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////READ INCLUDING EXCLUSIVE CHARS P and .///////////////////////////////////////////////////////////////////
    else if(op=='0'||op=='1'||op=='P'||op=='.'){
     if(column<Boundc&&row<Boundr){
     _2DBOARD_[row][column]=op;
     //printf("%c",_2DBOARD_[row][column]);
     }  
     column = column+1;
    }
    
}   
    
    return;
}

void PrintBoard(char ** _2DBOARD_){
    int row = 0;
    int column = 0;
    
    //printf("\n 2D BOARD \n");
    
    while(row<Boundr){
        column = 0;
        while(column<Boundc){
            printf("%c ",_2DBOARD_[row][column]);
            column = column+1;
        }
            row = row+1;
            printf("\n");
    }
    
    
    return;
}

void ResetBoard(char ** _2DBOARD_){
int row = 0;
    int column = 0;

    //printf("\n RESET 2D BOARD TO UNVISITED \n");

    while(row<Boundr){
        column = 0;
        while(column<Boundc){
            //printf("%c ",_2DBOARD_[row][column]);
            if(_2DBOARD_[row][column]=='X'){
	    _2DBOARD_[row][column]='1';
 	    }
	    column = column+1;
        }
            row = row+1;
            //printf("\n");
    }

 //PrintBoard(_2DBOARD_);
return;
}
void DeleteBoard(char** _2DBOARD_){
    
    int i=0;
    
    while(i<Boundr){
    //_BOARD_[i]=(char*)malloc(Boundc*sizeof(char));
    free((char*)_2DBOARD_[i]);
    _2DBOARD_[i]=NULL;
    i++;
    }
    
    free((char**)_2DBOARD_);

    return;
}

void Insert(Queue_of_Paths * Q1){

if(Q==NULL&&Q1!=NULL){
/*Q = (Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));
Q->StartR = Q1->StartR;
Q->StartC = Q1->StartC;
Q->EndR = Q1->EndR;
Q->EndC = Q1->EndC;
Q->ListN = Q1->ListN;
*/
Q=Q1;
Q->Next=NULL;
//printf("\nFIRST ENTRY\n");
return;
}

if(Q1==NULL){
//printf("\nNULL ENTRY\n");
return;
}

Queue_of_Paths*Q2 =Q;//(Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));

//Q2 = Q;

while(Q2!=NULL){

if(Q2->Next==NULL){
//printf("\nAPPEND ENTRY:[%d,%d] , %s\n",Q1->StartR,Q1->StartC,Q1->ListN);
/*
Q2->Next=(Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));
Q2->Next->StartR = Q1->StartR;
Q2->Next->StartC = Q1->StartC;
Q2->Next->EndR = Q1->EndR;
Q2->Next->EndC = Q1->EndC;
Q2->Next->ListN = Q1->ListN;
*/
Q2->Next=Q1;
Q2->Next->Next=NULL;
return;
}


Queue_of_Paths* Q3 = Q2->Next;

Q2 = Q3;
}

return;

}
void PrintQueue(){

if(Q==NULL){
printf("\n-----START-QUEUE-----");
printf("\nNULL\n");
printf("-----END-QUEUE-----\n");
return;
}

Queue_of_Paths* Q1 = Q;

int i=0;

printf("\n-----START-QUEUE-----");

while(Q1!=NULL){
printf("\n%d:",i);
printf("Start Row:%d\nStart Column:%d\n",Q1->StartR,Q1->StartC);
//printf("Goal Row:%d\nGoal Column:%d\n",Q1->EndR,Q1->EndC);
if(Q1->ListN!=NULL){
printf("SEQ:%s (SIZE:%d) \n",Q1->ListN,(int)strlen(Q1->ListN));
}
printf("\nHeuristic (Manhattan+Complete): %d\n",Q1->H1_H2_G);
Queue_of_Paths* Q2 = Q1->Next;

Q1 = Q2;
i++;
}
if(Q1==NULL){
//printf("\n-----START-QUEUE-----");
printf("\nNULL\n");
//printf("-----END-QUEUE-----\n");
//return;
}


printf("-----END-QUEUE-----\n");


return;
}


void Free(){
if(Q==NULL){
return;
}
Queue_of_Paths* Q1;
// = Q->Next;
while(Q!=NULL){
Q1=Q->Next;

if(Q->ListN!=NULL){
free(Q->ListN);
Q->ListN=NULL;
}

free(Q);
Q=NULL;
Q=Q1;

}
return;
}

void Delete(Queue_of_Paths * Q1){

if(Q==NULL){
return;
}
if(Q1==NULL){
return;
}

printf("\n\nDELETING SEQ:%s\n\n",Q1->ListN==NULL ? "NULL":Q1->ListN);

Queue_of_Paths*Q2 = Q;

//Delete First Node
if(Q1->ListN!=NULL&&Q2->ListN!=NULL){
if(strcmp(Q1->ListN,Q2->ListN)==0&&Q1->StartR==Q2->StartR&&Q1->StartC==Q2->StartC/*&&Q1->EndR==Q2->EndR&&Q1->EndC==Q2->EndC*/){

//printf("\nFOUND SAME PATH SEQS [FIRST DELETE] (((INCLUDING FROM SAME POSITION)))\n");

Queue_of_Paths* Q4 = Q2->Next;

if(Q2->ListN!=NULL)
free(Q2->ListN);
Q2->ListN=NULL;

free(Q2);
Q2=NULL;

Q = Q4;

PrintQueue();

return;
}
}
else{
if(Q1->ListN==NULL&&Q2->ListN==NULL&&Q1->StartR==Q2->StartR&&Q1->StartC==Q2->StartC/*&&Q1->EndR==Q2->EndR&&Q1->EndC==Q2->EndC*/){

//printf("\nPATH SEQ ARE NULLLLL\n");

Queue_of_Paths* Q4 = Q2->Next;

free(Q2);
Q2=NULL;

Q = Q4;

PrintQueue();

return;
}
}

while(Q2!=NULL){

if(Q2->Next!=NULL){
if(Q2->Next->ListN!=NULL&&Q1->ListN!=NULL){
if(strcmp(Q1->ListN,Q2->Next->ListN)==0&&Q1->StartR==Q2->Next->StartR&&Q1->StartC==Q2->Next->StartC/*&&Q1->EndR==Q2->Next->EndR&&Q1->EndC==Q2->Next->EndC*/){
//printf("\nFOUND SAME PATH SEQS [DELETE] (((INCLUDING FROM SAME POSITION)))\n");
//
Queue_of_Paths* Q4 = Q2->Next->Next;


if(Q2->Next->ListN!=NULL)
free(Q2->Next->ListN);
Q2->Next->ListN=NULL;

free(Q2->Next);
Q2->Next=NULL;

Q2->Next = Q4;
//

PrintQueue();

return;
//
}
}
else{

if(Q2->Next->ListN==NULL&&Q1->ListN==NULL&&Q1->StartR==Q2->Next->StartR&&Q1->StartC==Q2->Next->StartC/*&&Q1->EndR==Q2->Next->EndR&&Q1->EndC==Q2->Next->EndC*/){
//printf("\nPATH SEQ ARE NULLLLL, CONTINUEEEEE\n");
//return;

Queue_of_Paths* Q4 = Q2->Next->Next;

free(Q2->Next);
Q2->Next=NULL;

Q2->Next = Q4;

PrintQueue();

}
}
}
//
Queue_of_Paths* Q3 = Q2->Next;
Q2 = Q3;
}

//
//return (Queue_of_Paths*)NULL;
return;
}

int ManhattanHeuristic(int r1, int c1, int r2, int c2){

/*
double R = abs(r2-r1);
double C = abs((c2-c1));
return (int)((R+C)+Density);
*/

return (int)ceil((sqrt((double)((r2-r1)*(r2-r1))+(double)((c2-c1)*(c2-c1))))*(Density*10));

}

//Insert NewQ
void InsertQ(Queue_of_Paths * Q, Queue_of_Paths* NewQ){

//printf("\n INSERT Q!!!!!!!!!!!!\n");

if(NewQ==NULL){
NewQ = Q;
return;
}

Queue_of_Paths * Q2 = NewQ;

while(Q2->Next!=NULL){
Queue_of_Paths*Q3=Q2->Next;
Q2=Q3;
}

Q2->Next=Q;

return;
}

//Given A List* to insert
void InsertL(FrontierList* LL){

if(L==NULL){
L = LL;
return;
}

FrontierList* L2 = L;

while(L2->Next!=NULL){
FrontierList* L3 = L2->Next;
L2=L3;
}

L2->Next=LL;

return;
}

void Sort(Queue_of_Paths * Q){
Queue_of_Paths * Q1 = Q;
if(Q1==NULL){

//printf("\n\n\n\n\nNULL POINTER\n");
}
while(Q1!=NULL){
Queue_of_Paths* Q2 = Q1->Next;
while(Q2!=NULL){
if(Q1->H1_H2_G>Q2->H1_H2_G){
//Switch
int R = Q1->StartR;
int C = Q1->StartC;
int F = Q1->H1_H2_G;
char* s =(char*) malloc((strlen(Q1->ListN)+1)*sizeof(char));

strncpy(s,Q1->ListN,strlen(Q1->ListN));

s[strlen(Q1->ListN)]='\0';

char* s2 =(char*) malloc((strlen(Q2->ListN)+1)*sizeof(char));

strncpy(s2,Q2->ListN,strlen(Q2->ListN));

s2[strlen(Q2->ListN)]='\0';


//printf("\nSTORE SWAP S:%s WITH: %s\n",s,s2);

Q1->StartR = Q2->StartR;
Q1->StartC = Q2->StartC;
Q1->H1_H2_G = Q2->H1_H2_G;
free(Q1->ListN);
Q1->ListN=NULL;
Q1->ListN = s2;


Q2->StartR = R;
Q2->StartC = C;
Q2->H1_H2_G = F;
//Q2->ListN = s;
free(Q2->ListN);
Q2->ListN = NULL;
Q2->ListN = s;

}
Queue_of_Paths * Q4 = Q2->Next;
Q2 = Q4;
}
Queue_of_Paths* Q3 = Q1->Next;
Q1 = Q3;
}


return;
}


void AdjacentCheck(char* App, int* Startr, int* Startc, int Endr, int Endc){
//Have Frontier List
if(App==NULL){
//First Node NULL
return;
}

char* MinSeq = App;
int AdjCount = 0;

//int V = strlen(App)+Value(Startr,Startc,Endr,Endc);

FrontierList* LL = L;

while(LL!=NULL){
AdjCount = 0;
Queue_of_Paths * QQ = LL->NewQ;
while(QQ!=NULL && AdjCount<3){
//IF La
//Return Pointer to Adjacent Var to given StartN, If Exists!
Queue_of_Paths * E = Exists(*Startr,*Startc,App[strlen(App)-1]);
//Iterate through each of these... E's

if(E!=NULL){
//Found Adjacent path, now determine min
Queue_of_Paths* Q3 = E;
while(Q3!=NULL){

int V = strlen(App)+Value(*Startr,*Startc,Endr,Endc);

if(V>E->H1_H2_G/*strlen(MinSeq)>strlen(E->ListN)*/){
//Set New Min
MinSeq = E->ListN;

*Startr = E->StartR;
*Startc = E->StartC;

}

Queue_of_Paths* Q4 = Q3->Next;
Q3 = Q4;
}

}

else{
//No Adjacent Paths found...
}

Queue_of_Paths* Q2 = QQ->Next;
QQ=Q2;
AdjCount = AdjCount+1;
}
FrontierList * L2 = LL->Next;
LL=L2;
}

//POINTER CHANGED
if(strcmp(MinSeq,App)!=0){
App=MinSeq;
}
//POINTER CHANGED
return;
}

//Check ALL LIST, QUEUE if another path exists neighbor
Queue_of_Paths* Exists(int R, int C, char LastDir){
FrontierList * LL = L;

//printf("\n  CHAR GIVEN: %c\n",LastDir);


while(LL!=NULL){
Queue_of_Paths*QQ = LL->NewQ;
while(QQ!=NULL){
//Don't Check R+1!!!!!!!!!!!
if(LastDir=='u'){
if((QQ->StartR==R && QQ->StartC == C+1)||(QQ->StartR==R-1 && QQ->StartC == C)||(QQ->StartR==R && QQ->StartC == C-1)){
//Found Some Adjacency, Check if both started at same start? If yes, return QQ if no, connect start to its start

return QQ;
}
}
//Dont Check C-1!!!!!!11
else if(LastDir=='r'){
if((QQ->StartR==R+1 && QQ->StartC == C)||(QQ->StartR==R && QQ->StartC == C+1)||(QQ->StartR==R-1 && QQ->StartC == C)){
//Found Some Adjacency
return QQ;
}
}
//Don't check R-1!!!!!!!!!!!
else if(LastDir=='d'){
if((QQ->StartR==R+1 && QQ->StartC == C)||(QQ->StartR==R && QQ->StartC == C+1)||(QQ->StartR==R && QQ->StartC == C-1)){
////Found Some Adjacency
return QQ;
}
}
//Don't Check C+1!!!!!!!!!!!
else if(LastDir=='l'){
if((QQ->StartR==R+1 && QQ->StartC == C)||(QQ->StartR==R-1 && QQ->StartC == C)||(QQ->StartR==R && QQ->StartC == C-1)){
////Found Some Adjacency
return QQ;
}
}
//FAILURE OF INPUT!!!! SHOOULD NEVER HAPPEN
else{
printf("\n INVALID CHAR: %c ,EXITING",LastDir);

exit(-1);
}

Queue_of_Paths * Q2 = QQ->Next;
QQ=Q2;
}
FrontierList * L2 = LL->Next;
LL = L2;
}

return NULL;
}


Queue_of_Paths* Evaluate(char* App, int Startr, int Startc, int Endr, int Endc, char ** ENV){

Queue_of_Paths * NewQ = NULL;

bool FirstNull = false;

//InsertQ(Q,NewQ)

//printf("\n EVALUATE: [%d][%d]\n",Startr-1,Startc);

if(Startr>0){
if(ENV[Startr-1][Startc]!='0'){
if(ENV[Startr-1][Startc]!='X'){

//printf("\n EVALUATE: [%d][%d]\n",Startr-1,Startc);


Queue_of_Paths * QQ =(Queue_of_Paths*) malloc(sizeof(Queue_of_Paths));

if(App==NULL){
App=(char*)malloc(sizeof(char));
App[0]='\0';
FirstNull = true;

}

char* App2 = (char*)malloc((strlen(App)+2)*sizeof(char));

strncpy(App2,App,strlen(App));
App2[strlen(App)+1]='\0';
App2[strlen(App)]='u';

//free(App);
//App=NULL;

//printf("\n NEW PATH: %s",App2);

QQ->ListN = App2;
QQ->StartR = Startr-1;
QQ->StartC = Startc;
//QQ->EndR = Endr;
//QQ->EndC = Endc;
QQ->H1_H2_G = strlen(App2)+Value(QQ->StartR,QQ->StartC,Endr,Endc);
QQ->Next=NULL;

//InsertQ(QQ,NewQ);

if(NewQ==NULL)
NewQ = QQ;
else
InsertQ(QQ,NewQ);

//NewQ->Next=NULL;

}
}
}

//return NULL;

if(Startr<Boundr-1){
if(ENV[Startr+1][Startc]!='0'){
if(ENV[Startr+1][Startc]!='X'){

//printf("\n EVALUATE: [%d][%d]\n",Startr+1,Startc);

Queue_of_Paths * QQ = (Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));

if(App==NULL){
App=(char*)malloc(sizeof(char));
//App[0]='d';
App[0]='\0';
FirstNull = true;
}


//char App2[strlen(App)+2];

char* App2 = (char*)malloc((strlen(App)+2)*sizeof(char));


strncpy(App2,App,strlen(App));
App2[strlen(App)+1]='\0';
App2[strlen(App)]='d';


//free(App);
//App=NULL;


//printf("\n NEW PATH: %s",App2);


QQ->ListN = App2;
QQ->StartR = Startr+1;
QQ->StartC = Startc;
//QQ->EndR = Endr;
//QQ->EndC = Endc;
QQ->H1_H2_G = strlen(App2)+Value(QQ->StartR,QQ->StartC,Endr,Endc);
QQ->Next=NULL;


if(NewQ==NULL)
NewQ = QQ;
else
InsertQ(QQ,NewQ);


}
}
}

if(Startc>0){
if(ENV[Startr][Startc-1]!='0'){
if(ENV[Startr][Startc-1]!='X'){

//printf("\n EVALUATE: [%d][%d]\n",Startr,Startc-1);

Queue_of_Paths * QQ = (Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));

if(App==NULL){
//N=true;
App=(char*)malloc(sizeof(char));
//App[0]='l';
App[0]='\0';
FirstNull = true;
}

//char App2[strlen(App)+2];

char* App2 = (char*)malloc((strlen(App)+2)*sizeof(char));


strncpy(App2,App,strlen(App));
App2[strlen(App)+1]='\0';
App2[strlen(App)]='l';

//free(App);
//App=NULL;

//printf("\n NEW PATH: %s",App2);


QQ->ListN = App2;
QQ->StartR = Startr;
QQ->StartC = Startc-1;
//QQ->EndR = Endr;
//QQ->EndC = Endc;
QQ->H1_H2_G = strlen(App2)+Value(QQ->StartR,QQ->StartC,Endr,Endc);
QQ->Next=NULL;


if(NewQ==NULL)
NewQ = QQ;
else
InsertQ(QQ,NewQ);

}
}
}

if(Startc<Boundc-1){
if(ENV[Startr][Startc+1]!='0'){
if(ENV[Startr][Startc+1]!='X'){

//printf("\n EVALUATE: [%d][%d]\n",Startr-1,Startc+1);

Queue_of_Paths * QQ = (Queue_of_Paths*)malloc(sizeof(Queue_of_Paths));

if(App==NULL){
App=(char*)malloc(sizeof(char));
//App[0]='r';
App[0]='\0';
FirstNull = true;
}

//char App2[strlen(App)+2];

char* App2 = (char*)malloc((strlen(App)+2)*sizeof(char));

strncpy(App2,App,strlen(App));
App2[strlen(App)+1]='\0';
App2[strlen(App)]='r';

//free(App);
//App=NULL;

//printf("\n NEW PATH: %s",App2);

QQ->ListN = App2;
QQ->StartR = Startr;
QQ->StartC = Startc+1;
//QQ->EndR = Endr;
//QQ->EndC = Endc;
QQ->H1_H2_G = strlen(App2)+Value(QQ->StartR,QQ->StartC,Endr,Endc);
QQ->Next=NULL;

if(NewQ==NULL)
NewQ = QQ;
else
InsertQ(QQ,NewQ);

}
}
}

/*
if(NewQ!=NULL){
printf("\n NEW Q BEFORE SORT:%d \n",NewQ->H1_H2_G);
}

printf("\nSORT Q\n");
*/
//return NewQ;

Sort(NewQ);

/*
if(NewQ!=NULL){
printf("\n FIRST NODE:%d\n\n", NewQ->H1_H2_G);
}
*/
FrontierList * LL = (FrontierList*)malloc(sizeof(FrontierList));

LL->NewQ = NewQ;
LL->Next=NULL;

InsertL(LL);

if(FirstNull==true){
free(App);
App=NULL;
}
return NewQ;

}


int Value(int StartR, int StartC, int EndR, int EndC){

int F =  (int)floor(ManhattanHeuristic(StartR, StartC, EndR, EndC));//*Density);

return F;

}

void GetDensity(char** ENV){
int i=0;
int j=0;

double CountBlocks = 0.0;
double Total = 0.0;


while(i<Boundr){
j=0;
while(j<Boundc){
if(ENV[i][j]=='0'){
CountBlocks++;
}
Total++;
j++;
}
i++;
}

Density = (CountBlocks)/(Total);

if(Density<=0||Density>=1){
printf("\n ERROR, DENSITY INVALID\n");
exit(-1);
}

return;
}

char* Path(int StartR, int StartC, int EndR, int EndC, char* App, char** ENV){
if(StartR<0||StartR>Boundr||StartC<0||StartC>Boundc){
return NULL;
}

if(StartR==EndR && StartC==EndC){
//GOAL FOUND
//eturn App;
/*
if(ASize%2==0){
if(StartR==AllStarts[ASize-2]&&StartC==AllStarts[ASize-1]){
//GOAL IS WHERE YOU STARTED NOW
IsGoal=1;
return App;
}
else{
//IsGoal=1;
return App;
}
}
else{
//printf("\n Error, NOt valid Vector Space\n");
return NULL;
}
*/
return App;
}

//VOID FUNC...

//return NULL;

AdjacentCheck(App, &StartR, &StartC, EndR, EndC);

//return NULL;

Queue_of_Paths * QQ = Evaluate(App,StartR,StartC,EndR,EndC,ENV);


/*
Queue_of_Paths * QQ2 = QQ;


printf("\n PRINT LIST \n");
while(QQ2!=NULL){

printf("\n STARTr:%d STARTc: %d VALUE: %d 	SEQ:%s\n",QQ2->StartR,QQ2->StartC,QQ2->H1_H2_G, QQ2->ListN);

Queue_of_Paths * QQ3 = QQ2->Next;
QQ2=QQ3;
}
*/
//PrintBoard(ENV);

if(QQ==NULL){
//Nowhere to expand
return NULL;
}

//FrontierList* LL = L;

int Tries = 0;

//while(LL!=NULL){
Queue_of_Paths * Q2 = QQ;//LL->NewQ;
while(Q2!=NULL){

//printf("\n NEXT Q: %d\n",Q2->H1_H2_G);

if(ENV[Q2->StartR][Q2->StartC]!='X'){
//Not Already visited, good to go
//NOW VISIT it
ENV[Q2->StartR][Q2->StartC]='X';

char* P = Path(Q2->StartR,Q2->StartC,EndR,EndC,Q2->ListN,ENV);
if(P==NULL){
//DEAD END
//break;
Tries++;
if(Tries>=4){
//Tried Within current frontier.. Leave loop
return NULL;
}
}
else{
//RETURN SUCCESSOR
return P;
}

//break;

}

else{
//KEEP TRYING UNTIL END OF ALL FRONTIERS!
}

Queue_of_Paths * Q3 = Q2->Next;
Q2=Q3;
}
//printf("\n NEXT LIST\n");
//FrontierList* L2 = LL->Next;
//LL=L2;
//}

//EXHAUSTED ALL WAYS FOR ALL OPTIMAL FRONTS AND THEN ALL UNOPTIMAL FRONTS
//printf("\n EXHAUSTED ALL POSSIBLE PATHS\n");

return NULL;

}

void DeleteL(){
FrontierList*LL = L;
if(LL==NULL){
return;
}

while(LL!=NULL){
Queue_of_Paths * QQ = LL->NewQ;

//if(QQ!=NULL){
while(QQ!=NULL){


Queue_of_Paths* QQ2 = QQ->Next;

if(QQ->ListN!=NULL){
free(QQ->ListN);
QQ->ListN=NULL;
}

free(QQ);
QQ=NULL;
QQ=QQ2;
//if(QQ==NULL)
//break;
}
//}
/*
if(LL->NewQ!=NULL){
free(LL->NewQ);
LL->NewQ=NULL;
}
*/
FrontierList* LL2 = LL->Next;
free(LL);
LL=NULL;
LL=LL2;
//if(LL==NULL)
//break;
}


//free(L);
//L=NULL;
return;
}
//REMEMBER TO INSERT TWO NUMS... PAIRS
void InsertStart(int Num){
//Given AllStarts int*

if(Num<0){
return;
}
if(Num==Boundc&&Num==Boundr&&Num>=Boundr){
return;
}
if(Num>=Boundr){
return;
}
if(Num>=Boundc){
return;
}

//printf("\n INSERT:%d\n",Num);

int * A = AllStarts;
ASize = ASize+1;
if(A==NULL){
AllStarts=(int*)malloc(sizeof(int));
AllStarts[0]=Num;
}
else{
//ASize = ASize+1;
int* A2 = (int*)malloc(ASize*sizeof(int));
int i=0;
while(i<ASize-1){
A2[i]=AllStarts[i];
++i;
}
A2[i]=Num;

free(AllStarts);
AllStarts=NULL;
AllStarts=A2;
}

return;
}

void DeleteStarts(){
free(AllStarts);
AllStarts=NULL;
ASize=0;
return;
}

void PrintStart(int* AS,int Size){
int* A = AS;

int i=0;
//printf("\n ALLSTARTS DATA: \n");
if(i%2==0){
while(i<Size-1){
//int j=0;
printf(" [%d,",A[i]);
printf("%d] ",A[i+1]);
i=i+2;
}
}
else{

printf("\n NOT EVENLY DISPERSED VECTORS!!!\n");
}
return;
}

//StartR, C will be from AList next vectors
int* SequenceGen(int StartR, int StartC, char* S){

if(S==NULL){
return NULL;
}

//printf("\nGenerating Sequence of paths for:%s\n",S);

//Two coords for each one char str...
int D = ((strlen(S))*2);

ISize = D;

int* Seq = (int*)malloc(D*sizeof(int));
int i=0;
int k=0;
while(i<(D/2)){

//printf("\n%c\n",S[i]);

if(S[i]=='u'){
StartR=StartR-1;

}
if(S[i]=='r'){
StartC=StartC+1;

}
if(S[i]=='d'){
StartR = StartR+1;

}
if(S[i]=='l'){
StartC=StartC-1;

}

Seq[k+i]=StartR;
Seq[k+i+1]=StartC;
k+=1;
i+=1;
}

//i=4;
//Seq[i]=StartR;
//Seq[i+1]=StartC;

printf("\nPosition Sequence: ");
PrintStart(Seq,D);

return Seq;
}


char* MAIN(FILE* F, int initial_i, int initial_j,int goal_i,int goal_j ){
//Everything you need
 //CRUCIAL PART, IMPLEMENT IN SCOPE OF FUNC GIVEN... 
    //return NULL;
    
    if(F==NULL){    
     printf("\nFILE OPEN ERROR\n");
     exit(0);
    }
    

    int FileCount = 0;

    char* c;
    c  = (char*)GetNextValue(F);
    
    Boundr = atoi(c);
    //free(c);
    //c=NULL; 
    //printf("Rows:%d",Boundr);
    
    char* d; 
    d = GetNextValue(F);
    Boundc = atoi(d);
    //free(d);
    //d = NULL;
    //printf("Columns:%d\n\n",Boundr); 

    

    //CHECK VALUES FOR BOARD     
    if(Boundc<=0||Boundr<=0){

    printf("\nError, BOUNDC or BOUNDR Data Lost");

    exit(-1);;

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
    SetUpBoard(F,_BOARD_);
  
    fclose(F);

    //return 0; 
    //PrintBoard(_BOARD_);
  
    GetDensity(_BOARD_);

    //printf("\n DENSITY: %lf",Density);
 
    _BOARD_[initial_i][initial_j] = 'P';
    _BOARD_[goal_i][goal_j]='.';
   
    //PrintBoard(_BOARD_);

    InsertStart(initial_i);
    InsertStart(initial_j);
 
    char* C = Path(initial_i,initial_j,goal_i,goal_j,NULL,_BOARD_);
    
    if(C==NULL){
    if(IsGoal==1){
    printf("\nGoal Found, but no Path Required\n");
    }
    else{
    printf("\nNo Path Found\n"); 
    }
    }
    else{
    printf("\nCOMPLETE AND OPTIMAL PATH FOUND: %s \n",C);
    }
   
    //int* I = SequenceGen(AllStarts[ASize-2],AllStarts[ASize-1],C); 
 

    //PrintStart(AllStarts,ASize);
 
    //printf("\nVector Seq first node: [%d,%d]\n",I[0],I[1]);

    //int g=0;
    //int k=0;
   
     
    //while(g<ISize){
    //path.push_back(std::make_pair(I[g+k],I[g+k+1]));
    //k++;
    //g++;
    //}
    

    //ISize=0;

    //Delete ENV
    //DeleteBoard(_BOARD_);   
    //Close File
    //fclose(F);
    //
    //return 0;
    FileCount++;
    //if(FileCount==10){
    DeleteBoard(_BOARD_);
    //}
    //return I;
    //}
    //Free All Queues if created
    Free();
    //Free All FrontierList
    DeleteL();
    //Close File 
    //fclose(S);
    DeleteStarts();
   
    printf("\n SIZE OF SEQ: %d",ISize);

    //char CC[strlen(C)+1];
    //bzero(CC,strlen(C)+1); 
    //strncpy(CC,C,strlen(C));
    //free(C);
    //C=NULL;
    return C;

}


