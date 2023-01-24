#pragma once

#include <Windows.h>
#include <d3d11.h>
#include <functional>

#pragma comment(lib, "d3d11.lib")

#include "../imguiaddons/imguidatechooser.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ImWindows {
public:
    struct Item {
        const char *menu;
        std::function<void()> body;
    };
private:
    inline static ID3D11Device *d3dDevice{nullptr};
    inline static ID3D11DeviceContext *d3dDeviceContext{nullptr};
    inline static IDXGISwapChain *d3dSwapChain{nullptr};
    inline static ID3D11RenderTargetView *d3dMainRenderTargetView{nullptr};
    inline static WNDCLASSEX windowClass{};
    inline static HWND mainWindow{};
    std::vector<Item> items{};
    size_t currentItem{0};

    static bool createDeviceD3D(HWND hWnd);

    static void createRenderTarget();

    static void cleanupDeviceD3D();

    static void cleanupRenderTarget();

    static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit ImWindows(LPCWSTR name = L"ImGui",
                       LPCWSTR className = L"ImGuiClass",
                       HINSTANCE hInstance = GetModuleHandle(nullptr));

    ~ImWindows();

    void mainloop();

    void addItem(const Item &item);

    template<class T> void addItem();
};

template<class T> void ImWindows::addItem() {
    items.push_back({T::getMenuName(), T::render});
}
