#ifndef _GJAGETHREAD_H_
#define _GJAGETHREAD_H_
#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "CoreMinimal.h"
class IJageThreadModule : public IModuleInterface
{
public:
	virtual uint16_t getCount(uint16_t x, uint16_t y) = 0;
};

#endif // !_GJAGETHREAD_H_
