#include "JageGameplay/Public/JageGameplay.h"
class FJageGameplayModule : public IJageGameplayModule
{
public:

	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FGGameplay is working."));
	}

	virtual void ShutdownModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("FGGameplay is End."));
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

IMPLEMENT_GAME_MODULE(FJageGameplayModule, JageGameplay)
