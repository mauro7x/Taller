#include <gtkmm.h>
#include <stdio.h>

#include <condition_variable>
#include <exception>
#include <fstream>
#include <iostream>
#include <list>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Gtk::ComboBoxText combo;
    Glib::ustring opcion = "opción xx";
    for (int i = 1; i <= 10; i++) {
        Glib::ustring new_opcion = opcion.substr(0, opcion.length() - 2);
        if (i == 10) {
            new_opcion += "10";
        } else {
            new_opcion += ("0" + std::to_string(i));
        }
        combo.append(new_opcion);
    }

    Gtk::VBox vbox;
    vbox.add(combo);
    Gtk::Window v;
    v.add(vbox);
    v.show_all();
    Gtk::Main::run(v);
    return 0;
}