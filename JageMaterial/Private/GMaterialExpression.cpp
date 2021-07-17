// Fill out your copyright notice in the Description page of Project Settings.


#include "GMaterialExpression.h"
#include "MaterialCompiler.h"
#include "Internationalization.h"
#define LOCTEXT_NAMESPACE "JageMaterial"

UGMaterialExpression::UGMaterialExpression(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	FText LocalName = LOCTEXT("MaterialKey", "MaterialValue");
	FText LocalName1 = LOCTEXT("MaterialKey1", "MaterialValue1");
#if WITH_EDITORONLY_DATA
	MenuCategories.Add(LocalName);
	//MenuCategories.Add(LocalName1);
#endif //WITH_EDITORONLY_DATA
}
#if WITH_EDITOR
void UGMaterialExpression::GetCaption(TArray<FString>& OutCaptions) const
{
	OutCaptions.Add(TEXT("BottomNane"));
}
#endif //WITH_EDITOR

#if WITH_EDITOR
int32 UGMaterialExpression::Compile(class FMaterialCompiler* Compiler, int32 OutputIndex)
{
	int res = INDEX_NONE;
	//Super::Compile(Compiler, OutputIndex);
	if (!Input1.GetTracedInput().Expression)
	{
		res = Compiler->Errorf(TEXT("My Err."));
	}
	else
	{
		int res1 = Input1.Compile(Compiler);
		int res2 = Input2.Compile(Compiler);
		int32 res3 = Input3.Compile(Compiler);
		res = Compiler->Add(res1, res2);
		res = Compiler->Div(res, res3);
	}
	return res;
}
#endif //WITH_EDITOR
