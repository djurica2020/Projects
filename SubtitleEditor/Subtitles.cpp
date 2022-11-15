#include "Subtitles.h"
#include <iostream>


int SubtitleEditor::loadSubtitles(string subtitles) {

	int i = 0;
	Elem* newFirst = nullptr, * newLast = nullptr;
	while (i < subtitles.length()) {

		Elem* newElem = new Elem();

		newElem->ordNumb = 0;

		while (subtitles[i] != '\n') {
			newElem->ordNumb = newElem->ordNumb * 10 + subtitles[i] - '0';
			i++;
		}
		i++;


		newElem->begin.h = time->readHours(subtitles, i);
		newElem->begin.m = time->readMinutes(subtitles, i);
		newElem->begin.s = time->readSeconds(subtitles, i);
		newElem->begin.ms = time->readMilliSeconds(subtitles, i);

		newElem->msBegin = time->convertToMs(newElem->begin.h, newElem->begin.m, newElem->begin.s, newElem->begin.ms);


		while (subtitles[i] > '9' || subtitles[i] < '0') i++;

		newElem->end.h = time->readHours(subtitles, i);
		newElem->end.m = time->readMinutes(subtitles, i);
		newElem->end.s = time->readSeconds(subtitles, i);
		newElem->end.ms = time->readMilliSeconds(subtitles, i);

		newElem->msEnd = time->convertToMs(newElem->end.h, newElem->end.m, newElem->end.s, newElem->end.ms);

		int j = i;

		while (1) {
			if (subtitles[j] == '\n') {
				j++;
				if (subtitles[j++] == '\n') break;
			}
			else j++;
		}

		newElem->text.append(subtitles, i, j - i - 2);

		i = j;

		if (newLast != nullptr) {
			if (newElem->msBegin < newLast->msBegin || newElem->msEnd < newLast->msEnd || newElem->text.length() == 0) {
				return newElem->ordNumb;
			}
		}

		for (int m = 0; m < newElem->text.length(); m++) {
			if (newElem->text[m] == '<') {
				m++;
				if (newElem->text[m] != 'b' && newElem->text[m] != 'u' && newElem->text[m] != 'i') {
					for (current = newFirst; current; ) {
						newFirst = newFirst->next;
						delete current;
						current = newFirst;
					}
					return newElem->ordNumb;
				}
				else {
					m++;
					if (newElem->text[m] != '>') {
						for (current = newFirst; current; ) {
							newFirst = newFirst->next;
							delete current;
							current = newFirst;
						}
						return newElem->ordNumb;
					}
				}

				while (newElem->text[m] != '<' && m < newElem->text.length()) m++;
				if (m >= newElem->text.length()) {
					for (current = newFirst; current; ) {
						newFirst = newFirst->next;
						delete current;
						current = newFirst;
					}
					return newElem->ordNumb;
				}
				m++;
				if (newElem->text[m] != '/') {
					for (current = newFirst; current; ) {
						newFirst = newFirst->next;
						delete current;
						current = newFirst;
					}
					return newElem->ordNumb;
				}
				else {
					m++;
					if (newElem->text[m] != 'b' && newElem->text[m] != 'u' && newElem->text[m] != 'i') {
						for (current = newFirst; current; ) {
							newFirst = newFirst->next;
							delete current;
							current = newFirst;
						}
						return newElem->ordNumb;
					}
					else {
						m++;
						if (newElem->text[m] != '>') {
							for (current = newFirst; current; ) {
								newFirst = newFirst->next;
								delete current;
								current = newFirst;
							}
							return newElem->ordNumb;
						}
					}
				}

			}
		}
		newElem->words = 0;
		for (int m = 0; m <= newElem->text.length(); m++) {
			if (newElem->text[m] == ' ' || newElem->text[m] == '\n') newElem->words += 1;
		}
		if (newElem->words != 0) newElem->words++;

		if (!newFirst) newFirst = newElem;
		else newLast->next = newElem;
		newLast = newElem;
	}

	if (!head) head = newFirst;
	if (last) last->next = newFirst;
	last = newLast;

	if (stack == nullptr) stack = new Stack;
	return -1;
}

