#include <gtkmm.h>
#include<iostream>

class MainWindow: public Gtk::Window
{

    Glib::RefPtr<Gtk::Builder> _builder;
    //
public:
    /** "quit" action handler. */
    void
    OnQuit()
    {
        hide();
    }
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
            Gtk::Window(cobject), _builder(builder)
    {
        /* Retrieve all widgets. */
        //
        /* Actions. */
        Glib::RefPtr<Gtk::Action>::cast_dynamic(_builder->get_object("action_quit"))->
                signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));
    }

};

int main(int argc, char **argv)
{
    Gtk::Main app(argc, argv);
    //Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(Glib::ustring("userInterface.glade"));
    //Load the GtkBuilder file and instantiate its widgets:
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    try
    {
        builder->add_from_file("userInterface.glade");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    Gtk::Window *w;
    //MainWindow *w = 0;
    //builder->get_widget_derived("window_main",w);
    builder->get_widget("window_main", w);
    w->show_all_children();
    app.run(*w);
    //delete w;
    return 0;
}






































//
// Created by User on 09.07.2015.
//

