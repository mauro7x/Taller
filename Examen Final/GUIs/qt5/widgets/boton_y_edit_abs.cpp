#include <stdio.h>

#include <QtWidgets>

// Escriba una rutina que muestre un botón y un cuadro de texto en una
// ventana. Al hacer click en el botón debe desaparecer el cuadro de texto,
// dejando el resto de la ventana intácta.

class Widget : public QWidget {
   private:
    void onButton() {
        QLineEdit *edit = this->findChild<QLineEdit *>();
        if (edit) {
            edit->setVisible(false);
        }
    }

   public:
    Widget(QWidget *parent = 0) : QWidget(parent) {
        // botón
        QPushButton *btn = new QPushButton("Botón", this);
        connect(btn, &QPushButton::clicked, this, &Widget::onButton);

        // edit
        QLineEdit *edit = new QLineEdit(this);

        btn->setGeometry(10, 10, 100, 50);
        edit->setGeometry(10, 70, 100, 50);
        this->resize(120, 130);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.show();

    return app.exec();
}