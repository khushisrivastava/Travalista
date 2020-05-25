#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
//
int ID_init, totalRevenue, hcount = 0, fcount = 0;  char flno[7];

//Linked Lists for the Program
typedef struct user {
  char username[25];
  char password[16];
  struct details {
    char fName[25];
    char lName[25];
    struct birthdate {
      int day;
      int month;
      int year;
    }eb;
    char contact[25];
    char city[25];
    char state[25];
  }ed;
  struct user *next;
}USER;
USER *newNode, *head = 0, *temp = 0, *temp1 = 0;

typedef struct ufile {
  char key;
  int id;
  char name[50];
  int cin_day, cin_month, cin_year;
  int cout_day, cout_month, cout_year;
  int amount;
  struct ufile *next;
}UFILE;
UFILE *newNodef, *headf = 0, *tempf = 0, *temp1f = 0;

//Hotel's
typedef struct hotel {
  char name[50], location[50]; int avgFare, no;
  struct ROOM {
    char type[10];
    int rfare;
  }e[6];
  struct hotel *next;
}HOTEL;
HOTEL *newNodeH, *headH = 0, *tempH = 0, *tempH1 = 0;

typedef struct hbook {
  char key;
  int id;
  char name[50];
  int cin_day, cin_month, cin_year;
  int cout_day, cout_month, cout_year;
  int amount;
  struct hbook *next;
}HK;
HK *newNodeHK, *headHK = 0, *tempHK = 0, *temp1HK = 0;


//Flight's
struct node {
  char name[30];
  int clas;
  int adults;
  int children;
  int infants;
  int trip_type;
  int routing;
  char mobileno[11];
  struct node*next;
}*ptr,*current, *headi=NULL;

struct filenode {
  char src[15],desti[15];
  char flightno[7];
  int fare ;
  struct filenode*next;
}*headd=NULL, *ptrr=NULL;

typedef struct fbook {
  char key;
  int id;
  char name[50];
  int cin_day, cin_month, cin_year;
  int cout_day, cout_month, cout_year;
  int amount;
  struct fbook *next;
}FK;
FK *newNodeFK, *headFK = 0, *tempFK = 0, *temp1FK = 0;


//FunctionPrototypes
void clrscr();
void currentTime();
void paymentPortal(int);
void arrorHere(int, int);
void fileEntry();
void fileRetrive();
void sortList(HOTEL *headS);
void freeHotel();
void freeFilenode();
void scanID();
void writeID();

void flightRecords(int amount, int tid);
void display();
void reserve();
void confirmation();

void hotelRecords(int amount, int tid);
void hotelFinalizing(HOTEL *op);
void hotelPrinting(char country[]);
void displayPreviousRecords(HK *headHK, HK*tempHK);

void flightBooking();
void hotelBooking();
void feedback();
void aboutUs();

void menu();

void userList(USER *head, USER* temp);
void recordBook();
void revenue();
void usrfeeds();
void adminMenu();

void fileToList();
void adminLogin();
void createUser();
void loginCheck(char uname[], char upass[]);
void login();
void userPortal();



//MiscelleneousFunctions
int position = 1; int keyPressed = 0;
void clrscr() {
  system("@cls||clear");
}
void currentTime() {
  time_t rawtime;
    struct tm*  time_;

    time(&rawtime);
    time_ = localtime(&rawtime);

    printf("\t\t\t\t\t %i:%i:%i | %i-%i-%i\n", time_->tm_hour, time_->tm_min,
            time_->tm_sec, time_->tm_mday, time_->tm_mon+1,
            time_->tm_year+1900);

}
void paymentPortal(int amount) {
  int traveliz_id, traveliz_cvv, month, year, tid; char c;
  clrscr();
  printf("AMOUNT: %d\n\n", amount);
  printf("Enter the TRAVLIZ Card id: ");
  scanf("%d", &traveliz_id);
  printf("Enter CVV: ");
  scanf("%d", &traveliz_cvv);
  printf("Enter month: ");
  scanf("%d", &month);
  printf("Enter year: ");
  scanf("%d", &year);
  printf(":::CONFIRM PAYMENT:::\nPress 1 to confirm else 0 to reenter card details:-\n");
  c = getch();
  if(c == '1') {
    tid = (1*69) + ID_init; ID_init = tid;
    totalRevenue = totalRevenue + amount;
    writeID();
    printf("Your transaction id is: %d\n\nPress any key to display booking details\n", tid);
    getch();
  }
  else {
    paymentPortal(amount);
  }
}
void arrorHere(int realPosition, int arrowPosition) {
  if(realPosition == arrowPosition) {
    printf(">>>>  ");
  }
  else {
    printf("      ");
  }
}
void fileEntry() {
  tempf = headf;
  char tname[100];
  char path[] = "./Source Files/USERS\\";
  strcpy(tname, path);
  strcat(tname, temp->username);
  strcat(tname, ".txt");
  FILE *fp = fopen(tname, "w+");
  while(tempf != NULL) {
    fprintf(fp, "%c %d %s %d-%d-%d %d-%d-%d %d\n", tempf->key, tempf->id, tempf->name, tempf->cin_day, tempf->cin_month, tempf->cin_year, tempf->cout_day, tempf->cout_month, tempf->cout_year, tempf->amount);
    tempf = tempf->next;
  }
  fclose(fp);
  printf("*************************************\n");
  printf("*     BOOKING SUCCESSFULLY DONE!!   *\n");
  printf("*************************************\n\n\n");
  printf("\nPress any key to return to main menu...");
  getch();
  menu(temp->username);
}
void fileRetrive() {
  char tname[100];
  char path[] = "./Source Files/USERS\\";
  strcpy(tname, path);
  strcat(tname, temp->username);
  strcat(tname, ".txt");
  FILE *fp = fopen(tname, "r");
  while(!feof(fp)) {
    newNodef = (UFILE *)malloc(sizeof(UFILE));
    fscanf(fp, "%c %d %s %d-%d-%d %d-%d-%d %d\n", &newNodef->key, &newNodef->id, newNodef->name, &newNodef->cin_day, &newNodef->cin_month, &newNodef->cin_year, &newNodef->cout_day, &newNodef->cout_month, &newNodef->cout_year, &newNodef->amount);
    if(headf != 0) {
      tempf->next = newNodef;
      tempf = newNodef;
    }
    else {
      headf = tempf = newNodef;
    }
  }
  tempf->next = NULL;
  fclose(fp);
  tempf = headf;
  while(tempf != NULL) {
    if(tempf->key == 'h') {
      newNodeHK = (HK *)malloc(sizeof(HK));
      newNodeHK->key = tempf->key;
      newNodeHK->id  = tempf->id;
      strcpy(newNodeHK->name, tempf->name);
      newNodeHK->cin_day  = tempf->cin_day;
      newNodeHK->cin_month  = tempf->cin_month;
      newNodeHK->cin_year  = tempf->cin_year;
      newNodeHK->cout_day  = tempf->cout_day;
      newNodeHK->cout_month  = tempf->cout_month;
      newNodeHK->cout_year  = tempf->cout_year;
      newNodeHK->amount  = tempf->amount;
      if(headHK != 0) {
        tempHK->next = newNodeHK;
        tempHK = newNodeHK;
      }
      else {
        headHK = tempHK = newNodeHK;
      }
    } if(tempf->key == 'f') {
      newNodeFK = (FK *)malloc(sizeof(FK));
      newNodeFK->key = tempf->key;
      newNodeFK->id  = tempf->id;
      strcpy(newNodeFK->name, tempf->name);
      newNodeFK->cin_day  = tempf->cin_day;
      newNodeFK->cin_month  = tempf->cin_month;
      newNodeFK->cin_year  = tempf->cin_year;
      newNodeFK->cout_day  = tempf->cout_day;
      newNodeFK->cout_month  = tempf->cout_month;
      newNodeFK->cout_year  = tempf->cout_year;
      newNodeFK->amount  = tempf->amount;
      if(headFK != 0) {
        tempFK->next = newNodeFK;
        tempFK = newNodeFK;
      }
      else {
        headFK = tempFK = newNodeFK;
      }
    }
    tempf = tempf->next;
  }
  if(tempHK != 0)
    tempHK->next = NULL;
  if(tempFK != 0)
    tempFK->next = NULL;
}
void sortList(HOTEL *headS) {
  HOTEL *tempS, *tempS1, *tempS2;
  for(tempS1=headS; tempS1->next!=NULL; tempS1=tempS1->next){
    for(tempS2=tempS1->next; tempS2!=NULL; tempS2=tempS2->next){
      if(tempS1->avgFare > tempS2->avgFare){
        strcpy(tempS->name,tempS1->name);
        strcpy(tempS1->name,tempS2->name);
        strcpy(tempS2->name,tempS->name);
        strcpy(tempS->location,tempS1->location);
        strcpy(tempS1->location,tempS2->location);
        strcpy(tempS2->location,tempS->location);
        tempS->avgFare=tempS1->avgFare;
        tempS1->avgFare=tempS2->avgFare;
        tempS2->avgFare=tempS->avgFare;
      }
    }
  }
}
void freeHotel() {
  tempH1 = headH;
  while(tempH1 != NULL) {
    tempH = tempH1->next;
    free(tempH1);
    tempH1 = tempH;
  }
  headH = 0;

}
void freeFilenode() {
  struct filenode *tempFN = headd;
  struct filenode *tempFN1;
  while(tempFN != NULL) {
    tempFN1 = tempFN->next;
    free(temp1);
    tempFN = tempFN1;
  }
  headd = NULL;
}
void scanID() {
  FILE *fp = fopen("./Source Files/ID.txt", "r");
  while(!feof(fp))
    fscanf(fp, "%d\n%d", &ID_init, &totalRevenue);
  fclose(fp);
}
void writeID() {
  FILE *fp = fopen("./Source Files/ID.txt", "w");
  fprintf(fp, "%d\n%d", ID_init, totalRevenue);
  fclose(fp);
}


