#include "../kernel/AST.h"
#include "../kernel/BuiltinFunctions.h"
#include "../kernel/Error.h"
#include <QCommandLineParser>
#include <QDir>
#include <QFileInfo>
#include <QSet>

extern int yyparse(Kernel::AST *&);

extern int yylex();

extern FILE *yyin, *yyout;

static Kernel::AST *ast = 0;

void translate() {
    static QTextStream cerr(stderr);
    try
    {
        yyparse(ast);
        ast->exec();
    }
    catch (Error &error)
    {
        cerr << "Error: " << error.getText() << endl;
    }
}

void interactive() {
    yyin = stdin;
    yyout = 0;
    static QTextStream cout(stdout), cerr(stderr);
    do {
        try {
            cout << ">>> " << flush;
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

QSet<QString> includePaths { "library" };
QString fileDir;

void setInputFile(QString filename) {
    QFileInfo fi(filename);
    fileDir = fi.absoluteDir().absolutePath();
    //QTextStream(stdout) << QString("Filedir set to %1").arg(fileDir);
    yyin = fopen(filename.toLocal8Bit().constData(), "r");
}

QString checkFilename(QString filename) {
    QDir fd(fileDir);
    QFileInfo fi(fd.absoluteFilePath(filename));
    if(fi.exists() && fi.isFile())
        return fi.absoluteFilePath();
    for(QString p: includePaths) {
        QDir d(p);
        QString path = d.absoluteFilePath(filename);
        QFileInfo fi(path);
        if(fi.exists() && fi.isFile())
            return fi.absoluteFilePath();
    }
    return filename;
}

int main(int argc, char** argv) {
    // always use non-buffered stdin
    setvbuf(stdin,  0, _IONBF, BUFSIZ);
    setvbuf(stdout, 0, _IONBF, BUFSIZ);
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
    if (!args.empty()) {
        QString path = args.at(0);
        setInputFile(path);
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
