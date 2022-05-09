#pragma once

#include "../invader.h"

/// ARM(armored) invader
/// 
/// an invader with low initiative, moves slow, special move
class ARM_invader : public invader {
 public:
	 ARM_invader() : invader(10, 3, 2) {

	 }
 private:
};
