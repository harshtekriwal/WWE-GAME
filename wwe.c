
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<windows.h>
#define DECK_SIZE 8

int victory;
int playgame(float,float, int,int);
void showHand();
//My Card Class
struct card
{
    char ar[20];
    float defence;
    float attack;
    float weight;
    float speed;
};
struct card wrestler[DECK_SIZE];

struct player
{
    char name[20];
    char pass[10];
    struct card collection[DECK_SIZE];
    int numCards;
    float win;
    float loss;
    float wlRatio;
    struct player *next;

} currentData,*players;

void reg()
{
    Sleep(30);
    system("CLS");
    FILE *fp;
    struct player pin;
    fp=fopen("DATA.TXT","ab+");
    if(fp==NULL)
    {
        printf("\n  UNABLE TO REGISTER YOUR ACCOUNT.. Sorry Try again later. ");
        getch();
        return;
    }
    pin.numCards=0;
    pin.loss=0;
    pin.win=0;
    pin.wlRatio=100;
    printf("\n ENTER USERNAME :");
    scanf("%s",pin.name);
    printf("\n ENTER PASSWORD LESS  THAN 8 CHARS : ");
    char ch;
    int i=0;
    do
    {
        ch=getch();
        if(ch==8)
        {
            if(i==0)
            {
                continue;
            }
            printf("\b");
            i=i-1;
            continue;
        }
        if(i==0&&ch==13)
        {
            printf("\n Enter atleast 1 character for password....");
            getch();
            fclose(fp);
            return;
        }
        if(ch==13)
        {
            break;
        }
        printf("*");
        pin.pass[i]=ch;
        i++;
    }
    while(ch!=13);
    if(i>7)
    {
        printf("\n Password is too big....");
        getch();
        fclose(fp);
        return;
    }
    pin.pass[i]='\0';
    struct player pp;
    fseek(fp, 0, SEEK_SET);
    while(!feof(fp))
    {
        fread(&pp,sizeof(struct player),1,fp);
        if(strcmpi(pin.name,pp.name)==0)
        {
            printf("\n \n An account with that name already Exists...");
            getch();
            fclose(fp);
            return;
        }
        else
        {
            continue;
        }
    }
    fwrite(&pin,sizeof(struct player),1,fp);
    printf("\n Account Successfully Registered....");
    printf("\n Press Any key to continue..");
    getch();
    fclose(fp);
    return;
}

int login()
{
    Sleep(30);
    int s=0;
    system("CLS");
    FILE *fp;
    fp=fopen("DATA.TXT","rb");
    if(fp==NULL)
    {
        printf("\n First Register your account..");
        getch();
        return s;
    }
    char username[20];
    char password[10];
    printf("\n  ENTER YOUR NAME :");
    scanf("%s",username);
    printf("\n  ENTER YOUR PASSWORD :");
    int i=0;
    char c;
    for(i=0; i<8; i++)
    {
        c=getch();
        if(c==13)
        {
            break;
        }
        else if(c==8)
        {
            if(i==0)
            {
                i=i-1;
                continue;
            }
            printf("\b");
            i=i-2;
            continue;
        }
        else
        {
            password[i]=c;
            printf("*");
        }
    }
    password[i]='\0';
    while(!feof(fp))
    {
        fread(&currentData,sizeof(struct player),1,fp);
        if(strcmpi(currentData.name,username)==0)
        {
            if(strcmpi(currentData.pass,password)==0)
            {
                Sleep(120);

                printf("\n \n Congrats Login Success..");
                printf("\n \n No of Cards in your deck are:-  %d",currentData.numCards);
                printf("\n \n Enter any Key to start the game...");
                getch();
                s=1;
                system("CLS");
                printf("  Welcome to the game user %s",currentData.name);
                fclose(fp);
                return s;
            }
            else
            {
                printf("\n Incorrect Password...");
                getch();
                fclose(fp);
                return  s;
            }
        }
        else
        {
            continue;
        }
    }
    printf("\n  No account with that username exists...");
    getch();
    fclose(fp);
    return  s;
}

