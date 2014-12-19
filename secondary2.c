#include <stdio.h>
#include <stdlib.h>
#include "structs2.h"

#define MAX 100

Client create_account(void)
{
    int i;

    Client person;

    do{
        i = 0;
        printf("\n\t\tName: ");
        while(((person.name[i]=getchar())!= '\n')&&(i<MAX)){i++;}
        person.name[i] = '\0';
    } while (!name_validation(person.name)); /*preciso ver name_validation, parametros*/

    do{
        printf("\n\t\tCellphone number: ");
        scanf("%d",&person.cell);
    }while(!cell_validation(person.cell));

    person.id_client = id_client;       /* id_client is a global variable */

    printf("\n\t\tYou were given \033[4;33m%d\033[0m as your client id.\n\n",id_client);

    id_client++;                        /* id_client is a global variable */

    return person;
}

void book_it(Booking *book, int id, int op)
{
    int valid;

    printf("\n\t\tBook date (d m y): ");
    scanf("%*c%d%*[ \n\t|.:]%d%*[ \n\t|.:]%d", &book->slot.client_date.day, &book->slot.client_date.month, &book->slot.client_date.year);
    
    valid = date_validation(book->slot.client_date); /*checks if date is valid or not*/

    switch(valid){
        case 1: /*if so, then ask for time*/
        {
            valid = 0;
            while(!valid){  
                printf("\n\t\tBook hour (hh:mm): ");
                scanf("%*[ \n\t|.:]%d%*[ \n\t|.:]%d",&book->slot.client_hour.hour,&book->slot.client_hour.minutes);
                valid = hour_validation(book->slot.client_hour,op); /*checks if hour is valid or not*/
            }
            break;
        }
	break;      
        default: /*if not, then ask again*/
        {
            while(!valid){
                printf("\n\t\t\033[0;91mWe're sorry, but that's not a valid date.\033[0m\n\n\t\tBook date: ");
                scanf("%*c%d%*[ \n\t|.:]%d%*[ \n\t|.:]%d", &book->slot.client_date.day, &book->slot.client_date.month, &book->slot.client_date.year);
                valid = date_validation(book->slot.client_date); /*checks again if date is valid or not*/
            }
            
            valid = 0;
            
            while(!valid){
                printf("\n\t\tBook hour (hh:mm): ");
                scanf("%*[ \n\t|.:]%d%*[ \n\t|.:]%d",&book->slot.client_hour.hour,&book->slot.client_hour.minutes);
                valid = hour_validation(book->slot.client_hour, op); /*checks again if hour is valid or not*/
            }
            break;
        }
	break;
    }
    /*when all is checked, book structure gets the client id*/
    book->id = id;
}

int compare(Date d1, Hours h1, Date d2, Hours h2)
{
    int date1, date2, hour1, hour2;
    date1 = ((d1.year)*10000)+((d1.month)*100)+d1.day;
    date2 = ((d2.year)*10000)+((d2.month)*100)+d2.day;
    hour1 = ((h1.hour)*100)+(h1.minutes);
    hour2 = ((h2.hour)*100)+(h2.minutes);

    if(date1 > date2)
    {
        return 0;
    }
    else if(date2 > date1)
    {
        return 1;
    }
    else
    {
        if(hour2 > hour1){
            return 1;
        }
        else if(hour2 == hour1){
            return 2;
        }
        else{
            return 0;
        }
    }
}

int cell_validation(int cell)
{
    int digit;
    int i;
    for(i=1;i<10;i++){
        digit = cell%10;
        cell = (cell-digit)/10;
        if(cell==0){
            break;
        }
    }
    return (i==9);  /*short-form*/
}

