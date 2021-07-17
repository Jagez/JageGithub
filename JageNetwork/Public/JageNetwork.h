#ifndef _GNETWORK_H_
#define _GNETWORK_H_
#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
class IJageNetworkModule : public IModuleInterface
{
public:
	virtual uint16_t getCount(uint16_t x, uint16_t y) = 0;
};

#endif // !_GNETWORK_H_
