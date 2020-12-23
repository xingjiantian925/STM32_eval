
#include "delay.h"
#include "lcd.h"

#include "w25qxx.h"
#include "touch.h"
#include<math.h>

int fnflag=0;
char * calculate(char * equ);
unsigned short int is_digit(char ch);
unsigned short int is_operation(char ch);
unsigned short int is_x(char ch);
void secondPriority(double *numbuffer, char *opbuffer, double *result);
void thirdPriority(double *numbuffer, char *opbuffer, double *result);
void firstPriority(double *numbuffer, char *opbuffer, double *result);
void bracketSolve(double *numbuffer, char *opbuffer, double *result);
void calculateEx(double *numbuffer, char *opbuffer, double *result);
void bracketInit(double *numinbracket, char *opinbracket);
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

void secondPriority(double *numbuffer, char *opbuffer, double *result);
void thirdPriority(double *numbuffer, char *opbuffer, double *result);
void firstPriority(double *numbuffer, char *opbuffer, double *result);
void bracketSolve(double *numbuffer, char *opbuffer, double *result);
void calculateEx(double *numbuffer, char *opbuffer, double *result);
void bracketInit(double *numinbracket, char *opinbracket);
void num_push(double * buffer)
{//!要保持buffer 的值不变
    double *i = buffer;
    //while (buffer-startnum<maxitem)
    int tp = 0;
    while(tp<9)
    {
        *buffer = *(buffer+1);
        buffer++;
        tp++;
    }
    buffer = i;
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
unsigned short int is_operation(char ch)
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
unsigned short int is_digit(char ch)
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
unsigned short int is_x(char ch)
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
     //  printf("double1:%lf", double1);
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
       // printf("operaton1:%c", &*opebuffer);
        }
        
    }
    }


//void calculate(double * numbuffer,char * opbuffer,double * result)
//{   
//    double mid =  *(numbuffer++);
//    double first = *numbuffer;
//    while(*numbuffer!='\0'&& *opbuffer!='\0')
//    {
//    switch (*(opbuffer++))
//    {
//        case addt:
//            mid =  mid + *(numbuffer++);
//            break;
//        case minust:
//            mid = mid- *(numbuffer++);
//            break;
//        case multiplyt:
//            mid = mid * (*numbuffer++);
//            break;
//        case dividet:
//            mid = mid / (*numbuffer++);
//            break;
//        case powt:
//            mid = pow(mid, (*numbuffer++));
//            break;
//        case st:
//            numbuffer--;
//            calculate(numbuffer, opbuffer, &mid);
//            numbuffer++;
//            break;
//        case et:
//            break;
//    }
//    }
//    *(result++) = mid;