void lboard()
{
    players=NULL;
    FILE *fp;
    fp=fopen("DATA.TXT","rb");
    if(!fp)
    {
        system("CLS");
        printf("\n No account Exists....");
        getch();
        return;
    }
    struct player pin;
    fread(&pin,sizeof(struct player),1,fp);
    while(!feof(fp))
    {
        struct player *temp=(struct player *)malloc(sizeof(struct player));
        strcpy(temp->name,pin.name);
        temp->loss=pin.loss;
        temp->win=pin.win;
        temp->wlRatio=pin.wlRatio;
        temp->numCards=pin.numCards;
        strcpy(temp->pass,pin.pass);
        temp->next=NULL;
        if(players==NULL)
        {
            players=temp;
        }
        else
        {
            temp->next=players;
            players=temp;
        }
        fread(&pin,sizeof(struct player),1,fp);
    }
    getch();
    fclose(fp);
}

void dplay(int num)
{
    if(players==NULL)
    {
        printf("\n No Account exists");
        return;
    }
    system("CLS");
    struct player *temp=NULL;
    temp=players;
    int i=1;
    if(num==1)
    {    printf(" \n \t \t MOST NO OF WINS.");
        while(temp!=NULL)
        {
            printf("\n \n %d. User name :- %s",i,temp->name);
            printf("\n No of wins :- %d",(int)temp->win);
            temp=temp->next;
            i++;
        }
    }
    else if(num==2)
    {   printf(" \n \t \t MOST NO Of LOSS.");
        while(temp!=NULL)
        {
            printf("\n \n %d. User name :- %s",i,temp->name);
            printf("\n No of Losses :- %d",(int)temp->loss);
            temp=temp->next;
            i++;
        }
    }
    else if(num==3)
    {
        printf(" \n \t \t Best win/loss percentage.");
        while(temp!=NULL)
        {
            printf("\n \n %d. User name :- %s",i,temp->name);
            if(temp->loss==0&&temp->win==0)
            {
                printf("\n   Win Loss Percentage :- 100" );
                printf("%%");
            }
            else if(temp->loss==0)
            {
                printf("\n   Win Loss Percentage :- Infinity" );
            }
            else
            {
                printf("\n   Win Loss Percentage %d ",(int)temp->wlRatio);
                printf("%%");
            }
            temp=temp->next;
            i++;
        }
    }
}

void sort_max()
{
    if(players==NULL)
    {
        printf("\n No account yet.");
        return;
    }
    struct player *temp=players;
    struct player *temp2 = NULL;
    struct player *temp3 = (struct player*)malloc(sizeof(struct player));
    while(temp!=NULL)
    {
        temp2=temp->next;
        while(temp2!=NULL)
        {
            if(temp2->win>temp->win)
            {
                temp3->loss=temp2->loss;
                temp3->win=temp2->win;
                strcpy(temp3->name,temp2->name);
                temp2->loss=temp->loss;
                temp2->win=temp->win;
                strcpy(temp2->name,temp->name);
                temp->loss=temp3->loss;
                temp->win=temp3->win;
                strcpy(temp->name,temp3->name);
            }
            temp2=temp2->next;
        }
        temp=temp->next;
    }
    return;
}

void sort_min()
{
    if(players==NULL)
    {
        printf("\n No account yet.");
        return;
    }
    struct player *temp=players;
    struct player *temp2 = NULL;
    struct player *temp3 = (struct player*)malloc(sizeof(struct player));
    while(temp!=NULL)
    {
        temp2=temp->next;
        while(temp2!=NULL)
        {
            if(temp2->loss>temp->loss)
            {
                temp3->loss=temp2->loss;
                temp3->win=temp2->win;
                strcpy(temp3->name,temp2->name);
                temp2->loss=temp->loss;
                temp2->win=temp->win;
                strcpy(temp2->name,temp->name);
                temp->loss=temp3->loss;
                temp->win=temp3->win;
                strcpy(temp->name,temp3->name);
            }
            temp2=temp2->next;
        }
        temp=temp->next;
    }
    return;
}

