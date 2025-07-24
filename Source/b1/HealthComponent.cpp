// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include <GameFramework/GameSession.h>
#include <Kismet/GameplayStatics.h>

#include "HealthInterface.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	//�������ֵ
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth; // ��ʼ����ǰ����ֵΪ�������ֵ
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
		return; // ����˺���С�ڵ���0��ֱ�ӷ���
	}
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	if (GetOwner()->Implements<UHealthInterface>())
	{
		//���ýӿں�������˺�
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
		return; // ����ظ���С�ڵ���0��ֱ�ӷ���
	}
	if (CurrentHealth == 0)
	{
		Death(); // �����ǰ����ֵΪ0��ֱ�ӵ�����������
	}
	CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
	UE_LOG(LogTemp, Warning, TEXT("Current Health: %f"), CurrentHealth);
	if (GetOwner()->Implements<UHealthInterface>())
	{
		//���ýӿں����ظ�����
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
		//���ýӿں�������
		IHealthInterface::Execute_Death(GetOwner());
	}
}

void UHealthComponent::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0.0f, MaxHealth); // ȷ����ǰ����ֵ�������µ��������ֵ
	if (CurrentHealth == MaxHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("Health is full."));
	}
}

