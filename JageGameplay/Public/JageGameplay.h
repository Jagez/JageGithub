#ifndef _GGAMEPLAY_H_
#define _GGAMEPLAY_H_
#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
class IJageGameplayModule : public IModuleInterface
{
public:
	virtual uint16_t getCount(uint16_t x, uint16_t y) = 0;
};

#endif // !_GGAMEPLAY_H_
