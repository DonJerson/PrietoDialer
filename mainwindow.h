#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <vector>
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loginButton_clicked();
    void on_userField_textChanged(const QString &arg1);

    void on_loadButton_clicked();

    void on_numbersLoader_textChanged();

    void on_deleteAllButton_clicked();

    void on_powerButton_clicked();
private:
    Ui::MainWindow *ui;
    QString userName="";
    QString userPassword="";
    bool logged=false;
    bool power=false;
    int cantidadLeads =0;
    std::vector<QString> myLeads;
    QString leadsLoader="";
};


#endif // MAINWINDOW_H

