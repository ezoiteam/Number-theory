#ifndef _GCD_HPP_
#define _GCD_HPP_

namespace alg {
template <typename T>
T gcd(T a, T b) {
  while (b) {
    T t = b;
    b = a % b;
    a = t;
  }
  return a;
}

template <typename T>
void exgcd(T a, T b, T c, T& x, T& y, T& d) {
  if (!b) {
    y = 0;
    d = a;
    x = c / a;
  } else {
    exgcd(b, a % b, c, y, x, d);
    y -= (a / b) * x;
  }
}
}

#endif  // _GCD_HPP_