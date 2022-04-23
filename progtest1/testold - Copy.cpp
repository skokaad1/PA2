#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */
bool fail = 0; 
class Node {
    public:
    char character;
    class Node *L_Zero;
    class Node *R_One;
};

typedef unsigned char BYTE;

void printBT(const std::string& prefix, class Node* node, bool isLeft)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isLeft ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->character << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), node->L_Zero, true);
        printBT( prefix + (isLeft ? "│   " : "    "), node->R_One, false);
    }
}

void printBT(class Node* node)
{
    printBT("", node, false);    
}

void deleteTree(class Node* node)
{
    if (node == nullptr) {
      delete node; 
      return;
    }
    /* first delete both subtrees */
    deleteTree(node->L_Zero);
    deleteTree(node->R_One);
    delete node;
}

/*std::vector<BYTE> readFile(const char* filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);
    if ( file.bad() || file.fail()){
      fail = 1;
      std::vector<BYTE> fileData(0);
      return fileData;
    }
    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<BYTE> fileData;
    cout << fileData.max_size() << endl;
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}*/

bool ChartoBitstream(const char * inFileName , vector<bool> &outVector){
  char ch;
  fstream fin(inFileName, fstream::in);
  if ( fin.bad() || fin.fail() ){
    //cout << "fail here" << endl;
    return false;
  } 
  else{ 
    while (fin >> noskipws >> ch){
      for(int i = 7; i >= 0 ; i--){
        bool k = (ch >> i) & 1;
        outVector.push_back(k);
        }
    }
  }
  return true;
}

struct Exc_out_of_range {};
int make_int(const unsigned long int a) {
    const int n = static_cast<int>(a);
    const unsigned long int a2 = static_cast<unsigned long int>(n);
    if (a2 != a) throw Exc_out_of_range();
    return n;
}

class Node * ReconstructEncodingTree(class Node * Current_node , bool LorR , int &position , vector<bool> &bitStream){
  int Maxlength = 0; 
  Maxlength  = make_int(bitStream.size());
  if((position >= Maxlength) || (fail == 1)){
    fail = 1;
    delete Current_node;
    //cout << "caught" << endl;
    return NULL;
  }
  if (bitStream[position] == 0){
    class Node* Left = new class Node();
    position++;
    Current_node->L_Zero = ReconstructEncodingTree(Left, false, position, bitStream);
    class Node* Right = new class Node();
    position++;
    Current_node->R_One = ReconstructEncodingTree(Right, true, position, bitStream);
    return Current_node;
  }
  if (bitStream[position] == 1){
    string next8 = "";
    for (int i = 1; i <= 8;i++){
      if (bitStream[position+i] == true){
        next8.push_back('1');
      }
      if (bitStream[position+i] == false){
        next8.push_back('0');
      }
    }
    position += 8;
    int parseInt = stoi(next8, 0, 2);
    if ((parseInt > 127) || (parseInt < 1)){
      fail = 1;
      delete Current_node;
      //cout << "caught" << endl; 
      return NULL;
    }
    Current_node->character =(char)(parseInt);
        //cout << parseInt << " : " << Current_node->character << endl; 
    Current_node->L_Zero = nullptr;
    Current_node->R_One = nullptr;
    return Current_node;
  }
  return nullptr;
}

