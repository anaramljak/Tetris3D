#include "MyPawn.h"
#include "MyGameStateBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AMyPawn::AMyPawn() 
{
}

auto AMyPawn::SetupPlayerInputComponent(UInputComponent *in) -> void
{
	in->BindAction("Left", IE_Pressed, this, &AMyPawn::left);
	in->BindAction("Right", IE_Pressed, this, &AMyPawn::right);
	in->BindAction("Rotate", IE_Pressed, this, &AMyPawn::rotate);
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

auto AMyPawn::getGameState() const -> AMyGameStateBase*
{
	return Cast<AMyGameStateBase>(GetWorld()->GetGameState());
}