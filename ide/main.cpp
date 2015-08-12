int main()
{
    return 0;
}

// OLD CONTENTS PRESERVED
/*
   #include <gtkmm.h>
   #include<iostream>

   class MainWindow : public Gtk::Window {
   //Child widgets:
    Glib::RefPtr<Gtk::Builder> _builder;
    Gtk::TextView *_source_view;
    //
   public:
    // signal handlers
    void
    OnQuit() {
        hide();
    }

    //"Open" or "Save" toolbuttons handlers
    // Choose the folder
    void on_toolbutton_folder_clicked() {
        Gtk::FileChooserDialog dialog("Please choose a folder",
                                      Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
        dialog.set_transient_for(*this);

        //Add response buttons the the dialog:
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("Select", Gtk::RESPONSE_OK);

        //Show the dialog and wait for a user response:
        int result = dialog.run();

        //Handle the response:
        switch (result) {
            case(Gtk::RESPONSE_OK): {
                std::cout << "Select clicked." << std::endl;
                std::cout << "Folder selected: " << dialog.get_filename()
                << std::endl;
                break;
            }
            case(Gtk::RESPONSE_CANCEL): {
                std::cout << "Cancel clicked." << std::endl;
                break;
            }
            default: {
                std::cout << "Unexpected button clicked." << std::endl;
                break;
            }
        }
    }

    //Choose the file
    void on_toolbutton_file_clicked() {
        Gtk::FileChooserDialog dialog("Please choose a file",
                                      Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.set_transient_for(*this);

        //Add response buttons the the dialog:
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        //Add filters, so that only certain file types can be selected:

        Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
        filter_text->set_name("Text files");
        filter_text->add_mime_type("text/plain");
        dialog.add_filter(filter_text);

        Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
        filter_cpp->set_name("C/C++ files");
        filter_cpp->add_mime_type("text/x-c");
        filter_cpp->add_mime_type("text/x-c++");
        filter_cpp->add_mime_type("text/x-c-header");
        dialog.add_filter(filter_cpp);

        Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
        filter_any->set_name("Any files");
        filter_any->add_pattern("*");
        dialog.add_filter(filter_any);

        //Show the dialog and wait for a user response:
        int result = dialog.run();

        //Handle the response:
        switch (result) {
            case(Gtk::RESPONSE_OK): {
                std::cout << "Open clicked." << std::endl;

                std::string filename = dialog.get_filename();
                std::cout << "File selected: " << filename << std::endl;
                // Set the text TODO(hyst329): add the real text instead of filename
                _source_view->get_buffer()->set_text(filename);
                break;
            }
            case(Gtk::RESPONSE_CANCEL): {
                std::cout << "Cancel clicked." << std::endl;
                break;
            }
            default: {
                std::cout << "Unexpected button clicked." << std::endl;
                break;
            }
        }
    }

    //Constructor
    MainWindow(BaseObjectType *cobject, const Glib::RefPtr<Gtk::Builder> &builder) :
            Gtk::Window(cobject), _builder(builder) {
        // Retrieve widgets.
        //toolbar
        Gtk::ToolButton *Open = 0;
        _builder->get_widget("toolbutton_open", Open);
        //Open->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_toolbutton_folder_clicked));
        Open->signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_toolbutton_file_clicked));


        //menubar
        Gtk::MenuItem *Quit = 0;
        _builder->get_widget("menuitem_quit_commands", Quit);
        Quit->signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));

        // Actions.
        //TODO(hyst329): create action action_quit
        //Glib::RefPtr<Gtk::Action>::cast_dynamic(_builder->get_object("action_quit"))->
        //        signal_activate().connect(sigc::mem_fun(*this, &MainWindow::OnQuit));

        _builder->get_widget("textview_commands", _source_view);

        show_all_children();
    }

   };

   int main(int argc, char **argv) {
    Gtk::Main app(argc, argv);

    //Load the GtkBuilder file and instantiate its widgets:
    Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create();
    try {
        builder->add_from_file("userInterface.glade");
    }
    catch (const Glib::FileError &ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Glib::MarkupError &ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Gtk::BuilderError &ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    MainWindow *w = 0;
    builder->get_widget_derived("window_main", w);
    app.run(*w);
    delete w;
    return 0;
   }
 */





































//
// Created by User on 09.07.2015.
//

