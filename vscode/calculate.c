#define u8 unsigned short int
#define cost 'c'
#define sint 's'
#define tant 't'
#define multiplyt '*'
#define addt '+'
#define minust '-'
#define dividet '/'
#define powt '^'
#define st '('
#define et ')'
#define maxitem 50
#define dmax (pow(2,63)-1)
#define P 3.14159265
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double *startnum;
char *startop;
void getBuffer(char * equ,double * numbuffer,char * opebuffer)
void secondPriority(double *numbuffer, char *opbuffer, double *result);
void thirdPriority(double *numbuffer, char *opbuffer, double *result);
void firstPriority(double *numbuffer, char *opbuffer, double *result);
void bracketSolve(double *numbuffer, char *opbuffer, double *result);
void calculateEx(double *numbuffer, char *opbuffer, double *result);
void bracketInit(double *numinbracket, char *opinbracket);
//注意当括号内的操作符大于等于两个的时候，两个push函数会出错
//当为+-时，只计算第一个符
double eval(char * equ )
{
    getBuffer(equ, doublebuffer, operationbuffer);
    calculateEx(doublebuffer, operationbuffer, (result));
    return doublebuffer[0];
}
void num_push(double * buffernumin)
{//!要保持buffer 的值不变
    double * i =  buffernumin;
    //while (buffer-startnum<maxitem)
    int tp = 0;
    while(tp<9)
    {
        *buffernumin = *(buffernumin+1);
        buffernumin++;
        tp++;
    }
    buffernumin = i;
}
void op_push(char * buffer)
{
    char * i = buffer;
    int tp = 0;
    while (tp<9)
    //while (buffer-startop<maxitem)
    {
        *buffer = *(buffer+1);
        buffer++;
        tp++;
    }
    buffer = i;
}
u8 is_triangle(char ch)
{
        if(
        (ch==cost)||
        (ch==sint)||
        (ch==tant)
    )
        return 1;
    else
        return 0;
}
u8 is_operation(char ch)
{
    if(
        (ch==cost)||
        (ch==sint)||
        (ch==tant)||
        (ch==multiplyt)||
        (ch==addt)||
        (ch==minust)||
        (ch==dividet)||
        (ch==powt)
    )
        return 1;
    else
        return 0;
}
u8 is_digit(char ch)
{
	if(
		(ch=='1')||
		(ch=='2')||
		(ch=='3')||
		(ch=='4')||
		(ch=='5')||
		(ch=='6')||
		(ch=='7')||
		(ch=='8')||
		(ch=='9')||
		(ch=='0')||
		(ch=='.')||
        (ch=='P')
		)
		return 1;
	else
		return 0;
}
u8 is_x(char ch)
{
    if(ch=='x'){
        return 1;;
    }
    return 0;
}
u8 is_brackets(char ch)
{
    if(ch==st)
    {
        return 1;
    }
    else if(ch==et)
    {
        return 1;
    }
    return 0;
}

void bufferClear(char * temp,int n)
{
    int i = 0;
    for (i = 0; i < n;i++)
    {
        *(temp+i)= '\0';
    }
}
void getBuffer(char * equ,double * numbuffer,char * opebuffer)
{
    char res[50];
 
    char *cequ = equ;
    
    while(*equ!='\0')
    {
    char temp[50];
    char *ptemp = temp;
    bufferClear(temp, 10);
    if(is_digit(*equ))
    {
         while (is_digit(*equ)) 
         {
             *(ptemp++) = *(equ++);
        }
        double double1 = -1;
        if(*(ptemp-1)=='P')
        {
         double1 = P;
        }
        else
        {
         double1=atof(temp);
        }
        *(numbuffer++) = double1;
       printf("double1:%lf", double1);
        cequ = equ;
    }
    if(is_operation(*equ) || is_brackets(*equ))
    {

         char *ptemp = temp;
        while(is_operation(*equ)|| is_brackets(*equ))
        {
            *(ptemp++)=*(equ++);
             *(opebuffer++) = *((ptemp)-1);

        }
        printf("operaton1:%c", &*opebuffer);
        }
        
    }
    }


