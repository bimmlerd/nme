#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <unsupported/Eigen/KroneckerProduct>
#include <iostream>

using namespace Eigen;

SparseMatrix<double> buildC(const MatrixXd &A) {
    long n = A.rows();
    long n2 = n*n;
    SparseMatrix<double> C(n2, n2);
    SparseMatrix<double> C1(n2, n2);
    SparseMatrix<double> C2(n2, n2);

    std::vector<Triplet<double>> triplets;
    MatrixXd Id = MatrixXd::Identity(n,n);
    SparseMatrix<double> I = Id.sparseView();

    kroneckerProduct(A, I).evalTo(C1);
    kroneckerProduct(I, A).evalTo(C2);
    C = C1 + C2;

    C.makeCompressed();
    return C;
}

void solveLyapunov(const MatrixXd & A, MatrixXd & X) {
    SparseMatrix<double> C = buildC(A);
    // map identity to column vector
    long n = A.rows();
    MatrixXd I = MatrixXd::Identity(n,n);
    VectorXd b = Map<VectorXd>(I.data(), n*n);
    SparseLU<SparseMatrix<double>> solver;
    solver.compute(C);
    // solve C \ b
    VectorXd x = solver.solve(b);
    X = Map<MatrixXd>(x.data(), n, n);
}

int main() {
    MatrixXd A(5,5);
    A << 10, 2, 3, 4, 5,
        6, 20, 8, 9, 1,
        1, 2, 30, 4, 5,
        6, 7, 8, 20, 0,
        1, 2, 3, 4, 10;
    MatrixXd X(5,5);
    solveLyapunov(A, X);
    std::cout << X;
    return 0;
}