// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"
#include "JageProjectCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ACameraDirector::ACameraDirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//init camera view
	mCameraMode = E_CameraMode_First;
	mCameraViewDistance = 0.0f;
	TimeToNextCameraChange = 3.f;
	
	

}

bool ACameraDirector::ChangeCameraMode(JageProjectCharacterCameraMode mode)
{
	FRotator cameraRotator;
	FVector cameraLocation;

	/**
	 * Delay ��ʹ�� 
	 */
	
	FLatentActionInfo latenInfo;
	latenInfo.Linkage = 0;
	//�����Ҫʹ��������ͬ��Delay����ҪCallbacTarget��UUID��һ�����������Ϊ��ͬһ��Delay
	latenInfo.CallbackTarget = this;	//�ص�����
	latenInfo.UUID = 0;
	latenInfo.ExecutionFunction = "MyCallback";
	UKismetSystemLibrary::Delay(GetWorld(), 0.5f, latenInfo);

	switch (mode)
	{
		//��һ�˳�
	case E_CameraMode_First:
		break;
	case E_CameraMode_Third:
		//�ж������
		/*if (playerController != nullptr && (playerController->GetViewTarget() != mCameras[0].cameraActor)
			&& mCameras[0].cameraActor != nullptr)
		{
			playerController->SetViewTarget(mCameras[0].cameraActor);
		}
		else if (playerController != nullptr && (playerController->GetViewTarget() != mCameras[1].cameraActor)
			&& mCameras[1].cameraActor != nullptr)
		{
			playerController->SetViewTargetWithBlend(mCameras[1].cameraActor, 1.f);
		}*/
		//����Ĭ�������
		//Mesh1P->SetupAttachment(ThirdPersonCameraActor);
		mCameraMode = mode;
		break;

	default:
		break;
	}
	return true;
}

// Called when the game starts or when spawned
void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraDirector::MyCallback()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("C++ Delay() is called."));
	}
	return;
}

// Called every frame
void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TimeToNextCameraChange -= DeltaTime;

	//if (TimeToNextCameraChange <= 0.0f)
	//{
	//	
	//	//��ȡ��ҵĿ�����
	//	APlayerController *playerController = UGameplayStatics::GetPlayerController(this, 0);
	//	if (playerController != nullptr)
	//	{
	//		if (playerController->GetViewTarget() != mCameras[0].cameraActor && mCameras[0].cameraActor != nullptr)
	//		{
	//			TimeToNextCameraChange += mCameras[0].TimeBetweenCameraChanges;
	//			//playerController->SetViewTargetWithBlend(mCameras[0].cameraActor, mCameras[0].TimeBlend);
	//			playerController->SetViewTargetWithBlend(
	//				static_cast<AJageProjectCharacter*>(playerController->GetCharacter())->ThirdPersonCameraActor->GetChildActor(),
	//				mCameras[0].TimeBlend);
	//		}
	//		//else if (playerController->GetViewTarget() != )
	//	}
	//}

}

