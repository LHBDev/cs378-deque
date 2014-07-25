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
         * @param lhs - deque on left hand side of operation
         * @param rhs - deque on right hand side of operation
         * @return bool
         * returns a boolean indicating whether the two deques are the same size
         *      and hold the same values
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
         * @param lhs - deque on left hand side of operation
         * @param rhs - deque on right hand side of operation
         * @return bool
         * returns a boolean indicating whether lhs is lexicographically less than
         *                  rhs
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

        allocator_type _a;
        p_a_t _pa;

        p_p _fr;
        p_p _ba;
        pointer _b; 
        pointer _e; 

        pointer _front; 
        pointer _begin; 
        pointer _end;   
        pointer _back;  
   

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
                 * @param lhs - deque constant iterator for lhs of operation
                 * @param rhs - deque constant iterator for rhs of operation
                 * @return bool
                 * returns boolean indicating if the iterators iterate over the same
                 * containers
                 */
                friend bool operator == (const iterator& lhs, const iterator& rhs) {
                    return lhs._c == rhs._c && lhs.index == rhs.index;
                }

                /**
                 * @param lhs - constant iterator for lhs of operation
                 * @param rhs - constant iterator for rhs of operation
                 * @return bool
                 * returns boolean indicating if lhs iterators iterate over rhs
                 *      iterates over, uses ==
                 */
                friend bool operator != (const iterator& lhs, const iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs - deque iterator
                 * @param rhs - value to add to iterator
                 * @return iterator - lhs at new position
                 * returns iterator pointing to lhs + rhs
                 */
                friend iterator operator + (iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 * @param lhs - deque iterator
                 * @param rhs - value to subtract from iterator
                 * @return iterator - lhs at new position
                 * returns iterator pointing to lhs - rhs
                 */
                friend iterator operator - (iterator lhs, difference_type rhs) {
                    return lhs -= rhs;}

            private:
                // ----
                // data
                // ----

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
                 * @param c - pointer to deque
                 * @param i - index to start at
                 * constructs iterator for deque c at position i
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
                 * @parame deque
                 * @return reference
                 * returns a dereference for iterator
                 */
                reference operator * () const {
                    return (*_c)[index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * @param deque
                 * @return pointer
                 * returns pointer to item at deque[0]
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * @param deque
                 * @return iterator reference
                 * pre-increments an iterator
                 */
                iterator& operator ++ () {
                    // ++(*this);
                    ++index;
                    assert(valid());
                    return *this;}

                /**
                 * @param iterator
                 * @return iterator
                 * post-increments and returns old value
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
                 * @param iterator
                 * @return iterator reference
                 * pre-decrements iterator
                 */
                iterator& operator -- () {
                    // --(*this);
                    --index;
                    assert(valid());
                    return *this;}

                /**
                 * @param iterator
                 * @return iterator reference
                 * post-decrements iterator
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
                 * @param iterator
                 * @param d - value to add to iterator
                 * @return iterator reference to new position
                 * adds d to iterator and returns a reference to new iterator
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
                 * @param iterator
                 * @param d - value to subtract from iterator
                 * @return iterator reference
                 * subtracts d from iterator and returns reference to it
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
                 * @param lhs - constant iterator left hand side of operation
                 * @param rhs - constant iterator right hand side of operation
                 * @return bool
                 * returns whether two iterators iterate over same container
                 */
                friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) {
                    return lhs._c == rhs._c && lhs.index == rhs.index;}

                /**
                 * @param lhs - constant iterator left hand side of operation
                 * @param rhs - constant iterator right hand side of operation
                 * @return bool
                 * returns whether two iterators don't iterate over same things uses ==
                 */
                friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) {
                    return !(lhs == rhs);}

                // ----------
                // operator +
                // ----------

                /**
                 * @param lhs - const_iterator
                 * @param rhs - value to add to iterator
                 * @return const_iterator
                 * returns a constant iterator to position lhs + rhs
                 */
                friend const_iterator operator + (const_iterator lhs, difference_type rhs) {
                    return lhs += rhs;}

                // ----------
                // operator -
                // ----------

                /**
                 ** @param lhs - const_iterator
                 * @param rhs - value to subtract from iterator
                 * @return const_iterator
                 * returns a constant iterator to position lhs - rhs
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
                 * @param deque c
                 * @param index i
                 * construct a const_iterator for c starting at i
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
                 * @param const_iterator
                 * @return reference
                 * dereferences const_iterator
                 */
                reference operator * () const {
                   
                    return (*_c)[index];}

                // -----------
                // operator ->
                // -----------

                /**
                 * @param const_iterator
                 * @return pointer
                 * returns pointer to beginning of deque
                 */
                pointer operator -> () const {
                    return &**this;}

                // -----------
                // operator ++
                // -----------

                /**
                 * @param const_iterator
                 * @return const_iterator reference
                 * pre-increments const_iterator
                 */
                const_iterator& operator ++ () {
                    ++index;
                    assert(valid());
                    return *this;}

                /**
                 * @param const_iterator
                 * @return const_iterator 
                 * post-increments const_iterator
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
                 * @param const_iterator
                 * @return const_iterator reference
                 * pre-decrements const_iterator
                 */
                const_iterator& operator -- () {
                    --index;
                    assert(valid());
                    return *this;}

                /**
                 * @param const_iterator
                 * @return const_iterator
                 * post-decrements const_iterator
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
                 * @param cosnt_iterator
                 * @param value d
                 * @return const_iterator reference
                 * adds d to iterator
                 */
                const_iterator& operator += (difference_type d) {

                    index += d;
                    assert(valid());
                    return *this;}

                // -----------
                // operator -=
                // -----------

                /**
                 * @param const_iterator
                 * @param value d
                 * @return const_iterator reference
                 * subtracts d from iterator
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
         * @param allocator a - defaulted
         * cosntructs an empty deque
         */
         //default size
        explicit my_deque (const allocator_type& a = allocator_type())
        : _a(a), _pa(), _fr(0), _ba(0), _b(0), _e(0), _front(0), _begin(0), _end(0), _back(0){

        assert(valid() );}

        /**
         * @param s - size of deque to create
         * @param v - value to fill deque with - defaults to default for type
         * @param a - allocator - defaulted
         * constructs deque of size s filled with v
         */
         // given size
        explicit my_deque (size_type s, const_reference v = value_type(), const allocator_type& a = allocator_type())
        :_a(a), _pa(){

            size_type num_arrays = s / WIDTH + (s % WIDTH? 1 : 0);
            _fr = _pa.allocate(num_arrays);
            for (size_type i = 0; i < num_arrays; ++i) {
                _fr[i] = _a.allocate(WIDTH);
            }

            _ba = _fr + num_arrays;
            _b = _fr[0];
            size_type offset = WIDTH - (WIDTH * num_arrays - s); 
            _e = _fr[num_arrays - 1] + offset;            
            _front = _begin = _a.allocate(num_arrays * WIDTH);
            _back = _front + (num_arrays * WIDTH);
            _end = _begin + s;
            uninitialized_fill(_a, _begin, _end, v);

            assert(valid());}

        /**
         * @param deque this
         * @param deque that
         * deep copies that to this
         */
         //copy constructor
        my_deque (const my_deque& that) 
            : _a(that._a), _pa(that._pa),  _fr(0), _ba(0), _b(0), _e(0), _front(0), _begin(0), _end(0), _back(0){


            _fr = _ba = 0;
            _b = _e;
            _front = _begin = _a.allocate(that.size());
            _end = _begin + that.size();
            _back = _front + (that._back - that._front);
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
         * Destroys this deque and frees up all memory used
         */
        ~my_deque () {
            destroy(_a, _front, _back);
            for (int i = 0; i < _ba - _fr; ++i) {
                _a.deallocate(_fr[i], WIDTH);
            }
            
            _pa.deallocate(_fr, _ba - _fr);
            assert(valid());}

        // ----------
        // operator =
        // ----------

        /**
         * @param this
         * @param deque rhs
         * @return deque reference
         * deep copies rhs and assigns to this
         */
        my_deque& operator = (const my_deque& rhs) {
            clear();
            _pa.deallocate(_fr, _ba - _fr);
            destroy(_a, _begin, _back);
            _a.deallocate(_begin, _back - _begin);

            size_type new_size = rhs.size();
            size_type num_arrays = new_size / WIDTH + (new_size % WIDTH? 1 : 0);

            _fr = _pa.allocate(num_arrays);
            for(size_type i = 0; i < num_arrays; ++i){
                _fr[i] = _a.allocate(WIDTH);
            }

            _front = _begin = _a.allocate(new_size);
            _end = _begin + new_size;
            _back = _front + (rhs._back - rhs._front);
            uninitialized_copy(_a, rhs._begin, rhs._end, _begin);


            assert(valid());
            return *this;}

        // -----------
        // operator []
        // -----------

        /**
         * @param index
         * @return reference
         * returns reference to object at index in deque
         */
        reference operator [] (size_type index) {
            if(index > size() - 1)
                throw std::out_of_range("Bad Index");
            reference x = *(_begin+ index);
            return x;}

        /**
         * @param index
         * @return constant reference
         * returns constant reference to object at index in deque
         */
        const_reference operator [] (size_type index) const {
            return const_cast<my_deque*>(this)->operator[](index);}

        // --
        // at
        // --

        /**
         * @param index
         * @return reference
         * returns referece to object at index in deque
         */
        reference at (size_type index) {
            size_type i =0;
            auto _at = begin();
            while(i != index){
                ++_at;
                ++i;
            }
            return *_at;}

        /**
         * @param index
         * @return const_reference
         * returns constant reference to object at index in deque
         */
        const_reference at (size_type index) const {
            return const_cast<my_deque*>(this)->at(index);}

        // ----
        // back
        // ----

        /**
         * @param this
         * @return reference
         * returns last object in this
         */
        reference back () {
            auto b = end();
            --b;
            return *b;}

        /**
         * @param this
         * @return const_reference
         * returns constant reference to last object in deque
         */
        const_reference back () const {
            return const_cast<my_deque*>(this)->back();}

        // -----
        // begin
        // -----

        /**
         * @param this
         * @return iterator
         * returns iterator pointing to first object in deque
         */
        iterator begin () {

            return iterator(this, 0);}

        /**
         * @param this
         * @return const_iterator
         * returns constant iterator pointing to first object in deque
         */
        const_iterator begin () const {
            return const_iterator(this, 0);}

        // -----
        // clear
        // -----

        /**
         * @param this
         * clears the deque 
         */
        void clear () {
            _pa.deallocate(_fr, _ba - _fr);
            destroy(_a, _front, _back);
            _a.deallocate(_front, _back - _front);
            resize(0);
            assert(valid());}

        // -----
        // empty
        // -----

        /**
         * @param this
         * @return bool
         * returns if this deque is empty
         */
        bool empty () const {
            return !size();}

        // ---
        // end
        // ---

        /**
         * @param this
         * @return iterator
         * returns iterator to one index past the last element in deque
         */
        iterator end () {
            return iterator(this, size());}

        /**
         * @param this
         * @return const_iterator
         * returns const_iterator to on index past the last element in deque
         */
        const_iterator end () const {
         return const_iterator(this, size() );}

        // -----
        // erase
        // -----

        /**
         * @param iterator
         * @return iterator
         * removes the object at the current iterator and returns new iterator pointing
         *      to new objec at that position
         */
        iterator erase (iterator given_pos) {
            
           auto b = begin(); 
           auto e = end();
           size_type size = distance(b,e) - 1;
           size_type index_pos = distance(b , given_pos) ;
            // cout << "This is size: " << size << endl;
            // cout << "This is index_pos: " << index_pos <<endl;        
           my_deque x(size,0);
           size_type i = 0;
           for (auto pos = x.begin(), end = x.end(); pos!=end;) {
                if(i == index_pos){
                    ++b;
                }
                else{

                    *pos = *b;
                    ++b;

                    ++pos;
                }  
                ++i;

            }
            swap(x);
            assert(valid());
            return iterator(&x, index_pos);}

        // -----
        // front
        // -----

        /**
         * @param this
         * @return reference
         * retruns reference to the first item in array
         */
        reference front () {
            auto b = begin();
            return *b;}

        /**
         * @param this
         * @return const_reference
         * returns const_reference to the first item in array
         */
        const_reference front () const {
            return const_cast<my_deque*>(this)->front();}

        // ------
        // insert
        // ------

        /**
         * @param iterator - position where insert should occur
         * @param v - value to insert at position
         * @return iterator - returns new iterator to item inserted at current position
         */
        iterator insert (iterator given_pos, const_reference v) {
           
           auto b = begin(); 
           auto e = end();
           size_type size = distance(b,e) + 1;
           size_type index_pos = distance(b , given_pos) ;

           my_deque x(size,0);
           size_type i = 0;
           for (auto pos = x.begin(), end = x.end(); pos!=end; ++pos) {
                if(i == index_pos){
                    *pos = v;
                }
                else{
                    *pos = *b;
                    ++b;
                }                  
                ++i;    
            }


           
            swap(x);

            assert(valid());
            return iterator(&x, index_pos);}

        // ---
        // pop
        // ---

        /**
         * @param this
         * removes the last element in deque
         */
        void pop_back () {
            _end = destroy(_a, _end - 1, _end);
            assert(valid());}

        /**
         * @param this
         * removes the first element in deque
         */
        void pop_front () {
            _begin = destroy(_a, _begin, _begin + 1);
            ++_begin;
            assert(valid());}

        // ----
        // push
        // ----



        /**
         * @param v - value to add to deque
         * adds v to the back of deque
         */
        void push_back (const_reference v) {
            using namespace std;
            if(_end == _back){
                if(_end == 0){
                    _fr = _pa.allocate(3);
                    for(int i = 0; i < 3; ++i)
                        _fr[i] = _a.allocate(WIDTH);

                    _ba = _fr + 3;
                    _front = _a.allocate( 3 * WIDTH);
                    _end = _begin = _front;
                    _back = _front + (3 * WIDTH);
                    _end = uninitialized_fill(_a, _begin, _begin +1, v);
                }
                else{
                    size_type old_size = size();
                    size_type new_size = size() * 2;
                    size_type num_arrays = new_size / WIDTH + (new_size % WIDTH? 1 : 0);

                    p_p temp_fr(0);
                    p_p temp_ba(0);

                    temp_fr = _pa.allocate(num_arrays);

                    for(size_type i = 0; i < num_arrays; ++i){
                        temp_fr[i] = _a.allocate(WIDTH);
                    }

                    temp_ba = temp_fr + num_arrays;

                    for(int i = 0; i < _ba - _fr; ++i){
                        temp_fr[i] = _fr[i];
                    }
                    
                    destroy(_a, _front, _back);
                    _pa.deallocate(_fr, _ba - _fr);
                    _fr = temp_fr;
                    _ba = temp_ba;
                    pointer old_front = _front;
                    _front = _a.allocate(num_arrays * new_size);

                    _end = uninitialized_copy(_a, _begin, _end, _front);
                    _a.deallocate(old_front, _back - old_front);
                    _begin = _front;
                    _back = _front + (new_size * num_arrays);
                    push_back(v);
                }

            }
            else if(_end != _back){
                _end = uninitialized_fill(_a, _end, _end + 1, v);
            }
            assert(valid());}

        /**
         * @param v - value to add to deque
         * adds v to front of deque
         */
        void push_front (const_reference v) {
            if(_begin == _front){
                if(_begin == 0){
                    _fr = _pa.allocate(3);
                    for(int i = 0; i < 3; ++i)
                        _fr[i] = _a.allocate(WIDTH);

                    _ba = _fr + 3;
                    _front = _a.allocate(3 * WIDTH);
                    _back = _front + (3 * WIDTH);
                    _begin = _front + WIDTH;
                    _end = uninitialized_fill(_a, _begin, _begin +1, v);

                }else{
                    size_type old_size = size();
                    size_type new_size = size() * 2;
                    size_type num_arrays = new_size / WIDTH + (new_size % WIDTH? 1 : 0);

                    p_p temp_fr(0);
                    p_p temp_ba(0);

                    temp_fr = _pa.allocate(num_arrays);

                    for(size_type i = 0; i < num_arrays; ++i){
                        temp_fr[i] = _a.allocate(WIDTH);
                    }

                    temp_ba = temp_fr + num_arrays;

                    for(int i = 1; i < _ba - _fr; ++i){
                        temp_fr[i] = _fr[i];
                    }

                    destroy(_a, _front, _back);
                    _pa.deallocate(_fr, _ba - _fr);
                    _fr = temp_fr;
                    _ba = temp_ba;
                    pointer old_front = _front;
                    _front = _a.allocate(num_arrays * new_size);

                    _end = uninitialized_copy(_a, _begin, _end, _front + WIDTH);
                    _a.deallocate(old_front, _back - old_front);
                    _begin = _front + WIDTH;
                    _back = _front + (new_size * num_arrays);
                    push_front(v);
                }
            }
            else if(_begin != _front){
                _begin = uninitialized_fill(_a, _begin -1, _begin, v);
                --_begin;
            }
            assert(valid());}

        // ------
        // resize
        // ------

        /**
         * @param s - new size
         * @param v - value to fill with - defaulted
         * resizes the current deque to size s and fills with v if growing
         */
        void resize (size_type s, const_reference v = value_type()) {
            if(s < size())
            {
                pop_back();
                resize(s, v);
            }
            else if(s > size())
            {
                push_back(v);
                resize(s, v);
            }

            else
                return;
            assert(valid());}

        // ----
        // size
        // ----

        /**
         * returns the size of the deque
         */
        size_type size () const {
            return _end - _begin;
        }

        // ----
        // swap
        // ----

        /**
         * @param this - deque
         * @param that - deque
         * if allocators are equivalent - swaps all elements between this and that
         * else creates a copy of this and swaps deques between copy, this and that
         */
        void swap (my_deque& that) {
             destroy(_a, _front, _back);
            _a.deallocate(_front, _back - _front);

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
