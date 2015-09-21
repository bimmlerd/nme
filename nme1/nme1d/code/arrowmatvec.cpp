#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

template <class Vector> Vector arrowmatvec(const Vector & d, const Vector & a, const Vector & x);

int main() {
    Eigen::Vector4d d(5,6,7,8), a(1,2,3,4), x(1,1,1,1);
    Eigen::Vector4d r = arrowmatvec(d,a,x);
    std::cout << r;
    return 0;
}


template <class Vector>
Vector arrowmatvec(const Vector & d, const Vector & a, const Vector & x) {
    int d_s = d.size();
    if (d.size() != a.size()) {
        std::cerr << "size mismatch";
        throw 1;
    }
    MatrixXd A(d_s, d_s);
    A.rightCols(1) = a;
    A.bottomRows(1) = a.transpose();
    A.diagonal() = d;
    return A*A*x;
}

