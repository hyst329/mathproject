#include <gtkmm.h>

int main(int argc, char **argv)
{
    // TODO(hyst329) : Rebuild gtkmm under gcc 5.1.0
    Gtk::Main app(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(Glib::ustring("userInterface.glade"));
    Gtk::Window *w;
    builder->get_widget("window_main", w);
    w->show_all_children();
    app.run(*w);
    return 0;
}






































//
// Created by User on 09.07.2015.
//

