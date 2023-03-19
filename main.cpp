#include "QT/mainwindow.h"
#include "DB/DatabaseManager.h"

#include <QApplication>
#include <QDebug>
#include <QLocale>
#include <QTranslator>

#include <cstdio>
#include <cstdlib>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}

int main(int argc, char *argv[]) {
  // TODO: reenable the message handler
    //qInstallMessageHandler(myMessageOutput);
  QApplication a(argc, argv);

  if (DatabaseManager dbManager; !dbManager.initDatabase()) {
	qDebug() << "Database not open";
  }

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
      const QString baseName = "test_" + QLocale(locale).name();
      if (translator.load(":/i18n/" + baseName)) {
          QApplication::installTranslator(&translator);
          break;
      }
  }

  MainWindow mainWindow;
  mainWindow.show();

  return QApplication::exec();
}
