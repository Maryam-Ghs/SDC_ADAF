#ifndef ADAF_H
#define ADAF_H

#include <stdio.h>

class adaf {
protected:
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
  int operator== (const adaf &a) const;
  int operator!= (const adaf &a) const;
  int operator< (const adaf &a) const;
  int operator> (const adaf &a) const;
  int operator<= (const adaf &a) const;
  int operator>= (const adaf &a) const;
  int operator== (float dval) const;
  int operator!= (float dval) const;
  int operator< (float dval) const;
  int operator> (float dval) const;
  int operator<= (float dval) const;
  int operator>= (float dval) const;
  friend int operator== (float dval, const adaf &a);
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

// functions in fault.cpp
extern float get_faulty_float(int id, float value);
extern int get_faulty_boolean(int id, int value);

// functions in main.cpp
extern int coredump(int index, int lb, int ub);
  
#endif /* ADAF_H */
