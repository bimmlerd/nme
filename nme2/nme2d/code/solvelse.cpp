#include <Eigen/Dense>
#include <iostream>

using namespace Eigen;

template <class Matrix, class Vector>
void solvelse(const Matrix & R, const Vector & v, const Vector & u, const Vector & b, Vector & x) {
    typedef typename Matrix::Scalar Scalar;
    long n = R.rows();
    Vector z(n);

    if (v.size() != n || u.size() != n || x.size() != n + 1 || b.size() != n + 1) {
        std::cerr << "Dimensions aren't right." << std::endl;
        throw (-1);
    }

    Matrix R_i = R.inverse();
    Vector b_n = b.segment(0,n);
    Scalar chi = b(n) + (Scalar) (u.transpose() * R_i * b_n) / (u.transpose() * R_i * v);
    z = R_i * (b_n + (chi * v));
    x << z, chi;
};

int main() {
    VectorXd u(3);
    VectorXd v(3);
    VectorXd b(4);
    VectorXd x(4);
    MatrixXd R(3, 3);
    MatrixXd X(3, 3);

    R << 1, 2, 3,
        0, 2, 3,
        0, 0, 3;
    u << 1,2,3;
    v << 4,5,6;
    b << 3,3,3,3;

    solvelse(R, v, u, b, x);
    std::cout << x << std::endl;
    return 0;
}