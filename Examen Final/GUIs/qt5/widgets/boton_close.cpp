#include <stdio.h>

#include <QtWidgets>

/* Escriba un pequeño programa de interfaz gráfica que lance una aplicación de
 * ventana simple, con un único botón. El botón debe tener  l texto 'Cerrar' que
 * al ser presionado  culta la ventana y cierra el sistema. */

class Widget : public QWidget {
   private:
    void onButton() {
        close();
    }

   public:
    Widget(QWidget *parent = 0) : QWidget(parent) {
        // botón
        QPushButton *btn = new QPushButton("Cerrar", this);
        connect(btn, &QPushButton::clicked, this, &Widget::onButton);

        btn->setGeometry(10, 10, 100, 50);
        this->resize(120, 70);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.show();

    return app.exec();
}