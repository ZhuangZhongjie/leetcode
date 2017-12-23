#include <iostream>
#include <array>
#include <vector>
#include "util.h"

using namespace std;

static const int CAPACITY = 128;

enum class AoiState : int {
	ST_OUT = 0,
	ST_IN
};

enum class AoiEvent : int {
	EV_NONE = 0,
	EV_ENTER,
	EV_LEAVE,
	EV_CHANGE
};

// EV_TABLE[old_state][new_state]
static int EV_TABLE[][2] =
{
	{static_cast<int>(AoiEvent::EV_NONE), static_cast<int>(AoiEvent::EV_ENTER)},  // ST_OUT
	{static_cast<int>(AoiEvent::EV_LEAVE), static_cast<int>(AoiEvent::EV_CHANGE)} // ST_IN
};

class Space
{
public:
	Space(): cap(CAPACITY), num(0)
	{
		
	}

	void tick()
	{
		for(int i = 0; i < num; ++i) 
		{
			if (!dirty[i])
			{
				continue;
			}

			dirty[i] = false;
			for(int j = 0; j < num; ++j)
			{

				int mat_idx = i * num + j;
				int old_state = state[mat_idx];
				int within = int(calcDistSq(i, j) <= radius_sq[i]);
				int new_state = within;
				state[mat_idx] = new_state;
				event[mat_idx] = EV_TABLE[old_state][new_state];
			}
		}
	}

	void setPos(int i, float x, float y)
	{
		posx[i] = x;
		posy[i] = y;
		dirty[i] = true;
	}

	void setRadiusSq(int i, float radius_square)
	{
		radius_sq[i] = radius_square;
		dirty[i] = true;
	}

	inline float calcDistSq(int i, int j)
	{
		float dx = posx[i] - posx[j];
		float dy = posy[i] - posy[j];
		return dx * dx + dy * dy;
	}

private:
	size_t cap;  // max entities
	size_t num;  // actual number of entities 

	using FloatArray = std::array<float, CAPACITY>;
	using BoolArray = std::array<bool, CAPACITY>;
	using IntMatrix = std::array<int, CAPACITY * CAPACITY>;

	FloatArray posx; // pos.x
	FloatArray posy; // pos.y
	FloatArray radius_sq; // square of aoi radius
	BoolArray dirty; // dirty flag
	IntMatrix state; // aoi states: 0=out, 1=in
	IntMatrix event; // aoi events: 0=none, 1=enter, 2=leave, 3=change
};


int func0()
{
	int s = 0;
	for(int i = 0; i < 1000000; ++i) 
	{
		s += i;
	}

	s -= 50000;
	return s;
}

int func1()
{
	int s = 0;
	for(int i = 0; i < 1000000; ++i) 
	{
		if (i == 50000)
		{
			continue;
		}

		s += i;
	}

	return s;
}

int func2()
{
	int s = 0;
	for(int i = 0; i < 1000000; ++i) 
	{
		switch(i)
		{
		case 50000:
			break;
		default:
			s += 1;
			break;
		}
	}

	return s;
}

int func3()
{
	int s = 0;
	int table[] = {0, 1};
	for(int i = 0; i < 1000000; ++i) 
	{
		s += table[i == 50000];
	}

	return s;
}

int main(int argc, char** argv)
{
	time_it(func0, 1, "LoopAdd");
	time_it(func1, 1, "LoopIfAdd");
	time_it(func2, 1, "LoopSwitch");
	time_it(func3, 1, "LoopJumpTable");
	return 0;
}