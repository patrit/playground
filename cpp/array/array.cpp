#include <cstdio>
#include <cstring>
#include <initializer_list>
#include <cassert>

template< class T, size_t M >
class ArrayProxy;

template< class T, size_t M >
class Array
{
public:
  Array() { _data = {0}; };
  Array(std::initializer_list<T> const& l) {
    assert(l.size() <= M);
    size_t i = 0;
    for (auto v: l) {
      _data[i] = v;
      i++;
    }
  };

  T& operator() (size_t m) { return _data[m-1]; }
  ArrayProxy<T, M> operator() (size_t start, size_t end) { return ArrayProxy<T, M>(*this, start, end); }

private:
  T _data[M];
};

template< class T, size_t M >
class ArrayProxy
{
public:
  ArrayProxy(Array<T, M>& data, size_t start, size_t end) :
    _data(data), _start(start), _end(end) {
  }
  
  template< class Z >
  ArrayProxy<T, M>& operator= (Z const* values) {
    Z const* val = values;
    for(size_t pos = _start; pos != _end; pos++) {
      _data(pos) = static_cast<T>(*val);
      val++;
    }
    return *this;
  }
  
private:
  Array<T, M>& _data;
  size_t _start;
  size_t _end;
};

int main()
{
    Array<short, 4> o = {1, 2, 3, 4};
    printf("val = %d %d %d %d\n", o(1), o(2), o(3), o(4));
    o(4) = 12;
    printf("val = %d %d %d %d\n", o(1), o(2), o(3), o(4));    
    o(2, 4) = "foo";
    printf("val = %d %d %d %d\n", o(1), o(2), o(3), o(4));    
}
