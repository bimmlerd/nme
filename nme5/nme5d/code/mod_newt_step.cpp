#include <iostream>
#include <Eigen/Dense>
#include <vector>

using namespace std;

template <typename arg, class func, class jac>
void mod_newt_step(const arg & x, arg & x_next, func&& f, jac&& df) {
    arg y = x + (1 / df(x)) * f(x);
    x_next = y - (1 / df(x)) * f(y);
};

void mod_newt_ord() {
    double x, x_next, p;
    const double x_star = 0.123624065869274, tol = 2e-16;
    int max_iter = 100;
    double err[3] = {0,0,0};
    vector<double> ps;


    auto f = [](double d){
        return atan(d) - 0.123;
    };
    auto df = [](double d){
        return (1/(pow(d, 2) + 1));
    };

    x_next = 5; // Initial guess

    for (int i = 0; i < max_iter; i++) {
        err[i % 3] = x_next;

        if (i > 2) {
            p = (log(err[2]) - log(err[1]))/(log(err[1]) / log(err[0]));
            ps.push_back(p);
        }

        x = x_next;
        mod_newt_step(x, x_next, f, df);

        if (abs(x - x_next) < tol || abs(x - x_next) < abs(x_next) * tol) {
            std::cout << "Abort condition reached" << std::endl;
            break;
        }
    }

    std::cout << "x_next: " << x_next << std::endl;
    for (std::vector<double>::iterator it = ps.begin(); it != ps.end(); ++it) {
        std::cout << "p: " << *it << std::endl;
    }

}

int main() {
    mod_newt_ord();
    return 0;
}