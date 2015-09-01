#include "stdafx.h"
#include "GoogleEarth.h"


STDMETHODIMP CGoogleEarth::IrACoordenadas(DOUBLE latitud, DOUBLE longitud)
{
	if( googleEarth == NULL ) {
		auto hr = googleEarth.CreateInstance(__uuidof(EARTHLib::ApplicationGE));
		if( S_OK != hr )
			return hr;
	}

	googleEarth->SetCameraParams(
		latitud, 
		longitud, 
		0.0, 
		EARTHLib::RelativeToGroundAltitudeGE, 
		googleEarth->GetCamera(TRUE)->Range, 
		0.0, 
		0.0, 
		1.0);

	return S_OK;
}

STDMETHODIMP CGoogleEarth::GetCoordenadas(DOUBLE* latitud, DOUBLE* longitud)
{
	if( googleEarth == NULL ) {
		auto hr = googleEarth.CreateInstance(__uuidof(EARTHLib::ApplicationGE));
		if( S_OK != hr )
			return hr;
	}

	auto camara = googleEarth->GetCamera(TRUE);
	*latitud = camara->FocusPointLatitude;
	*longitud = camara->FocusPointLongitude;

	return S_OK;
}
