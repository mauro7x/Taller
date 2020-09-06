#include <stdio.h>

#include <QtWidgets>

/* Escriba una función que cargue un listbox (combo o dropdown) con 10 strings
 * de la forma "opción xx", siendo xx una cadena de 2 dígitos con la forma
 * 01,02,...10. */

void cargar_combobox(QComboBox* cb);

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QComboBox cb;
    cargar_combobox(&cb);
    cb.show();

    return app.exec();
}

void cargar_combobox(QComboBox* cb) {
    std::string base = "opción ";
    std::string opcion;

    for (int i = 1; i <= 10; i++) {
        opcion = base;
        if (i < 10) {
            opcion += '0';
        }

        opcion += std::to_string(i);
        cb->addItem(opcion.data());
    }
}