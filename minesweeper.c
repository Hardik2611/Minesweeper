#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 10 // defining the size as a macro to prevent hard coding
int a[size][size]; // 2D array to store the dimensions of the board (i.e size x size )
int score=0; // to keep track of score of the user
int result=0; // to keep track of equivalence between coordinates
int x_coor, y_coor;// to take the x and y co-ordinates from user
struct queue{
int x;
int y;// to take the x and y co-ordinates from user
struct queue *next;
};
struct queuepointers{
struct queue *front;
struct queue *rear;
}c, m, b; // front and rear pointers for queue of coordinates, mines and bonus
struct queue coor; // stack to store the x and y co-ordinates given by user
struct queue mine; // stack to store the x and y co-ordinates of the mines
struct queue bonus; // stack to store the x and y co-ordinates of the bonus points
void print(); // to print the board after each user input
void random_no_generator(int);
void insert(int, int, int); // to insert the coordinates with mines and bonus into the queues
int traverse(); // to traverse the queues to check for repetition in user input & coordinates with

int main(){
int i,j;
for(i=0 ; i<size ; i++){
for(j=0 ; j<size ; j++)
a[i][j]=0;
} random_no_generator(20);
print();
while(1){
A:
printf("Enter y-coordinate (from 0 to 9) : ");
scanf("%d",&x_coor);
if(x_coor<0 || x_coor>9){
printf("Please enter coordinates within the specified range.\n");

goto A;
}
B:
printf("Enter x-coordinate (from 0 to 9) : ");
scanf("%d",&y_coor);
if(y_coor<0 || y_coor>9){
printf("Please enter coordinates within the specified range.\n");
goto B;
} if(traverse(1)==2){
printf("Cannot repeat the coordinates.\n");// checking for repitition
goto A;
} insert(x_coor,y_coor,1);
if(traverse(2)==2){
a[x_coor][y_coor]=3;
print();
printf("Stepped on mine,\nGame over :(\nScore: %d",score);
return 0;
} if(traverse(3)==2){
score+=2;
printf("Bonus!!!");
a[x_coor][y_coor]=2;
print();
}
else{
score+=1;
a[x_coor][y_coor]=1;
print();
}
}
}
void print(){
int i,j;
printf("\n\n");
printf(" ");
for(i=0 ; i<size ; i++)
printf("%d ",i);
printf("\n\n");
for(i=0 ; i<size ; i++){
printf("%d ",i);
if(i<size)
printf(" ");
for(j=0 ; j<size ; j++)
printf("%d ",a[i][j]);
printf("\n");
}

}
void random_no_generator(int count){
int i,j,nm,flag=0;
int num_x,num_y;
srand(time(NULL)); // to get different random numbers during each execution
for(j=1 ; j<=2 ; j++)
{
if(j==1)
flag=2; // indicates insertion into the mine queue
if(j==2)
flag=3; // indicates insertion into the bonus queue
for(i=0 ; i<count ; i++){
num_x = rand() % 10;
num_y = rand() % 10;
insert(num_x,num_y,flag);
}
}
}
void insert(int x_value, int y_value, int flag){
struct queue *newnode;
newnode=(struct queue*)malloc(sizeof(struct queue));
newnode->x=x_value;
newnode->y=y_value;
newnode->next=NULL;
switch(flag){
case 1: // insert previous coordinates enetered by user into coor queue
if(c.front==NULL){
c.front=newnode;
c.rear=newnode;
}
else{
c.rear->next=newnode;
c.rear=newnode;
}
coor.x=newnode->x;
coor.y=newnode->y;
break;
case 2: // insert coordinates of mines
if(m.front==NULL){
m.front=newnode;
m.rear=newnode;
}
else{
m.rear->next=newnode;
m.rear=newnode;
}

mine.x=newnode->x;
mine.y=newnode->y;
break;
case 3: // insert coordinates of bonus
if(b.front==NULL){
b.front=newnode;
b.rear=newnode;
}
else{
b.rear->next=newnode;
b.rear=newnode;
}
bonus.x=newnode->x;
bonus.y=newnode->y;
break;
}
} int traverse(int t){
struct queue *temp1;
if(t==1)
temp1=c.front; // assigning front node of coor to temp1
else if(t==2)
temp1=m.front; // assigning front node of mine to temp1
else
temp1=b.front; // assigning front node of bonus to temp1
while(temp1!=NULL){
result = 0;
if(temp1->x==x_coor)
result+=1;
if(temp1->y==y_coor)
result+=1;
if(result==2)
return result; // result=2 is returned if coordinates match
temp1=temp1->next;
} return result;// result=0

}
