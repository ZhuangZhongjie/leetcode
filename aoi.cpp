#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <cmath>
#include <emmintrin.h>
#include "util.h"

using namespace std;

static const int CAPACITY = 1280;

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
		std::fill(posx.begin(), posx.end(), 0.0f);
		std::fill(posy.begin(), posy.end(), 0.0f);
		std::fill(radius_sq.begin(), radius_sq.end(), 0.0f);
		std::fill(dirty.begin(), dirty.end(), false);
		std::fill(state.begin(), state.end(), int(AoiState::ST_OUT));
		std::fill(event.begin(), event.end(), int(AoiEvent::EV_NONE));
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

				int mat_idx = i * cap + j;
				int old_state = state[mat_idx];
				int within = int(calcDistSq(i, j) <= radius_sq[i]);
				int new_state = within;
				state[mat_idx] = new_state;
				event[mat_idx] = EV_TABLE[old_state][new_state];
			}
		}
	}

	void tick2()
	{

		for(int i = 0; i < num; ++i)
		{
			if (!dirty[i])
			{
				continue;
			}

			for(int j = 0; j < num; ++j) 
			{
				int mat_idx = i * cap + j;
				dist_sq[mat_idx] = calcDistSq(i, j);
			}
		}

		for(int i = 0; i < num; ++i) 
		{
			if (!dirty[i])
			{
				continue;
			}

			dirty[i] = false;
			for(int j = 0; j < num; ++j)
			{

				int mat_idx = i * cap + j;
				int old_state = state[mat_idx];
				int within = int(dist_sq[mat_idx] <= radius_sq[i]);
				int new_state = within;
				state[mat_idx] = new_state;
				event[mat_idx] = EV_TABLE[old_state][new_state];
			}
		}
	}	

	int add(float x, float y)
	{
		int id = num++;
		setPos(id, x, y);
		return id;
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

	float calcDistSq(int i, int j)
	{
		float dx = posx[i] - posx[j];
		float dy = posy[i] - posy[j];
		return dx * dx + dy * dy;
	}

	int getNum()
	{
		return num;
	}

private:
	size_t cap;  // max entities
	size_t num;  // actual number of entities 

	using FloatArray = std::array<float, CAPACITY>;
	using BoolArray = std::array<bool, CAPACITY>;
	using IntMatrix = std::array<int, CAPACITY * CAPACITY>;
	using FloatMatrix = std::array<float, CAPACITY * CAPACITY>;

	FloatArray posx; // pos.x
	FloatArray posy; // pos.y
	FloatArray radius_sq; // square of aoi radius
	BoolArray dirty; // dirty flag
	IntMatrix state; // aoi states: 0=out, 1=in
	IntMatrix event; // aoi events: 0=none, 1=enter, 2=leave, 3=change
	FloatMatrix dist_sq;
};


int nums[1000000] = {0};

int func0()
{
	int s = 0;
	for(int i = 0; i < 1000000; ++i) 
	{
		s += nums[i];
	}

	s -= nums[50000];
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

		s += nums[i];
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


class Test1: public TimeItBase
{
public:
	void setup() override 
	{
		for(int i = 0; i < CAPACITY; ++i)
		{
			space.add(0, 1);
		}
	};

	int process() override 
	{
		space.tick();
		return space.getNum();
	}

	void cleanup() override 
	{

	}

protected:
	Space space;
};

class Test2: public Test1
{
public:
	int process() override 
	{
		space.tick2();
		return space.getNum();
	}
};


// 5x Faster than sqrtf, less precision
inline float sqrtFast(float x) 
{
	unsigned int i = *(unsigned int*) &x;
	i  += 127 << 23;  // adjust bias
	i >>= 1;          // approximation of square root
	return *(float*) &i;
}

int func4()
{
	// testify sqrtFast
	float s = 0.0f;
	for(int i = 0; i < 100000; ++i)
	{
		s += sqrtFast((float)i);
	}
	return s;
}

int func5()
{
	// testify std::sqrt
	float s = 0.0f;
	for(int i = 0; i < 100000; ++i)
	{
		s += std::sqrt((float)i);
	}
	return s;
}

double inline __declspec (naked) __fastcall sqrt14(double n)
{
	_asm fld qword ptr [esp+4]
	_asm fsqrt
	_asm ret 8
} 

int func6()
{
	// testify fsqrt
	double s = 0.0f;
	for(int i = 0; i < 100000; ++i)
	{
		s += sqrt14((double)i);
	}
	return s;
}


int main(int argc, char** argv)
{

	time_it(func0, 1, "Load");
	time_it(func0, 1, "LoopAdd");
	time_it(func1, 1, "LoopIfAdd");

	time_it(func2, 1, "LoopSwitch");
	time_it(func3, 1, "LoopJumpTable");

	time_it(new Test1(), 1000, "SpackTick");
	time_it(new Test2(), 1000, "SpackTick2");

	time_it(func4, 10000, "SqrtFast");
	time_it(func5, 10000, "StdSqrt");
	time_it(func6, 10000, "fsqrt");

	return 0;
}