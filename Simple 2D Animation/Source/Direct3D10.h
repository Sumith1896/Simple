#include <d3d10.h>
#include <d3dx10.h>

//////////////////////////////////////////////////////////////////////////
// Direct3D 10 Global Variables
//////////////////////////////////////////////////////////////////////////
static D3D10_DRIVER_TYPE       g_driverType			= D3D10_DRIVER_TYPE_NULL;	// A NULL device; which is a reference 
static ID3D10Device*           g_pd3dDevice			= NULL;						// D3D10 device interface
static LPD3DX10SPRITE		   g_pd3dSprite			= NULL; 
static IDXGISwapChain*         g_pSwapChain			= NULL;						// An IDXGISwapChain interface implements 
static ID3D10RenderTargetView* g_pRenderTargetView	= NULL;						// A render-target-view interface identifies the 

//////////////////////////////////////////////////////////////////////////
// Create Direct3D device and swap chain
//////////////////////////////////////////////////////////////////////////
static HRESULT InitDevice(HWND hWnd)
{
	HRESULT hr = S_OK;;
	RECT rc;
	GetClientRect( hWnd, &rc );
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;
	UINT createDeviceFlags = 0;

#ifdef _DEBUG
	createDeviceFlags |= D3D10_CREATE_DEVICE_DEBUG;
#endif


	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof(sd) );

	sd.BufferCount							= 1;
	sd.BufferDesc.Width						= width;
	sd.BufferDesc.Height					= height;
	sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.RefreshRate.Numerator		= 60;   
	sd.BufferDesc.RefreshRate.Denominator	= 1;
	sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow							= hWnd;
	sd.SampleDesc.Count						= 1;
	sd.SampleDesc.Quality					= 0;
	sd.SwapEffect							= DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed								= TRUE;

	// Create an array of 2 types of devices - Hardware and software
	D3D10_DRIVER_TYPE driverTypes[] = 
	{
		D3D10_DRIVER_TYPE_HARDWARE,
		D3D10_DRIVER_TYPE_REFERENCE,
	};

	UINT numDriverTypes = sizeof(driverTypes) / sizeof(driverTypes[0]);

	// Iterate over the array and see which one works?
	for( UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++ ) 
	{
		g_driverType = driverTypes[driverTypeIndex];
		
		//attempt to create the device and swap chain
		hr = D3D10CreateDeviceAndSwapChain
			( 
			NULL, 
			g_driverType, 
			NULL, 
			createDeviceFlags, 
			D3D10_SDK_VERSION, 
			&sd, 
			&g_pSwapChain, 
			&g_pd3dDevice 
			);

		if( SUCCEEDED( hr ) )
		{
			break;
		}
		else 
		{
			MessageBox(hWnd, TEXT("A DX10 Compliant Video Card is not Available"), TEXT("ERROR"), MB_OK);
		}
	}

	if( FAILED(hr) )
	{
		return hr;
	}


	// Create a render target view
	ID3D10Texture2D *pBackBuffer;
	hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer );

	if( FAILED(hr) )
	{
		return hr;
	}

	hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, &g_pRenderTargetView );
	pBackBuffer->Release();

	if( FAILED(hr) )
	{
		return hr;
	}

	// set the render target
	g_pd3dDevice->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );

	// Setup the viewport
	D3D10_VIEWPORT vp;
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	g_pd3dDevice->RSSetViewports( 1, &vp );

	//create the sprite interface with room for 4096 sprites
	D3DX10CreateSprite(g_pd3dDevice, 0, &g_pd3dSprite);

	return S_OK;
}


static void Render()
{
	// Just clear the backbuffer
	g_pd3dDevice->ClearRenderTargetView( g_pRenderTargetView, D3DXCOLOR(0.2f, 0.3f, 1.0f, 0.0f) );
	g_pSwapChain->Present( 0, 0 );
}


static void CleanupDevice()
{
	if( g_pd3dDevice ) g_pd3dDevice->ClearState();

	if( g_pRenderTargetView ) g_pRenderTargetView->Release();
	if( g_pSwapChain ) g_pSwapChain->Release();
	if( g_pd3dDevice ) g_pd3dDevice->Release();
	if( g_pd3dSprite ) g_pd3dSprite->Release();
}