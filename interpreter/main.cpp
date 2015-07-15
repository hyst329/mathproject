#include <iostream>
#include "../kernel/AST.h"
#include <boost/program_options.hpp>
#include <fstream>

using namespace std;
using namespace boost::program_options;

extern int yyparse(Kernel::AST *&);

extern int yylex();

extern FILE *yyin;

static Kernel::AST *ast = 0;

void showVersion() {
    cout << "Version 0.0.0 (currently versioning is not implemented)" << endl;
};

void translate() {
    yyparse(ast);
}

void setInputFile(string filename) {
    yyin = fopen(filename.c_str(), "r");
}

int main(int argc, char **argv) {
    options_description desc("General options");
    string path;
    desc.add_options()
            ("help,h", "Show this help message")
            ("version,v", "Show version")
            ("input-file,i", value<string>(&path), "Input file name");
    positional_options_description pos;
    pos.add("input-file", -1);
    variables_map vm;
    try {
        parsed_options parsed = command_line_parser(argc, argv).options(desc).positional(pos).
                allow_unregistered().run();
        store(parsed, vm);
        notify(vm);
    }
    catch (exception &a_exc) {
        cout << "Parse error: " << a_exc.what() << endl;
        cout << desc;
        return 0;
    }
    if (vm.count("help")) {
        cout << desc;
    }
    if (vm.count("version")) {
        showVersion();
    }
    if (vm.count("input-file")) {
        setInputFile(path);
        cout << "Translating file " << path << "...\n";
        translate();
    }
    if (vm.empty()) {
        cout << "No options specified!" << endl;
        cout << desc;
    }
    return 0;
}