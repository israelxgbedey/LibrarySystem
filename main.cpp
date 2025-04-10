#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <limits>   
#include <ios> 
#include <string>  // Add this at the top

#include "library.h"



using namespace std;




int user_count = 0;

int book_count = 0;
double user_balance[MAX_USERS];
int user_roll[MAX_USERS];
char user_name[MAX_USERS][MAX_NAME_LENGTH];
std::string book_title[MAX_BOOKS];
std::string book_author[MAX_BOOKS];
int book_isbn[MAX_BOOKS];
bool book_available[MAX_BOOKS];
int book_borrower[MAX_BOOKS];


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

#ifndef BUILD_TESTS

int main() {
    load_data();

    int option;
    bool is_admin = false;
    string password;
    int login_roll;
    bool logged_in = false;

    while (true) {
        if (!logged_in) {
            cout << "\n=== Library System ===\n"
                 << "1. Admin Login\n"
                 << "2. User Login\n"
                 << "3. Create New Account\n"
                 << "4. View Available Books\n"
                 << "0. Exit\n"
                 << "Select an option: ";
            cin >> option;

            if (option == 0) {
                save_data();
                cout << "Exiting and saving data. See you later!\n";
                break;
            }

            switch (option) {
                case 1: {  // Admin Login
                    is_admin = true;
                    cout << "Enter admin password: ";
                    cin >> password;
                    if (password == "admin123") {
                        logged_in = true;
                        cout << "Admin logged in successfully.\n";
                    } else {
                        cout << "Incorrect admin password.\n";
                        is_admin = false;
                    }
                    break;
                }
                case 2: {  // User Login
                    cout << "Enter your user ID (roll number): ";
                    cin >> login_roll;
                    int user_index = find_user(login_roll);
                    if (user_index != -1) {
                        logged_in = true;
                        is_admin = false;
                        cout << "User logged in successfully.\n";
                    } else {
                        cout << "User ID not found. Create account? (1. Yes / 2. No): ";
                        int create_opt;
                        cin >> create_opt;
                        if (create_opt == 1) {
                            create_account();
                        }
                    }
                    break;
                }
                case 3: {  // Create New Account
                    create_account();
                    break;
                }
                case 4: {  // View Available Books
                    cout << "\n=== Available Books ===\n";
                    bool any_available = false;
                    for (int i = 0; i < book_count; i++) {
                        if (book_available[i]) {
                            cout << "Title: " << book_title[i] << "\n"
                                 << "Author: " << book_author[i] << "\n"
                                 << "ISBN: " << book_isbn[i] << "\n"
                                 << "------------------------\n";
                            any_available = true;
                        }
                    }
                    if (!any_available) {
                        cout << "No books currently available.\n";
                    }
                    break;
                }
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        } else {  // User is logged in
            if (is_admin) {
                cout << "\n=== Admin Menu ===\n"
                     << "1. Add Book\n"
                     << "2. Remove Book\n"
                     << "3. Edit Book\n"
                     << "4. View All Books\n"
                     << "5. Search Books\n"
                     << "6. View Users\n"
                     << "7. Remove User\n"
                     << "8. View User Balance\n"
                     << "9. Logout\n"
                     << "Select an option: ";
                cin >> option;

                switch (option) {
                    case 1: add_book(); break;
                    case 2: remove_book(); break;
                    case 3: edit_book(); break;
                    case 4: view_books(); break;
                    case 5: search_books(); break;
                    case 6: display_sorted(); break;
                    case 7: remove_user(); break;
                    case 8: {
                        int roll;
                        cout << "Enter User roll number: ";
                        cin >> roll;
                        display(roll);
                        break;
                    }
                    case 9: 
                        logged_in = false;
                        is_admin = false;
                        cout << "Logged out successfully.\n";
                        break;
                    default: 
                        cout << "Invalid option.\n";
                }
            } else {  // Regular user menu
                cout << "\n=== User Menu ===\n"
                     << "1. View Balance\n"
                     << "2. Deposit Money\n"
                     << "3. Borrow Book\n"
                     << "4. Return Book\n"
                     << "5. Logout\n"
                     << "Select an option: ";
                cin >> option;

                switch (option) {
                    case 1: display(login_roll); break;
                    case 2: {
                        double amount;
                        cout << "Enter amount to deposit: $";
                        cin >> amount;
                        deposit_amount(login_roll, amount);
                        break;
                    }
                    case 3: issue_item(login_roll); break;
                    case 4: return_book(login_roll); break;
                    case 5: 
                        logged_in = false;
                        cout << "Logged out successfully.\n";
                        break;
                    default: 
                        cout << "Invalid option.\n";
                }
            }
        }
    }
    return 0;
}
#endif


void create_account() {
    if (user_count >= MAX_USERS) {
        cout << "User limit reached.\n";
        return;
    }
    int roll;
    cout << "Enter roll number (User ID): ";
    cin >> roll;

    if (find_user(roll) != -1) {
        cout << "Account with this User ID already exists.\n";
        return;
    }

    user_roll[user_count] = roll;
    cout << "Enter name: ";
    cin.ignore();
    cin.getline(user_name[user_count], MAX_NAME_LENGTH);

    double initial_deposit;
    cout << "Initial deposit (minimum $50): $";
    cin >> initial_deposit;

    if (initial_deposit < 50) {
        cout << "Minimum deposit is $50.\n";
        return;
    }
    user_balance[user_count] = initial_deposit - 50;
    user_count++;
    cout << "Account created successfully.\n";

    ofstream fs("users.txt", ios::app);
    if (fs) {
        fs << user_roll[user_count - 1] << " " << user_balance[user_count - 1] << " " << user_name[user_count - 1] << endl;
    } else {
        cout << "Error saving user data.\n";
    }
}


void remove_user() 
{
    int roll; 
    cout << "Enter user number to remove: ";
    cin >> roll;
    int index = find_user(roll);
    if (index == -1) 
    {
        cout << "User not found.\n";
        return;
    }

    for (int i = index; i < user_count - 1; i++)
    {
        user_roll[i] = user_roll[i + 1];
        user_balance[i] = user_balance[i + 1]; // Fix '-' to '='
        strcpy(user_name[i], user_name[i + 1]);
    }
    user_count--;
    cout << "User removed. \n";
}

void display(int roll) 
{
int index =find_user(roll);
if (index == -1)
{ 
    cout << "User not found.\n";
    return;
}
cout << "Roll number: " << user_roll[index] << "\nName:" << user_name[index]
        << "\nBalance: $" << fixed << setprecision(2) << user_balance[index] << endl;

}

void deposit_amount(int roll, double amount) 
{
    int index = find_user(roll);
    if (index == -1 )
    {
        cout << "User not found. \n";
        return;
    }
    user_balance[index] += amount;
    cout << "Deposited. New Balance: $" << fixed << setprecision(2) << user_balance[index] << endl;


}

void issue_item(int roll) {
    int index = find_user(roll);
    if (index == -1) return;

    cout << "\nAvailable books:\n";
    for (int i = 0; i < book_count; i++) {
        if (book_available[i])
            cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] << " (ISBN: " << book_isbn[i] << ")\n";
    }

    int choice;
    cout << "Select book number to borrow (0 to cancel): ";
    cin >> choice;

    if (choice <= 0 || choice > book_count || !book_available[choice - 1]) {
        cout << "Invalid or unavailable.\n";
        return;
    }

    if (user_balance[index] < 2) {
        cout << "Insufficient balance.\n";
        return;
    }

    // Update the book availability and borrower
    book_available[choice - 1] = false;
    book_borrower[choice - 1] = roll; // Record who borrowed the book
    user_balance[index] -= 2;
    cout << "Book borrowed. $2 deducted. New balance: $" << user_balance[index] << endl;

    // Save the updated user and book data
    save_data();
}


