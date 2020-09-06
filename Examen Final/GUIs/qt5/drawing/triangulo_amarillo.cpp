#include <QApplication>
#include <QtWidgets>

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        size_t width = size().width();
        size_t height = size().height();

        QPainterPath path;
        path.moveTo(0, height);
        path.lineTo(width / 2, 0);
        path.lineTo(width, height);
        path.lineTo(0, height);

        painter.setPen(Qt ::NoPen);
        painter.fillPath(path, QBrush(QColor("yellow")));
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.resize(500, 500);
    w.show();

    return app.exec();
}