string SubtitleEditor::saveSubtitles() {

	string out;
	int i;
	for (current = head, i = 0; current; current = current->next) {

		out.append(to_string(current->ordNumb));
		out.append("\n");
		if (current->begin.h < 10) {
			out.append("0");
			out.append(to_string(current->begin.h));
			out.append(":");
		}
		else {
			out.append(to_string(current->begin.h));
			out.append(":");
		}

		if (current->begin.m < 10) {
			out.append("0");
			out.append(to_string(current->begin.m));
			out.append(":");
		}
		else {
			out.append(to_string(current->begin.m));
			out.append(":");
		}

		if (current->begin.s < 10) {
			out.append("0");
			out.append(to_string(current->begin.s));
			out.append(",");
		}
		else {
			out.append(to_string(current->begin.s));
			out.append(",");
		}

		if (current->begin.ms < 100) {
			if (current->begin.ms < 10) {
				out.append("00");
				out.append(to_string(current->begin.ms));
			}
			else {
				out.append("0");
				out.append(to_string(current->begin.ms));
			}
		}
		else {
			out.append(to_string(current->begin.ms));
		}

		out.append(" --> ");

		if (current->end.h < 10) {
			out.append("0");
			out.append(to_string(current->end.h));
			out.append(":");
		}
		else {
			out.append(to_string(current->end.h));
			out.append(":");
		}

		if (current->end.m < 10) {
			out.append("0");
			out.append(to_string(current->end.m));
			out.append(":");
		}
		else {
			out.append(to_string(current->end.m));
			out.append(":");
		}

		if (current->end.s < 10) {
			out.append("0");
			out.append(to_string(current->end.s));
			out.append(",");
		}
		else {
			out.append(to_string(current->end.s));
			out.append(",");
		}

		if (current->end.ms < 100) {
			if (current->end.ms < 10) {
				out.append("00");
				out.append(to_string(current->end.ms));
			}
			else {
				out.append("0");
				out.append(to_string(current->end.ms));
			}
		}
		else {
			out.append(to_string(current->end.ms));
		}
		out.append("\n");
		out.append(current->text);
		out.append("\n\n");
	}

	for (current = head; current; ) {
		head = head->next;
		delete current;
		current = head;
	}

	delete stack;
	return out;
}

