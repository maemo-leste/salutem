#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <iostream>
#include <QString>
#include <QTextDocument>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("UVOS");
	QCoreApplication::setOrganizationDomain("uvos.xyz");
	QCoreApplication::setApplicationName("Salutem");
	QCoreApplication::setApplicationVersion("0.1");

	QCommandLineParser parser;
	parser.setApplicationDescription("Greeter for Maemo Leste");
	parser.addHelpOption();
	parser.addVersionOption();
	QCommandLineOption textOption(QStringList() << "t" << "text", QCoreApplication::translate("main", "Specify html file to use"), "filename");
	parser.addOption(textOption);
	parser.process(a);

	if(!parser.isSet(textOption)) {
		std::cout<<"A text file must be specified\n";
		return -1;
	}

	QFile file(parser.value(textOption));
	if(!file.open(QIODevice::ReadOnly)) {
		std::cout<<"Can not load "<<parser.value(textOption).toStdString()<<'\n';
		return -1;
	}
	QTextStream in(&file);

	QTextDocument text;
	text.setHtml(in.readAll());
	file.close();

	MainWindow w(&text);
	w.show();
	return a.exec();
}
