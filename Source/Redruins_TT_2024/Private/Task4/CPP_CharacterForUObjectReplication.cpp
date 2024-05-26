// RedRuins Softworks (c)


#include "Task4/CPP_CharacterForUObjectReplication.h"
#include "Task4/CPP_ReplicatedObject.h"
#include "Engine/ActorChannel.h"
#include "Net/UnrealNetwork.h"


bool ACPP_CharacterForUObjectReplication::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	bWroteSomething |= Channel->ReplicateSubobject(ReplicatedObject, *Bunch, *RepFlags);
	return bWroteSomething;
}

void ACPP_CharacterForUObjectReplication::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACPP_CharacterForUObjectReplication, ReplicatedObject);
}