//CalenderFunctions
int v=1;
typedef struct day{
  int dd;
  int mm;
  int yy;
}DAY;
DAY curr, d, d1, d2 ,df;

COORD xy={0,0};
DAY currentDate() {
  time_t rawtime;
    struct tm*  time_;
    DAY cdate;
    time(&rawtime);
    time_ = localtime(&rawtime);
    cdate.dd=time_->tm_mday;
    cdate.mm=time_->tm_mon+1;
    cdate.yy=time_->tm_year+1900;
    return(cdate);
}
void gotoxy(int x, int y){
  xy.X=x;
  xy.Y=y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),xy);
}
void plus(int *month, int *year){
  ++*month;
  if(*month>12){
    ++*year;
    *month=*month-12;
  }
}
void minus(int *month, int *year){
    --*month;
    if(*month<1){
      --*year;
      *month=*month+12;
    }
}
int checkLeap(int year){
  if(year % 400 ==0||(year % 100 !=0 && year % 4 ==0))
     return(1);
  return(0);
}
int verification(DAY vday){
  curr= currentDate();
  int date= curr.dd;
  int month= curr.mm;
  int year= curr.yy;
  if((vday.dd < date && vday.mm == month && vday.yy==year) || (vday.mm==month && vday.yy < year) || (vday.mm < month && vday.yy == year)){
    printf("PLEASE ENTER A VALID DATE.\n");
    return (1);
  }
  if(vday.yy >= year){
    if(vday.mm >= 1 && vday.mm <=12){
      if((vday.dd >=1 && vday.dd <=31) &&(vday.mm ==1 || vday.mm ==3 || vday.mm ==5 || vday.mm ==7 || vday.mm ==8 || vday.mm ==10 || vday.mm ==12)){
        return (0);
      }
      if((vday.dd >=1 && vday.dd <=30) &&(vday.mm ==4 || vday.mm ==6 || vday.mm ==9 || vday.mm ==11)){
        return (0);
      }
      if(vday.mm==2){
        int leap= checkLeap(vday.yy);
        if(vday.dd<=29 && leap==1){
          return (0);
        }
        else{
          printf("PLEASE ENTER A VALID DATE.\n");
          return (1);
        }
      }
    }
    else{
      printf("PLEASE ENTER A VALID DATE.\n" );
      return (1);
    }
  }
  else{
    printf("PLEASE ENTER A VALID DATE.\n" );
    return (1);
  }
}
void printmonth(int month, int year){
  gotoxy(20,2);
  printf("-----------------------------------------------------\n" );
  gotoxy(20,3);
  printf("-----------------------------------------------------\n" );
  gotoxy(40,4);
  printf("%d ",year );

  switch (month) {
    case 1:printf("JANUARY\n");break;
    case 2:printf("FEBRAURY\n");break;
    case 3:printf("MARCH\n");break;
    case 4:printf("APRIL\n");break;
    case 5:printf("MAY\n");break;
    case 6:printf("JUNE\n");break;
    case 7:printf("JULY\n");break;
    case 8:printf("AUGUST\n");break;
    case 9:printf("SEPTEMBER\n");break;
    case 10:printf("OCTOBER\n");break;
    case 11:printf("NOVEMBER\n");break;
    case 12:printf("DECEMBER\n");break;

  }
  gotoxy(20,5);
  printf("-----------------------------------------------------\n" );
  gotoxy(20,6);
  printf("-----------------------------------------------------\n" );
  gotoxy(20,7);
}
int days(int month ,int year){
  switch (month) {
    case 1: return(31);
    case 2: if(checkLeap(year)==1)
              return(29);
            else
              return(28);
    case 3: return(31);
    case 4: return(30);
    case 5: return(31);
    case 6: return(30);
    case 7: return(31);
    case 8: return(31);
    case 9: return(30);
    case 10: return(31);
    case 11: return(30);
    case 12: return(31);

  }
}
int countdays(struct day d1,struct day d2){
  int c1=365*(d2.yy-1)+d2.dd;
  for(int i=0;i<d2.mm-1;i++){
    c1+=days(d2.mm,d2.yy);
  }
  int c2=365*(d1.yy-1)+d1.dd;
  for(int i=0;i<d1.mm-1;i++){
    c2+=days(d1.mm,d1.yy);
  }
  return(c1-c2);
}
int getDayNumber(int day,int mon,int year){
    int res = 0, t1, t2, y = year;
    year = year - 1600;
    while(year >= 100){
        res = res + 5;
        year = year - 100;
    }
    res = (res % 7);
    t1 = ((year - 1) / 4);
    t2 = (year-1)-t1;
    t1 = (t1*2)+t2;
    t1 = (t1%7);
    res = res + t1;
    res = res%7;
    t2 = 0;
    for(t1 = 1;t1 < mon; t1++){
        t2 += days(t1,y);
    }
    t2 = t2 + day;
    t2 = t2 % 7;
    res = res + t2;
    res = res % 7;
    if(y > 2000)
        res = res + 1;
    res = res % 7;
    return res;
}
void printcalender(struct day curr, int x, int y){
  int d=1, count,x1=x;
  int month=curr.mm;
  int year=curr.yy;
  int date=curr.dd;
  if(month<1 || month >12 ){
    printf("INVALID MONTH!\n");
//    break;
  }
  if(year<1600){
    printf("INVALID YEAR!\n" );
//    break;
  }
  gotoxy(20,y);
  printmonth(month,year);
  y+=4;
  gotoxy(x,y);
  printf("S\t    M\t    T\t    W\t    T\t    F\t    S\n");
  int n=days(month,year);
    int day=getDayNumber(d,month,year);
    y++;
    switch (day) {
      case 0:{
        x=x;
        count=1;
        break;
      }
      case 1:{
        x+=8;
        count=2;
        break;
      }
      case 2:{
        x+=16;
        count=3;
        break;
      }
      case 3:{
        x+=24;
        count=4;
        break;
      }
      case 4:{
        x+=32;
        count=5;
        break;
      }
      case 5:{
        x+=40;
        count=6;
        break;
      }
      case 6:{
        x+=48;
        count=7;
        break;
      }
    }
    gotoxy(x,y);
    printf("%d",d);
    for(d=2;d<=n;d++){
      if(count%7==0){
  //      printf("\n" );
        y++;
        count=0;
        x=x1-8;
      }
      x=x+8;
      gotoxy(x,y);
      count++;
      printf("%d\t",d );
      if(d==date){
          gotoxy(x-2,y);
          printf(">>");
        }
      }
  //pointday(n,date);
  gotoxy(20, y+2);
  printf("CALENDER ONLY FOR WEEK DAY REFERENCE\n");
  gotoxy(8,y+4);
  printf("\nPress 'RIGHT'  to Next, Press 'LEFT' to Previous and '0' to Enter Date");
}
DAY calendermain(){
  v = 1;
  char c;
  curr=currentDate();
  system("cls");
  while(c!='0'){
    printcalender(curr,20,5);
    c=getch();
    fflush(stdin);
    if(GetAsyncKeyState(VK_RIGHT)){
      plus(&curr.mm,&curr.yy);
      system("cls");
      printcalender(curr,20,5);
      fflush(stdin);
      }
    if(GetAsyncKeyState(VK_LEFT)){
      minus(&curr.mm,&curr.yy);
      system("cls");
      printcalender(curr,20,5);
      fflush(stdin);
      }
    }
    if(c=='0'){
      while(v){
        printf("\nEnter Date (DD MM YYYY)\n");
        scanf("%d %d %d",&d.dd, &d.mm, &d.yy);
        v=verification(d);
      }
      return (d);
    }
}