void calculate(double * numbuffer,char * opbuffer,double * result)
{   
    double mid =  *(numbuffer++);
    double first = *numbuffer;
    while(*numbuffer!='\0'&& *opbuffer!='\0')
    {
    switch (*(opbuffer++))
    {
        case addt:
            mid =  mid + *(numbuffer++);
            break;
        case minust:
            mid = mid- *(numbuffer++);
            break;
        case multiplyt:
            mid = mid * (*numbuffer++);
            break;
        case dividet:
            mid = mid / (*numbuffer++);
            break;
        case powt:
            mid = pow(mid, (*numbuffer++));
            break;
        case st:
            numbuffer--;
            calculate(numbuffer, opbuffer, &mid);
            numbuffer++;
            break;
        case et:
            break;
    }
    }
    *(result++) = mid;

}

double curnum[10];
char curop[10];

double doTriangle(char  ch,double num)
{
    switch(ch)
    {
        case sint:
            return sin(num);
        case cost:
            return cos(num);
        case tant:
            return tan(num);
        }
}
void triangleBracketSolve(double * numbuffer, char * opbuffer,double * result)
{
        double numinbracket[19];
    char opinbracket[19];
    bracketInit(numinbracket, opinbracket);
    char *c = opbuffer;
    double *d = numbuffer;
    char *sgo;
    char *ego;
    double *dgo;
    double *start;
    int pos = 0;
    while( *opbuffer!='\0')
    {
        //bracketInit();
        char ch = *(opbuffer);
        //opbuffer++;
        if(is_triangle(ch))//get evry thing in bracket except the brackets
        {//and push them into calEx
            //bracketInit();
            char *op = opinbracket;
            double *num = numinbracket;
            sgo = opbuffer;
            dgo = numbuffer;
            start = numbuffer;
            opbuffer++;
            while(*(opbuffer++)!=et)
            {
                
                if(*opbuffer!=et )
                {
                *(op++)=*(opbuffer);
                }
                *(num++) = *(numbuffer++);
                if(*opbuffer==et)
                {
                    ego = opbuffer;
                    break;
                }
            }

            calculateEx(numinbracket, opinbracket,result);
            if (opinbracket[0]=='\0' )
            {
                double res = doTriangle(ch, numinbracket[0]);
                printf("\ndoTriangle:%lf", res);
                *dgo = res;
            }
            else 
            {
                *dgo = -1;
            }

            int i = 0;
            
            for (i = numbuffer-start; i>1;i--)
            {
                num_push(start+i-1);
                //////wtf!!!!!!!!!!!!!!!!!!
            }

            for (i = ego-sgo+1; i >0 ;i--)
            {
            op_push(sgo+i-1);
            }
            ;
            opbuffer = c;
            numbuffer = d;//start with the first one again
        }
        
        else
        {
        numbuffer++;
        opbuffer++;
        }
    }
    opbuffer = c;
    numbuffer = d;
    

}
void calculateEx(double * numbuffer,char * opbuffer,double * result)
{
    
    triangleBracketSolve(numbuffer, opbuffer,result);
    bracketSolve(numbuffer, opbuffer, result);
    firstPriority(numbuffer, opbuffer, result);
    secondPriority( numbuffer, opbuffer,result );
    thirdPriority( numbuffer,opbuffer,result);

}

