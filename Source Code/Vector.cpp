#include <iostream>
using namespace std;

struct Vector {
  int *arr, cap, length;
  Vector() { length = 0; cap = 10; arr = new int[cap]; }
  Vector(int sz) { length = 0; cap = sz + 2; arr = new int[cap]; }
  Vector(const Vector& src) { copy(src); }
  Vector& operator = (const Vector& rhs) { copy(rhs); return *this; }
  void copy(const Vector& src) {
    if (this == &src) return;
    clear();
    cap = src.cap;
    length = src.length;
    arr = new int[cap];
    for (int i = 0; i < length; ++i) arr[i] = src.arr[i];
  }
  void clear() {
    delete [] arr;
    length = 0;
    cap = 10;
  }
  ~Vector() { clear(); }
  int& operator [] (int i) { return arr[i]; }
  void pushBack(int n) {
    if (cap <= length + 1) {
      cap *= 2;
      int *newArr = new int[cap];
      for (int i = 0; i < length; ++i) newArr[i] = arr[i];
      delete [] arr;
      arr = newArr;
    }
    arr[length++] = n;
  }
};