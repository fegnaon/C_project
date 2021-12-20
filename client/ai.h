typedef struct Leaf{
    int grade;
}Leaf;

typedef struct Branch{
    int val;
    int grade;
    Leaf *leaves[255];
}Branch;

typedef struct Root{
    Branch *branches[255];
}Root;

#define TYPENUM 43

Root root;

int AllSonType[43] = {
3,2,
31,
23,21,
313,311,
231,213,211,
3133,3131,3113,3111,
2311,2133,2131,2113,2111,
31333,31331,31313,31311,31133,31131,31111,
23111,21331,21311,21131,21113,21111,
313331,313311,313131,313111,311331,311311,311111,
231113,211311,211131,211111};

int AllType[TYPENUM] = {212,2112,21112,211112,2111112,
213,312,
313,
2113,3112,31312,21313,313312,213313,3133313,
3113,31313,31331,
31112,21113,313112,211313,311312,213113,3113313,3133113,3131313,2311132,
31113,313113,311313,313313,
311112,211113,3113112,2113113,3131112,2111313,
311113,
3111113,3111112,2111113,2111112};

int TypeVal(int type);
int CalculateGrade(char (*board)[15],char mpiece);
int CalculateLineGrade(char *line,char piece,int len,int ifstart);
void Game(int* maxi,int* maxj,char (*board)[15],char mpiece,char epiece);
void Initialize();