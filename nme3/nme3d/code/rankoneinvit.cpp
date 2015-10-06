#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

template <class Vector>
double rankoneinvit(Vector d, double tol) {
    Vector ev = d;
    double lmin = 0;
    double lnew = d.cwiseAbs().minCoeff();

    while (fabs(lnew-lmin) > tol * lmin) {
        lmin = lnew;
        MatrixXd M = d.asDiagonal();
        M = M + ev * ev.transpose();
        ev = M.colPivHouseholderQr().solve(ev);
        ev.noalias() = ev / ev.norm();
        lnew = ev.transpose() * M * ev;
    }

    return lnew;
}

template <class Vector>
double rankoneinvit(Vector d) {
    return rankoneinvit(d, 1e-6);
}

int main() {
    VectorXd a(3);
    a << 1,2,3;
    std::cout << rankoneinvit(a) << std::endl;
    return 0;
}