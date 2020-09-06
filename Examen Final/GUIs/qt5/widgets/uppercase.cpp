#include <stdio.h>

#include <QtWidgets>

/* Escriba una rutina (para ambiente gráfico Windows o Linux) que tome el
 * contenido de un edit y ponga la primera letra de cada palabra de su contenido
 * en mayúsculas */

void rutina(QLineEdit* edit);

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QLineEdit edit("hola que tal?");
    rutina(&edit);
    edit.show();

    return app.exec();
}

void rutina(QLineEdit* edit) {
    std::string original = edit->text().toStdString();

    bool convert = true;
    for (auto it = original.begin(); it != original.end(); it++) {
        if (convert) {
            *it = std::toupper(*it);
            convert = false;
        }

        if (*it == ' ') {
            convert = true;
        }
    }

    edit->setText(original.data());
}