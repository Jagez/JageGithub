/*****************************************
@brief:		过场动画类
@file:
@version:
@company:	jage.Ltd
@author:	jage
@email:		lwk283587151@outlook.com
@time:		19.12.11
******************************************/


#pragma once

#include "CoreMinimal.h"
#include "ModuleInterface.h"
#include "Modules/ModuleManager.h"

class IJageLoadingScreenModule : public IModuleInterface
{
public:
	static inline IJageLoadingScreenModule& Get()
	{
		//检查该模块是否存在 
		return FModuleManager::LoadModuleChecked<IJageLoadingScreenModule>("JageLoadingScreen");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LoadingScreen")
		TSubclassOf<UUserWidget> UserWidgetClass;

	UPROPERTY()
		UUserWidget* LoadingScreenWidget;
	// 开始加载
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;
	//停止加载
	virtual void StopInGameLoadingScreen() = 0;

};
