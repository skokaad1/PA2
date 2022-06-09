#pragma once

#include "../invader.h"

/// ARM(armored) invader
/// 
/// an invader with low initiative, moves slow, special move
class ARM_invader : public invader {
 public:
	 ARM_invader();
	 string sprite() const;

	 shared_ptr<invader> clone() const;
 private:
};
