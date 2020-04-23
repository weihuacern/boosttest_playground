#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

#include "huawei_vector.hpp"

namespace huawei {
    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n, const T& value) {
        _start = _alloc.allocate(n); // allocate memory
        std::uninitialized_fill(_start, _start + n, value); // http://www.cplusplus.com/reference/memory/uninitialized_fill/
        _end = _end_of_storage = _start + n; // modify the end related iterator
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(size_type n) {
        _start = _alloc.allocate(n);
        std::uninitialized_fill(_start, _start + n, 0); // Initialize with 0
        _end = _end_of_storage = _start + n;
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(iterator first, iterator last) {
        _start = _alloc.allocate(last - first); // http://www.cplusplus.com/reference/memory/allocator/allocate/
        _end = _end_of_storage = std::uninitialized_copy(first, last, _start); // http://www.cplusplus.com/reference/memory/uninitialized_copy/
    }

    template <class T, class Alloc>
    vector<T, Alloc>::vector(const vector& v) {
        size_type n = v.cend() - v.cbegin();
        _start = _alloc.allocate(n);
        _end = _end_of_storage = std::uninitialized_copy(v.cbegin(), v.cend(), _start);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::swap(vector &other) {
        std::swap(_start, other._start);
        std::swap(_end, other._end);
        std::swap(_end_of_storage, other._end_of_storage);
    }

    template <class T, class Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector &rhs) {
        if (this == &rhs) { return *this; }
        size_type n = rhs.cend() - rhs.cbegin();
        _start = _alloc.allocate(n);
        _end = _end_of_storage = std::uninitialized_copy(rhs.cbegin(), rhs.cend(), _start);
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::insert(iterator position, size_type n, const T& x) {
        if (n >= 0) {
            if (_end_of_storage - _end >= n) { // If enough capacity remain...
                T x_copy = x;
                const size_type elem_after = _end - position; // Calculate how many element do we need
                iterator old_end = _end;
                if (elem_after > n) {
                    std::uninitialized_copy(_end - n, _end, _end);
                    _end = _end + n; // move tail...
                    std::copy_backward(position, old_end - n, old_end); // http://www.cplusplus.com/reference/algorithm/copy_backward/
                    std::fill(position, position + n, x_copy); // http://www.cplusplus.com/reference/algorithm/fill/
                } else {
                    std::uninitialized_fill_n(_end, n - elem_after, x_copy); // http://www.cplusplus.com/reference/memory/uninitialized_fill_n/
                    _end += n - elem_after;
                    std::uninitialized_copy(position, old_end, _end);
                    _end += elem_after;
                    std::fill(position, old_end, x_copy);
                }
            } else { // If not enough capacity remain
                const size_type old_size = size();
                const size_type len = old_size + std::max(old_size, n); // http://www.cplusplus.com/reference/algorithm/max/
                iterator new_start = _alloc.allocate(len);
                iterator new_end = new_start;
                new_end = std::uninitialized_copy(_start, position , new_start); // copy original elements that before position
                new_end = std::uninitialized_fill_n(new_end, n, x); // insert new element
                new_end = std::uninitialized_copy(position, _end, new_end); // copy the rest of original element
                _destroy(); // destory
                _start = new_start;
                _end = new_end;
                _end_of_storage = new_start + len;
            }
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::push_back(const T& value) {
        if (_end != _end_of_storage) { // If enough capacity left
            _alloc.construct(_end, value); // https://en.cppreference.com/w/cpp/memory/allocator/construct
            ++_end; // move end iterator
        } else { // If not enough capacity left
            _insert_aux(end(), value);
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::pop_back() {
        --_end; // move end iterator back
        _alloc.destroy(_end);
    }

    //template <class T, class Alloc = std::allocator<T>>
    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position) {
        if (position + 1 != end()) {
            std::copy(position + 1, end(), position);
        }
        --_end;
        _alloc.destroy(_end);
        return position;
    }

    template <class T, class Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) {
        difference_type left = _end - last;
        std::copy(last, _end, first);
        iterator it(first + left);
        while (_end != it) {
            _alloc.destroy(--_end);
        }
        return first;
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::_insert_aux(iterator positon, const T& x) {
        if (_end != _end_of_storage) {
        } else {
            const size_type old_size = size();
            const size_type len = old_size ? 2 * old_size : 1; // length 1, otherwise double
            iterator new_start = _alloc.allocate(len); // re-allocate
            iterator new_end = new_start;

            new_end = std::uninitialized_copy(_start, positon, new_start); // copy origin before position
            _alloc.construct(new_end, x); // insert the one
            ++new_end;
            new_end = std::uninitialized_copy(positon, _end, new_end); // copy origin after position
            _destroy();
            // Point to new location
            _start = new_start;
            _end = new_end;
            _end_of_storage = new_start + len;
        }
    }

    template <class T, class Alloc>
    void vector<T, Alloc>::_destroy() {
        if (_start) {
            iterator it(_end);
            while (it != _start) { _alloc.destroy(--it); }
        }
        
        _alloc.deallocate(_start, _end_of_storage - _start);
        _start = _end_of_storage = _end = NULL;
    }

    template class vector<int>;
    template class vector<float>;
    template class vector<double>;
    template class vector<char>;
}
