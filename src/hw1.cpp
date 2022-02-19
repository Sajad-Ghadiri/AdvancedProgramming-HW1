#include "hw1.h"

//using namespace Algebra{};
using Matrix = std::vector<std::vector<double>>;

Matrix zeros(size_t n , size_t m)
{
    Matrix sajad[n][m];
    for (int i{} ; i < n ; i++)
        for(int j{} ; j < m ; j++)
            sajad[i][j] = 0.0 ;

    return sajad ;

}
/*
int main()
{

std::cout << zeros(3,3) <<std::endl;
}*/