#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QTextStream>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Untitled file*");
}

MainWindow::~MainWindow()
{
    delete ui;
}

int new_file=1;
int open_file=0;
void MainWindow::on_actionNew_triggered()
{
    file_path = "";
    ui->textEdit->setText("");
    ui->statusbar->showMessage("New file!",5000);
    new_file=1;
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this,"Select a file");
    QFile file(file_path);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Error!","Cannot open the file");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
    new_file=0;
    open_file=1;
    QString title("*");
    title+=file_path;
    this->setWindowTitle(title);
    ui->statusbar->showMessage("Opened "+file_path,5000);
}

void MainWindow::on_actionSave_triggered()
{
    if(open_file==1)
    {
        QFile file(file_path);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::critical(this,"Error!","Cannot save the file");
        }
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();
        file.flush();
        file.close();
        ui->statusbar->showMessage("Edited "+file_path,5000);
     }
    if(new_file==1)
    {
        file_path = QFileDialog::getSaveFileName(this,"Save file",NULL,"Text (*.txt)");
        QFile file(file_path);
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::critical(this,"Error!","File is not saved");
        }
        QTextStream out(&file);
        out<<ui->textEdit->toPlainText();
        file.flush();
        file.close();
        ui->statusbar->showMessage("Saved "+file_path,5000);
        new_file=0;
    }
    this->setWindowTitle(file_path);
}

void MainWindow::on_actionSave_as_triggered()
{
    file_path = QFileDialog::getSaveFileName(this,"Save file",NULL,"Text (*.txt)");
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::critical(this,"Error!","File is not saved!");
    }
    QTextStream out(&file);
    out<<ui->textEdit->toPlainText();
    file.flush();
    file.close();
    this->setWindowTitle(file_path);
    ui->statusbar->showMessage("Saved as "+file_path,5000);
}

void MainWindow::on_actionClose_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionundo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionredo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionpaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionAbout_Jnots_triggered()
{
    QMessageBox::information(this,"About Jnotes","JNotes v1.0");
}
