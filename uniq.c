#include <stdio.h>

int main ( )
{
    int size , i , j , flag = 0 ;
    printf ( "Enter the size : " ) ;
    scanf ( "%d" , & size ) ;
    int arr [ size ] ;
    printf ( "Enter the %d element of array :" , size ) ;
    for ( i = 0 ; i < size ; i ++ )
    {
        scanf ( "%d" , & arr [ i ] ) ;
    }
    for ( i = 0 ; i < size - 1 ; i ++ )
    {
        for ( j = 0 ; j < size - i ; j ++ )
        {
            if ( arr [ i ] == arr [ j + 1 ] )
            {
                flag = 1 ;
                break ;
            }
        }
    }
    flag == 1 ? printf ( "Array is not unique\n" ) : printf ( "array is unique\n" ) ;
}