void sort_winloss()
{
    if(players==NULL)
    {
        printf("\n No account yet.");
        return;
    }
    struct player *temp=players;
    struct player *temp2 = NULL;
    struct player *temp3 = (struct player*)malloc(sizeof(struct player));
    while(temp!=NULL)
    {
        temp2=temp->next;
        while(temp2!=NULL)
        {
            if(temp2->wlRatio>temp->wlRatio)
            {
                temp3->wlRatio=temp2->wlRatio;
                temp3->loss=temp2->loss;
                temp3->win=temp2->win;
                strcpy(temp3->name,temp2->name);

                temp2->loss=temp->loss;
                temp2->wlRatio=temp->wlRatio;
                temp2->win=temp->win;
                strcpy(temp2->name,temp->name);

                temp->loss=temp3->loss;
                temp->win=temp3->win;
                strcpy(temp->name,temp3->name);
                temp->wlRatio=temp3->wlRatio;
            }
            temp2=temp2->next;
        }
        temp=temp->next;
    }
    return;
}
struct card rcard()
{
    int i;
    struct card temp;
    srand(time(NULL));
    for(i=DECK_SIZE-1; i>=1; i--)
    {
        int num=(rand()%(i+1));
        if(i==num)
        {
            continue;
        }
        temp=wrestler[num];
        wrestler[num]= wrestler[i];
        wrestler[i]=temp;
    }
    return wrestler[0];
}
void addcard()
{
    system("CLS");
    struct player pp;
    FILE *fp;
    fp=fopen("DATA.TXT","r+b");
    currentData.win=currentData.win+1;
    currentData.wlRatio=((currentData.win/currentData.loss)*100);
    int k=currentData.numCards-1;
    while(!feof(fp))
    {
        fread(&pp,sizeof(struct player),1,fp);
        if(strcmpi(currentData.name,pp.name)==0)
        {
            currentData.collection[k]=rcard();
            Sleep(80);
            printf("\n Added card %s  to your Collection", currentData.collection[k].ar);
            printf("\n No Of Cards in Your collection are:-  %d",currentData.numCards);
            getch();
            fseek(fp,-(sizeof(struct player)),SEEK_CUR);
            fwrite(&currentData,sizeof(struct player),1,fp);
            break;
        }
        else
            continue;
    }
    fclose(fp);
}
void delcard()
{
    struct player pp;
    currentData.loss=currentData.loss+1;
    currentData.wlRatio=((currentData.win/currentData.loss)*100);
    system("CLS");
    FILE *fp;
    fp=fopen("DATA.TXT","r+b");
    while(!feof(fp))
    {
        fread(&pp,sizeof(struct player),1,fp);
        if(strcmpi(currentData.name,pp.name)==0)
        {
            if(currentData.numCards<=0)
            {
                printf("\n NO CARD CAN BE DELETED FROM YOUR COLLECTION");
                fseek(fp,-sizeof(struct player),1);
                fwrite(&currentData,sizeof(struct player),1,fp);
                Sleep(80);
                fclose(fp);
                return;
            }
            currentData.numCards=currentData.numCards-1;
            fseek(fp,-sizeof(struct player),1);
            fwrite(&currentData,sizeof(struct player),1,fp);
            Sleep(80);
            printf("\n Deleted card %s from your collection",currentData.collection[currentData.numCards].ar);
            getch();
            break;
        }
        else

            continue;
    }
    fclose(fp);
}
struct node
{
    struct card obj;
    struct node *next;
};

struct player1
{
    struct node *top;
    struct node *rear;
};

struct player2
{
    struct node *top;
    struct node *rear;

};
struct player2 p2= {NULL,NULL};
struct player1 p1= {NULL,NULL};

void addcardp1(struct card wrest)
{
    struct node *temp;
    temp= (struct node*)malloc(sizeof(struct node));
    temp->obj=wrest;
    temp->next=NULL;
    if(p1.rear==NULL)
    {
        p1.top=temp;
        p1.rear=temp;
    }
    else
    {
        p1.rear->next=temp;
        p1.rear=temp;
    }
}
void addcardp2(struct card wrest)
{
    struct node *temp = (struct node*)malloc(sizeof(struct node));
    temp->obj=wrest;
    temp->next=NULL;
    if(p2.rear==NULL)
    {
        p2.top=temp;
        p2.rear=temp;
    }
    else
    {
        p2.rear->next=temp;
        p2.rear=temp;
    }
}
void delcardp1()
{
    if(p1.top!=NULL)
    {
        struct node *temp;
        temp=p1.top;
        p1.top=p1.top->next;
        free(temp);
        if(p1.top==NULL)
        {
            p1.rear=NULL;
        }
    }

}
void delcardp2()
{
    if(p2.top!=NULL)
    {
        struct node *temp;
        temp=p2.top;
        p2.top=p2.top->next;
        free(temp);
        if(p2.top==NULL)
        {
            p2.rear=NULL;
        }
    }

}
void addcardlastp1()
{
    struct card temp=p1.top->obj;
    delcardp1();
    addcardp1(temp);
}

