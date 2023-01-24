#include "config/config.hpp"
#include "imwindows/imwindows.hpp"

#include "requests/amount_masters.hpp"
#include "requests/amount_accidents.hpp"
#include "requests/average_cost_repairing.hpp"
#include "requests/accidents_types.hpp"
#include "requests/amount_brigades.hpp"
#include "requests/earnings_masters.hpp"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    ImWindows im_window{L"Курсова робота", L"CourseWorkWindowClass", hInstance};

    im_window.addItem<Requests::AmountMasters>();
    im_window.addItem<Requests::AmountAccidents>();
    im_window.addItem<Requests::AverageCostRepairing>();
    im_window.addItem<Requests::AccidentsTypes>();
    im_window.addItem<Requests::EarningsMasters>();
    im_window.addItem<Requests::AmountBrigades>();

    bool done{false};
    MSG msg;
    while (!done) {
        while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                done = true;
        }
        im_window.mainloop();
        Sleep(10);
    }

    return EXIT_SUCCESS;
}