int date_validation(Date date)
{
    int valid = 0;
    int days_of_months[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	if ((date.month<=5 && date.day < 31) && date.year <= 2014)
        valid = 0;
    else if (date.day>0 && date.day <= days_of_months[date.month-1] && date.month >0 && date.month<13 && date.year >0)
        valid = 1;
    else if (date.month==2 && date.day == 29 && /*check if leap year*/ !(date.year % 4 == 0 && (date.year % 100 != 0 || date.year % 400 == 0)))
        valid = 0;
    return valid;
}

int hour_validation(Hours hours, int op){
    int valid = 0;
    
    if(op == 2)
    {
        if (hours.hour<18 && hours.hour>=8)
        {
            switch(hours.minutes){
                case 00: valid = 1; break;
                case 30: valid = 0; printf("\n\t\tFixes start at the beggining of each hour.\n\n"); break;
                case 60: {hours.hour++; hours.minutes = 00; valid = 1;} break;
                default: valid=0; printf("\n\t\tFixes start at the beggining of each hour.\n\n"); break;
            }
        }
        else{
            printf("\n\t\t\033[0;91mSchedule: 8.00 AM -- 18.00 PM\033[0m\n");
        }
    }
    else
    {
        if (hours.hour<18 && hours.hour>=8)
        {
            switch(hours.minutes){
                case 00: valid = 1; break;
                case 30: valid = 1; break;
                case 60: {hours.hour++; hours.minutes = 00; valid = 1;} break;
                default: valid=0; break;
            }
        }
        else{
            printf("\n\t\t\033[0;91mSchedule: 8.00 AM -- 18.00 PM\033[0m\n");
        } 
    }
    return valid;
}

int name_validation(char *original){
    int i;
    if (*(original)==' ') return 0;

    for (i=0;*(original+i);i++)
        if (!(((*(original+i)>='A') && (*(original+i)<='Z')) || ((*(original+i)>='a') && (*(original+i)<='z')) || ((*(original+i)==' ') )))
            return 0;
    return 1;
}

int check_file(FILE *fp,char *filename)
{

    if (fp==NULL){      /*if file doesnt exist....*/            /*  (R E D )=  \033[1;31 */  /*(R E S E T)=  \033[0m*/
        printf("\t\t\n\033[1;31mError while opening '%s'. File not loaded.\033[0m\n" ,filename);       
        return 0;
    }else{
        return 1;
    } 
}


void load_image(char *filename)
{
    int c;
    FILE *file; 
    file = fopen("image.txt", "r");
    if (file) {
        while ((c = getc(file)) != EOF)
            putchar(c);
    }
    fclose(file);
    printf("\n");
}
int check_input(void)
{
    char key;
    while ((key = getchar()) != '\n');
}

int input_from_user(void){  

    int num;
    printf("\n\t\tWhat do you want to do: ");

    while(1){
        scanf("%d",&num);
        check_input();
        if ((num>=0) && (num<8)) break;
        printf("\n\t\tWhat do you want to do: ");
    }
    return num;
}

void booking_validation(books list_b, books list_pb, Booking *book,int op)
{
    int aux_book_day  = book->slot.client_date.day;
    int aux_book_month= book->slot.client_date.month;
    int aux_book_year = book->slot.client_date.year;
    int aux_book_hour = book->slot.client_hour.hour;
    int aux_book_minutes = book->slot.client_hour.minutes;


    books l;
    l = list_b->next; /* Salta o header */
    
    while (l!=NULL)
    {
        int aux_l_day  = l->info.slot.client_date.day;
        int aux_l_month= l->info.slot.client_date.month;
        int aux_l_year = l->info.slot.client_date.year;
        int aux_l_hour = l->info.slot.client_hour.hour;
        int aux_l_minutes = l->info.slot.client_hour.minutes;
        
        if ((aux_l_day==aux_book_day) && (aux_l_month==aux_book_month)&&(aux_l_year==aux_book_year)&&(aux_l_hour==aux_book_hour)&&(aux_l_minutes==aux_book_minutes)){
            printf("\n\t\t\033[1;33m+-------------------------------------------------------------+\033[0m\n");
            printf("\t\t\033[1;33m+\033[0m That hour is already booked for another client.      \033[1;33m+\033[0m\n");
            printf("\t\t\033[1;33m+\033[0m Your book will be added to the waiting list.       \033[1;33m+\033[0m\n");
            printf("\t\t\033[1;33m+-------------------------------------------------------------+\033[0m\n");
            insert_book(list_pb,book);
            if (op == 1)
            {
                write_to_file(list_pb,"wash_prebooks.txt");
            }
            else if(op == 2)
            {
                write_to_file(list_pb,"fix_prebooks.txt");
            }
            return ;
        }
        
        l=l->next;
    }
    insert_book(list_b,book);
}
