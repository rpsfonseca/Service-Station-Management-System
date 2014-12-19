#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs2.h"

books create_books(void)
{
    books aux;
    aux = (books) malloc (sizeof (books_node));
    if(aux != NULL){
        aux -> info.slot.client_date.day  = 0;
        aux -> info.slot.client_date.month= 0;
        aux -> info.slot.client_date.year = 0;

        aux -> info.slot.client_hour.hour = 0;
        aux -> info.slot.client_hour.minutes = 0;

        aux -> info.id = 0;

        aux -> next = NULL;
    }
    return aux;
}

clients create_clients(void)
{
    clients aux;
    aux = (clients) malloc (sizeof (clients_node));
    if(aux != NULL){
        aux -> info.id_client = 0;
        aux -> info.cell = 0;
        strcpy(aux->info.name,"0");

        aux -> next = NULL;
    }
    return aux;
}

books destroy_books(books list_b)
{
    books temp_ptr;
    while (empty_books(list_b) == 0)
    {
        temp_ptr = list_b; /*Points to the first node of the list of books*/
        list_b = list_b -> next;
        free(temp_ptr);
    }
    free(list_b);
    return NULL;
}

clients destroy_clients(clients list_c)
{
    clients temp_ptr; /*Creating a temporary list, in this case just a node, so we won't lose any node*/
    while(empty_clients(list_c) == 0) /*While the list is not empty, do that*/
    {
        temp_ptr = list_c; /*Points to the first node of the list of clients*/
        list_c = list_c -> next; /*The beggining of the list is now the next node*/
        free(temp_ptr); /*Wipes what was the first node of the list*/
    }
    free(list_c); /*Wipes the last node*/
    return NULL;
}

void delete_book_node(books list_b, books list_pb, int id,int op)
{
    char ltr;
    int count = 1;

    books ant;
    books actual;
    books ant1;
    books actual1;
    
    ant = list_b;
    actual = list_b->next;

    while(actual!=NULL)
    {
        if(actual->info.id == id)
        {
            printf("\n\t\t\033[0;33m+-------Booking %d-------+\033[0m\n",count);
            printf("\t\t\033[0;33m+\033[0m Date: %d/%d/%d\n",actual->info.slot.client_date.day,actual->info.slot.client_date.month,actual->info.slot.client_date.year);
            if(actual->info.slot.client_hour.minutes == 0){
                printf("\t\t\033[0;33m+\033[0m Hour: %d:%d0\n\n",actual->info.slot.client_hour.hour,actual->info.slot.client_hour.minutes);
            }
            else{
                printf("\t\t\033[0;33m+\033[0m Hour: %d:%d\n\n",actual->info.slot.client_hour.hour,actual->info.slot.client_hour.minutes);
            }
            printf("\t\tDo you want to delete? [y for yes, n for no]: "); getchar();
            ltr=getchar();
            if (ltr == 'y' || ltr == 'Y')
            {
                ant1=list_pb;
                actual1=list_pb->next;
                while(actual1!=NULL && compare(actual1->info.slot.client_date,actual1->info.slot.client_hour,actual->info.slot.client_date,actual->info.slot.client_hour)!=2){
                    ant1 = actual1;
                    actual1 = actual1->next;
                }
                if(actual1==NULL){
                    ant->next = actual->next;
                    free(actual);
                    actual = ant;
                }
                else if(actual1!=NULL)
                {
                    ant->next = actual->next;
                    free(actual);
                    insert_book(list_b,&actual1->info);
                    ant1->next=actual1->next;
                    free(actual1);
                    if (op == 1)
                    {
                        write_to_file(list_pb,"wash_prebooks.txt");
                    }
                    else if(op == 2)
                    {
                        write_to_file(list_pb,"fix_prebooks.txt");
                    }
                }
                if (op == 1)
                {
                    write_to_file(list_b,"wash_books.txt");
                }
                else if(op == 2)
                {
                    write_to_file(list_b,"fix_books.txt");
                }
                count++;
                printf("\n\t\t\033[0;32mBooking successfuly deleted!\033[0m");
            }
            
        }
        ant = actual;
        actual = actual->next;
    }
}

