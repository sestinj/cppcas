#include "arrayfire.h"
#include <iostream>
#include <vector>
using namespace std;

vector<int> slow_double(vector<int> a) {
    vector<int> b(a.size());
    for (int i = 0; i < a.size(); i++) {
        b[i] = a[i] * 2;
    }
    return b;
}

vector<int> fast_double(vector<int> a) {
    vector<int> b(a.size());
    af::array a_af = af::array(a.size(), a.data());
    af::array b_af = a_af * 2;
    b_af.host(b.data());
    return b;
}

double fast_sum() {
    // Generate 10,000 random values
    af::array a = af::randu(10000);
 
    // Sum the values and copy the result to the CPU:
    double sum = af::sum<float>(a);
 
    printf("sum: %g\n", sum);
    return sum;
}

double slow_sum() {
    // Generate 10,000 random values
    vector<int> a(10000);
    for (int i = 0; i < a.size(); i++) {
        a[i] = i;
    }
    double sum = 0;
    for (int i = 0; i < a.size(); i++) {
        sum += a[i];
    }
    return sum;
}
int main() {
  
  af::timer::start();
  double a = fast_sum();
  printf("Slow double: %f\n", af::timer::stop());

  af::timer::start();
  double b = slow_sum();
  printf("Fast double: %f\n", af::timer::stop());
  return 0;
}