#ifndef __PROGTEST__
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
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
  public:
    InvalidDateException ( )
      : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
  return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
  public:
    CDate (int year, int month,int day)
    {
      Ctime.tm_year = year- 1900 ;
      Ctime.tm_mon = month -1 ;
      Ctime.tm_mday = day ;
      struct tm  Ctime_copy = Ctime;
      time_t a = mktime(&Ctime); 
      if (Ctime.tm_year != Ctime_copy.tm_year || Ctime.tm_mon != Ctime_copy.tm_mon || Ctime.tm_mday != Ctime_copy.tm_mday || a == -1){
        throw InvalidDateException();
      }
    }
    // ---------------------------- MATH OPERATORS -----------------------------------------------------------------------------------------
    CDate operator + (int operand) const{
      CDate x (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);
      x.Ctime.tm_mday += operand;
      mktime(&x.Ctime);
      return (x);
    }

    CDate operator - (int operand) const{
      CDate x (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);
      x.Ctime.tm_mday -= operand;
      mktime(&x.Ctime);
      return (x);
    }

    CDate operator ++ (){
      Ctime.tm_mday++;
      mktime(&Ctime);
      return (*this);
    }

    CDate operator -- (){
      Ctime.tm_mday--;
      mktime(&Ctime);
      return (*this);
    }

    CDate operator++(int){
      CDate x (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);
      Ctime.tm_mday++;
      mktime(&Ctime);
      return (x);
    }

    CDate operator--(int) {
      CDate x (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);
      Ctime.tm_mday--;
      mktime(&Ctime);
      return (x);
    }


    int operator - (const CDate & Next_date) const{
      CDate usable_current (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);   
      CDate Next_date_usable (Next_date.Ctime.tm_year+ 1900, Next_date.Ctime.tm_mon+1, Next_date.Ctime.tm_mday);   
      int a = (difftime(mktime(&usable_current.Ctime), mktime(&Next_date_usable.Ctime)));
      if (a < 0){
        a = -a;
      } 
      a = a / 86400;
      //cout << a << endl;
      return a;
    }
    // ---------------------------- booLEAN OPERATORS --------------------------------------------------------------------------------------
    bool operator < (const CDate & Next_date) const{
      CDate usable_current (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);   
      CDate Next_date_usable (Next_date.Ctime.tm_year+ 1900, Next_date.Ctime.tm_mon+1, Next_date.Ctime.tm_mday);   
      time_t a = mktime(&usable_current.Ctime);
      time_t b =mktime(&Next_date_usable.Ctime);
      if (a < b){
        return true;
      }
      return false;
    }

    bool operator <= (const CDate & Next_date) const{
      CDate usable_current (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);   
      CDate Next_date_usable (Next_date.Ctime.tm_year+ 1900, Next_date.Ctime.tm_mon+1, Next_date.Ctime.tm_mday);   
      time_t a = mktime(&usable_current.Ctime);
      time_t b =mktime(&Next_date_usable.Ctime);
      if (a <= b){
        return true;
      }
      return false;
    }

    bool operator > (const CDate & Next_date) const{
      CDate usable_current (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);   
      CDate Next_date_usable (Next_date.Ctime.tm_year+ 1900, Next_date.Ctime.tm_mon+1, Next_date.Ctime.tm_mday);   
      time_t a = mktime(&usable_current.Ctime);
      time_t b =mktime(&Next_date_usable.Ctime);
      if (a > b){
        return true;
      }
      return false;
    }

    bool operator >= (const CDate & Next_date) const{
      CDate usable_current (Ctime.tm_year+ 1900, Ctime.tm_mon+1, Ctime.tm_mday);   
      CDate Next_date_usable (Next_date.Ctime.tm_year+ 1900, Next_date.Ctime.tm_mon+1, Next_date.Ctime.tm_mday);   
      time_t a = mktime(&usable_current.Ctime);
      time_t b =mktime(&Next_date_usable.Ctime);
      if (a >= b){
        return true;
      }
      return false;
    }

    bool operator == (const CDate & Next_date) const{
      if (Next_date.Ctime.tm_year == Ctime.tm_year && Next_date.Ctime.tm_mon == Ctime.tm_mon && Next_date.Ctime.tm_year == Ctime.tm_year){
        return true;
      }
      return false;
    }
    
    bool operator != (const CDate & Next_date) const{
      if (Next_date.Ctime.tm_year == Ctime.tm_year && Next_date.Ctime.tm_mon == Ctime.tm_mon && Next_date.Ctime.tm_year == Ctime.tm_year){
        return false;
      }
      return true;
    }
    // ---------------------------- STREAM OPERATORS ----------------------------------------------------------------------------------------
    friend ostream &operator<<(ostream &oStream, const CDate &date){
       return oStream << (date.Ctime.tm_year + 1900) << "-" << setfill('0') << setw(2) << (date.Ctime.tm_mon + 1) << "-" << setw(2) << date.Ctime.tm_mday << flush;

    }  

    friend istream &operator>>(istream &InStream,  CDate &datum){
      tm temp = {1};
      temp.tm_year = 0;
      temp.tm_mon = 20;
      temp.tm_mday = 132;
      InStream >> get_time(&temp, "%Y-%m-%d") ;
      struct tm  temp_copy = temp;
      time_t a = mktime(&temp); 
      if (temp.tm_year != temp_copy.tm_year || temp.tm_mon != temp_copy.tm_mon || temp.tm_mday != temp_copy.tm_mday || a == -1 || InStream.fail()){
        InStream.setstate(ios::failbit);
      }
      else{
      datum.Ctime = temp;
      }
      return InStream;
    }

  private:
  tm Ctime = {1};
  time_t T_CTime;
};

