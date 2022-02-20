#include "hw1.h"


Matrix algebra::zeros(size_t n , size_t m)
{
     Matrix sajad1 ( n , std::vector<double>(m, 0));
     return sajad1;
        
} 
Matrix algebra::ones(size_t n, size_t m)
{
     Matrix sajad2 ( n , std::vector<double>(m,1));
     return sajad2;
}
Matrix algebra::random(size_t n, size_t m, double min, double max)
{    if( min <= max )
     {
     std::random_device ran_dev ;
     std::uniform_real_distribution<double> dist(min,max);
     Matrix sajad3(n , std::vector<double>(m, dist(ran_dev)));
     return sajad3;
     }
     else
     {
          throw std::invalid_argument( "Caution: min cannot be greater than max" );
     }
}
void algebra::show(const Matrix& matrix)
{

for (size_t i {}; i < matrix.size(); i++) {
        for (size_t j {}; j < matrix[i].size(); j++) {
            std::cout << std::setw(15) << matrix[i][j];
        }
        std::cout << std::endl;
    }
}
Matrix algebra::multiply(const Matrix& matrix, double c)
{
     Matrix sajad = algebra::zeros ( matrix.size() , matrix[0].size() );
     for(size_t i{} ; i < sajad.size()  ; i++)
     {
          for(size_t j{} ; j < sajad[i].size()  ; j++)
          {
               sajad[i][j] = sajad[i][j] * c ;
          }
     }
     return sajad;
}


