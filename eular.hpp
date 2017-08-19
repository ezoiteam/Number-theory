#ifndef _EULAR_HPP_
#define _EULAR_HPP_
#include <cstdio>
#include <vector>
using std::vector;

namespace alg {
  void find_prime(vector<int>& prime, int n) {
    vector<int> vis(n + 1);
    for (int i = 2; i <= n; i++) {
      if (!vis[i]) prime.push_back(i);
      for (size_t j = 0; j < prime.size(); j++) {
        if (i * prime[j] > n) break;
        vis[i * prime[j]] = 1;
        if (i % prime[j] == 0) break;
      }
    }
  }
  template <typename _Tp>
  inline _Tp phi(_Tp x) {
    _Tp ret = x;
    for (int i = 2; i * i <= x; i++) {
      if (x % i == 0) {
        ret = ret / i * (i - 1);
        while (x % i == 0) x /= i;
      }
    }
    if (x > 1) ret = ret / x * (x - 1);
    return ret;
  }
};

#endif //  _EULAR_HPP_
