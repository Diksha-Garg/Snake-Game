#include<stdio.h>
#include<math.h>
#include<cmath>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#define rows 25
#define cols 40
//static int s=100;
static int life=3;
static int foodIndex;
static int poisonIndex;
static int score=0;
static int mov=0;
static int dist=0;
struct poison
{
        int px,py;
    char pvalue;
};
struct food
{
    int fx,fy;
    char fvalue;
};
struct snake
{
    int x;
    int y;
    char value;
    struct snake *next;
};
int posoffood(struct snake *head,int c1,int c2)
{
    struct snake *ptr=head;
    int flag=0;
    while(ptr!=NULL)
    {
        if(c1==ptr->x || c2==ptr->y)
        {
            flag=1;
            return 1;

        }
        ptr=ptr->next;

    }
    if(flag==0)
        return 0;
}
int foodoverfood(struct food f[],int c1,int c2)
{   int flag=0;
 for(int i=0;i<4;i++)
 {
     if((c1==f[i].fx || c2==f[i].fy)){
            flag=1;
        return 1;
     }
 }
 if(flag==0)
    return 0;
}
void createfood(struct food f[],struct snake *head)
{
    int c1,c2,c3,c4, c=0;
    while(c<4){
    if(c==0){
    do{
 c1=(rand()%rows);
 c2=(rand()%cols);
 c3=posoffood(head,c1,c2);
    }while(c3!=0);
    f[c].fx=c1;
    f[c].fy=c2;
    f[c].fvalue='F';
        }
    else{
        do{
 c1=(rand()%rows);
 c2=(rand()%cols);
 c3=posoffood(head,c1,c2);
 c4=foodoverfood(f,c1,c2);
    }while(c3!=0 && c4!=0);
    f[c].fx=c1;
    f[c].fy=c2;
    f[c].fvalue='F';
    }
    c++;
}

}
int poisonoverpoison(struct poison p[],int c1,int c2)
{   int flag=0;
 for(int i=0;i<2;i++)
 {
     if((c1==p[i].px || c2==p[i].py)){
            flag=1;
        return 1;
     }
 }
 if(flag==0)
    return 0;
}
void createpoison(struct poison p[],struct snake *head,struct food f[])
{
    int c1,c2,c3,c4,c5,c=0;
    while(c<2){
    if(c==0){
    do{
 c1=(rand()%rows);
 c2=(rand()%cols);
 c3=posoffood(head,c1,c2);
  c4=foodoverfood(f,c1,c2);
    }while(c3!=0 && c4!=0);
    p[c].px=c1;
    p[c].py=c2;
    p[c].pvalue='P';

        }
    else{
        do{
 c1=(rand()%rows);
 c2=(rand()%cols);
 c3=posoffood(head,c1,c2);
 c4=foodoverfood(f,c1,c2);
 c5=poisonoverpoison(p,c1,c2);
    }while(c3!=0 && c4!=0 && c5!=0);
    p[c].px=c1;
    p[c].py=c2;
    p[c].pvalue='P';
    }
    c++;
}
}
void delay(int ms)
{
	clock_t stime=clock();
	while(clock()<stime+ms)
	{if(kbhit())
	break;
	}
}

struct snake* makofsnake(struct snake * head,struct food f[],struct poison p[])
{

