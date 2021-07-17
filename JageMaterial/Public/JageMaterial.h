#ifndef _GMATERIAL_H_
#define _GMATERIAL_H_
#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
class IJageMaterialModule : public IModuleInterface
{
public:
	virtual uint16_t getCount(uint16_t x, uint16_t y) = 0;
};

#endif // !_GMATERIAL_H_
