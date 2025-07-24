// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HealthInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UHealthInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class B1_API IHealthInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//这么写可以在蓝图与C++中都能调用该接口
	//造成伤害
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void Damage();
	virtual void Damage_Implementation()=0;
	//回血
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void Heal();
	virtual void Heal_Implementation() = 0;
	//死亡
	UFUNCTION(BlueprintNativeEvent, Category = "Health")
	void Death();
	virtual void Death_Implementation() = 0;
};
