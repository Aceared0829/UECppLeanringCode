// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include <GameFramework/GameSession.h>
#include <Kismet/GameplayStatics.h>

#include "HealthInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//最大生命值
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth; // 初始化当前生命值为最大生命值
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage (float DamageAmount)
{
	if (DamageAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage amount must be positive."));
		return; // 如果伤害量小于等于0，直接返回
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	if (GetOwner()->Implements<UHealthInterface>())
	{
		//调用接口函数造成伤害
		IHealthInterface::Execute_Damage(GetOwner());
	}
	if (CurrentHealth == 0)
	{
		if (GetOwner()->Implements<UHealthInterface>())
		{
			IHealthInterface::Execute_Death(GetOwner());
		}
	}
}

void UHealthComponent::TakeHeal (float HealAmount)
{
	if (HealAmount <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Heal amount must be positive."));
		return; // 如果回复量小于等于0，直接返回
	}
	if (CurrentHealth == 0)
	{
		Death(); // 如果当前生命值为0，直接调用死亡函数
	}
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	if (GetOwner()->Implements<UHealthInterface>())
	{
		//调用接口函数回复生命
		IHealthInterface::Execute_Heal(GetOwner());
	}
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

void UHealthComponent::Death () const
{
	UE_LOG(LogTemp, Warning, TEXT("Character is dead!"));
	if (GetOwner()->Implements<UHealthInterface>())
	{
		//调用接口函数死亡
		IHealthInterface::Execute_Death(GetOwner());
	}
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth); // 确保当前生命值不超过新的最大生命值
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