void addcardlastp2()
{
    struct card temp=p2.top->obj;
    delcardp2();
    addcardp2(temp);
}


void shuffle()
{
    // Shuffling d deck
    printf("\n  SHUFFLING CARDS!!!!.. ");
    int i;
    struct card temp;
    srand(time(NULL));
    for(i=DECK_SIZE-1; i>0; i--)
    {
        int num=(rand()%(i+1));
        temp=wrestler[num];
        wrestler[num]= wrestler[i];
        wrestler[i]=temp;
    }

}

float avgatk()
{
    int i;
    float sum=0;
    for(i=0; i<DECK_SIZE; i++)
    {
        sum+=wrestler[i].attack;
    }
    return sum/DECK_SIZE;
}

float avgspeed()
{
    int i;
    float sum=0;
    for(i=0; i<DECK_SIZE; i++)
    {
        sum+=wrestler[i].speed;
    }
    return sum/DECK_SIZE;
}
float avgdef()
{
    int i;
    float sum=0;
    for(i=0; i<DECK_SIZE; i++)
    {
        sum+=wrestler[i].defence;
    }
    return sum/DECK_SIZE;
}

float avgweight()
{
    int i;
    float sum=0;
    for(i=0; i<DECK_SIZE; i++)
    {
        sum+=wrestler[i].weight;
    }
    return sum/DECK_SIZE;
}



float maxo(float z1,float z2, float z3, float z4)
{
    float max1, max2,max;
    if(z1>z2)
        max1=z1;
    else
        max1=z2;
    if(z3>z4)
        max2=z3;
    else
        max2=z4;

    if(max1>max2)
        max=max1;

    else
        max=max2;
    return max;

}

float minimum(float z1,float z2,float z3,float z4)
{
    float min1, min2,min;
    if(z1>z2)
    {
        min1=z2;
    }
    else
        min1=z1;
    if(z3>z4)
    {
        min2=z4;
    }
    else
        min2=z3;

    if(min1>min2)
    {
        return min1;
    }
    else
        return min2;
}

