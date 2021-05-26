#pragma once

#include <QObject>

#include "desktop_settings.h"

class QCustomPlot;

class DisplayControl : public QObject
{
    Q_OBJECT
public:

    double delay = 0;
    double window = MAX_WINDOW_SIZE;
    double y0 = 0;
    double y1 = 0;
    double x0 = 0;
    double x1 = 0;
    double topRange = DEFAULT_TOP_RANGE;
    double botRange = DEFAULT_BOTTOM_RANGE;

    void setVoltageRange (const QPointF &position, const QPoint zoomDelta, const Qt::KeyboardModifiers modifiers, bool isProperlyPaused, double maxWindowSize, QCustomPlot* axes);

    void zoomVertically(const double delta, const double y, QCustomPlot *axes);
    void zoomHorizontally(const double delta, const double x, bool isProperlyPaused, double maxWindowSize, QCustomPlot* axes);

signals:
    void topRangeUpdated(double);
    void botRangeUpdated(double);
    void timeWindowUpdated(double);
    void delayUpdated(double);
};
