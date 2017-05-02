#include "stdafx.h"
#import "../ProxyGoogleEarth/Debug/ProxyGoogleEarth.tlb"

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);

	ProxyGoogleEarthLib::IGoogleEarthPtr proxy;

	auto hr = proxy.CreateInstance(__uuidof(ProxyGoogleEarthLib::GoogleEarth));
	if( S_OK == hr ) {
		try {
			double latitud, longitud;
			proxy->GetCoordenadas(&latitud, &longitud);

			hr = proxy->IrACoordenadas(latitud+0.001, longitud);
			MessageBox(NULL, L"Bien", L"Bien", MB_OK);
		} 
		catch(_com_error& e)
		{
			MessageBox(NULL, L"Mal", L"Mal", MB_OK);
		}
	} else {
		MessageBox(NULL, L"Mal", L"Mal", MB_OK);
	}

	return 0;
}

