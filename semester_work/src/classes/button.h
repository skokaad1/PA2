#pragma once

#include "includes.h"

class button {
 public:
	 button();

	 virtual ~button() = default;

	 void render(int x, int y);

	 virtual void interact();



	 virtual ~button() = default;
 private:
};