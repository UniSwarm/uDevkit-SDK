/**
 * @file htmlGen.cpp
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2017
 *
 * @date June 2, 2017, 14:07 PM
 *
 * @brief Tool to tranform a directory of files into file struct system
 * for web server
 */

#include <QApplication>
#include <QCommandLineParser>

#include <QTextStream>
#include <QDir>
#include <QMimeDatabase>
#include <QMimeType>

QString typeFromExtension(const QString &file_name)
{
    QMimeDatabase database;
    return database.mimeTypeForFile(file_name).name();
}

void exportPathToStruct(const QString &path, const QString &outputFile)
{
    QDir dir(path);

    QFile output(outputFile);
    output.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream text(&output);

    QString filesLog;
    QStringList files;
    files = dir.entryList(QDir::Files);

    // files.replaceInStrings(".", "_");

    // header comments
    text << "/* ================================================================" << endl;
    text << "   ================= automatically generated file =================" << endl;
    text << "   ==================== by HTMLGen (c)Robotips ====================" << endl;
    text << "   ================================================================" << endl;
    text << endl;
    text << "  | " << QString("File name").leftJustified(30, ' ') << "| "
         << QString("Struct name").leftJustified(30, ' ') << '|' << endl;
    text << "   --------------------------------------------------------------- " << endl;

    foreach (QString file, files)
    {
        QString filewodot = file;
        filewodot.replace(".", "_");

        filesLog.append(file);
        filesLog.append('\n');

        text << "  | " << file.leftJustified(30, ' ') << "| "
             << filewodot.leftJustified(30, ' ') << "|" << endl;
    }
    text << "   --------------------------------------------------------------- " << endl;
    text << "*/" << endl;
    text << endl;
    
    text << "#include \"fs_data.h\"" << endl << endl;

    text << "// ======== Struct content ======== " << endl;
    foreach (QString file, files)
    {
        QString filewodot = file;
        filewodot.replace(".", "_");
        QFile filebin(path + file);
        filebin.open(QIODevice::ReadOnly);
        text << "// -> " << file << endl;
        text << "const char " << filewodot << "_name[] = \"" << file
             << "\";" << endl;
        text << "const char " << filewodot << "_type[] = \""
             << typeFromExtension(file) << "\";" << endl;
        text << "const char " << filewodot << "_data[] = " << endl
             << "{" << endl
             << "    ";
        unsigned int addr = 0;
        while (filebin.bytesAvailable() > 0)
        {
            char data;
            QString hexdat;
            filebin.getChar(&data);
            addr++;

            hexdat = QString::number((unsigned char)data, 16);
            if (hexdat.size() < 2)
                hexdat.prepend('0');
            text << "0x" << hexdat;
            if (filebin.bytesAvailable() > 0)
                text << ", ";
            if (addr % 10 == 0)
                text << endl << "    ";
        }
        text << endl << "};" << endl;
        text << "const Fs_File " << filewodot << " = {" << filewodot << "_name, "
             << filewodot << "_type, " << filewodot << "_data, " << addr << "};"
             << endl
             << endl;
    }

    text << "// ======== List of files ======== " << endl;
    text << "const Fs_File *files_ptr[] = {" << endl;
    int size = 0;
    foreach (QString file, files)
    {
        size++;
        text << "&" << file.replace(".", "_");
        if (size < files.count())
            text << ", ";
        if (size % 32 == 0)
            text << endl;
    }
    text << "};" << endl;

    text << "const Fs_FilesList file_list = {files_ptr, " << files.count() << "};"
         << endl;

    output.close();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("htmlGen");
    QApplication::setApplicationVersion("1.0");
    QTextStream out(stdout);

    QCommandLineParser parser;
    parser.setApplicationDescription("Tool to tranform a directory of \
files into file struct system for web server");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption inputOption(QStringList() << "i" << "input",
        "Input path file", "data/");
    parser.addOption(inputOption);
    QCommandLineOption outputOption(QStringList() << "o" << "output",
        "Write generated data into <file>.", "html_data.c");
    parser.addOption(outputOption);

    parser.process(app);
    
    // check input
    if (!parser.isSet(inputOption))
    {
        out << "No input path specified." << endl;
        return 1;
    }
    QString inputPath = parser.value(inputOption);

    // output
    if (!parser.isSet(outputOption))
    {
        out << "No output file or police name specified." << endl;
        return 1;
    }
    QString outputFile = parser.value(outputOption);

    exportPathToStruct(inputPath, outputFile);

    return 0;
}
