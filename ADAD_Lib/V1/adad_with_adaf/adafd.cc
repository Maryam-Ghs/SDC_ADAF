#include <stdio.h>
#include <string>
#include <map>
#include <cmath>
#include "FI_Lib.h"
#include "adafd.h"

// ADAFD Operator implementations
void adafd::operator=(double dval) {
  int id = get_location_id("F=K");
  value = get_faulty_double(id, dval);
}

void adafd::operator=(const adafd &v) { 
  int id = get_location_id("F=F");
  value = get_faulty_double(id, v.value);
}

// unary + and -
adafd adafd::operator+ () const { 
  return *this;
}

adafd adafd::operator- () const {
  adafd   r;
  int id = get_location_id("-F");
  r.value = get_faulty_double(id, -value);
  return(r);
}

// binary +
void adafd::operator+= (const adafd &a) {
  int id = get_location_id("F+=F");
  value = get_faulty_double(id, value + a.value);  
}

adafd adafd::operator+ (const adafd &a) const {
  adafd   r = *this;
  int id = get_location_id("F=F+F");
  r.value = get_faulty_double(id, r.value + a.value);  
  return(r);
}

void adafd::operator+= (double dval) {
  int id = get_location_id("F+=K");
  value = get_faulty_double(id, value + dval);  
}

adafd adafd::operator+ (double dval) const {
  adafd   r = *this;
  int id = get_location_id("F=F+K");
  r.value = get_faulty_double(id, r.value+dval);
  return(r);
}

adafd operator+ (double dval, const adafd &a) {
  adafd   r;
  int id = get_location_id("F=K+F");
  r.value = get_faulty_double(id, dval+r.value);
  return(r);
}

// binary -
void adafd::operator-= (const adafd &a) {
  int id = get_location_id("F-=F");
  value = get_faulty_double(id, value - a.value);
}

adafd adafd::operator- (const adafd &a) const {
  adafd   r = *this;
  int id = get_location_id("F=F-F");
  r.value = get_faulty_double(id, r.value - a.value);
  return(r);
}

void adafd::operator-= (double dval) {
  int id = get_location_id("F-=K");
  value = get_faulty_double(id, value - dval);
}

adafd adafd::operator- (double dval) const {
  adafd   r = *this;
  int id = get_location_id("F=F-K");
  r.value = get_faulty_double(id, r.value - dval);
  return(r);
}

adafd operator- (double dval, const adafd &a) {
  adafd   r;
  int id = get_location_id("F=K-F");
  r.value = get_faulty_double(id, dval - a.value);
  return(r);
}

// binary *
void adafd::operator*= (const adafd &a) {
  int id = get_location_id("F*=F");
  value = get_faulty_double(id, value * a.value);
}

adafd adafd::operator* (const adafd &a) const {
  adafd   r = *this;
  int id = get_location_id("F=F*F");
  r.value = get_faulty_double(id, r.value * a.value);
  return(r);
}

void adafd::operator*= (double dval) {
  int id = get_location_id("F*=K");
  value = get_faulty_double(id, value * dval);
}

adafd adafd::operator* (double dval) const {
  adafd   r = *this;
  int id = get_location_id("F=F*K");
  r.value = get_faulty_double(id, r.value * dval);
  return(r);
}

adafd operator* (double dval, const adafd &a) {
  adafd   r;
  int id = get_location_id("F=K*F");
  r.value = get_faulty_double(id, dval * a.value);
  return(r);
}

// binary /
void adafd::operator/= (const adafd &a) {
  int id = get_location_id("F/=F");
  value = get_faulty_double(id, value / a.value);
}

adafd adafd::operator/ (const adafd &a) const {
  adafd   r = *this;
  int id = get_location_id("F=F/F");
  r.value = get_faulty_double(id, r.value / a.value);
  return(r);
}

void adafd::operator/= (double dval) {
  int id = get_location_id("F/=K");
  value = get_faulty_double(id, value / dval);
}

