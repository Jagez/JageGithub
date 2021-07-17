// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestUserWidget.generated.h"

class UProgressBar;		//����Ҫ֪�������͵Ĵ�С�����Բ��ð���ͷ�ļ�
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
	*	BindWidget ���԰�UButton��UEditableBox��UUserWidget����
	*	��Ҫ�ڸ������ж���һ��������ͬ���ͺ����Ƶı�����Widget��Ҫ��ͬ���Ŀؼ�
	*/
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ButtonTest;
	
};
