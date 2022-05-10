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

