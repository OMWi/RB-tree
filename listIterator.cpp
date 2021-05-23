#include <iostream>
#include <iterator>
#include <cstddef>


class Integers {
    int m_data[10];
public:
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int;
        using pointer = int*;
        using reference = int&;

        Iterator(pointer ptr) : m_ptr(ptr) {}
        reference operator*() const { return *m_ptr;}
        //pointer operator->() { return m_ptr; }
        Iterator& operator++() {m_ptr++; return *this; }
        //Iterator operator++(int) {Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }
    private:
        pointer m_ptr;
    };
    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[10]); }


};

int main() {
    Integers integers;
    std::fill(integers.begin(), integers.end(), 3);
    for (auto elem : integers) {
        std::cout << elem << ' ';
    }
    std::cout << "\n\n";

}