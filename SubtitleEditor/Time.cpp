#include "Time.h"
#include <iostream>

time::time(Time* ret) {
	this->reset(ret);
}

void time::reset(Time* ret) {
	ret->h = ret->m = ret->s = ret->ms = 0;
}

int time::readHours(string subtitles, int& i) {
	int h = 0;
	h = subtitles[i++] - '0';
	h = h * 10 + subtitles[i++] - '0';
	i++;
	return h;
}

int time::readMinutes(string subtitles, int& i) {
	int m = 0;
	m = subtitles[i++] - '0';
	m = m * 10 + subtitles[i++] - '0';
	i++;
	return m;
}

int time::readSeconds(string subtitles, int& i) {
	int s = 0;
	s = subtitles[i++] - '0';
	s = s * 10 + subtitles[i++] - '0';
	i++;
	return s;
}

int time::readMilliSeconds(string subtitles, int& i) {
	int ms;
	ms = subtitles[i++] - '0';
	ms = ms * 10 + subtitles[i++] - '0';
	ms = ms * 10 + subtitles[i++] - '0';
	i++;
	return ms;
}

int time::convertToMs(int h, int m, int s, int ms) {
	ms = ((h * 60 + m) * 60 + s) * 1000 + ms;
	return ms;
}

void time::fromMs(int ms, Time* ret) {

	if (ms / 1000 != 0) {
		ret->s += ms / 1000;
		ret->ms = ms % 1000;
		if (ret->s >= 60) {
			ret->m = ret->s / 60;
			ret->s = ret->s % 60;
			if (ret->m >= 60) {
				ret->h = ret->s / 60;
				ret->m = ret->m % 60;
			}
		}
	}
}

