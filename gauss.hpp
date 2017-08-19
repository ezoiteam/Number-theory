#ifndef _GAUSS_HPP_
#define _GAUSS_HPP_
#include <algorithm>
#include "gcd.hpp"
#include "matrix.hpp"
using std::abs;

namespace alg {
void gauss_elimination(matrix<long long>& equations, std::vector<int>& ans,
                       int mod = 2147483647) {
  for (int i = 0, j = 0; i < equations.row && j < equations.col; j++) {
    int max_row = i;
    for (int k = i + 1; k < equations.row; k++)
      if (abs(equations[k][j]) > abs(equations[max_row][j])) max_row = k;
    if (equations[max_row][j] != 0) {
      for (int k = 0; k < equations.row; k++)
        std::swap(equations[max_row][k], equations[i][k]);
      for (int k = i + 1; k < equations.row; k++) {
        int temp_gcd = gcd(equations[i][j], equations[k][j]);
        int org_gcd = equations[i][j] / temp_gcd;
        int now_gcd = equations[k][j] / temp_gcd;
        for (int l = 0; l < equations.col; l++) {
          equations[k][l] *= org_gcd;
          equations[k][l] -= (long long)equations[i][l] * now_gcd % mod;
        }
      }
      i++;
    }
  }
  for (int i = equations.row - 1, j = equations.col - 1; i >= 0 && j >= 0;
       j--) {
    if (equations[i][j] != 0) {
      for (int k = i - 1; k >= 0; k--) {
        int temp_gcd = gcd(equations[i][j], equations[k][j]);
        int org_gcd = equations[i][j] / temp_gcd;
        int now_gcd = equations[k][j] / temp_gcd;
        for (int l = 0; l < equations.col; l++) {
          equations[k][l] *= org_gcd;
          equations[k][l] -= (long long)equations[i][l] * now_gcd % mod;
        }
      }
      i--;
    }
  }
  for (int i = 0; i < equations.row; i++) {
    int cnt = 0;
    int pos = 0;
    for (int j = 0; j < equations.col; j++)
      if (equations[i][j]) {
        cnt++;
        pos = j;
      }
    if (cnt == 1) ans[i] = equations[i][pos];
  }
}
template <typename _Tp>
void gauss_elimination(matrix<_Tp>& equations, vector<_Tp>& ans) {
  for (int i = 0, j = 0; i < equations.row && j < equations.col; j++) {
    int max_row = i;
    for (int k = i + 1; k < equations.row; k++)
      if (abs(equations[k][j]) > abs(equations[max_row][j])) max_row = k;
    if (equations[max_row][j]) {
      for (int k = 0; k < equations.col; k++)
        std::swap(equations[max_row][k], equations[i][k]);
      _Tp division = equations[i][j];
      for (int k = 0; k < equations.col; k++) equations[i][k] /= division;
      for (int k = i + 1; k < equations.row; k++) {
        _Tp multi = equations[k][j];
        for (int l = 0; l < equations.col; l++)
          equations[k][l] -= equations[i][l] * multi;
      }
      i++;
    }
  }
  for (int i = equations.row - 1, j = equations.col - 2; i >= 0 && j >= 0;
       j--) {
    if (equations[i][j]) {
      _Tp division = equations[i][j];
      for (int k = equations.col - 1; k >= 0; k--) equations[i][k] /= division;
      for (int k = i - 1; k >= 0; k--) {
        _Tp multi = equations[k][j];
        for (int l = equations.col - 1; l >= 0; l--)
          equations[k][l] -= equations[i][l] * multi;
      }
      i--;
    }
  }
  int flag = 0;
  int free_cnt = 0;
  for (int i = 0; i < equations.row; i++) {
    int cnt = 0;
    for (int j = 0; j < equations.col - 1; j++) {
      if (equations[i][j] != 0) cnt++;
    }
    if (cnt == 1)
      ans[i] = equations[i][equations.col - 1];
    else {
      flag = 1;
      free_cnt += cnt - 1;
    }
  }
  if (flag == 1) throw cnt;
}
template <typename _Tp>
void gauss_elimination(matrix<_Tp>& equations, int row_idx, int col_idx) {
  _Tp division = equations[row_idx][col_idx];
  for (int i = 0; i < equations.col; i++) equations[row_idx][i] /= division;
  for (int i = 0; i < equations.row; i++) {
    if (i != row_idx && equations[i][col_idx] != 0) {
      _Tp multi = equations[i][col_idx];
      for (int j = 0; j < equations.col; j++)
        equations[i][j] -= equations[row_idx][j] * multi;
    }
  }
}
}

#endif  // _GAUSS_HPP_