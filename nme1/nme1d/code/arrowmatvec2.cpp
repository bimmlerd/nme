#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

template <class Vector>
Vector arrowmatvec2(const Vector & d, const Vector & a, const Vector & x) {
    long n = d.size();
    if (n != a.size()) {
        std::cerr << "size mismatch";
        throw 1;
    }
    Vector a_ = a;
    a_(n-1) = 0;
    Vector yy = (d.array() * x.array()).matrix() + x(n-1) * a_;
    yy(n-1) += a_.topRows(n).dot(x.topRows(n));
    Vector y = (d.array() * yy.array()).matrix() + yy(n-1) * a_;
    y(n-1) += a_.topRows(n).dot(yy.topRows(n));
    return y;
}

int main() {
    Eigen::Vector4d d(5,6,7,8), a(1,2,3,4), x(1,1,1,1);
    Eigen::Vector4d r = arrowmatvec2(d,a,x);
    std::cout << r;
    return 0;
}