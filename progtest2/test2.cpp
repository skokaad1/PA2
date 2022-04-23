#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream> 
#include <iomanip> 
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */
string To_Upper(const string  TO_UPPER){
    string tmp_str = TO_UPPER;
     transform(tmp_str.begin(), tmp_str.end(), tmp_str.begin(),[](unsigned char c){ return toupper(c); });
     return tmp_str; 
}
class CVAT{
  public:
    string inner_name;
    string inner_addr;
    string inner_taxID;
    string upper_inner_addr;
    string upper_inner_name;
    unsigned int  logged_invoices;

    CVAT(const string    & name,const string    & addr, const string    & taxID)
      :inner_name(name),
      inner_addr(addr),
      inner_taxID(taxID),
      upper_inner_addr(addr),
      upper_inner_name(name),
      logged_invoices(0)  
    {
      upper_inner_addr = To_Upper(addr);
      upper_inner_name = To_Upper(name);
    }
    void Test_Print(CVAT data){
      cout << data.inner_name << " : " << data.inner_addr << " : " << data.inner_taxID << endl;
    }
  private:
};






class CVATRegister{
  public:
    CVATRegister   ( void ){
    }
    ~CVATRegister  ( void ){
    }
    //testing
    void PrintAll(){  
      for (CVAT company: Database){
        company.Test_Print(company);
      }
    }


    //end testing
    struct Int_compare{
      inline bool operator() (unsigned int num1,unsigned int num2){
        return (num1 < num2);
      }
    };

    struct comes_before_NAME{
      inline bool operator() (const CVAT& str1,const  CVAT& str2){
        int a = str1.inner_name.compare(str2.inner_name);
        if (str1.inner_name.empty() == 1 || str2.inner_name.empty() == 1){
          if (str1.inner_name.empty() == 1 && str2.inner_name.empty() == 1){
          a = 1;
          }
          else if(str1.inner_name.empty() == 1){
          a = 1;
          }
          else{
          a = 0;
          }
        }
        if (a < 0 ){
          return 1;
        }
        else if (a == 0){
          int c = str1.inner_addr.compare(str2.inner_addr);
          if (str1.inner_addr.empty() == 1 || str2.inner_addr.empty() == 1){
            if (str1.inner_addr.empty() == 1 && str2.inner_addr.empty() == 1){
            c = 1;
            }
            else if(str1.inner_addr.empty() == 1){
            c = 1;
            }
            else{
            c = 0;
            }
          }
          if (c < 1 ){
            return 1;
          }
          else {
            return 0;
          }
        }
        else{
          return 0;
        }
      }
    };
    /*struct comes_before_ADRESS{
      inline bool operator() (const CVAT& str1,const  CVAT& str2){
        int a = str1.inner_addr.compare(str2.inner_addr);
        if (str1.inner_name.empty() == 1 || str2.inner_name.empty() == 1){
          if (str1.inner_name.empty() == 1 && str2.inner_name.empty() == 1){
          a = 1;
          }
          else if(str1.inner_name.empty() == 1){
          a = 1;
          }
          else{
          a = 0;
          }
        }
        if (a < 1 ){
          return 1;
        }
        else {
          return 0;
        }
      }
    };*/

    void SortCompanies(){
      sort(Database.begin(),Database.end(),comes_before_NAME());
    }

    bool IsUnique(const string    & name , const string    & addr , const string    & taxID){
      string tmp_addr = To_Upper(addr);
      string tmp_name = To_Upper(name);
      for (CVAT company: Database){
        if(company.inner_taxID.compare(taxID) == 0){
          return 0;
        }
        if(company.upper_inner_name.compare(tmp_name) == 0 && company.upper_inner_addr.compare(tmp_addr) == 0){
          return 0;
        }
      }
      return 1;
    }