 struct snake *ptr,*n;
 if(head==NULL)
 {
    n=new snake;
    n->x=3;
    n->y=4;
    n->value='$';
    n->next = NULL;
    head=n;
    ptr=head;
    //delete n;

    n=new snake;
    n->x=3;
    n->y=3;
    n->value='#';
    n->next=NULL;
    ptr->next=n;
    ptr=n;
    //delete n;

    n=new snake;
    n->x=3;
    n->y=2;
    n->value='*';
    n->next=NULL;
    ptr->next=n;
    ptr=n;
    //delete n;
 srand(time(NULL));
 createfood(f,head);
 createpoison(p,head,f);
 }
 return head;
}
/*void printofsnake(struct snake *head)
{
    struct snake *ptr=head;
    while(ptr!=NULL)
    {
        printf("%c",ptr->value);
        ptr=ptr->next;
    }

}*/
void makofbound(char bound[rows][cols],struct snake * head,struct food f[],struct poison p[])
{
  int i,j,c=0,k=0;
  for(i=0;i<rows;i++)
  {
      for(j=0;j<cols;j++)
        bound[i][j]=' ';
  }
  while(c<4){
        int a=f[c].fx;
   int b=f[c].fy;
  bound[a][b]=f[c].fvalue;
  c++;
  }
  while(k<2)
  {
      int x=p[k].px;
      int q=p[k].py;
      bound[x][q]=p[k].pvalue;
      k++;
  }
  struct snake *temp=head;
  while(temp!=NULL)
  {
      bound[temp->x][temp->y]=temp->value;
      temp=temp->next;
  }

}
void printofboard(char bound[rows][cols],struct snake *head)
{
    printf("LIFE : %d\tDISTANCE : %d\tMOVES :%d\tSCORE : %d\n",life,dist,mov,score);
    int i,j;
    for(i=0;i<=cols+1;i++)
        printf("*");
        printf("\n");
    for(i=0;i<rows;i++)
    {   printf("*");
        for(j=0;j<cols;j++)
            printf("%c",bound[i][j]);
        printf("*");
        printf("\n");
    }
for(i=0;i<=cols+1;i++)
        printf("*");

        //cout<<head->x<<"\t"<<head->y<<endl;
}
int validmove(struct snake *head,char dir)
{
    int f=1;
    int hx=head->x,hy=head->y;
    int bx=head->next->x,by=head->next->y;
   // printf("dir = %c\nhx = %d\thy = %d \n bx = %d\tby = %d\n",dir,hx,hy,bx,by);
    if(hy==by && abs(hx-bx)!=1)
    {

        if(hx==0 && bx==rows-1)
        {
            bx=-1;
        }
        else
        {
            hx=-1;
        }

    }
    else if(hx==bx && abs(hy-by)!=1)
    {
        if(hy==0 && by==cols-1)
        {
            by=-1;
        }
        else
        {
            hy=-1;
        }
    }
    if(dir!='a' && dir!='w' && dir!='s' && dir!='d' )
        return 0;
    else if(dir=='s')
    {
       if(hx == (bx-1))
            return 0;
        else
            return 1;
    }
    else if(dir=='w')
    {
        if(hx == (bx+1))
            return 0;
        else
            return 1;
    }
    else if(dir == 'a')
    {
        if(hy == (by+1 ))
            return 0;
        else
            return 1;
    }
    else if(dir == 'd')
    {

        if( hy == (by-1) )
            {
                return 0;
            }
        else
            return 1;
    }


}

char cdir(struct snake *head)
{
    int cx=head->x;
    int cy=head->y;
    int nx=head->next->x;
    int ny=head->next->y;
    if(cx==nx && abs(cy-ny)!=1)
    {
        if(cy==0 && ny==cols-1)
            ny=-1;
        else
            cy=-1;
    }
    else if(cy==ny && abs(cx-nx)!=1)
    {
        if(cx==0 && nx==rows-1)
            nx=-1;
        else
            cx=-1;
    }
    if(cx==(nx-1))
        return 'w';
    else if(cx==(nx+1))
        return 's';
    else if(cy==(ny-1))
        return 'a';
    else if(cy==(ny+1))
        return 'd';

}
void swap(int *t,int *s)
{
    int b = *t;
    *t=*s;
    *s=b;
}
int checkfood(struct food f[],struct snake *head)
{   int j=0;
int flag=0;
while(j<4){
    if((f[j].fx==head->x) && (f[j].fy == head->y)){
        flag=1;
        foodIndex=j;
       break;
    }
        else
        {
            flag=0;

        }
        j++;
}
if(flag==0)
    return 0;
    else
        return 1;
}
int checkpoison(struct poison p[],struct snake *head)
{
     int j=0;
int flag=0;
while(j<2){
    if((p[j].px==head->x) && (p[j].py == head->y)){
        flag=1;
        poisonIndex=j;
       break;
    }
        else
        {
            flag=0;

        }
        j++;
}
if(flag==0)
    return 0;
    else
        return 1;
}
struct snake* insertion(struct snake *head,int t1,int t2)
{
   if(head!=NULL)
{
          struct snake *n;
       n=new snake;
       n->x=t1;
       n->y=t2;
       n->value='*';
       n->next=NULL;
       struct snake *ptr=head;
       while(ptr->next!=NULL)
        ptr=ptr->next;
       ptr->next=n;
       ptr->value='#';
       //s=s+100;
       //cout<<score;
   }
   return head;
}
void createfoodAtIndex(struct food f[],struct snake *head)
{   int c1,c2,c3,c4;
    do{
 c1=(rand()%rows);
 c2=(rand()%cols);
  c3=posoffood(head,c1,c2);
  c4=foodoverfood(f,c1,c2);
    }while(c3!=0 && c4!=0);
    f[foodIndex].fx=c1;
    f[foodIndex].fy=c2;
    f[foodIndex].fvalue='F';
        }
