// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Scripts/LogicEvents.h"
#include "JageGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class JAGEGAMEPLAY_API AJageGameModeBase : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;


	virtual void BeginPlay() override;


	virtual void Logout(AController* Exiting) override;

	//install KBE events
	virtual void InstallEvents();

	//��ұ��߳��¼�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnKicked(const UKBEventData* pEventData);
	//��ҶϿ������¼�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnDisconnected(const UKBEventData* pEventData);
	//���״̬�����ı��¼�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnConnectedState(const UKBEventData* pEventData);
	//����������ӳɹ��¼�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnReloginBaseappSuccessfully(const UKBEventData* pEventData);
	//�����������ʧ���¼�
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "KBEngine")
		void OnReloginBaseappFailed(const UKBEventData* pEventData);

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void OnReloginBaseapp();

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void OnStartReloginTimer();

	UFUNCTION(BlueprintCallable, Category = "KBEngine")
		void OnStopReloginTimer();

	FTimerHandle ReloginHandle;

};
