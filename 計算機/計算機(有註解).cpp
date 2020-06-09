#include <windows.h>
#include <stdio.h>
#include <cwchar>
using namespace std;
#define BUFFER_LEN 256
void CursorPosition(int x,int y)//自訂游標位置函數
	{
		COORD pos={x,y};//字符在屏幕上的坐標
		HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);//讓調用的函數知道作用在誰身上。
		SetConsoleCursorPosition(hOut,pos);
	}	

int NowPos(int *nx,int *ny)
{
	HANDLE gh_std_out;//獲取當前游標位置 
	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(gh_std_out,&bInfo);
	*nx=bInfo.dwCursorPosition.X;
	*ny=bInfo.dwCursorPosition.Y;
} 

int main()
{	
		//字大小
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = 35;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
	
	int nx,ny;
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    
    //印計算機外殼
    SetConsoleTextAttribute(hOut,253);//253是顏色 
    for(int i=0;i<5;i++)
    {
    	for(int j=0;j<38;j++)
    		printf(" ");
    	printf("\n");
	}
	SetConsoleTextAttribute(hOut,15);
	CursorPosition(0,0);   
    for(int i=0;i<39;i++)
	printf("-");
	for(int i=1;i<9;i++){
		CursorPosition(0,i);
		printf("|");
	}
	for(int i=1;i<9;i++){
		CursorPosition(38,i);
		printf("|");
	}
	for(int i=0;i<39;i++){
		CursorPosition(i,9);
		printf("-");
	}
	for(int i=5;i<9;i++){
		CursorPosition(4,i);
		printf("|");
	}
	for(int i=5;i<9;i++){
		CursorPosition(8,i);
		printf("|");
	}
	//印輸入欄 
	for(int i=0;i<39;i++){
		CursorPosition(i,2);
		printf("-");
	}
	for(int i=0;i<39;i++){
		CursorPosition(i,4);
		printf("-");
	}
	SetConsoleTextAttribute(hOut,14);//數字顏色 
	BOOL SetConsoleFont(HANDLE, DWORD);
	for(int i=1,x=0;i<=3;i++,x++)//印數字 
	{
		CursorPosition(1+x,5);
		printf("%d",i);
	}
	for(int i=4,x=0;i<=6;i++,x++)
	{
		CursorPosition(1+x,6);
		printf("%d",i);
	}
	for(int i=7,x=0;i<=9;i++,x++)
	{
		CursorPosition(1+x,7);
		printf("%d",i);
	}
	CursorPosition(1,8);
	printf("0");	
	CursorPosition(2,8);
	printf(".");	
	CursorPosition(3,8);
	printf("=");
	SetConsoleTextAttribute(hOut,10);
	CursorPosition(5,5);
	printf("+");	
	CursorPosition(5,6);
	printf("-");	
	CursorPosition(6,5);
	printf("*");	
	CursorPosition(6,6);
	printf("/");
	CursorPosition(5,7);
	printf("AC");	
	CursorPosition(5,8);
	printf("Del");
	//印說明
	SetConsoleTextAttribute(hOut,15);
	CursorPosition(10,5);
	printf("1.使用W,A,S,D或方向鍵來移動");
	SetConsoleTextAttribute(hOut,11);
	CursorPosition(10,6);
	printf("2.使用Enter鍵或空白建輸入");
	SetConsoleTextAttribute(hOut,12);
	CursorPosition(10,7);
	printf("3.Del清一格,AC為全部清空"); 
	SetConsoleTextAttribute(hOut,13);
	CursorPosition(10,8);
	printf("4.按好算式後選擇'='算出答案");
	CursorPosition(1,5);
	//按鍵輸入	
	HANDLE handle;
    DWORD cnt;//儲存出入
    DWORD mode;//Console Mode
    INPUT_RECORD input;

    handle = GetStdHandle(STD_INPUT_HANDLE);//先取得基本輸入Handle
    GetConsoleMode(handle, &mode);//得到基本輸入的Mode
    SetConsoleMode(handle, mode & ~ENABLE_LINE_INPUT);//設定基本輸入模式，其中~ENABLE_LINE_INPUT代表不用按下Enter也可動作
	
	SetConsoleTextAttribute(hOut,253);
int j=0;/*s*/
char s[100]={0},c[30]={0};//運算符號 
int n=0,dn=0/*dq*/,point=0,poi=-1;//小數點位置				
float	q[30]={0}/*數字陣列*/,dq[30]={0}/*轉成數字的陣列*/,ans,an=0,a[30]={0};//a

    while(ReadConsoleInput(handle, &input, 1, &cnt))//開始讀取使用者的動作
    {
        if(input.EventType == KEY_EVENT)
        {
            if(input.Event.KeyEvent.bKeyDown == TRUE)
            {           	
            	if(input.Event.KeyEvent.wVirtualKeyCode==VK_CONTROL) break;
            	switch(input.Event.KeyEvent.wVirtualKeyCode){
                case (VK_LEFT):
                case (0x41):
					NowPos(&nx,&ny);
					CursorPosition(nx-1,ny);
					break;			    
                case (VK_RIGHT):
				case (0x44):				
					NowPos(&nx,&ny);
					CursorPosition(nx+1,ny);
					break;
				case (VK_UP):
				case (0x57):				
					NowPos(&nx,&ny);
					CursorPosition(nx,ny-1);
					break;
                case (VK_DOWN):
				case (0x53):				
					NowPos(&nx,&ny);
					CursorPosition(nx,ny+1);
					break;
				}
				if(input.Event.KeyEvent.wVirtualKeyCode==VK_RETURN ||
				   input.Event.KeyEvent.wVirtualKeyCode==VK_SPACE)
				{
					//數字功能
					NowPos(&nx,&ny);
					if(nx==1 && ny==5) {s[j]='1';}				
					else if(nx==2 && ny==5) s[j]='2'; 
					else if(nx==3 && ny==5) s[j]='3';  
					else if(nx==1 && ny==6) s[j]='4'; 
					else if(nx==2 && ny==6) s[j]='5'; 
					else if(nx==3 && ny==6) s[j]='6'; 
					else if(nx==1 && ny==7) s[j]='7'; 
					else if(nx==2 && ny==7) s[j]='8'; 
					else if(nx==3 && ny==7) s[j]='9'; 
					else if(nx==1 && ny==8) s[j]='0'; 
					else if(nx==2 && ny==8) s[j]='.';
					
					
					
					
					
					
					else if((nx==5 && ny==8) || (nx==6 && ny==8) || (nx==7 && ny==8))
					{					
						s[j-1]='\0'; j=j-2;n=0;dn=0;point=0;poi=-1;					
							CursorPosition(1,1);
							for(int i=0 ;i<27; i++)
								printf(" ");
										
					}
					else if((nx==5 && ny==7) || (nx==6 && ny==7))
					{
						for(int i=0 ;i<27; i++)
							s[i]=' ';
							j=-1;//位置 
							n=0;dn=0;
							for(int i=0;i<30;i++){ 
								dq[i]={'\0'};
								q[i]={'\0'};
								c[i]={'\0'};
							}//清空陣列 
							CursorPosition(1,3);
							for(int i=0 ;i<27; i++){
								printf(" ");
								s[i]={'\0'};
							}
							CursorPosition(1,1);
							for(int i=0 ;i<27; i++)
								printf(" ");
					}
						
							
					
					else if(nx==3 && ny==8) //=做運算 
					{
						s[j]='=';
						for(int i=0,j=0;i<=30;i++)
						{							
							if(s[i]=='+'){c[j]='+';j++;}
							if(s[i]=='-'){c[j]='-';j++;}
							if(s[i]=='*'){c[j]='*';j++;}
							if(s[i]=='/'){c[j]='/';j++;}
						}
						int sn=0;
						while(s[sn]!='\0')
							sn++;
						for(int i=0;i<=sn;i++)
						{
							if (s[i]=='1') {q[n]=1;n++;}
							if (s[i]=='2') {q[n]=2;n++;}
							if (s[i]=='3') {q[n]=3;n++;}
							if (s[i]=='4') {q[n]=4;n++;}
							if (s[i]=='5') {q[n]=5;n++;}
							if (s[i]=='6') {q[n]=6;n++;}
							if (s[i]=='7') {q[n]=7;n++;}
							if (s[i]=='8') {q[n]=8;n++;}
							if (s[i]=='9') {q[n]=9;n++;}
							if (s[i]=='0') {q[n]=0;n++;}
						    if (s[i]=='.')
								{
									point=1;
									poi=-1;
								}
							poi++;	
							if (s[i]=='+' || s[i]=='-' ||s[i]=='*' || s[i]=='/')
							{						
								for(int i=n-1,j=1;i>=0;i--,j=j*10)
									dq[dn]=dq[dn]+q[i]*j;
								if (point==1)
									for(int i=1;i<poi;i++)
										dq[dn]=dq[dn]/10;
										
								point=0;					
								dn++;
								n=0;
							}																						
						}						
						for(int i=n-1,j=1;i>=0;i--,j=j*10)
							dq[dn]=dq[dn]+q[i]*j;
						if (point==1)
							for(int i=1;i<poi-1;i++)
								dq[dn]=dq[dn]/10;	
						int cn=0;
						for(int i=0;i<=dn;i++)
						while(c[cn]!='\0')
							cn++;
						a[n]=dq[0];//a																										
						for(int i=0;i<cn;i++)
						{
						   	if(c[i]=='*')							
								a[n]=a[n]*dq[i+1];				    							   	
						   	if(c[i]=='/')													   		
								a[n]=a[n]/dq[i+1];				   							   	 
						   	if(c[i]=='+' )					   	
							{
								n++;
								a[n]=dq[i+1];																					    	
							}
						   	if(c[i]=='-')
							{
								n++;
								a[n]=-(dq[i+1]);						    	
						   	} 
						}											
						for(int i=0;i<30;i++)
							ans=ans+a[i];
						CursorPosition(1,3);
						printf("%f",ans);
						ans=0;
						an=0;
						dn=0;
						n=0;
						point=0;
						poi=-1;
						for(int i=0;i<30;i++){ 
								dq[i]={'\0'};
								q[i]={'\0'};
								c[i]={'\0'};
								a[i]={'\0'};
							}//清空陣列 
					}
					else if(nx==5 && ny==5)//+					
						s[j]='+'; 																		 
					else if(nx==5 && ny==6)//-
						s[j]='-'; 											
					else if(nx==6 && ny==5)//*					
						s[j]='*';												
					else if(nx==6 && ny==6)//'/'					
						s[j]='/'; 											
					else continue; 
					j++;
					CursorPosition(1,1);
					int sn=0;
					while(s[sn]!='\0')
						sn++;
				  	for(int i=0 ;i<sn; i++)
					{
        				printf("%c",s[i]);
    				}
    				CursorPosition(nx,ny);
				}	
									
            }
            
        }
    }
        return 0;
}



