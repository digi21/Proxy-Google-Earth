// ProxyGoogleEarth.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "ProxyGoogleEarth_i.h"



class CProxyGoogleEarthModule : public ATL::CAtlExeModuleT< CProxyGoogleEarthModule >
	{
public :
	DECLARE_LIBID(LIBID_ProxyGoogleEarthLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_PROXYGOOGLEEARTH, "{037B4494-7FA5-4E95-BA71-B2EDB1BE891A}")
	};

CProxyGoogleEarthModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

