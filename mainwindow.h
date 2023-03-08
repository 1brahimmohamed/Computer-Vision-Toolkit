/******************************************************************************
 *
 * File Name: mainwindow.h
 * Description: Header file for the GUI main window of the program
 * Authors: Ibrahim Mohamed
 * Last Modified: 3 Mar 23 - 01:40
 *
 *******************************************************************************/

#include <QMainWindow>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
