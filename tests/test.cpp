#include "str.hpp"
#include <gtest/gtest.h>

bool operator==(const string& l, const char* r) {
    return std::strcmp(l.c_str(), r) == 0;
}

TEST(Test, t1) {
    string s;
    ASSERT_EQ(s.getSize(), 0);
    ASSERT_EQ(s.getCapacity(), 1);
    ASSERT_EQ(s.c_str()[0], '\0');
}

TEST(Test, t2) {
    string s("Hello");
    ASSERT_EQ(s.getSize(), 5);
    ASSERT_EQ(s, "Hello");
}

TEST(Test, t3) {
    string s(nullptr);
    ASSERT_EQ(s.getSize(), 0);
    ASSERT_EQ(s, "");
}

TEST(Test, t4) {
    string s1("11111");
    string s2(s1);
    ASSERT_EQ(s2, "11111");
    ASSERT_EQ(s2.getSize(), 5);
}

TEST(Test, t5) {
    string s1("11111");
    string s2(std::move(s1));
    ASSERT_EQ(s2, "11111");
    ASSERT_EQ(s1.getSize(), 0);
}

TEST(Test, t6) {
    string s1("1");
    string s2("2");
    s1 = s2;
    ASSERT_EQ(s1, "2");
    ASSERT_EQ(s1.getSize(), 1);
}

TEST(Test, t7) {
    string s("1");
    s = s;
    ASSERT_EQ(s, "1");
}

TEST(Test, t8) {
    string s("Hello");
    s.append(", World!");
    ASSERT_EQ(s, "Hello, World!");
    ASSERT_EQ(s.getSize(), 13);
}

TEST(Test, t9) {
    string s("Test");
    s.append("");
    ASSERT_EQ(s, "Test");
    ASSERT_EQ(s.getSize(), 4);
}

TEST(Test, t10) {
    string s("Test");
    s.append(nullptr);
    ASSERT_EQ(s, "Test");
}

TEST(Test, t11) {
    string s("aha");
    ASSERT_EQ(s.is_palindrome(), true);
}

TEST(Test, t12) {
    string s("haha");
    ASSERT_EQ(s.is_palindrome(), false);
}