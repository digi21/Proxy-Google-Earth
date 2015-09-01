// GoogleEarth.h : Declaration of the CGoogleEarth

#pragma once
#include "resource.h"       // main symbols



#include "ProxyGoogleEarth_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CGoogleEarth

class ATL_NO_VTABLE CGoogleEarth :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CGoogleEarth, &CLSID_GoogleEarth>,
	public IDispatchImpl<IGoogleEarth, &IID_IGoogleEarth, &LIBID_ProxyGoogleEarthLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	EARTHLib::IApplicationGEPtr googleEarth;

public:
	CGoogleEarth()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_GOOGLEEARTH)


BEGIN_COM_MAP(CGoogleEarth)
	COM_INTERFACE_ENTRY(IGoogleEarth)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



	STDMETHOD(IrACoordenadas)(DOUBLE latitud, DOUBLE longitud);
	STDMETHOD(GetCoordenadas)(DOUBLE* latitud, DOUBLE* longitud);
};

OBJECT_ENTRY_AUTO(__uuidof(GoogleEarth), CGoogleEarth)
