// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------

#ifndef Deque_h
#define Deque_h

// --------
// includes
// --------

#include <algorithm> // copy, equal, lexicographical_compare, max, swap
#include <cassert>   // assert
#include <iterator>  // iterator, bidirectional_iterator_tag
#include <memory>    // allocator
#include <stdexcept> // out_of_range
#include <utility>   // !=, <=, >, >=
#include <cmath>


using namespace std;

// -----
// using
// -----

using std::rel_ops::operator!=;
using std::rel_ops::operator<=;
using std::rel_ops::operator>;
using std::rel_ops::operator>=;

// -------
// destroy
// -------

template <typename A, typename BI>
BI destroy (A& a, BI b, BI e) {
    while (b != e) {
        --e;
        a.destroy(&*e);}
    return b;}

// ------------------
// uninitialized_copy
// ------------------

template <typename A, typename II, typename BI>
BI uninitialized_copy (A& a, II b, II e, BI x) {
    BI p = x;
    try {
        while (b != e) {
            a.construct(&*x, *b);
            ++b;
            ++x;}}
    catch (...) {
        destroy(a, p, x);
        throw;}
    return x;}

// ------------------
// uninitialized_fill
// ------------------

template <typename A, typename BI, typename U>
BI uninitialized_fill (A& a, BI b, BI e, const U& v) {
    BI p = b;
    try {
        while (b != e) {
            a.construct(&*b, v);
            ++b;}}
    catch (...) {
        destroy(a, p, b);
        throw;}
    return e;}

// -------
// my_deque
// -------

template < typename T, typename A = std::allocator<T> >
class my_deque {
    public:
        // --------
        // typedefs
        // --------

        typedef A                                        allocator_type;
        typedef typename allocator_type::value_type      value_type;

        typedef typename allocator_type::size_type       size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename allocator_type::pointer         pointer;
        typedef typename allocator_type::const_pointer   const_pointer;

        typedef typename allocator_type::reference       reference;
        typedef typename allocator_type::const_reference const_reference;

        typedef typename allocator_type::template rebind<T*>::other p_a_t;
        typedef typename p_a_t::pointer p_p;

    public:
        // -----------
        // operator ==
        // -----------

        /**
         * <your documentation>
         */
        friend bool operator == (const my_deque& lhs, const my_deque& rhs) {
            //our code
            // you must use std::equal()
            if(lhs.size() != rhs.size())
                return false;
            return std::equal(lhs._b, lhs._e, rhs._b);
        }

        // ----------
        // operator <
        // ----------

        /**
         * <your documentation>
         */
        friend bool operator < (const my_deque& lhs, const my_deque& rhs) {
            // our code
            // you must use std::lexicographical_compare()
            return std::lexicographical_compare(lhs._b, lhs._e, rhs._b, rhs._e);
        }




    private:
        // ----
        // data
        // ----

        allocator_type _a;  // T allocator
        p_a_t _pa; // T* allocator

        p_p _fr;    // front of outer array
        p_p _ba;    // back of outer array
        pointer _b;     // beginning of inner array
        pointer _e;     // end of inner array

        pointer _front;     // front of allocated space
        pointer _begin;     // beginning of used space
        pointer _end;       // end of used space
        pointer _back;      // back of allocated space

       

        const size_type WIDTH = 10;

    private:
        // -----
        // valid
        // ----- 

        bool valid () const {
            // our code - taken from Prof. Downings Vector.h example
            return(!_begin && !_end) || ((_begin <= _end));
        }



    public:
        // --------
        // iterator
        // --------

