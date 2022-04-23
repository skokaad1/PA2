#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;

class CArray
 {
   public:
    CArray ( int len )
     {
       m_D = new int[ m_L = len ];
       for ( int i = 0; i < m_L; i ++ ) m_D[i] = 0;
     }  
    CArray & operator = ( const CArray & src )
     {
       delete [] m_D;  
       m_D = new int[ m_L = src . m_L ];
       for ( int i = 0; i < m_L; i ++ ) m_D[i] = src . m_D[i];
       return *this;
     } 
    ~CArray ( void ) { delete [] m_D; }
    int & operator [] ( int i ) { return m_D[i]; }
   private:   
    int * m_D;
    int   m_L;
 };
     
int main ( void )
 {
   CArray a(39), b(26);

   b = a;
   a[26] = 23;   
   cout << b[26];
   return 0;
 }
