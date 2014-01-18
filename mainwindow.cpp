#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

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

void MainWindow::saveVarToFile(QString varName, QString filename = "") {
    QString filePath;
    if(filename == "") {
        filePath = ui->mainFolder->text() + varName + ".txt";
    } else {
        filePath = ui->mainFolder->text() + filename + ".txt";
    }
    QLineEdit * lineedit = ui->tabWidget-> findChild < QLineEdit *>(varName);
    if (lineedit == NULL) {
        qDebug() << "Widget not found: " << varName << filename;
        return;
    }
    QString text = lineedit->text();
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << text;
    file.close();
}

void MainWindow::saveIntToFile(QString varName, QString filename = "") {
    QString filePath;
    if(filename == "") {
        filePath = ui->mainFolder->text() + varName + ".txt";
    } else {
        filePath = ui->mainFolder->text() + filename + ".txt";
    }
    QSpinBox * lineedit = ui->tabWidget-> findChild < QSpinBox *>(varName);
    if (lineedit == NULL) {
        qDebug() << "Widget not found";
        return;
    }
    QString text = lineedit->text();
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << text;
    file.close();
}

void MainWindow::on_pushButton_clicked()
{
    saveVarToFile("varTourName");
    if( ui->varSwapTeams->isChecked() ) {
        // swap teams
        saveVarToFile("varTeam1", "varTeam2");
        saveIntToFile("varTeam1Score", "varTeam2Score");
        saveVarToFile("varTeam2", "varTeam1");
        saveIntToFile("varTeam2Score", "varTeam1Score");
    } else {
        saveVarToFile("varTeam1");
        saveIntToFile("varTeam1Score");
        saveVarToFile("varTeam2");
        saveIntToFile("varTeam2Score");
    }
    saveVarToFile("varCaster");
}
