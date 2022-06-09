#pragma once

#include "../tower.h"

/// BSC(basic) tower
/// 
/// Basic tower has no special attacks and only shoots one shot at one target
class BSC_tower : public tower {
public:
	BSC_tower();

	~BSC_tower();

	string sprite() const;

	virtual shared_ptr<tower> clone() const;

private:
};