adafd adafd::operator/ (double dval) const {
  adafd   r = *this;
  int id = get_location_id("F=F/K");
  r.value = get_faulty_double(id, r.value / dval);
  return(r);
}

adafd operator/ (double dval, const adafd &a) {
  adafd r;
  int id = get_location_id("F=K/F");
  r.value = get_faulty_double(id, dval / r.value);
  return(r);
}

// relational operators
int adafd::operator== (const adafd &a) const {
  int id = get_location_id("F==F");
  return get_faulty_boolean(id, value == a.value);
}

int adafd::operator!= (const adafd &a) const {
  int id = get_location_id("F!=F");
  return get_faulty_boolean(id, value != a.value);
}

int adafd::operator< (const adafd &a) const {
  int id = get_location_id("F<F");
  return get_faulty_boolean(id, value < a.value);
}

int adafd::operator> (const adafd &a) const {
  int id = get_location_id("F>F");
  return get_faulty_boolean(id, value > a.value);
}

int adafd::operator<= (const adafd &a) const {
  int id = get_location_id("F<=F");
  return get_faulty_boolean(id, value <= a.value);
}

int adafd::operator>= (const adafd &a) const {
  int id = get_location_id("F>=F");
  return get_faulty_boolean(id, value >= a.value);
}

int adafd::operator== (double dval) const {
  int id = get_location_id("F==K");
  return get_faulty_boolean(id, value == dval);
}

int adafd::operator!= (double dval) const {
  int id = get_location_id("F!=K");
  return get_faulty_boolean(id, value != dval);
}

int adafd::operator< (double dval) const {
  int id = get_location_id("F<K");
  return get_faulty_boolean(id, value < dval);
}

int adafd::operator> (double dval) const {
  int id = get_location_id("F>K");
  return get_faulty_boolean(id, value > dval);
}

int adafd::operator<= (double dval) const {
  int id = get_location_id("F<=K");
  return get_faulty_boolean(id, value <= dval);
}

int adafd::operator>= (double dval) const {
  int id = get_location_id("F>=K");
  return get_faulty_boolean(id, value >= dval);
}

int operator== (double dval, const adafd &a) {
  int id = get_location_id("K==F");
  return get_faulty_boolean(id, dval == a.value);
}

int operator!= (double dval, const adafd &a) {
  int id = get_location_id("K!=F");
  return get_faulty_boolean(id, dval != a.value);
}

int operator< (double dval, const adafd &a) {
  int id = get_location_id("K<F");
  return get_faulty_boolean(id, dval < a.value);
}

int operator> (double dval, const adafd &a) {
  int id = get_location_id("K>F");
  return get_faulty_boolean(id, dval > a.value);
}

int operator<= (double dval, const adafd &a) {
  int id = get_location_id("K<=F");
  return get_faulty_boolean(id, dval <= a.value);
}

int operator>= (double dval, const adafd &a) {
  int id = get_location_id("K>=F");
  return get_faulty_boolean(id, dval <= a.value);
}

adafd expf(const adafd &a) {
  int id = get_location_id("exp(F)");
  return get_faulty_double(id, std::exp((double)(a.value)));
}

adafd sqrtf(const adafd &a) {
  int id = get_location_id("sqrt(F)");
  return get_faulty_double(id, std::sqrt((double)(a.value)));
}

adafd_array::adafd_array(int N) {
  DATA = new adafd[N];
  size = N;
  for (int i=0; i<N; i++) {
    DATA[i].set( 0 );
  }
}

adafd_array::adafd_array(double *A, int N) {
  DATA = new adafd[N];
  size = N;
  for (int i=0; i<N; i++) {
    DATA[i].set( A[i] );
  }
}

adafd &adafd_array::operator[](int index) {
  if (index < 0 || index >= size) {
    // if the index is out of bounds, we assume a core dump
    coredump(index, 0, size);
  }
  return DATA[index];
}