    bool  newCompany  ( const string    & name , const string    & addr , const string    & taxID ){
      if (IsUnique(name,addr,taxID) == 0){
        return 0;
      }
      const CVAT aaa = CVAT(name, addr, taxID);
      auto it = lower_bound(begin(Database), end(Database), aaa ,comes_before_NAME() );
      Database.insert(it, aaa);
      //Database.push_back(CVAT(name, addr, taxID));
      SortCompanies();
      return 1;
    }
    bool  cancelCompany  ( const string & name , const string & addr ){ //NAME ADDRES
      string tmp_addr = To_Upper(addr);
      string tmp_name = To_Upper(name);
      int i = 0;
      for (CVAT company: Database){
        if(company.upper_inner_name == tmp_name && company.upper_inner_addr == tmp_addr){
          Database.erase(Database.begin()+i);
          /*Database[i].inner_taxID.erase();
          Database[i].inner_addr.erase();
          Database[i].inner_name.erase();
          Database[i].upper_inner_addr.erase();
          Database[i].upper_inner_name.erase();*/
          // SortCompanies();
          return 1;
        }
        i++;
      }
      return 0;
    }
    bool  cancelCompany ( const string    & taxID ){ // TAX ID
            int i = 0;
      for (CVAT company: Database){
        if(company.inner_taxID == taxID){
          Database.erase(Database.begin()+i);
          return 1;
        }
        i++;
      }
      return 0;
    }
    bool  invoice ( const string & taxID , unsigned int amount ){ // TAX ID
      int i = 0;
      for (CVAT company: Database){
        if(company.inner_taxID == taxID){
          Database[i].logged_invoices += company.logged_invoices + amount;
          //cout << "fucked here : " << amount << " : " << company.inner_taxID << " : " << company.inner_name << " : " << Database[i].logged_invoices << endl;
          auto it = lower_bound(begin(all_invoices), end(all_invoices), amount, Int_compare() );
          all_invoices.insert(it, amount);
          return 1;
        }
        i++;
      }
      return 0;
    }
    bool  invoice ( const string & name , const string & addr , unsigned int amount ){   // name addres
      string tmp_addr = To_Upper(addr);
      string tmp_name = To_Upper(name);
      int i = 0;
        for (CVAT company: Database){
        if(company.upper_inner_name == tmp_name && company.upper_inner_addr == tmp_addr){
          Database[i].logged_invoices = company.logged_invoices + amount;
          //cout << "fucked here : " << amount << " : " << company.inner_taxID << " : " << company.inner_name << " : " << Database[i].logged_invoices << endl;
          auto it = lower_bound(begin(all_invoices), end(all_invoices), amount, Int_compare() );
          all_invoices.insert(it, amount);
          return 1;
        }
        i++;
      }
      return 0;
    }
    bool  audit ( const string & name,const string & addr,unsigned int & sumIncome ) const{ // name addres
      string tmp_addr = To_Upper(addr);
      string tmp_name = To_Upper(name);
          sumIncome = 0;
      int i = 0;
        for (CVAT company: Database){
          if(company.upper_inner_name.compare(tmp_name) == 0&& company.upper_inner_addr.compare(tmp_addr) == 0){
            sumIncome = company.logged_invoices;
            //cout << sumIncome << endl; // audit check
            return 1;
          }
        i++;
      }
        return 0;
    }
    bool  audit ( const string & taxID,unsigned int & sumIncome ) const{ // tax ID
      int i = 0;
      sumIncome = 0;
      for (CVAT company: Database){
        if(company.inner_taxID == taxID){
            sumIncome = company.logged_invoices;
          return 1;
        }
        i++;
      }
      return 0;
    }
    bool  firstCompany ( string & name,string & addr ) const{
      if (Database.size() == 0){
      return 0;
      }
      else{
        name = Database[0].inner_name;
        addr = Database[0].inner_addr;
        if (Database.size() == 0 || name.empty() == 1 || addr.empty() == 1){
          return 0;
        }
        return 1;
      }
      return 1;
    }
    bool  nextCompany  ( string & name,string & addr ) const{
      if (Database.size() == 0 || name.empty() == 1 || addr.empty() == 1){
      return 0;
      }
      else{
        string tmp_addr = To_Upper(addr);
        string tmp_name = To_Upper(name);
        long unsigned int i = 0;
        for (CVAT company: Database){
          if (company.upper_inner_addr.empty() == 1 || company.upper_inner_name.empty() == 1){
            return 0;
          }
          if(company.upper_inner_addr == tmp_addr && company.upper_inner_name == tmp_name && i+1 < Database.size()){
            if (Database[i+1].upper_inner_addr.empty() == 1 || Database[i+1].upper_inner_name.empty() == 1){
            return 0;
            }
            name = Database[i+1].inner_name;
            addr = Database[i+1].inner_addr;
            if (Database.size() == 0 || name.empty() == 1 || addr.empty() == 1){
              return 0;
            }
            return 1;
          }
          i++;
        }
      }
      return 0;
    }
    unsigned int  medianInvoice  ( void ) const{
      if (all_invoices.size() != 0){
      return all_invoices[ceil(all_invoices.size()/2)];
      }
      else{
      return 0;
      }
    }
  private:
    vector<unsigned int>  all_invoices;
    vector<CVAT> Database = {};
};

