#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje, en
 * color azul, un óvalo que ocupe toda la pantalla. */

class Widget : public QWidget {
   protected:
    void onButton() {
        QMessageBox msgBox;
        QCheckBox* cb = new QCheckBox("Un check box!");
        msgBox.setCheckBox(cb);
        msgBox.setText("Una ventana de diálogo.");
        msgBox.exec();
    }

   public:
    Widget(QWidget* parent = 0) : QWidget(parent) {
        QGridLayout* grid = new QGridLayout(this);
        QPushButton* btn = new QPushButton("Dialog!", this);
        connect(btn, &QPushButton::clicked, this, &Widget::onButton);

        grid->addWidget(btn, 0, 0);
        setLayout(grid);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.show();
    return app.exec();
}