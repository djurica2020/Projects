#ifndef TIME_H
#define TIME_H

#include <string>
using namespace std;

struct Time {
	int h, m, s, ms;
};

class time {
public:
	time(Time* ret);
	void reset(Time* ret);
	int readHours(string subtitles, int& i);
	int readMinutes(string subtitles, int& i);
	int readSeconds(string subtitles, int& i);
	int readMilliSeconds(string subtitles, int& i);
	int convertToMs(int h, int m, int s, int ms);
	void fromMs(int ms, Time* ret);

private:
	int b;
};

#endif