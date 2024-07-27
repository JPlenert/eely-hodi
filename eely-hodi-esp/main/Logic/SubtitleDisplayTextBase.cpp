// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "SubtitleDisplayTextBase.h"

bool SubtitleDisplayTextBase::HasText()
{
	return !GetText().empty();
}

int SubtitleDisplayTextBase::DisplayTime()
{
	return 3;
}