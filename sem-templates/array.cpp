#include <iostream>
#include <cstring>

using namespace std;

template <typename T>
class Array {
 public:
    ~Array() {
        delete[] buffer;
    }

    void Add(const T& element) {
        buffer[size] = element;
        ++size;
        if (size > capacity) {
            T* newBuffer = new T[capacity*2];
            memmove(newBuffer, buffer, size * sizeof(T));
            delete[] buffer;
            buffer = newBuffer;
        }
    }

    int Size() const {
        return size;
    }

    T& operator[](int pos) {
        return buffer[pos];
    }

    const T& operator[](int pos) const {
        return buffer[pos];
    }

 private:
    static constexpr int initialCapacity = 4;
    T* buffer = new T[initialCapacity];
    int size = 0;
    int capacity = initialCapacity;
};

int main() {
    Array<int> arr;
    for (int i = 0; i < 10; ++i) {
        arr.Add(i);
    }
    for (int i = 0; i < arr.Size(); ++i) {
        std::cout << arr[i] << std::endl;
    }
    return 0;
}