#ifndef _CLASSES_H
#define _CLASSES_H

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
	SCT_invader();
	void damage(int damage);

private:
};

/// ARM(armored) invader
/// 
/// an invader with low initiative, moves slow, special move
class ARM_invader : public invader {
 public:
	 ARM_invader() : invader(10, 3, 2) {

	 }
 private:
};

/// INT(caster) invader
/// 
/// bad stats, good ability
class INT_invader : public invader {
 public:
	 INT_invader() : invader(5, 3, 4) {

	 }
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