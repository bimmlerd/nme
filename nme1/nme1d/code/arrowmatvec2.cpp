#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;

template <class Vector>
Vector arrowmatvec2(const Vector & d, const Vector & a, const Vector & x) {
    size_t n = d.size();
    if (n != a.size()) {
        std::cerr << "size mismatch";
        throw 1;
    }
    a.tail(1) = 0;
    Vector yy = d.array() * x.array() + x.tail(1) * a;
    yy.tail(1) += a.rows(n-1).dot(x.rows(n-1));
    Vector y = d.array() * yy.array() + yy.tail(1) * a;
    y.tail(1) += a.rows(n-1).dot(yy.rows(n-1));
}

int main() {
    Eigen::Vector4d d(5,6,7,8), a(1,2,3,4), x(1,1,1,1);
    Eigen::Vector4d r = arrowmatvec2(d,a,x);
    std::cout << r;
    return 0;
}