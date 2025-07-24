// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPlayerController.h"

#include <EnhancedInputSubsystems.h>
#include <InputMappingContext.h>

#include "RestartUserWidget.h"

void AThirdPersonPlayerController::BeginPlay ()
{
	Super::BeginPlay();
	if (const TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(GetLocalPlayer()))
	{
		if (const TObjectPtr<UEnhancedInputLocalPlayerSubsystem> InputSubsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			for (const UInputMappingContext* Context : InputMappingContexts)
			{
				InputSubsystem->AddMappingContext(Context, 0);
			}
		}
	}
}

void AThirdPersonPlayerController::ShowRestartWidget ()
{
	if (RestartWidgetClass)
	{
		SetPause(true);//��ͣ��Ϸ
		SetInputMode(FInputModeUIOnly());//��������ģʽΪUIģʽ
		bShowMouseCursor = true;//��ʾ�����
		RestartUserWidget = CreateWidget<URestartUserWidget>(this, RestartWidgetClass);
		RestartUserWidget->AddToViewport();

	}
}

void AThirdPersonPlayerController::HideRestartWidget ()
{
	if (RestartWidgetClass)
	{
		RestartUserWidget->RemoveFromParent();
		RestartUserWidget->Destruct();
		SetPause(false);//ȡ����ͣ��Ϸ
		SetInputMode(FInputModeGameOnly());//��������ģʽΪ��Ϸģʽ
		bShowMouseCursor = false;//���������
	}
}
