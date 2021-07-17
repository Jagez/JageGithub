// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeLogin.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEMain.h"

AGameModeLogin::AGameModeLogin(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AGameModeLogin::BeginPlay()
{
	//«Â¿Ìª∫¥Ê
	KBEngine::KBEngineApp::getSingleton().reset();
	Super::BeginPlay();
}

void AGameModeLogin::InstallEvents()
{
	Super::InstallEvents();
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::login, OnLogin);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::logout, OnLogout);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onCreateAccountResult, OnCreateAccountResult);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginFailed, OnLoginFaild);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseappFailed, OnLoginBaseappFaild);
	KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::onLoginBaseapp, OnLoginBaseapp);
	//KBENGINE_REGISTER_EVENT(KBEngine::KBEventTypes::)
	KBENGINE_REGISTER_EVENT("onLoginSuccessfully", OnLoginSuccessfully);
	KBENGINE_REGISTER_EVENT("Loginapp_importClientMessages", Loginapp_ImportClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientMessages", Baseapp_ImportClientMessages);
	KBENGINE_REGISTER_EVENT("Baseapp_importClientEntityDef", Baseapp_ImportClientEntityDef);
}

bool AGameModeLogin::ValidEmail(FString Email)
{
	return KBEngine::KBEngineApp::getSingleton().validEmail(Email);
}

void AGameModeLogin::OnLogout_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnLogin_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnCreateAccountResult_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnLoginFaild_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnLoginBaseappFaild_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnLoginSuccessfully_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::OnLoginBaseapp_Implementation(const UKBEventData* pEventData)
{

}


void AGameModeLogin::Loginapp_ImportClientMessages_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::Baseapp_ImportClientMessages_Implementation(const UKBEventData* pEventData)
{

}

void AGameModeLogin::Baseapp_ImportClientEntityDef_Implementation(const UKBEventData* pEventData)
{

}

