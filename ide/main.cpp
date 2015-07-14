#include <gtkmm.h>
//using namespace Gtk;

class MainWindow:public Gtk::Window{
public:
    Glib::RefPtr<Gtk::Builder> _builder;
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
            Gtk::Window(cobject), _builder(builder)
    {
        //
    }

    //Gtk::TextView *textView1 = 0;
    //_builder->get_widget("textview_commands",textView1);
};

int main(int argc, char **argv)
{
    Gtk::Main app(argc, argv);
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(Glib::ustring("userInterface.glade"));
    //MainWindow *w = 0;
    //builder->get_widget_derived("window_main", w);
    Gtk::Window *w;
    builder->get_widget("window_main", w);
    w->show_all_children();
    app.run(*w);
    return 0;
}






































//
// Created by User on 09.07.2015.
//

