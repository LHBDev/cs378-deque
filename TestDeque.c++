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

    using namespace std;

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

TYPED_TEST(TestDeque, Size_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15,3);
    const size_type s = x.size();
    ASSERT_EQ(15, s); 
}



TYPED_TEST(TestDeque, constructor_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    
    deque_type x(10);
    const size_type s = x.size();
    ASSERT_EQ(10, s); 
}

TYPED_TEST(TestDeque, constructor_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    
    deque_type x(1232);
    const size_type s = x.size();
    ASSERT_EQ(1232, s); 
}

TYPED_TEST(TestDeque, constructor_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    
    deque_type x(1188,4);
    const size_type s = x.size();
    ASSERT_EQ(1188, s); 
}

TYPED_TEST(TestDeque, copy_constructor){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(20, 2);
    deque_type y(x);
    const size_type x_s = x.size();
    const size_type y_s = y.size();

    ASSERT_EQ(x_s, 20);
    ASSERT_EQ(y_s, 20);
    ASSERT_EQ(x_s, y_s);
    ASSERT_TRUE(x[0] == y[0]);


    x[19] = 19;

    ASSERT_EQ(19, x[19]);
}



TYPED_TEST(TestDeque, copy_constructor_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(100, 2);
    deque_type y(x);
    const size_type x_s = x.size();
    const size_type y_s = y.size();

    ASSERT_EQ(x_s, 100);
    ASSERT_EQ(y_s, 100);
    ASSERT_EQ(x_s, y_s);
    ASSERT_TRUE(x[0] == y[0]);


    x[19] = 19;

    ASSERT_EQ(19, x[19]);
}

TYPED_TEST(TestDeque, copy_constructor_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;

    for(int i =0; i < 60; ++i){
        x.push_back(i);
    }
    

    deque_type y(x);
    const size_type x_s = x.size();
    const size_type y_s = y.size();

    ASSERT_EQ(x_s, 60);
    ASSERT_EQ(y_s, 60);
    ASSERT_EQ(x_s, y_s);
    ASSERT_TRUE(x[0] == y[0]);


        
    for(size_type i =0; i < y.size(); ++i){
        ASSERT_EQ(i, x[i]);
    }
    
}

TYPED_TEST(TestDeque, push_back){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15, 0);
    deque_type y(15, 0);
    x.push_back(1);
    y.push_back(1);
    x.push_back(2);
    y.push_back(2);   
    x.push_back(3);
    y.push_back(3);   
    x.push_back(4);
    y.push_back(4);   
    x.push_back(5);
    y.push_back(5); 

    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator e = x.end();
    typename deque_type::iterator b = y.begin();
    while(it != e)
        ASSERT_EQ(*it++, *b++);
    ASSERT_EQ(x[19], 5);
}


TYPED_TEST(TestDeque, push_back_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 2);
    x.push_back(3);
    ASSERT_EQ(x.back(), 3);    
}


TYPED_TEST(TestDeque, push_back_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;

    for(int i =0; i < 60; ++i){
        x.push_back(i);
    }
    

    deque_type y(x);
    const size_type x_s = x.size();
    const size_type y_s = y.size();

    ASSERT_EQ(x_s, 60);
    ASSERT_EQ(y_s, 60);
    ASSERT_EQ(x_s, y_s);
    ASSERT_TRUE(x[0] == y[0]);


        
    for(size_type i =0; i < y.size(); ++i){
        ASSERT_EQ(i, x[i]);
    }   
}



TYPED_TEST(TestDeque, front){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 0);
    x[0] = 0;
    x[1] = 1;
    x[9] = 10;
    ASSERT_EQ(0, x.front());

}
TYPED_TEST(TestDeque, front_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 0);
        x[0] = 99;
        x[1] = 1;
        x[9] = 10;
    ASSERT_EQ(99, x.front());

}

TYPED_TEST(TestDeque, front_3 ){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    x.push_back(44);
    x.push_back(41);
    ASSERT_EQ(44, x.front());

}


TYPED_TEST(TestDeque, back_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 0);
    x[0] = 0;
    x[1] = 1;
    x[9] = 9;
    ASSERT_EQ(9, x.back());

}

