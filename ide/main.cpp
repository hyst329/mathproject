#include <gtkmm.h>
#include <glibmm/i18n.h>

int main(int argc, char **argv)
{
    bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);
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

