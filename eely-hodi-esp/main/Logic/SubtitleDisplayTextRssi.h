// Eely-HoDi - (c) 2022-26 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextRssi_h
#define SubtitleDisplayTextRssi_h

#include "SubtitleDisplayTextBase.h"
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"

class SubtitleDisplayTextRssi : public SubtitleDisplayTextBase
{
public:
	bool HasText() override;
	string GetText() override;
};

#endif