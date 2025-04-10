#ifndef LIBRARY_H
#define LIBRARY_H
#include <string>  // Add this

// Constants
const int MAX_USERS = 20;
const int MAX_BOOKS = 100;
const int MAX_NAME_LENGTH = 100;



// Function declarations
void create_();
void remove_user();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void return_book(int roll);
void display_sorted();
int find_user(int roll);
int find_book(int isbn);
void add_book();
void remove_book();
void edit_book();
void view_books();
void search_books();
void save_data();
void load_data();
void create_account();

// Global variables (declare extern in main.cpp if needed)
extern int user_count;
extern int book_count;
extern double user_balance[MAX_USERS];
extern int user_roll[MAX_USERS];
extern char user_name[MAX_USERS][MAX_NAME_LENGTH];
extern std::string book_title[MAX_BOOKS];  // Changed to string
extern std::string book_author[MAX_BOOKS]; // Changed to strin
extern int book_isbn[MAX_BOOKS];
extern bool book_available[MAX_BOOKS];
extern int book_borrower[MAX_BOOKS];

#endif // LIBRARY_H