void createpoisonAtIndex(struct poison p[],struct snake *head,struct food f[])
{
    int c1,c2,c3,c4,c5;
    //cout<<"One life deducted";
    do{
 c1=(rand()%rows);
 c2=(rand()%cols);
  c3=posoffood(head,c1,c2);
  c4=foodoverfood(f,c1,c2);
  c5=poisonoverpoison(p,c1,c2);
    }while(c3!=0 && c4!=0 && c5!=0);
    p[poisonIndex].px=c1;
    p[poisonIndex].py=c2;
    p[poisonIndex].pvalue='P';
}
struct snake* newsnake(struct snake *head,int pos,int pos1,struct food f[],struct poison p[])
{
    int s1=pos;
    int s2=pos1;
    struct snake *ptr=head;
    while(ptr!=NULL)
    {
        swap(&s1,&(ptr->x));
        swap(&s2,&(ptr->y));
        ptr=ptr->next;
    }
    if(checkfood(f,head))
    {
        score=score+5;
        head=insertion(head,s1,s2);
        //cout<<s<<endl;
        createfoodAtIndex(f,head);
    }
    else if(checkpoison(p,head))
    {   score=score-5;
        life--;
       // cout<<"One life deducted";
        //system("cls");
      createpoisonAtIndex(p,head,f) ;
    }
    return head;
}
void cut(struct snake *head)
{   int f=0;
    int x=head->x,y=head->y;
    struct snake *ptr=head->next;
    while(ptr!=NULL)
    {
        if((ptr->x==x)&&(ptr->y==y))
        {   life=life-1;
            f=1;
            break;
        }
        ptr=ptr->next;
    }
    if(f==1){
    struct snake *temp;
    temp=head;
    while(temp->next!=ptr)
        temp=temp->next;
        temp->value='*';
    temp->next=NULL;
    }
}
void savegame(struct snake *head,struct food f[],struct poison p[])
{
    FILE *fptr;
    fptr=fopen("diksha.txt","w");
    while(head!=NULL)
    {
        fprintf(fptr,"%d,%d,%c\n",head->x,head->y,head->value);
        head=head->next;
    }
    for(int i=0;i<4;i++)
    fprintf(fptr,"%d,%d,%d,%c\n",f[i].fx,f[i].fy,i,f[i].fvalue);
    for(int i=0;i<2;i++)
    fprintf(fptr,"%d,%d,%d,%c\n",p[i].px,p[i].py,i,p[i].pvalue);
    fprintf(fptr,"%d,%c\n",life,'L');
    fprintf(fptr,"%d,%c\n",dist,'D');
    fprintf(fptr,"%d,%c\n",mov,'M');
    fprintf(fptr,"%d,%c\n",score,'S');
    fclose(fptr);
    exit(0);

}
struct snake* moves(struct snake *head,struct food f[],struct poison p[])
{   delay(120);
   char dir;
    if(kbhit())
    {dir=getch();
    mov=mov+1;}
   else
    dir=cdir(head);
    //cin>>dir;
    if(dir=='q')
       {    char ch;
            system("cls");
           cout<<"do you want to save the game";
           cin>>ch;
           if(ch=='y'){
                cout<<"\nYOUR GAME IS SUCCESFULLY SAVED.YOU CAN PLAY IT LATER\n";
            savegame(head,f,p);

           }
            else{
                 cout<<"\nyour game is lost.You can play it later\n";
                exit(0);
            }
       }
       else if(validmove(head,dir))
   {
       dist=dist+1;
       int pos,pos1;
       pos=head->x;
       pos1=head->y;
       if(dir=='w')
       {
           pos=pos-1;
           if(pos<0)
            pos=rows-1;
       }
       else if(dir=='s')
       {
           pos=pos+1;
           if(pos>=rows)
            pos=0;
       }
       else if(dir=='a')
       {
           pos1=pos1-1;
           if(pos1<0)
            pos1=cols-1;
       }
       else if(dir=='d')
       {
           pos1=pos1+1;
           if(pos1>=cols)
            pos1=0;
       }

       head=newsnake(head,pos,pos1,f,p);
    cut(head);
   }

