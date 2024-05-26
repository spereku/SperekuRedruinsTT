// RedRuins Softworks (c)


#include "Interaction/CPP_InteractionComponent.h"

#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"
#include "Interaction/CPP_InteractionInterface.h"
#include "Kismet/KismetSystemLibrary.h"


UCPP_InteractionComponent::UCPP_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UCPP_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (!ownerPawn)return;
	if (APlayerController* pc = Cast<APlayerController>(ownerPawn->GetOwner()))OwnerPlayerController = pc;

	ownerPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UCPP_InteractionComponent::OwnerPawn_ReceiveControllerChanged);

	if (HoverWidgetClass)
	{
		HoverWidgetActor = GetWorld()->SpawnActor<AActor>();
		UWidgetComponent* hoverWidgetComponent = Cast<UWidgetComponent>(HoverWidgetActor->AddComponentByClass(UWidgetComponent::StaticClass(), false, FTransform::Identity, false));
		if (hoverWidgetComponent)
		{
			hoverWidgetComponent->SetDrawAtDesiredSize(true);
			hoverWidgetComponent->SetWidgetClass(HoverWidgetClass);
			hoverWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		}
		HoverWidgetActor->SetActorHiddenInGame(true);
		HoverWidgetActor->SetActorEnableCollision(false);
	}
}

void UCPP_InteractionComponent::TickComponent(float _deltaTime, ELevelTick _tickType, FActorComponentTickFunction* _thisTickFunction)
{
	Super::TickComponent(_deltaTime, _tickType, _thisTickFunction);
	UpdateHoveredActor();
}

void UCPP_InteractionComponent::Deactivate()
{
	Super::Deactivate();
	UpdateHoveredActor();
}

void UCPP_InteractionComponent::OwnerPawn_ReceiveControllerChanged(APawn* _pawn, AController* _oldController, AController* _newController)
{
	OwnerPlayerController = Cast<APlayerController>(_newController);
}

void UCPP_InteractionComponent::UpdateHoveredActor()
{
	AActor* newHoveredActor = nullptr;
	if (IsActive() && OwnerPlayerController && OwnerPlayerController->PlayerCameraManager)
	{
		FHitResult cameraOutHit;
		const FVector traceEnd = OwnerPlayerController->PlayerCameraManager->GetCameraLocation() +
			OwnerPlayerController->PlayerCameraManager->GetCameraRotation().Vector() * TraceDistanceFromCamera;


		UKismetSystemLibrary::LineTraceSingle(GetWorld(), OwnerPlayerController->PlayerCameraManager->GetCameraLocation(), traceEnd, UEngineTypes::ConvertToTraceType(TraceChannel),
		                                      true, TArray<AActor*>(), EDrawDebugTrace::None, cameraOutHit, false);
		if (cameraOutHit.GetActor() && cameraOutHit.GetActor()->Implements<UCPP_InteractionInterface>())
		{
			if (ICPP_InteractionInterface::Execute_CanInteract(cameraOutHit.GetActor(), this))
			{
				FVector pawnEyeLocation;
				FRotator pawnEyeRotation;
				OwnerPlayerController->GetPawn()->GetActorEyesViewPoint(pawnEyeLocation, pawnEyeRotation);
				if (FVector::Distance(pawnEyeLocation, cameraOutHit.ImpactPoint) < InteractionDistanceFromPawn)
				{
					FHitResult pawnOutHit;
					UKismetSystemLibrary::LineTraceSingle(GetOwner(), pawnEyeLocation, pawnEyeLocation + (cameraOutHit.ImpactPoint - pawnEyeLocation) * 1.1f
					                                      , UEngineTypes::ConvertToTraceType(TraceChannel), true, TArray<AActor*>(), EDrawDebugTrace::None, pawnOutHit, true);
					if (pawnOutHit.GetActor() == cameraOutHit.GetActor())newHoveredActor = cameraOutHit.GetActor();
				}
			}
		}
	}
	if (HoverWidgetActor)
	{
		HoverWidgetActor->SetActorHiddenInGame(newHoveredActor == nullptr);
		if (newHoveredActor)
		{
			HoverWidgetActor->SetActorLocation(ICPP_InteractionInterface::Execute_GetInteractionWidgetOffset(newHoveredActor, this) + newHoveredActor->GetActorLocation());
		}
	}
	HoveredActor = newHoveredActor;
}

void UCPP_InteractionComponent::Interact()
{
	UpdateHoveredActor();
	if (HoveredActor)ICPP_InteractionInterface::Execute_Interact(HoveredActor, this);
}
