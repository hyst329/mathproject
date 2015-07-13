#include <iostream>
#include "Token.h"
#include <boost/program_options.hpp>
#include <fstream>

using namespace std;
using  namespace boost::program_options;

extern int yyparse();
extern int  yylex();

void showVersion() {
    ifstream cin("version.txt");
    while (!cin.eof())
    {
        std::string text;
        getline(cin,text);
        cout<<text<<'\n';
    }
};
void openFile(string task) {
    ;
}
void showInfo() {
    ifstream cin("info.txt");
    while (!cin.eof())
    {
        std::string text;
        getline(cin,text);
        cout<<text<<'\n';
    }
}


int main(int ac,char **av) {
    yyparse();
    options_description desc("General options");
    std::string task;
    desc.add_options()
            ("help,h", "Show help")
            ("version,v","Show version")
            ("openfile,o",value<std::string>(&task),"Open file")
            ("info,i","Show info");
    variables_map vm;
    parsed_options parsed = command_line_parser(ac, av).options(desc).allow_unregistered().run();
    store(parsed, vm);
    notify(vm);
    if (vm.count("help")) {
        cout<<desc;
    }
    if (vm.count("version")) {
        showVersion();
    }
    if (vm.count("openfile")) {
        openFile(task);
    }
    if (vm.count("info")) {
        showInfo();
    }
    return 0;
}