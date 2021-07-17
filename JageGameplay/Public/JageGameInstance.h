// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JageGameInstance.generated.h"

//DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCreateWidgetEventSignature, UObject*, OwningObject);
/**
 * 
 */
UCLASS()
class JAGEGAMEPLAY_API UJageGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;
	void BeginLoadingScreen(const FString &MapName);
	void EndLoadingScreen(UWorld * LoadedWorld);


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "LoadingScreen")
		TSubclassOf<class UUserWidget> UserWidgetClass;

	UPROPERTY()
		class UUserWidget* LoadingScreenWidget;
	//FOnCreateWidgetEventSignature OnCreateWidgetEvent;

	virtual bool JoinSession(ULocalPlayer* LocalPlayer, int32 SessionIndexInSearchResults) override;


	virtual bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult) override;

};