float moderate(float z1,float z2, float z3, float z4)
{

    float max1, max2,max;
    if(z1>z2)
        max1=z1;
    else
        max1=z2;
    if(z3>z4)
        max2=z3;
    else
        max2=z4;

    if(max1>max2)
        return max2;

    else
        return max1;

}
int decide(int level)
{
    float n1,n2,n3,n4;
    n1=p1.top->obj.attack;
    n2=p1.top->obj.defence;
    n3=p1.top->obj.speed;
    n4=p1.top->obj.weight;

    n1=((n1-avgatk())/avgatk())*100;
    n2=((n2-avgdef())/avgdef())*100;
    n3=((n3-avgspeed())/avgspeed())*100;
    n4=((n4-avgweight())/avgweight())*100;

    float maxim;

    if(level==3)
    {
    maxim= maxo(n1,n2,n3,n4);
    if (maxim==n1)
    {
        return 1;
    }

    else if (maxim==n2)
    {
        return 2;
    }
    else if (maxim==n3)
    {
        return 3;
    }
    else if (maxim==n4)
    {
        return 4;
    }
    }

    if(level==2)
    {
     maxim= moderate(n1,n2,n3,n4);
    if (maxim==n1)
    {
        return 1;
    }

    else if (maxim==n2)
    {
        return 2;
    }
    else if (maxim==n3)
    {
        return 3;
    }
    else if (maxim==n4)
    {
        return 4;
    }
    }

    if(level==1)
    {
     maxim= minimum(n1,n2,n3,n4);
    if (maxim==n1)
    {
        return 1;
    }

    else if (maxim==n2)
    {
        return 2;
    }
    else if (maxim==n3)
    {
        return 3;
    }
    else if (maxim==n4)
    {
        return 4;
    }
    }
}
int clash(float var1,float var2, int k,int lvl)
{
    int u;
    struct card temp1;
    struct card temp2;
    temp1=p1.top->obj; ;
    temp2=p2.top->obj;
    delcardp1();
    delcardp2();
    if(p1.rear==NULL&&p2.rear==NULL)
    {
        printf(" \n\n Damnn... Its a tie, ;( The game ends in a tie...");
        printf("\n \n Press any key to continue..");
        getch();
        victory=3;
        return 0;
    }
    if(p1.rear==NULL)
    {
        printf("\n\n CPU DOSENT HAVE ANY CARD LEFT AND HAS LOST THE GAME.!!");
        printf("\n \n Press any key to continue..");
        getch();
        victory=1;
        return 0;
    }
    else if(p2.rear==NULL)
    {
        printf("\n\n YOU DONT EVEN HAVE A CARD HAHAHHA LOST IT... ");
        printf("\n \n Press any key to continue..");
        getch();
        victory=2;
        return 0;
    }
    if(k==1)
    {
        getch();
        system("CLS");
        printf("\n\n ITS CPUS TURN AGAIN:");
        if(decide(lvl)==1)
        {
            printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
            printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
            printf(" \n\n CPU CHOOSES ATTACK = %f",p1.top->obj.attack);
            printf(" \n\n YOUR ATTACK IS = %f",p2.top->obj.attack);
            u=playgame(p1.top->obj.attack, p2.top->obj.attack,k,lvl);
        }

        else if(decide(lvl)==2)
        {
            printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
            printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
            printf("\n\n CPU CHOOSES DEFENCE = %f",p1.top->obj.defence);
            printf(" \n\n YOUR DEFENCE IS = %f",p2.top->obj.defence);
            u=playgame(p1.top->obj.defence, p2.top->obj.defence,k,lvl);

        }
        else if(decide(lvl)==3)
        {
            printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
            printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
            printf(" \n\n CPU CHOOSES SPEED = %f",p1.top->obj.speed);
            printf("\n \n YOUR SPEED IS = %f",p2.top->obj.speed);
            u=playgame(p1.top->obj.speed, p2.top->obj.speed,k,lvl);
        }

        else if(decide(lvl)==4)
        {
            printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
            printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
            printf(" \n\n CPU CHOOSES WEIGHT = %f",p1.top->obj.weight);
            printf(" \n\n YOUR WEIGHT IS = %f",p2.top->obj.weight);
            u=playgame(p1.top->obj.weight, p2.top->obj.weight,k,lvl);
        }
    }
    else if(k==2)
    {
        getch();
        system("CLS");
        printf("\n\n ITS YOUR TURN AGAIN USER:");
        int ch;
        printf("\n\n NAME   : %s",p2.top->obj.ar);
        printf("\n\n 1.ATTACK : %f",p2.top->obj.attack);
        printf("\n\n 2.DEFENCE: %f",p2.top->obj.defence);
        printf("\n\n 3.SPEED  : %f",p2.top->obj.speed);
        printf("\n\n 4.WEIGHT : %f",p2.top->obj.weight);
        printf("\n\n ENTER YOUR CHOICE:");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
        {
            printf(" \n CPU CHOOSES ATTACK = %f",p1.top->obj.attack);
            u=playgame(p1.top->obj.attack, p2.top->obj.attack,k,lvl);
            break;

        }
        case 2:
        {
            printf(" \n CPU CHOOSES DEFENCE = %f",p1.top->obj.defence);
            u=playgame(p1.top->obj.defence, p2.top->obj.defence,k,lvl);
            break;
        }
        case 3:
        {
            printf(" \n CPU CHOOSES SPEED = %f",p1.top->obj.speed);
            u=playgame(p1.top->obj.speed, p2.top->obj.speed,k,lvl);
            break;
        }
        case 4:
        {
            printf(" \n CPU CHOOSES WEIGHT = %f",p1.top->obj.weight);
            u=playgame(p1.top->obj.weight, p2.top->obj.weight,k,lvl);
            break;
        }

        }
        if(u==2)
        {
            printf("\n\n USER WON THE CLASH.");
            addcardp2(temp2);
            addcardp2(temp1);
            return u;
        }
    }
    if(u==1)
    {
        printf("\n \n CPU WON THE CLASH.");
        addcardp1(temp1);
        addcardp1(temp2);
        return u;
    }
}
void delf()
{
    struct node *temp=p1.top;
    while(p1.top!=NULL)
    {
        free(temp);
        p1.top=p1.top->next;
    }
    p1.rear=p1.top;
    struct node *temp2=p2.top;
    while(p2.top!=NULL)
    {
        free(temp2);
        p2.top=p2.top->next;
    }
    p2.rear=p2.top;
}
void playthegame(int lvl)
{
    int ret=10;
    srand(time(NULL));
    int k=rand()%2;
    int ch;
    int toss;
    printf("\n \n  Enter 0 for head or 1 for  tail:");
    scanf(" %d",&ch);
    printf("\n  FLIPPING THE COIN.");
    int i=0;
    for(i=0; i<15; i++)
    {
        Sleep(80);
        printf(".");
    }
    if(k!=ch)
    {
        printf("\n \n  YOU LOST THE TOSS...");
        toss=1;
    }
    else if(k==ch)
    {
        printf("\n \n  CONGRATS YOU WON THE TOSS...");
        toss=2;
    }
    getch();
    int turn=0;
    while(p1.rear!=NULL && p2.rear!=NULL)
    {
        system("CLS");
        printf("\n 1.NEXT TURN.");
        printf("\n 2.SHOW HAND.");
        int ch;
        printf("\n ENTER YOUR CHOICE.");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
        {
            getch();
            system("cls");
            ++turn;
            printf(" \n TURN NO :  %d ",turn);
            if(ret==1||toss==1)
            {
                toss=5;
                ret =1;
                printf("\n\n CPU will move first: ");
                if(decide(lvl)==1)
                {
                    printf("\n \n CPU'S CARD IS  is %s",p1.top->obj.ar);
                    printf(" \n\n USERS CARD IS  is %s",p2.top->obj.ar);
                    printf(" \n\n CPU CHOOSES ATTACK = %f",p1.top->obj.attack);
                    printf(" \n\n YOUR ATTACK IS = %f",p2.top->obj.attack);
                    ret=playgame(p1.top->obj.attack, p2.top->obj.attack,ret,lvl);
                }
                else if(decide(lvl)==2)
                {
                    printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
                    printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
                    printf("\n\n CPU CHOOSES DEFENCE = %f",p1.top->obj.defence);
                    printf("\n\n YOUR DEFENCE IS = %f",p2.top->obj.defence);
                    ret=playgame(p1.top->obj.defence, p2.top->obj.defence,ret,lvl);
                }

                else if(decide(lvl)==3)
                {
                    printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
                    printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
                    printf(" \n\n CPU CHOOSES SPEED = %f",p1.top->obj.speed);
                    printf(" \n\n YOUR SPEED IS = %f",p2.top->obj.speed);
                    ret=playgame(p1.top->obj.speed, p2.top->obj.speed,ret,lvl);
                }

                else if(decide(lvl)==4)
                {
                    printf("\n\n CPU'S CARD IS  is %s",p1.top->obj.ar);
                    printf("\n\n USERS CARD IS  is %s",p2.top->obj.ar);
                    printf(" \n\n CPU CHOOSES WEIGHT = %f",p1.top->obj.weight);
                    printf(" \n\n YOUR WEIGHT IS = %f",p2.top->obj.weight);
                    ret=playgame(p1.top->obj.weight, p2.top->obj.weight,ret,lvl);
                }
            }
            else if(ret==2||toss==2)
            {
                toss=5;
                ret=2;
                int ch;
                printf(" \n Its your turn.. ");
                printf("\n\n NAME   : %s",p2.top->obj.ar);
                printf("\n\n 1.ATTACK : %f",p2.top->obj.attack);
                printf("\n\n 2.DEFENCE: %f",p2.top->obj.defence);
                printf("\n\n 3.SPEED  : %f",p2.top->obj.speed);
                printf("\n\n 4.WEIGHT : %f",p2.top->obj.weight);
                printf("\n\n ENTER YOUR CHOICE:");
                scanf("%d",&ch);
                switch(ch)
                {
                case 1:
                {
                    printf(" \n \n CPU CHOOSES ATTACK = %f",p1.top->obj.attack);
                    ret=playgame(p1.top->obj.attack, p2.top->obj.attack,ret,lvl);
                    break;
                }
                case 2:
                {
                    printf(" \n\n  CPU CHOOSES DEFENCE = %f",p1.top->obj.defence);
                    ret=playgame(p1.top->obj.defence, p2.top->obj.defence,ret,lvl);
                    break;
                }
                case 3:
                {
                    printf(" \n\n  CPU CHOOSES SPEED = %f",p1.top->obj.speed);
                    ret=playgame(p1.top->obj.speed, p2.top->obj.speed,ret,lvl);
                    break;
                }
                case 4:
                {
                    printf(" \n\n CPU CHOOSES WEIGHT = %f",p1.top->obj.weight);
                    ret=playgame(p1.top->obj.weight, p2.top->obj.weight,ret,lvl);
                    break;
                }
                }
            }
            getch();
            break;
        }
        case 2:
        {
            system("CLS");
            showHand();
            getch();
            break;
        }
        }
    }
}
void distribute()
{
    int i;
    for(i=0; i<DECK_SIZE/2; i++)
    {
        addcardp1(wrestler[i]);
    }
    for(i=DECK_SIZE/2; i<DECK_SIZE; i++)
    {
        addcardp2(wrestler[i]);
    }
    printf("\n \n  Distributing.");
    i=0;
    for(i=0; i<15; i++)
    {
        Sleep(80);
        printf(".");
    }
    printf("\n \n  Cards Distributed Successfully...");
    Sleep(200);
}

