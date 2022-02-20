#include "hw1.h"


Matrix algebra::zeros(size_t n , size_t m)
{    // we creating a 1*m vector with zero initialization and we put them in each n row, so finally we have a n*m matrix
     if( (m != 0) && (n != 0) )
     {
     Matrix matrix_1 ( n , std::vector<double>(m, 0));
     return matrix_1;
     }
     else
     {    throw std::invalid_argument( "Caution: dimention of matrix can not be zero" );  }
        
} 
Matrix algebra::ones(size_t n, size_t m)
{    
     if( (m != 0) && (n != 0) )
     {
     Matrix matrix_2 ( n , std::vector<double>(m,1));
     return matrix_2;
     }
     else
     {
          throw std::invalid_argument( "Caution: dimention of matrix can not be zero" );
     }
}
Matrix algebra::random(size_t n, size_t m, double min, double max)
{    if( min <= max )
     {
     std::random_device ran_dev ;
     std::uniform_real_distribution<double> dist(min,max);
     Matrix matrix_3(n , std::vector<double>(m, dist(ran_dev)));
     return matrix_3;
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
     //we are Creating a matrix of zeros with same dimention of input matrix 
    Matrix result { algebra::zeros(matrix.size(), matrix[0].size()) };
    //we are multiplying each element of the matrix by the constant with 2 for loop
    for (size_t i {}; i < matrix.size(); i++)
    {
        for (size_t j {}; j < matrix[i].size(); j++) {
            result[i][j] = matrix[i][j] * c ;
        }
    }
    // Returning the result
    return result;
}

Matrix algebra::multiply(const Matrix& matrix1, const Matrix& matrix2)
{    
     if( matrix1.empty() && matrix2.empty() )
     {
          return Matrix{};
     }

     if( matrix1[0].size() != matrix2.size())
     {
          throw std::invalid_argument( "Caution: matrices with wrong dimensions cannot be multiplied" );
     }

     Matrix temp { algebra::zeros(matrix1.size() ,matrix2[0].size()) };
     
     for (size_t i{} ; i < temp.size() ; i++)
          for(size_t j{} ; j < temp[i].size() ; j++) 
               for(size_t k{} ; k < matrix1[0].size() ; k++)
                    temp[i][j] += matrix1[i][k] * matrix2[k][j] ;

     return temp;
     
}


Matrix algebra::sum(const Matrix& matrix, double c)

{    
     if(  matrix.empty() )
          return Matrix{};

     Matrix result { algebra::zeros(matrix.size() ,matrix[0].size()) };
     for(size_t i{} ; i < matrix.size() ; i++)
          for(size_t j{} ; j < matrix[0].size() ; j++)
               result[i][j] = matrix[i][j] + c ;

     return result;
}
Matrix algebra::sum(const Matrix& matrix1, const Matrix& matrix2)
{
     if( matrix1.empty() && matrix2.empty() )
     {
          return Matrix{};
     }
     if ( (matrix1.size() != matrix2.size()) || (matrix1[0].size() != matrix2[0].size()) )
     {
          throw std::invalid_argument( "Caution: matrices with wrong dimensions cannot be summed" );
     }

     Matrix result { algebra::zeros(matrix1.size() ,matrix1[0].size()) };
     for(size_t i{} ; i < matrix1.size() ; i++)
          for(size_t j{} ; j < matrix2[0].size() ; j++)
               result[i][j] = matrix1[i][j] + matrix2[i][j];

     return result ;
}
Matrix algebra::transpose(const Matrix& matrix)
{
     if( matrix.empty() )
     {
          return Matrix{};
     }

     Matrix result { algebra::zeros(matrix[0].size() ,matrix.size()) };
     for(size_t i{} ; i < matrix.size() ; i++)
          for(size_t j{} ; j < matrix[0].size() ; j++)
               result[j][i] = matrix[i][j];

     return result;
}
Matrix algebra::minor(const Matrix& matrix, size_t n, size_t m)
{    
     Matrix result {matrix};
     result.erase(result.begin() + n);
     result = algebra::transpose(result);
     result.erase(result.begin() + m);
     result = algebra::transpose(result);
     return result;
}




double algebra::determinant(const Matrix& matrix)
{    
     if( matrix.empty() )
     {
          return 1;
     }

     if( matrix.size() != matrix[0].size())
     {
          throw std::logic_error( "Caution: non-square matrices have no determinant" );
     }
     
     Matrix temp {matrix};
     double det{};
     if( temp.size() == 1)
     {
          return temp[0][0];
     }
     for(size_t i{} ; i < matrix.size() ; i++ )
     {
          temp = algebra::minor(matrix,i,0);
          det += pow(-1,i) * matrix[i][0] * algebra::determinant(temp);
     }

return det;
}





Matrix algebra::inverse(const Matrix& matrix)
{
     if( matrix.empty() )
     {
          return Matrix{};
     }

     if( matrix.size() != matrix[0].size())
     {
          throw std::logic_error( "Caution: non-square matrices have no inverse" );
     }

     double main_det {algebra::determinant(matrix)};
     if( main_det == 0 )
     {
          throw std::logic_error( "Caution: singular matrices have no inverse" );
     }
     
     Matrix temp1 { algebra::zeros(matrix.size() -1,matrix[0].size() - 1) };
     Matrix result { algebra::zeros(matrix.size() ,matrix[0].size() ) };

     for (size_t i{} ; i < matrix.size() ; i++)
          for(size_t j{} ; j < matrix[0].size() ; j++)
               {
                    temp1 = algebra::minor(matrix,i,j);
                    double det = algebra::determinant(temp1); //we are creating adjoint matrix with calculating determinant of minors
                    result[i][j] = pow(-1 , i+j) * det ;
               }
     
     result = algebra::transpose(result);
     return algebra::multiply(result , (1/main_det)) ;
    
}




Matrix algebra::concatenate(const Matrix& matrix1, const Matrix& matrix2 , int axis)
{
    
     Matrix concatenated_matrix_row {matrix1};
     Matrix concatenated_matrix_column {algebra::transpose(matrix1)};
     if( axis == 0 )
     {
          if( (matrix1[0].size() != matrix2[0].size()) )
          {
          throw std::logic_error( "Caution: matrices with wrong dimensions cannot be concatenated" );
          }

          for(size_t i{} ; i < matrix2.size() ; i++)
               concatenated_matrix_row.push_back(matrix2[i]);
          
          return concatenated_matrix_row ;
     }

     else if( axis == 1 )
     {
          if( (matrix1.size() != matrix2.size()) )
          {
          throw std::logic_error( "Caution: matrices with wrong dimensions cannot be concatenated" );
          }
          for(size_t i{} ; i < matrix2[0].size() ; i++)
               concatenated_matrix_column.push_back(algebra::transpose(matrix2)[i]); // first i transpose the whole matrix and then i choose rows 1 by 1
          return algebra::transpose(concatenated_matrix_column);
          
     }
     else
     {
          return Matrix {};
     }

}

Matrix algebra::ero_swap(const Matrix& matrix, size_t r1, size_t r2)
{    
     if( matrix.empty() )
     {
          return Matrix{};
     }

     if( r1 > matrix.size() || r2 > matrix.size() || r1 <= 0  || r2 <= 0)
     {
          throw std::logic_error( "Caution: r1 or r2 inputs are out of range" );
     }
     Matrix swaped_matrix { matrix } ;
     swaped_matrix[r2].swap(swaped_matrix[r1]);
     return swaped_matrix ;
}

Matrix algebra::ero_multiply(const Matrix& matrix, size_t r, double c)
{
     if( matrix.empty() )
     {
          return Matrix{};
     }

     Matrix multipied_matrix { matrix } ;
     Matrix temp {algebra::multiply(matrix , c)} ;

     for(size_t i{} ; i < matrix.size() ; i++)
          if(i == r)
          {
               multipied_matrix[r] = temp[r];
          }
return multipied_matrix;

}

Matrix algebra::ero_sum(const Matrix& matrix, size_t r1, double c, size_t r2)
{
     if( matrix.empty() )
     {
          return Matrix{};
     }

     Matrix sumed_matrix { matrix } ;
     Matrix temp {algebra::multiply(matrix , c)} ;

     for(size_t i{} ; i < matrix.size() ; i++)
          if(i == r2)
          {
               temp = algebra::sum(sumed_matrix , temp);
               sumed_matrix[r2] = temp[r2] ;
               return sumed_matrix;
          }
          else{}

return Matrix{};
}

Matrix upper_triangular(const Matrix& matrix)
{
     

}
