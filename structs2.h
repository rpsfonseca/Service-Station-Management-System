#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED
#define MAX 100

extern int id_client;

typedef struct{
	int day;
	int month;
	int year;
}Date;

typedef struct{
	int hour;
	int minutes;
}Hours;

typedef struct{
	Date client_date;
	Hours client_hour;
}Slot;

typedef struct{
	char name[MAX];
	int id_client;
	int cell;
}Client;

typedef struct{
	Slot slot;
	int id;
}Booking;

/* booking linked list */
typedef struct node *books;
typedef struct node {
	Booking info;
	books next;
}books_node;

/*client linked list*/
typedef struct node2 *clients;
typedef struct node2 {
	Client info;
	clients next;
}clients_node;

/*_______________________manipulation2.c_________________________*/
books create_books(void);
clients create_clients(void);

books destroy_books(books );
clients destroy_clients(clients );

void delete_book_node(books,books,int,int);
void delete_pbook_node(books,int,int);
void end_book2(books , Booking *, int );

int empty_books(books);
int empty_clients(clients);

int full_books(books);
int full_clients(clients);

void search_books(books,Booking *,books *,books *);
void search_books_id(books,int,books *,books *);
void search_clients_id(clients,int,clients *,clients *);
void search_clients_cell(clients,int,clients *,clients *);

clients research_clients_id(clients,int);
clients research_clients_cell(clients,int);

void insert_book(books,Booking *);
void insert_client(clients,Client *);

void print_list(books,clients );

void recursive_id(books,int);
int check_file(FILE *,char *);
void build_from_file(books,char *);
void build_clients(clients,char *);
void write_to_file(books,char *);
void write_client(Client *,char *);

/*___________________________secondary2.c________________________*/
Client create_account(void);
void book_it(Booking *,int,int);
int compare(Date,Hours,Date,Hours);
void booking_validation(books,books,Booking *,int);
int cell_validation(int);
int name_validation(char *);
int hour_validation(Hours,int);
int date_validation(Date);
int check_file(FILE *,char *);
void load_image(char *);
int input_from_user(void);
int clean_stdin(void);


/*__________________________operations2.c_______________________*/
void booking(clients,books,books,int);
void delete_book(books,books,books,books);
void delete_prebook(books,books);
void end_book(books,books,books,books);
void print_all(books,books,books,books,clients);
void print_of_client(books,books,books,books,clients);

#endif	/* STRUCT_H_INCLUDED */
