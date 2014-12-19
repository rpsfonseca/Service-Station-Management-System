/**************************************
*   Mini_Project - PPP  2013/2014     *
*   by Ricardo Fonseca e Adolfo Pinto *
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs2.h"
#include "secondary2.c"
#include "operations2.c"
#include "manipulation2.c"

int id_client;      /*global variable*/

int main()
{
    int num;
    books wash;
    books fix;
    books pbwash;
    books pbfix;
    Booking book;
    clients list;

    load_image("image.txt");        /* load company name in ascii art*/

    list  = create_clients();
    fix   = create_books();
    wash  = create_books();
    pbwash= create_books();
    pbfix = create_books();

    build_from_file(wash,"wash_books.txt");
    build_from_file(fix,"fix_books.txt");
    build_from_file(pbwash,"wash_prebooks.txt");           /*loads info*/
    build_from_file(pbfix,"fix_prebooks.txt");
    build_clients(list,"clients.txt");

    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    book.slot.client_date.day = timeinfo->tm_mday;
    book.slot.client_date.month = timeinfo->tm_mon+1;
    book.slot.client_date.year = timeinfo->tm_year+1900;

    while(1){
        book.slot.client_hour.hour = timeinfo->tm_hour;
        book.slot.client_hour.minutes = timeinfo->tm_min;

        end_book2(wash,&book,1);
        end_book2(fix,&book,2);
        end_book2(pbwash,&book,-1);
        end_book2(pbfix,&book,-2);
        
        printf("\n\n\n");
        printf("\t\t1. Book wash\n\n");
        printf("\t\t2. Book fix\n\n");
        printf("\t\t3. Cancel book\n\n");
        printf("\t\t4. Cancel pre-book\n\n");
        printf("\t\t5. Show wash and fix's books and pre-books ordered by date (older first)\n\n");
        printf("\t\t6. Show client's books and pre-books ordered by date (recent first)\n\n");
        printf("\t\t0. Exit\n\n");

        num = input_from_user();

        switch(num){
            case 1: booking(list,wash,pbwash,1);break;
            case 2: booking(list,fix,pbfix,2);break;
            case 3: delete_book(wash,pbwash,fix,pbfix);break;
            case 4: delete_prebook(pbwash,pbfix);break;
            case 5: print_all(wash,pbwash,fix,pbfix,list);break;
            case 6: print_of_client(wash,pbwash,fix,pbfix,list);break;
            default:return 0;break;
        };
    }
    destroy_books(wash);
    destroy_books(pbwash);
    destroy_books(fix);
    destroy_books(pbfix);
    destroy_clients(list);
    return 0;
}
