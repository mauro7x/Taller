#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina (para ambiente gráfico Windows o Linux) que dibuje un
 * rombo azul del tamaño de la pantalla. */

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent* event) {
        size_t w = size().width();
        size_t h = size().height();
        QPainter painter(this);

        QPainterPath path;
        path.moveTo(w / 2, 0);
        path.lineTo(w, h / 2);
        path.lineTo(w / 2, h);
        path.lineTo(0, h / 2);
        path.lineTo(w / 2, 0);

        painter.setPen(Qt::NoPen);
        painter.fillPath(path, QBrush(Qt::blue));
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    Widget w;
    w.resize(500, 500);
    w.show();
    return app.exec();
}