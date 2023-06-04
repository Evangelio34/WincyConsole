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
vector<WindowInfo> windowList; // Lista de ventanas abiertas
string ownWindowTitle = "Wincy"; // Cambia esto con el título de tu propia aplicación

BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam) {
    char windowTitle[256];
    GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));

    if (IsWindowVisible(hwnd) && strlen(windowTitle) > 0) {
        if (ownWindowTitle != windowTitle && hwnd != GetConsoleWindow()) { // Ignorar la ventana de la terminal
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

int main() {
    bool continuar = false;
    EnumWindows(EnumWindowsCallback, NULL);
    system("cls");
    cout << "\n __          ___                  ";
    cout << "\n . .        / (_)                 ";
    cout << "\n  . .  /.  / / _ _ __   ___ _   _ ";
    cout << "\n   . ./  ./ / | | '_ . / __| | | |";
    cout << "\n    .  /.  /  | | | | | (__| |_| |";
    cout << "\n     ./  ./   |_|_| |_|.___|.__, |";
    cout << "\n                             __/ |";
    cout << "\n                            |___/  By Evangelio69";
    cout << "\n                                  ";
    cout << "\n                          Ventanas Abiertas :            ";

    do
    {
        for (int i = 0; i < windowList.size(); i++) {
            cout << "\n[" << i + 1 << "] " << windowList[i].title << endl;
        }

        int selectedWindowNumber;
        cout << "\n";
        cout << "Ingrese el numero de la ventana a la que desea ajustar la transparencia: ";
        cin >> selectedWindowNumber;

        if (selectedWindowNumber >= 1 && selectedWindowNumber <= windowList.size()) {
            HWND selectedWindowHandle = windowList[selectedWindowNumber - 1].handle;

            cout << "Ingrese el nivel de opacidad (0-255): ";
            int opacity;
            cin >> opacity;

            setWindowOpacity(selectedWindowHandle, static_cast<BYTE>(opacity));
            cout << "Transparencia de la ventana ajustada." << std::endl;
        }
        else {
            cout << "Numero de ventana inválido." << std::endl;
        }
        char respuesta;
        cout << "¿Desea continuar? (S/N): ";
        cin >> respuesta;
        if (respuesta == 'S' || respuesta == 's') {
            continuar = true;
        }
        else {
            continuar = false;
        }
    } while (continuar);

    system("cls");
    cout << "See you Later" << endl;
    seconds duracionEspera(3);
this_thread::sleep_for(duracionEspera);
exit(0);
}
