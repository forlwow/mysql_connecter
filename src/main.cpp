#include "mainwindow.h"
#include "windows.h"
#include <QApplication>

FILE *output;
void outputRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    // debug
    AllocConsole();
    freopen("CON","w",stdout);
    output = stdout;
    qInstallMessageHandler(outputRedirection);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void outputRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(output, "Debug: \n%s\n (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(output, "Info: \n%s\n (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(output, "Warning: \n%s\n (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(output, "Critical: \n%s\n (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(output, "Fatal: \n%s\n (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}