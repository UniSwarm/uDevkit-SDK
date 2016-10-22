/**
 * @file img2raw.c
 * @author Sebastien CAUX (sebcaux) / Charles-Antoine NOURY (CharlyBigoud)
 * @copyright Robotips 2016
 *
 * @date April 25, 2016, 18:39 PM
 *
 * @brief Tool to transform image in const C raw data (xc16 format) and storing its metadata
 */

#include <QCommandLineParser>
#include <QApplication>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>

#include <QImage>

#include <QFont>
#include <QFontDatabase>
#include <QFontMetrics>
#include <QPainter>
#include <QRegExp>

void exportImage(QImage image, QString filename)
{
    QFileInfo finfo(filename);
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);

    stream << "#ifndef " << finfo.baseName() << "_PICTURE_" << endl;
    stream << "#define " << finfo.baseName() << "_PICTURE_" << endl;
    stream << endl;

    // stream << "#include <stdint.h>" << endl;
    stream << "#include <pictures.h>" << endl;
    stream << endl;

    //starting image data array
    stream << "__prog__ const uint16_t " << finfo.baseName() << "_data[] __attribute__((space(prog))) = {";

    QImage mirrored = image.mirrored(false,false);

    for(int x=0; x<mirrored.width(); x++)
    {
        stream << endl;
        for(int y=0; y<mirrored.height(); y++)
        {
            QRgb color = mirrored.pixel(x,y);

            unsigned short syscolor = 0;
            syscolor |= (qRed(color)&0xF8)<<8;
            syscolor |= (qGreen(color)&0xFC)<<3;
            syscolor |= (qBlue(color)&0xF8)>>3;
            stream << "0x" << QString::number(syscolor,16);
            if(x!=mirrored.width()-1 || y!=mirrored.height()-1) stream << ", ";
        }
    }
    stream << endl << "};\n" << endl;

    //initializing the structure
    stream << "const Picture " << finfo.baseName() << " = {" << image.width() << ", " << image.height() << ", " << finfo.baseName() << "_data};" << endl;
    
    //ending file
    stream << endl;
    stream << "#endif //" << finfo.baseName() << "_PICTURE_" << endl;

    file.close();
}

