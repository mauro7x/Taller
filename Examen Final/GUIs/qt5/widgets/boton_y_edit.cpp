#include <stdio.h>

#include <QtWidgets>

// Escriba una rutina que muestre un botón y un cuadro de texto en una
// ventana. Al hacer click en el botón debe desaparecer el cuadro de texto,
// dejando el resto de la ventana intácta.

class MyWindow : public QWidget {
   private:
    QGridLayout *grid = NULL;
    QPushButton *btn = NULL;
    QLineEdit *edit = NULL;

    void onButton() {
        fprintf(stderr, "%s\n", edit->text().toStdString().data());
        edit->hide();
    }

   public:
    MyWindow(QWidget *parent = 0) : QWidget(parent) {
        // Grilla
        grid = new QGridLayout(this);

        // Widgets
        btn = new QPushButton("Un botón", this);
        edit = new QLineEdit(this);

        // Para que no se vaya
        QSizePolicy sp_retain = edit->sizePolicy();
        sp_retain.setRetainSizeWhenHidden(true);
        edit->setSizePolicy(sp_retain);

        grid->addWidget(btn, 0, 0);
        grid->addWidget(edit, 1, 0);

        // Layout
        setLayout(grid);

        // Callbacks
        connect(btn, &QPushButton::clicked, this, &MyWindow::onButton);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyWindow window;
    window.show();
    return app.exec();
}