void bracketSolve(double * numbuffer,char * opbuffer,double * result)
{
    double numinbracket[19];
    char opinbracket[19];
    bracketInit(numinbracket, opinbracket);
    char *c = opbuffer;
    double *d = numbuffer;
    char *sgo;
    char *ego;
    double *dgo;
    double *start;
    double first = *numbuffer;
    int pos = 0;
    while( *opbuffer!='\0')
    {
        if(*(opbuffer)==st)//get evry thing in bracket except the brackets
        {//and push them into calEx
            //bracketInit();
            char *op = opinbracket;
            
            double *num = numinbracket;
            sgo = opbuffer;
            dgo = numbuffer;
            start = numbuffer;
            int bracketCount = 0;
            int bracketEncounterFlag = 0;
            while(*(opbuffer++)!=et || bracketCount==0)
            {
                
                //bracket can also in another bracket
                if(*opbuffer==st)
                {
                    bracketCount++;
                    bracketEncounterFlag = 1;
                }
                if(*opbuffer==et)
                {
                    bracketCount--;
                }
                
                if(*opbuffer!=et || bracketCount==0)
                {
                *(op++)=*(opbuffer);
                }
                if (*opbuffer!=et || bracketEncounterFlag==0)
                {
                *(num++) = *(numbuffer++);
                }
                if(*opbuffer==et)
                {
                    ego = opbuffer;
                    break;
                }
            }
            ;
            calculateEx(numinbracket, opinbracket, result);
            
            *dgo = *numinbracket;
            int i = 0;
            numbuffer = start;
            for (i = numbuffer-start; i>1;i--)
            {
                num_push(numbuffer+i-1);
                //////wtf!!!!!!!!!!!!!!!!!!
            }
            opbuffer = sgo;
            for (i = ego-sgo+1; i >0 ;i--)
            {
            op_push(opbuffer+i-1);
            }
            
            opbuffer = c;
            numbuffer = d;//start with the first one again
        }
        
        else
        {
        numbuffer++;
        opbuffer++;
        }
    }
    opbuffer = c;
    numbuffer = d;
}
void bracketInit(double * numinbracket,char * opinbracket)
{
    int i = 0;
    for (i = 0; i <10;i++)
{
    numinbracket[i] = -1;
    opinbracket[i] = '\0';
}
}
void firstPriority(double * numbuffer,char * opbuffer,double * result)
{   // including ^ whatever
    char *c = opbuffer;
    double *d = numbuffer;
    double mid = 0;
    int pos = 0;
    int calFlag = 0;
    while(*opbuffer!='\0')
    {

        switch (*(opbuffer))
        {

        case powt:
            
            mid = pow(*(numbuffer), (*(numbuffer+1)));
            calFlag = 1;
            pos++;
            break;
        
    }

    if(calFlag)
    {

        if(*(opbuffer+1)!='\0' && *(numbuffer+1)!= '\0' && *(numbuffer+2)!='\0' )
        calFlag = 0;

        //change numbuffer and opbuffer
        *(numbuffer) = mid;
        num_push(numbuffer + 1);
        op_push(opbuffer);
        // don't know if pointer can beheave like a arraylist;
    }
    else
    {
    numbuffer++;
    opbuffer++;
    }
    *(result++) = mid;
    }
        opbuffer = c;
    numbuffer = d;
}
void secondPriority(double * numbuffer,char * opbuffer,double * result)
{
        char *c = opbuffer;
    double *d = numbuffer;
   double mid = 0;
    int pos = 0;
    int calFlag = 0;
    while( *opbuffer!='\0')
    {
    switch (*(opbuffer))
    {

        case multiplyt:
            
            mid = *(numbuffer)*(*(numbuffer+1));
            calFlag = 1;
            pos++;
            break;
        case dividet:
            mid = *(numbuffer) / (*(numbuffer + 1));
            calFlag = 1;
            pos++;
            break;
    }

    if(calFlag)
    {

        if(*(opbuffer+1)!='\0' && *(numbuffer+1)!= '\0' && *(numbuffer+2)!='\0' )
        calFlag = 0;

        //change numbuffer and opbuffer
        *(numbuffer) = mid;
        num_push(numbuffer + 1);
        op_push(opbuffer);
        // don't know if pointer can beheave like a arraylist;
    }
    else
    {
    numbuffer++;
    opbuffer++;
    }
    *(result++) = mid;
    }
        opbuffer = c;
    numbuffer = d;
}
void thirdPriority(double * numbuffer,char * opbuffer,double * result)
{
        char *c = opbuffer;
    double *d = numbuffer;
       double mid = 0;
    int pos = 0;
    int calFlag = 0;
    while(*opbuffer!='\0')
    {
    switch (*(opbuffer))
    {

        case addt:
            
            mid = *(numbuffer)+(*(numbuffer+1));
            calFlag = 1;
            pos++;
            break;
        case minust:
            mid = *(numbuffer) -(*(numbuffer + 1));
            calFlag = 1;
            pos++;
            break;
    }

    if(calFlag)
    {

        
        calFlag = 0;

        //change numbuffer and opbuffer

        *(numbuffer) = mid;
        num_push(numbuffer + 1);
        op_push(opbuffer);
    
        // don't know if pointer can beheave like a arraylist;
    }
    else
    {
    numbuffer++;
    opbuffer++;
    }
    *(result++) = mid;
    }
    opbuffer = c;
    numbuffer = d;
}


