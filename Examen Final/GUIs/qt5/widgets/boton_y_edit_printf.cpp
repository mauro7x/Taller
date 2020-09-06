#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina para ambientes gráficos que exponga una ventana con un
 * cuadro de texto y un botón. Al realizar un click sobre el botón, el sistema
 * debe tomar la información ingresada en el cuadro de texto e imprimirla por
 * consola. */

class Widget : public QWidget {
   protected:
    void onButton() {
        QLineEdit* edit = this->findChild<QLineEdit*>();
        if (edit) {
            printf("%s\n", edit->text().toStdString().data());
        }
    }

   public:
    Widget(QWidget* parent = 0) : QWidget(parent) {
        QGridLayout* grid = new QGridLayout(this);

        QPushButton* btn = new QPushButton("Imprimir", this);
        connect(btn, &QPushButton::clicked, this, &Widget::onButton);
        QLineEdit* edit = new QLineEdit(this);

        grid->addWidget(edit, 0, 0);
        grid->addWidget(btn, 1, 0);
        setLayout(grid);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}