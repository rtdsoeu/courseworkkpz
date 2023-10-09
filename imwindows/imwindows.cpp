#include "imwindows.hpp"

bool ImWindows::createDeviceD3D(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0,};
    if (D3D11CreateDeviceAndSwapChain(nullptr,
                                      D3D_DRIVER_TYPE_HARDWARE,
                                      nullptr,
                                      createDeviceFlags,
                                      featureLevelArray,
                                      2,
                                      D3D11_SDK_VERSION,
                                      &sd,
                                      &d3dSwapChain,
                                      &d3dDevice,
                                      &featureLevel,
                                      &d3dDeviceContext) != S_OK)
        return false;

    createRenderTarget();
    return true;
}

void ImWindows::createRenderTarget() {
    ID3D11Texture2D *pBackBuffer;
    d3dSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    d3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &d3dMainRenderTargetView);
    pBackBuffer->Release();
}

void ImWindows::cleanupDeviceD3D() {
    cleanupRenderTarget();
    if (d3dSwapChain) {
        d3dSwapChain->Release();
        d3dSwapChain = nullptr;
    }
    if (d3dDeviceContext) {
        d3dDeviceContext->Release();
        d3dDeviceContext = nullptr;
    }
    if (d3dDevice) {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }
}

void ImWindows::cleanupRenderTarget() {
    if (d3dMainRenderTargetView) {
        d3dMainRenderTargetView->Release();
        d3dMainRenderTargetView = nullptr;
    }
}

LRESULT WINAPI ImWindows::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return 1;
    switch (msg) {
        case WM_SIZE:
            if (d3dDevice != nullptr && wParam != SIZE_MINIMIZED) {
                cleanupRenderTarget();
                d3dSwapChain->ResizeBuffers(0, (UINT) LOWORD(lParam), (UINT) HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
                createRenderTarget();
            }
            return 0;
        case WM_SYSCOMMAND:
            if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
                return 0;
            break;
        case WM_DESTROY:
            ::PostQuitMessage(0);
            return 0;
    }
    return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

ImWindows::ImWindows(LPCWSTR name, LPCWSTR className, HINSTANCE hInstance) {
    windowClass = {
            sizeof(windowClass), CS_CLASSDC, WndProc, 0L, 0L, hInstance,
            LoadIcon(hInstance, L"IDI_ICON1"), nullptr, nullptr,
            nullptr,
            className, nullptr};

    ::RegisterClassEx(&windowClass);
    mainWindow = ::CreateWindow(windowClass.lpszClassName,
                                name,
                                WS_OVERLAPPEDWINDOW,
                                100,
                                100,
                                720,
                                400,
                                nullptr,
                                nullptr,
                                windowClass.hInstance,
                                nullptr);
    if (!createDeviceD3D(mainWindow)) {
        cleanupDeviceD3D();
        ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
        assert("CANNOT CREATE D3DDEVICE");
    }
    ::ShowWindow(mainWindow, SW_SHOWDEFAULT);
    ::UpdateWindow(mainWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImFontConfig fconf;
    fconf.OversampleH = 4;

    io.Fonts->AddFontFromFileTTF(R"(C:\Windows\Fonts\trebuc.ttf)",
                                 14.0f,
                                 &fconf,
                                 io.Fonts->GetGlyphRangesCyrillic());

    ImGui::StyleColorsLight();

    ImGui_ImplWin32_Init(mainWindow);
    ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);
}

ImWindows::~ImWindows() {
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    cleanupDeviceD3D();
    ::DestroyWindow(mainWindow);
    ::UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

void ImWindows::mainloop() {
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    constexpr ImGuiWindowFlags
            flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings;
    const auto viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);

    ImGui::Begin("Main", nullptr, flags);
    {
        ImGui::BeginChild("Navigation", {viewport->WorkSize.x / 4, -1}, true);
        {
            for (int i = 0; i < items.size(); ++i) {
                static bool color_pushed{false};
                if (currentItem == i) {
                    ImVec4 col{ImGui::GetStyleColorVec4(ImGuiCol_Button)};
                    col.w = 0.8f;
                    ImGui::PushStyleColor(ImGuiCol_Button, col);
                    color_pushed = true;
                }
                if (ImGui::Button(items[i].menu, {-1, 30})) {
                    currentItem = i;
                }
                if (color_pushed) {
                    ImGui::PopStyleColor(1);
                    color_pushed = false;
                }
            }
        }
        ImGui::EndChild();
        ImGui::SameLine();
        ImGui::BeginChild("Body", {-1, -1}, true);
        {
            items[currentItem].body();
        }
        ImGui::EndChild();
    }
    ImGui::End();

    ImGui::Render();

    d3dDeviceContext->OMSetRenderTargets(1, &d3dMainRenderTargetView, nullptr);
    constexpr static float clearColor[4]{0.f, 0.f, 0.f, 0.f};
    d3dDeviceContext->ClearRenderTargetView(d3dMainRenderTargetView, clearColor);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    d3dSwapChain->Present(1, 0);
}

void ImWindows::addItem(const Item &item) {
    items.push_back(item);
}
