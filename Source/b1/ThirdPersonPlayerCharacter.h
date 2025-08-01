// 第三人称模板自定义实现

#pragma once

#include "CoreMinimal.h"
#include "HealthInterface.h"
#include "GameFramework/Character.h"
#include "ThirdPersonPlayerCharacter.generated.h"

class UHealthComponent;
struct FInputActionValue;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class B1_API AThirdPersonPlayerCharacter : public ACharacter,public IHealthInterface
{
	GENERATED_BODY()

public:
	AThirdPersonPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//摄像机设置
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Camera)
	TObjectPtr<USpringArmComponent> ThirdPersonSpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Camera)
	TObjectPtr<UCameraComponent> ThirdPersonCameraComponent;

	//生命值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UHealthComponent> HealthComponent;

	//移动操作
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	//视角移动
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;
	//鼠标灵敏度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float MouseSensitivity = 1.0f;
	//跳跃操作
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UFUNCTION(BlueprintCallable)
	void Move(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable)
	void JumpStart();

	UFUNCTION(BlueprintCallable)
	void JumpEnd();

	//接口实现、与组件搭配使用
	virtual void Damage_Implementation() override;
	virtual void Heal_Implementation() override;
	virtual void Death_Implementation() override;

};
