#pragma once

#include <Windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include <functional>
#include <type_traits>
#include <string_view>
#include <memory>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "misc/cpp/imgui_stdlib.h"
#include "../imguiaddons/imguidatechooser.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

template <typename T>
concept StaticCallable = requires {
    T::render();
    {std::invoke(&T::getMenuName)} -> std::convertible_to<std::string_view>;
};

template <typename T>
concept NonStaticCallable = !StaticCallable<T> && std::default_initializable<T> && requires(T t) {
    t.render();
    {std::invoke(&T::getMenuName, t)} -> std::convertible_to<std::string_view>;
};

class ImWindows {
public:
    struct Item {
        std::string_view menuName;
        std::function<void()> bodyCallback;
    };
private:
    inline static ID3D11Device *d3dDevice{nullptr};
    inline static ID3D11DeviceContext *d3dDeviceContext{nullptr};
    inline static IDXGISwapChain *d3dSwapChain{nullptr};
    inline static ID3D11RenderTargetView *d3dMainRenderTargetView{nullptr};
    inline static WNDCLASSEX windowClass{};
    inline static HWND mainWindow{};
    inline static std::vector<Item> items{};
    inline static size_t currentItem{0};

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

    template<StaticCallable T> 
    void addItem();
    template<NonStaticCallable T> 
    void addItem();
};

template<StaticCallable T> 
void ImWindows::addItem() {
    items.push_back({std::invoke(T::getMenuName), T::render});
}
template<NonStaticCallable T>
void ImWindows::addItem() {
    static std::vector<std::unique_ptr<T>> objectsHolder;
    objectsHolder.push_back(std::make_unique<T>());
    T* object = objectsHolder.back().get();
    items.push_back({std::invoke(&T::getMenuName, object), std::bind(&T::render, object)});
}