void return_book(int roll) {
    int isbn;
    cout << "Enter ISBN to return: ";
    cin >> isbn;
    int index = find_book(isbn);
    if (index == -1 || book_available[index]) {
        cout << "Invalid return.\n";
        return;
    }

    book_available[index] = true;
    book_borrower[index] = -1;
    cout << "Book returned.\n";
}

// Display users sorted by roll(id) number

void display_sorted()
 {
    for (int i = 0; i < user_count; i++) 
    {
        for (int j = i + 1; j < user_count; j++)
         {
            if (user_roll[i] > user_roll[j])
             {
                swap(user_roll[i], user_roll[j]);
                swap(user_balance[i], user_balance[j]);
                swap(user_name[i], user_name[j]);
            }
        }
    }

    for (int i = 0; i < user_count; i++) {
        cout << user_roll[i] << " - " << user_name[i] << " - $" << fixed << setprecision(2) << user_balance[i] << endl;
    }
}

int find_user(int roll) 
{
    for (int i = 0; i < user_count; i++)
        if (user_roll[i] == roll) return i;
    return -1;
}

int find_book(int isbn)

{
    for (int i = 0; i < book_count; i++)
        if (book_isbn[i] == isbn) return i;
    return -1;
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        cout << "Book limit reached.\n";
        return;
    }

    cout << "Enter title: ";
    cin.ignore();
    getline(cin, book_title[book_count]);
    cout << "Enter author: ";
    getline(cin, book_author[book_count]);
    cout << "Enter ISBN: ";
    cin >> book_isbn[book_count];

    if (find_book(book_isbn[book_count]) != -1) {
        cout << "ISBN already exists.\n";
        return;
    }

    book_available[book_count] = true;
    book_count++;
    cout << "Book added.\n";
}

