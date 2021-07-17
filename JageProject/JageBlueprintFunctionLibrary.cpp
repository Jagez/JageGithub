// Fill out your copyright notice in the Description page of Project Settings.

#include "JageBlueprintFunctionLibrary.h"
#include "JageLoadingScreen/Public/JageLoadingScreen.h"

void UJageBlueprintFunctionLibrary::StartPlayingLoadingScreen(bool bLoadingAbt, float durTime)
{
	//load loadingscreen module
	IJageLoadingScreenModule & loadingScreenModule = IJageLoadingScreenModule::Get();
	//调用模块的开始动画
	loadingScreenModule.StartInGameLoadingScreen(bLoadingAbt, durTime);
}

void UJageBlueprintFunctionLibrary::StopPlayingLoadingScreen()
{
	IJageLoadingScreenModule & iLoaingScreenModule = IJageLoadingScreenModule::Get();
	iLoaingScreenModule.StopInGameLoadingScreen();
}
