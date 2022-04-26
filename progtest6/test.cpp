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
    virtual ~CData() = default;

    CData(string temp_name, size_t temp_size){
      name = temp_name;
      size = temp_size;
    }
    virtual size_t getSize() const {
      return size;
    }

    bool operator == (const CData & Next_data) const{
      if (Next_data.Name() == Name() /* && Next_data.size == size */ && comparator(Next_data)) {
        return true;
      }
      return false;
    }

    bool operator != (const CData & Next_data) const{
      if (Next_data.Name() == Name() /* && Next_data.size == size*/ && comparator(Next_data)) {
        return false;
      }
      return true;
    }
    virtual bool comparator(const CData & Next_data)const{
      return true;
    }
    virtual string Name()const = 0;
    virtual const CData& field(const string& name)const = 0;

    virtual ostream& Output(ostream& stream)const = 0;
    //{
		//return stream << Name();
	  //}

    friend ostream &operator<<(ostream &oStream, const CData &data){
       return data.Output(oStream);
    }  
    virtual shared_ptr<CData> clone () const = 0;

  //    virtual shared_ptr<CData> CloneImpl() const =0; 
  //  virtual CData * clone () = 0 ;
  protected:
  string name;
  size_t size;
};


class CDataTypeInt : public CData{
  public:
  CDataTypeInt() : CData("int", 4){
  }
  ~CDataTypeInt(){
  //  cout << "me!!!! " << endl;
  }

  virtual const CData& field(const string& name)const{
      throw invalid_argument("Cannot use field() for type: int");
      return *this;
  }

  virtual  string Name()const override{
		  return "int";
	  }


  virtual shared_ptr<CData> clone () const{
          return make_shared<CDataTypeInt> (CDataTypeInt());
  }
  
  virtual ostream& Output(ostream& stream)const {
    return stream << Name();
	}
};
class CDataTypeDouble : public CData{
  public:
  CDataTypeDouble() : CData("double", 8){
  }
  ~CDataTypeDouble(){
   // cout << "me!!!! " << endl;
  }

  virtual  string Name()const override{
		  return "double";
	}

  virtual const CData& field(const string& name)const{
      throw invalid_argument("Cannot use field() for type: double");
    return *this; 
  }

  virtual ostream& Output(ostream& stream)const {
    return stream << Name();
	}

  virtual shared_ptr<CData> clone () const{
            return make_shared<CDataTypeDouble> (CDataTypeDouble());
    }

};
class CDataTypeEnum : public CData{
  public:
  CDataTypeEnum() : CData("enum", 4){
  }
  CDataTypeEnum(const CDataTypeEnum& old) : CData("enum", 4){
    for (auto it = old.enum_storage.begin(); it != old.enum_storage.end(); it++){
		enum_storage.push_back(*it);
    }
  }
  ~CDataTypeEnum(){}

  size_t getSize()const{
    size_t counter = 0;
      for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
        counter ++;
      }
    return counter;
  }

  CDataTypeEnum& add(const string& temp) {
    for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
        if(it != enum_storage.end()){
         if ((*it) == temp){
           throw  invalid_argument( "Duplicate enum value: " + temp);
         }
    }}
     enum_storage.push_back(temp);
     size++;
    return *this;
  }

  virtual const  CData& field(const string& name)const{
      throw invalid_argument("Cannot use field() for type: " + Name());
      return *this;
  }

  virtual ostream& Output(ostream& stream)const {
    return stream << Name();
	}
    virtual string Name()const override{
      stringstream oStream;
      oStream << name << "\n{" << endl;
      int help = 0;
       for (auto it = enum_storage.begin(); it != enum_storage.end(); it++){
          if (help > 0){
          oStream << "," << endl;
          }
          oStream << "  " <<enum_storage[help];
          help++;
       }
       oStream << "\n" << "}" ;
		  return oStream.str();
	  }
  
  bool comparator(const CData & Next_data)const{
    if(typeid(Next_data) == typeid(*this)){
     return true;
    }
    //cout << "fokked" << endl;
    return false;
  }

  virtual shared_ptr<CData> clone () const{
           return make_shared<CDataTypeEnum> (CDataTypeEnum(*this));
    }

  private:
  vector<string> enum_storage = {};
};
class CDataTypeStruct : public CData{
  public:
  CDataTypeStruct() : CData("struct", 0){
  }
  CDataTypeStruct(const CDataTypeStruct& old) : CData("struct", 0){
    for (auto it = old.struct_storage.begin(); it != old.struct_storage.end(); it++){
		struct_storage.push_back(*it);
    }
  }
  
