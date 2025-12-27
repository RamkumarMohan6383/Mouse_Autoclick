#ifndef AUTOCLICK_H
#define AUTOCLICK_H

#include <QObject>
#include <QPoint>
#include <QTimer>
#include <windows.h>

class AutoClick : public QObject {
    Q_OBJECT

public:
    explicit AutoClick(QObject *parent = nullptr);

    void startClicking();
    void performClick();
    void stopClicking();
    void setClickPosition(int x, int y);
    QPoint getClickPosition() const;

signals:
    void clicked();



private:
    QPoint clickPosition;
    QTimer clickTimer;
};

#endif // AUTOCLICK_H
