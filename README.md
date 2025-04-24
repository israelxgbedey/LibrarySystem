# 📚 Simple C++ Library Management System

This is a console-based Library Management System written in C++. It supports both admin and user operations such as managing books, creating accounts, borrowing and returning books, and saving data to files.

---

## 🚀 Features

### Admin Features:
- Add new books with title, author, and ISBN.
- Edit or remove existing books.
- Search books by title, author, or ISBN.
- View all registered users.
- View individual user balances.
- Remove users.

### User Features:
- Create a new account (with an initial $50 minimum deposit).
- Login using roll number (User ID).
- View account balance.
- Deposit money into account.
- Borrow books (costs $2 per book).
- Return borrowed books.
- View available books.

## 🛠️ How It Works

### Data Storage:
- User data is stored in `users.txt`.
- Book data is stored in `books.txt`.

### Account Management:
- Each user is assigned a unique roll number.
- Users must deposit at least $50 when creating an account. $50 is a registration fee and is deducted.

### Book Borrowing:
- Books cost $2 to borrow.
- Only available books are listed.
- Users must return books using ISBN.


## 🗂️ File Structure

```text
.
├── main.cpp         // Main logic and menu handling
├── library.h        // Constants and shared definitions
├── users.txt        // Saved user data
├── books.txt        // Saved book data