void delete_pbook_node(books list_pb, int id,int op)
{
    char ltr;
    int count = 1;

    books ant;
    books actual;
    
    ant = list_pb;
    actual = list_pb->next;

    if (actual == NULL){
        printf("\t\tThere are no pre-bookings.\n");
    }

    while(actual!=NULL)
    {
        if(actual->info.id == id)
        {
            printf("\n\t\t\033[0;33m+-------Pre-Booking %d-------+\033[0m\n",count);
            printf("\t\t\033[0;33m+\033[0m Date: %d/%d/%d\n",actual->info.slot.client_date.day,actual->info.slot.client_date.month,actual->info.slot.client_date.year);
            if(actual->info.slot.client_hour.minutes == 0){
                printf("\t\t\033[0;33m+\033[0m Hour: %d:%d0\n\n",actual->info.slot.client_hour.hour,actual->info.slot.client_hour.minutes);
            }
            else{
                printf("\t\t\033[0;33m+\033[0m Hour: %d:%d\n\n",actual->info.slot.client_hour.hour,actual->info.slot.client_hour.minutes);
            }
            printf("\t\tDo you want to delete? [y for yes, n for no]: "); getchar();
            ltr=getchar();
            if (ltr == 'y' || ltr=='Y'){
                ant->next = actual->next;
                free (actual);
                if (op == 1){
                    write_to_file(list_pb,"wash_prebooks.txt");
                }
                else if(op == 2){
                    write_to_file(list_pb,"fix_prebooks.txt");
                }
                printf("\n\t\t\033[0;32mPre-Booking successfuly deleted!\033[0m\n");
            }
            actual=ant;
            count++;
        }
        ant = actual;
        actual = actual->next;
    }
}

void end_book2(books list_b, Booking *book, int l)
{
    books ant;
    books actual;
    ant = list_b;
    actual = list_b->next;
    while(actual!=NULL && compare(actual->info.slot.client_date,actual->info.slot.client_hour,book->slot.client_date,book->slot.client_hour))
    {
        ant->next = actual->next;
        free(actual);
        actual = ant;
        ant = actual;
        actual = actual->next;
    }
    if (l == -1){
        write_to_file(list_b,"wash_prebooks.txt");
    }
    else if(l == -2){
        write_to_file(list_b,"fix_prebooks.txt");
    }
    else if (l == 1){
        write_to_file(list_b,"wash_books.txt");
    }
    else if(l == 2){
        write_to_file(list_b,"fix_books.txt");
    }
}

int empty_books(books list_b)
{
    return(list_b == NULL ? 1 : 0);
}

int empty_clients(clients list_c)
{
    return(list_c == NULL ? 1 : 0);
}

void search_books(books list_b, Booking *book, books *ant, books *inutil)
{
    *ant = list_b; *inutil = list_b->next;
    while ((*inutil)!= NULL && compare((*inutil)->info.slot.client_date, (*inutil)->info.slot.client_hour, (*book).slot.client_date, (*book).slot.client_hour))
    {
        *ant = *inutil;
        *inutil = (*inutil)->next;
    }
    if ((*inutil) != NULL && compare((*inutil)->info.slot.client_date, (*inutil)->info.slot.client_hour, (*book).slot.client_date, (*book).slot.client_hour))
    {
        *inutil = NULL; /*If element not found*/
    }
}

void search_books_id(books list_b, int id, books *ant, books *actual)
{
    *ant = list_b; *actual = list_b->next;
    while (((*actual) != NULL) && ((*actual)->info.id < id))
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if (((*actual) != NULL) && ((*actual)->info.id != id)){
        *actual = NULL; /* If element not found*/
    }
}

void search_clients_id(clients list_c, int id, clients *ant, clients *actual)
{
    *ant = list_c; *actual = list_c->next;
    while (((*actual) != NULL) && ((*actual)->info.id_client < id))
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if (((*actual) != NULL) && ((*actual)->info.id_client != id)){
        *actual = NULL; /* If element not found*/
    }
}

void search_clients_cell(clients list_c, int cell, clients *ant, clients *actual)
{
    *ant = list_c; *actual = list_c->next;
    while (((*actual) != NULL) && ((*actual)->info.cell != cell))
    {
        *ant = *actual;
        *actual = (*actual)->next;
    }
    if (((*actual) != NULL) && ((*actual)->info.cell != cell))
    {
        *actual = NULL; /* If element not found*/
    }
}

void insert_book(books list_b, Booking *book)
{
    books no;
    books ant, inutil;
    no = (books) malloc (sizeof (books_node));
    if (no != NULL) {
        no->info = *book;
        search_books(list_b, book, &ant, &inutil);
        no->next = ant->next;
        ant->next = no;
    }
}

void insert_client(clients list_c, Client *person)
{
    clients no;
    clients ant, actual;
    no = (clients)malloc(sizeof(clients_node));
    if(no != NULL){
        no->info = *person;
        search_clients_id(list_c, person->id_client, &ant, &actual);
        no->next = ant->next;
        ant->next = no;
    }
}

