// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestUserWidget.generated.h"

class UProgressBar;		//不需要知道该类型的大小，可以不用包含头文件
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class JAGEUSERINTERFACE_API UTestUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	UProgressBar* HPBar;

	UPROPERTY()
	UProgressBar* ManaBar;

public:
	UFUNCTION(BlueprintImplementableEvent, Category=CPP)
	UButton* GetTestButton();

	UFUNCTION()
	void OnButtonClick();

protected:
	virtual void NativeConstruct();

private:
	/*
	*	BindWidget 可以绑定UButton、UEditableBox、UUserWidget。。
	*	需要在该子类中定义一个具有相同类型和名称的变量，Widget中要有同样的控件
	*/
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonTest;
	
};
