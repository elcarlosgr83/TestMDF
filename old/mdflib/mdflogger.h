#pragma once
#include <QObject>
#include <QString>

class MDFLogger : public QObject {
    Q_OBJECT
public:
    explicit MDFLogger(QObject *parent = nullptr);

    Q_INVOKABLE void write(const QString &filePath);
    Q_INVOKABLE void read(const QString &filePath);
};
