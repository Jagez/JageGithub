// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Materials/MaterialExpression.h"
#include "GMaterialExpression.generated.h"

/**
 * 
 */
UCLASS()
class JAGEMATERIAL_API UGMaterialExpression : public UMaterialExpression
{
	GENERATED_UCLASS_BODY()
public:
	UPROPERTY()
		FExpressionInput Input1;
	UPROPERTY()
		FExpressionInput Input2;
	UPROPERTY()
		FExpressionInput Input3;
#if WITH_EDITOR
	virtual void GetCaption(TArray<FString>& OutCaptions) const override;
#endif // WITH_EDITOR
	
private:
#if WITH_EDITOR

	int32 Compile(class FMaterialCompiler* Compiler, int32 OutputIndex) override;
#endif // WITH_EDITOR


};
