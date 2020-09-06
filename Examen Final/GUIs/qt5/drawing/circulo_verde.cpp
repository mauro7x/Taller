#include <QApplication>
#include <QtWidgets>

class Widget : public QWidget {
   protected:
    void paintEvent(QPaintEvent *event) {
        QPainter painter(this);
        size_t width = size().width();
        size_t height = size().height();

        painter.setPen(QPen(Qt::green, 1));
        painter.setBrush(QBrush(Qt::green));
        // painter.drawEllipse(0, 0, width, height / 2);
        painter.drawEllipse(QPoint(width / 2, height / 2), width / 2,
                            height / 2);
    }
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget w;
    w.resize(500, 500);
    w.show();

    return app.exec();
}