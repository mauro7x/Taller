#include <QtWidgets>

class MyWindow : public QWidget {
   protected:
    void paintEvent(QPaintEvent* event) {
        size_t w = size().width();
        size_t h = size().height();

        QPainter painter(this);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QBrush(Qt::red));
        // Podemos dibujar las elipses de dos formas: o definimos un rectángulo
        // y se dibujará una elipse dentro de este, o definimos el centro y los
        // radios de sus ejes.
        painter.drawEllipse(0, 0, w / 4,
                            h / 4);  // rectángulo desde(x, y), hasta(x, y)
        painter.setBrush(QBrush(Qt::blue));
        painter.drawEllipse(QPoint(w / 2, h / 2), w / 3,
                            h / 3);  // centro(x, y), radio_ax, radio_ay
    }

   public:
    MyWindow(QWidget* parent = 0) : QWidget(parent) {
        // Constructor. Aquí podemos agregar distintos widgets, layouts, etc.
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MyWindow w;
    w.show();
    return app.exec();
}