TYPED_TEST(TestDeque, back_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(9, 3);
    x[8] = 8;
    ASSERT_EQ(8, x.back());
}


TYPED_TEST(TestDeque, back_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(1000, 0);
    x[999] = 45;
    ASSERT_EQ(45, x.back());
}


TYPED_TEST(TestDeque, at_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(4545, 3);


    x[456] = 999;
    ASSERT_EQ(999, x.at(456));

}
TYPED_TEST(TestDeque, at_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(1000, 3);


    x[45] = 45;
    ASSERT_EQ(45, x.at(45));

}
TYPED_TEST(TestDeque, at_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 3);


    x[3] = 10000;
    ASSERT_EQ(10000, x.at(3));

}



TYPED_TEST(TestDeque, insert_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5, 1);
    
    auto it = x.begin();
    ++it;
    ++it;
    it = x.insert(it, 3);
    x[3] = 55;
    ASSERT_EQ(3, x.at(2));
    ++it;
    ASSERT_EQ(55, x.at(3));
}

TYPED_TEST(TestDeque, insert_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5, 1);
    
    auto it = x.begin();
        ++it;
    it = x.insert(it, 1);
    it = x.begin();
        ++it;
        ++it;
    it = x.insert(it, 2);
    ASSERT_EQ(1, x.at(1));
    ASSERT_EQ(2, x.at(2));
}

TYPED_TEST(TestDeque, insert_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5, 1);
    
    auto it = x.begin();
        ++it;
    it = x.insert(it, 99);
    it = x.begin();
        ++it;
        ++it;
    it = x.insert(it, 999);

    ASSERT_EQ(99, x.at(1));
    ASSERT_EQ(999, x.at(2));
    ASSERT_EQ(7, x.size());

    // for(int d : x){
    //     cout << d <<" ";
    // }

}


TYPED_TEST(TestDeque, erase_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5,0);
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    x[3] = 3;
    x[4] = 4;

    
    auto it = x.begin();
        ++it;
    it = x.erase(it);



    ASSERT_EQ(2, x.at(1));
    ASSERT_EQ(4, x.size() );

    it = x.begin();

    ++it;

    it = x.erase(it);

    ASSERT_EQ(3, x.at(1));
    ASSERT_EQ(3, x.size() );

}



TYPED_TEST(TestDeque, erase_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5,0);
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    x[3] = 3;
    x[4] = 4;

    
    auto it = x.begin();
        ++it;
        ++it;
    it = x.erase(it);



    ASSERT_EQ(3, x.at(2));
    ASSERT_EQ(4, x.size() );

    it = x.begin();

    ++it;

    it = x.erase(it);

    ASSERT_EQ(3, x.at(1));
    ASSERT_EQ(3, x.size() );

    // for(int d : x)
    //     cout << d <<" ";
    // cout << endl;

}



TYPED_TEST(TestDeque, erase_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(5,0);
    x[0] = 0;
    x[1] = 1;
    x[2] = 2;
    x[3] = 3;
    x[4] = 4;

    
    auto it = x.begin();
    it = x.erase(it);



    ASSERT_EQ(1, x.at(0));
    ASSERT_EQ(4, x.size() );

    it = x.begin(); 

    it = x.erase(it);

    ASSERT_EQ(2, x.at(0));
    ASSERT_EQ(3, x.size() );

}


TYPED_TEST(TestDeque, begin_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

  


    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    x[5] = 5;
    x[8] = 8;
    x[9] = 9;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    ASSERT_TRUE(x[5] == 5);
    ASSERT_TRUE(x[9] == 9);
    auto it = x.begin();
    ASSERT_EQ(0, *it);
    auto itend = x.end();
    --itend;
    ASSERT_EQ(9, *itend );
    --itend;
    ASSERT_EQ(8, *itend );

 
}

TYPED_TEST(TestDeque, begin_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 2);

    x[0] =99;
    ASSERT_TRUE(x[0] == 99);
    auto it = x.begin();
    ASSERT_EQ(99, *it);

}


TYPED_TEST(TestDeque, begin_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 2);

    x[0] =10;
    ASSERT_TRUE(x[0] == 10);
    auto it = x.begin();
    ASSERT_EQ(10, *it);

}

