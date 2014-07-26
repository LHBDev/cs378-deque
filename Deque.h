// ----------------------
// projects/deque/Deque.h
// Copyright (C) 2014
// Glenn P. Downing
// ----------------------
//-----------------------
// Deque.h
// Ruben Baeza rb27735
// Norman Lopez nel349
//-----------------------

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

        p_p _bucket_begin;
        p_p _bucket_end;

        pointer _inner_begin; 
        pointer _data_begin; 
        pointer _data_end;   
        pointer _inner_end;  
   

        const size_type DEFAULT_ARRAY_SIZE = 10;
        const size_type DEFAULT_BUCKET_SIZE = 3;

    private:
        // -----
        // valid
        // ----- 

        bool valid () const {
            // our code - taken from Prof. Downings Vector.h example
            return(!_data_begin && !_data_end) || ((_data_begin <= _data_end));
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
        : _a(a), _pa(), _bucket_begin(0), _bucket_end(0), _inner_begin(0), _data_begin(0), _data_end(0), _inner_end(0){

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

            size_type num_arrays = s / DEFAULT_ARRAY_SIZE + (s % DEFAULT_ARRAY_SIZE? 1 : 0);
            _bucket_begin = _pa.allocate(num_arrays);
            for (size_type i = 0; i < num_arrays; ++i) {
                _bucket_begin[i] = _a.allocate(DEFAULT_ARRAY_SIZE);
            }

            _bucket_end = _bucket_begin + num_arrays;
            size_type offset = DEFAULT_ARRAY_SIZE - (DEFAULT_ARRAY_SIZE * num_arrays - s); 
            _inner_begin = _data_begin = _a.allocate(num_arrays * DEFAULT_ARRAY_SIZE);
            _inner_end = _inner_begin + (num_arrays * DEFAULT_ARRAY_SIZE);
            _data_end = _data_begin + s;
            uninitialized_fill(_a, _data_begin, _data_end, v);

            assert(valid());}

        /**
         * @param deque this
         * @param deque that
         * deep copies that to this
         */
         //copy constructor
        my_deque (const my_deque& that) 
            : _a(that._a), _pa(that._pa),  _bucket_begin(0), _bucket_end(0), _inner_begin(0), _data_begin(0), _data_end(0), _inner_end(0){


            _bucket_begin = _bucket_end = 0;
            _inner_begin = _data_begin = _a.allocate(that.size());
            _data_end = _data_begin + that.size();
            _inner_end = _inner_begin + (that._inner_end - that._inner_begin);
            uninitialized_copy(_a, that._data_begin, that._data_end, _data_begin);
 
        }




        my_deque(const my_deque& that, size_type s): _a(that._a), _pa(that._pa){
            _bucket_begin = _bucket_end = 0;
            _inner_begin = _data_begin = _a.allocate(s);
            _data_end = _inner_end = _data_begin + s;
            uninitialized_copy(_a, that._data_begin, that._data_end, _data_begin);
        }

        // ----------
        // destructor
        // ----------

        /**
         * Destroys this deque and frees up all memory used
         */
        ~my_deque () {
            destroy(_a, _inner_begin, _inner_end);
            for (int i = 0; i < _bucket_end - _bucket_begin; ++i) {
                _a.deallocate(_bucket_begin[i], DEFAULT_ARRAY_SIZE);
            }
            
            _pa.deallocate(_bucket_begin, _bucket_end - _bucket_begin);
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
            _pa.deallocate(_bucket_begin, _bucket_end - _bucket_begin);
            destroy(_a, _data_begin, _inner_end);
            _a.deallocate(_data_begin, _inner_end - _data_begin);

            size_type new_size = rhs.size();
            size_type num_arrays = new_size / DEFAULT_ARRAY_SIZE + (new_size % DEFAULT_ARRAY_SIZE? 1 : 0);

            _bucket_begin = _pa.allocate(num_arrays);
            for(size_type i = 0; i < num_arrays; ++i){
                _bucket_begin[i] = _a.allocate(DEFAULT_ARRAY_SIZE);
            }

            _inner_begin = _data_begin = _a.allocate(new_size);
            _data_end = _data_begin + new_size;
            _inner_end = _inner_begin + (rhs._inner_end - rhs._inner_begin);
            _data_end = uninitialized_copy(_a, rhs._data_begin, rhs._data_end, _data_begin);


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
            reference x = *(_data_begin+ index);
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
            _pa.deallocate(_bucket_begin, _bucket_end - _bucket_begin);
            destroy(_a, _inner_begin, _inner_end);
            _a.deallocate(_inner_begin, _inner_end - _inner_begin);
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
            _data_end = destroy(_a, _data_end - 1, _data_end);
            assert(valid());}

        /**
         * @param this
         * removes the first element in deque
         */
        void pop_front () {
            _data_begin = destroy(_a, _data_begin, _data_begin + 1);
            ++_data_begin;
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
            if(_data_end == _inner_end){
                if(_data_end == 0){
                    _bucket_begin = _pa.allocate(DEFAULT_BUCKET_SIZE);
                    for(unsigned int i = 0; i < DEFAULT_BUCKET_SIZE; ++i)
                        _bucket_begin[i] = _a.allocate(DEFAULT_ARRAY_SIZE);

                    _bucket_end = _bucket_begin + DEFAULT_BUCKET_SIZE;
                    _inner_begin = _a.allocate( DEFAULT_BUCKET_SIZE * DEFAULT_ARRAY_SIZE);
                    _data_end = _data_begin = _inner_begin;
                    _inner_end = _inner_begin + (DEFAULT_BUCKET_SIZE * DEFAULT_ARRAY_SIZE);
                    _data_end = uninitialized_fill(_a, _data_begin, _data_begin +1, v);
                }
                else{
                    size_type old_size = size();
                    size_type new_size = size() * 2;
                    size_type num_arrays = new_size / DEFAULT_ARRAY_SIZE + (new_size % DEFAULT_ARRAY_SIZE? 1 : 0);

                    p_p temp_fr(0);
                    p_p temp_ba(0);

                    temp_fr = _pa.allocate(num_arrays);

                    for(size_type i = 0; i < num_arrays; ++i){
                        temp_fr[i] = _a.allocate(DEFAULT_ARRAY_SIZE);
                    }

                    temp_ba = temp_fr + num_arrays;

                    for(int i = 0; i < _bucket_end - _bucket_begin; ++i){
                        temp_fr[i] = _bucket_begin[i];
                    }
                    
                    destroy(_a, _inner_begin, _inner_end);
                    _pa.deallocate(_bucket_begin, _bucket_end - _bucket_begin);
                    _bucket_begin = temp_fr;
                    _bucket_end = temp_ba;
                    pointer old_front = _inner_begin;
                    _inner_begin = _a.allocate(num_arrays * new_size);

                    _data_end = uninitialized_copy(_a, _data_begin, _data_end, _inner_begin);
                    _a.deallocate(old_front, _inner_end - old_front);
                    _data_begin = _inner_begin;
                    _inner_end = _inner_begin + (new_size * num_arrays);
                    push_back(v);
                } 

            }
            else if(_data_end != _inner_end){
                _data_end = uninitialized_fill(_a, _data_end, _data_end + 1, v);
            }
            assert(valid());}

        /**
         * @param v - value to add to deque
         * adds v to front of deque
         */
        void push_front (const_reference v) {
            if(_data_begin == _inner_begin){
                if(_data_begin == 0){
                    _bucket_begin = _pa.allocate(DEFAULT_BUCKET_SIZE);
                    for(unsigned int i = 0; i < DEFAULT_BUCKET_SIZE; ++i)
                        _bucket_begin[i] = _a.allocate(DEFAULT_ARRAY_SIZE);

                    _bucket_end = _bucket_begin + DEFAULT_BUCKET_SIZE;
                    _inner_begin = _a.allocate(DEFAULT_BUCKET_SIZE * DEFAULT_ARRAY_SIZE);
                    _inner_end = _inner_begin + (DEFAULT_BUCKET_SIZE * DEFAULT_ARRAY_SIZE);
                    _data_begin = _inner_begin + DEFAULT_ARRAY_SIZE;
                    _data_end = uninitialized_fill(_a, _data_begin, _data_begin +1, v);

                }else{
                    size_type old_size = size();
                    size_type new_size = size() * 2;
                    size_type num_arrays = new_size / DEFAULT_ARRAY_SIZE + (new_size % DEFAULT_ARRAY_SIZE? 1 : 0);

                    p_p temp_fr(0);
                    p_p temp_ba(0);

                    temp_fr = _pa.allocate(num_arrays);

                    for(size_type i = 0; i < num_arrays; ++i){
                        temp_fr[i] = _a.allocate(DEFAULT_ARRAY_SIZE);
                    }

                    temp_ba = temp_fr + num_arrays;

                    for(int i = 1; i < _bucket_end - _bucket_begin; ++i){
                        temp_fr[i] = _bucket_begin[i];
                    }

                    destroy(_a, _inner_begin, _inner_end);
                    _pa.deallocate(_bucket_begin, _bucket_end - _bucket_begin);
                    _bucket_begin = temp_fr;
                    _bucket_end = temp_ba;
                    pointer old_front = _inner_begin;
                    _inner_begin = _a.allocate(num_arrays * new_size);

                    _data_end = uninitialized_copy(_a, _data_begin, _data_end, _inner_begin + DEFAULT_ARRAY_SIZE);
                    _a.deallocate(old_front, _inner_end - old_front);
                    _data_begin = _inner_begin + DEFAULT_ARRAY_SIZE;
                    _inner_end = _inner_begin + (new_size * num_arrays);
                    push_front(v);
                }
            }
            else if(_data_begin != _inner_begin){
                _data_begin = uninitialized_fill(_a, _data_begin -1, _data_begin, v);
                --_data_begin;
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
            return _data_end - _data_begin;
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
             destroy(_a, _inner_begin, _inner_end);
            _a.deallocate(_inner_begin, _inner_end - _inner_begin);

            if (_a == that._a) {
                std::swap(_inner_begin, that._inner_begin);
                std::swap(_data_begin, that._data_begin);
                std::swap(_data_end, that._data_end);
                std::swap(_inner_end, that._inner_end);}
            else {
                my_deque x(*this);
                *this = that;
                that = x;}
            assert(valid());}};

#endif // Deque_h
