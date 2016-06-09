#include "mainwindow.h"
#include "ui_mainwindow.h"
 
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QDebug>
#include <QMimeDatabase>
#include <QMimeType>
 
#include "aboutdialog.h"
 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
 
    QFile param("param.ini");
    param.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream text_param(&param);
    ui->pathEdit->setText(text_param.readLine());
    ui->outFileEdit->setText(text_param.readLine());
    param.close();
}
 
MainWindow::~MainWindow()
{
    delete ui;
}
 
void MainWindow::on_pathButton_clicked()
{
    ui->pathEdit->setText(QFileDialog::getExistingDirectory(this, "Choisir un dossier"));
}
 
QString MainWindow::typeFromExtension(QString file_name)
{
    QMimeDatabase database;
    return database.mimeTypeForFile(file_name).name();
}
 
void MainWindow::on_generateButton_clicked()
{
    QString path = ui->pathEdit->text() + "/";
    QDir dir(ui->pathEdit->text());
 
    QFile output(ui->outFileEdit->text());
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream text(&output);
 
    QString filesLog;
    QStringList files;
    files = dir.entryList(QDir::Files);
 
    //files.replaceInStrings(".", "_");
 
    // header comments
    text << "/* ================================================================  " << endl;
    text << "   ================ automatically generated file ==================  " << endl;
    text << "   ============== by HTMLGen 2.0 (c)Sebastien CAUX ================  " << endl;
    text << "   ================================================================  " << endl;
    text << "  | " << QString("File name").leftJustified(30, ' ') << "| " << QString("Struct name").leftJustified(30, ' ') << endl;
    text << "   ---------------------------------------------------------------- " << endl;
    foreach(QString file, files)
    {
        QString filewodot=file;
        filewodot.replace(".", "_");
 
        filesLog.append(file);
        filesLog.append('\n');
 
        text << "  | " << file.leftJustified(30, ' ') << "| " << filewodot.leftJustified(30, ' ') << "|" <<  endl;
    }
    text << "   ---------------------------------------------------------------- */" << endl;
    text << endl;
     
    // structs
    text << "// ======== Struct declare ======== " << endl;
    text << "typedef struct" << endl;
    text << "{" << endl;
    text << "\tunsigned char *name;" << endl;
    text << "\tunsigned char *type;" << endl;
    text << "\tunsigned char *data;" << endl;
    text << "\tunsigned int size;" << endl;
    text << "} File;" << endl << endl;
 
    text << "typedef struct" << endl;
    text << "{" << endl;
    text << "\tFile **files;" << endl;
    text << "\tunsigned int count;" << endl;
    text << "} FilesList;" << endl << endl;
 
    text << "// ======== Struct content ======== " << endl;
    foreach(QString file, files)
    {
        QString filewodot=file;
        filewodot.replace(".", "_");
        QFile filebin(path + file);
        filebin.open(QIODevice::ReadOnly);
        text << "// -> " << file << endl;
        text << "const unsigned char " << filewodot << "_name[] = \"" << file << "\";" << endl;
        text << "const unsigned char " << filewodot << "_type[] = \"" << typeFromExtension(file) << "\";" << endl;
        text << "const unsigned char " << filewodot << "_data[] = " << endl << "{" << endl << '\t';
        unsigned int addr=0;
        while(filebin.bytesAvailable()>0)
        {
            char data;
            QString hexdat;
            filebin.getChar(&data);
            addr++;
 
            hexdat = QString::number((unsigned char)data, 16);
            if(hexdat.size()<2) hexdat.prepend('0');
            text << "0x" << hexdat;
            if(filebin.bytesAvailable()>0) text << ", ";
            if(addr % 32 == 0) text << endl << '\t';
        }
        text << endl << "};" << endl;
        text << "const File " << filewodot << " = {" << filewodot << "_name, " << filewodot << "_type, " << filewodot << "_data, " << addr << "};" << endl << endl;
    }
 
    text << "// ======== List of files ======== " << endl;
    text << "const File *files_ptr[] = {" << endl;
    unsigned int size=0;
    foreach(QString file, files)
    {
        size++;
        text << "&" << file.replace(".", "_");
        if(size<files.count()) text << ", ";
        if(size % 32 == 0) text << endl;
    }
    text  << "};" << endl;
 
    text << "const FilesList file_list = {files_ptr, " << files.count() << "};" << endl;
 
    ui->log->setText(filesLog);
    output.close();
 
    QFile param("param.ini");
    param.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream text_param(&param);
    text_param << ui->pathEdit->text() << endl;
    text_param << ui->outFileEdit->text() << endl;
    param.close();
}
 
void MainWindow::on_actionA_propos_triggered()
{
    AboutDialog dialog;
    dialog.exec();
}