        class iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::pointer         pointer;
                typedef typename my_deque::reference       reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return lhs._c == rhs._c && lhs.index == rhs.index;
                }

                /**
                 * <your documentation>
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----
                // <your data>

                my_deque* _c;
                size_type index;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return index >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                iterator (my_deque* c, size_type i = 0) : _c(c), index(0){

                    index = i;

                    assert(valid());
                }

                // Default copy, destructor, and copy assignment.
                // iterator (const iterator&);
                // ~iterator ();
                // iterator& operator = (const iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                    return (*_c)[index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator ++ () {
                    // ++(*this);
                    ++index;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator ++ (int) {
                    iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -- () {
                    // --(*this);
                    --index;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                iterator operator -- (int) {
                    iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator += (difference_type d) {
                    index += d;
                    // *this = *this + d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                iterator& operator -= (difference_type d) {
                    index -= d;
                    assert(valid());
                    return *this;}};

    public:
        // --------------
        // const_iterator
        // --------------

        class const_iterator {
            public:
                // --------
                // typedefs
                // --------

                typedef std::bidirectional_iterator_tag   iterator_category;
                typedef typename my_deque::value_type      value_type;
                typedef typename my_deque::difference_type difference_type;
                typedef typename my_deque::const_pointer   pointer;
                typedef typename my_deque::const_reference reference;

            public:
                // -----------
                // operator ==
                // -----------

                /**
                 * <your documentation>
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return lhs._c == rhs._c && lhs.index == rhs.index;}

                /**
                 * <your documentation>
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * <your documentation>
                 */
                friend const_iterator operator - (const_iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

                // <your data>

                const my_deque* _c;
                size_type index;

            private:
                // -----
                // valid
                // -----

                bool valid () const {
                    return index >= 0;}

            public:
                // -----------
                // constructor
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator  (const my_deque* c, size_type i = 0) : _c(c), index(0){

                    index = i;
                    assert(valid());}

                // Default copy, destructor, and copy assignment.
                // const_iterator (const const_iterator&);
                // ~const_iterator ();
                // const_iterator& operator = (const const_iterator&);

                // ----------
                // operator *
                // ----------

                /**
                 * <your documentation>
                 */
                reference operator * () const {
                   
                    return (*_c)[index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * <your documentation>
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator ++ () {
                    ++index;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator ++ (int) {
                    const_iterator x = *this;
                    ++(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator --
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;}

                /**
                 * <your documentation>
                 */
                const_iterator operator -- (int) {
                    const_iterator x = *this;
                    --(*this);
                    assert(valid());
                    return x;}

                // -----------
                // operator +=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator += (difference_type d) {
            // cout << "YOU CALLED THE CONSTANT ONE!!!  YEAH!!!"<< endl;

                    index += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * <your documentation>
                 */
                const_iterator& operator -= (difference_type d) {
                    index -= d
                    assert(valid());
                    return *this;}};

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
         //default size
        explicit my_deque (const allocator_type& a = allocator_type())
        : _a(a), _pa(), _fr(0), _ba(0), _b(0), _e(0), _front(0), _begin(0), _end(0), _back(0){

        assert(valid() );}

        /**
         * <your documentation>
         */
         // given size
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type())
        :_a(a), _pa(){
                // we need s / WIDTH full arrays, and possibly 1 partial array
            size_type num_arrays = s / WIDTH + (s % WIDTH? 1 : 0);
            // allocate outer array and save pointer to front
            _fr = _pa.allocate(num_arrays);
            // allocate inner arrays
            for (size_type i = 0; i < num_arrays; ++i) {
                _fr[i] = _a.allocate(WIDTH);
            }
            // set pointer to back
            _ba = _fr + num_arrays;
            // set pointer to beginning of data
            _b = _fr[0];
            // offset < WIDTH if we have a partial array
            size_type offset = WIDTH - (WIDTH * num_arrays - s); 
            assert  (0 < offset and offset <= WIDTH);
            // set pointer to end of data
            _e = _fr[num_arrays - 1] + offset;
            // fill inner arrays with default value
            for (size_type i = 0; i < num_arrays; ++i) {
                _a.deallocate(_fr[i], WIDTH);
            }
            _pa.deallocate(_fr, num_arrays);
            _front = _begin = _a.allocate(num_arrays * WIDTH);
            _back = _front + (num_arrays * WIDTH);
            _end = _begin + s;
            uninitialized_fill(_a, _front, _end, v);

            assert(valid());}

        /**
         * <your documentation>
         */
         //copy constructor
        my_deque (const my_deque& that) 
            : _a(that._a), _pa(that._pa),  _fr(0), _ba(0), _b(0), _e(0), _front(0), _begin(0), _end(0), _back(0){


            
            _fr = _ba = 0;
            _b = _e;
            _front = _begin = _a.allocate(that.size());
            _end = _back = _begin + that.size();
            uninitialized_copy(_a, that._begin, that._end, _begin);
 
        }




        my_deque(const my_deque& that, size_type s): _a(that._a), _pa(that._pa){
            _fr = _ba = 0;
            _b = _e;
            _front = _begin = _a.allocate(s);
            _end = _back = _begin + s;
            uninitialized_copy(_a, that._begin, that._end, _begin);
        }

        // ----------
        // destructor
        // ----------

        /**
         * <your documentation>
         */
        ~my_deque () {
            
            
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * <your documentation>
         */
        my_deque& operator = (const my_deque& rhs) {
            // <your code>
            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * <your documentation>
         */
        reference operator [] (size_type index) {
            reference x = *(_begin+ index);
            return x;}

        /**
         * <your documentation>
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * <your documentation>
         */
        reference at (size_type index) {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * <your documentation>
         */
        reference back () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * <your documentation>
         */
        iterator begin () {

            return iterator(this, 0);}

        /**
         * <your documentation>
         */
        const_iterator begin () const {
                    // cout << "YOU CALLED THE CONSTANT ONE!!!  YEAH!!!"<< endl;
            return const_iterator(this, 0);}

        // -----
        // clear
        // -----

        /**
         * <your documentation>
         */
        void clear () {
            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * <your documentation>
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * <your documentation>
         */
        iterator end () {
            // <your code>
            return iterator(this, size());}

        /**
         * <your documentation>
         */
        const_iterator end () const {
         // cout << "YOU CALLED THE CONSTANT END !!!  YEAH!!!"<< endl;

         return const_iterator(this, size() );}

        // -----
        // erase
        // -----

        /**
         * <your documentation>
         */
        iterator erase (iterator) {
            // <your code>
            assert(valid());
            return iterator();}

        // -----
        // front
        // -----

        /**
         * <your documentation>
         */
        reference front () {
            // <your code>
            // dummy is just to be able to compile the skeleton, remove it
            static value_type dummy;
            return dummy;}

        /**
         * <your documentation>
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * <your documentation>
         */
        iterator insert (iterator, const_reference) {
            // <your code>
            assert(valid());
            return iterator();}

        // ---
        // pop
        // ---

        /**
         * <your documentation>
         */
        void pop_back () {
            assert(!empty());
            resize(size() - 1);
            assert(valid());}

        /**
         * <your documentation>
         */
        void pop_front () {
            // <your code>
            assert(valid());}

        // ----
        // push
        // ----

        /**
         * <your documentation>
         */
        void push_back (const_reference v) {
            if(_end == _back){
                

            }
            if(_end != _back){
                _end = uninitialized_fill(_a, _end, _end + 1, v);
            }
            assert(valid());}

        /**
         * <your documentation>
         */
        void push_front (const_reference v) {
            // _b-- = v;
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * <your documentation>
         */
        void resize (size_type s, const_reference v = value_type()) {
            if(s == size())
                return;
            else if(s < size()){                                    // less than size
                _end = destroy(_a, _begin + s, _end);
            }else if(s <= (size_type)(_back - _front)){      // less than capacity, greater than size
                _end = uninitialized_fill(_a, _end, _end + (s - size()), v);
            }
            else{   
               cout << "AQUI ENTRO" << endl;                                             // greather than size & capacity
                my_deque x(*this, s);
                swap(x);
            }
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * <your documentation>
         */
        size_type size () const {
            return _end - _begin;
        }

        // ----
        // swap
        // ----

        /**
         * <your documentation>
         */
        void swap (my_deque& that) {

            if (_a == that._a) {
                std::swap(_front, that._front);
                std::swap(_begin, that._begin);
                std::swap(_end, that._end);
                std::swap(_back, that._back);}
            else {
                my_deque x(*this);
                *this = that;
                that = x;}
            assert(valid());}};

#endif // Deque_h
