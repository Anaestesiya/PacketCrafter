#ifndef CPACKETHANDLER_H
#define CPACKETHANDLER_H

#include "protoFields/cfields.h"

#include <QProcess>
#include <QMessageBox>
#include <QProgressDialog>

class CPacketHandler: public QWidget
{
public:
    CPacketHandler(QWidget *parent = nullptr);
    QString formatProtos();
    int sendPacket();

    QString packet;
    QString filename_;

    QList<CFields *> protoVector;
    QString Ifc;
    int packetCount;
    int period;

private:
    QProcess *process_;
    QMessageBox *messageBox_;
    QProgressDialog *progressDialog_;
    int progress;

private slots:
    void onReadyReadStandardOutput();
    void onReadyReadStandardError();
    void onProcessFinished();
    void showProgressDialog();
    void onProgressDialogCanceled();
};

#endif // CPACKETHANDLER_H
