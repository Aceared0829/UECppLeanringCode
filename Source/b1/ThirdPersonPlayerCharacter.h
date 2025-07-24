// �����˳�ģ���Զ���ʵ��

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

	//���������
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Camera)
	TObjectPtr<USpringArmComponent> ThirdPersonSpringArmComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = Camera)
	TObjectPtr<UCameraComponent> ThirdPersonCameraComponent;

	//����ֵ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Core")
	TObjectPtr<UHealthComponent> HealthComponent;

	//�ƶ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	//�ӽ��ƶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TObjectPtr<UInputAction> LookAction;
	//���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	float MouseSensitivity = 1.0f;
	//��Ծ����
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

	//�ӿ�ʵ�֡����������ʹ��
	virtual void Damage_Implementation() override;
	virtual void Heal_Implementation() override;
	virtual void Death_Implementation() override;

};
