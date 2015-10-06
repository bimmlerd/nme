#include <iostream>
#include <vector>
#include <algorithm>

#include <Eigen/Dense>
#include <Eigen/Sparse>

using namespace Eigen;
using namespace std;

template <class scalar>
struct TripletMatrix {
    vector<Triplet<scalar, size_t>> triplets;

    size_t rows, cols;

public:
    TripletMatrix() {
        triplets = {};
        rows = 0;
        cols = 0;
    }

    TripletMatrix(size_t na, size_t ma) {
        triplets = {};
        rows = na;
        cols = ma;
    }

    size_t getRows() const {
        return rows;
    }

    size_t getCols() const {
        return cols;
    }

    vector<Triplet<scalar, size_t>> getTriplets() const {
        return triplets;
    }

    void insert(size_t i, size_t j, scalar v) {
        rows = max(rows, i);
        cols = max(cols, j);
        triplets.push_back(Triplet<scalar, size_t>(i, j, v));
    }

    Matrix<scalar, -1, -1> densify() const {
        Matrix<scalar, -1, -1> M = Matrix<scalar, -1, -1>::Zero(rows, cols);
        for (typename vector<const Triplet<scalar, size_t>>::iterator it = triplets.begin(); it != triplets.end(); ++it) {
            M(it->row(), it->col()) += it->value();
        }
        return M;
    }
};

// Uncomment if you want to use this structure for CRSMatrix
 template <class scalar>
 struct ColValPair {
     size_t c;
     scalar v;

 public:
     ColValPair(size_t col, scalar val) {
         c = col; v = val;
     }

     size_t col() const {
         return c;
     }

     scalar val() const {
         return v;
     }
 };

template <class scalar>
struct CRSMatrix {
public:
    vector<ColValPair<scalar>> pairs;
    vector<int> rowPtr;
    size_t rows, cols;

    CRSMatrix() {
        rows = 0;
        cols = 0;
        pairs = {};
        rowPtr = {0};
    }

    CRSMatrix(size_t r, size_t c):
            rowPtr(r+1) {
        rows = r;
        cols = c;
        pairs = {};
    }

    Matrix<scalar, -1, -1> densify() const {
        Matrix<scalar, -1, -1> M = Matrix<scalar, -1, -1>::Zero(rows, cols);
        for (typename vector<ColValPair<scalar>>::size_type i = 1; i < rowPtr.size(); i++) {
            int count = rowPtr[i] - rowPtr[i-1];
            if (count <= 0) {
                cout << "ARGH, I think that's a whole row of zeros there?" << endl;
            }
            for (int j = rowPtr[i-1]; j < rowPtr[i]; j++) {
                ColValPair<scalar> cvp = pairs[j];
                M(i-1, cvp.col()) = cvp.val();
            }
        }
        return M;
    }
};

template <class scalar>
void tripletToCRS(const TripletMatrix<scalar> & T, CRSMatrix<scalar> & C) {
    vector<Triplet<scalar, size_t>> triplets = T.getTriplets();
    sort(triplets.begin(), triplets.end(),
    [](const Triplet<scalar, size_t> & a, const Triplet<scalar, size_t> & b) -> bool
    {
        if (a.row() < b.row()) {
            return true;
        } else if (a.row() > b.row()) {
            return false;
        } else {
            return a.col() < b.col();
        }
    });
    C = CRSMatrix<scalar>(T.getRows(), T.getCols());
    for (typename vector<const Triplet<scalar, size_t>>::iterator it = triplets.begin(); it != triplets.end(); ++it) {
        ColValPair<scalar> pair = ColValPair<scalar>(it->col(), it->value());
        cout << "pushing pair " << pair << " and incrementing " << C.rowPtr[it->row() + 1] << " at " << it->row()+1 << endl;
        C.pairs.push_back(pair);
        C.rowPtr[it->row() + 1] += 1;
    }
    cout << "[" << C.rowPtr[0];
    for (int i = 1; i < C.rowPtr.size(); i++) {
        C.rowPtr[i] += C.rowPtr[i-1];
        cout << " " << C.rowPtr[i];
    }
    cout << "]" << endl;

}

//! \brief overload of operator << for output of Triplet Matrix (debug).
//! WARNING: uses densify() so there may be a lot of fill-in
//! this allows something like std::cout << S
//! \param o standard output stream
//! \param S matrix in Triplet matrix format
//! \return a ostream o, s.t. you can write o << A << B;
std::ostream & operator<<(std::ostream & o, const TripletMatrix<double> & S) {
    return o << S.densify();
}

//! \brief overload of operator << for output of CRS Matrix (debug).
//! WARNING: uses densify() so there may be a lot of fill-in
//! this allows something like std::cout << S
//! \param o standard output stream
//! \param S matrix in CRS matrix format
//! \return a ostream o, s.t. you can write o << A << B;
std::ostream & operator<<(std::ostream & o, const CRSMatrix<double> & S) {
    return o << S.densify();
}

//! \brief overload of operator << for output of ColValPair (debug).
//! this allows something like std::cout << S
//! \param o standard output stream
//! \param S matrix in ColValPair format
//! \return a ostream o, s.t. you can write o << A << B;
std::ostream & operator<<(std::ostream & o, const ColValPair<double> & S) {
    return o << "(" << S.col() << ", " << S.val() << ")";
}

int main() {
    //// Correctness test
    srand(13); // TODO this is pretttty hacky, but this gives me a seed which doesn't contain rows full of zeros.
    size_t nrows = 7, ncols = 5, ntriplets = 9;

    MatrixXd R (nrows, ncols);
    TripletMatrix<double> T (nrows, ncols);
    CRSMatrix<double> C;

    for(auto i = 0u; i < ntriplets; ++i) {
        size_t ii = rand() % nrows, jj = rand() % ncols;
        double v = rand() % 1000;
        R(ii, jj) = v;
        T.insert(ii, jj, v);
    }
    
    cout << "***Test conversion with random matrices***" << endl;
    tripletToCRS(T, C);
    cout << "--> Frobenius norm of T - C: " << (T.densify()-C.densify()).norm() << endl;
    cout << "R = " << std::endl << R << std::endl;
    cout << "T = " << std::endl << T << std::endl;
    cout << "C = " << std::endl << C << std::endl;
}
