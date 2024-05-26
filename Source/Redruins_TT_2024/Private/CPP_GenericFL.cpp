// RedRuins Softworks (c)


#include "CPP_GenericFL.h"

#include "GameFramework/ProjectileMovementComponent.h"

void UCPP_GenericFL::ResetProjectileMovement(UProjectileMovementComponent* _projectileMovementComponent, UPrimitiveComponent* _updateComponent, const FVector& _velocity)
{
	if(!_projectileMovementComponent||!_updateComponent)return;
	_projectileMovementComponent->SetUpdatedComponent(_updateComponent);
	_projectileMovementComponent->Velocity = _velocity;
	_projectileMovementComponent->UpdateComponentVelocity();
}
