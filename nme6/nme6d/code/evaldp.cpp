#include <iostream>
#include <Eigen/Dense>
#include <vector>

#include "timer.h"

using namespace std;
using namespace Eigen;

/*template<typename CoeffVec>
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
};*/

template<typename CoeffVec>
std::pair<double, double> evaldp(const CoeffVec &c, double x) {
    // runs in O(n)
    int n = c.rows();
    std::pair<double, double> result(0.0, 0.0);
    double p = c(0);
    double pd = c(0) * (n - 1);
    for (int i = 1; i < (n - 1); i++) {
        p = x * p + c(i);
        pd = x * pd + c(i) * (n - (i + 1));
    }
    p = x * p + c(n - 1);
    result.first = p;
    result.second = pd;
    return result;
}

template<typename CoeffVec>
pair<double, double> evaldp_naive(const CoeffVec &c, double x) {
    pair<double, double> res = pair<double, double>();
    long degree = c.size() - 1;

    CoeffVec dc = c;
    // "derive" c
    for (long i = 0; i <= degree; i++) {
        // we intentionally stick a wrong 0 at the end to make the loop below easy
        dc(i) = dc(i) * (degree - i);
    }

    res.first = 0;
    res.second = 0;
    for (long j = 0, i = degree; i >= 0; i--, j++) {
        res.first += pow(x, i) * c(j);
        res.second += pow(x, i-1) * dc(j);
    }

    return res;
}

int main() {
    timer<> tm_eff, tm_naive;

    for (int i = 1; i <= 20; i++) {
        long degree = pow(2, i) - 1;
        tm_eff.reset();
        tm_naive.reset();

        for (int j = 0; j < 3; j++) {

            VectorXd coeffs = VectorXd::Random(degree + 1);
            double x = 1;

            tm_eff.start();
            auto res = evaldp(coeffs, x);
            tm_eff.stop();

            tm_naive.start();
            auto res_check = evaldp_naive(coeffs, x);
            tm_naive.stop();

            assert(abs(res.first - res_check.first) < 2e-20);
            assert(abs(res.second - res_check.second) < 2e-20);
        }

        cout << "Degree " << degree << endl;
        cout << "Time eff:\t" << tm_eff.avg().count() / 1000 << "ns" << endl;
        cout << "Time naive:\t" << tm_naive.avg().count() / 1000 << "ns" << endl << endl;
    }

    return 0;
}
