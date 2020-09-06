#include <QApplication>
#include <QtWidgets>

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent *event) {
        QPainter painter(this);

        size_t width = size().width();
        size_t height = size().height();

        painter.setPen(QPen(Qt::red, 2));
        painter.drawLine(0, 0, width, height);
        painter.drawLine(0, height, width, 0);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.resize(500, 500);
    w.show();

    return app.exec();
}