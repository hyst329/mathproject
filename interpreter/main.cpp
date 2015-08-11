#include <iostream>
#include "../kernel/AST.h"
#include "../kernel/BuiltinFunctions.h"
#include "../kernel/Error.h"
//#include <boost/program_options.hpp>

using namespace std;
//using namespace boost::program_options;

extern int yyparse(Kernel::AST *&);

extern int yylex();

extern FILE *yyin, *yyout;

static Kernel::AST *ast = 0;

void showVersion() {
    cout << "Version 0.0.0 (currently versioning is not implemented)" << endl;
};

void translate() {
    yyparse(ast);
    ast->exec();
//    cout << "Functions:\n";
//    cout << "UserFunction TTM: " << (int)Kernel::AST::functions["ToTriangleMatrix"] << endl;
//    for (auto p: Kernel::AST::functions) {
//        cout << "Name: " << p.first << "\t\tValue:" << (int)p.second << endl;
//    }
}

void interactive() {
    yyin = stdin;
    yyout = 0;
    do {
        try {
            cout << ">>> ";
            ast = 0;
            //while (!feof(yyin)) {
            yyparse(ast);
            if (!ast) return;
            ast->exec();
            //}
        }
        catch (Error &error) {
            cerr << "Error: " << error.getText() << endl;
        }
    } while (1);
}

void setInputFile(string filename) {
    yyin = fopen(filename.c_str(), "r");
}

int main(int argc, const char *const argv[]) {
    Kernel::initialiseBuiltins();
    //options_description desc("General options");
    string path;
    /*desc.add_options()
            ("help,h", "Show this help message")
            ("version,v", "Show version")
            ("interactive,i", "Run in interactive mode")
            ("input-file,I", value<string>(&path), "Input file name");
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
        return 1;
    }
    if (vm.count("help")) {
        cout << desc;
        return 0;
    }
    if (vm.count("version")) {
        showVersion();
        return 0;
    }
    if (vm.count("input-file")) {
        setInputFile(path);
        cout << "Translating file " << path << "...\n";
        translate();
    }
    if (vm.count("interactive")) {
        cout << "Running in interactive mode...\n";
        interactive();
    }
    if (vm.empty()) {
        cout << "No options specified!" << endl;
        cout << desc;
        return 0;
    }*/
    return 0;
}
