#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>
#include <cstdlib>
using namespace std;
using namespace chrono;

struct WindowInfo {
    HWND handle;
    std::string title;
};

vector<WindowInfo> windowList;
string ownWindowTitle = "Wincy";

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) {
        if (ownWindowTitle != windowTitle && hwnd != GetConsoleWindow()) {
            WindowInfo windowInfo;
            windowInfo.handle = hwnd;
            windowInfo.title = windowTitle;
            windowList.push_back(windowInfo);
        }
    }

    return TRUE;
}

void setWindowOpacity(HWND hwnd, BYTE opacity) {
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, opacity, LWA_ALPHA);
}

void bringWindowToTop(HWND hwnd) {
    SetForegroundWindow(hwnd);
}

int main() {
    bool continuar = true;
    int opcion;

    do {
        cout << "=== Menu de Opciones ===" << endl;
        cout << "1. Ajustar Transparencia de Ventana" << endl;
        cout << "2. Poner Ventana en Primer Plano" << endl;
        cout << "3. Salir" << endl;
        cout << "Elija una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                EnumWindows(windowList.clear(), NULL);
                // Resto del código para ajustar la transparencia...
                int selectedWindowNumber;
                // Código para seleccionar ventana y ajustar la opacidad...
                break;
            }
            case 2: {
                EnumWindows(windowList.clear(), NULL);
                // Código para poner ventana en primer plano...
                int selectedWindowNumber;
                // Código para seleccionar ventana y ponerla en primer plano...
                break;
            }
            case 3: {
                cout << "Saliendo del programa." << endl;
                continuar = false;
                break;
            }
            default: {
                cout << "Opción inválida. Por favor, elija una opción válida." << endl;
                break;
            }
        }

    } while (continuar);

    return 0;
}
