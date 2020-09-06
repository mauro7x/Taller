#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina que lea los elementos de un listbox, los revierta ("abcd"
 * → "dcba") y los escriba nuevamente en el control. */

void procesar_combobox(QComboBox* cb);

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QComboBox cb;
    cb.addItem("una opcion");
    cb.addItem("abcd");
    cb.addItem("otra opcion");
    cb.addItem("otnot");
    procesar_combobox(&cb);
    cb.show();

    return app.exec();
}

void procesar_combobox(QComboBox* cb) {
    size_t count = cb->count();
    std::string data;

    for (size_t i = 0; i < count; i++) {
        data = cb->itemText(0).toStdString();
        std::reverse(data.begin(), data.end());
        cb->removeItem(0);
        cb->addItem(data.data());
    }
}