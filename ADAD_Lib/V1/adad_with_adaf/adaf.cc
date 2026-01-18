#include <stdio.h>
#include <string>
#include <map>
#include <cmath>
#include "FI_Lib.h"
#include "adaf.h"

// ADAF Operator implementations
void adaf::operator=(float dval) {
  int id = get_location_id("F=K");
  value = get_faulty_float(id, dval);
}

void adaf::operator=(const adaf &v) { 
  int id = get_location_id("F=F");
  value = get_faulty_float(id, v.value);
}

// unary + and -
adaf adaf::operator+ () const { 
  return *this;
}

adaf adaf::operator- () const {
  adaf   r;
  int id = get_location_id("-F");
  r.value = get_faulty_float(id, -value);
  return(r);
}

// binary +
void adaf::operator+= (const adaf &a) {
  int id = get_location_id("F+=F");
  value = get_faulty_float(id, value + a.value);  
}

adaf adaf::operator+ (const adaf &a) const {
  adaf   r = *this;
  int id = get_location_id("F=F+F");
  r.value = get_faulty_float(id, r.value + a.value);  
  return(r);
}

void adaf::operator+= (float dval) {
  int id = get_location_id("F+=K");
  value = get_faulty_float(id, value + dval);  
}

adaf adaf::operator+ (float dval) const {
  adaf   r = *this;
  int id = get_location_id("F=F+K");
  r.value = get_faulty_float(id, r.value+dval);
  return(r);
}

adaf operator+ (float dval, const adaf &a) {
  adaf   r;
  int id = get_location_id("F=K+F");
  r.value = get_faulty_float(id, dval+r.value);
  return(r);
}

// binary -
void adaf::operator-= (const adaf &a) {
  int id = get_location_id("F-=F");
  value = get_faulty_float(id, value - a.value);
}

adaf adaf::operator- (const adaf &a) const {
  adaf   r = *this;
  int id = get_location_id("F=F-F");
  r.value = get_faulty_float(id, r.value - a.value);
  return(r);
}

void adaf::operator-= (float dval) {
  int id = get_location_id("F-=K");
  value = get_faulty_float(id, value - dval);
}

adaf adaf::operator- (float dval) const {
  adaf   r = *this;
  int id = get_location_id("F=F-K");
  r.value = get_faulty_float(id, r.value - dval);
  return(r);
}

adaf operator- (float dval, const adaf &a) {
  adaf   r;
  int id = get_location_id("F=K-F");
  r.value = get_faulty_float(id, dval - a.value);
  return(r);
}

// binary *
void adaf::operator*= (const adaf &a) {
  int id = get_location_id("F*=F");
  value = get_faulty_float(id, value * a.value);
}

adaf adaf::operator* (const adaf &a) const {
  adaf   r = *this;
  int id = get_location_id("F=F*F");
  r.value = get_faulty_float(id, r.value * a.value);
  return(r);
}

void adaf::operator*= (float dval) {
  int id = get_location_id("F*=K");
  value = get_faulty_float(id, value * dval);
}

adaf adaf::operator* (float dval) const {
  adaf   r = *this;
  int id = get_location_id("F=F*K");
  r.value = get_faulty_float(id, r.value * dval);
  return(r);
}

adaf operator* (float dval, const adaf &a) {
  adaf   r;
  int id = get_location_id("F=K*F");
  r.value = get_faulty_float(id, dval * a.value);
  return(r);
}

// binary /
void adaf::operator/= (const adaf &a) {
  int id = get_location_id("F/=F");
  value = get_faulty_float(id, value / a.value);
}

adaf adaf::operator/ (const adaf &a) const {
  adaf   r = *this;
  int id = get_location_id("F=F/F");
  r.value = get_faulty_float(id, r.value / a.value);
  return(r);
}

void adaf::operator/= (float dval) {
  int id = get_location_id("F/=K");
  value = get_faulty_float(id, value / dval);
}

