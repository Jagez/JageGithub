#include "JageUserInterface/Public/JageUserInterface.h"

class FJageUserInterfaceModule : public IJageUserInterfaceModule
{
public:

	virtual void StartupModule() override
	{
		UE_LOG(LogTemp, Warning, TEXT("UserInter is working."));
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

IMPLEMENT_GAME_MODULE(FJageUserInterfaceModule, JageUserInterface)
