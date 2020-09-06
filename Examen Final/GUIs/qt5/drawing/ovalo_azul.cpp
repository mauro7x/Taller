#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje, en
 * color azul, un óvalo que ocupe toda la pantalla. */

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent* event) {
        size_t w = size().width();
        size_t h = size().height();
        QPainter painter(this);

        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(0, 0, w, h);
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.resize(300, 500);
    w.show();
    return app.exec();
}