void remove_book() {
    int isbn;
    cout << "Enter ISBN to remove: ";
    cin >> isbn;
    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    for (int i = index; i < book_count - 1; i++) {
        book_title[i] = book_title[i + 1];  // Direct string assignment
        book_author[i] = book_author[i + 1];  // Direct string assignment
        book_isbn[i] = book_isbn[i + 1];
        book_available[i] = book_available[i + 1];
    }
    book_count--;
    cout << "Book removed.\n";
}

void edit_book() 
{
    int isbn;
    cout << "Enter ISBN to edit: ";
    cin >> isbn;
    int index = find_book(isbn);
    if (index == -1) 
    {
        cout << "Book not found.\n";
        return;
    }
    // Get new details

    cout << "New title: ";
    cin.ignore();
    getline(cin, book_title[index]);  // Proper std::string version
    cout << "New author: ";
    getline(cin, book_author[index]);  // Proper std::string version
    cout << "Book updated.\n";
}
void view_books() {
    for (int i = 0; i < book_count; i++) {
        if (book_available[i]) {  // Only show if available
            cout << "Title: " << book_title[i] << "\nAuthor: " << book_author[i]
                 << "\nISBN: " << book_isbn[i] << "\nAvailable: Yes\n\n";
        }
    }
}

// Search books by different criteria

void search_books() {
    int option;
    string keyword;
    int search_isbn;
    cout << "Search by: 1. Title  2. Author  3. ISBN\n";
    cin >> option;

    bool found = false;

    if (option == 3) {
        cout << "Enter ISBN: ";
        cin >> search_isbn;
        for (int i = 0; i < book_count; i++) {
            if (book_isbn[i] == search_isbn) {
                cout << "Title: " << book_title[i] << ", Author: " << book_author[i]
                     << ", ISBN: " << book_isbn[i] << ", Available: " 
                     << (book_available[i] ? "Yes" : "No") << "\n";
                found = true;
                break;
            }
        }
    } else if (option == 1 || option == 2) {
        cout << "Enter keyword: ";
        cin.ignore();
        getline(cin, keyword);
        for (int i = 0; i < book_count; i++) {
            if ((option == 1 && book_title[i].find(keyword) != string::npos) ||
                (option == 2 && book_author[i].find(keyword) != string::npos)) {
                cout << "Title: " << book_title[i] << ", Author: " << book_author[i]
                     << ", ISBN: " << book_isbn[i] << ", Available: " 
                     << (book_available[i] ? "Yes" : "No") << "\n";
                found = true;
            }
        }
    } else {
        cout << "Invalid search option.\n";
        return;
    }

    if (!found) {
        cout << "No results found.\n";
    }
}

// Save all data to files

void save_data() {
    ofstream fs("users.txt"), fb("books.txt");

    // Save user data
    fs << user_count << endl;
    for (int i = 0; i < user_count; i++) {
        fs << user_roll[i] << " " << fixed << setprecision(2) << user_balance[i] << " " << user_name[i] << endl;
    }

    // Save book data
    fb << book_count << endl;
    for (int i = 0; i < book_count; i++) {
        fb << book_isbn[i] << " " << book_available[i] << " " << book_borrower[i] << " " << book_title[i] << "|" << book_author[i] << endl;
    }
}

// Load book data

void load_data() {
    ifstream fs("users.txt"), fb("books.txt");

    if (fs) {
        fs >> user_count;
        fs.ignore();
        for (int i = 0; i < user_count; i++) {
            fs >> user_roll[i] >> user_balance[i];
            fs.ignore();
            fs.getline(user_name[i], MAX_NAME_LENGTH);
        }
    }

    if (fb) {
        fb >> book_count;
        fb.ignore();

        for (int i = 0; i < book_count; i++) {
            fb >> book_isbn[i] >> book_available[i] >> book_borrower[i];
            fb.ignore(); // Skip the space after borrower
            string combined;
            getline(fb, combined);
                      // Split combined string into title and author

            size_t pipe_pos = combined.find('|');
            if (pipe_pos != string::npos) {
                book_title[i] = combined.substr(0, pipe_pos);
                book_author[i] = combined.substr(pipe_pos + 1);
            } else {
                book_title[i] = combined;
                book_author[i] = "";
            }
        }
    }
}
