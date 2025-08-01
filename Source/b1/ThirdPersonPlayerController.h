// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ThirdPersonPlayerController.generated.h"

class URestartUserWidget;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class B1_API AThirdPersonPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TArray<UInputMappingContext*> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
	TSubclassOf<URestartUserWidget> RestartWidgetClass;

	//��ʾ����UI
	void ShowRestartWidget();
	//��������UI
	void HideRestartWidget();

private:
	UPROPERTY()
	TObjectPtr<URestartUserWidget> RestartUserWidget;
};
