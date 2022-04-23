#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#endif /* __PROGTEST__ */
using namespace std;

class CDate{
  public:
    CDate (int year, int month,int day)
    {
      tm Ctime = {1};
      Ctime.tm_year = year- 1900 ;
      Ctime.tm_mon = month -1 ;
      Ctime.tm_mday = day ;
      //struct tm  Ctime_copy = Ctime;
      time_t a = mktime(&Ctime); 
      //if (Ctime.tm_year != Ctime_copy.tm_year || Ctime.tm_mon != Ctime_copy.tm_mon || Ctime.tm_mday != Ctime_copy.tm_mday || a == -1){
      //  throw InvalidDateException();
      //}
      T_CTime = a;
    }
  time_t T_CTime;
  private:
};


class CSupermarket{
  public:
    void Print_all(){
      for (map<string, map<int,int>>::iterator itr1 = storage.begin(); itr1 != storage.end(); ++itr1){
        cout << (*itr1).first;
        for(map<int,int>::iterator itr2 = (*itr1).second.begin(); itr2 != (*itr1).second.end(); ++itr2){
          cout << "/" << (*itr2).first << " : " << (*itr2).second << "/";
        } 
        cout << endl;
      }
    } 

    CSupermarket& store(const string item,const CDate date,const int amount){
      int expiration = date.T_CTime;
      map<string, map<int,int>>::iterator it;
      if(storage.count(item)){
        if(storage[item].count(expiration)){
          storage[item].at(expiration) += amount;
        }
        else{
          storage[item].emplace(expiration,amount);
        }
      }
      else{
        pair<int, int> expiration_amount(expiration,amount);
        map<int, int> inner_temp;
        inner_temp.insert(expiration_amount);
        pair<string, map<int,int>> item_expiration_amount(item,inner_temp);
        storage.emplace(item_expiration_amount);
      }
      return *this;
    }

    const list<pair<string,int> > expired (const CDate date) const{
      list<pair<string,int>> Ordered_return;
      int expiration = date.T_CTime;
      multimap<int, string, greater<int>> Expired_storage;
      for (map<string, map<int,int>>::const_iterator itr1 = storage.begin(); itr1 != storage.end(); ++itr1){
        int Expired_count = 0;
        for(map<int,int>::const_iterator itr2 = (*itr1).second.begin(); itr2 != (*itr1).second.end(); ++itr2){
          if ((*itr2).first < expiration){
            Expired_count += (*itr2).second;
          }
         } 
        if (Expired_count > 0){
          Expired_storage.emplace(Expired_count, (*itr1).first);
        }
      }
      for (multimap<int,string>::iterator itr = Expired_storage.begin(); itr != Expired_storage.end(); ++itr){
        Ordered_return.emplace_back((*itr).second,(*itr).first);
      }
      return Ordered_return;
    }
    
    const bool check_existence(string &product){
      string product_swap_to = "";
      int amount = 0;
      if (storage.find(product) != storage.end()){
        return true;
      }
      for (map<string, map<int,int>>::iterator itr = storage.begin(); itr != storage.end(); ++itr){
        if ((*itr).first.length() == product.length()){
          int diff = 0;
          for(long unsigned int i = 0; i<product.length(); i++) {
            if (product[i] != (*itr).first[i]){
              diff++;
            }
          }
          if (diff == 1){
            product_swap_to = (*itr).first;
            amount++;
          }
        }
      }
      product = product_swap_to;
      return true;
    }
    const int dispense(string product, int amount){
      int dispensed_counter = 0;
      while(storage[product].empty() == false ){
        auto item = storage[product].begin();
        if( amount  > (*item).second + dispensed_counter){
          dispensed_counter += (*item).second;
          storage[product].erase(item);
        }
        else{
          (*item).second -= (amount - dispensed_counter);
          dispensed_counter = amount; 
          break;
        }
      }
      return dispensed_counter;
    }

    const void sellable(list<pair<string, int>> &groceries,set<string> &unsellable){
      for (list<pair<string, int>>::iterator itr1 = groceries.begin(); itr1 != groceries.end(); itr1++){
      if (storage.find(itr1->first) != storage.end()){
        continue;
      }
      int amount = 0;
        for (map<string, map<int,int>>::iterator itr2 = storage.begin(); itr2 != storage.end(); itr2++){
          if ((*itr2).first.length() == (*itr1).first.length()){
            int diff = 0;
            for(long unsigned int i = 0; i<(*itr2).first.length(); i++) {
              if ((*itr1).first[i] != (*itr2).first[i]){
                diff++;
              }
            }
            if (diff == 1){
              amount++;
            }
          }
        }
      if (amount > 1){
        unsellable.insert((*itr1).first);
      }
      }
    }