//}

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
            if (opinbracket[0]=='\0')
            {
                double res = doTriangle(ch, numinbracket[0]);

                *dgo = res;//////////////halt
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

       // if(*(opbuffer+1)!='\0' && *(numbuffer+1)!= '\0' && *(numbuffer+2)!='\0' )
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

        //if(*(opbuffer+1)!='\0' && *(numbuffer+1)!= '\0' && *(numbuffer+2)!='\0' )
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
    while( *opbuffer!='\0')
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

        //if(*(opbuffer+1)!='\0' && *(numbuffer+1)!= '\0' && *(numbuffer+2)!='\0' )
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
////
double doublebuffer[32];
char operationbuffer[32];
double result[32];
double eval(char * equ )
{
    getBuffer(equ, doublebuffer, operationbuffer);
    calculateEx(doublebuffer, operationbuffer, (result));
    return doublebuffer[0];
}
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////
char GetInput(void)
{
	
	u16 x=0;
	u16 y=0;
	TP_Read_XY(&x,&y);
	char buffer[32];
	//LCD_ShowString(30,90,lcddev.width,lcddev.height,16,BLACK,"_____________");
	//sprintf(buffer,"x:%d,y:%d",x,y);
	//LCD_ShowString(30,90,lcddev.width,lcddev.height,16,BLACK,buffer);
	if(x<1100)
	{
		if (y>1000)
		
		if(y<1600)
		{
			if(fnflag){
			return 'n';
			}
			return '^';
		}
		else if( y<2100)
		{
			if(fnflag){
				return 'P';
			}
			return '/';
		}
		else if(y<2700){
			if(fnflag){
			return 's';
			}
			return '*';
		}
		else if(y<3300)
		{
			if(fnflag){
				return 'c';
				}
			return '-';
		}
		else if(y<3800){
			if(fnflag){
			return 't';
			}
			return '+';
		}
	
	}
	else if(x<2100)
	{
			if(y<1600)
		{
			return ')';
		}
		else if( y<2100)
		{
			return '9';
		}
		else if(y<2700){
			return '6';
		}
		else if(y<3300)
		{
			return '3';
		}
		else if(y<3800){
			return '=';
		}
	}
	else if(x<3000)
	{
		if(y<1600)
		{
			return '(';
		}
		else if( y<2100)
		{
			return '8';
		}
		else if(y<2700){
			return '5';
		}
		else if(y<3300)
		{
			return '2';
		}
		else if(y<3800){
			return '.';
		}
	}
	else if(x>3000)
	{
		if(y<1600)
		{
			return 'F';
		}
		else if( y<2100)
		{
			return '7';
		}
		else if(y<2700){
			return '4';
		}
		else if(y<3300)
		{
			return '1';
		}
		else if(y<3800){
			return '0';
		}
	}
	
	return '!';
}



void drawbutton(void)
{
	int i=0;
	int len=0;
	LCD_ShowString(0,70,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,120,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,170,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,220,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,270,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	
	for(i=0;i<=18;i++)
	{LCD_ShowString(50,85+len,lcddev.width,lcddev.height,16,BLACK,"|");
	len=len+14;	
	
	}
	len=0;
	for(i=0;i<=18;i++)
	{LCD_ShowString(110,85+len,lcddev.width,lcddev.height,16,BLACK,"|");//显示清屏区域  lcddev竖屏
	len=len+14;	
	
	}
		len=0;
	for(i=0;i<=18;i++)
	{LCD_ShowString(170,85+len,lcddev.width,lcddev.height,16,BLACK,"|");//显示清屏区域  lcddev竖屏
	len=len+14;	
	
	}
	
	LCD_ShowString(25,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"Fn");
	LCD_ShowString(25,150+50*0,lcddev.width,lcddev.height,16,BLACK,"7");
	LCD_ShowString(25,150+50,lcddev.width,lcddev.height,16,BLACK,"4");
	LCD_ShowString(25,150+50*2,lcddev.width,lcddev.height,16,BLACK,"1");	
	LCD_ShowString(25,150+50*3,lcddev.width,lcddev.height,16,BLACK,"0");	
	
	LCD_ShowString(80,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"(");
	LCD_ShowString(80,150+50*0,lcddev.width,lcddev.height,16,BLACK,"8");
	LCD_ShowString(80,150+50,lcddev.width,lcddev.height,16,BLACK,"5");
	LCD_ShowString(80,150+50*2,lcddev.width,lcddev.height,16,BLACK,"2");	
	LCD_ShowString(80,150+50*3,lcddev.width,lcddev.height,16,BLACK,".");	
	
	LCD_ShowString(140,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,")");
	LCD_ShowString(140,150+50*0,lcddev.width,lcddev.height,16,BLACK,"9");
	LCD_ShowString(140,150+50,lcddev.width,lcddev.height,16,BLACK,"6");
	LCD_ShowString(140,150+50*2,lcddev.width,lcddev.height,16,BLACK,"3");	
	LCD_ShowString(140,150+50*3,lcddev.width,lcddev.height,16,BLACK,"=");	
	
	LCD_ShowString(205,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"^");
	LCD_ShowString(205,150+50*0,lcddev.width,lcddev.height,16,BLACK,"/");
	LCD_ShowString(205,150+50,lcddev.width,lcddev.height,16,BLACK,"*");
	LCD_ShowString(205,150+50*2,lcddev.width,lcddev.height,16,BLACK,"-");	
	LCD_ShowString(205,150+50*3,lcddev.width,lcddev.height,16,BLACK,"+");
}

    void bufferInit()
   {
int i=0;
        for (i = 0; i < 50; i++)
        {
           
            operationbuffer[i] = '\0';
            doublebuffer[i] = -1;
            result[i] = '\0';
        }
}
	 
	char equ[32];
	 void equInit()
	 {
		 int i=0;
		 for (i=0;i<32;i++)
		 {
			 equ[i]='\0';
		 }
	 }
	 int latestInput(char * equ)
	 {
		 char * const_equ=equ;
		 int i=-1;
		 while(*(equ++)!='\0')
		 {
			 i++;
		 }
		 equ=const_equ;
		 return i;
	 }
	void drawbutton2(void)
{
	int i=0;
	int len=0;
	LCD_ShowString(0,70,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,120,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,170,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,220,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	LCD_ShowString(0,270,lcddev.width,lcddev.height,16,BLACK,"______________________________");
	
	for(i=0;i<=18;i++)
	{LCD_ShowString(50,85+len,lcddev.width,lcddev.height,16,BLACK,"|");
	len=len+14;	
	
	}
	len=0;
	for(i=0;i<=18;i++)
	{LCD_ShowString(110,85+len,lcddev.width,lcddev.height,16,BLACK,"|");//显示清屏区域  lcddev竖屏
	len=len+14;	
	
	}
		len=0;
	for(i=0;i<=18;i++)
	{LCD_ShowString(170,85+len,lcddev.width,lcddev.height,16,BLACK,"|");//显示清屏区域  lcddev竖屏
	len=len+14;	
	
	}
	
	LCD_ShowString(25,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"Fn");
	LCD_ShowString(25,150+50*0,lcddev.width,lcddev.height,16,BLACK,"7");
	LCD_ShowString(25,150+50,lcddev.width,lcddev.height,16,BLACK,"4");
	LCD_ShowString(25,150+50*2,lcddev.width,lcddev.height,16,BLACK,"1");	
	LCD_ShowString(25,150+50*3,lcddev.width,lcddev.height,16,BLACK,"0");	
	
	LCD_ShowString(80,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"(");
	LCD_ShowString(80,150+50*0,lcddev.width,lcddev.height,16,BLACK,"8");
	LCD_ShowString(80,150+50,lcddev.width,lcddev.height,16,BLACK,"5");
	LCD_ShowString(80,150+50*2,lcddev.width,lcddev.height,16,BLACK,"2");	
	LCD_ShowString(80,150+50*3,lcddev.width,lcddev.height,16,BLACK,".");	
	
	LCD_ShowString(140,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,")");
	LCD_ShowString(140,150+50*0,lcddev.width,lcddev.height,16,BLACK,"9");
	LCD_ShowString(140,150+50,lcddev.width,lcddev.height,16,BLACK,"6");
	LCD_ShowString(140,150+50*2,lcddev.width,lcddev.height,16,BLACK,"3");	
	LCD_ShowString(140,150+50*3,lcddev.width,lcddev.height,16,BLACK,"=");	
	
	LCD_ShowString(205,150+50*(-1),lcddev.width,lcddev.height,16,BLACK,"<-");
	LCD_ShowString(205,150+50*0,lcddev.width,lcddev.height,16,BLACK,"Pi");
	LCD_ShowString(205,150+50,lcddev.width,lcddev.height,16,BLACK,"sin");
	LCD_ShowString(205,150+50*2,lcddev.width,lcddev.height,16,BLACK,"cos");	
	LCD_ShowString(205,150+50*3,lcddev.width,lcddev.height,16,BLACK,"tan");
	
}
int main()
{
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	LCD_Init();          //液晶屏初始化
	LCD_Clear(WHITE);
  W25QXX_Init();			//W25QXX初始化
	TP_Init();
	//LCD_Clear(WHITE);//清除屏幕
	drawbutton();
	char tempinmain='!';
	equInit();
	char *pequ=equ;
	const char *const_pequ=equ;
	bufferInit();
char ans[32];
	while(1)
	{
		delay_ms(165);
		tempinmain=GetInput();

		if(tempinmain!='!')
		{
			
			if(tempinmain=='n')
			{
			int pos=latestInput(equ);
			if(pos==-1)
			{
				continue;
			}
			else
			{
				pequ--;
			equ[pos]='\0';
				LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,"                         ");
			LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,equ);
			
			continue;
			}
		}
			if (fnflag==0 && tempinmain=='F')
			{
				LCD_Clear(WHITE);
				
				drawbutton2();
				LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,equ);
					LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,"                                                       ");
				LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,ans);
				
				fnflag=1;
			}
			else if (fnflag==1 && tempinmain=='F')
			{
				LCD_Clear(WHITE);
				drawbutton();
				LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,equ);
					LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,"                                                       ");
				LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,ans);
				
				fnflag=0;
			}
			LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,"                           ");

			if(tempinmain!='=' && tempinmain!='F'){
			*(pequ++)=tempinmain;
			}
			
//				if (p==30)
//				{
//					p=0;
//				}
			
			LCD_ShowString(2,20,lcddev.width,lcddev.height,16,BLACK,equ);
			if(tempinmain=='=')
			{
//				getBuffer(equ,doublebuffer,operationbuffer);
//				calculateEx(doublebuffer,operationbuffer,result);
				
				sprintf(ans,"ANS:%lf",eval(equ));
				LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,"                                                       ");
				LCD_ShowString(0,45,lcddev.width,lcddev.height,16,BLACK,ans);
				equInit();
				pequ=const_pequ;
				bufferInit();
				
				
			}
		}
		
		
	}
		return 0;
}

