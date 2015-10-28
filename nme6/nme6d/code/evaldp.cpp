#include <iostream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

template<typename CoeffVec>
pair<double, double> evaldp(const CoeffVec &c, double x) {
    pair<double, double> res = pair<double, double>();
    int degree = c.size() - 1;
    double b = c(0);
    double b_prime = c(0) * degree;
    for (int i = 1; i < degree; i++) {
        b = c(i) + b * x;
        b_prime = c(i) * (degree - i) + b_prime * x;
    }
    res.first = c(degree) + b * x;
    res.second = b_prime;
    return res;
};

template<typename CoeffVec>
pair<double, double> evaldp_naive(const CoeffVec &c, double x) {
    pair<double, double> res = pair<double, double>();
    int degree = c.size() - 1;

    CoeffVec dc = c;
    // "derive" c
    for (int i = 0; i <= degree; i++) {
        // we intentionally stick a wrong 0 at the end to make the loop below easy
        dc(i) = dc(i) * (degree - i);
    }

    res.first = 0;
    res.second = 0;
    for (int j = 0, i = degree; i >= 0; i--, j++) {
        res.first += pow(x, i) * c(j);
        res.second += pow(x, i-1) * dc(j);
    }

    return res;
}

int main() {
    VectorXd coeffs(3);
    coeffs << 1,2,1;
    double x = 2;
    auto res = evaldp(coeffs, x);
    auto res_check = evaldp_naive(coeffs, x);
    //assert(res == res_check);

    cout << "For coefficients " << endl << coeffs << endl << "we have p(" << x << ") = " << res.first << " and p'(" << x << ") = "
            << res.second << endl;
    return 0;
}
