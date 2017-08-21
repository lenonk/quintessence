//
// Created by lenon on 8/13/17.
//

#ifndef QUINTESSENCE_UTILITIES_H
#define QUINTESSENCE_UTILITIES_H

#include <cstddef>
#include <algorithm>

// Wrapper class
template <typename T>
class enumerate_impl
{
public:
    // The return value of the operator* of the iterator, this
    // is what you will get inside of the for loop
    struct node {
        size_t index;
        typename T::value_type &item;
    };
    typedef node value_type;

    // Custom iterator with minimal interface
    struct iterator {
        explicit iterator(typename T::iterator _it, size_t counter = 0) :
                it(_it), counter(counter) {}

        iterator operator ++() {
            return iterator(++it, ++counter);
        }

        bool operator!=(iterator other) {
            return it != other.it;
        }

        typename T::iterator::value_type item() {
            return *it;
        }

        value_type operator *() {
            return value_type{counter, *it};
        }

        size_t index() {
            return counter;
        }

    private:
        typename T::iterator it;
        size_t counter;
    };

    explicit enumerate_impl(T &t) : container(t) {}

    iterator begin() {
        return iterator(container.begin());
    }

    iterator end() {
        return iterator(container.end());
    }

private:
    T &container;
};

// A templated free function allows you to create the wrapper class
// conveniently
template <typename T>
enumerate_impl<T> enumerate(T &t) {
    return enumerate_impl<T>(t);
}

template<typename T1, typename T2>
void clamp(T1 a, T2 b, T2 c) { a = std::min(std::max(a, b), c); };

#endif //QUINTESSENCE_UTILITIES_H