//FlightBooking SubFunctions
void flightRecords(int amount, int tid) {
  newNodeFK = (FK *)malloc(sizeof(FK));
  newNodef = (UFILE *)malloc(sizeof(UFILE));
  newNodeFK->key = newNodef->key = 'f';
  newNodeFK->id  = newNodef->id = tid;
  strcpy(newNodeFK->name, flno);
  strcpy(newNodef->name, flno);
  newNodeFK->cin_day  = newNodef->cin_day = df.dd;//d1.dd;
  newNodeFK->cin_month  = newNodef->cin_month = df.mm;//d1.mm;
  newNodeFK->cin_year  = newNodef->cin_year  = df.yy;//d1.yy;
  newNodeFK->cout_day  = newNodef->cout_day  = 0;
  newNodeFK->cout_month  = newNodef->cout_month = 0;
  newNodeFK->cout_year  = newNodef->cout_year  = 1980;
  newNodeFK->amount  = newNodef->amount  = amount;
  if(headFK != 0) {
    tempFK->next = newNodeFK;
    tempFK = newNodeFK;
  }
  else {
    headFK = tempFK = newNodeFK;
  }
  tempFK->next = NULL;

  if(headf != 0) {
    tempf = headf;
    while(tempf->next != NULL) {
      tempf = tempf->next;
    }
    tempf->next = newNodef;
    tempf = newNodef;
  }
  else {
    headf = tempf = newNodef;
  }
  tempf->next = NULL;
  clrscr();
  fileEntry();
}
void reserve() {

  ptr=(struct node*)malloc(sizeof(struct node));

//taking details of the node
  printf("Dear Customer ,kindly enter your details please:- \n NAME:\n");
  scanf("%s",ptr->name);
  do{
    printf("Enter mobile number\n");                           //check for validity
    scanf("%s",ptr->mobileno);

        if(strlen(ptr->mobileno)!=10){
              printf("\n\t\tInvalid MOBILE NO .\n") ;
        }
      }while(strlen(ptr->mobileno)!=10);

  printf("\t\tchoose the class(Press the corresponding number ) :-\n1)bussiness\t2)economy\t3)premium economy\n \n");
  scanf("%d",&ptr->clas);
    system("cls");

  printf("\n\t\t\t**************************************************\n");
  printf("\t\t\tnow please enter the details of the traveller(s)\n" );                     //column wise representation
  printf("\t\t\t**************************************************\n\n");


  printf("Number of children (age group 2-12)\n");
  scanf("%d",&ptr->children);

  printf("Number of adults(age above 12)\n");
  scanf("%d",&ptr->adults);

  printf("Number of infants(age group below 2)\n");
  scanf("%d",&ptr->infants);
  printf("Your trip type? ONE WAY or TWO WAY ROUND TRIP \n\n Press 1 for one way trip \n\n       2 for a two way trip\n\n\n");
  char c;
  c = getch();
  ptr->trip_type = (int)(c - '0');
  //scanf("%d",&ptr->trip_type);

  printf("Tell us about your comfortable routing style\n \nPress 1 for DIRECT FLIGHTS \n\n      2 for CONNECTING(VIA) FLIGHTS\n");
  char c1;
  c1 = getch();
  ptr->routing = (int)(c1 - '0');
  ptr->next=NULL;
  if(headi==NULL) {
    headi=ptr;
    current=ptr;
  }
  else {
    current->next=ptr;
    current=ptr;
  }
  //printing individual ticket details for each new noode -> each time new record in ticket.txt
  FILE*f;
  f=fopen("./Source Files/FLIGHT FILES/ticket.txt","w");
  fprintf(f,"NAME:%s\nMOBILE_NO%s\nCLASS%d\nNUMBER OF ADULTS:%d\nNUMBER OF CHILDREN%d\nNUMBER OF INFANTS%d\nTRIP_TYPE:%d\nROUTING:%d\n",ptr->name,ptr->mobileno,ptr->clas,ptr->adults,ptr->children,ptr->infants,ptr->trip_type,ptr->routing);
  fclose(f);
  printf("Your records have been saved!");
//printing all details of everyone to a record book ALL_RECORDS ->appending data
  FILE*fp;
  fp=fopen("./Source Files/FLIGHT FILES/allrecords.txt","a");
  struct node*temp;
  temp=(struct node*)malloc(sizeof(struct node));
  temp=headi;
  while (temp!=NULL) {
    fprintf(fp,"NAME:%s\nMOBILE_NO%s\nCLASS%d\nNUMBER OF ADULTS:%d\nNUMBER OF CHILDREN%d\nNUMBER OF INFANTS%d\nTRIP_TYPE:%d\nROUTING:%d\n",temp->name,temp->mobileno,temp->clas,temp->adults,temp->children,temp->infants,temp->trip_type,temp->routing);
    temp=temp->next;
  }
  fclose(fp);
}
void confirmation() {

  int payout;
  printf("Enter the flight no: ");
  scanf("%s",flno);
  ptrr=headd;
  while(ptrr!=0) {
    if(strcmp(ptrr->flightno,flno)==0) {
      payout=ptrr->fare;
    }
    ptrr=ptrr->next;
  }
  df = calendermain();
  system("cls");
  reserve();

  FILE*f;
  f=fopen("./Source Files/FLIGHT FILES/ticket.txt","r");
  while(!feof(f)) {
    fscanf(f,"NAME:%s\nMOBILE_NO%s\nCLASS%d\nNUMBER OF ADULTS:%d\nNUMBER OF CHILDREN%d\nNUMBER OF INFANTS%d\nTRIP_TYPE:%d\nROUTING:%d\n",ptr->name,ptr->mobileno,&ptr->clas,&ptr->adults,&ptr->children,&ptr->infants,&ptr->trip_type,&ptr->routing);
  }
  keyPressed = 0; position = 1;
  while(keyPressed != 13) {
    clrscr();
    printf("Total fare--->>%d\n",payout);
    printf("**********************************************************\n");
    printf("\nProceed for the payment:-\n");
    arrorHere(1, position); printf("  YES\n");
    arrorHere(2, position); printf("  NO\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 2) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1: paymentPortal(payout); break;
    case 2: display(); break;
  }
  clrscr();
  system("color 1F");
  printf("\n\n\n\t\t\t\tTICKET\n\n\n");
  printf("NAME:%s\nMOBILE_NO%s\nCLASS%d\nNUMBER OF ADULTS:%d\nNUMBER OF CHILDREN%d\nNUMBER OF INFANTS%d\nTRIP_TYPE:%d\nROUTING:%d\n",ptr->name,ptr->mobileno,ptr->clas,ptr->adults,ptr->children,ptr->infants,ptr->trip_type,ptr->routing);
  printf("FlightNO--->>%s\n",flno);
  printf("Press any key to continue...");
  getch();
  flightRecords(payout, ID_init);
  system("cls");
  fclose(f);
}
void display() {
  freeFilenode();
  struct filenode *s=0,*temp=0;
  //system("color 0E");
  char source [10],destination[15];
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("For checking the details of available flights,\n\n please choose nearest INTERNATIONAL AIRPORT\n\n\t DELHI->INDIRA GANDHI INTERNATIONAL AIRPORT \n\n\tMUMBAI->CHHATRAPATI SHIVAJI INTERNATIONAL AIRPORT\n\n\tCHENNAI->CHENNAI INTERNATIONAL AIRPORT\n ");
    printf("*******************************************");
    printf("CHOOSE FROM THE SOURCES:\n");
    arrorHere(1, position); printf("1. DELHI\n");
    arrorHere(2, position); printf("2. MUMBAI\n");
    arrorHere(3, position); printf("3. CHENNAI\n");
    keyPressed = getch();

    if(keyPressed == 80 && position != 3) {
      position++;
    } else if(keyPressed == 72 && position != 1) {
        position--;
      } else {
        position = position;
      }
}
switch(position) {
  case 1: strcpy(source, "Delhi"); break;
  case 2: strcpy(source, "Mumbai"); break;
  case 3: strcpy(source, "Chennai"); break;
}
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("\n\n\n Now enter the destination  \n");
    printf("Choose from the below given list\n");
    arrorHere(1, position); printf("1. RUSSIA\n");
    arrorHere(2, position); printf("2. UK\n");
    arrorHere(3, position); printf("3. SPAIN\n");
    arrorHere(4, position); printf("4. FRANCE\n");
    arrorHere(5, position); printf("5. TORONTO\n");
    arrorHere(6, position); printf("6. SINGAPORE\n");
    arrorHere(7, position); printf("7. SOUTHKOREA\n");
    arrorHere(8, position); printf("8. EUROPE\n");
    arrorHere(9, position); printf("9. HONGKONG\n");
    arrorHere(10, position); printf("0. DUBAI\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 10) {
      position++;
    } else if(keyPressed == 72 && position != 1) {
        position--;
    } else {
        position = position;
    }
  }
