// Fill out your copyright notice in the Description page of Project Settings.


#include "TestUserWidget.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UTestUserWidget::OnButtonClick()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("OnButtonClick"));
}

void UTestUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//UButton* TempButton = GetTestButton();
	//UButton* TempButton = Cast<UButton>(GetWidgetFromName(TEXT("Button")));
	if (NULL != ButtonTest)
	{
		FScriptDelegate ButtonDelegate;
		ButtonDelegate.BindUFunction(this, "OnButtonClick");
		ButtonTest->OnClicked.Add(ButtonDelegate);
		//HPBar->
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("button is ok."));
	}
	APawn* OwnerPawn = GetOwningPlayerPawn();
	if (nullptr != OwnerPawn)
	{
		//UGameplayStatics::GetPlayer
	}
}
