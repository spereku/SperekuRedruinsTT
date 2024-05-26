// RedRuins Softworks (c)


#include "Markers/CPP_MarkerManager.h"


void UCPP_MarkerManager::AddMarker(UCPP_MarkerComponent* _marker)
{
	if (!_marker || Markers.Contains(_marker))return;
	Markers.Add(_marker);
	OnMarkersChanged.Broadcast();
}

void UCPP_MarkerManager::RemoveMarker(UCPP_MarkerComponent* _marker)
{
	if (!_marker || !Markers.Contains(_marker))return;
	Markers.Remove(_marker);
	OnMarkersChanged.Broadcast();
}
