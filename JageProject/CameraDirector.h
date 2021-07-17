// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

//摄像机模式
UENUM()
enum JageProjectCharacterCameraMode
{
	E_CameraMode_None,
	E_CameraMode_First,
	E_CameraMode_Third,
	E_CameraMode_ThirdRotator,		//跟随视角移动
	E_CameraMode_ThirdWOW,			//第三人称可拉近
	E_CameraMode_Top,
	E_CameraMode_Max
};


USTRUCT(BlueprintType)
struct FSCharacterCameraInfo
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CamerasInfo)
		int id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CamerasInfo)
		AActor *cameraActor;

	//摄像机切换的时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CamerasInfo)
	float TimeBetweenCameraChanges = 2.f;

	//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CamerasInfo)
	float TimeBlend = 0.75f;


};

UCLASS()
class ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraDirector();
	bool ChangeCameraMode(JageProjectCharacterCameraMode mode);

public:

	//摄像机当前模式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		TEnumAsByte<enum JageProjectCharacterCameraMode> mCameraMode;
	//摄像机的距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		float mCameraViewDistance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
		TArray<FSCharacterCameraInfo> mCameras;

	//切换摄像机的剩余时间
	float TimeToNextCameraChange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void MyCallback();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
