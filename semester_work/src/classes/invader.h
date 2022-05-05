#pragma once

#include "includes.h"

/// parent invader
/// 
/// TBD invaders are player interactible units, this provides template on how to deploy, visualise and work with them, will be split into multiple children classes of different jobs
//	public: 
//		invader(int inc_health,int inc_speed,int inc_initiative)
//		special()
//		damage(int)
// variables: 
//		int health
//		int speed
//		int initiative
class invader {
 public:
	invader(int inc_health,int inc_speed,int inc_initiative);
	invader();

	virtual ~invader() = default;

	void damage(int damage);

	void special();

	void render(int x, int y);

 private:
	int health;
	int speed;
	int initiative;
};