void print_list(books list_b, clients list_c)
{
    int count = 1;

    books l = list_b->next;            /* Skips the header */   /*\e[1;33m*/
    clients ant;
    clients actual;
    
    if(l==NULL){
        printf("\t\tThere are no pre-bookings/bookings.\n");
    }
    while (l!= NULL)
    {
        printf("\n");
        printf("\t\t+-------------------------------------------------------------------------+\n");
        printf("\t\t+    \033[0;32mClient name \033[0m\033[91m%d\033[0m\033[0m      |   \033[0;32mDate\033[0m     |    \033[0;32mHour\033[0m     |    \033[0;32mClient id\033[0m |\n",count);
        printf("\t\t+-------------------------------------------------------------------------+\n");
        search_clients_id(list_c,l->info.id,&ant,&actual);
        if(l->info.slot.client_hour.minutes == 0){
            printf("%38s \t %7d/%d/%d %7d:%d0  \t%9d",actual->info.name,l->info.slot.client_date.day, l->info.slot.client_date.month, l->info.slot.client_date.year,l->info.slot.client_hour.hour, l->info.slot.client_hour.minutes,l->info.id);
        }
        else{
            printf("%38s \t %7d/%d/%d  %7d:%d  \t%9d",actual->info.name,l->info.slot.client_date.day, l->info.slot.client_date.month, l->info.slot.client_date.year,l->info.slot.client_hour.hour, l->info.slot.client_hour.minutes,l->info.id);
        }
        count++;
        l=l->next;
    }
}

void recursive_id(books list_b, int id)
{
    if(list_b== NULL){
        /*printf("\t\tEste cliente nao tem pre-reservas/reservas deste tipo\n");*/
        return;
    }
    recursive_id(list_b->next,id);      /* recursive call */
    if(list_b->info.id==0)
        return;
    else if(list_b->info.id==id){
        printf("\n");
        printf("\t\t\033[0;96mDate:\033[0m %d/%d/%d \033[0;96mHour:\033[0m %d:%d \n",list_b->info.slot.client_date.day, list_b->info.slot.client_date.month, list_b->info.slot.client_date.year,list_b->info.slot.client_hour.hour, list_b->info.slot.client_hour.minutes);
        
    }
}

void build_from_file(books list_b, char *filename)
{  
    
    int size;
    Booking book;
    

    FILE *fp;    
    fp = fopen(filename,"r");           /* open text file for reading */
    

    if (check_file(fp,filename))
    {
        fseek(fp, 0, SEEK_END);         /* seek to the 0th byte before the end of file */
        size = ftell(fp);               /* Returns the current value of the position indicator of the stream. */
        fseek(fp, 0, SEEK_SET);         /* seek to the beginning of the file */
        

        while (ftell(fp)!=size)         /*til the very end */
        { 
            fscanf(fp,"%d %d %d\n",&book.slot.client_date.day,&book.slot.client_date.month,&book.slot.client_date.year);
            fscanf(fp,"%d %d\n",&book.slot.client_hour.hour,&book.slot.client_hour.minutes);
            fscanf(fp,"%d\n",&book.id);
           
            insert_book(list_b,&book);
        }

        fclose(fp);
    }    
}

void build_clients(clients list_c, char *filename)   
{
    int size;
    Client person;    

    FILE *fp;    
    fp = fopen(filename,"r");       /* open text file for reading */
    

    if (check_file(fp,filename))
    {
        fseek(fp, 0, SEEK_END);     /* seek to the 0th byte before the end of file */
        size = ftell(fp);           /* Returns the current value of the position indicator of the stream. */
        fseek(fp, 0, SEEK_SET);     /* seek to the beginning of the file */


        while (ftell(fp)!=size) /*til the very end */
        { 
            fscanf(fp,"%100[^\n]%*c",person.name); /*special case in fscanf :%100[^\n]%*c  names with spaces allowed*/
            
            fscanf(fp,"%d",&person.cell);
            fscanf(fp,"%d",&person.id_client);
        
            insert_client(list_c,&person);
        }
        id_client = person.id_client + 1;

        fclose(fp);
    }
}

void write_to_file(books list_b, char *filename)
{

    Booking book;
    books l_b;

    FILE *fp;    
    fp = fopen(filename,"w+");      /* Open for reading and writing. */
    

    if (check_file(fp,filename))
    {
        l_b = list_b -> next;
        while (l_b!=NULL)           /*til the very end */
        { 
            book = l_b->info;
            
            fprintf(fp,"%d %d %d\n",book.slot.client_date.day,book.slot.client_date.month,book.slot.client_date.year);
            fprintf(fp,"%d %d\n",book.slot.client_hour.hour,book.slot.client_hour.minutes);
            fprintf(fp,"%d\n",book.id);

            l_b = l_b -> next;
        }

        fclose(fp);
    }    
}

void write_client(Client *person, char *filename)
{

    FILE *fp;    
    fp = fopen(filename,"a");           /* open  for  appending  (writing  at  end  of file) */
    
    if (check_file(fp,filename))
    {
        fprintf(fp,"%s\n",person->name);                                                                                                                                                                                                                              
        fprintf(fp,"%d\n",person->cell);
        fprintf(fp,"%d\n",person->id_client);
        
        fclose(fp);
    }
}
