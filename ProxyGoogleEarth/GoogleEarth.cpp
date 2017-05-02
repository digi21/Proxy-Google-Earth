#include "stdafx.h"
#include "GoogleEarth.h"

STDMETHODIMP CGoogleEarth::IrACoordenadas(DOUBLE latitud, DOUBLE longitud)
{
	IDispatchPtr dispatch;
	auto hr = dispatch.CreateInstance(__uuidof(EARTHLib::ApplicationGE));

	IDispatchPtr camara;
	hr = GetCamara(dispatch, camara);
	if (FAILED(hr))
		return hr;

	double rango;
	hr = GetPropiedadDouble(camara, L"Range", rango);
	if (FAILED(hr))
		return hr;

	LPOLESTR nombreMetodoSetCameraParams = L"SetCameraParams";
	DISPID dispIdSetCameraParams;
	hr = dispatch->GetIDsOfNames(
		IID_NULL,
		&nombreMetodoSetCameraParams,
		1,
		LOCALE_USER_DEFAULT,
		&dispIdSetCameraParams);
	if (FAILED(hr))
		return hr;

	DISPPARAMS dispparams;
	ZeroMemory(&dispparams, sizeof(dispparams));
	dispparams.cArgs = 8;

	std::unique_ptr<VARIANTARG[]> argumentos(new VARIANTARG[8]);
	dispparams.rgvarg = argumentos.get();
	ZeroMemory(argumentos.get(), 8 * sizeof(VARIANTARG));
	argumentos[7] = _variant_t(latitud);
	argumentos[6] = _variant_t(longitud);
	argumentos[5] = _variant_t(0.0);
	argumentos[4] = _variant_t(1);		// EARTHLib::RelativeToGroundAltitudeGE
	argumentos[3] = _variant_t(rango);
	argumentos[2] = _variant_t(0.0);
	argumentos[1] = _variant_t(0.0);
	argumentos[0] = _variant_t(1.0);

	EXCEPINFO exceptInfo;
	UINT argErr;

	hr = dispatch->Invoke(
		dispIdSetCameraParams,
		IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,
		&dispparams,
		nullptr,
		&exceptInfo,
		&argErr);

	return hr;
}

STDMETHODIMP CGoogleEarth::GetCamara(IDispatchPtr aplicacion, IDispatchPtr& camara)
{
	LPOLESTR nombreMetodoGetCamera = L"GetCamera";
	DISPID dispIdGetCamera;
	auto hr = aplicacion->GetIDsOfNames(
		IID_NULL,
		&nombreMetodoGetCamera,
		1,
		LOCALE_USER_DEFAULT,
		&dispIdGetCamera);
	if (FAILED(hr))
		return hr;

	DISPPARAMS dispparams;
	ZeroMemory(&dispparams, sizeof(dispparams));
	dispparams.cArgs = 1;

	std::unique_ptr<VARIANTARG[]> argumentos(new VARIANTARG[1]);
	dispparams.rgvarg = argumentos.get();
	ZeroMemory(argumentos.get(), sizeof(VARIANTARG));
	argumentos[0] = _variant_t(true);

	VARIANTARG pvRet;
	VariantInit(&pvRet);

	EXCEPINFO exceptInfo;
	UINT argErr;

	hr = aplicacion->Invoke(dispIdGetCamera,
		IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_METHOD,
		&dispparams,
		&pvRet,
		&exceptInfo,
		&argErr);
	if (FAILED(hr))
		return hr;

	camara = pvRet;
	camara->Release();
	return S_OK;
}

STDMETHODIMP CGoogleEarth::GetCoordenadas(DOUBLE* latitud, DOUBLE* longitud)
{
	// Esto antes era así:
	//
	//	EARTHLib::IApplicationGEPtr googleEarth = dispatch;
	//	hr = googleEarth.CreateInstance(__uuidof(EARTHLib::ApplicationGE));
	//	if (S_OK != hr)
	//		return hr;
	//
	//	auto camara = googleEarth->GetCamera(TRUE);
	//
	//	*latitud = camara->FocusPointLatitude;
	//  *longitud = camara->FocusPointLongitude;
	//
	// Pero parece que en las últimas versiones de Google Earth han hecho que los objetos únicamente implementen el interfaz IDispatch, de manera que únicamente se puede acceder
	// a los objetos mediante automatización.
	//
	// Lo he averiguado mediante el siguiente código que enumera los métodos soportados por un objeto:
	//
	//		IDispatchPtr camara = pvRet;
	//		UINT cuenta = 0;
	//		camara->GetTypeInfoCount(&cuenta);

	//		if (cuenta) {
	//			ITypeInfo* typeInfo;
	//			camara->GetTypeInfo(0, 0, &typeInfo);
	//
	//		for (int i = 0;; i++) {
	//			FUNCDESC* pfundesc;
	//			typeInfo->GetFuncDesc(i, &pfundesc);
	//			auto idMember = pfundesc->memid;
	//			BSTR bstrName;
	//			typeInfo->GetDocumentation(idMember, &bstrName, NULL, NULL, NULL);
	//			typeInfo->ReleaseFuncDesc(pfundesc);
	//		}
	//
	//
	IDispatchPtr dispatch;
	auto hr = dispatch.CreateInstance(__uuidof(EARTHLib::ApplicationGE));
	if (FAILED(hr))
		return hr;

	IDispatchPtr camara;
	hr = GetCamara(dispatch, camara);
	if (FAILED(hr))
		return hr;

	hr = GetPropiedadDouble(camara, L"FocusPointLatitude", *latitud);
	if (FAILED(hr))
		return hr;

	hr = GetPropiedadDouble(camara, L"FocusPointLongitude", *longitud);
	if (FAILED(hr))
		return hr;

	return S_OK;
}

STDMETHODIMP CGoogleEarth::GetPropiedadDouble(IDispatchPtr camara, LPOLESTR nombrePropiedad, DOUBLE& resultado)
{
	DISPID dispId;

	auto hr = camara->GetIDsOfNames(
		IID_NULL,
		&nombrePropiedad,
		1,
		LOCALE_USER_DEFAULT, &dispId);
	if (FAILED(hr))
		return hr;

	DISPPARAMS dispparams;
	ZeroMemory(&dispparams, sizeof(dispparams));
	dispparams.cArgs = 0;

	EXCEPINFO exceptInfo;
	UINT argErr;
	VARIANTARG pvRet;

	VariantInit(&pvRet);
	hr = camara->Invoke(
		dispId,
		IID_NULL,
		LOCALE_USER_DEFAULT,
		DISPATCH_PROPERTYGET,
		&dispparams,
		&pvRet,
		&exceptInfo,
		&argErr);
	if (FAILED(hr))
		return hr;

	resultado = pvRet.dblVal;

	return S_OK;
}
