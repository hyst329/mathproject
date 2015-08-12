#include "../kernel/AST.h"
#include "../kernel/BuiltinFunctions.h"
#include "../kernel/Error.h"
#include <QCommandLineParser>

extern int yyparse(Kernel::AST *&);

extern int yylex();

extern FILE *yyin, *yyout;

static Kernel::AST *ast = 0;

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
    static QTextStream cout(stdout), cerr(stderr);
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

void setInputFile(QString filename) {
    yyin = fopen(filename.toLocal8Bit().constData(), "r");
}

int main(int argc, char** argv) {
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("mathproject-interpreter");
    QCoreApplication::setApplicationVersion("0.0.0");
    QTextStream cout(stdout);
    Kernel::initialiseBuiltins();
    QCommandLineParser parser;
    parser.setApplicationDescription("mathproject interpreter");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("input-file", QCoreApplication::translate("main", "File to interpret."));
    parser.addOptions({
        {{"i", "interactive"}, QCoreApplication::translate("main", "Run in interactive mode.")}
    });
    parser.process(a.arguments());
    const QStringList args = parser.positionalArguments();
    cout << "This is a test";
    if (!args.empty()) {
        QString path = args.at(0);
        setInputFile(path);
        cout << "Translating file " << path << "...\n";
        translate();
    }
    else if (parser.isSet("interactive")) {
        cout << "Running in interactive mode...\n";
        interactive();
    }
    else {
        parser.showHelp();
        return 0;
    }
    return 0;
}
