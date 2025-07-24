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
		SetPause(true);//暂停游戏
		SetInputMode(FInputModeUIOnly());//设置输入模式为UI模式
		bShowMouseCursor = true;//显示鼠标光标
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
		SetPause(false);//取消暂停游戏
		SetInputMode(FInputModeGameOnly());//设置输入模式为游戏模式
		bShowMouseCursor = false;//隐藏鼠标光标
	}
}
