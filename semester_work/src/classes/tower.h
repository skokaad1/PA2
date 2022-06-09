#pragma once

#include "includes.h"
#include "child_invader/invaders.h"

#include <memory>

/// parent tower
/// 
/// TBD towers are ai placed and controlled defenses, this provides template on how they attack, visualize 
// public:	
//		attack(invader&)
// 
//	variable:
//		int initiative
//		int damage_mod
class tower {
 public:
	tower();

	//tower(int damage_mod, int inc_initiative);

	virtual ~tower() = default;

	virtual string sprite() const = 0; 

	//void attack(invader& target);

	//void render(int x, int y);

	//void disable(int turns);

	virtual shared_ptr<tower> clone() const = 0;

 private:
	bool disabled;
	int initiative;
	int damage_mod;
};
