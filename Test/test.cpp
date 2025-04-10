#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include "library.h"
#include "main.cpp"  




class LibraryTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize test data
        user_count = 0;
        book_count = 0;
        
        // Add test users
        user_roll[user_count] = 1001;
        strcpy(user_name[user_count], "Test User");
        user_balance[user_count] = 50.0;
        user_count++;

        // Add test books
        strcpy(book_title[book_count], "Test Book");
        strcpy(book_author[book_count], "Test Author");
        book_isbn[book_count] = 123456;
        book_available[book_count] = true;
        book_count++;
    }

    void TearDown() override {
        // Clean up after each test
        user_count = 0;
        book_count = 0;
    }
};

// Test cases
TEST_F(LibraryTest, FindUserSuccess) {
    EXPECT_EQ(find_user(1001), 0);
}

TEST_F(LibraryTest, FindUserFailure) {
    EXPECT_EQ(find_user(9999), -1);
}

TEST_F(LibraryTest, AddBook) {
    int initial_count = book_count;
    strcpy(book_title[book_count], "New Book");
    strcpy(book_author[book_count], "New Author");
    book_isbn[book_count] = 789012;
    book_available[book_count] = true;
    book_count++;
    
    EXPECT_EQ(book_count, initial_count + 1);
    EXPECT_EQ(find_book(789012), initial_count);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
