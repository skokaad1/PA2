#ifndef _CLASSES_H
#define _CLASSES_H

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
#include <thread>
#include <ostream>

#include "classes_parent.h"

class  map {

};
//=====================================================================================FIELDS
/// PTH(pathway) field
/// 
/// pathway field - used for building pathways on gamemap for invaders to walk through
class PTH_field : public field {
 public:
 private:
};

/// TWR(tower) field
/// 
/// tower field - enables tower placement
class TWR_field : public field {
 public:
 private:
};

/// BCK(background) field
/// 
/// background field - used for filling rest of the map visually
class BCK_field : public field {
 public:
 private:
};

/// END(ending field) field
/// 
/// field at the end of map - used for registering win condition
class END_field : public field {
 public:
 private:
};

//=====================================================================================INVADERS

/// SCT(scout) invader
/// 
/// an invader with high initiative, moves fast
class SCT_invader : public invader {
 public:
 private:
};

/// ARM(armored) invader
/// 
/// an invader with low initiative, moves slow, special move
class ARM_invader : public invader {
 public:
 private:
};

/// INT(caster) invader
/// 
/// bad stats, good ability
class INT_invader : public invader {
 public:
 private:
};

//=====================================================================================TOWERS

/// BSC(basic) tower
/// 
/// Basic tower has no special attacks and only shoots one shot at one target
class BSC_tower : public tower {
public:

private:
};

/// LGHT(lightning) tower
/// 
/// TBD towers are ai placed and controlled defenses, this provides template on how they attack, visualize 
class LGHT_tower : public tower {
 public:

 private:
};


#endif