void loader()
{
    int i;
    system("cls");
    printf("\n \t\t\t\t\tPlease wait loading....\n");
    system("COLOR 0");
    printf("\n\n\t\t\t");
    for(i=0; i<60; i++)
    {
        Sleep(50);
        printf("%c",219);
    }

}
void initWrestlers()
{
    FILE* file = fopen("wrestlers.txt", "r");
    char line[256];
    int index = 0;
    while (fgets(line, sizeof(line), file)) {
        //printf("%s\n", line);
        parse(line, index);
        index++;
    }
    fclose(file);
}
void parse(char* line, int index)
{
    char *data;

    data = strtok(line, ",");
    strcpy(wrestler[index].ar, data);

    data = strtok (NULL, ",");
    wrestler[index].defence = atof(data);

    data = strtok (NULL, ",");
    wrestler[index].attack = atof(data);

    data = strtok (NULL, ",");
    wrestler[index].weight = atof(data);

    data = strtok (NULL, ",");
    wrestler[index].speed = atof(data);
}
int startGame()
{
    players=NULL;
    initWrestlers();
    loader();
    system("cls");
    printf("\n \n \t \t \t \t \t Content loaded successfully");
    printf("\n \n \t \t \t \t \tWELCOME TO THE WWE TRUMP CARD GAME!!! \n");
    printf("\n\nPress Any Key to Continue:-");
    getch();
    int choice;
    char ans='y';
    do
    {
        system("CLS");
        system("COLOR 0");
        printf("\n 1.REGISTER :");
        printf("\n 2.LOGIN :");
        printf("\n 3.Rankings:");
        printf("\n 4.Exit:");
        printf("\n ENTER YOUR CHOICE :");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
        {
            reg();
            break;

        }
        case 2:
        {
            int r;
            r=login();
            if(r==1)
            {

                int ch;
                do
                {
                    system("CLS");
                    printf("\n1.PLAY GAME:-");
                    printf("\n2 Check Your COLLECTION");
                    printf("\n3. How to play");
                    printf("\n4.Logout:-");
                    printf("\nENTER YOUR CHOICE:");
                    scanf("%d",&ch);
                    switch(ch)
                    {
                    case 1:
                    {
                        int diff;
                        system("CLS");
                        printf("\n Choose Difficulty:-");
                        printf("\n1.Easy");
                        printf("\n2.Moderate");
                        printf("\n3.Difficult");
                        printf("\n Enter your choice:-");
                        scanf("%d",&diff);
                        system("CLS");
                        delf();
                        shuffle();
                        distribute();
                        playthegame(diff);
                        if(victory==1)
                        {
                            currentData.numCards=currentData.numCards+1;
                            addcard();
                            getch();
                        }
                        else if(victory==2)
                        {
                            delcard();
                            getch();
                        }
                        else if(victory==3)
                        {
                            printf("\n NO GAIN OR LOSS IN TIE!");
                            getch();
                        }
                        break;
                    }
                    case 2:
                    {
                        system("CLS");
                        int counter=0;
                        if(currentData.numCards==0)
                        {
                            printf("\n YOU HAVE NO CARD IN YOUR COLLECTION..");
                            getch();
                            break;
                        }
                        for(counter=0; counter<currentData.numCards; counter++)
                        {
                            printf("\n");
                            puts(currentData.collection[counter].ar);

                        }
                        getch();
                        break;
                    }
                    case 3:
                    {
                        system("CLS");
                        printf("\t\t\t\t HOW TO PLAY THE GAME:-");
                        printf("\n \n The game will be between USER and Computer, Both Player's will be given 5-5 cards each randomly.");
                        printf("\n Each card has 4 Stats:-ATTACK,DEFENCE,SPEED,WEIGHT. The One with greater Stat will win the turn.");
                        printf("\n and gain the card , whereas other will loose the card. The one who has empty hand first looses the game.");
                        printf("\n If there is a clash the winner of that turn will be decided by the winner of the next turn. ");
                        printf("\n In case both the players have empty hand, The game will end in a tie.");
                        getch();
                        break;
                    }
                    case 4:
                        break;
                    }
                }
                while(ch!=4);

            }
            break;
        }
        case 3:
        {
            int choice_;
            do
            {
                lboard();
                system("CLS");
                printf("\n 1.Most Wins:-");
                printf("\n 2.Most Losses:-");
                printf("\n 3.Best Win/Loss Ratio:-");
                printf("\n 4.Exit:-");
                printf("\n Enter your choice:-");
                scanf("%d",&choice_);
                switch(choice_)
                {
                case 1:
                {
                    system("CLS");
                    sort_max();
                    dplay(1);
                    break;

                }
                case 2:
                {
                    system("CLS");
                    sort_min();
                    dplay(2);
                    break;
                }
                case 3:
                {
                    system("CLS");
                    sort_winloss();
                    dplay(3);
                    break;
                }
                case 4:
                    break;
                }
            }
            while(choice_!=4);
            break;
        }
        case 4:
        {
            return 0;
        }

        default:
        {
            printf("\n Wrong choice entered...");
            getch();
            continue;
        }
        }
    }
    while(ans!='n');

    return 0;
}

