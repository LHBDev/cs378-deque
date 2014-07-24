// ----------------------------
// projects/deque/TestDeque.c++
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

/*
Google Test Libraries:
    % ls -al /usr/include/gtest/
    ...
    gtest.h
    ...

    % locate libgtest.a
    /usr/lib/libgtest.a

    % locate libpthread.a
    /usr/lib/x86_64-linux-gnu/libpthread.a
    /usr/lib32/libpthread.a

    % locate libgtest_main.a
    /usr/lib/libgtest_main.a

To compile the test:
    % g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall TestDeque.c++ -o TestDeque -lgtest -lgtest_main -lpthread

To run the test:
    % valgrind TestInteger

To obtain coverage of the test:
    % gcov-4.7 -b Integer.c++ TestInteger.c++
*/

// --------
// includes
// --------

#include <algorithm> // equal
#include <cstring>   // strcmp
#include <deque>     // deque
#include <sstream>   // ostringstream
#include <stdexcept> // invalid_argument
#include <string>    // ==

#include "gtest/gtest.h"

#include "Deque.h"

// ---------
// TestDeque
// ---------

template <typename D>
struct TestDeque : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          D                  deque_type;
    typedef typename D::allocator_type  allocator_type;
    typedef typename D::value_type      value_type;
    typedef typename D::size_type       size_type;
    typedef typename D::difference_type difference_type;
    typedef typename D::pointer         pointer;
    typedef typename D::const_pointer   const_pointer;
    typedef typename D::reference       reference;
    typedef typename D::const_reference const_reference;};

typedef testing::Types<
            std::deque<int>,
            std::deque<double>,
            my_deque<int>,
            my_deque<double> >
        my_types;

TYPED_TEST_CASE(TestDeque, my_types);

TYPED_TEST(TestDeque, Empty) {
    typedef typename TestFixture::deque_type      deque_type;
    // typedef typename TestFixture::allocator_type  allocator_type;
    // typedef typename TestFixture::value_type      value_type;
    // typedef typename TestFixture::size_type       size_type;
    // typedef typename TestFixture::difference_type difference_type;
    // typedef typename TestFixture::pointer         pointer;
    // typedef typename TestFixture::const_pointer   const_pointer;
    // typedef typename TestFixture::reference       reference;
    // typedef typename TestFixture::const_reference const_reference;

    deque_type x;
    const bool b = x.empty();
    ASSERT_TRUE(b);}

TYPED_TEST(TestDeque, Size) {
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    const size_type s = x.size();
    ASSERT_EQ(0, s);}

TYPED_TEST(TestDeque, Size_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10,3);
    const size_type s = x.size();
    ASSERT_EQ(10, s); 
    ASSERT_EQ(3,  x[0]);
}


TYPED_TEST(TestDeque, constructor_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    
    deque_type x(10);
    const size_type s = x.size();
    ASSERT_EQ(10, s); 
}

TYPED_TEST(TestDeque, copy_constructor){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 2);
    deque_type y(x);
    const size_type x_s = x.size();
    const size_type y_s = y.size();

    ASSERT_EQ(x_s, 10);
    ASSERT_EQ(y_s, 10);
    ASSERT_EQ(x_s, y_s);
    ASSERT_TRUE(x[0] == y[0]);
}

TYPED_TEST(TestDeque, push_back){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(2);
    x.push_back(3);
    x.push_back(4);
    x.push_back(5);
    x.push_back(6);
    x.push_back(7);
    x.push_back(8);
    x.push_back(9);
    ASSERT_EQ(x.size(), 10);
    // ASSERT_EQ(x[0], 0);
    // ASSERT_EQ(x[1], 1);
    // ASSERT_EQ(x[2], 2);
    // ASSERT_EQ(x[3], 3);
    // ASSERT_EQ(x[4], 4);
    // ASSERT_EQ(x[5], 5);
    // ASSERT_EQ(x[6], 6);
    // ASSERT_EQ(x[7], 7);
    // ASSERT_EQ(x[8], 8);
    // ASSERT_EQ(x[9], 9);
       
}