#ifndef __PROGTEST__
int               main           ( void )
{
  string name, addr;
  unsigned int sumIncome;

  CVATRegister b1;
  assert ( !(b1 . medianInvoice () == 2000) );
  assert ( !(b1 . invoice ( "666/666", 2000 )) );
  assert ( !(b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000) );
  assert ( !(b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . cancelCompany ( "ACME", "KoLeJnI" )) );
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  //assert ( !(b1 . invoice ( "666/666", 2000 )) );
  assert ( !(b1 . medianInvoice () == 2000) );
  //b1.PrintAll();
  assert ( !(b1 . audit ( "ACME", "Thakurova", sumIncome ) && sumIncome == 2000) );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );


  assert ( !(b1 . newCompany ( "ACME", "Thakurova", "666/666" )) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  assert ( b1 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b1 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b1 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( !(b1 . medianInvoice () == 0) );
  assert ( b1 . invoice ( "ABCDEF", 1000 ) );
  assert ( b1 . medianInvoice () != 0);
  assert ( b1 . invoice ( "abcdef", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b1 . medianInvoice () != 0);
  assert ( ! b1 . invoice ( "1234567", 100 ) );
  assert ( ! b1 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b1 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b1 . audit ( "1234567", sumIncome ) );
  assert ( ! b1 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b1 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b1 . cancelCompany ( "1234567" ) );
  assert ( ! b1 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b1 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b1 . cancelCompany ( "abcdef" ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( ! b1 . cancelCompany ( "abcdef" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b1 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b1 . cancelCompany ( "ACME", "Kolejni" ) );

  assert ( b1 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( !(b1 . newCompany ( "ACME", "Kolejni", "abcdef" )) );
  assert ( b1 . newCompany ( "ACMEd", "Kolejni", "abcdefe" ) );
  assert ( b1 . newCompany ( "ACMEee", "Kolejni", "abcdefee" ) );
  assert ( b1 . newCompany ( "ACMEeee", "Kolejni", "abcdefeee" ) );
  assert ( b1 . newCompany ( "ACMEeeee", "Kolejni", "abcdefeeee" ) );
  assert ( ! b1 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b1 . cancelCompany ( "abcdef" ) );
  assert ( b1 . cancelCompany ( "abcdefe" ) );
  assert ( b1 . cancelCompany ( "abcdefee" ) );
  assert ( b1 . cancelCompany ( "abcdefeee" ) );
  assert ( b1 . cancelCompany ( "abcdefeeee" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( !(b1 . newCompany ( "ACME", "Kolejni", "abcdef" )) );
  assert ( b1 . newCompany ( "ACMEd", "Kolejni", "abcdefe" ) );
  assert ( b1 . newCompany ( "ACMEee", "Kolejni", "abcdefee" ) );
  assert ( b1 . newCompany ( "ACMEeee", "Kolejni", "abcdefeee" ) );
  assert ( b1 . newCompany ( "ACMEeeee", "Kolejni", "abcdefeeee" ) );
    assert ( b1 . cancelCompany ( "abcdef" ) );
  assert ( b1 . cancelCompany ( "abcdefe" ) );
  assert ( b1 . cancelCompany ( "abcdefee" ) );
  assert ( b1 . cancelCompany ( "abcdefeee" ) );
  assert ( b1 . cancelCompany ( "abcdefeeee" ) );
    assert ( b1 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( !(b1 . newCompany ( "ACME", "Kolejni", "abcdef" )) );
  assert ( b1 . newCompany ( "ACMEd", "Kolejni", "abcdefe" ) );
  assert ( b1 . newCompany ( "ACMEee", "Kolejni", "abcdefee" ) );
  assert ( b1 . newCompany ( "ACMEeee", "Kolejni", "abcdefeee" ) );
  assert ( b1 . newCompany ( "ACMEeeee", "Kolejni", "abcdefeeee" ) );
  //b1.PrintAll();
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  //cout << name <<" : " << addr << endl;
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  assert ( !(b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova") );
  b1.PrintAll();


  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
