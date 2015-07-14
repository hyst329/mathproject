#include <iostream>
#include "../kernel/AST.h"
#include <boost/program_options.hpp>
#include <fstream>

using namespace std;
using  namespace boost::program_options;

extern int yyparse(Kernel::AST *&);
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

int main(int argc,char **argv) {
    Kernel::AST *ast = 0;
    yyparse(ast);
    options_description desc("General options");
    string path;
    desc.add_options()
            ("help,h", "Show help")
            ("version,v","Show version")
            ("openfile,o",value<string>(&path),"Open file")
            ("info,i","Show info")
            ;
    variables_map vm;
    try {
        parsed_options parsed = command_line_parser(argc, argv).options(desc).allow_unregistered().run();
        store( parsed, vm);
        notify(vm);
    }
    catch(exception &a_exc) {
        cout << "Parse error: " << a_exc.what() <<endl;
        cout<<desc;
        return 0;
    }
    if (vm.count("help")) {
        cout<<desc;
    }
    if (vm.count("version")) {
        showVersion();
    }
    int a=0;
    if (vm.count("openfile")) {
        openFile(path);
    }
    if (vm.count("info")) {
        showInfo();
    }
    if (vm.empty())
        cout<<"Command not found";
    return 0;
}