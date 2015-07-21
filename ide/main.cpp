#include <gtkmm.h>
#include<iostream>

class MainWindow: public Gtk::Window
{
    Glib::RefPtr<Gtk::Builder> _builder;
    //
public:
    /** "quit" action handler. */
    G_MODULE_EXPORT void
    OnQuit()
    {
        hide();
    }
    MainWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder):
            Gtk::Window(cobject), _builder(builder)
    {
        /* Retrieve all widgets. */
        Gtk::Box *box3 = 0;
        _builder->get_widget("box_workspace",box3);

        //create the Actions and add them to an ActionGroup, with ActionGroup::add()

        Glib::RefPtr<Gtk::ActionGroup> actionGroup1 =
                Gtk::ActionGroup::create();
        //Меню "Файл":
         Glib::RefPtr<Gtk::Action> action1 =
                Gtk::Action::create("quit",
                                   sigc::mem_fun(*this, &MainWindow::OnQuit));
        actionGroup1->add(action1);
        //insert_action_group("example",actionGroup1);
        Glib::RefPtr<Gtk::UIManager> uiManager1 =
                Gtk::UIManager::create();
        uiManager1->insert_action_group(actionGroup1);
        add_accel_group(uiManager1->get_accel_group());
        //Строковое описание пользовательского интерфейса для меню и панели инструментов:
        Glib::ustring ui_info =
                "<interface>"
                        "  <menubar name='MenuBar'>"
                        "    <menu action='MenuFile'>"
                        "      <menuitem action='Quit'/>"
                        "    </menu>"
                        "  </menubar>"
                        "</interface>";


        try
        {
            uiManager1->add_ui_from_string(ui_info);
            //_builder->add_from_string(ui_info);
        }
        catch(const Glib::Error& ex)
        {
            std::cerr << "не удалось создать меню: " <<  ex.what();
        }

        //Получение виджета меню и добавление его в контейнерный виджет:
        Gtk::Widget* pMenubar = uiManager1->get_widget("/MenuBar");
        box3->add(*pMenubar);


        /* Actions. */
        //Glib::RefPtr<Gtk::Action>::cast_dynamic(_builder->get_object("action_quit"))->
        //        signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));

        show_all_children();
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

    //Gtk::Window *w;
    MainWindow *w = 0;
    builder->get_widget_derived("window_main",w);
    //builder->get_widget("window_main", w);
    //w->show_all_children();
    app.run(*w);
    delete w;
    return 0;
}






































//
// Created by User on 09.07.2015.
//

