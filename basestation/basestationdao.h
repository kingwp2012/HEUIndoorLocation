#ifndef BASESTATIONASESTATIONDAO_H
#define BASESTATIONASESTATIONDAO_H

#include <QObject>

class BaseStationDao : public QObject
{
    Q_OBJECT
public:
    explicit BaseStationDao(QObject *parent = 0);

signals:

public slots:
};

#endif // BASESTATIONASESTATIONDAO_H