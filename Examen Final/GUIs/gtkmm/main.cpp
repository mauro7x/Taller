#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/label.h>
#include <iostream>

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.examples.base");

  Gtk::Label label;
  label.set_text("Hola mundo!");

  Gtk::Window ventana;
  ventana.set_border_width(10);
  ventana.add(label);
  
  label.show();
  
  return app->run(ventana,argc,argv);
}
