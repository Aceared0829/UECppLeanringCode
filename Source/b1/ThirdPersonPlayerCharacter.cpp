// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonPlayerCharacter.h"

#include <EnhancedInputComponent.h>
#include <Camera/CameraComponent.h>
#include <GameFramework/CharacterMovementComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/KismetSystemLibrary.h>

#include "HealthComponent.h"
#include "ThirdPersonPlayerController.h"

// Sets default values
AThirdPersonPlayerCharacter::AThirdPersonPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//创建第三人称摄像机组件
	ThirdPersonSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("ThirdPersonSpringArmComponent"));
	check(ThirdPersonSpringArmComponent);
	ThirdPersonSpringArmComponent->TargetArmLength = 250.0f;
	ThirdPersonSpringArmComponent->bUsePawnControlRotation = true;
	ThirdPersonSpringArmComponent->bInheritYaw = true;
	ThirdPersonSpringArmComponent->bInheritPitch = true;
	ThirdPersonSpringArmComponent->bInheritRoll = false;
	ThirdPersonSpringArmComponent->bAutoActivate = true;
	ThirdPersonSpringArmComponent->SetupAttachment(RootComponent);

	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCameraComponent"));
	check(ThirdPersonCameraComponent);
	ThirdPersonCameraComponent->bUsePawnControlRotation = false;
	ThirdPersonCameraComponent->FieldOfView = 90.0f;
	ThirdPersonCameraComponent->bAutoActivate = true;
	ThirdPersonCameraComponent->SetupAttachment(ThirdPersonSpringArmComponent, USpringArmComponent::SocketName);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	check(HealthComponent);
	HealthComponent->SetMaxHealth(100.0f); // 设置最大生命值为100
}

// Called when the game starts or when spawned
void AThirdPersonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThirdPersonPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AThirdPersonPlayerCharacter::SetupPlayerInputComponent (UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (TObjectPtr<UEnhancedInputComponent> PlayerEnhancedInputComponent = Cast<
		UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (MoveAction)
		{
			PlayerEnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this,
			                                         &AThirdPersonPlayerCharacter::Move);
		}
		if (LookAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this,
			                                         &AThirdPersonPlayerCharacter::Look);
		}
		if (JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
			                                         &AThirdPersonPlayerCharacter::JumpStart);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
			                                         &AThirdPersonPlayerCharacter::JumpEnd);
		}
	}
}

void AThirdPersonPlayerCharacter::Move (const FInputActionValue& Value)
{
	FVector2D MoveValue = Value.Get<FVector2D>();
	if (GetController() && MoveValue.IsZero() == false)
	{
		const FRotator ControllerRotation = GetController()->GetControlRotation();
		const FRotator YawRotation = FRotator(0.0f, ControllerRotation.Yaw, 0.0f);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MoveValue.Y);
		AddMovementInput(RightDirection, MoveValue.X);
	}
}

void AThirdPersonPlayerCharacter::Look (const FInputActionValue& Value)
{
		FVector2D LookValue = Value.Get<FVector2D>();
	if (GetController() && LookValue.IsZero() == false)
	{
		const FRotator ControllerRotation = GetController()->GetControlRotation();
		const float MouseX = LookValue.X * MouseSensitivity;
		const float MouseY = LookValue.Y * MouseSensitivity;
		AddControllerYawInput(MouseX);
		AddControllerPitchInput(MouseY);
	}
}

void AThirdPersonPlayerCharacter::JumpStart ()
{
	Jump();
}

void AThirdPersonPlayerCharacter::JumpEnd ()
{
	StopJumping();
}

void AThirdPersonPlayerCharacter::Damage_Implementation ()
{
	UE_LOG(LogTemp, Warning, TEXT("Damage called on %s"), *GetName());
}

void AThirdPersonPlayerCharacter::Heal_Implementation ()
{
	HealthComponent->TakeHeal(10.0f);
	UE_LOG(LogTemp, Warning, TEXT("Heal called on %s"), *GetName());
}

void AThirdPersonPlayerCharacter::Death_Implementation ()
{
	HealthComponent->Death();
	UE_LOG(LogTemp, Warning, TEXT("Death called on %s"), *GetName());
	if (TObjectPtr<AThirdPersonPlayerController> PlayerController = Cast<AThirdPersonPlayerController>(GetController()))
	{
		if (PlayerController)
		{
			PlayerController->ShowRestartWidget();
		}
	}
}