  ~CDataTypeStruct(){
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
     // delete it->second;
    //cout << it->second.shared() << endl;
    //delete it->second;
    }
  }

  size_t getSize() const{
    size_t counter = 0;
      for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
        counter += it->second->getSize();
      }
    return counter;
  }

   CDataTypeStruct& addField(const string& name,const CData& object){
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
      if(it != struct_storage.end()){
         if (it->first == name){
           throw  invalid_argument( "Duplicate field: " + name);
         }
    }}
    struct_storage.emplace_back(pair<string, shared_ptr<CData>> (name, object.clone()));
    return *this;
  }

  const CData& field(const string& name )const{
    ostringstream oStream;
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
         if (it->first == name){
           return *(it->second);
         }
    }
    throw  invalid_argument( "Unknown field: " + name);
    return *this;
  }

  virtual shared_ptr<CData> clone () const{
      return make_shared<CDataTypeStruct> (CDataTypeStruct(*this));
  }

  virtual bool comparator(const CData & Next_dataaa)const override{
    if(typeid(Next_dataaa) == typeid(*this)){
      bool diff_flag = 0;
      shared_ptr<CData> killmenow= Next_dataaa.clone();
      CData * dumb1 = killmenow.get();
      auto Next_data = static_cast<CDataTypeStruct*>(dumb1);
        if(Next_data->struct_storage.size() == struct_storage.size()){
        for (size_t i = 0 ; i < struct_storage.size(); i++){
          if(Next_data->struct_storage[i].second->Name() != struct_storage[i].second->Name()){
            diff_flag = 1;
          }
        }
            if (diff_flag == 0){
      return true;
      }}
    }
    return false;
  }

  ostream& Output(ostream& oStream)const override{
    oStream << name << "{" << endl;
    for (auto it = struct_storage.begin(); it != struct_storage.end(); it++){
      it->second->Output(oStream) << " " << it->first << ";" << endl;
    }
    return oStream << "}";
  }

  virtual  string Name()const override{
		  return "struct";
	  }
  private:
  vector<pair<string , shared_ptr<CData>>> struct_storage = {};
};
class CDataTypeArray : public CData{
  // todo
};
class CDataTypePtr : public CData{
  // todo
};
#ifndef __PROGTEST__

static bool whitespaceMatch(const string& alp_a,
    const string& alp_b) {
    string a = alp_a;
    string b = alp_b;
    for (size_t i = 0; i < a.length(); i++)
    {
        if (a[i] == ' ' || a[i] == '\n' || a[i] == '\t') {
            a.erase(i, 1);
            i--;
        }
        if (b[i] == ' ' || b[i] == '\n' || b[i] == '\t') {
            b.erase(i, 1);
            i--;
        }
    }
    for (size_t i = 0; i < b.length(); i++)
    {
        if (b[i] == ' ' || b[i] == '\n' || b[i] == '\t') {
            b.erase(i, 1);
            i--;
        }
    }
    if (a == b) {
        return true;
    }
    cout << a << endl;
    cout << b << endl;
    return false;
}

template <typename T_>

static bool whitespaceMatch(const T_& x, const string& ref)
{
    ostringstream oss;
    oss << x;
    return whitespaceMatch(oss.str(), ref);
}