int main()
{
    return startGame();
}

int playgame(float var1,float var2,int k,int lvl)
{
    if(var1>var2)
    {
        struct card wrest;
        wrest=p2.top->obj;
        delcardp2();
        printf("\n\n USER LOST A CARD \n");
        addcardp1(wrest);
        printf("\n\n CPU GAINED A CARD \n");
        addcardlastp1();
        if(p2.rear!=NULL)
        {
            return 1;
        }
        if(p2.rear==NULL)
        {
            printf(" \n \n DAMN CPU WINS.....  \n");
            printf("\n\n Press any key to continue.. ");
            getch();
            victory=2;
            return 100;
        }
    }
    else if(var2>var1)
    {
        struct card wrest;
        wrest=p1.top->obj;
        delcardp1();
        printf("\n \n CPU LOST A CARD\n");
        addcardp2(wrest);
        printf(" \n \n USER gained a card \n");
        addcardlastp2();
        if(p1.rear!=NULL)
        {
            return 2;
        }
        if(p1.rear==NULL)
        {
            printf("\n \n CONGRATULATIONS USER WINS :");
            printf("\n\n Press any key to continue.. ");
            getch();
            victory=1;
            return 100;
        }

    }

    else if(var1==var2)
    {
        printf("\n \n ITS A CLASH");
        int i=clash(var1,var2,k,lvl);
        return i;
    }
}

void showHand()
{
    struct node*temp=p2.top;
    while(temp!=NULL)
    {

        printf("\n\n NAME   : %s",temp->obj.ar);
        printf("\n\n 1.ATTACK : %f",temp->obj.attack);
        printf("\n\n 2.DEFENCE: %f",temp->obj.defence);
        printf("\n\n 3.SPEED  : %f",temp->obj.speed);
        printf("\n\n 4.WEIGHT : %f",temp->obj.weight);
        printf("\n\n");
        temp=temp->next;

    }
}
