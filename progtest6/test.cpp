#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

class CData{
  public:
    CData(string temp_name, size_t temp_size){
      name = temp_name;
      size = temp_size;
    }
    virtual ~CData(){
     // cout << "deleted : " << name << endl;
    }
    size_t getSize(){
      return size;
    }

    bool operator == (const CData & Next_data) const{
      if (Next_data.name == name && Next_data.size == size){
        return true;
      }
      return false;
    }

    bool operator != (const CData & Next_data) const{
      if (Next_data.name == name && Next_data.size == size){
        return false;
      }
      return true;
    }

    virtual string Name()const {
		  return name;
	  }

    virtual ostream& Output(ostream& stream)const {
		return stream << name;
	  }

    friend ostream &operator<<(ostream &oStream, const CData &data){
       return data.Output(oStream);
    }  
  
    virtual CData * clone () const = 0;

  protected:
  string name;
  size_t size;
};

class CDataTypeInt : public CData{
  public:
  CDataTypeInt() : CData("int", 4){
  }
  ~CDataTypeInt(){

  }
  CData * clone () const override {
    return new CDataTypeInt ();
  }
};
class CDataTypeDouble : public CData{
  public:
  CDataTypeDouble() : CData("double", 8){
  }
  ~CDataTypeDouble(){

  }
  CData * clone () const override {
    return new CDataTypeDouble ();
  }
};
class CDataTypeEnum : public CData{
  public:
  CDataTypeEnum() : CData("enum", 0){
  }
  ~CDataTypeEnum(){

  }
  CDataTypeEnum& add(string temp){
    for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
         if ((*it) == temp){
           throw  invalid_argument( "Duplicate enum value: " + temp);
         }
    }
     enum_storage.push_back(temp);
     size++;
    return *this;
  }

  // ostream& Output(ostream& oStream)const override {
  //     oStream << name << "{" << endl;
  //     for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
  //        oStream << *it << "," << endl;
  //     }
  //     return oStream << "}" << flush;
  // }
    virtual string Name()const override{
      stringstream oStream;
      oStream << name << "{" << endl;
       for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
          oStream << *it << "," << endl;
       }
		  return oStream.str();
	  }

  bool operator == (const CDataTypeEnum & Next_data) const{
    if (Next_data.name == name && Next_data.size == size && equal(enum_storage.begin(), enum_storage.end(), Next_data.enum_storage.begin())){
      return true;
    }
    return false;
  }

  bool operator != (const CDataTypeEnum & Next_data) const{
    if (Next_data.name == name && Next_data.size == size && equal(enum_storage.begin(), enum_storage.end(), Next_data.enum_storage.begin())){
      return true;
    }
    return false;
  }

  CData * clone () const override {

    auto temp = new CDataTypeEnum();
		 for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
			temp->enum_storage.push_back(*(it));
		}
    return temp;
  }

  private:
  vector<string> enum_storage = {};
};
class CDataTypeStruct : public CData{
  public:
  CDataTypeStruct() : CData("struct", 0){
  }
  virtual ~CDataTypeStruct() override{
       for (auto it = struct_storage.begin(); it != struct_storage.end(); it++) { 
         delete it->second;
         }
  }
  CDataTypeStruct& addField(string name,const CData& object){
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
         if ((*it).first == name){
           throw  invalid_argument( "Duplicate field: " + name);
         }
    }
    struct_storage.push_back(pair<string, CData *> (name,object.clone()) );
    //cout << "hello" << object << endl;
    return *this;
  }

  CData* field(string name){
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
         if ((*it).first == name){
           return it->second;
         }
    }
    throw  invalid_argument( "Unknown field: m_Fail" + name);
  }

  CData * clone () const override {
    return new CDataTypeStruct (*this);
  }

  ostream& Output(ostream& oStream)const override {
    oStream << name << "{" << endl;
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
      oStream << (*(*it).second).Name() << " " << (*it).first << ";" << endl;
    }
    return oStream << "}" << flush;
  }

  private:
  vector<pair<string , CData *>> struct_storage = {};
};
class CDataTypeArray : public CData{
  // todo
};
class CDataTypePtr : public CData{
  // todo
};
#ifndef __PROGTEST__

