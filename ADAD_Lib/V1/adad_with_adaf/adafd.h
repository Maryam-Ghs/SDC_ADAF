#ifndef ADAFD_H
#define ADAFD_H

#include <stdio.h>
#include <cstdint>
#include <cstring>
#include <ulmblas/ulmblas.h>
#include <list>
#include <unordered_map>
#include <mutex>

class adafd {
public:
  double	value;
public:
  adafd() {
    value = 0.0f;
  };
  adafd(const adafd& val) {
    value = val.value;
  };
  adafd(double val) {
    value = val;
  };
  ~adafd() {
  };
  double val() {
    return value;
  };
  void set(double val) {
    value = val;
  };

  // assignment
  void operator= (double dval);
  void operator= (const adafd& val);

  // unary + and -
  adafd operator+ () const;
  adafd operator- () const;

  // binary +
  void operator+= (const adafd &a);
  adafd operator+ (const adafd &a) const;
  void operator+= (double dval);
  adafd operator+ (double dval) const;
  friend adafd operator+ (double dval, const adafd &a);

  // binary -
  void operator-= (const adafd &a);
  adafd operator- (const adafd &a) const;
  void operator-= (double dval);
  adafd operator- (double dval) const;
  friend adafd operator- (double dval, const adafd &a);

  // binary *
  void operator*= (const adafd &a);
  adafd operator* (const adafd &a) const;
  void operator*= (double dval);
  adafd operator* (double dval) const;
  friend adafd operator* (double dval, const adafd &a);

  // binary /
  void operator/= (const adafd &a);
  adafd operator/ (const adafd &a) const;
  void operator/= (double dval);
  adafd operator/ (double dval) const;
  friend adafd operator/ (double dval, const adafd &a);

  // relational operators
  int operator== (const adafd &a) const noexcept;
  int operator!= (const adafd &a) const;
  int operator< (const adafd &a) const;
  int operator> (const adafd &a) const;
  int operator<= (const adafd &a) const;
  int operator>= (const adafd &a) const;
  int operator== (double dval) const noexcept;
  int operator!= (double dval) const;
  int operator< (double dval) const;
  int operator> (double dval) const;
  int operator<= (double dval) const;
  int operator>= (double dval) const;
  friend int operator== (double dval, const adafd &a) noexcept;
  friend int operator!= (double dval, const adafd &a);
  friend int operator< (double dval, const adafd &a);
  friend int operator> (double dval, const adafd &a);
  friend int operator<= (double dval, const adafd &a);
  friend int operator>= (double dval, const adafd &a);

  // function calls
  friend adafd expf(const adafd &a);
  // function calls
  friend adafd sqrtf(const adafd &a);
};

class adafd_array {
private:
  adafd	*DATA;
  int	 size;
public:
  adafd_array(int N);
  adafd_array(double *A, int N);
  adafd &operator[](adafd jndex);
  adafd &operator[](int index);
};

struct adafdhash
{
    std::size_t operator()(const adafd& a) const noexcept
    {
        std::uint64_t bits;
        std::memcpy(&bits, &a.value, sizeof(bits));
        return std::hash<std::uint64_t>{}(bits);
    }
};

namespace ulmBLAS {

template class MemoryPool<adafd>;

template <>
struct BlockSize<adafd>
{
    static const int MC = 384;
    static const int KC = 384;
    static const int NC = 4096;
    static const int MR = 4;
    static const int NR = 4;
};

template <> inline
typename std::enable_if<! std::is_fundamental<adafd>::value,
         const adafd>::type
conjugate(const adafd &x)
{
    return x;
}

template <> inline
typename std::enable_if<! std::is_fundamental<adafd>::value,
         const adafd>::type
conjugate(const adafd &x, bool)
{
    return x;
}

}

#endif /* ADAFD_H */