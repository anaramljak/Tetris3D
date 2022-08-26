#include "MyPawn.h"
#include "MyGameStateBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


void AMyPawn::SetupPlayerInputComponent(UInputComponent *ic)
{
	ic->BindAction("Left", IE_Pressed, this, &AMyPawn::left);
	ic->BindAction("Right", IE_Pressed, this, &AMyPawn::right);
	ic->BindAction("Rotate", IE_Pressed, this, &AMyPawn::rotate);
	ic->BindAction("Down", IE_Pressed, this, &AMyPawn::down);
}

auto AMyPawn::left() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("left"));
	getGameState()->left();
}
auto AMyPawn::right() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("right"));
	getGameState()->right();
}
auto AMyPawn::rotate() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("rotate"));
	getGameState()->rotate();
}
auto AMyPawn::down() -> void
{
	UE_LOG(LogTemp, Warning, TEXT("down"));
	getGameState()->down();
}

auto AMyPawn::getGameState() const -> AMyGameStateBase*
{
	return Cast<AMyGameStateBase>(GetWorld()->GetGameState());
}