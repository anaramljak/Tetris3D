// Fill out your copyright notice in the Description page of Project Settings.


#include "Camera.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACamera::ACamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
		PrimaryActorTick.bCanEverTick = true;
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
		USpringArmComponent* armComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
		armComponent->SetupAttachment(RootComponent);
		armComponent->SetRelativeLocationAndRotation(FVector(-1820.0f, 50.0f, 1020.0f), FRotator(0.0f, 0.0f, -720.0f));
		armComponent->TargetArmLength = 400.0f;
		armComponent->bEnableCameraLag = true;
		armComponent->CameraLagSpeed = 3.0f;
		armComponent->bDrawDebugLagMarkers = true;

		UCameraComponent* m_cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraMain"));
		m_cameraComponent->SetupAttachment(armComponent, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ACamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

