#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QScroller>

MainWindow::MainWindow(QTextDocument* text, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->textEdit->setDocument(text);
	ui->textEdit->setTextInteractionFlags(Qt::NoTextInteraction);
	QScroller::grabGesture(ui->textEdit, QScroller::TouchGesture);
	QScroller::grabGesture(ui->textEdit, QScroller::LeftMouseButtonGesture);
	ui->textEdit->setStyleSheet("background-color : rgba(0,0,0,0%); color : white;");
}

MainWindow::~MainWindow()
{
	delete ui;
}

