#ifndef SUBTITLES_H
#define SUBTITLES_H

#include <string>
#include "Stack.h"
using namespace std;


struct Selection {
	int start, end;
	Selection* next;
};


class SubtitleEditor {

public:
	int loadSubtitles(string subtitles);
	string saveSubtitles();
	void addToSelection(int start, int end);
	void deselect();
	void boldText(int start, int end);
	void italicText(int start, int end);
	void underlineText(int start, int end);
	void removeStyle();
	void shiftForward(int ms);
	void shiftBackward(int ms);
	void insertSubtitle(int start, int length, string text);
	void deleteSubtitles();
	void merge(string subtitles);
	void fixLongLines(int max);
	void fixLongTime(int ms);
	void undo();


private:
	Elem* head = nullptr, * current = nullptr, * last = nullptr;
	Selection* range = nullptr, * endRange = nullptr;
	time* time;
	Stack* stack = nullptr;
};


#endif