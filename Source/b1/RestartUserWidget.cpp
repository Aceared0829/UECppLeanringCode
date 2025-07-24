// Fill out your copyright notice in the Description page of Project Settings.


#include "RestartUserWidget.h"

#include <Components/Button.h>
#include <Kismet/GameplayStatics.h>

#include "ThirdPersonPlayerController.h"

void URestartUserWidget::NativeOnInitialized ()
{
	Super::NativeOnInitialized();
}

void URestartUserWidget::OnRestartButtonClicked ()
{
	if(TObjectPtr<AThirdPersonPlayerController> PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		//如果存在重启UI则隐藏
		PlayerController->HideRestartWidget();
	}
	UGameplayStatics::OpenLevel(this, FName(*UGameplayStatics::GetCurrentLevelName(this)));
}

void URestartUserWidget::OnCloseButtonClicked ()
{
	if (AThirdPersonPlayerController* PlayerController = Cast<AThirdPersonPlayerController>(GetOwningPlayer()))
	{
		UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
	}
}
