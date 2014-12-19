#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs2.h"

#define MAX 100

void booking(clients list, books type, books type2,int op)
{
	char ans;
	int num_c, verif;
	
	Booking book;

	printf("\n\t\tAlready have a client account? [y for yes; n for no]: ");
	ans = getchar();

	/*unacceptable answer*/
	while(ans!= 'n' && ans != 'N' && ans != 'y' && ans != 'Y'){
		getchar();
		printf("\n\t\tOnly y or n are accepted.\n\n\t\tPlease, enter a new answer: ");getchar();
		ans = getchar();
	}

	/*acceptable answers*/
	if(ans == 'n' || ans == 'N'){ /*no client account, creating one*/
		Client person;
		printf("\n\t\t\033[0;92mCreate new account:\033[0m\n");
	
		getchar();
		person = create_account();
		insert_client(list, &person);
		write_client(&person, "clients.txt");
		book_it(&book, person.id_client, op);
		booking_validation(type,type2,&book,op);
		printf("\n\t\t\033[0;92m***Successfuly booked***\033[0m\n");
	}

	else if(ans == 'y' || ans == 'Y'){
		clients ant;
		clients actual;
		/*has client account, going to check who that person is*/
		printf("\n\t\tEnter client id: ");
		scanf("%d", &num_c);
		
		search_clients_id(list, num_c, &ant, &actual); /*searches for the client id*/

		if(actual == NULL){
			/*If it doesn't exist, maybe it was a mistake, let's double check*/
			printf("\n\t\tClient id does not exist. Please enter cellphone number: ");
			scanf("%d",&verif); /*using second parameter, cellphone number*/

			search_clients_cell(list, verif, &ant, &actual); /*searches for the client cellphone*/

			if(actual == NULL) /*If it doesn't exist, then the account doesn't exist either*/
			{
				Client person;
				printf("\n\t\tThere's no account for that client. Let's create a new one.\n\n");
				getchar();
				person = create_account(); /*Than, let's create one*/
				insert_client(list, &person);
				write_client(&person, "clients.txt");
				book_it(&book,num_c, op);
				booking_validation(type,type2,&book,op);
			}
			else if(actual != NULL){ /*If the id exists, the account exists; Let's confirm by the name*/
				/*Going to show cellphone and name, and then ask to confirm to proceed*/
				printf("\n\t\tClient name: "); puts(actual->info.name);
				printf("\n\t\tCellphone number: %d\n\n", actual->info.cell);

				printf("\t\tConfirm? [y for yes; n for no]: ");getchar();
				ans = getchar();
				
				/*if confirmed, proceed to booking*/
				if(ans == 'y' || ans == 'Y'){
					book_it(&book, num_c, op);
					booking_validation(type,type2,&book,op); /*checks if book is valid or not*/
				}
			}
		}
		else if(actual != NULL){ /*If the id exists, the account exists; Let's confirm by the name*/
			/*Going to show cellphone and name, and then ask to confirm to proceed*/
			printf("\n\t\tClient name: "); puts(actual->info.name);
			printf("\n\t\tCellphone number: %d\n\n", actual->info.cell);

			printf("\t\tConfirm? [y for yes; n for no]: ");getchar();
			ans = getchar();
			
			/*if confirmed, proceed to booking*/
			if(ans == 'y' || ans == 'Y'){
				book_it(&book, num_c, op);
				booking_validation(type,type2,&book,op); /*checks if book is valid or not*/
			}
		}
	}
	if (op == 1){
	    write_to_file(type,"wash_books.txt");
	}
	else if(op == 2){
	    write_to_file(type,"fix_books.txt");
	}
}


void delete_book(books wash,books pbwash,books fix,books pbfix)
{
    int a,tipo;
    tipo = 0;

    while(tipo!=2 && tipo != 1){
        printf("\n\t\tType of booking (1 for wash, 2 for fix): ");
        scanf("%d",&tipo);
        if(tipo==1 && wash->next==NULL){
        	printf("\n\t\t\033[1;31mThere are no wash books.\033[0m\n");
        	return;
        }
        else if(tipo==2 && fix->next==NULL){
        	printf("\n\t\t\033[1;31mThere are no fix books.\033[0m\n");
        	return;
        }
    }
    printf("\n\t\tEnter client's id: ");
    scanf("%d",&a);
    switch(tipo){
        case 1:	delete_book_node(wash, pbwash, a,tipo);break;
        case 2: delete_book_node(fix, pbfix, a,tipo); break;
        default: break;
    }
}