switch(position) {
case 1: strcpy(destination, "Russia"); break;
case 2: strcpy(destination, "UK"); break;
case 3: strcpy(destination, "Spain"); break;
case 4: strcpy(destination, "France"); break;
case 5: strcpy(destination, "Toronto"); break;
case 6: strcpy(destination, "Singapore"); break;
case 7: strcpy(destination, "SouthKorea"); break;
case 8: strcpy(destination, "Europe"); break;
case 9: strcpy(destination, "HongKong"); break;
case 10: strcpy(destination, "Dubai"); break;
}

  system("cls");
  FILE *f;
  f=fopen("./Source Files/FLIGHT FILES/details.txt","r");
//copying the content of file to structure nodes
  while(!feof(f)) {
    s=(struct filenode*)malloc(sizeof(struct filenode));
    fscanf(f,"%s %s %s %d\n",s->src,s->desti,s->flightno,&s->fare);
    if(headd!=0) {
      temp->next=s;
      temp=s;
    } else {
      headd=temp=s;
    }
  }
  temp->next=NULL;
  fclose(f);
//now extracting the values from these nodes to get desired output
  temp=headd;
  printf("\n\n\nChoose the desired flight from the list:- \n");
  printf("------------------------------------------------------------------------------------\n");
  printf("SOURCE\t\t\tDESTINATION\t\tFLIGHT_NO\t\tFARE\n");
  printf("------------------------------------------------------------------------------------\n");
  while(temp!=0) {
    if(strcmpi(temp->src,source)==0&&strcmpi(temp->desti,destination)==0) {
    printf("%s\t\t\t%s\t\t\t%s\t\t\t%d\t\n",temp->src,temp->desti,temp->flightno,temp->fare);
    printf("------------------------------------------------------------------------------------\n");
      }
    temp=temp->next;
  }
