// Eely-HoDi - (c) 2022-24 by Joerg Plenert | https://eely.eu
#ifndef SubtitleDisplayTextStatus_h
#define SubtitleDisplayTextStatus_h

#include "SubtitleDisplayTextBase.h"
#include "ConfigStoreApp.h"
#include "DeviceInstance.h"

class SubtitleDisplayTextStatus : public SubtitleDisplayTextBase
{
public:
	bool HasText() override;
	string GetText() override;
};

#endif