string duha_jeeee(const string & str, size_t pos) {
    return str.substr(0, pos) + "\033[31m" + str.substr(pos) + "\033[0m";
}

static bool whitespaceMatch ( const string & a, const string & b ){
    size_t i =0, j =0;
  for(i = 0,j=0; i < a.length() && j<b.length();  ) {
      if(isspace(a[i])) {
          i++;
          continue;
      }
      if(isspace(b[j])) {
          j++;
          continue;
      }
      if(a[i++] != b[j++]) {
          std::cout << "You:  " << duha_jeeee(a,i) << "\nCORRECT:  " << duha_jeeee(b,j) << std::endl;
          return false;
      }
  }
  if(i!=a.length() || j!=b.length()) {
      std::cout << "You:  " << duha_jeeee(a,i) << "\nCORRECT:  " << duha_jeeee(b,j) << std::endl;
      return false;
  }
  return true;
}
template <typename T_>
static bool whitespaceMatch (const T_ & x, const string & ref )
{
  ostringstream oss;
  oss << x;
  return whitespaceMatch ( oss . str (), ref );
}
int main ( void )
{

  CDataTypeStruct workffs = CDataTypeStruct ();
  workffs. addField ( "m_Length", CDataTypeInt () )
  . addField ( "m_Status", CDataTypeEnum ()
  .add ( "NEW" ) )
  ;

  CDataTypeStruct  a = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "DEAD" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );
  cout << "fuck me sideways" << endl;
  assert ( whitespaceMatch ( a, "struct\n"
    "{\n"
    "  int m_Length;\n"
    "  enum\n"
    "  {\n"
    "    NEW,\n"
    "    FIXED,\n"
    "    BROKEN,\n"
    "    DEAD\n"
    "  } m_Status;\n"
    "  double m_Ratio;\n"
    "}") );
  cout << "segfault before" << endl;
  CDataTypeStruct b = CDataTypeStruct () .
                        addField ( "m_Length", CDataTypeInt () ) .
                        addField ( "m_Status", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "READY" ) ).
                        addField ( "m_Ratio", CDataTypeDouble () );
  
  CDataTypeStruct c =  CDataTypeStruct () .
                        addField ( "m_First", CDataTypeInt () ) .
                        addField ( "m_Second", CDataTypeEnum () . 
                          add ( "NEW" ) . 
                          add ( "FIXED" ) . 
                          add ( "BROKEN" ) . 
                          add ( "DEAD" ) ).
                        addField ( "m_Third", CDataTypeDouble () );

  // CDataTypeStruct  d = CDataTypeStruct () .
  //                       addField ( "m_Length", CDataTypeInt () ) .
  //                       addField ( "m_Status", CDataTypeEnum () . 
  //                         add ( "NEW" ) . 
  //                         add ( "FIXED" ) . 
  //                         add ( "BROKEN" ) . 
  //                         add ( "DEAD" ) ).
  //                       addField ( "m_Ratio", CDataTypeInt () );

  // assert ( whitespaceMatch ( b, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    READY\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "}") );

  // assert ( whitespaceMatch ( c, "struct\n"
  //   "{\n"
  //   "  int m_First;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Second;\n"
  //   "  double m_Third;\n"
  //   "}") );

  // assert ( whitespaceMatch ( d, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Status;\n"
  //   "  int m_Ratio;\n"
  //   "}") );

  // assert ( a != b );
  // assert ( a == c );
  // assert ( a != d );
  // assert ( a != CDataTypeInt() );
  // assert ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
  //   "{\n"
  //   "  NEW,\n"
  //   "  FIXED,\n"
  //   "  BROKEN,\n"
  //   "  DEAD\n"
  //   "}") );

  // b . addField ( "m_Other", a );

  // a . addField ( "m_Sum", CDataTypeInt ());

  // assert ( whitespaceMatch ( a, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "  int m_Sum;\n"
  //   "}") );

  // assert ( whitespaceMatch ( b, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    READY\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      DEAD\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "  } m_Other;\n"
  //   "}") );

  // assert ( whitespaceMatch ( b . field ( "m_Other" ), "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "}") );

  // assert ( whitespaceMatch ( b . field ( "m_Other" ) . field ( "m_Status" ), "enum\n"
  //   "{\n"
  //   "  NEW,\n"
  //   "  FIXED,\n"
  //   "  BROKEN,\n"
  //   "  DEAD\n"
  //   "}") );

  // assert ( a . getSize () == 20 );
  // assert ( b . getSize () == 32 );
  // b . addField ( "m_Other1", b );
  // b . addField ( "m_Other2", b );
  // b . addField ( "m_Other3", b );
  // assert ( b . field ( "m_Other3" ) . field ( "m_Other2" ) . field ( "m_Other1" ) == b . field ( "m_Other1" ) );

  // assert ( b . getSize () == 256);

  // assert ( whitespaceMatch ( b, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    READY\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      DEAD\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "  } m_Other;\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      READY\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        DEAD\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "    } m_Other;\n"
  //   "  } m_Other1;\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      READY\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        DEAD\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "    } m_Other;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        READY\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "      struct\n"
  //   "      {\n"
  //   "        int m_Length;\n"
  //   "        enum\n"
  //   "        {\n"
  //   "          NEW,\n"
  //   "          FIXED,\n"
  //   "          BROKEN,\n"
  //   "          DEAD\n"
  //   "        } m_Status;\n"
  //   "        double m_Ratio;\n"
  //   "      } m_Other;\n"
  //   "    } m_Other1;\n"
  //   "  } m_Other2;\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      READY\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        DEAD\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "    } m_Other;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        READY\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "      struct\n"
  //   "      {\n"
  //   "        int m_Length;\n"
  //   "        enum\n"
  //   "        {\n"
  //   "          NEW,\n"
  //   "          FIXED,\n"
  //   "          BROKEN,\n"
  //   "          DEAD\n"
  //   "        } m_Status;\n"
  //   "        double m_Ratio;\n"
  //   "      } m_Other;\n"
  //   "    } m_Other1;\n"
  //   "    struct\n"
  //   "    {\n"
  //   "      int m_Length;\n"
  //   "      enum\n"
  //   "      {\n"
  //   "        NEW,\n"
  //   "        FIXED,\n"
  //   "        BROKEN,\n"
  //   "        READY\n"
  //   "      } m_Status;\n"
  //   "      double m_Ratio;\n"
  //   "      struct\n"
  //   "      {\n"
  //   "        int m_Length;\n"
  //   "        enum\n"
  //   "        {\n"
  //   "          NEW,\n"
  //   "          FIXED,\n"
  //   "          BROKEN,\n"
  //   "          DEAD\n"
  //   "        } m_Status;\n"
  //   "        double m_Ratio;\n"
  //   "      } m_Other;\n"
  //   "      struct\n"
  //   "      {\n"
  //   "        int m_Length;\n"
  //   "        enum\n"
  //   "        {\n"
  //   "          NEW,\n"
  //   "          FIXED,\n"
  //   "          BROKEN,\n"
  //   "          READY\n"
  //   "        } m_Status;\n"
  //   "        double m_Ratio;\n"
  //   "        struct\n"
  //   "        {\n"
  //   "          int m_Length;\n"
  //   "          enum\n"
  //   "          {\n"
  //   "            NEW,\n"
  //   "            FIXED,\n"
  //   "            BROKEN,\n"
  //   "            DEAD\n"
  //   "          } m_Status;\n"
  //   "          double m_Ratio;\n"
  //   "        } m_Other;\n"
  //   "      } m_Other1;\n"
  //   "    } m_Other2;\n"
  //   "  } m_Other3;\n"
  //   "}" ) );

  // try
  // {
  //   a . addField ( "m_Status", CDataTypeInt () );
  //   assert ( "addField: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( e . what () == "Duplicate field: m_Status"sv );
  // }

  // try
  // {
  //   cout << a . field ( "m_Fail" ) << endl;
  //   assert ( "field: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( e . what () == "Unknown field: m_Fail"sv );
  // }

  // try
  // {
  //   cout << a . field ( "m_Length" ) . field ( "m_Foo" ) << endl;
  //   assert ( "field: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( whitespaceMatch ( e . what (), "Cannot use field() for type: int" ));
  // }

  // try
  // {
  //   cout << a . field ( "m_Status" ) . field ( "m_Foo" ) << endl;
  //   assert ( "field: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( whitespaceMatch ( e . what (), "Cannot use field() for type: enum\n"
  //   "{\n"
  //   "  NEW,\n"
  //   "  FIXED,\n"
  //   "  BROKEN,\n"
  //   "  DEAD\n"
  //   "}" ));
  // }

  // try
  // {
  //   CDataTypeEnum en;
  //   en . add ( "FIRST" ) .
  //        add ( "SECOND" ) .
  //        add ( "FIRST" );
  //   assert ( "add: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( e . what () == "Duplicate enum value: FIRST"sv );
  // }

  // CDataTypeArray ar1 ( 10, CDataTypeInt () );
  // assert ( whitespaceMatch ( ar1, "int[10]") );
  // assert ( whitespaceMatch ( ar1 . element (), "int") );
  // CDataTypeArray ar2 ( 11, ar1 );
  // assert ( whitespaceMatch ( ar2, "int[11][10]") );
  // assert ( whitespaceMatch ( ar2 . element (), "int[10]") );
  // assert ( whitespaceMatch ( ar2 . element () . element (), "int") );
  // CDataTypeArray ar3 ( 10, CDataTypeArray ( 20, CDataTypePtr ( CDataTypeInt () ) ) );
  // assert ( whitespaceMatch ( ar3, "int*[10][20]") );
  // assert ( whitespaceMatch ( ar3 . element (), "int*[20]") );
  // assert ( whitespaceMatch ( ar3 . element () . element (), "int*") );
  // assert ( whitespaceMatch ( ar3 . element () . element () . element (), "int") );
  // CDataTypePtr ar4  ( ar1 . element () );
  // assert ( whitespaceMatch ( ar4, "int*") );
  // assert ( whitespaceMatch ( ar4 . element (), "int") );
  // CDataTypePtr ar5  ( b . field ( "m_Status" ) );
  // assert ( whitespaceMatch ( ar5, "enum\n"
  //   "{\n"
  //   "  NEW,\n"
  //   "  FIXED,\n"
  //   "  BROKEN,\n"
  //   "  READY\n"
  //   "}*") );
  // assert ( whitespaceMatch ( ar5 . element (), "enum\n"
  //   "{\n"
  //   "  NEW,\n"
  //   "  FIXED,\n"
  //   "  BROKEN,\n"
  //   "  READY\n"
  //   "}") );
  // CDataTypePtr ar6 ( ar3 . element () . element () );
  // assert ( whitespaceMatch ( ar6, "int**") );
  // assert ( whitespaceMatch ( ar6 . element (), "int*") );
  // assert ( whitespaceMatch ( ar6 . element () . element (), "int") );
  // CDataTypePtr ar7 ( CDataTypeArray ( 50, ar6 ) );
  // assert ( whitespaceMatch ( ar7, "int**(*)[50]") );
  // assert ( whitespaceMatch ( ar7 . element (), "int**[50]") );
  // assert ( whitespaceMatch ( ar7 . element () . element (), "int**") );
  // assert ( whitespaceMatch ( ar7 . element () . element () . element (), "int*") );
  // assert ( whitespaceMatch ( ar7 . element () . element () . element () . element (), "int") );
  // CDataTypeArray ar8 ( 25, ar7 );
  // assert ( whitespaceMatch ( ar8, "int**(*[25])[50]") );
  // CDataTypePtr ar9 ( ar8 );
  // assert ( whitespaceMatch ( ar9, "int**(*(*)[25])[50]") );
  // a . addField ( "m_Ar1", ar1 ) .
  //     addField ( "m_Ar2", ar2 ) .
  //     addField ( "m_Ar3", ar3 ) .
  //     addField ( "m_Ar4", ar4 ) .
  //     addField ( "m_Ar5", ar5 ) .
  //     addField ( "m_Ar6", ar6 ) .
  //     addField ( "m_Ar7", ar7 ) .
  //     addField ( "m_Ar8", ar8 ) .
  //     addField ( "m_Ar9", ar9 );
  // assert ( whitespaceMatch ( a, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "  int m_Sum;\n"
  //   "  int m_Ar1[10];\n"
  //   "  int m_Ar2[11][10];\n"
  //   "  int* m_Ar3[10][20];\n"
  //   "  int* m_Ar4;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    READY\n"
  //   "  }* m_Ar5;\n"
  //   "  int** m_Ar6;\n"
  //   "  int**(* m_Ar7)[50];\n"
  //   "  int**(* m_Ar8[25])[50];\n"
  //   "  int**(*(* m_Ar9)[25])[50];\n"
  //   "}") );
  // a . addField ( "m_Madness", CDataTypeArray ( 40, CDataTypePtr ( a ) ) );
  // assert ( whitespaceMatch ( a, "struct\n"
  //   "{\n"
  //   "  int m_Length;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Status;\n"
  //   "  double m_Ratio;\n"
  //   "  int m_Sum;\n"
  //   "  int m_Ar1[10];\n"
  //   "  int m_Ar2[11][10];\n"
  //   "  int* m_Ar3[10][20];\n"
  //   "  int* m_Ar4;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    READY\n"
  //   "  }* m_Ar5;\n"
  //   "  int** m_Ar6;\n"
  //   "  int**(* m_Ar7)[50];\n"
  //   "  int**(* m_Ar8[25])[50];\n"
  //   "  int**(*(* m_Ar9)[25])[50];\n"
  //   "  struct\n"
  //   "  {\n"
  //   "    int m_Length;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      DEAD\n"
  //   "    } m_Status;\n"
  //   "    double m_Ratio;\n"
  //   "    int m_Sum;\n"
  //   "    int m_Ar1[10];\n"
  //   "    int m_Ar2[11][10];\n"
  //   "    int* m_Ar3[10][20];\n"
  //   "    int* m_Ar4;\n"
  //   "    enum\n"
  //   "    {\n"
  //   "      NEW,\n"
  //   "      FIXED,\n"
  //   "      BROKEN,\n"
  //   "      READY\n"
  //   "    }* m_Ar5;\n"
  //   "    int** m_Ar6;\n"
  //   "    int**(* m_Ar7)[50];\n"
  //   "    int**(* m_Ar8[25])[50];\n"
  //   "    int**(*(* m_Ar9)[25])[50];\n"
  //   "  }* m_Madness[40];\n"
  //   "}") );
  // assert ( a . field ( "m_Madness" ) . element () . element () . field ( "m_Ar9" ) == a . field ( "m_Ar9" ));
  // assert ( a . field ( "m_Madness" ) . element () . element () . field ( "m_Ar9" ) != a . field ( "m_Ar8" ));
  // try
  // {
  //   cout << ar2 . field ( "m_Foo" ) << endl;
  //   assert ( "field: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( whitespaceMatch ( e . what (), "Cannot use field() for type: int[11][10]" ));
  // }

  // try
  // {
  //   cout << c . element () << endl;
  //   assert ( "element: missing exception!" == nullptr );
  // }
  // catch ( const invalid_argument & e )
  // {
  //   assert ( whitespaceMatch ( e . what (), "Cannot use element() for type: struct\n"
  //   "{\n"
  //   "  int m_First;\n"
  //   "  enum\n"
  //   "  {\n"
  //   "    NEW,\n"
  //   "    FIXED,\n"
  //   "    BROKEN,\n"
  //   "    DEAD\n"
  //   "  } m_Second;\n"
  //   "  double m_Third;\n"
  //   "}" ));
  //}

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
