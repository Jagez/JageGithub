#include "JageToolUnit/Public/JageToolUnit.h"
class FJageToolUnitModule : public IJageToolUnitModule
{
public:

	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FGNetwork is working."));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FGNetwork is End."));
	}

	virtual bool IsGameModule() const override
	{
		return true;
	}

	virtual uint16_t getCount(uint16_t x, uint16_t y) override
	{
		return x + y;
	}
};

IMPLEMENT_GAME_MODULE(FJageToolUnitModule, JageToolUnit)
