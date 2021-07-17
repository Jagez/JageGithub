/*****************************************
@brief:		����������
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
		//����ģ���Ƿ���� 
		return FModuleManager::LoadModuleChecked<IJageLoadingScreenModule>("JageLoadingScreen");
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LoadingScreen")
		TSubclassOf<UUserWidget> UserWidgetClass;

	UPROPERTY()
		UUserWidget* LoadingScreenWidget;
	// ��ʼ����
	virtual void StartInGameLoadingScreen(bool bPlayUntilStopped, float PlayTime) = 0;
	//ֹͣ����
	virtual void StopInGameLoadingScreen() = 0;

};
