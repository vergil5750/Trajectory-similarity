#ifndef CLIENT_H
#define CLIENT_H
#include <QTcpSocket>
#include <QHostAddress>
#include <QObject>
#include <QDataStream>
#include "sequence.h"
class Client:public QTcpSocket
{
    Q_OBJECT
public:

    quint16 nextBlockSize;
    quint8 requestType;

    explicit Client();
    ~Client();

    void closeConnection();
    void connectToServer(QString ipaddr, uint port);

    void upload(vector<Sequence> sequences);
    void search(Sequence sequence);
    void echo(QString msg);
};

#endif // CLIENT_H
