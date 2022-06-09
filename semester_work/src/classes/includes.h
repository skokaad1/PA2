#pragma once

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <thread>
#include <ostream>

#define W_HEIGHT  38
#define W_LENGTH  120


#define FIELD_X 2
#define FIELD_Y 2

#define MENU_SPACING 2

#define MAP_X (W_LENGTH)/FIELD_X - 2 - 2 - 2 - FIELD_X
#define MAP_Y (W_HEIGHT)/FIELD_Y - 2 - 2 - 1 - FIELD_Y

#define EXIT 0
#define BACK 1
