/* use a,s,d,w for movement instead of arrow keys*/

#include <iostream>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
using namespace std;


//structure for snake
struct snake
{
	int x;
	int y;
	char val;
	snake* next;
};

//structure for food
struct food
{
	int x;
	int y;
	char ch;
};

/*
TODO
	food disappear
	move the snake
	generate new position for the food
	increase the size of snake
*/


snake* createSnake(snake* head, int x, int y);
food* generateFood(food* head,int x, int y);
void display(snake* s, food* f);
void move(snake* s, food* f,char ch);
void eatFood(snake* s,food* f);
void gameOver(snake* s,food* f);
void saveGame(snake*s,food*f);
void resumeGame(char* str);
/*
File -> String -> Linked List -> Matrix -> Screen

# Game Over then,
String - clear
Linked List - empty / free

# food eaten and size incresed
String - 

# if done nothing, then do not make any saves...check the previous state with the new one
so compare string with  every Nodes in the LL


*/

//function to create a snake
snake* createSnake(snake* head, int x, int y)
{
	snake* s = new snake();
	s->x = x;
	s->y = y;
	s->next = NULL;
	if(head == NULL)
	{
		s->val = 'A';
		head = s;
	}
	else
	{
		snake* temp = head;
		s->val = '#';
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = s;
	}

	return head;

}

//function to generate food
food* generateFood(food* head,int x, int y)
{
	food* f = new food();
	f->x = x;
	f->y = y;
	f->ch = '@';
	return f;
}

//function to display the snake and the food
void display(snake* s, food* f)
{
	Sleep(40);
	system("CLS");
	//system("color 5C");
	char matrix[30][30] = {' '};
	snake* temp = s;
	
	matrix[f->x][f->y]=f->ch;
	
	while(temp != NULL)
	{
		matrix[temp->x][temp->y] = temp->val;
		temp = temp->next;
	}
	
	

	
	for(int i = 0; i< 30; ++i){
		for(int j = 0; j < 30; ++j){
			cout<<matrix[i][j];
		}
		cout<<endl;
	}

}

//function to move
void move(snake* s, food* f)
{
	char prevkey ='a';
	char key ='a';
	while(key!=27)
	{
	display(s,f);
		
	if(kbhit())
	{
		prevkey = key;
		key =getch();
	}
	snake* temp = s;
	snake* invalid = temp->next;
	
	int foodeaten =0;
	if(s->x==f->x && s->y == f->y){eatFood(s,f); Beep(700,100); foodeaten=1;}
	
	int nextx, nexty;
	
	
	if(key == 'a'){nextx = temp->x; nexty = temp->y-1;}
	else if(key == 'd'){nextx = temp->x; nexty = temp->y+1;}
	else if(key == 'w'){nextx = temp->x-1; nexty = temp->y;}
	else if(key == 's'){nextx = temp->x+1; nexty = temp->y;}
	
	if(nextx == -1) nextx =29; if(nextx == 30) nextx = 0;
	if(nexty == -1) nexty = 29; if(nexty == 30) nexty = 0;
	
	if(nextx == invalid->x && nexty == invalid->y){key = prevkey; continue;}

	
	temp = s;
	int a,b;
	snake* record=temp;
	while(temp != NULL)
	{
		a = temp->x; b = temp->y;  //current position of head
		temp->x = nextx; temp->y = nexty;//updateed value of head
		nextx=a;nexty=b;
		record = temp;
		temp = temp->next;
	}
	
	if(foodeaten)
	{
		snake* newbody = new snake();
		newbody->x= a;newbody->y= b;newbody->val ='#';
		record->next = newbody;
	}
	
	
	temp = s->next;
	while(temp!= NULL)
	{
		if(s->x == temp->x && s->y == temp->y)
		gameOver(s,f);
		
		temp = temp->next;
	}
	
	
	
}
	saveGame(s,f);
}




void eatFood(snake* s,food* f)
{
	//food eating 
	snake* temp = s;
	int x=s->x, y=s->y;
	while(s->x==x && s->y == y){
		x =rand()%30;y = rand()%30;
	}
	f->x =x;f->y=y;
}
 




