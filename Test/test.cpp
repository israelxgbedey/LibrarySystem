#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "library.h"
#include "main.cpp"  

class LibraryTest : public ::testing::Test {
protected:
    void SetUp() override {

        user_count = 0;
        book_count = 0;
        

        user_roll[user_count] = 1001;
        strcpy(user_name[user_count], "Test User");
        user_balance[user_count] = 50.0;
        user_count++;


        book_title[book_count] = "Test Book";
        book_author[book_count] = "Test Author";
        book_isbn[book_count] = 123456;
        book_available[book_count] = true;
        book_count++;
    }

    void TearDown() override {

        user_count = 0;
        book_count = 0;
    }
};

TEST_F(LibraryTest, FindUserSuccess) {

    EXPECT_EQ(find_user(1001), 0);
}

TEST_F(LibraryTest, FindUserFailure) {

    EXPECT_EQ(find_user(9999), -1);
}

TEST_F(LibraryTest, AddBook) {
    std::istringstream input("Test Book\nTest Author\n789012\n");
    std::streambuf* original_cin = std::cin.rdbuf(input.rdbuf()); 

    add_book(); 

    std::cin.rdbuf(original_cin); // Restore cin

    EXPECT_EQ(book_count, 2);
    EXPECT_NE(find_book(789012), -1);
}

TEST_F(LibraryTest, RemoveUser) {
    
    remove_user();  

    EXPECT_EQ(find_user(1001), -1);  
    EXPECT_EQ(user_count, 0);  
}

TEST_F(LibraryTest, DepositAmount) {
    deposit_amount(1001, 20.0);

    int user_index = find_user(1001);
    EXPECT_EQ(user_balance[user_index], 70.0);  
}

TEST_F(LibraryTest, IssueBook) {

    issue_item(1001);  

    EXPECT_EQ(book_available[0], false);  
    EXPECT_EQ(user_balance[0], 48.0);  
}

TEST_F(LibraryTest, ReturnBook) {
    issue_item(1001); 

    return_book(1001);

    EXPECT_EQ(book_available[0], true);  
    EXPECT_EQ(book_borrower[0], -1);  
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
