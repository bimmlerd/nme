#include <Eigen/Dense>
#include <iostream>
#define     N   7

//! \brief Compute an ONB of the space orthogonal to $v$
//! \param[in] v vector $ v \in \mathbb{R}^n \setminus \{ 0 \} $
//! \param[out] Z matrix $ Z \in \mathbb{R}^{n-1 \times n} $
void houserefl(const Eigen::VectorXd & v, Eigen::MatrixXd & Z)
{
    // TODO
}


int main(int argc, char ** argv) {
    // Check what houserefl does to random vector
    srand((unsigned int) time(0));
    unsigned int n = N;
    if(argc >= 2) n = std::atoi(argv[1]);
    
    Eigen::VectorXd v = Eigen::VectorXd::Random(n); // Not truly random if missing srand
    Eigen::MatrixXd Z;
    
    houserefl(v, Z);
    
    std::cout << "v = " << v << std::endl;
    std::cout << "Z = " << Z << std::endl;
}
