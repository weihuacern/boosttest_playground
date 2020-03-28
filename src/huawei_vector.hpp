#include <algorithm>
#include <iostream>
#include <memory>

namespace huawei {
	template <class T, class Alloc=std::allocator<T>> class vector {
	public:
	    typedef T value_type;
		typedef value_type* iterator;
	    typedef const value_type* const_iterator;
	    typedef value_type& reference;
	    typedef value_type* pointer;
	    typedef	size_t size_type;
		typedef ptrdiff_t difference_type;
    protected:
        std::allocator<value_type> _alloc; // memory allocator
	    iterator _start; // first of used element
	    iterator _end; // last of used element
	    iterator _end_of_storage; // last of whole capacity
    public:
	    vector() :_start(0), _end(0), _end_of_storage(0){} // default constructor
	    vector(size_type n, const T& value);
	    vector(size_type n);
	    vector(iterator first, iterator last);
	    vector(const vector& v);
	    vector& operator=(const vector& rhs); // overload operator=
	    ~vector() { _destroy(); } // destructor

	    iterator begin() { return _start; }
	    iterator end() { return _end; }
	    const_iterator cbegin() const { return _start; } // const iterator
	    const_iterator cend() const { return _end; } // const iterator

	    size_type size()  { return size_type(end() - begin()); }
	    size_type capacity() { return size_type(_end_of_storage - begin()); }
	    bool empty() { return begin() == end(); }
	    void swap(vector &other);

	    reference front() { return *begin(); }
	    reference back() { return *(end() - 1); }
	    reference operator[] (size_type n) { return *(begin() + n); } // overload operator[]

		void push_back(const T& value);
		void pop_back();
		void insert(iterator position, size_type n, const T& x);

		iterator erase(iterator position);
		iterator erase(iterator first, iterator last); // erase all elements between first and last
		void clear() { erase(begin(), end()); }
	private:
	    void _insert_aux(iterator positon, const T& x);
		void _destroy();
    };
}
