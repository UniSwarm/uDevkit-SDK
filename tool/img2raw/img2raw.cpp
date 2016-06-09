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
#include <QFont>

void exportimg(QImage image, QString filename)
{
    QFileInfo finfo(filename);
    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream stream(&file);

	stream << "#include <stdint.h>" << endl;
    stream << "__prog__ const uint16_t " << finfo.baseName() << "[] __attribute__((space(prog))) ={";

    QImage mirored = image.mirrored(false,false);

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

void exportfont(QFont font, QString filename )
{
    /*bool ok;
    char c;
    unsigned value;
    int x,y,height,nb,width;
    char first=' ',last='z';
    bool prem;
    QString res,fontName;
    font = QFontDialog::getFont(&ok,font);
    if (!ok) return;
    QFontMetrics metric(font);
    height=metric.height();
    ui->appercuFichier->clear();
    ui->listChar->clear();

    fontName=font.family().replace(" ","");
    if (fontName.size()>10) fontName = fontName.mid(0,10);
    if(font.bold()) fontName.append("b");
    if(font.underline()) fontName.append("u");
    if(font.italic()) fontName.append("i");

    if(font.pixelSize()!=-1)
        fontName.append(QString::number(font.pixelSize()));
    else
        fontName.append(QString::number(font.pointSize()));
    ui->appercuFichier->appendHtml("<font color=\"green\">"
                                   +QString("#ifndef _")+fontName+QString("_font_<br>")
                                   +QString("#define _")+fontName+QString("_font_<br>")
                                   +QString("#include \"police.h\"</font><br><br>"));
    QImage lettre(50,50,QImage::Format_Mono);
    QPainter paint;
    for (c=first;c<=last;c++)
    {
        if (c!='\\') ui->appercuFichier->appendHtml(QString("<font color=\"green\">// ")+c+QString("</font>"));
        else ui->appercuFichier->appendHtml(QString("<font color=\"green\">// (antislash)"+QString("</font>")));
        res="";
        res.append("<font color=\"blue\">const char </font>");
        res.append("<font color=\"black\">");
        res.append(fontName+QString("_data_")+QString::number(c)+QString("[] = {"));
        paint.begin(&lettre);
        paint.setFont(font);
        paint.drawRect(QRect(-1,-1,50,50));
        paint.drawText(QRect(0,0,20,20),Qt::AlignLeft|Qt::AlignTop,QString(c));
        paint.end();
        width=metric.width(c);
        prem = true;
        for(x=0;x<width;x++)
        {
            nb=0;
            value=0;
            for(y=0;y<height;y++)
            {
                if((y%8)==0 && y!=0)
                {
                    if(!prem) res.append(", ");
                    prem = false;
                    res.append(QString("0x"));
                    if(QString::number(value,16).size()<2) res.append('0');
                    res.append(QString::number(value,16).toUpper());
                    value=0;
                }
                if(lettre.pixel(x,y)==qRgb(0,0,0))
                {
                    value=value+(1<<(y%8));
                    nb++;
                }
            }
            if((y%8)!=0)
            {
                res.append(", ");
                res.append(QString("0x"));
                if(QString::number(value,16).size()<2) res.append('0');
                res.append(QString::number(value,16).toUpper());
                value=0;
            }
        }
        res.append(" };<br>");
        res.append("<font color=\"blue\">const Lettre </font>"+fontName+QString("_lettre_")+QString::number(c)+" = {"+QString::number(width)+","+fontName+QString("_data_")+QString::number(c)+"};<br>");
        ui->appercuFichier->appendHtml(res);
        ui->listChar->addItem(QString(c));
    }
    res="";
    ui->appercuFichier->appendHtml("<br><font color=\"green\">// Tableau des structures Lettre</font>");
    res.append(QString("<font color=\"blue\">const Lettre* </font>")+fontName+QString("_lettres[] = {"));
    for (c=first;c<last;c++)
    {
        res.append(QString("&")+fontName+QString("_lettre_")+QString::number(c)+QString(", "));
    }
    res.append(QString("&")+fontName+QString("_lettre_")+QString::number(c)+QString("}\n"));
    ui->appercuFichier->appendHtml(res+QString(";"));
    ui->appercuFichier->appendHtml("<font color=\"green\"><br>// Structure de la Police</font>");
    ui->appercuFichier->appendHtml("<font color=\"blue\">const Police </font>"+fontName+QString(" = {")+QString::number(height)+QString(",")+QString::number(first)+QString(",")+QString::number(last)+QString(",")+fontName+QString("_lettres")+QString("};"));

    ui->appercuFichier->appendHtml("<br><font color=\"green\">#endif</font>");

    pixm.setPixmap(QPixmap::fromImage(lettre).scaled(lettre.width()*10,lettre.height()*10));
    pixm.setPos(0,0);

    QString fileName = QFileDialog::getSaveFileName(this, "Enregistrer sous...",
                                                    fontName+QString(".h"),
                                                    "Fichier header (*.h)");

    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        file.write(ui->appercuFichier->toPlainText().toStdString().c_str(),ui->appercuFichier->toPlainText().size());
        file.close();
    }*/
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
        qDebug()<<inputFile;
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

    QFileInfo fileInfo(inputFile);

    // image mode
    QStringList imageExts;
    imageExts<<"jpg"<<"jpeg"<<"png"<<"bmp";
    if(imageExts.contains(fileInfo.suffix(), Qt::CaseInsensitive))
    {
        QImage image(inputFile);
        exportimg(image, outputFile);
        return 0;
    }

    // font mode

    return 1;
}
