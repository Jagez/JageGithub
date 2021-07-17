// Fill out your copyright notice in the Description page of Project Settings.


#include "JageGameModeBase.h"
AJageGameModeBase::AJageGameModeBase(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AJageGameModeBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	//注销KBE事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void AJageGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AJageGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	//注册KBE事件
	InstallEvents();
}

void AJageGameModeBase::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (Exiting)
	{
		KBENGINE_DEREGISTER_ALL_EVENT();
	}
}

void AJageGameModeBase::InstallEvents()
{
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onKicked, OnKicked);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onDisconnected, OnDisconnected);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onConnectionState, OnConnectedState);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappSuccessfully, OnReloginBaseappSuccessfully);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onReloginBaseappFailed, OnReloginBaseappFailed);
}

void AJageGameModeBase::OnKicked_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onKicked* KickedEvent = Cast<UKBEventData_onKicked>(pEventData);
	if (nullptr != KickedEvent)
	{
		KickedEvent->errorStr;
		KickedEvent->failedcode;
	}
}

void AJageGameModeBase::OnDisconnected_Implementation(const UKBEventData* pEventData)
{
	
}

void AJageGameModeBase::OnConnectedState_Implementation(const UKBEventData* pEventData)
{
	const UKBEventData_onConnectionState* ConnectionState = Cast<UKBEventData_onConnectionState>(pEventData);
	if (nullptr != ConnectionState)
	{
		if (ConnectionState->success)
		{
			//connect success
		}
		else
		{
			ConnectionState->address;
		}
	}
}

void AJageGameModeBase::OnReloginBaseappSuccessfully_Implementation(const UKBEventData* pEventData)
{

}

void AJageGameModeBase::OnReloginBaseappFailed_Implementation(const UKBEventData* pEventData)
{

}

void AJageGameModeBase::OnReloginBaseapp()
{

}

void AJageGameModeBase::OnStartReloginTimer()
{
	if (ReloginHandle.IsValid() == true)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloginHandle, this, &AJageGameModeBase::OnReloginBaseapp, 1.f, false, 1.f);
	}
}

void AJageGameModeBase::OnStopReloginTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(ReloginHandle);
}