// nested function ->calling confirmation() inside display function
confirmation();
}

//HotelBooking SubFunctions
void hotelRecords(int amount, int tid) {
  newNodeHK = (HK *)malloc(sizeof(HK));
  newNodef = (UFILE *)malloc(sizeof(UFILE)); newNodef->next = NULL;
  newNodeHK->key = newNodef->key = 'h';
  newNodeHK->id  = newNodef->id = tid;
  strcpy(newNodeHK->name, tempH1->name);
  strcpy(newNodef->name, tempH1->name);
  newNodeHK->cin_day  = newNodef->cin_day = d1.dd;
  newNodeHK->cin_month  = newNodef->cin_month = d1.mm;
  newNodeHK->cin_year  = newNodef->cin_year  = d1.yy;
  newNodeHK->cout_day  = newNodef->cout_day  = d2.dd;
  newNodeHK->cout_month  = newNodef->cout_month = d2.mm;
  newNodeHK->cout_year  = newNodef->cout_year  = d2.yy;
  newNodeHK->amount  = newNodef->amount  = amount;
  if(headHK != 0) {
    tempHK->next = newNodeHK;
    tempHK = newNodeHK;
  }
  else {
    headHK = tempHK = newNodeHK;
  }
  tempHK->next = NULL;

  if(headf != 0) {
    tempf = headf;
    while(tempf->next != NULL) {
      tempf = tempf->next;
    }
    tempf->next = newNodef;
    tempf = newNodef;
  }
  else {
    headf = tempf = newNodef;
  }
  clrscr();
  printf("\n:::BOOKING DETAILS:::\n");
  fileEntry();
  printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
  printf("Transaction ID\t\t\t\t Name\t\t\t\t Check In Date\t\t\t\t Check Out Date\t\t\t\t Amount\n" );
  printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n" );
  printf("%d\t\t\t\t %s\t\t\t\t %d-%d-%d\t\t\t\t %d-%d-%d\t\t\t\t %d\n",tid, tempH1->name, d1.dd,d1.mm,d1.yy,d2.dd,d2.mm,d2.yy,amount );
}
void hotelFinalizing(HOTEL *op) {
  clrscr();
  int choice; int fday, fmonth, fyear, tday, tmonth, tyear, days, nights, price, tprice;
  keyPressed = 0; position = 1;
  while(keyPressed != 13) {
    clrscr();
    printf("Hotel: %s\n\nChoose room type:-\n", op->name);
    printf("--------------------------------------------------------------------------------\n");
    printf("SerialNo.\t\tTYPE\t\t\t\t\tFARE\n");
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(1, position); printf("%d. %20s\t\t\t\t\t%d\n", 1, op->e[0].type, op->e[0].rfare);
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(2, position); printf("%d. %20s\t\t\t\t\t%d\n", 2, op->e[1].type, op->e[1].rfare);
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(3, position); printf("%d. %20s\t\t\t\t\t%d\n", 3, op->e[2].type, op->e[2].rfare);
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(4, position); printf("%d. %20s\t\t\t\t\t%d\n", 4, op->e[3].type, op->e[3].rfare);
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(5, position); printf("%d. %20s\t\t\t\t\t%d\n", 5, op->e[4].type, op->e[4].rfare);
    printf("--------------------------------------------------------------------------------\n");
    arrorHere(6, position); printf("%d. %20s\t\t\t\t\t%d\n", 6, op->e[5].type, op->e[5].rfare);
    printf("--------------------------------------------------------------------------------\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 6) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1: price = op->e[0].rfare; break;

    case 2: price = op->e[1].rfare; break;

    case 3: price = op->e[2].rfare; break;

    case 4: price = op->e[3].rfare; break;

    case 5: price = op->e[4].rfare; break;

    case 6: price = op->e[5].rfare; break;

    default: printf("Invalid choice, press any key to try again."); getch(); hotelFinalizing(op);
  }
  printf("Choose checkin date: \n");
  d1 = calendermain();

  printf("Choose checkout date: \n");
  d2 = calendermain();

  nights = countdays(d1, d2);
  days = nights + 1;
  tprice = op->avgFare + (price * days);
  keyPressed = 0; position = 1;
  while(keyPressed != 13) {
    clrscr();
    printf("\n\t\t\t\t\t\t\t\t\t\t<<<<<Summary >>>>>\n\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  FARE\t\t\t\t\t\t\t\tNAME\t\t\t\t\t  CHECKIN\t\t\t\t\t\t   CHECKOUT\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf(" %d\t\t\t  %42s\t\t\t\t %10d-%d-%d\t\t\t\t\t  %10d-%d-%d\n", tprice, op->name, d1.dd, d1.mm, d1.yy, d2.dd, d2.mm, d2.yy);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\nProceed for the payment:-\n");
    arrorHere(1, position); printf("  YES\n");
    arrorHere(2, position); printf("  NO\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 2) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1: paymentPortal(tprice); break;
    case 2: hotelFinalizing(op); break;
  }
  hotelRecords(tprice, ID_init);
}
void hotelPrinting(char country[]) {
  clrscr();
  char path[100] = "./Source Files/COUNTRY\\"; int choice;
  strcat(path, country);
  strcat(path, ".txt");
  FILE *fp = fopen(path, "r+");
  for(int i=0; i<5; i++) {
    newNodeH = (HOTEL *)malloc(sizeof(HOTEL));
    fscanf(fp, "%s %s %d\n", newNodeH->name, newNodeH->location, &newNodeH->avgFare);
    for(int i=0; i<6; i++) {
      fscanf(fp, "%s %d\n", newNodeH->e[i].type, &newNodeH->e[i].rfare);
    }
    if(headH != 0) {
      tempH->next = newNodeH;
      tempH = newNodeH;
    }
    else {
      headH = tempH = newNodeH;
    }
  }
  temp->next = NULL;
  //sortList(headH);
  keyPressed = 0; position = 1;
  while(keyPressed != 13) {
    clrscr();
    printf("Choose a Hotel:-\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("SerialNo.\t\t\t\t\tNAME\t\t\t\t  LOCATION  \t\t\t\t\t\t\t\tAVG FARE\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tempH = headH;
    arrorHere(1, position); printf("%d. %45s %35s %70d\n", 1, tempH->name, tempH->location, tempH->avgFare);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tempH = tempH->next;
    arrorHere(2, position); printf("%d. %45s %35s %70d\n", 2, tempH->name, tempH->location, tempH->avgFare);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tempH = tempH->next;
    arrorHere(3, position); printf("%d. %45s %35s %70d\n", 3, tempH->name, tempH->location, tempH->avgFare);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tempH = tempH->next;
    arrorHere(4, position); printf("%d. %45s %35s %70d\n", 4, tempH->name, tempH->location, tempH->avgFare);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tempH = tempH->next;
    arrorHere(5, position); printf("%d. %45s %35s %70d\n", 5, tempH->name, tempH->location, tempH->avgFare);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    tempH = tempH->next;
    fclose(fp);
    keyPressed = getch();
    if(keyPressed == 80 && position != 5) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1:
    tempH1 = headH;
    hotelFinalizing(tempH1);
    break;

    case 2:
    tempH1 = headH->next;
    hotelFinalizing(tempH1);
    break;

    case 3:
    tempH1 = headH->next->next;
    hotelFinalizing(tempH1);
    break;

    case 4:
    tempH1 = headH->next->next->next;
    hotelFinalizing(tempH1);
    break;

    case 5:
    tempH1 = headH->next->next->next->next;
    hotelFinalizing(tempH1);
    break;

    default:
    printf("Invalid choice, press any key to try again.");
    getchar();
    hotelPrinting(country);
  }
  getch();
}
void displayPreviousRecords(HK *headHK, HK*tempHK){
  clrscr();
  if(headf==0){
    printf("NO PREVIOUS RECORDS...\n");
  }
  else{
    tempf=headf->next;
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Transaction ID\t\t\t\tHOTEL NAME/FLIGHT NO.\t\t\t\tCHECK IN DATE\t\t\t\tCHECK OUT DATE\t\t\t\tAMOUNT\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(tempf!=0){
      printf("%10d %50s  %30d-%2d-%2d  %30d-%2d-%2d %32d\n",tempf->id, tempf->name, tempf->cin_day, tempf->cin_month, tempf->cin_year, tempf->cout_day, tempf->cout_month, tempf->cout_year, tempf->amount );
      tempf=tempf->next;
    }
  }
  printf("\nPress any key to return to main menu...\n");
  getch();
  menu(temp->username);
}

//TravalistaCoreFunctions
void flightBooking() {
  clrscr();
  printf("****************WELCOME TO TRAVELISTA FLIGHT BOOKING MODE********************\n");
  printf("While booking flights with TRAVELISTA, you can expect the ultimate online booking experience.\n With premium customer service, 24/7 dedicated helpline for support, TRAVELISTA takes great pride in enabling customer satisfaction.\n With a cheapest flight guarantee, book your tickets at the lowest airfares.\n Avail great offers, exclusive deals for loyal customers and get instant updates for your flight status and fare drops.");
  display();
}
void hotelBooking() {
  keyPressed = 0; position = 1;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("Choose among the following countries:-\n");
    arrorHere(1, position); printf("1.\tDubai\n");
    arrorHere(2, position); printf("2.\tEurope\n");
    arrorHere(3, position); printf("3.\tFrance\n");
    arrorHere(4, position); printf("4.\tHong Kong\n");
    arrorHere(5, position); printf("5.\tRussia\n");
    arrorHere(6, position); printf("6.\tSingapure\n");
    arrorHere(7, position); printf("7.\tSouth Korea\n");
    arrorHere(8, position); printf("8.\tSpain\n");
    arrorHere(9, position); printf("9.\tToronto\n");
    arrorHere(10, position); printf("10.\tUK\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 10) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }

  switch(position) {
    case 1: hotelPrinting("Dubai"); break;

    case 2: hotelPrinting("Europe"); break;

    case 3: hotelPrinting("France"); break;

    case 4: hotelPrinting("HongKong"); break;

    case 5: hotelPrinting("Russia"); break;

    case 6: hotelPrinting("Singapure"); break;

    case 7: hotelPrinting("SouthKorea"); break;

    case 8: hotelPrinting("Spain"); break;

    case 9: hotelPrinting("Toronto"); break;

    case 10: hotelPrinting("UK"); break;

    default: printf("Invalid Choice, Press any key to try again.\n"); hotelBooking();
  }
  getch();
}
void feedback() {
  clrscr();
  char fback[10000];
    int rate;
    printf("Rate us out of 5:\n");
    printf("1 for Unsatisfied\n2 for Can-be-better\n3 for Average\n4 for Good\n5 for Excellent\nEnter your choice: ");
    scanf("%d", &rate);
    printf("Thanks for rating\n");
    printf("\nPlease provide your feedback.... Highly appreciated!\nBegin typing >>> ");
    fflush(stdin);
    gets(fback);
    FILE *fp = fopen("./Source Files/Feedbacks.txt", "a+");
    fprintf(fp, "%s\n\n", fback);
    fclose(fp);
    printf("Thanks a lot for the feedback!\nPress any key to return to main menu.");
    getch();
    menu(temp->username);
}
void aboutUs() {
 clrscr();
 printf("_______________\n");
 printf("BATCH   A2\nBRANCH   ECE\n");
 printf("_______________\n");
 printf("\nMADE BY\n");
 printf("\n\nNAME\t\t\t\tENROLLMENT NUMBER\n");
 printf("_________________________________________________\n");
 printf("ISHIKA SHARMA\t\t\t\t18102034\n" );
 printf("_________________________________________________\n");
 printf("KHUSHI SRIVASTAVA\t\t\t18102035\n" );
 printf("_________________________________________________\n");
 printf("PRANAV JAIN\t\t\t\t18102039\n" );
 printf("_________________________________________________\n");
 printf("SATYAM RAJPOOT\t\t\t\t18102234\n");
 printf("_________________________________________________\n");

}


//MainMenuFunction
void menu(char mname[]) {
  system("COLOR F0");
  freeHotel();
  scanID();
  freeFilenode();
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("\n\t\t\t\t\t---------------------------------------- TRAVALISTA ---------------------------------------------\n");
    printf("\t\t\t\t\t Login Date and Time\t\t\t\t\t\t\t\tWelcome @%s\n ", mname);
    currentTime();
    printf("\n\t\t\t\t\tChoose among the following:-\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(1, position); printf("1. Flight Booking\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(2, position); printf("2. Hotel Booking\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(3, position); printf("3.  Previous Records\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(4, position); printf("4. About us\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(5, position); printf("5. Feedback\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n");
    printf("\t\t\t\t\t"); arrorHere(6, position); printf("0. Exit\n");
    printf("\t\t\t\t\t-------------------------------------------------------------------------------------------------\n\n\n");
    printf("\t\t\t\t\t\t\t\t>>> USE UP AND DOWN ARROW KEYS FOR NAVIGATION <<<\n\n");
    keyPressed = getch();

    if(keyPressed == 80 && position != 6) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1: flightBooking(); break;
    case 2: hotelBooking(); break;
    case 3: displayPreviousRecords(headHK, tempHK); break;
    case 4: aboutUs(); break;
    case 5: feedback(); break;
    case 6: exit(0); break;
  }
}

//AdminFunctions
void userList(USER *head, USER* temp){
  int n;
  char sname[25];
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("CHOOSE FROM THE OPTIONS:\n");
    arrorHere(1, position); printf("1. Search for a user\n");
    arrorHere(2, position); printf("2. Show complete list\n");
    keyPressed = getch();

    if(keyPressed == 80 && position != 2) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1:{
      printf("Enter username:\n");
      scanf("%s",sname);
      temp=head;
      while(temp!=NULL) {
        if(strcmp(temp->username,sname) == 0) {
          clrscr();
          printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
          printf("USERNAME\t\t\t\tNAME\t\t\t\tCONTACT\t\t\t\tADDRESS\n");
          printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
          printf("%s\t\t\t%s %s\t\t\t\t%s\t\t\t\t%s %s \n",temp->username, temp->ed.fName, temp->ed.lName, temp->ed.contact, temp->ed.city, temp->ed.state);
        }
        temp=temp->next;
      }
      if(temp->next == NULL && strcmp(temp->username,sname) != 0) {
        printf("USER NOT FOUND..\n");
      }
      break;
    }
    case 2:{
      clrscr();
      if(head==0) printf("NO USER FOUND>>\n");
      else{
        temp=head;
        printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("USERNAME\t\t\t\tNAME\t\t\t\tCONTACT\t\t\t\tADDRESS\n");
        printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while(temp!=NULL){
          printf("%s\t\t\t%s %s\t\t\t\t%s\t\t\t\t%s %s \n",temp->username, temp->ed.fName, temp->ed.lName, temp->ed.contact, temp->ed.city, temp->ed.state);
          temp=temp->next;
        }
      }
      printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }
  }
  getch();
}
void recordBook(){
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("CHOOSE FROM THE OPTIONS:\n");
    arrorHere(1, position); printf("1. Flight records\n");
    arrorHere(2, position); printf("2. Hotel records\n");
    keyPressed = getch();

    if(keyPressed == 80 && position != 2) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position){
    case 1:{
      clrscr();
      temp=head;
      tempf=headf;
      if(temp==0){  if(tempf==0){
          printf("NO FLIGHT RECORDS TO SHOW.\n");
        }
      }
      else{
        clrscr();
        temp=head;
        tempf=headf;
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("TRAVLIZ ID\t\t\t\tNAME\t\t\t\tBOARDIND DATE\t\t\t\tAMOUNT PAID\n" );
        printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while(temp!=NULL){
          tempf = headf;
          char tname[100];
          char path[] = "./Source Files/USERS\\";
          strcpy(tname, path);
          strcat(tname, temp->username);
          strcat(tname, ".txt");
          FILE *fp = fopen(tname, "r");
          while(tempf != NULL) {
            fprintf(fp, "%c %d %s %d-%d-%d %d-%d-%d %d\n", tempf->key, tempf->id, tempf->name, tempf->cin_day, tempf->cin_month, tempf->cin_year, tempf->cout_day, tempf->cout_month, tempf->cout_year, tempf->amount);
            if(tempf->key=='h'){
            printf("%d\t\t\t\t%s %s\t\t\t\t%d-%d-%d\t\t\t\t%d\n",tempf->id,tempf->name,tempf->cin_day,tempf->cin_month,tempf->cin_year,tempf->amount);
            }
           tempf=tempf->next;
         }
        fclose(fp);
          }
          temp=temp->next;
        }
      }
    case 2:{
      clrscr();
      temp=head;
      tempf=headf;
      if(temp==0){
        if(tempf==0){
          printf("NO HOTEL RECORDS TO SHOW.\n");
        }
      }
        else{
        clrscr();
        temp=head;
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("TRAVLIZ ID\t\t\t\tNAME\t\t\t\tCHECK IN DATE\t\t\t\tCHECK OUT DATE\t\t\t\tAMOUNT PAID\n" );
        printf("-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        while(temp!=NULL){
          tempf = headf;
          char tname[100];
          char path[] = "./Source Files/USERS\\";
          strcpy(tname, path);
          strcat(tname, temp->username);
          strcat(tname, ".txt");
          FILE *fp = fopen(tname, "r");
          while(tempf != NULL) {
            fprintf(fp, "%c %d %s %d-%d-%d %d-%d-%d %d\n", tempf->key, tempf->id, tempf->name, tempf->cin_day, tempf->cin_month, tempf->cin_year, tempf->cout_day, tempf->cout_month, tempf->cout_year, tempf->amount);
            if(tempf->key=='h'){
            printf("%d\t\t\t\t%s %s\t\t\t\t%d-%d-%d\t\t\t\t%d-%d-%d\t\t\t\t%d\n",tempf->id,tempf->name,tempf->cin_day,tempf->cin_month,tempf->cin_year,tempf->cout_day,tempf->cout_month,tempf->cout_year, tempf->amount);
            }
           tempf=tempf->next;
         }
        fclose(fp);
        temp=temp->next;
      }
     }
    }
   }
 }
void revenue() {
  clrscr();
  printf("Revenue earned by the program: %d\n\nPress any key to return to Admin Menu...", totalRevenue);
  getch();
  adminMenu();
}
void usrfeeds() {
  char feed[10000]; int r;
  FILE *fp = fopen("./Source Files/Feedbacks.txt", "r+");
  while(!feof(fp)) {
    fscanf(fp, "%s\n\n", feed);
    printf("%s ", feed);
  }
  fclose(fp);
}
void adminMenu() {
  scanID();
  position = 1; keyPressed = 0;
  clrscr();
  while(keyPressed != 13) {
    clrscr();
    printf("\t\t\t\t\t\t\t\t\t");printf(":::::::::::::::ADMIN MENU:::::::::::::::\n\n");
    printf("\t\t\t\t\t\t\t\t\t");arrorHere(1, position); printf("1. List of users\n");
    printf("\t\t\t\t\t\t\t\t\t");arrorHere(2, position); printf("2. Total Bookings\n");
    printf("\t\t\t\t\t\t\t\t\t");arrorHere(3, position); printf("3. Amount generated \n");
    printf("\t\t\t\t\t\t\t\t\t");arrorHere(4, position); printf("4. Feedbacks\n");
    printf("\t\t\t\t\t\t\t\t\t");arrorHere(5, position); printf("0. Exit\n");
    keyPressed = getch();
    if(keyPressed == 80 && position != 5) {
      position++;
    }else if(keyPressed == 72 && position != 1) {
      position--;
    }else {
      position = position;
    }
  }
  switch(position) {
    case 1:userList(head, temp); break;

    case 2: recordBook(); break;

    case 3: revenue(); break;

    case 4: usrfeeds(); break;

    case 5: exit(0); break;
  }
  getch();
}


//LoginIntoDatabaseFunctions
void fileToList() {
  clrscr();
  printf("LOADING DATABASE......\n");
  FILE *fp = fopen("./Source Files/Database.txt", "r");
  while(!feof(fp)) {
    newNode = (USER *)malloc(sizeof(USER));
    fscanf(fp, "%s %s %s %s %d %d %d %s %s %s\n", newNode->username, newNode->password, newNode->ed.fName, newNode->ed.lName,
     &newNode->ed.eb.day, &newNode->ed.eb.month, &newNode->ed.eb.year, newNode->ed.contact, newNode->ed.state, newNode->ed.city);
     if(head != 0) {
       temp->next = newNode;
       temp = newNode;
     }
     else {
       head = temp = newNode;
     }
  }
  temp->next = NULL;
  fclose(fp);
}
void adminLogin() {
  clrscr();
  char aPass[25];
  printf("ENTER ADMINSTRATOR PASSWORD:\n");
  scanf("%s",aPass);
  if(strcmp(aPass,"admintravaliz")==0){
    adminMenu();
  }
  else {
    printf("ADMIN PASSWORD INVALID!!\nPress any key to login again.\n");
    getch();
    adminLogin();
  }
}
void createUser() {
  newNode = (USER *)malloc(sizeof(USER));
  printf("Username: ");
  scanf("%s", newNode->username);
  printf("Password: ");
  scanf("%s", newNode->password);
  printf("\n-----Fill the form-----\n");
  printf("First Name: ");
  scanf("%s", newNode->ed.fName);
  printf("Last Name: ");
  scanf("%s", newNode->ed.lName);
  printf("Birth Date (dd-mm-yyyy): ");
  scanf("%d-%d-%d", &newNode->ed.eb.day, &newNode->ed.eb.month, &newNode->ed.eb.year);
  printf("Contact number: ");
  scanf("%s", newNode->ed.contact);
  printf("State: ");
  scanf("%s", newNode->ed.state);
  printf("City: ");
  scanf("%s", newNode->ed.city);

  if(head != 0) {
    temp->next = newNode;
    temp = newNode;
  }
  else {
    head = temp = newNode;
  }
  temp->next = NULL;
  FILE *fp = fopen("./Source Files/Database.txt", "a");
  fprintf(fp,"%s %s %s %s %d %d %d %s %s %s\n", temp->username, temp->password, temp->ed.fName, temp->ed.lName,
   temp->ed.eb.day, temp->ed.eb.month, temp->ed.eb.year, temp->ed.contact, temp->ed.state, temp->ed.city);
  printf("\nUser registered successfully.\n\nPROGRAM WILL NOW QUIT, RESTART TO LOGIN.\n\nPress any key to continue.");
  fclose(fp);
  getch();
  //File for the user created
  char tname[100];
  char path[] = "./Source Files/USERS\\";
  strcpy(tname, path);
  strcat(tname, temp->username);
  strcat(tname, ".txt");

  fp = fopen(tname, "w+");

  fclose(fp);
  exit(0);
}
void loginCheck(char uname[], char upass[]) {
  temp = head;
  while(temp != NULL) {
    if(strcmp(uname, temp->username) == 0) {
      if(strcmp(upass, temp->password) == 0) {
        fileRetrive();
        menu(temp->username);
        temp = head;
        break;
      }
      else {
        printf("Invalid Password!\nPress any key to login again.\n\n");
        getch();
        clrscr();
        login();
        break;
      }
    }
    else if (strcmp(uname, temp->username) != 0) {
      temp = temp->next;
    }
  }
  if(temp == NULL) {
    printf("User not found,  Register first.\n\nPROGRAM WILL NOW QUIT.\n"); getch();
    exit(0);
  }
}
void login() {
  char tuname[25], tupass[25];
  printf("\n\t\t\t\t\t\t\t\t\t"); printf("Username: ");
  scanf("%s", tuname);
  printf("\t\t\t\t\t\t\t\t\t"); printf("Password: ");
  scanf("%s", tupass);
  loginCheck(tuname, tupass);
}
void userPortal() {
  #define MAX 3
  #define MIN 1
  while(keyPressed != 13) {
    clrscr();
    printf("\t\t\t\t\t\t\t\t\t<<<<<<<<<<<<<< TRAVALISTA >>>>>>>>>>>>>>\n");
    printf("\n\t\t\t\t\t\t\t\t\t\t     :::USERLOGIN:::\n\n");
    printf("\t\t\t\t\t\t\t\t\t"); arrorHere(1, position); printf("1. LOGIN\n");
    printf("\t\t\t\t\t\t\t\t\t"); arrorHere(2, position); printf("2. SIGNUP\n\n");
    printf("\t\t\t\t\t\t\t\t\t"); arrorHere(3, position); printf("0. << ADMINLOGIN >>\n");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t    >>> USE UP AND DOWN ARROW KEYS FOR NAVIGATION <<<\n\n");

    keyPressed = getch();

    if(keyPressed == 80 && position != MAX) {
      position++;
    }else if(keyPressed == 72 && position != MIN) {
      position--;
    }else {
      position = position;
    }
  }

  switch(position) {
    case 1: login(); break;
    case 2: createUser(); break;
    case 3: adminLogin(); break;
    default: printf("Invalid choice.\n"); clrscr(); userPortal();

  }
  getch();
}

int main() {
  fileToList();
  system("COLOR F0");
  userPortal();
  return 0;
}