adaf adaf::operator/ (float dval) const {
  adaf   r = *this;
  int id = get_location_id("F=F/K");
  r.value = get_faulty_float(id, r.value / dval);
  return(r);
}

adaf operator/ (float dval, const adaf &a) {
  adaf r;
  int id = get_location_id("F=K/F");
  r.value = get_faulty_float(id, dval / r.value);
  return(r);
}

// relational operators
int adaf::operator== (const adaf &a) const noexcept {
  int id = get_location_id("F==F");
  return get_faulty_boolean(id, value == a.value);
}

int adaf::operator!= (const adaf &a) const {
  int id = get_location_id("F!=F");
  return get_faulty_boolean(id, value != a.value);
}

int adaf::operator< (const adaf &a) const {
  int id = get_location_id("F<F");
  return get_faulty_boolean(id, value < a.value);
}

int adaf::operator> (const adaf &a) const {
  int id = get_location_id("F>F");
  return get_faulty_boolean(id, value > a.value);
}

int adaf::operator<= (const adaf &a) const {
  int id = get_location_id("F<=F");
  return get_faulty_boolean(id, value <= a.value);
}

int adaf::operator>= (const adaf &a) const {
  int id = get_location_id("F>=F");
  return get_faulty_boolean(id, value >= a.value);
}

int adaf::operator== (float dval) const noexcept {
  int id = get_location_id("F==K");
  return get_faulty_boolean(id, value == dval);
}

int adaf::operator!= (float dval) const {
  int id = get_location_id("F!=K");
  return get_faulty_boolean(id, value != dval);
}

int adaf::operator< (float dval) const {
  int id = get_location_id("F<K");
  return get_faulty_boolean(id, value < dval);
}

int adaf::operator> (float dval) const {
  int id = get_location_id("F>K");
  return get_faulty_boolean(id, value > dval);
}

int adaf::operator<= (float dval) const {
  int id = get_location_id("F<=K");
  return get_faulty_boolean(id, value <= dval);
}

int adaf::operator>= (float dval) const {
  int id = get_location_id("F>=K");
  return get_faulty_boolean(id, value >= dval);
}

int operator== (float dval, const adaf &a) noexcept {
  int id = get_location_id("K==F");
  return get_faulty_boolean(id, dval == a.value);
}

int operator!= (float dval, const adaf &a) {
  int id = get_location_id("K!=F");
  return get_faulty_boolean(id, dval != a.value);
}

int operator< (float dval, const adaf &a) {
  int id = get_location_id("K<F");
  return get_faulty_boolean(id, dval < a.value);
}

int operator> (float dval, const adaf &a) {
  int id = get_location_id("K>F");
  return get_faulty_boolean(id, dval > a.value);
}

int operator<= (float dval, const adaf &a) {
  int id = get_location_id("K<=F");
  return get_faulty_boolean(id, dval <= a.value);
}

int operator>= (float dval, const adaf &a) {
  int id = get_location_id("K>=F");
  return get_faulty_boolean(id, dval <= a.value);
}

adaf expf(const adaf &a) {
  int id = get_location_id("exp(F)");
  return get_faulty_float(id, std::exp((float)(a.value)));
}

adaf sqrtf(const adaf &a) {
  int id = get_location_id("sqrt(F)");
  return get_faulty_float(id, std::sqrt((float)(a.value)));
}

adaf_array::adaf_array(int N) {
  DATA = new adaf[N];
  size = N;
  for (int i=0; i<N; i++) {
    DATA[i].set( 0 );
  }
}

adaf_array::adaf_array(float *A, int N) {
  DATA = new adaf[N];
  size = N;
  for (int i=0; i<N; i++) {
    DATA[i].set( A[i] );
  }
}

adaf &adaf_array::operator[](int index) {
  if (index < 0 || index >= size) {
    // if the index is out of bounds, we assume a core dump
    coredump(index, 0, size);
  }
  return DATA[index];
}
