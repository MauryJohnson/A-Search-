#ifndef HEADER_H
#define HEADER_H
//extern "C"
//{
//#endif

//#define NULL 0


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

//BOARD SIZE
int Boundc;
int Boundr;
    
//void PrintBoard(char ** _BOARD_);

//void ResetBoard(char ** _BOARD_);

int* AllStarts = NULL;

int STARTR = 0;

int STARTC= 0;

int ASize = 0;

int IsGoal = 0;

int ISize = 0;

int GCOUNTER = 0;

double Density = 0.0;

//FrontierList* L = NULL;

extern "C"{

char* MAIN(FILE* F, int r, int c, int R, int C);

void PrintBoard(char ** _BOARD_);

void ResetBoard(char ** _BOARD_);

void InsertStart();

void PrintStart(int* G, int Size);

void DeleteStarts();

//For setting up variables
//int GCOUNTER = 0;
int GET(char* S,char* P);
//
char* GetNextValue(FILE *F);
//
void SetUpBoard(FILE *File,char ** _BOARD_);
//points to each exact path cost list

void DeleteBoard(char** _BOARD);

//LIST OF LISTS
//Queue of Paths
typedef struct Queue_of_Paths_{

    int OrigR;
    int OrigC;
    
    //Position Startd
    int StartR;
    int StartC;
    
    //The Entire Path Sequence
    //Sequence of steps u,l,r,d, character array (May be as long as necessary)
    //u = row - 1
    //ntierList* L = NULL;


    //d = row+1
    //l = column - 1
    //r = column + 1
    // use STRLEN(ListN) to get path length.
    char* ListN;
    
    //THE VALUE
    int H1_H2_G;

    //Another Path List (Potential)
    struct Queue_of_Paths_* Next;
    
}Queue_of_Paths;


typedef struct FrontierList_{


Queue_of_Paths * NewQ;

struct FrontierList_* Next;


} FrontierList;

//Priority Queue, because want to minimize paths of queue

//Inserts a Path into Queue, All Paths should be COMPLETE and UNIQUE.
//INCLUDE ALL ENTRIES FULFILLED for Q(n)
void Insert(Queue_of_Paths * Q);

void InsertQ(Queue_of_Paths * Q);

//NEEDED
//FrontierList * L = NULL;

void InsertL(FrontierList* L);

//Delete all entries in List, including char*'s
void DeleteL();

void Sort(Queue_of_Paths * Q);

void AdjacentCheck(char* App, int* Startr, int* Startc, int Endr, int Endc);

Queue_of_Paths* Evaluate(char* App, int Startr, int Startc, int Endr, int Endc, char** ENV);

Queue_of_Paths* Exists(int R, int C, char LastDir);

FrontierList * Prev(FrontierList* LL);

//double Density = 0.0;

void GetDensity(char** ENV);

int Value(int StartR, int StartC, int EndR, int EndC);

//Delete an entry in Queue, MAKE SURE, WHEN FOUND nth Optimal Path, Save that queue node and prepare for the next Challenge
void Delete(Queue_of_Paths * Q);

void PrintQueue();

void Free();

//Call strcmp of each complete path sequence in queue, if true, delete one, if not, continue for all path pointers in queue
//WILL READ PATH BY U,D,R,L.... From position path started
//RETURN THE POINTER TO DUPLICATE NODE, NULL IF NONE, CALL Delete(CheckDuplicatePath(Queue_of_Paths * Q1, Queue_of_Paths *Q2));
Queue_of_Paths* CheckDuplicatePath(Queue_of_Paths * Q1);

//Complete Heuristic 1, always return 0 (0 when reached goal), call this heuristic on a path, must expand each path, and then will determine if path is complete...
int DFS(int startr, int startc, int goalr, int goalc,char** A);

//Manhattan Heuristic 2, return estimate dist (Magnitude), used when, if found a complete path, get estimated magnitude.
int ManhattanHeuristic(int r1, int c1, int r2, int c2);

//Root contains blank char... 
//Else contains path seq char
typedef struct TraceTree_{

char ActFromPrev;

struct TraceTree_* NextUp;
struct TraceTree_* NextRight;
struct TraceTree_* NextDown;
struct TraceTree_* NextLeft;

}TraceTree;

//Once Tree is done, all have to do is search tree preorder
//Create State Tree
//void PopulateTree(int Starts, int Startc, char** ENV);
//Insert chars, but only the next node of tree... Check if valid move as well
//void InsertTree(char C,char* V);
//Delete Starting at specified node
//void DeleteTree(TraceTree* TT,int Level);
//Print Tree PReorder Up Right Down Left... Important, because these are all adjecent actions to eachother!!!
//void PrintTree(TraceTree* TT, int Level);

//int IndicateCompletePath = 0;

//char* Trace(char** ENV,int Startr,int Startc, int Endr, int Endc,char* App,int Size);

char* Path(int StartR, int StartC, int EndR, int EndC, char* App, char** ENV);

//int STARTR = 0;
//int STARTC = 0;
int* TraceBack(char* App, int Startr, int Startc, char** ENV);

//Queue_of_Paths* Q = NULL;

int* SequenceGen(int StartR,int StartC,char* S);


}

FrontierList* L = NULL;

Queue_of_Paths* Q = NULL;
//TraceTree* T = NULL;
//#ifdef HEADER_H
//}
#endif
