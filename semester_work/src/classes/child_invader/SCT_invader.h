#pragma once

#include "../invader.h"

/// SCT(scout) invader
/// 
/// an invader with high initiative, moves fast
class SCT_invader : public invader {
public:
	SCT_invader();
	void damage(int damage);
	string sprite() const;

	shared_ptr<invader> clone() const;
private:
};

