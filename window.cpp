#include "window.h"
#include <iostream>
#include <X11/Xlib.h>
#include <cstring>
using namespace std;
namespace window {
    class blinker {
        int color = 10;
    public:
        int getColor() {
            if (color > 100) {
                color = 10;
            }
            return color++;
        }
    };

    int test() {
        try {
            Display *d;
            Window w;
            XEvent e{};
            auto msg = "Hello, World!";
            int s;
            // Соединиться с X сервером,
            if ((d = XOpenDisplay(getenv("DISPLAY"))) == nullptr) {
                printf("Can't connect X server: %s\n", strerror(errno));
                exit(1);
            }
            s = DefaultScreen(d);
            // Создать окно
            w = XCreateSimpleWindow(d, RootWindow(d, s),
                                    10, 10, 200, 200, 1,
                                    BlackPixel(d, s), WhitePixel(d, s));
            // На какие события будем реагировать?
            XSelectInput(d, w, ExposureMask | KeyPressMask);
            // Вывести окно на экран
            XMapWindow(d, w);
            // I support the WM_DELETE_WINDOW protocol
            Atom WM_DELETE_WINDOW = XInternAtom(d, "WM_DELETE_WINDOW", False);
            XSetWMProtocols(d, w, &WM_DELETE_WINDOW, 1);
            blinker b;
            while (true) {
                XNextEvent(d, &e);
                // Перерисовать окно
                if (e.type == Expose) {
                    XFillRectangle(d, w, DefaultGC(d, s), b.getColor(), 20, 10, 10);
                    XDrawString(d, w, DefaultGC(d, s), 50, 50, msg, static_cast<int>(strlen(msg)));
                }
                // При нажатии кнопки - выход
                if (e.type == KeyPress) {
                    string msg1("Message = " + b.getColor());
                    XFillRectangle(d, w, DefaultGC(d, s), b.getColor(), 20, 10, 10);
                    XFillRectangle(d, w, DefaultGC(d, s), 50, 38, 100, 14);
                    XDrawString(d, w, DefaultGC(d, s), 50, 50, msg1.data(), static_cast<int>(strlen(msg)));
//                    break;
                } else if (e.type == ClientMessage)
                    // Should check here for other client message types -
                    // however as the only protocol registered above is WM_DELETE_WINDOW
                    // it is safe for this small example.
                    break;
            }
            // Закрыть соединение с X сервером
            XCloseDisplay(d);
        }
        catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << "\n";
        }
        return 0;
    }
}