// Fill out your copyright notice in the Description page of Project Settings.


#include "JageGameInstance.h"
#include "JageLoadingScreen.h"
#include "ModuleManager.h"
#include "Blueprint/UserWidget.h"
#include "MoviePlayer/Public/MoviePlayer.h"

void UJageGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UJageGameInstance::BeginLoadingScreen);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &UJageGameInstance::EndLoadingScreen);
}

void UJageGameInstance::BeginLoadingScreen(const FString& MapName)
{
	IJageLoadingScreenModule* LoadingScreen = FModuleManager::LoadModulePtr<IJageLoadingScreenModule>(TEXT("JageLoadingScreen"));
	if (nullptr != LoadingScreen)
	{
		//LoadingScreen->StartInGameLoadingScreen(true, 3.f);

		FLoadingScreenAttributes LoadingScreen;
		LoadingScreen.bAutoCompleteWhenLoadingCompletes = true;
		LoadingScreen.bAllowEngineTick = false;
		LoadingScreen.bWaitForManualStop = false;
		LoadingScreen.bMoviesAreSkippable = true;
		LoadingScreen.MinimumLoadingScreenDisplayTime = 5.f;

		//static ConstructorHelpers::FClassFinder<UUserWidget> LoadingScreenClass(TEXT("/Game/G_Widget/LoadingScreen"));
		//UserWidgetClass = LoadingScreenClass.Class;
		LoadingScreenWidget = CreateWidget<UUserWidget>(this, UserWidgetClass);
		TSharedPtr<SWidget> LoadingScreenWidgetPtr = LoadingScreenWidget->TakeWidget();

		LoadingScreen.WidgetLoadingScreen = LoadingScreenWidgetPtr;			//FLoadingScreenAttributes::NewTestLoadingScreenWidget();//SNew(SJageLoadingScreen);
		LoadingScreen.MoviePaths.Add("myMp4");
		GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, MapName);
	}
}

void UJageGameInstance::EndLoadingScreen(UWorld* LoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

bool UJageGameInstance::JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults)
{
	Super::JoinSession(LocalPlayer, SessionIndexInSearchResults);
	return true;
}

bool UJageGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	Super::JoinSession(LocalPlayer, SearchResult);
	return true;
}
