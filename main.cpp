/* 
 * This file is part of Salutem
 * Copyright (c) 2021 Carl Philipp Klemm.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <iostream>
#include <QString>
#include <QTextDocument>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QStandardPaths>

QByteArray fileChecksum(const QString &fileName, 
                        QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result();
        }
    }
    return QByteArray();
}

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
	QCommandLineOption onceOption(QStringList() << "o" << "once", QCoreApplication::translate("main", "show given file only once"));
	parser.addOption(onceOption);
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
	QString textString(in.readAll());
	file.close();
	
	if(parser.isSet(onceOption)) {
		QFile readFile(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/salutem-ran");
		if(readFile.open(QIODevice::ReadOnly)) {
			QTextStream readFileTx(&readFile);
			QString md5(readFileTx.readLine());
			QCryptographicHash hash(QCryptographicHash::Md5);
			hash.addData(textString.toUtf8());
			readFile.close();
			
			if(md5.toLatin1() == hash.result().toHex())
				return 0;
			else
				file.remove();
		}
	}

	QTextDocument text;
	text.setHtml(textString);

	MainWindow w(&text);
	w.show();
	
	int ret = a.exec();
	
	if(parser.isSet(onceOption)) {
		QFile readFile(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/salutem-ran");
		if(readFile.open(QIODevice::WriteOnly)) {
			QTextStream readFileTx(&readFile);
			QCryptographicHash hash(QCryptographicHash::Md5);
			hash.addData(textString.toUtf8());
			readFileTx<<hash.result().toHex();
			readFile.close();
			std::cout<<"saved md5 sum to "
					 <<(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/salutem-ran").toStdString()
					 <<'\n';
		}
		else {
			std::cout<<"Can not open "
					 <<(QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/salutem-ran").toStdString()
					 <<'\n';
			return -1;
		}
	}
	
	return ret;
}
