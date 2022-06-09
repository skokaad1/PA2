#pragma once

#include "../invader.h"

/// INT(caster) invader
/// 
/// bad stats, good ability
class INT_invader : public invader {
 public:
	 INT_invader();
	 string sprite() const;

	 shared_ptr<invader> clone() const;
 private:
};