    const void sell(list<pair<string, int>> &shoppinglist){
      set<string> unsellable;
      sellable(shoppinglist,unsellable);
      for (list<pair<string, int>>::iterator itr = shoppinglist.begin(); itr != shoppinglist.end(); itr++){
        string usable = (*itr).first;
        if (check_existence(usable) == true && unsellable.find((*itr).first) == unsellable.end()){
          int sold = dispense(usable, (*itr).second);
          if (sold == (*itr).second){
            itr = shoppinglist.erase(itr);
            itr--;
          }
          else{
            (*itr).second -= sold;
          }
        }       
      }
      for (map<string, map<int,int>>::iterator itr = storage.begin(); itr != storage.end(); itr++){
        if((*itr).second.empty() == 1){
          itr = storage.erase(itr);
          itr--;
        }
      }
    }
  private:
    map<string, map<int,int>> storage = {};
};
#ifndef __PROGTEST__
int main ( void )
{
  CSupermarket s;
  s . store ( "bread", CDate ( 2016, 4, 30 ), 100 )
    . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
    . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
    . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
    . store ( "okey", CDate ( 2016, 7, 18 ), 5 );

  list<pair<string,int> > l0 = s . expired ( CDate ( 2018, 4, 30 ) );
  assert ( l0 . size () == 4 );
  assert ( ( l0 == list<pair<string,int> > { { "bread", 200 }, { "beer", 50 }, { "butter", 10 }, { "okey", 5 } } ) );

  list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
  s . sell ( l1 );
  assert ( l1 . size () == 2 );
  assert ( ( l1 == list<pair<string,int> > { { "Coke", 5 }, { "butter", 10 } } ) );

  list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
  assert ( l2 . size () == 1 );
  assert ( ( l2 == list<pair<string,int> > { { "bread", 98 } } ) );

  list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
  assert ( l3 . size () == 1 );
  assert ( ( l3 == list<pair<string,int> > { { "bread", 198 } } ) );

  list<pair<string,int> > l4 { { "bread", 105 } };
  s . sell ( l4 );
  assert ( l4 . size () == 0 );
  assert ( ( l4 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l5 . size () == 3 );
  assert ( ( l5 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 } } ) );

  s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );

  list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
  s . sell ( l6 );
  assert ( l6 . size () == 3 );
  assert ( ( l6 == list<pair<string,int> > { { "cake", 1 }, { "cuke", 1 }, { "Cokes", 1 } } ) );

  list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l7 . size () == 4 );
  assert ( ( l7 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 7 }, { "okey", 5 } } ) );

  s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );

  list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
  s . sell ( l8 );
  assert ( l8 . size () == 2 );
  assert ( ( l8 == list<pair<string,int> > { { "Cake", 1 }, { "coke", 1 } } ) );

  list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l9 . size () == 5 );
  assert ( ( l9 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 }, { "cake", 3 } } ) );

  list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
  s . sell ( l10 );
  assert ( l10 . size () == 2 );
  assert ( ( l10 == list<pair<string,int> > { { "cake", 12 }, { "Cake", 2 } } ) );

  list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l11 . size () == 4 );
  assert ( ( l11 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "Coke", 6 }, { "okey", 5 } } ) );

  list<pair<string,int> > l12 { { "Cake", 4 } };
  s . sell ( l12 );
  assert ( l12 . size () == 0 );
  assert ( ( l12 == list<pair<string,int> > {  } ) );

  list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
  assert ( l13 . size () == 4 );
  assert ( ( l13 == list<pair<string,int> > { { "bread", 93 }, { "beer", 50 }, { "okey", 5 }, { "Coke", 2 } } ) );

  list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
  s . sell ( l14 );
  assert ( l14 . size () == 1 );
  assert ( ( l14 == list<pair<string,int> > { { "beer", 5 } } ) );

  s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
    . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
    . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );

  list<pair<string,int> > l15 { { "ccccc", 10 } };
  s . sell ( l15 );
  assert ( l15 . size () == 1 );
  assert ( ( l15 == list<pair<string,int> > { { "ccccc", 10 } } ) );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
