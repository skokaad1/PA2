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

	//void damage(int damage);

	//void special();

	//void render(int x, int y);

	virtual string sprite() const = 0;

	virtual shared_ptr<invader> clone() const = 0;

	shared_ptr<invader> deploy(int& a);
 private:
	int health;
	int speed;
	int initiative;
};