TYPED_TEST(TestDeque, end_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;

    x[5] = 5;
    x[8] = 8;
    x[9] = 9;
    // cout << x[9]  << endl;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    ASSERT_TRUE(x[5] == 5);
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    --itend;
    ASSERT_EQ(9, *itend );
    --itend;
    ASSERT_EQ(8, *itend );
}

TYPED_TEST(TestDeque, end_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    x.push_back(10);
    auto itend = x.end();
    --itend;
    ASSERT_EQ(10, *itend );
}


TYPED_TEST(TestDeque, end_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    x.push_back(10);

    x.push_back(9);
    auto itend = x.end();
    --itend;
    ASSERT_EQ(9, *itend );
}


TYPED_TEST(TestDeque, iterator_pre_minus_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[8] = 8;
    x[9] = 9;

    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    --itend;
    ASSERT_EQ(9, *itend );
    --itend;
    ASSERT_EQ(8, *itend );
}


TYPED_TEST(TestDeque, iterator_pre_minus_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);


    x[7] = 7;
    x[8] = 8;
    x[9] = 9;
    
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    --itend;
    --itend;
    ASSERT_EQ(8, *itend );

}

TYPED_TEST(TestDeque, iterator_pre_minus_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);


    x[7] = 7;
    x[8] = 8;
    x[9] = 9;
    
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    --itend;
    --itend;
    ASSERT_EQ(8, *itend );

}


TYPED_TEST(TestDeque, iterator_post_minus_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[8] = 8;
    x[9] = 9;

    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    itend--;
    ASSERT_EQ(9, *itend );
    itend--;
    ASSERT_EQ(8, *itend );
}


TYPED_TEST(TestDeque, iterator_post_minus_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);


    x[7] = 7;
    x[8] = 8;
    x[9] = 9;
    
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    itend--;
    itend--;
    ASSERT_EQ(8, *itend );

}

TYPED_TEST(TestDeque, iterator_post_minus_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);


    x[7] = 7;
    x[8] = 8;
    x[9] = 9;
    
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    itend--;
    itend--;
    ASSERT_EQ(8, *itend );

}

TYPED_TEST(TestDeque, iterator_pre_plus_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    auto itend = x.begin();
    ++itend;
    ASSERT_EQ(1, *itend );
    ++itend;
    ASSERT_EQ(2, *itend );
}

TYPED_TEST(TestDeque, iterator_pre_plus_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    auto itend = x.begin();
    ++itend;
    ASSERT_EQ(1, *itend );
    ++itend;
    ASSERT_EQ(2, *itend );
}


TYPED_TEST(TestDeque, iterator_pre_plus_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    auto itend = x.begin();
    ++itend;
    ASSERT_EQ(1, *itend );
    ++itend;
    ASSERT_EQ(2, *itend );
}

TYPED_TEST(TestDeque, iterator_post_plus_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    auto itend = x.begin();
    itend++;
    ASSERT_EQ(1, *itend );
    itend++;
    ASSERT_EQ(2, *itend );
}



TYPED_TEST(TestDeque, iterator_post_plus_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(100, 2);

    for (int i =0; i < 100; ++i){
        x[i] = i;
    }
    auto b = x.begin();
    auto e = x.end();
    int i =0;
    while(b != e){
        ASSERT_TRUE(*b == i);
        ++b;
        ++i;
    }
    

}


TYPED_TEST(TestDeque, iterator_post_plus_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[2] =3;
    auto itend = x.begin();
    itend++;
    itend++;
    ASSERT_EQ(3, *itend );
}


TYPED_TEST(TestDeque, iterator_plus_equal_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    x[3] = 3;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    ASSERT_TRUE(x[3] == 3);
    auto itend = x.begin();
    itend+=2;
    ASSERT_EQ(2, *itend );
    itend--;
    ASSERT_EQ(1, *itend );

    itend+=2;
    ASSERT_EQ(3, *itend );
}


TYPED_TEST(TestDeque, iterator_plus_equal_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[0] =0;
    x[1] =1;
    x[3] = 3;
    x[6] = 6;
    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] == 1);
    ASSERT_TRUE(x[3] == 3);

    auto itend = x.begin();
    itend+=2;
    ASSERT_EQ(2, *itend );
    itend--;
    ASSERT_EQ(1, *itend );

    itend+=5;
    ASSERT_EQ(6, *itend );
}

