#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina para ambiente gráfico que pinte un triángulo azul con las
 * carcterísticas que muestra la siguiente figura: (esta es mas jodida de
 * expresar, here we go: es un triangulo isóceles azul en un fondo blanco,
 * centrado horizontalmente, sólo en la mitad inferior). (ver final 2016.2.3 si
 * no me entendiste je). */

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent* event) override {
        QPainter painter(this);
        size_t w = size().width();
        size_t h = size().height();

        QPainterPath path;
        path.moveTo(0, h);
        path.lineTo(w / 2, h / 2);
        path.lineTo(w, h);
        path.lineTo(0, h);

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