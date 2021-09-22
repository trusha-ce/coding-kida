#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#define max 6

int a[max]={0},b[max]={0},c[max]={0},ta=-1,tb=-1,tc=-1;
int x1,x2,x3,y1,y2,mx,my,diff,dx,dy,dyy,d[max][3],step=0;

void push(int[],int*,int);
int pop(int[],int*);
void tower(int,int[],int*,int[],int*,int[],int*);
void display();

void main()
{
	int gd=DETECT,gm,nd,i;

    //--------------------initialize graphics
	initgraph(&gd,&gm,"C:\\bgi");

	//--------------------input number of disk in tower
	printf("Enter number of disk :--> ");
	scanf("%d",&nd);

	//--------------------calculate disk dimension
	mx=getmaxx();
	my=getmaxy();

	x1=mx/4;
	x2=mx/2;
	x3=3*mx/4;
	y1=my/4;
	y2=my/2;

	setcolor(WHITE);
	diff=10;
	for(i=1;i<=nd;i++)
	{
		dx=diff*i;
		dy=diff*(nd-i+1);
		dyy=diff*(nd-i);

		d[i-1][0]=-dx;
		d[i-1][1]=+dx;
		d[i-1][2]=i;
	}

	for(i=nd-1;i>=0;i--)
	{
		push(a,&ta,i+1);
	}

	display();
	delay(1000);
	tower(nd,a,&ta,b,&tb,c,&tc);

	getch();
}

//--------------------push operation
void push(int s[], int *top, int disk)
{
	*top=*top+1;
	s[*top]=disk;
}

//--------------------pop operation
int pop(int s[], int *top)
{
	int disk;
	disk=s[*top];
	s[*top]=0;
	*top=*top-1;
	return disk;
}

//--------------------tower of hanoi logic
void tower(int n,int s[],int *ts,int t[],int *tt,int d[], int *td)
{
	if(n==1)
	{
		push(d,td,pop(s,ts));
		display();
		delay(1000);
	}
	else if(n>1)
	{
		tower(n-1,s,ts,d,td,t,tt);
		push(d,td,pop(s,ts));
		display();
		delay(1000);
		tower(n-1,t,tt,s,ts,d,td);
	}
}

//--------------------display disk
void display()
{
	int i,j;

	clrscr();
	cleardevice();

	printf("Step :--> %d",step++);

	setcolor(RED);
	line(x1,y1,x1,y2);
	setcolor(YELLOW);
	line(mx/2,my/4,mx/2,my/2);
	setcolor(GREEN);
	line(3*mx/4,my/4,3*mx/4,my/2);
//	setcolor(WHITE);
//	line(0,my/2,mx,my/2);

	setcolor(WHITE);
	for(i=0;i<=ta;i++)
	{
		j=a[i]-1;
		setfillstyle(SOLID_FILL,d[j][2]);
		rectangle(x1+d[j][0],y2-(diff*(i+1)),x1+d[j][1],y2-(diff*i));
		floodfill(x1+d[j][0]+2,y2-(diff*(i+1))+2,WHITE);
	}
	for(i=0;i<=tb;i++)
	{
		j=b[i]-1;
		setfillstyle(SOLID_FILL,d[j][2]);
		rectangle(x2+d[j][0],y2-(diff*(i+1)),x2+d[j][1],y2-(diff*i));
		floodfill(x2+d[j][0]+2,y2-(diff*(i+1))+2,WHITE);
	}
	for(i=0;i<=tc;i++)
	{
		j=c[i]-1;
		setfillstyle(SOLID_FILL,d[j][2]);
		rectangle(x3+d[j][0],y2-(diff*(i+1)),x3+d[j][1],y2-(diff*i));
		floodfill(x3+d[j][0]+2,y2-(diff*(i+1))+2,WHITE);
	}
       //	outtextxy(mx/2,3*my/4,++step);
}
