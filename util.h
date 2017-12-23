#include <chrono>

class Timer 
{
public:
	Timer(): _start(now()), _end(_start) 
	{
	}

	void start()
	{
		_start = now();
		_end = _start;
	}

	void end()
	{
		_end = now();
	}

	float duration()
	{
		// in milliseconds, ms
		auto s = std::chrono::duration_cast<std::chrono::duration<double>>(_end - _start);
		return static_cast<float>(s.count()) * 1000.0f;
	}


private:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;

	TimePoint now() 
	{
		return Clock::now();
	}

	TimePoint _start;
	TimePoint _end;
};


using TimeItFunc = int (*) (void);
float time_it(TimeItFunc func, int repeat = 1, const char* output_tag = nullptr) 
{
	Timer t;
	for(int i = 0; i < repeat; ++i) 
	{
		func();
	}
	t.end();

	if(output_tag != nullptr)
	{
		printf("%s: %.3fms\n", output_tag, t.duration());
	}

	return t.duration();
}