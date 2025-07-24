// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RestartUserWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class B1_API URestartUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//��ʼ��
	virtual void NativeOnInitialized() override;
protected:
	//������Ϸ
	UFUNCTION(BlueprintCallable)
	void OnRestartButtonClicked();

	//�ر���Ϸ
	UFUNCTION(BlueprintCallable)
	void OnCloseButtonClicked();
};
