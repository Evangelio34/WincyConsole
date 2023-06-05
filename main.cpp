#include <QApplication>
#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <windows.h>

void setWindowOpacity(HWND hwnd, qreal opacity) {
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
    SetLayeredWindowAttributes(hwnd, 0, static_cast<BYTE>(opacity * 255), LWA_ALPHA);
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    QLabel *titleLabel = new QLabel("Seleccione una ventana:");
    layout->addWidget(titleLabel);

    QComboBox *windowComboBox = new QComboBox;
    // Rellenar la lista de ventanas disponibles en el combobox
    EnumWindows([](HWND hwnd, LPARAM lParam) {
        if (IsWindowVisible(hwnd)) {
            char windowTitle[256];
            GetWindowTextA(hwnd, windowTitle, sizeof(windowTitle));
            reinterpret_cast<QComboBox *>(lParam)->addItem(QString::fromUtf8(windowTitle));
        }
        return TRUE;
    }, reinterpret_cast<LPARAM>(windowComboBox));
    layout->addWidget(windowComboBox);

    QLabel *opacityLabel = new QLabel("Seleccione el nivel de opacidad:");
    layout->addWidget(opacityLabel);

    QSlider *opacitySlider = new QSlider(Qt::Horizontal);
    opacitySlider->setRange(0, 100);
    layout->addWidget(opacitySlider);

    QPushButton *applyButton = new QPushButton("Aplicar");
    layout->addWidget(applyButton);

    QObject::connect(applyButton, &QPushButton::clicked, [&windowComboBox, &opacitySlider]() {
        HWND selectedWindowHandle = reinterpret_cast<HWND>(windowComboBox->currentData().toULongLong());
        qreal opacity = static_cast<qreal>(opacitySlider->value()) / 100.0;
        setWindowOpacity(selectedWindowHandle, opacity);
    });

    window.setLayout(layout);
    window.show();

    return app.exec();
}
