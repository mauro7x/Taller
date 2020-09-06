#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina de interfaz gráfica que  lance una aplicación de ventana
 * simple, con un cuadro de texto y un botón. Al presionar el  botón, se debe
 * borrar el valor ingresado por el usuario en el cuadro de texto. */

class Widget : public QWidget {
   private:
    void onButton() {
        QLineEdit *edit = this->findChild<QLineEdit *>();
        if (edit) {
            edit->clear();
        }
    }

   public:
    Widget(QWidget *parent = 0) : QWidget(parent) {
        QGridLayout *grid = new QGridLayout(this);

        QLineEdit *edit = new QLineEdit(this);

        QPushButton *btn = new QPushButton("Clear", this);
        connect(btn, &QPushButton::clicked, this, &Widget::onButton);

        grid->addWidget(edit, 0, 0);
        grid->addWidget(btn, 1, 0);

        setLayout(grid);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}