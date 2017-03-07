#include <windows.h>
#include <stdio.h>                
#include <conio.h>                   
#include <stdlib.h>
#include <string.h>                  
#include <ctype.h>                   
#include <dos.h>                     
#include <time.h>
#include <iostream>
#define RETURNTIME 15
//edit all string inputs to accomodate spaces later

char catagories[][15]={"Burgers","Chicken","Breakfast","Happy_Meal","Desserts","Add-Ons"};
void returnfunc(void);
void mainmenu(void);
void addfood(void);
void deletefood(void);
void editfoods(void);
void searchfoods(void);
void issuefoods(void);
void viewfoods(void);
void closeapplication(void);
int  getdata();
int  checkid(int);
int t(void);
void loading();
void welcome();
void issuerecord();
void loaderanim();

COORD coord = {0, 0};
COORD max_res,cursor_size;
void gotoxy (int x, int y){
        coord.X = x; coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
FILE *fp,*ft,*fs;

int s;
//char findbook;  //removed this
char username[100];


struct meroDate{
    int mm,dd,yy;
};
struct books{
    int id;
    char stname[20];
    char name[100];
    char Author[20];
    int quantity;
    float Price;
    int count;
    int rackno;
    char *cat;
    struct meroDate issued;
    struct meroDate duedate;
};
struct books a;
int main(){
	loading();
	getch;
}
void loading(){ //j changed into delay -PMC
 std::cout<<"\n\n\n\t\t\t\tLoading\n\n";
 char a=177, b=219;
 std::cout<<"\t\t\t\t";
 for (int i=0;i<=15;i++)
 std::cout<<a;
 std::cout<<"\r";
 std::cout<<"\t\t\t\t";
 for (int i=0;i<=15;i++)
 {
  std::cout<<b;
  delay(25);
  //for (int j=0;j<=1e8;j++); //this shd be changed to delay
 }
   mainmenu();
   getch;
}
	
void mainmenu(){ //edited exit msg, changed invalid input code
    system("cls");
	int i;
	gotoxy(20,3);
	printf("\t\t MAIN MENU ");
	gotoxy(20,5);
	printf("\t 1. View Food List");
	gotoxy(20,7);
	printf("\t 2. Create an Order");
	gotoxy(20,9);
	printf("\t 3. Close Application");
	gotoxy(20,12);
	printf("---------------------------------------");
	gotoxy(20,13);
	t();
	
	for(;;){
		gotoxy(20,15);
		printf("Enter your choice: ");
		
		switch(getch()){
			case '1':
				viewfoods();
				return;
			case '2':
				issuefoods();
				return;
			case '3':{ //added \n\n\n
				system("cls");
				printf("\n\n\n\t\t\tExiting in 3 seconds...........");
				delay(3000);
				exit(0);
		    }
			default:{
				gotoxy(15,17);
				printf("\aInvalid Input! Please Try Again!");
			}
    	}
    }
}

void issuefoods(void){ //rewrote almost all
    int d; //input food id
    char surname[20],firname[20];
	int idno,oquantity;
	int c=0; //id checker

    system("cls");
    gotoxy(10,2);
	printf("----------Order Creation----------\n");
	gotoxy(10,5);
	printf("Please enter your surname: ");
	scanf("%s",&surname);
	gotoxy(10,6);
	printf("Please enter your first name: ");
	scanf("%s",&firname);
	gotoxy(10,7);
	printf("Please enter your ID Number: ");
	scanf("%d",&idno);
	
	gotoxy(10,10);
	printf("Hello %s %s (%d)", firname, surname, idno);
	gotoxy(10,11);
	printf("Enter the Food ID you wish to order: ");
	scanf("%d",&d);
	fp=fopen("Food.dat","rb+"); 
	
	while(fread(&a,sizeof(a),1,fp)==1)
	{
		if(checkid(d)==0)
		{
			gotoxy(10,13);
			printf("The food is available!");
			gotoxy(10,15);
			printf("There are %d %s available at Php%.2f. How many would you like to order? ",a.quantity,a.name,a.Price);
			scanf("%d",&oquantity);
			if(oquantity>a.quantity){
				gotoxy(10,16);
				printf("Sorry, but we don't have enough stock for that order. Please try again.");
				fclose(fp);
				getch();
			    mainmenu();
			    return;
			}
			float tprice;
			tprice = oquantity*a.Price;
								
			gotoxy(10,17);
			printf("That will be Php %.2f. Please expect your food to be delivered soon. Thank you!",tprice);
		
		
			//printing to txt//
			FILE *f = fopen("order.txt", "a");
			fprintf(f, "Surname: %s\n", surname);
			fprintf(f, "First Name: %s\n", firname);
			fprintf(f, "ID No.: %d\n", idno);
			fprintf(f, "ORDER: %d %s @ %.2f each\n",oquantity,a.name,a.Price);
			fprintf(f, "Total: Php %.2f\n.\n", tprice);
			
			a.quantity=a.quantity-oquantity;
			
			fseek(fp,ftell(fp)-sizeof(a),0);
			fwrite(&a,sizeof(a),1,fp);
			fclose(fp);
	
		    gotoxy(10,19);
			delay(3000);
			mainmenu();	return;
	
			c=1;
		}
		if(c==0)
		{
			gotoxy(10,16);
			printf("Food ID not found. Please modify the search.");
			fclose(fp);
			getch();
		    mainmenu();
		    return;
		}
	}
    
}
void viewfoods(void) {
    int i=0,j;
    system("cls");
    gotoxy(1,1);
    printf("*********************************Food List*****************************");
    gotoxy(1,2);
    printf("CATEGORY     FOOD ID      FOOD NAME                       QTY     PRICE");
    j=4;
    fp=fopen("Food.dat","rb");
    while(fread(&a,sizeof(a),1,fp)==1){
		gotoxy(0,j);
        printf("%.10s",a.cat);
        gotoxy(14,j);
        printf("%d",a.id);
        gotoxy(27,j);
        printf("%.30s",a.name);
        gotoxy(35,j);
        printf("%s",a.Author);
        gotoxy(59,j);
        if(a.quantity<1){
        	printf("N/A");
		} else {
			printf("%d",a.quantity);
		}
        gotoxy(67,j);
        printf("%.2f",a.Price);
        printf("\n\n");
		j++;
		i=i+a.quantity;
    }
    gotoxy(3,25);
    printf("Total Food Quantity = %d",i);
    fclose(fp);
    gotoxy(35,25);
      returnfunc();
}

void returnfunc(void){
    {
	printf(" Press ENTER to return to main menu");
    }
    a:
    if(getch()==13){
    	mainmenu();	return;
	}
    else
    goto a;
}
int getdata(){
	int t;
	gotoxy(20,3);printf("Please Enter The Information Below");
	gotoxy(20,4);printf("----------------------------------");
	gotoxy(21,5);
	printf("Category: ");
	gotoxy(31,5);
	printf("%s",catagories[s-1]);
	gotoxy(21,6);
	printf("Food ID:\t");
	gotoxy(30,6);
	scanf("%d",&t);
	if(checkid(t) == 0){
		gotoxy(21,13);
		printf("\aThe food id already exists\a");
		getch();
		mainmenu();
		return 0;
	}
	a.id=t;
	gotoxy(21,7);
	printf("Food Name: ");gotoxy(33,7);
	scanf("%s",a.name);
	gotoxy(21,8);
	printf("Quantity: ");gotoxy(31,8);
	scanf("%d",&a.quantity);
	gotoxy(21,9);
	printf("Price: ");gotoxy(28,9);
	scanf("%f",&a.Price);
	return 1;
}
int checkid(int t)  { //0 means match found
	rewind(fp);
	while(fread(&a,sizeof(a),1,fp)==1)
	if(a.id==t)
	return 0;  
      return 1; 
}
int t(void){
time_t t;
time(&t);
printf("Date and time: %s\n",ctime(&t));

return 0 ;
}
void loaderanim(){
	int loader;
	system("cls");
	gotoxy(20,10);
	printf("LOADING........");
	printf("\n\n");
	gotoxy(22,11);
	for(loader=1;loader<20;loader++){
		delay(100);printf("%c",219);
	}
}