TYPED_TEST(TestDeque, iterator_plus_equal_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(30, 2);

    x[0] =0;
    x[29] = 29;

    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[29] == 29);

    auto itend = x.begin();
    itend+=29;
    ASSERT_EQ(29, *itend );
}

TYPED_TEST(TestDeque, iterator_minus_equal_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(10, 2);

    x[8] = 8;
    x[9] = 9;

    x[6] =6;

    ASSERT_TRUE(x[8] == 8);
    ASSERT_TRUE(x[9] == 9);
    auto itend = x.end();
    itend-=2;
    ASSERT_EQ(8, *itend );

    itend-=2;
    ASSERT_EQ(6, *itend );
}


TYPED_TEST(TestDeque, iterator_minus_equal_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(40, 2);

    x[0] = 0;

    ASSERT_TRUE(x[0] == 0);
    ASSERT_TRUE(x[1] != 0);

    auto itend = x.end();
    itend-=40;
    ASSERT_EQ(0, *itend );
}


TYPED_TEST(TestDeque, iterator_minus_equal_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(40, 2);

    x[20] = 99;

    ASSERT_TRUE(x[20] == 99);
    ASSERT_TRUE(x[21] != 99);

    auto itend = x.end();
    itend-=20;
    ASSERT_EQ(99, *itend );
}


TYPED_TEST(TestDeque, const_begin_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    const deque_type x(10, 2);
    ASSERT_TRUE(x[0] == 2);
    ASSERT_TRUE(x[1] == 2);


    typename deque_type:: const_iterator it = x.begin();
    ASSERT_EQ(2, *it);

}

TYPED_TEST(TestDeque, const_begin_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    const deque_type x(20, 2);
    ASSERT_TRUE(x[0] == 2);
    ASSERT_TRUE(x[1] == 2);
    typename deque_type:: const_iterator it = x.begin();
    ASSERT_EQ(2, *it);

}


TYPED_TEST(TestDeque, const_begin_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    const deque_type x(10, 2);
    ASSERT_TRUE(x[0] == 2);
    ASSERT_TRUE(x[1] == 2);


    
    ASSERT_EQ(2, *x.begin());

}

TYPED_TEST(TestDeque, const_pre_minus_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;


    deque_type x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(2);

    const deque_type y(x);

    typename deque_type:: const_iterator it = y.end();
    --it;
    ASSERT_EQ(2, *it);

}


TYPED_TEST(TestDeque, const_pre_minus_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;


    deque_type x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(2);

    const deque_type y(x);

    typename deque_type:: const_iterator it = y.end();
    --it;
    --it;
    ASSERT_EQ(1, *it);

}


TYPED_TEST(TestDeque, const_pre_minus_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;


    deque_type x;
    x.push_back(0);

    const deque_type y(x);

    ASSERT_EQ(0, *(--y.end()) );

}

TYPED_TEST(TestDeque, const_end_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    x.push_back(0);
    x.push_back(1);

    const deque_type y(x);
    typename deque_type:: const_iterator it = y.begin();
    ++it;

    ASSERT_EQ(1, *it );

}


TYPED_TEST(TestDeque, const_end_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    x.push_back(0);
    x.push_back(1);
    x.push_back(3);


    const deque_type y(x);
    typename deque_type:: const_iterator it = y.begin();
    ++it;
    ++it;

    ASSERT_EQ(3, *it );

}

TYPED_TEST(TestDeque, const_end_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x;
    x.push_back(0);

    const deque_type y(x);

    ASSERT_EQ(0, *(y.begin()) );

}


TYPED_TEST(TestDeque, const_iterator_plus_equal_1){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;


    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    deque_type x(3000,0);
    x[99] = 99;

    const deque_type y(x);
    auto itend = y.begin();
    itend+=99;
    ASSERT_EQ(99, *itend );

}

TYPED_TEST(TestDeque, const_iterator_plus_equal_2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;
    const deque_type x(10, 2);
    ASSERT_TRUE(x[0] == 2);
    ASSERT_TRUE(x[1] == 2);
    ASSERT_TRUE(x[2] == 2);
    auto itend = x.begin();
    itend+=2;
    ASSERT_EQ(2, *itend );
}


