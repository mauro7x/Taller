#include <QApplication>
#include <QtWidgets>

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        size_t width = size().width();
        size_t height = size().height();

        painter.setPen(QPen(Qt::black, 2));
        painter.drawEllipse(QPoint(width / 2, height / 2), (width / 2) * 0.8,
                            (height / 2) * 0.8);
        painter.drawEllipse(QPoint(width / 2, height / 2), (width / 2) * 0.6,
                            (height / 2) * 0.6);
        painter.drawEllipse(QPoint(width / 2, height / 2), (width / 2) * 0.4,
                            (height / 2) * 0.4);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.resize(500, 500);
    w.show();

    return app.exec();
}