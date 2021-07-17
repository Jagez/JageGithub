// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JageProjectHUD.generated.h"

UCLASS()
class AJageProjectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AJageProjectHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

public:

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

