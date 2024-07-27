// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#include "SubtitleDisplayTextStatus.h"
#include "string_format.h"
#include "DisplayLogic.h"
#include "Eelyapp.h"

bool SubtitleDisplayTextStatus::HasText()
{
	return !g_eelyapp->GetSystemStatusString(true).empty();
}

string SubtitleDisplayTextStatus::GetText()
{
	return g_eelyapp->GetSystemStatusString(true);
}
