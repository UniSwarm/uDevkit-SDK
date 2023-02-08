#include <QApplication>

#include "cwritter.h"
#include "edcparser.h"

#include <QCollator>
#include <QDateTime>
#include <QDebug>
#include <QDirIterator>
#include <QRegularExpression>

#include "edcdb.h"
#include "nvmheadercreator.h"
#include "periphericalheadercreator.h"
#include "tableimporter.h"

#ifdef WIN32
QString edsPath = "C:/Program Files/Microchip/MPLABX/v5.50/packs/Microchip/";
#else
QString edsPath = "/opt/microchip/mplabx/v6.00/packs/Microchip/";
#endif

QStringList picFileList(const QString &picFilter, const QStringList &excludeDeviceList)
{
    QStringList fileList;

    QRegularExpression picFileRegExp(picFilter);
    QDirIterator it(edsPath, QStringList("*.PIC"), QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    int fileCount = 0;
    while (it.hasNext())
    {
        const QString &fileName = it.next();
        QFileInfo fileInfo(fileName);
        fileCount++;

        if (excludeDeviceList.contains(fileInfo.baseName()))
        {
            continue;
        }
        if (picFileRegExp.match(fileInfo.fileName()).hasMatch())
        {
            fileList << fileName;
        }
    }

    // Remove redondant CPU
    QCollator coll;
    coll.setNumericMode(true);
    std::sort(fileList.begin(), fileList.end(), [&](const QString &s1, const QString &s2) {
        return coll.compare(s1, s2) > 0;
    });
    QSet<QString> set;
    QMutableListIterator<QString> i(fileList);
    while (i.hasNext())
    {
        QFileInfo fileInfo(i.next());
        if (set.contains(fileInfo.baseName()))
        {
            i.remove();
        }
        set.insert(fileInfo.baseName());
    }

    return fileList;
}

int main(int argc, char *argv[])
{
    qint64 startMs;
    QApplication a(argc, argv);

    /*TableImporter t;
    t.fromClipBoard();
    return 0;*/

    // QString picFilter = "^(DS)?PIC(30|33|24)[^C]";

    QStringList excludeDeviceList("PIC32MZ1025W104132");

    QString allPicListFilter = "^(DS)?PIC(30|33|24|32)";
    startMs = QDateTime::currentMSecsSinceEpoch();
    EdcDb db;
    db.loadDb(picFileList(allPicListFilter, excludeDeviceList));
    qDebug() << "Load DB in" << QDateTime::currentMSecsSinceEpoch() - startMs << "ms";

    startMs = QDateTime::currentMSecsSinceEpoch();
    // NvmHeaderCreator(db, "^(DS)?PIC(30|33|24)", "nvm_pic24_dspic30f_dspic33.h");

    // QString picFilter = "^(DSPIC33[EC]|PIC24E)";
    // QString sfrFilter = "ADCBUF([0-9]+)";
    // QString deviceName = "ADC_CHANNEL";
    // QString sfrFilter = "ADFL[0-9]+DAT";
    // QString deviceName = "ADC_DIGITAL_FILTER";
    // QString sfrFilter = "ADCMP[0-9]+CON";
    // QString deviceName = "ADC_COMPARATOR";

    ////QString sfrFilter = "^C1FLTCON([0-9]+)L";
    PeriphericalHeaderCreator(db, "^DSPIC33C", "CAN", "^C1FLTCON([0-9]+)L", (PeriphCap)(P_COUNT), "can_dspic33c_flt.h");
    PeriphericalHeaderCreator(db, "^DSPIC33C", "CAN", "^C([0-9]+)CONL$", (PeriphCap)(P_COUNT), "can_dspic33c.h");
    PeriphericalHeaderCreator(db, "^PIC32", "CAN", "^C(FD)*([0-9]+)CON$", (PeriphCap)(P_COUNT), "can_pic32.h");
    PeriphericalHeaderCreator(db, "^PIC32", "CAN", "^CFD([0-9]+)CON$", (PeriphCap)(P_COUNT), "canfd_pic32.h");

    PeriphericalHeaderCreator(db, "^(DSPIC33|PIC24)", "CCP", "CCP([0-9]+)CON1L", (PeriphCap)(P_COUNT), "ccp_pic24_dspic33.h");
    PeriphericalHeaderCreator(db, "^PIC32", "CCP", "CCP([0-9]+)CON1", (PeriphCap)(P_COUNT), "ccp_pic32.h");

    PeriphericalHeaderCreator(db, "^(DSPIC3[03]|PIC24)", "I2C", "^I2C([0-9]*)CONL*$", (PeriphCap)(P_COUNT), "i2c_pic24_dspic30f_dspic33.h");
    PeriphericalHeaderCreator(db, "^(DSPIC3[03]|PIC24)", "I2C", "^I2C1CONL$", (PeriphCap)(P_COUNT), "i2c_pic24_dspic30f_dspic33_ext.h");
    PeriphericalHeaderCreator(db, "^PIC32", "I2C", "^I2C([0-9]+)CON$", (PeriphCap)(P_COUNT), "i2c_pic32.h");

    PeriphericalHeaderCreator(db, "^(DSPIC33[EC]|PIC24E)", "QEI", "QEI([0-9]*)CON", (PeriphCap)(P_COUNT), "qei_pic24e_dspic33e.h");
    PeriphericalHeaderCreator(db, "^(DSPIC33F|PIC24F)", "QEI", "QEI([0-9]*)CON", (PeriphCap)(P_COUNT), "qei_pic24f_dspic33f.h");
    PeriphericalHeaderCreator(db, "^PIC32MK", "QEI", "QEI([0-9]+)CON", (PeriphCap)(P_COUNT), "qei_pic32mk.h");

    PeriphericalHeaderCreator(db, "^DSPIC33C", "SENT", "SENT([0-9]+)CON1$", (PeriphCap)(P_COUNT), "sent_dspic33c.h");

    PeriphericalHeaderCreator(db, "^(DSPIC33[EC]|PIC24E)", "SPI", "SPI([0-9]+)CON1L*$", (PeriphCap)(P_COUNT), "spi_pic24e_dspic33e.h");

    PeriphericalHeaderCreator(db, "^DSPIC33C", "TIMER", "^T([0-9]+)CON", (PeriphCap)(P_COUNT), "timer_dspic33c.h");

    PeriphericalHeaderCreator(db, "^DSPIC33C.*[0-9]{3}$", "CMP", "^DAC([0-9]+)CONL", (PeriphCap)(P_COUNT), "cmp_dspic33c.h");
    PeriphericalHeaderCreator(db, "^DSPIC33C.*S1$", "CMP", "^DAC([0-9]+)CONL", (PeriphCap)(P_COUNT), "cmp_dspic33c_sec.h");

    // QString picFilter = "^((DSPIC33|PIC24)E|24FJ[0-9]+[GD])";
    // QString picFilter = "^(DSPIC3[03]F|24FJ[0-9]+M)";
    // QString sfrFilter = "^OC[0-9]+CON[1]*$";
    // QString deviceName = "OC";

    // QString picFilter = "^((DSPIC33|PIC24)E|24FJ[0-9]+[GD])";
    // QString picFilter = "^(DSPIC3[03]F|24FJ[0-9]+M)";
    // QString sfrFilter = "^IC[0-9]+CON[1]*$";
    // QString deviceName = "IC";

    PeriphericalHeaderCreator(db, "^DSPIC33C", "UART", "^U([0-9]+)MODE$", (PeriphCap)(P_COUNT), "uart_dspic33c.h");

    QString picFilter = "^(DSPIC33C)";
    QString sfrFilter = "^DMACH([0-9]+)";
    QString deviceName = "DMA";
    QString outputFileName = "can_dspic33.h";

    /*qDebug() << picFileList("^DSPIC30", excludeDeviceList).count();
    qDebug() << picFileList("^DSPIC33CH", excludeDeviceList).count();
    qDebug() << picFileList("^DSPIC33CK", excludeDeviceList).count();
    qDebug() << picFileList("^DSPIC33EP", excludeDeviceList).count();
    qDebug() << picFileList("^DSPIC33EV", excludeDeviceList).count();
    qDebug() << picFileList("^DSPIC33FJ", excludeDeviceList).count();
    qDebug() << picFileList("^PIC24EP", excludeDeviceList).count();
    qDebug() << picFileList("^PIC24FV*[0-9]", excludeDeviceList).count();
    qDebug() << picFileList("^PIC24FJ", excludeDeviceList);
    qDebug() << picFileList("^PIC24HJ", excludeDeviceList).count();

    qDebug() << picFileList("^DSPIC30", excludeDeviceList).count() \
    + picFileList("^DSPIC33CH", excludeDeviceList).count() \
    + picFileList("^DSPIC33CK", excludeDeviceList).count() \
    + picFileList("^DSPIC33EP", excludeDeviceList).count() \
    + picFileList("^DSPIC33EV", excludeDeviceList).count() \
    + picFileList("^DSPIC33FJ", excludeDeviceList).count() \
    + picFileList("^PIC24EP", excludeDeviceList).count() \
    + picFileList("^PIC24FV*[0-9]", excludeDeviceList).count() \
    + picFileList("^PIC24FJ", excludeDeviceList).count() \
    + picFileList("^PIC24HJ", excludeDeviceList).count();
    return 0;*/

    qDebug() << "Processing in" << QDateTime::currentMSecsSinceEpoch() - startMs << "ms";

    return 0;
}
