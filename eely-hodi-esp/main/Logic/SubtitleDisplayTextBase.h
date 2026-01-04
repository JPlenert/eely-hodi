// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextBase_h
#define SubtitleDisplayTextBase_h

#include <string>

using namespace std;

class SubtitleDisplayTextBase
{
public:
	virtual bool HasText();
	virtual string GetText() = 0;
	virtual int DisplayTime();
};

#endif