TYPED_TEST(TestDeque, const_iterator_plus_equal_3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(3000,0);
    x[2666] = 2666;

    const deque_type y(x);
    auto itend = y.begin();
    itend+=2666;
    ASSERT_EQ(2666, *itend );

}



TYPED_TEST(TestDeque, resize){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15, 0);
    size_type s1 = x.size();
    x.resize(20, 1);
    size_type s2 = x.size();
    x[17] = 5;
    ASSERT_EQ(15, s1);
    ASSERT_EQ(20, s2);
    ASSERT_EQ(5, x[17]);
}

TYPED_TEST(TestDeque, resize2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15, 0);
    size_type s1 = x.size();
    x.resize(10);
    size_type s2 = x.size();
    x[7] =5;
    ASSERT_EQ(15, s1);
    ASSERT_EQ(10, s2);
    ASSERT_EQ(5, x[7]);
}

TYPED_TEST(TestDeque, resize3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15, 0);
    size_type s1 = x.size();
    x.resize(15, 1);
    size_type s2 = x.size();
    ASSERT_EQ(15, s1);
    ASSERT_EQ(15, s2);
}

TYPED_TEST(TestDeque, pop_front){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    for(int i = 0; i < 10; ++i)
        x.push_back(i);
    ASSERT_EQ(10, x.size());
    x.pop_front();
    ASSERT_EQ(9, x.size());
}

TYPED_TEST(TestDeque, pop_front2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    for(int i = 0; i < 15; ++i)
        x.push_back(i);
    ASSERT_EQ(15, x.size());
    x[5] = 3;
    for(int i = 0; i < 5; ++i)
        x.pop_front();
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(3, x[0]);
}

TYPED_TEST(TestDeque, pop_front3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
   
    x.push_back(1);
    ASSERT_EQ(1, x.size());
    x.pop_front();
    ASSERT_EQ(0, x.size());
}

TYPED_TEST(TestDeque, pop_back){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    for(int i = 0; i < 10; ++i)
        x.push_back(i);
    ASSERT_EQ(10, x.size());
    x.pop_back();
    ASSERT_EQ(9, x.size());    
}

TYPED_TEST(TestDeque, pop_back2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    for(int i = 0; i < 15; ++i)
        x.push_back(i);
    x[9] = 5;
    ASSERT_EQ(15, x.size());
    for(int i = 0; i < 5; ++i)
        x.pop_back();
    ASSERT_EQ(10, x.size());
    ASSERT_EQ(5, x[9]);    
}

TYPED_TEST(TestDeque, pop_back3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    x.push_back(1);
    ASSERT_EQ(1, x.size());
    x.pop_back();
    ASSERT_EQ(0, x.size());    
}

TYPED_TEST(TestDeque, push_front){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(8, 0);
    x.push_front(1);
    ASSERT_EQ(1, x[0]);    
}

TYPED_TEST(TestDeque, push_front2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x;
    x.push_front(1);
    ASSERT_EQ(1, x.size());
    ASSERT_EQ(1, x[0]);    
}

TYPED_TEST(TestDeque, push_front3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 0);
    x.push_front(1);
    ASSERT_EQ(11, x.size());
    ASSERT_EQ(1, x[0]);    
}

TYPED_TEST(TestDeque, copy_assignment){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(10, 1);
    deque_type y = x;

    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator e  = x.end();
    typename deque_type::iterator b  = y.begin();

    while(it != e)
        ASSERT_EQ(*it++, *b++);    
}

TYPED_TEST(TestDeque, copy_assignment2){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(15, 1);
    deque_type y = x;
    x.push_front(2);
    y.push_front(2);

    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator e  = x.end();
    typename deque_type::iterator b  = y.begin();

    while(it != e)
        ASSERT_EQ(*it++, *b++);    
}

TYPED_TEST(TestDeque, copy_assignment3){
    typedef typename TestFixture::deque_type      deque_type;
    typedef typename TestFixture::size_type       size_type;

    deque_type x(99, 1);
    deque_type y = x;

    typename deque_type::iterator it = x.begin();
    typename deque_type::iterator e  = x.end();
    typename deque_type::iterator b  = y.begin();

    while(it != e)
        ASSERT_EQ(*it++, *b++);    
} 