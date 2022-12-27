// Copyright 2020 Your Name <your_email>

#include <gtest/gtest.h>

#include <matrix.hpp>
#include <string.hpp>

TEST(String, CopyString)
{
    const char* p = "some string";

    char* str = CopyString(p);
    p = "hello, world!";

    EXPECT_EQ(str[0], 's');
    EXPECT_EQ(str[1], 'o');
    EXPECT_EQ(str[2], 'm');
    EXPECT_EQ(str[3], 'e');
    EXPECT_EQ(str[4], ' ');
    EXPECT_EQ(str[5], 's');
    EXPECT_EQ(str[6], 't');
    EXPECT_EQ(str[7], 'r');
    EXPECT_EQ(str[8], 'i');
    EXPECT_EQ(str[9], 'n');
    EXPECT_EQ(str[10], 'g');
    EXPECT_EQ(str[11], 0);
    delete[] str;
}

TEST(String, ConcatinateStrings)
{
    const char* a = "hello,";
    const char* b = "world!";

    char* str = ConcatinateStrings(a, b);

    EXPECT_EQ(str[0], 'h');
    EXPECT_EQ(str[1], 'e');
    EXPECT_EQ(str[2], 'l');
    EXPECT_EQ(str[3], 'l');
    EXPECT_EQ(str[4], 'o');
    EXPECT_EQ(str[5], ',');
    EXPECT_EQ(str[6], 'w');
    EXPECT_EQ(str[7], 'o');
    EXPECT_EQ(str[8], 'r');
    EXPECT_EQ(str[9], 'l');
    EXPECT_EQ(str[10], 'd');
    EXPECT_EQ(str[11], '!');
    EXPECT_EQ(str[12], 0);
    
    delete[] str;
}

TEST(Matrix, Construct) {
  Matrix m;
  Construct(m, 10, 10);

  EXPECT_EQ(m.m_, 10);
  EXPECT_EQ(m.n_, 10);

  EXPECT_EQ(m.data_[9][9], 0);
  EXPECT_EQ(m.data_[0][2], 0);

  Destruct(m);
  EXPECT_EQ(m.data_, nullptr);
}

TEST(Matrix, Copy) {
  Matrix m;
  Construct(m, 2, 2);
  m.data_[0][0] = 1;
  m.data_[0][1] = 2;
  m.data_[1][0] = 3;
  m.data_[1][1] = 4;

  Matrix c = Copy(m);
  Destruct(m);

  EXPECT_EQ(c.m_, 2);
  EXPECT_EQ(c.n_, 2);

  EXPECT_EQ(c.data_[0][0], 1);
  EXPECT_EQ(c.data_[0][1], 2);
  EXPECT_EQ(c.data_[1][0], 3);
  EXPECT_EQ(c.data_[1][1], 4);
  Destruct(c);
}

TEST(Matrix, Transposition) {
  Matrix m;
  Construct(m, 2, 2);
  m.data_[0][0] = 1;
  m.data_[0][1] = 2;
  m.data_[1][0] = 3;
  m.data_[1][1] = 4;

  Transposition(m);
  EXPECT_EQ(m.data_[0][0], 1);
  EXPECT_EQ(m.data_[0][1], 3);
  EXPECT_EQ(m.data_[1][0], 2);
  EXPECT_EQ(m.data_[1][1], 4);

  Transposition(m);
  EXPECT_EQ(m.data_[0][0], 1);
  EXPECT_EQ(m.data_[0][1], 2);
  EXPECT_EQ(m.data_[1][0], 3);
  EXPECT_EQ(m.data_[1][1], 4);

  Destruct(m);
}

TEST(Matrix, Eq) {
  Matrix m;
  Construct(m, 2, 2);
  m.data_[0][0] = 1;
  m.data_[0][1] = 2;
  m.data_[1][0] = 3;
  m.data_[1][1] = 4;

  Matrix m2;
  Construct(m2, 2, 2);
  m2.data_[0][0] = 1;
  m2.data_[0][1] = 2;
  m2.data_[1][0] = 3;
  m2.data_[1][1] = 4;

  EXPECT_EQ(m, m2);

  Matrix c2 = Copy(m2);
  Matrix c = Copy(m);
  EXPECT_EQ(m, c2);
  EXPECT_EQ(m2, c);

  Destruct(m);
  Destruct(m2);
  Destruct(c);
  Destruct(c2);
}

