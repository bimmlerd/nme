#include<vector>
#include<cassert>
#include<iostream>
#include<Eigen/Sparse>
#include<Eigen/Dense>

class NatCSI {
public:
    using SM = Eigen::SparseMatrix<double>; 
    //! \brief Build the cubic spline interpolant with natural boundaries
    //! Setup the data structures you need.
    //! Pre-compute the coefficients of the spline (solve system)
    //! \param[in] t, nodes of the grid (for pairs (t_i, y_i)) (sorted!)
    //! \param[in] y, values y_i at t_i (for pairs (t_i, y_i))
    NatCSI(const std::vector<double> & t, const std::vector<double> & y)
    : t(t), y(y), h(t.size() - 1), c(t.size()), m(t.size()) {
        assert(y.size() == m && "Size mismatch");

        for (int i = 0; i < m - 1; ++i) {
            h(i) = t[i + 1] - t[i];
            assert(h(i) > 0 && "nodes must be sorted");
        }

        SM A(m, m);
        Eigen::VectorXd b(m);

        A.insert(0,0) = 2.0 / h(0);
        A.insert(0,1) = 1.0 / h(0);

        A.insert(m - 1, m - 2) = 1 / h(m - 2);
        A.insert(m - 1, m - 1) = 2 / h(m - 2);

        double b_precomputation = ((y[1] - y[0]) / (h(0) * h(0)));
        b(0) = 3 * b_precomputation;
        b(m-1) = 3 * ((y[m - 1] - y[m - 2]) / (h(m - 2) * h(m - 2)));
        double b_temp = 0;
        double b_old = 1 / h(0);
        double b_new;
        for (int i = 1; i < m - 1; ++i) {
            // vector b
            b_temp = ((y[i + 1] - y[i]) / (h(i) * h(i)));
            b(i) = 3 * (b_precomputation + b_temp);
            b_precomputation = b_temp;

            // A
            b_new = 1.0 / h(i);
            A.insert(i, i - 1) = b_old;
            A.insert(i, i) = 2 * (b_old + b_new);
            A.insert(i, i + 1) = b_new;
            b_old = b_new;
        }

        A.makeCompressed();
        std::cout << A;
        
        Eigen::SparseLU<SM> lu;
        lu.compute(A);
        c = lu.solve(b);
    }

    double operator() (double x) const {
        // Assert that x \in (t_0, t_n)
        assert( ( t[0] <= x && x <= t[m-1] ) && "Error: x must be in (t_0, t_n)");
        
        // Find j s.t. x \in (t_j,t_j+1)
        // as with the previous sheet (PS 6), we perform an efficient binary search on the data (log. complexity)
        auto j = (std::lower_bound(t.begin(), t.end(), x) - t.begin()) - 1;
        if( j == -1 ) j++;
        
        
        // Precompute tau and evaluate spline (3.5.5)
        double tau = (x - t[j]) / h(j);
        double tau2 = tau*tau;
        double tau3 = tau2*tau;
        return y[j] *           (1. - 3. * tau2 + 2 * tau3 ) +
               y[j+1] *         (3 * tau2 - 2 * tau3 ) +
               h(j) * c(j) *    (tau - 2 * tau2 + tau3 ) +
               h(j) * c(j+1) *  (- tau2 + tau3 );
               
    }

private:
    // nodes and values, node distances and coefficients
    std::vector<double> t, y;

    Eigen::VectorXd h, c;

    int m; // number of conditions == n + 1
};

int main() {
    
    int n = 8, m = 100;
    std::vector<double> t;
    std::vector<double> y;
    t.resize(n);
    y.resize(n);
    for(int i = 0; i < n; ++i) {
        t[i] = (double) i / (n-1);
        y[i] = cos(t[i]);
    }
    
    NatCSI N(t,y);
    
    Eigen::VectorXd x = Eigen::VectorXd::LinSpaced(m, 0, 1);
    for(int i = 0; i < x.size(); ++i) {
        x(i) = N(x(i));
    }
    std::cout << x << std::endl;
}