int main ( void )
{

    CDataTypeStruct  a = CDataTypeStruct() .
        addField("m_Length", CDataTypeInt()) .
        addField("m_Status", CDataTypeEnum() .
            add("NEW") .
            add("FIXED") .
            add("BROKEN") .
            add("DEAD")).
        addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct b = CDataTypeStruct() .
        addField("m_Length", CDataTypeInt()) .
        addField("m_Status", CDataTypeEnum() .
            add("NEW") .
            add("FIXED") .
            add("BROKEN") .
            add("READY")).
        addField("m_Ratio", CDataTypeDouble());

    CDataTypeStruct c = CDataTypeStruct() .
        addField("m_First", CDataTypeInt()) .
        addField("m_Second", CDataTypeEnum() .
            add("NEW") .
            add("FIXED") .
            add("BROKEN") .
            add("DEAD")).
        addField("m_Third", CDataTypeDouble());

    CDataTypeStruct  d = CDataTypeStruct() .
        addField("m_Length", CDataTypeInt()) .
        addField("m_Status", CDataTypeEnum() .
            add("NEW") .
            add("FIXED") .
            add("BROKEN") .
            add("DEAD")).
        addField("m_Ratio", CDataTypeInt());
    assert(whitespaceMatch(a, "struct\n"
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
        "}"));

    assert(whitespaceMatch(b, "struct\n"
        "{\n"
        "  int m_Length;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    READY\n"
        "  } m_Status;\n"
        "  double m_Ratio;\n"
        "}"));

    assert(whitespaceMatch(c, "struct\n"
        "{\n"
        "  int m_First;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    DEAD\n"
        "  } m_Second;\n"
        "  double m_Third;\n"
        "}"));

    assert(whitespaceMatch(d, "struct\n"
        "{\n"
        "  int m_Length;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    DEAD\n"
        "  } m_Status;\n"
        "  int m_Ratio;\n"
        "}"));

    assert(a != b);
    assert(a == c);
    assert(a != d);
    //whitespaceMatch(a.field("m_Status"), CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD"));
    //cout << a.field("m_Status").Name() << a.field("m_Status") << "aaaaaaaaaaaaaaaaa" << endl;
    //cout << CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD").Name() << CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD") << "aaaaaaaaaaaa" << endl;
    assert(a.field("m_Status") == CDataTypeEnum().add("NEW").add("FIXED").add("BROKEN").add("DEAD"));
    assert(a.field("m_Status") != CDataTypeEnum().add("NEW").add("BROKEN").add("FIXED").add("DEAD"));
    assert(a != CDataTypeInt());
    assert(whitespaceMatch(a.field("m_Status"), "enum\n"
        "{\n"
        "  NEW,\n"
        "  FIXED,\n"
        "  BROKEN,\n"
        "  DEAD\n"
        "}"));

    CDataTypeStruct aOld = a;
    b.addField("m_Other", CDataTypeDouble());

    a.addField("m_Sum", CDataTypeInt());

    assert(a != aOld);
    assert(a != c);
    assert(aOld == c);
    assert(whitespaceMatch(a, "struct\n"
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
        "  int m_Sum;\n"
        "}"));

    assert(whitespaceMatch(b, "struct\n"
        "{\n"
        "  int m_Length;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    READY\n"
        "  } m_Status;\n"
        "  double m_Ratio;\n"
        "  double m_Other;\n"
        "}"));

    c.addField("m_Another", a.field("m_Status"));

    assert(whitespaceMatch(c, "struct\n"
        "{\n"
        "  int m_First;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    DEAD\n"
        "  } m_Second;\n"
        "  double m_Third;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    DEAD\n"
        "  } m_Another;\n"
        "}"));

    d.addField("m_Another", a.field("m_Ratio"));

    assert(whitespaceMatch(d, "struct\n"
        "{\n"
        "  int m_Length;\n"
        "  enum\n"
        "  {\n"
        "    NEW,\n"
        "    FIXED,\n"
        "    BROKEN,\n"
        "    DEAD\n"
        "  } m_Status;\n"
        "  int m_Ratio;\n"
        "  double m_Another;\n"
        "}"));

    assert(a.getSize() == 20);
    assert(b.getSize() == 24);
    try
    {
        a.addField("m_Status", CDataTypeInt());
        assert("addField: missing exception!" == nullptr);
    }
    catch (const invalid_argument& e)
    {
        assert(e.what() == "Duplicate field: m_Status"sv);
    }

    try
    {
        cout << a.field("m_Fail") << endl;
        assert("field: missing exception!" == nullptr);
    }
    catch (const invalid_argument& e)
    {
        assert(e.what() == "Unknown field: m_Fail"sv);
    }

    try
    {
        CDataTypeEnum en;
        en.add("FIRST") .
            add("SECOND") .
            add("FIRST");
        assert("add: missing exception!" == nullptr);
    }
    catch (const invalid_argument& e)
    {
        assert(e.what() == "Duplicate enum value: FIRST"sv);
    }

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