void exportfont(QFont font, QString outFileName )
{
    char c;
    unsigned value;
    int x, y, height, nb, width, wl;
    char first=' ', last='z';
    bool prem;

    QFile file(outFileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);

    QString fontName;
    QFontMetrics metric(font);
    height=metric.height();

    fontName=font.family().replace(" ","");
    if (fontName.size()>10) fontName = fontName.mid(0,10);
    if(font.pixelSize()!=-1)
        fontName.append(QString::number(font.pixelSize()));
    else
        fontName.append(QString::number(font.pointSize()));
    if(font.bold()) fontName.append("b");
    if(font.underline()) fontName.append("u");
    if(font.italic()) fontName.append("i");

    stream << QString("#ifndef _")+fontName+QString("_font_") << endl;
    stream << QString("#define _")+fontName+QString("_font_") << endl << endl;
    stream << QString("#include \"gui/font.h\"") << endl << endl;

    QImage letter(50,50,QImage::Format_ARGB32);
    QImage letters(2000,50,QImage::Format_ARGB32);
    QPainter paint;
    QPainter paint2(&letters);
    paint2.setFont(font);
    paint2.drawRect(-1, -1, 2002, 52);
    wl = 0;
    for (c=first;c<=last;c++)
    {
        if (c!='\\')
            stream << "// " << c << endl;
        else
            stream << "// (antislash)" << endl;

        stream << "const char ";
        stream << fontName << "_data_" << QString::number(c) << "[] = {";

        paint.begin(&letter);
        paint.setBrush(Qt::white);
        paint.setFont(font);
        paint.drawRect(QRect(-1,-1,52,52));
        paint.drawText(QRect(0,0,50,50),Qt::AlignLeft|Qt::AlignTop,QString(c));
        paint.end();

        width=metric.width(c);
        paint2.drawText(QRect(wl,0,50,50),Qt::AlignLeft|Qt::AlignTop,QString(c));
        wl+=width;
        prem = true;
        for(x=0;x<width;x++)
        {
            nb=0;
            value=0;
            for(y=0;y<height;y++)
            {
                if((y%8)==0 && y!=0)
                {
                    if(!prem)
                        stream << ", ";
                    prem = false;
                    stream << "0x";
                    if(QString::number(value,16).size()<2)
                        stream << '0';
                    stream << QString::number(value,16).toUpper();
                    value=0;
                }
                if(qGray(letter.pixel(x,y)) == 0)
                {
                    value=value+(1<<(y%8));
                    nb++;
                }
            }
            if((y%8+1)!=0)
            {
                if(!prem)
                    stream << ", ";
                prem = false;
                stream << "0x";
                if(QString::number(value,16).size()<2)
                    stream << '0';
                stream << QString::number(value,16).toUpper();
                value=0;
            }
        }
        stream << "};" << endl;
        stream << "const Letter " << fontName << "_letter_" << QString::number(c) << " = {" << QString::number(width) << ", " << fontName << "_data_" << QString::number(c) << "};" << endl;
    }
    stream << endl << "// Table of letter struct" << endl;
    QString declareTable = "const Letter* " + fontName + "_letters[] = {";
    stream << declareTable << endl;
    for (c=first; c<=last; c++)
    {
        stream << QString(" ").repeated(declareTable.size()) << "&" << fontName << "_letter_" << QString::number(c) << ", " << endl;
    }
    stream << QString(" ").repeated(declareTable.size()-1) << "};";
    stream << endl << endl << "// Font structure" << endl;
    stream << "const Font " << fontName << " = {" << QString::number(height) << ", " << QString::number(first) << ", " << QString::number(last) << ", " << fontName << "_letters" << "};";

    stream << endl << "#endif";

    paint2.end();
    letters.save(outFileName+".png");
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QApplication::setApplicationName("img2raw");
    QApplication::setApplicationVersion("1.0");
    QTextStream out(stdout);

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption inputOption(QStringList() << "i" << "input", "Input image file (jpg, png, bmp ...)", "image.jpg");
    parser.addOption(inputOption);
    QCommandLineOption outputOption(QStringList() << "o" << "output", "Write generated data into <file>.", "image.c");
    parser.addOption(outputOption);

    parser.process(app);

    /*QFontDatabase db;
    foreach(QString family, db.families())
        out << family << endl;*/

    // check input
    if(!parser.isSet(inputOption))
    {
        out << "No input file or police name specified." << endl;
        return 1;
    }
    QString inputFile = parser.value(inputOption);

    // output
    QString outputFile = parser.value(outputOption);

    QFileInfo fileInfo(inputFile);

    // image mode
    QStringList imageExts;
    imageExts << "jpg" << "jpeg" << "png" << "bmp";
    if(imageExts.contains(fileInfo.suffix(), Qt::CaseInsensitive))
    {
        if(!QFile::exists(inputFile))
        {
            out << "File " << inputFile << " does not exist.";
            return 1;
        }
        QImage image(inputFile);
        exportImage(image, outputFile);

        return 0;
    }

    // font mode
    QRegExp regPolice("([a-zA-Z]+)([0-9]+)([bui]*)");
    if(regPolice.indexIn(inputFile) == 0)
    {
        QString fontName = regPolice.cap(1);
        int fontSize = regPolice.cap(2).toUInt();
        QString fontStyle = regPolice.cap(3);

        int bold = fontStyle.contains('b') ? QFont::Bold : QFont::Normal;
        bool italic = fontStyle.contains('i');

        QFont font(fontName, fontSize, bold, italic);
        out << "fontSize: " << fontSize << " family: " << font.family() << endl;
        exportfont(font, outputFile);

        return 0;
    }

    return 1;
}
