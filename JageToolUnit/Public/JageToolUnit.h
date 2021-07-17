#ifndef _GJAGETOOLUNIT_H_
#define _GJAGETOOLUNIT_H_
#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
class IJageToolUnitModule : public IModuleInterface
{
public:
	virtual uint16_t getCount(uint16_t x, uint16_t y) = 0;
};

#endif // !_GJAGETOOLUNIT_H_
