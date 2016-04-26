/**
 * @file img2raw.c
 * @author Sebastien CAUX (sebcaux)
 * @copyright Robotips 2016
 *
 * @date April 25, 2016, 18:39 PM 
 * 
 * @brief Tool to transform image in const C raw data (xc16 format)
 */

#include <QCoreApplication>

#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDebug>
#include <QCommandLineParser>

#include <QImage>

void exportimg(QImage image, QString filename)
{
    QFileInfo finfo(filename);
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);

    stream << "__prog__ const unsigned short " << finfo.baseName() << "[] __attribute__((space(prog))) ={";

    QImage mirored = image.mirrored(false,true);

    for(int x=0; x<mirored.width(); x++)
    {
        stream << endl;
        for(int y=0; y<mirored.height(); y++)
        {
            QRgb color = mirored.pixel(x,y);

            unsigned short syscolor = 0;
            syscolor |= (qRed(color)&0xF8)<<8;
            syscolor |= (qGreen(color)&0xFC)<<3;
            syscolor |= (qBlue(color)&0xF8)>>3;
            stream << "0x" << QString::number(syscolor,16);
            if(x!=mirored.width()-1 || y!=mirored.height()-1) stream << ", ";
        }
    }
    stream << endl << "};";

    file.close();
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("img2raw");
    QCoreApplication::setApplicationVersion("1.0");
    
    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption inputOption(QStringList() << "i" << "input", "Input image file (jpg, png, bmp ...)", "image.jpg");
    parser.addOption(inputOption);
    QCommandLineOption outputOption(QStringList() << "o" << "output", "Write generated data into <file>.", "image.c");
    parser.addOption(outputOption);

    parser.process(app);

    // check input
    if(!parser.isSet(inputOption))
    {
        qDebug()<<"No input file specified.";
        return 1;
    }
    QString inputFile = parser.value(inputOption);
    if(!QFile::exists(inputFile))
    {
        qDebug()<<"File " << inputFile << " does not exist.";
        return 1;
    }

    // outpout
    QString outputFile = parser.value(outputOption);
    
    /*QString filename = "../../../images_ecrans/new/Squaretips-smile-3.2.jpg";
    QImage image(filename);
    int ydec = (image.height()-(float)image.width()*320.0/480.0)/2.0;
    qDebug()<<ydec;
    QImage imageratio = image.copy(0,ydec,image.width(),image.height()-ydec*2);
    QImage imagesc = imageratio.scaled(480,320,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    exportimg(imagesc, filename);

    QImage zoeil1 = imagesc.copy(55,60,160,160);
    exportimg(zoeil1, filename+"_zoeuil1");

    QImage zoeil2 = imagesc.copy(267,60,160,160);
    exportimg(zoeil2, filename+"_zoeuil2");

    QImage bouche = imagesc.copy(190,220,110,90);
    exportimg(bouche, filename+"_bouche");

    ui->label->setPixmap(QPixmap::fromImage(imagesc));*/

    /*QDir dir("../../../images_ecrans/new/out/");
    foreach(QString file, dir.entryList(QStringList("*.jpg")))
    {
        qDebug()<<dir.path() + "/" + file;
        QImage image(dir.path() + "/" + file);
        exportimg(image, dir.path() + "/" + file.replace(".jpg",""));
    }*/
    
    exportimg(QImage(inputFile), outputFile);
}
