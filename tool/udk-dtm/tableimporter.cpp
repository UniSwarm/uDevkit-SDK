#include "tableimporter.h"

#include <QApplication>
#include <QClipboard>
#include <QCollator>
#include <QDebug>
#include <QRegularExpression>

TableImporter::TableImporter()
{
}

void TableImporter::fromClipBoard()
{
    QMap<QString, QString> map;
    QString clipText = QApplication::clipboard()->text();
    QTextStream stream(&clipText);

    QRegularExpression regexp("([0-9A-F]{2})h +(.+?)(?:[0-9A-F]{2}h|$)");
    while (!stream.atEnd())
    {
        int start = 0;
        QString line = stream.readLine();
        QString adress;
        QString def, defBase;
        QRegularExpressionMatch match;

        match = regexp.match(line, start);
        while (match.lastCapturedIndex() > 1)
        {
            adress = "0x" + match.captured(1);
            defBase = match.captured(2);
            defBase.remove(QRegularExpression(" \\.\\.\\..*"));
            def = defBase;
            def.remove(QRegularExpression(" [01]{7} $"));
            def.replace(QRegularExpression("\\(.*\\)"), "");
            def.replace(QRegularExpression(" (– )*"), "_");
            def.replace(QRegularExpression("/"), "_");
            def.remove(QRegularExpression("^\\_"));
            def.remove(QRegularExpression("\\_$"));
            if (!defBase.contains("Reserved"))
            {
                map.insert(adress, def);
            }

            start += match.capturedEnd(1);
            match = regexp.match(line, start);
        }
    }

    QMapIterator<QString, QString> i(map);
    while (i.hasNext())
    {
        i.next();
        qDebug().noquote().nospace() << "#define DMA_TRIGGER_" << i.value() << " " << i.key();
    }
}