   else
   {
       printf("Invalid dir");
       head=moves(head,f,p);
   }
   return head;
}
struct snake* createSnakeFromFile(struct snake* head,int x,int y,char value)
{
    struct snake *n,*ptr=head;
    if(head==NULL)
    {
        n=new snake;
    n->x=x;
    n->y=y;
    n->value=value;
    n->next = NULL;
    head=n;
    ptr=head;
    }
    else{
       n=new snake;
    n->x=x;
    n->y=y;
    n->value=value;
    n->next = NULL;
    while(ptr->next!=NULL)
        ptr=ptr->next;
    ptr->next=n;
    ptr=n;
    }

    return head;
};

void createFoodFromFile(struct food f[],int x,int y,int i,char value)
{
    f[i].fx=x;
    f[i].fy=y;
    f[i].fvalue=value;
}

void createPoisonFromFile(struct poison p[],int x,int y,int i,char value)
{
    p[i].px=x;
    p[i].py=y;
    p[i].pvalue=value;
}
struct snake * oldGame(struct snake*head, struct food *f,struct poison p[])
{
    int temp,x,y,count=0,i=0;
    char value,ch;
    char save[30];
    FILE *fptr;
    fptr=fopen("diksha.txt","r");
    ch=fgetc(fptr);
       while(ch!=EOF)
       {
           if(ch=='\n')
           {
               //cout<<x<<" "<<y<<" "<<value<<endl;
               if(value!='F' && value!='P' && value!='D'&& value!='S'&& value!='L'&& value!='M')
               {
                   head=createSnakeFromFile(head,x,y,value);

               }
               else if(value=='F')
                createFoodFromFile(f,x,y,temp,value);
                else if(value=='P')
                  createPoisonFromFile(p,x,y,temp,value);
                  else if(value=='L')
                    life=x;
                    else if(value=='S')
                        score=x;
                    else if(value=='D')
                        dist=x;
                    else if(value=='M')
                        mov=x;
               count=0;
               ch=fgetc(fptr);
               continue;
           }
           else if(ch!=',')
           {
               if(ch>='a' && ch<='z' || ch>='A' && ch<='Z' || ch=='$' || ch=='*' || ch=='#')
                value=ch;
               else{
                save[i]=ch;
                i++;
               }
           }
           else
           {
               save[i]='\0';
               i=0;
               int result=atoi(save);
               if(count==0)
               {
                   x=result;
                   count++;
               }
               else if(count==1)
               {
                   y=result;
                   count++;
               }
               else if(count ==2)
               {
                   temp=result;
                   count++;
               }
           }
           ch=fgetc(fptr);
    }
    fclose(fptr);
    return head;
};
int main()
{
    struct food f[4];
    struct poison p[2];
    struct snake *head=NULL;
    int choice;
    char ch;
    printf("\n----------------------------WELCOME TO SNAKE GAME-------------------------------\n");
    printf("INSTRUCTIONS:");
    printf("\n * There are total 3 lifes at starting of new game");
    printf("\n * After eating food 5 points will be increased in your score");
    printf("\n * After eating poison 5 points will be deducted from score nd one life will be decremented");
    printf("\n * If snake cuts itelf one life gets reduced and length of snake gets reduced");
    printf("\n * PRESS 1 for a new game");
    printf("\n * PRESS 0 for saved game");

    printf("\nEnter your choice");
    cin>>choice;
 system("cls");
    if(choice==1)
        head=makofsnake(head,f,p);
    else if(choice ==0){
            FILE *fptr;
    fptr=fopen("diksha.txt","r");
    ch=fgetc(fptr);
    if(ch==EOF){
        cout<<"\nThere is no saved game.Enjoy ur new game\n";
        cout<<"Press any key to continue";
        getch();
        head=makofsnake(head,f,p);
    }
    else
        head=oldGame(head,f,p);
    }
    //printofsnake(head);
    char bound[rows][cols];
    while(life>0){
    makofbound(bound,head,f,p);
    printofboard(bound,head);
    head=moves(head,f,p);
    system("cls");
    }
    cout<<"Game over";
    cout<<"\nYour final score is"<<score;
    FILE *fptr;
    fptr=fopen("diksha.txt","w");
    fclose(fptr);

    return 0;
}
