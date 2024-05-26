// RedRuins Softworks (c)


#include "Markers/CPP_MarkerComponent.h"

#include "GameFramework/GameStateBase.h"
#include "Markers/CPP_MarkerManager.h"


void UCPP_MarkerComponent::GetScreenLocationForMarker(APlayerController* _playerController, const float _edgePercent,
                                                      const FVector2D _viewportCenterLoc, FVector2D& _outScreenPosition, float& _outRotationAngleDegrees, bool& _bIsOnScreen)
{
	_bIsOnScreen = false;
	_outRotationAngleDegrees = 0.f;
	FVector2D ScreenPosition = FVector2D();

	if (!_playerController)return;


	const FVector2D ViewportSize = FVector2D(GEngine->GameViewport->Viewport->GetSizeXY());
	const FVector2D ViewportCenter = FVector2D(ViewportSize.X * _viewportCenterLoc.X, ViewportSize.Y * _viewportCenterLoc.Y);

	FVector CameraLoc;
	FRotator CameraRot;

	_playerController->GetPlayerViewPoint(CameraLoc, CameraRot);

	const FVector CameraToLoc = GetComponentLocation() - CameraLoc;
	FVector Forward = CameraRot.Vector();
	FVector Offset = CameraToLoc.GetSafeNormal();

	float DotProduct = FVector::DotProduct(Forward, Offset);
	bool bLocationIsBehindCamera = (DotProduct < 0);

	if (bLocationIsBehindCamera)
	{
		FVector Inverted = CameraToLoc * -1.f;
		FVector NewInLocation = CameraLoc + Inverted;

		_playerController->ProjectWorldLocationToScreen(NewInLocation, ScreenPosition);

		ScreenPosition.X = ViewportSize.X - ScreenPosition.X;
		ScreenPosition.Y = ViewportSize.Y - ScreenPosition.Y;
	}
	else
	{
		_playerController->ProjectWorldLocationToScreen(GetComponentLocation(), ScreenPosition);
	}

	// Check to see if it's on screen. If it is, ProjectWorldLocationToScreen is all we need, return it.
	if (ScreenPosition.X - ViewportSize.X * (1 - _edgePercent) / 2 >= 0.f && ScreenPosition.X + ViewportSize.X * (1 - _edgePercent) / 2 <= ViewportSize.X
		&& ScreenPosition.Y - ViewportSize.Y * (1 - _edgePercent) / 2 >= 0.f && ScreenPosition.Y + ViewportSize.Y * (1 - _edgePercent) / 2 <= ViewportSize.Y && !
		bLocationIsBehindCamera)
	{
		_outScreenPosition = ScreenPosition;
		_bIsOnScreen = true;
		return;
	}

	ScreenPosition -= ViewportCenter;

	float AngleRadians = FMath::Atan2(ScreenPosition.Y, ScreenPosition.X);
	AngleRadians -= FMath::DegreesToRadians(90.f);

	_outRotationAngleDegrees = FMath::RadiansToDegrees(AngleRadians) + 180.f;

	float Cos = cosf(AngleRadians);
	float Sin = -sinf(AngleRadians);

	ScreenPosition = FVector2D(ViewportCenter.X + (Sin * 150.f), ViewportCenter.Y + Cos * 150.f);

	float m = Cos / Sin;

	FVector2D ScreenBounds = ViewportCenter * _edgePercent;

	if (Cos > 0)
	{
		ScreenPosition = FVector2D(ScreenBounds.Y / m, ScreenBounds.Y);
	}
	else
	{
		ScreenPosition = FVector2D(-ScreenBounds.Y / m, -ScreenBounds.Y);
	}

	if (ScreenPosition.X > ScreenBounds.X)
	{
		ScreenPosition = FVector2D(ScreenBounds.X, ScreenBounds.X * m);
	}
	else if (ScreenPosition.X < -ScreenBounds.X)
	{
		ScreenPosition = FVector2D(-ScreenBounds.X, -ScreenBounds.X * m);
	}

	ScreenPosition += ViewportCenter;

	_outScreenPosition = ScreenPosition;
}

void UCPP_MarkerComponent::Activate(bool bReset)
{
	if (!GetWorld() || !GetWorld()->GetGameState())return;
	if (!MarkerManager)
	{
		MarkerManager = GetWorld()->GetGameState()->GetComponentByClass<UCPP_MarkerManager>();
		if (!MarkerManager)
		{
			MarkerManager = Cast<UCPP_MarkerManager>(GetWorld()->GetGameState()->AddComponentByClass(UCPP_MarkerManager::StaticClass(), false, FTransform::Identity, false));
		}
	}
	if (!MarkerManager)return;

	MarkerManager->AddMarker(this);
}

void UCPP_MarkerComponent::Deactivate()
{
	if (!MarkerManager)return;
	MarkerManager->RemoveMarker(this);
}