TEST(Matrix, Add) {
  Matrix m;
  Construct(m, 2, 2);
  m.data_[0][0] = 1;
  m.data_[0][1] = 2;
  m.data_[1][0] = 3;
  m.data_[1][1] = 4;

  Matrix c = Copy(m);

  Matrix s = Add(m, c);
  Matrix s2 = Add(c, m);
  EXPECT_EQ(s2, s);

  ASSERT_EQ(s.n_, 2);
  ASSERT_EQ(s.m_, 2);
  EXPECT_EQ(s.data_[0][0], 2);
  EXPECT_EQ(s.data_[0][1], 4);
  EXPECT_EQ(s.data_[1][0], 6);
  EXPECT_EQ(s.data_[1][1], 8);

  Destruct(m);
  Destruct(c);
  Destruct(s);
  Destruct(s2);
}

TEST(Matrix, AddEmpty) {
  Matrix m;
  Construct(m, 2, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Add(m, c);

  EXPECT_EQ(s.data_, nullptr);
  EXPECT_EQ(s.n_, 0);
  EXPECT_EQ(s.m_, 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, Sub) {
  Matrix m;
  Construct(m, 2, 2);
  m.data_[0][0] = 1;
  m.data_[0][1] = 2;
  m.data_[1][0] = 3;
  m.data_[1][1] = 4;

  Matrix c = Copy(m);

  Matrix s = Sub(m, c);

  ASSERT_EQ(s.n_, 2);
  ASSERT_EQ(s.m_, 2);
  EXPECT_EQ(s.data_[0][0], 0);
  EXPECT_EQ(s.data_[0][1], 0);
  EXPECT_EQ(s.data_[1][0], 0);
  EXPECT_EQ(s.data_[1][1], 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, SubEmpty) {
  Matrix m;
  Construct(m, 2, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Sub(m, c);

  EXPECT_EQ(s.data_, nullptr);
  EXPECT_EQ(s.n_, 0);
  EXPECT_EQ(s.m_, 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, Mult) {
  Matrix m;
  Construct(m, 2, 3);
  
  /*
  2 0
  0 2
  1 1
  */
  // first colunm
  m.data_[0][0] = 2;
  m.data_[0][1] = 0;
  m.data_[0][2] = 1;

  // second colunm
  m.data_[1][0] = 0;
  m.data_[1][1] = 2;
  m.data_[1][2] = 1;

  Matrix c;
  Construct(c, 2, 2);
  /*
  1 0
  1 1
  */
  c.data_[0][0] = 1;
  c.data_[0][1] = 1;
  c.data_[1][0] = 0;
  c.data_[1][1] = 1;

  Matrix s = Mult(m, c);

  ASSERT_EQ(s.n_, 2);
  ASSERT_EQ(s.m_, 3);
  /*
  2 0
  2 2
  2 1
  */
  EXPECT_EQ(s.data_[0][0], 2);
  EXPECT_EQ(s.data_[0][1], 2);
  EXPECT_EQ(s.data_[0][2], 2);
  EXPECT_EQ(s.data_[1][0], 0);
  EXPECT_EQ(s.data_[1][1], 2);
  EXPECT_EQ(s.data_[1][2], 1);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}

TEST(Matrix, MultEmpty) {
  Matrix m;
  Construct(m, 3, 2);

  Matrix c;
  Construct(c, 3, 3);

  Matrix s = Sub(m, c);

  EXPECT_EQ(s.data_, nullptr);
  EXPECT_EQ(s.n_, 0);
  EXPECT_EQ(s.m_, 0);

  Destruct(m);
  Destruct(c);
  Destruct(s);
}
