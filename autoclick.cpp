#include "autoclick.h"
#include <QDebug>

AutoClick::AutoClick(QObject *parent) : QObject(parent) {
    connect(&clickTimer, &QTimer::timeout, this, &AutoClick::performClick);
}

void AutoClick::setClickPosition(int x, int y) {
    clickPosition = QPoint(x, y);
    qDebug() << "Click position set to:" << x << "," << y;
}

QPoint AutoClick::getClickPosition() const {
    return clickPosition;
}

void AutoClick::startClicking() {
    if (clickPosition.isNull()) {
        qDebug() << "Click position not set!";
        return;
    }
    qDebug() << "Auto-clicking started...";
    clickTimer.start(3000); // Click every 3 seconds
}

void AutoClick::stopClicking() {
    qDebug() << "Auto-clicking stopped.";
    clickTimer.stop();
}

void AutoClick::performClick() {
    if (!clickPosition.isNull()) {
        SetCursorPos(clickPosition.x(), clickPosition.y());

        // Simulate mouse press and release
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        Sleep(50);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

        emit clicked();
        qDebug() << "Auto-click performed at:" << clickPosition;
    }
}
