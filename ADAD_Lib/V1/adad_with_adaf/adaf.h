#ifndef ADAF_H
#define ADAF_H

#include <stdio.h>
#include <string>
#include <cstdint>
#include <cstring>
#include <ulmblas/ulmblas.h>
#include <list>
#include <unordered_map>
#include <mutex>


class adaf {
public:
  float	value;
public:
  adaf() {
    value = 0.0f;
  };
  adaf(const adaf& val) {
    value = val.value;
  };
  adaf(float val) {
    value = val;
  };
  ~adaf() {
  };
  float val() {
    return value;
  };
  void set(float val) {
    value = val;
  };

  // assignment
  void operator= (float dval);
  void operator= (const adaf& val);

  // unary + and -
  adaf operator+ () const;
  adaf operator- () const;

  // binary +
  void operator+= (const adaf &a);
  adaf operator+ (const adaf &a) const;
  void operator+= (float dval);
  adaf operator+ (float dval) const;
  friend adaf operator+ (float dval, const adaf &a);

  // binary -
  void operator-= (const adaf &a);
  adaf operator- (const adaf &a) const;
  void operator-= (float dval);
  adaf operator- (float dval) const;
  friend adaf operator- (float dval, const adaf &a);

  // binary *
  void operator*= (const adaf &a);
  adaf operator* (const adaf &a) const;
  void operator*= (float dval);
  adaf operator* (float dval) const;
  friend adaf operator* (float dval, const adaf &a);

  // binary /
  void operator/= (const adaf &a);
  adaf operator/ (const adaf &a) const;
  void operator/= (float dval);
  adaf operator/ (float dval) const;
  friend adaf operator/ (float dval, const adaf &a);

  // relational operators
  int operator== (const adaf &a) const noexcept;
  int operator!= (const adaf &a) const;
  int operator< (const adaf &a) const;
  int operator> (const adaf &a) const;
  int operator<= (const adaf &a) const;
  int operator>= (const adaf &a) const;
  int operator== (float dval) const noexcept;
  int operator!= (float dval) const;
  int operator< (float dval) const;
  int operator> (float dval) const;
  int operator<= (float dval) const;
  int operator>= (float dval) const;
  friend int operator== (float dval, const adaf &a) noexcept;
  friend int operator!= (float dval, const adaf &a);
  friend int operator< (float dval, const adaf &a);
  friend int operator> (float dval, const adaf &a);
  friend int operator<= (float dval, const adaf &a);
  friend int operator>= (float dval, const adaf &a);

  // function calls
  friend adaf expf(const adaf &a);
  // function calls
  friend adaf sqrtf(const adaf &a);
};

class adaf_array {
private:
  adaf	*DATA;
  int	 size;
public:
  adaf_array(int N);
  adaf_array(float *A, int N);
  adaf &operator[](adaf jndex);
  adaf &operator[](int index);
};

struct adafhash
{
    std::size_t operator()(const adaf& a) const noexcept
    {
        std::uint32_t bits;
        std::memcpy(&bits, &a.value, sizeof(bits));
        return std::hash<std::uint32_t>{}(bits);
    }
};

namespace ulmBLAS {

template class MemoryPool<adaf>;

template <>
struct BlockSize<adaf>
{
    static const int MC = 768;
    static const int KC = 384;
    static const int NC = 4096;
    static const int MR = 8;
    static const int NR = 4;
};

template <> inline
typename std::enable_if<! std::is_fundamental<adaf>::value,
         const adaf>::type
conjugate(const adaf &x)
{
    return x;
}

template <> inline
typename std::enable_if<! std::is_fundamental<adaf>::value,
         const adaf>::type
conjugate(const adaf &x, bool)
{
    return x;
}
}


#endif /* ADAF_H */