void delete_prebook(books pbwash, books pbfix)
{
    int a,tipo;
    tipo = 0;

    while(tipo!=2 && tipo != 1){
        printf("\n\t\tType of pre-booking (1 for wash, 2 for fix): ");
        scanf("%d",&tipo);
        if(tipo==1 && pbwash->next==NULL){
        	printf("\n\t\t\033[1;31mThere are no wash bookings.\033[0m\n");
        	return;
        }
        else if(tipo==2 && pbfix->next==NULL){
        	printf("\n\t\t\033[1;31mThere are no fix bookings.\033[0m\n");
        	return;
        }
    }
    printf("\n\t\tEnter client's id: ");
    scanf("%d",&a);
    switch(tipo){
        case 1: delete_pbook_node(pbwash, a, tipo); break;
        case 2: delete_pbook_node(pbfix, a, tipo); break;
        default: break;
    }
}


void print_all(books wash,books pbwash,books fix,books pbfix,clients list)
{
	printf("\t\t\033[0;93m===========================================================================\n");
	printf("\t\t===============================\033[0;93mW A S H E S\033[0;93m=============================\n");
	printf("\t\t\033[0;93m===========================================================================\033[0;32m\n");
	printf("\t\t=============================  B O O K I N G S  ===========================\n");
	printf("\t\t===========================================================================\033[0m\n");

	print_list(wash,list);

	printf("\n\t\t\033[0;32m===========================================================================\n");
	printf("\t\t=========================  P R E --B O O K I N G S  =======================\n");
	printf("\t\t===========================================================================\033[0m\n");

	print_list(pbwash,list);

	printf("\n");
	printf("\t\t\033[0;93m===========================================================================\n");
	printf("\t\t===========================\033[0;93mF I X E S \033[0;93m============================\n");
	printf("\t\t\033[0;93m===========================================================================\033[0;32m\n");
	printf("\t\t===========================  B O O K I N G S  =============================\n");
	printf("\t\t===========================================================================\033[0m\n");

	print_list(fix,list);

	printf("\n\t\t\033[0;32m===========================================================================\n");
	printf("\t\t=========================  P R E --B O O K S  =======================\n");
	printf("\t\t===========================================================================\033[0m\n");


	print_list(pbfix,list);
}

void print_of_client(books wash, books pbwash, books fix, books pbfix,clients list)
{
	int a;

	clients ant;
	clients actual;
	
    printf("\n\t\tEnter client's id: ");
    scanf("%d",&a);
    printf("\n\n\t\t\033[0;96mClient:\033[0m ");
    
    search_clients_id(list,a,&ant,&actual);
    
    puts(actual->info.name);
    printf("\t\t\033[0;32m================\033[0m\n");
    printf("\t\t\033[0;93mB O O K I N G S:\033[0m\n");
    printf("\t\t\033[0;32m===========================================================================\n");
	printf("\t\t=============================\033[0;93mF I X E S \033[0;32m==========================\n");
	printf("\t\t\033[0;32m===========================================================================\n");

	if(fix->next==NULL){
        printf("\t\tThe client has no bookings of this type.\n");
        /*return;*/
    }
    else{
		recursive_id(fix,a);
	}

	printf("\t\t\033[0;32m===========================================================================\n");
	printf("\t\t===============================\033[0;93mW A S H E S\033[0;32m=============================\n");
	printf("\t\t\033[0;32m===========================================================================\n");

	if(wash->next==NULL){
        printf("\t\tThe client has no bookings of this type.\n");
        /*return;*/
    }
    else{
		recursive_id(wash,a);
	}

    printf("\n");
	printf("\t\t\033[0;32m=========================\033[0m\n");
	printf("\t\t\033[0;93mP R E --B O O K I N G S:\033[0m\n");
	printf("\t\t\033[0;32m===========================================================================\n");
	printf("\t\t=============================\033[0;93mF I X E S \033[0;32m==========================\n");
	printf("\t\t\033[0;32m===========================================================================\033[0m\n");

	if(pbfix->next==NULL){
        printf("\t\tThe client has no pre-bookings of this type.\n");
        /*return;*/
    }
    else{
		recursive_id(pbfix,a);
	}

	printf("\t\t\033[0;32m===========================================================================\n");
	printf("\t\t===============================\033[0;93mW A S H E S\033[0;32m=============================\n");
	printf("\t\t\033[0;32m===========================================================================\033[0m\n");
		
	if(pbwash->next==NULL){
        printf("\t\tThe client has no pre-bookings of this type.\n");
        /*return;*/
    }
    else{
		recursive_id(pbwash,a);
	}
}