//=================================================================================================
#ifndef __PROGTEST__
int main ( void )
{ 


  ostringstream oss;
  istringstream iss;
  //CDate u ( 2000, 13, 2 );
  CDate a ( 2000, 1, 2 );
  CDate b ( 2010, 2, 3 );
  CDate c ( 2004, 2, 10 );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2000-01-02" );
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2010-02-03" );
  oss . str ("");
  oss << c;
  assert ( oss . str () == "2004-02-10" );
  a = a + 1500;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2004-02-10" );
  b = b - 2000;
  oss . str ("");
  oss << b;
  assert ( oss . str () == "2004-08-13" );
  assert ( b - a == 185 );
  assert ( ( b == a ) == false );
  assert ( ( b != a ) == true );
  assert ( ( b <= a ) == false );
  assert ( ( b < a ) == false );
  assert ( ( b >= a ) == true );
  assert ( ( b > a ) == true );
  assert ( ( c == a ) == true );
  assert ( ( c != a ) == false );
  assert ( ( c <= a ) == true );
  assert ( ( c < a ) == false );
  assert ( ( c >= a ) == true );
  assert ( ( c > a ) == false );
  a = ++c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-11" );
  a = --c;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-10" );
  a = c++;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-10 2004-02-11" );
  a = c--;
  oss . str ( "" );
  oss << a << " " << c;
  assert ( oss . str () == "2004-02-11 2004-02-10" );
  iss . clear ();
  iss . str ( "2015-09-03" );
  assert ( ( iss >> a ) );
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-09-03" );
  a = a + 70;
  oss . str ("");
  oss << a;
  assert ( oss . str () == "2015-11-12" );

  CDate d ( 2000, 1, 1 );
  try
  {
    CDate e ( 2000, 32, 1 );
    assert ( "No exception thrown!" == nullptr );
  }
  catch ( ... )
  {
  }
  iss . clear ();
  iss . str ( "2000-12-33" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-11-31" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-01-01" );
  iss . clear ();
  iss . str ( "2000-02-29" );
  assert ( ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );
  iss . clear ();
  iss . str ( "2001-02-29" );
  assert ( ! ( iss >> d ) );
  oss . str ("");
  oss << d;
  assert ( oss . str () == "2000-02-29" );

  //-----------------------------------------------------------------------------
  // bonus test examples
  //-----------------------------------------------------------------------------
  CDate f ( 2000, 5, 12 );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  oss . str ("");
  oss << date_format ( "%Y/%m/%d" ) << f;
  assert ( oss . str () == "2000/05/12" );
  oss . str ("");
  oss << date_format ( "%d.%m.%Y" ) << f;
  assert ( oss . str () == "12.05.2000" );
  oss . str ("");
  oss << date_format ( "%m/%d/%Y" ) << f;
  assert ( oss . str () == "05/12/2000" );
  oss . str ("");
  oss << date_format ( "%Y%m%d" ) << f;
  assert ( oss . str () == "20000512" );
  oss . str ("");
  oss << date_format ( "hello kitty" ) << f;
  assert ( oss . str () == "hello kitty" );
  oss . str ("");
  oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
  assert ( oss . str () == "121212121212050505200020002000%%%%%" );
  oss . str ("");
  oss << date_format ( "%Y-%m-%d" ) << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-1" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-1-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-001-01" );
  assert ( ! ( iss >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2000-05-12" );
  iss . clear ();
  iss . str ( "2001-01-02" );
  assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2001-01-02" );
  iss . clear ();
  iss . str ( "05.06.2003" );
  assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2003-06-05" );
  iss . clear ();
  iss . str ( "07/08/2004" );
  assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2004-07-08" );
  iss . clear ();
  iss . str ( "2002*03*04" );
  assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2002-03-04" );
  iss . clear ();
  iss . str ( "C++09format10PA22006rulez" );
  assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2006-09-10" );
  iss . clear ();
  iss . str ( "%12%13%2010%" );
  assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
  oss . str ("");
  oss << f;
  assert ( oss . str () == "2010-12-13" );

  CDate g ( 2000, 6, 8 );
  iss . clear ();
  iss . str ( "2001-11-33" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "29.02.2003" );
  assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "14/02/2004" );
  assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2002-03" );
  assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "hello kitty" );
  assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "2005-07-12-07" );
  assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-06-08" );
  iss . clear ();
  iss . str ( "20000101" );
  assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
  oss . str ("");
  oss << g;
  assert ( oss . str () == "2000-01-01" );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