void SubtitleEditor::addToSelection(int start, int end) {

	if (head != nullptr) {

		Selection* current, * New = new Selection;
		New->start = start;
		New->end = end;

		if (this->range) {
			for (current = range; current; current = current->next) {
				if (New->start < current->start && New->end > current->start && New->end < current->end) { current->start = New->start; return; }
				else if (New->start > current->start && New->start < current->end && New->end > current->end) { current->end = New->end; return; }
				else if (New->start > current->start && New->end < current->end) { return; }
				else if (New->start < current->start && New->end > current->end) { current->start = New->start; current->end = New->end; return; }
			}
		}

		if (!this->range) range = New;
		else this->endRange->next = New;
		this->endRange = New;
		this->endRange->next = nullptr;

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::deselect() {
	Selection* current;
	for (current = this->range; this->range; ) {
		this->range = this->range->next;
		delete current;
		current = this->range;

	}
}

void SubtitleEditor::boldText(int start, int end) {
	if (head != nullptr) {
		current = head;
		Selection* currRange = this->range;
		while (currRange) {
			while (this->current != nullptr && currRange && current->ordNumb <= currRange->end) {
				while (current->ordNumb < currRange->start) this->current = this->current->next;

				if (start > current->text.length() || start < 0) current->text.insert(0, "<b>");
				else current->text.insert(start, "<b>");
				if (end > current->text.length() || end < 0) current->text.insert(current->text.length(), "</b>");
				else current->text.insert(end, "</b>");

				current = current->next;
			}
			current = head;
			currRange = currRange->next;
		}
		deselect();


		this->stack->head = stack->loadStack(head);

	}
}

void SubtitleEditor::italicText(int start, int end) {
	if (head != nullptr) {
		current = head;
		Selection* currRange = this->range;
		while (currRange) {
			while (this->current != nullptr && currRange && current->ordNumb <= currRange->end) {
				while (current->ordNumb < currRange->start) this->current = this->current->next;
				if (start > current->text.length() || start < 0) current->text.insert(0, "<i>");
				else current->text.insert(start, "<i>");
				if (end > current->text.length() || end < 0) current->text.insert(current->text.length(), "</i>");
				else current->text.insert(end, "</i>");

				current = current->next;
			}
			current = head;
			currRange = currRange->next;
		}
		deselect();

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::underlineText(int start, int end) {
	if (head != nullptr) {
		current = head;
		Selection* currRange = this->range;
		while (currRange) {
			while (this->current != nullptr && currRange && current->ordNumb <= currRange->end) {
				while (current->ordNumb < currRange->start) this->current = this->current->next;

				if (start > current->text.length() || start < 0) current->text.insert(0, "<u>");
				else current->text.insert(start, "<u>");
				if (end > current->text.length() || end < 0) current->text.insert(current->text.length(), "</u>");
				else current->text.insert(end, "</u>");

				current = current->next;
			}
			current = head;
			currRange = currRange->next;
		}
		deselect();

		this->stack->head = stack->loadStack(head);
	}

}

void SubtitleEditor::removeStyle() {
	if (head != nullptr) {
		if (!this->range) return;
		current = head;
		Selection* currRange = this->range;
		while (currRange) {
			while (this->current != nullptr && currRange && current->ordNumb <= currRange->end) {
				while (current->ordNumb < currRange->start) this->current = this->current->next;


				for (int i = 0; i < current->text.length(); i++) {
					if (current->text[i] == '<') {
						int j = i;
						i++;
						if (i < current->text.length()) {
							if (current->text[i] == 'b' || current->text[i] == 'i' || current->text[i] == 'u') {
								i++;
								if (i < current->text.length() && current->text[i] == '>') {
									current->text.erase(j, 3);
								}
							}
							else if (current->text[i] == '/') {
								i++;
								if (i < current->text.length() && current->text[i] == 'b' || current->text[i] == 'i' || current->text[i] == 'u') {
									i++;
									if (i < current->text.length() && current->text[i] == '>') current->text.erase(j, 4);
								}
							}
						}
					}
				}
				current = current->next;
			}
			current = head;
			currRange = currRange->next;
		}
		deselect();



		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::shiftForward(int ms) {
	if (head != nullptr) {

		if (this->range == nullptr) {
			this->range = new Selection;
			this->range->start = this->head->ordNumb;
			this->range->end = this->last->ordNumb;
			this->range->next = nullptr;
		}

		current = head;

		Selection* currRange = range;


		while (currRange) {
			while (this->current->ordNumb < currRange->start) current = current->next;
			for (; current; current = current->next) {
				if (current->ordNumb > currRange->end) break;
				current->msBegin += ms;
				current->begin.ms += ms;
				if (current->msBegin / 1000 != 0) {
					current->begin.s += current->begin.ms / 1000;
					current->begin.ms = (current->begin.ms) % 1000;
					if (current->begin.s >= 60) {
						current->begin.m = current->begin.m + current->begin.s / 60;
						current->begin.s = current->begin.s % 60;
						if (current->begin.m >= 60) {
							current->begin.h = current->begin.h + current->begin.m / 60;
							current->begin.m = current->begin.m % 60;
						}
					}
				}

				current->msEnd += ms;
				current->end.ms += ms;
				if (current->msEnd / 1000 != 0) {
					current->end.s += current->end.ms / 1000;
					current->end.ms = (current->end.ms) % 1000;
					if (current->end.s >= 60) {
						current->end.m = current->end.m + current->end.s / 60;
						current->end.s = current->end.s % 60;
						if (current->end.m >= 60) {
							current->end.h = current->end.h + current->end.m / 60;
							current->end.m = current->end.m % 60;
						}
					}
				}
			}

		}
		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::shiftBackward(int ms) {
	if (head != nullptr) {
		if (ms > head->msBegin) return;

		if (this->range == nullptr) {
			this->range = new Selection;
			this->range->start = this->head->ordNumb;
			this->range->end = this->last->ordNumb;
			this->range->next = nullptr;
		}

		current = head;

		Selection* currRange = range;
		while (currRange != nullptr) {
			while (this->current->ordNumb < currRange->start) current = current->next;
			for (; current; current = current->next) {
				if (current->ordNumb > currRange->end) break;
				current->msBegin -= ms;
				current->begin.ms -= ms;
				if (current->begin.ms < 0) {
					if (current->begin.ms > -1000) current->begin.s -= 1;
					else current->begin.s += current->begin.ms / 1000 - 1;
					current->begin.ms = 1000 + current->begin.ms % 1000;
					if (current->begin.ms == 1000) { current->begin.s += 1; current->begin.ms = 0; }
					if (current->begin.s < 0) {
						if (current->begin.s > -60) current->begin.m -= 1;
						else current->begin.m += current->begin.s / 60 - 1;
						current->begin.s = 60 + current->begin.s % 60;
						if (current->begin.s == 60) { current->begin.m += 1; current->begin.s = 0; }
						if (current->begin.m < 0) {
							if (current->begin.m > -60) current->begin.h -= 1;
							else current->begin.h += current->begin.m / 60 - 1;
							current->begin.m = 60 + current->begin.m % 60;
							if (current->begin.m == 60) { current->begin.h += 1; current->begin.m = 0; }
						}
					}
				}

				current->msEnd -= ms;
				current->end.ms -= ms;
				if (current->end.ms < 0) {
					if (current->end.ms > -1000) current->end.s -= 1;
					else current->end.s += current->end.ms / 1000 - 1;
					current->end.ms = 1000 + current->end.ms % 1000;
					if (current->end.ms == 1000) { current->end.s += 1; current->end.ms = 0; }
					if (current->end.s < 0) {
						if (current->end.s > -60) current->end.m -= 1;
						else current->end.m += current->end.s / 60 - 1;
						current->end.s = 60 + current->end.s % 60;
						if (current->end.s == 60) { current->end.m += 1; current->end.s = 0; }
						if (current->end.m < 0) {
							if (current->end.m > -60) current->end.h -= 1;
							else current->end.h += current->end.m / 60 - 1;
							current->end.m = 60 + current->end.m % 60;
							if (current->end.m == 60) { current->end.h += 1; current->end.m = 0; }
						}

					}
				}
			}
			current = head;
			currRange = currRange->next;
		}
		deselect();

		this->stack->head = stack->loadStack(head);

	}
}

void SubtitleEditor::insertSubtitle(int start, int length, string text) {
	if (head != nullptr) {
		for (current = head; current; current = current->next) {
			if (start >= current->msBegin && start < current->msEnd) return;
		}

		int i = 0;

		for (current = head; current, (start - current->msEnd) >= 0; current = current->next, i++);
		i--;
		for (current = head; i > 0; current = current->next, i--);


		Elem* newElem = new Elem;



		newElem->ordNumb = current->ordNumb + 1;
		newElem->text = text;
		newElem->msBegin = start;
		newElem->msEnd = start + length;
		this->time->reset(&newElem->begin);
		this->time->reset(&newElem->end);
		this->time->fromMs(start, &newElem->begin);
		this->time->fromMs(start + length, &newElem->end);

		if (newElem->text[newElem->text.length() - 1] == ' ') newElem->text.erase(newElem->text.length() - 1, 1);
		if (newElem->text[newElem->text.length() - 1] == '\n') newElem->text.erase(newElem->text.length() - 1, 1);

		newElem->next = current->next;
		this->current->next = newElem;


		Elem* prev;
		for (prev = head, current = prev->next; current; ) {
			current->ordNumb = prev->ordNumb + 1;
			prev = prev->next;
			current = current->next;
		}

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::deleteSubtitles() {
	if (head != nullptr) {
		Selection* currRange = this->range;
		if (currRange == nullptr) return;
		current = head;

		while (currRange) {

			Elem* prev = head;

			while (current->ordNumb < currRange->start) current = current->next;

			while (prev->next != current) prev = prev->next;

			for (Elem* old = current; old && old->ordNumb <= currRange->end; ) {
				current = current->next;
				prev->next = current;
				delete old;
				old = current;
			}


			current = head;
			currRange = currRange->next;
		}
		current->ordNumb = 1;
		Elem* prev = head;
		for (current = head->next; current; current = current->next) {
			current->ordNumb = prev->ordNumb + 1;
			prev = current;
		}

		deselect();

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::merge(string subtitles) {
	if (head != nullptr) {
		loadSubtitles(subtitles);
		Elem* prev = head;
		current = head;
		current->ordNumb = 1;
		for (prev = head, current = current->next; current; current = current->next) {
			current->ordNumb = prev->ordNumb + 1;
			prev = current;
		}

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::fixLongLines(int max) {
	if (head != nullptr) {
		for (current = head; current; current = current->next) {
			for (int pos, i = 0, j = 0; i < current->text.length();) {
				while (i < current->text.length() && current->text[i] != '\n') {
					if (current->text[i] == ' ' && j < (max)) pos = i;
					i++;
					if (current->text[i] != ' ') j++;
				}
				if (j > max && current->text[pos] == ' ') {
					current->text[pos] = '\n';
					i = pos;
				}
				j = 0;
				i++;
			}

		}

		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::fixLongTime(int ms) {
	if (head != nullptr) {
		Selection* currRange = range;
		current = head;
		int length, numberOfTitles;
		Elem* prev = head;;

		while (currRange) {
			while (current->ordNumb < currRange->start) current = current->next;
			for (; current->ordNumb <= currRange->end; current = current->next) {
				while (prev->next != current) prev = prev->next;
				length = current->msEnd - current->msBegin;
				if (length > ms) {
					if (length % ms != 0) { numberOfTitles = length / ms + 1; }
					else numberOfTitles = length / ms;
					int* lengths = (int*)calloc(numberOfTitles, sizeof(int));

					for (int i = 0; i < numberOfTitles; i++) {
						lengths[i] = length / numberOfTitles;
					}
					for (int i = 0; i < numberOfTitles; i++) {
						length -= lengths[i];
					}
					if (length > 0) lengths[0] += length;

					int* words = (int*)calloc(numberOfTitles, sizeof(int));

					for (int i = 0; i < numberOfTitles; i++) {
						words[i] = current->words / numberOfTitles;
					}
					for (int i = 0; i < numberOfTitles; i++) {
						current->words -= words[i];
					}
					if (current->words > 0) words[0] += current->words;

					while (1) {
						for (int i = 0; i < numberOfTitles; i++) {
							for (int j = 1; j < numberOfTitles; j++) {
								if (words[i] - words[j] > 1) {
									words[i]--;
									words[j]++;
								}
							}
						}
						if (words[1] - words[0] <= 1) break;
					}

					string text;

					for (int i = 0; i < current->text.length(); i++) {
						if (current->text[i] == '\n') current->text[i] = ' ';
					}

					prev->next = current->next;

					for (int i = 0, count = 0; i < current->text.length(); count++) {
						int pos = i, j = 0;
						while (j < words[count]) {
							if (i >= (current->text.length())) break;
							if (current->text[i] == ' ') j++;
							i++;
						}
						text.assign(current->text, pos, i - pos);

						Elem* temp = current;

						if (count == 0) {
							insertSubtitle(temp->msBegin, lengths[count], text);
							prev = prev->next;
						}
						else {
							current = prev;
							insertSubtitle(prev->msEnd, lengths[count], text);
							prev = prev->next;
						}
						current = temp;

					}

				}
			}
			current = head;
			prev = head;
			currRange = currRange->next;
		}


		this->stack->head = stack->loadStack(head);
	}
}

void SubtitleEditor::undo() {
	if (head != nullptr) {
		head = stack->returnLastState();
	}
}

