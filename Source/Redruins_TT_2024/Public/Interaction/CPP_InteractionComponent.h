// RedRuins Softworks (c)

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CPP_InteractionComponent.generated.h"


class USphereComponent;
class ICPP_InteractionInterface;
class UUserWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class REDRUINS_TT_2024_API UCPP_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCPP_InteractionComponent();

	UFUNCTION(BlueprintCallable, Category="Interaction")
	void Interact();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction) override;
	virtual void Deactivate() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<UUserWidget> HoverWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TEnumAsByte<ECollisionChannel> TraceChannel = ECC_Visibility;

	UPROPERTY(EditDefaultsOnly, Category="Settings", meta=(ClampMin=0, UIMin=0, Units="Centimeters"))
	float InteractionDistanceFromPawn = 200;

	UPROPERTY(EditDefaultsOnly, Category="Settings", meta=(ClampMin=0, UIMin=0, Units="Centimeters"))
	float TraceDistanceFromCamera = 500;

	void UpdateHoveredActor();

	UFUNCTION()
	void OwnerPawn_ReceiveControllerChanged(APawn* _pawn, AController* _oldController, AController* _newController);

	UPROPERTY(Transient)
	TObjectPtr<AActor> HoveredActor;

	UPROPERTY(Transient)
	TObjectPtr<APlayerController> OwnerPlayerController;

	UPROPERTY(Transient)
	TObjectPtr<AActor> HoverWidgetActor;
};