bool decompressFile ( const char * inFileName, const char * outFileName ){
  //loading file into char array

  vector<bool> bitStream = {};
  if (ChartoBitstream(inFileName,bitStream) == false)
  {
    return false;
  } 
  //generating tree
  int Maxlength = 0;
  Maxlength = make_int(bitStream.size());
  class Node* Root = new class Node();
  int position = 0;
  Root = ReconstructEncodingTree(Root, false ,position, bitStream);
  //printBT(Root);
  //decoding with bin tree
  ofstream file;
  file.open(outFileName);
  if (file.bad()){
    deleteTree(Root);
    return false;
  }
  position++;
  if (position >= Maxlength){
    deleteTree(Root);
    return false;
  }
  if (fail == 1){
    deleteTree(Root);
    //cout << "caught" << endl; 
    return false;
  }
  while(position < Maxlength){
    if (bitStream[position] == 1){
      class Node* currentNode = Root;
      int i = 1;
      int j = 0;
      while (j != 4096){
        if (position + i >= Maxlength){
          file.close();
          file.open(outFileName, ofstream::out | ofstream::trunc);
          file.close();
          deleteTree(Root);
          return false;
        }
        if(currentNode->character == '\0'){
          if(bitStream[position+i] == 0){
            currentNode = currentNode->L_Zero;
          }
          if(bitStream[position+i] == 1){
            currentNode = currentNode->R_One;
          }
        }
        if(currentNode->character != '\0'){
          file << currentNode->character;
          currentNode = Root;
          j++;
        }
        i++;
      }
      flush(file);
      position += i;
    }

    if (bitStream[position] == 0){
      string next12 = "";
      for (int i = 1; i <= 12;i++){
        if (bitStream[position+i] == true){
          next12.push_back('1');
        }
        if (bitStream[position+i] == false){
          next12.push_back('0');
        }
      }
      position += 12;
      int Lengthofchunk = stoi(next12, 0, 2);
      class Node* currentNode = Root;
      int i = 1;
      int j = 0;
      while (j != Lengthofchunk){
        if (position + i > Maxlength){
          file.close();
          file.open(outFileName, ofstream::out | ofstream::trunc);
          file.close();
          deleteTree(Root);
          //cout << "failhere" << endl;
          return false;
        }
        if(currentNode->character == '\0'){
          if(bitStream[position+i] == 0){
            currentNode = currentNode->L_Zero;
          }
          if(bitStream[position+i] == 1){
            currentNode = currentNode->R_One;
          }
        }
        if(currentNode->character != '\0'){
          file << currentNode->character;
          cout << currentNode->character;
          currentNode = Root;
          j++;
        }
        i++;
      }
      position += i;
      int remaining = 8-(position % 8);
      if (remaining == 8){
        remaining = 0;
      }
      /*cout << "position: " <<position << endl;
      cout << "remaining: " <<remaining<< endl;
      cout << "MaxLength: " <<Maxlength<< endl;*/
      if (position > Maxlength){
        file.close();
        file.open(outFileName, ofstream::out | ofstream::trunc);
        file.close();
        deleteTree(Root);
        return false;
      }
      for (int p = 0; p < remaining-1; p++){
        if(bitStream[position+p] == 0){}
        else {
          file.close();
          file.open(outFileName, ofstream::out | ofstream::trunc);
          file.close();
          deleteTree(Root);
          return false;
        }
      }
      if ((position + remaining) != Maxlength){
        file.close();
        file.open(outFileName, ofstream::out | ofstream::trunc);
        file.close();
        deleteTree(Root);
        return false;
      }
      flush(file);
      deleteTree(Root);
      return true;
    }
  }
  deleteTree(Root);
  return true;
}

bool compressFile ( const char * inFileName, const char * outFileName )
{
  // keep this dummy implementation (no bonus) or implement the compression (bonus)
  return false;
}

#ifndef __PROGTEST__
bool identicalFiles(const std::string& p1, const std::string& p2) {
  std::ifstream f1(p1, std::ifstream::binary|std::ifstream::ate);
  std::ifstream f2(p2, std::ifstream::binary|std::ifstream::ate);

  if (f1.fail() || f2.fail()) {
    return false; //file problem
  }

  if (f1.tellg() != f2.tellg()) {
    return false; //size mismatch
  }

  //seek back to beginning and use std::equal to compare contents
  f1.seekg(0, std::ifstream::beg);
  f2.seekg(0, std::ifstream::beg);
  return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
                    std::istreambuf_iterator<char>(),
                    std::istreambuf_iterator<char>(f2.rdbuf()));
}

int main ( void )
{
  assert ( decompressFile ( "tests/testfail6.bin", "tempfile" ) );
  /*assert ( decompressFile ( "tests/students.bin", "tempfile" ) );



  assert ( decompressFile ( "tests/test0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/test4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/test4.orig", "tempfile" ) );

  assert ( ! decompressFile ( "tests/test5.huf", "tempfile" ) );
  assert ( identicalFiles   ( "tests/test5.orig","tempfile" ) );

  assert ( ! decompressFile ( "tests/in_4552830.orig", "tempfile" ) );

  assert ( ! decompressFile ( "testfail1.bin", "tempfile" ) );

  assert ( ! decompressFile ( "testfail2.bin", "tempfile" ) );

  assert ( ! decompressFile ( "testfail3.bin", "tempfile" ) );

  assert ( ! decompressFile ( "testfail4.bin", "tempfile" ) );

  assert ( ! decompressFile ( "testfail5.extreme", "tempfile" ) );



  assert ( decompressFile ( "tests/extra0.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra0.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra1.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra1.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra2.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra2.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra3.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra3.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra4.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra4.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra5.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra5.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra6.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra6.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra7.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra7.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra8.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra8.orig", "tempfile" ) );

  assert ( decompressFile ( "tests/extra9.huf", "tempfile" ) );
  assert ( identicalFiles ( "tests/extra9.orig", "tempfile" ) );*/

  return 0;
}
#endif /* __PROGTEST__ */
