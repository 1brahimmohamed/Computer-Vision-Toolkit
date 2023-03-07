/******************************************************************************
 *
 * File Name: mainwindow.cpp
 * Description: Source file for the GUI main window of the program
 * Authors: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:40
 *
 *******************************************************************************/


#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
