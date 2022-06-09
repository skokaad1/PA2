#pragma once

#include "../tower.h"


/// LGHT(lightning) tower
/// 
/// TBD towers are ai placed and controlled defenses, this provides template on how they attack, visualize 
class LGHT_tower : public tower {
 public:
	 LGHT_tower();

	 ~LGHT_tower();

	 string sprite() const;

	 virtual shared_ptr<tower> clone() const;
 private:
};