int main()
{
	snake* s = NULL;
	s = createSnake(s,14,15);
	s = createSnake(s,14,16);
	s = createSnake(s,14,17);

	food* f = NULL;
	f = generateFood(f,12,13);
	
	display(s,f);
	move(s,f);
	
	return 0;
}


void gameOver(snake* s, food* f)
{
	system("CLS");
	snake* temp = s->next->next;
	int score = 0;
	while(temp != NULL)
	{
		score++;
		temp= temp->next;
	}
	
	cout<<"\nYour score is "<<score<<endl;
	saveGame(s,f);
}


void saveGame(snake*s,food*f)
{
	//if(f==NULL) cout<<"fuck"<<endl;
	char* str = new char[1000];
	
	snake* temp = s;
	int i = 0;
	while(temp != NULL)
	{
		str[i] = temp->val; i++;
		str[i] = ','; i++;
		if(temp->x < 10)
		{
			str[i] = temp->x+48;i++;
			str[i] = ','; i++;
		}
		else if(temp->x >= 10)
		{
			str[i] = (temp->x/10+48); i++;
			str[i] = (temp->x % 10+48); i++;
			str[i] = ','; i++;
			
		}
		
		
		if(temp->y < 10)
		{
			str[i] = (char)temp->y;i++;
			str[i] = ','; i++;
		}
		else if(temp->y >= 10)
		{
			str[i] = (temp->y/10+48); i++;
			str[i] = (temp->y % 10 + 48); i++;
			str[i] = ','; i++;
			
		}
		
		str[i] = '$';i++;
		str[i] = ',';i++;
		
		temp = temp->next;
	}
	
	
	str[i]='-';i++;
	str[i] = ',';i++;
	
		str[i] = f->ch; i++;
		str[i] = ','; i++;
			//cout<<f->x;
		if(f->x < 10)
		{
			str[i] = (char)temp->x;i++;
			str[i] = ','; i++;
		}
		else if(f->x >= 10)
		{
		//	int temp1=temp->x/10;
	//	cout<<"hey";
			str[i] = (f->x/10 + 48);i++;
			//cout<<"hey";
			str[i] = (f->x % 10 + 48); i++;
			str[i] = ','; i++;
			
		}
		
		if(f->y < 10)
		{
			str[i] = (char)f->y;i++;
			str[i] = ','; i++;
		}
		else if(f->y >= 10)
		{
			str[i] = (f->y/10 + 48); i++;
			str[i] = (f->y % 10 + 48); i++;
			str[i] = ','; i++;
			
		}	
		str[i] = '?';i++;
		str[i] = '\0';
		//temp = temp->next;
		
	for(int a= 0; str[a]!='\0'; a++)
	cout<<str[a];
	resumeGame(str);
}

//function to resume game

void resumeGame(char* str)
{
	//A,14,28,$,#,14,25,$,#,14,26,$,-,@,12,13,?
	
	snake* snew= NULL;
	int a,x,y;

	
	cout<<"hey"<<endl;
	
	for(a = 0; str[a] != '-'; a++)
	{
		if(str[a] == ',' ||str[a]=='A' || str[a]=='#' || str[a] == '$')continue;
		if(str[a] != ',')
		{
			while(str[a] !=',')
			{
				x = (str[a]-48)*10 + (str[a++] - 48);a++;a++;
			}
			cout<<"yay ***** "<<x<<endl<<endl;
			a++;
			while(str[a] !=',')
			{
				y = (str[a]-48)*10 + (str[a++] - 48);a++;a++;
			}
			a++;
		}
		snew=createSnake(snew,x,y);continue;
	}
	
	
	int xx = a++;
	food* fnew = NULL;
	
	for(int a = xx;str[a]!='\0';a++)
	{
		if(str[a] == '@')continue;
		if(str[a] != ',')
		{
			a++;
			while(str[a] !=',')
			{
				x = (str[a]-48)*10 + (str[a++] - 48);a++;a++;
			}
			
			a++;
			while(str[a] !=',')
			{
				y = (str[a]-48)*10 + (str[a++] - 48);a++;a++;
			}
			a++;
		}
		fnew=generateFood(fnew,x,y);continue;
	}
	display(snew,fnew);
	
	
}

	


