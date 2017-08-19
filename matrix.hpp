#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_
#include <vector>
using std::vector;

namespace alg {
template <typename _Tp>
class matrix {
 private:
  vector<vector<_Tp>> _matrix;

 public:
  int col, row;
    explicit matrix(size_t n = 0, size_t m = 0) {
    _matrix = vector<vector<_Tp>>(n, vector<_Tp>(m));
    row = n;
    col = m;
  }
  template <typename _Initial_function>
  explicit matrix(size_t n, size_t m, _Initial_function initial_func) {
    _matrix = vector<vector<_Tp>>(n, vector<_Tp>(m));
    row = n;
    col = m;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        _matrix[i][j] = initial_func(i, j);
  }
  matrix(int n, int m, int ** init_m) {
    _matrix = vector<vector<_Tp>>(n, vector<_Tp>(m));
    row = n;
    col = m;
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        _matrix[i][j] = init_m[i][j];
  }
  ~matrix() {}
  vector<_Tp>& operator[](const int& idx) { return _matrix[idx]; }
  matrix operator*(const matrix& t) const {
    if (col != t.row) return matrix(0, 0);
    matrix ret(row, t.col);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < t.col; j++)
        for (int k = 0; k < col; k++) ret[i][j] += _matrix[i][k] * t[k][j];
    return ret;
  }
  matrix operator+(const matrix& t) const {
    if (col != t.tol && row != t.row) return matrix(0, 0);
    matrix ret(row, col);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        ret[i][j] = _matrix[i][j] + t[i][j];
    return ret;
  }
  matrix operator-(const matrix& t) const {
    if (col != t.tol && row != t.row) return matrix(0, 0);
    matrix ret(row, col);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        ret[i][j] = _matrix[i][j] - t[i][j];
    return ret;
  }
  matrix operator+=(const matrix& t) const {
    if (col != t.col && row != t.row) return matrix(0, 0);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        _matrix[i][j] += t[i][j];
    return (*this);
  }
  matrix operator-=(const matrix& t) const {
    if (col != t.col && row != t.row) return matrix(0, 0);
    for (int i = 0; i < row; i++)
      for (int j = 0; j < col; j++)
        _matrix[i][j] -= t[i][j];
    return (*this);
  }
  matrix operator*=(const matrix& t) const {
    (*this) = (*this) * t;
    return (*this);
  }
};
}
#endif  // _MATRIX_HPP_
