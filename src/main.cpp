#include "mainwindow.h"
#include "windows.h"
#include <QApplication>
#include <other.hpp>

FILE *output;
void outputRedirection(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    // debug
    #ifndef QT_NO_DEBUG_OUTPUT
        AllocConsole();
        system("chcp 65001");
        freopen("CON","w",stdout);
        output = stdout;
        qInstallMessageHandler(outputRedirection);
    #endif

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
        fprintf(output, "Debug:\n");
        break;
    case QtInfoMsg:
        fprintf(output, "Info:\n");
        break;
    case QtWarningMsg:
        fprintf(output, "Warning:\n");
        break;
    case QtCriticalMsg:
        fprintf(output, "Critical:\n");
        break;
    case QtFatalMsg:
        fprintf(output, "Fatal:\n");
        abort();
    }
    QByteArray debug_line = QString::number(context.line).toLatin1();
    print(
        output, 
        localMsg.constData(), "\n",
        // context.file, "\n",
        // "line:", debug_line.data(), "\n",
        context.function, "\n",
        "\n"
    );
}

