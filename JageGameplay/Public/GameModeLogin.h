// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JageGameModeBase.h"
#include "GameModeLogin.generated.h"

/**
 * 
 */
UCLASS()
class JAGEGAMEPLAY_API AGameModeLogin : public AJageGameModeBase
{
	GENERATED_UCLASS_BODY()
	


public:
	virtual void BeginPlay() override;


	virtual void InstallEvents() override;

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		bool ValidEmail(FString Email);

	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
		void OnLogin(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, Category = "KBEngine")
		void OnLogout(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnCreateAccountResult(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnLoginFaild(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnLoginBaseappFaild(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnLoginSuccessfully(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnLoginBaseapp(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void Loginapp_ImportClientMessages(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void Baseapp_ImportClientMessages(const UKBEventData* pEventData);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void Baseapp_ImportClientEntityDef(const UKBEventData* pEventData);

};
