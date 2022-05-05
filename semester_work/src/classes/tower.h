#pragma once

#include <includes.h>


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
	tower(int damage_mod, int inc_initiative);

	virtual ~tower() = default;

	void attack(invader& target);

	void render(int x, int y);

	void disable(int turns);

 private:
	bool disabled;
	int initiative;
	int damage_mod;
};
