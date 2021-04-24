#include "DisplayControl.h"

#include <qcustomplot.h>
#include <QDebug>

void DisplayControl::setVoltageRange (const QPointF &position, const QPoint zoomDelta, const Qt::KeyboardModifiers modifiers, bool isProperlyPaused, double maxWindowSize, QCustomPlot* axes)
{
    const bool isVertical = qAbs(zoomDelta.y()) > qAbs(zoomDelta.x());
    const bool isHorizontal = qAbs(zoomDelta.x()) > qAbs(zoomDelta.y());
    if (!(modifiers == Qt::ControlModifier) && isVertical) {
        zoomVertically(zoomDelta.y(), position.y(), axes);
    } else if (isHorizontal) {
        zoomHorizontally(zoomDelta.x(), position.x(), isProperlyPaused, maxWindowSize, axes);
    }
}

void DisplayControl::zoomVertically(const double delta, const double y, QCustomPlot *axes)
{
    if (qFuzzyIsNull(delta)) {
        return;
    }

    double c;
    if (qFuzzyIsNull(topRange) || qFuzzyIsNull(botRange) || qFuzzyCompare(topRange, botRange)) {
        c = 1. / 400.;
    } else {
        c = (topRange - botRange) / 400.;
    }

    QCPRange range = axes->yAxis->range();

    double pixPct = (double)100 - ((double)100 * (((double)axes->yAxis->pixelToCoord(y)-range.lower) / range.size()));
    if (pixPct < 0) pixPct = 0;
    if (pixPct > 100) pixPct = 100;

    qDebug() << "WHEEL @ " << pixPct << "%";
    qDebug() << range.upper;

    topRange -= delta / 120.0 * c * pixPct;
    botRange += delta / 120.0 * c * (100.0 - pixPct);

    topRange = qMin(topRange, 20.);
    botRange = qMin(botRange, 20.);

    // Never allow 0 delta between top and bottom
    if (qFuzzyCompare(topRange, botRange)) {
        topRange += 0.01;
        botRange -= 0.01;
    }

    topRangeUpdated(topRange);
    botRangeUpdated(botRange);
}

void DisplayControl::zoomHorizontally(const double delta, const double x, bool isProperlyPaused, double maxWindowSize, QCustomPlot *axes)
{
    if (qFuzzyIsNull(delta)) {
        return;
    }

    double c;
    if (qFuzzyIsNull(window)) {
        c = 1. / 200.;
    } else {
        c = window / 200.;
    }

    QCPRange range = axes->xAxis->range();

    double pixPct = 100. * (double(axes->xAxis->pixelToCoord(x)) - range.lower);

    if (qFuzzyIsNull(window) || qFuzzyCompare(range.upper, range.lower)) {
        pixPct = 1;
    } else {
        pixPct /= isProperlyPaused ? double(range.upper - range.lower)
                                   : double(window);
    }

    pixPct = qBound(0., pixPct, 100.);

    qDebug() << "WHEEL @ " << pixPct << "%";
    qDebug() << delta;

    if (! isProperlyPaused)
    {
        qDebug() << "TIGGERED";
        qDebug() << "upper = " << range.upper << "lower = " << range.lower;
        qDebug() << "window = " << window;
        qDebug() << c * ((double)pixPct);
        qDebug() << c * ((double)100 - (double)pixPct) * pixPct / 100;
    }

    window -= delta / 120.0 * c * pixPct;

    delay += delta / 120.0 * c * (100.0 - pixPct) * pixPct / 100.0;
    delay = qBound(0., delay, maxWindowSize - window);

    if (window <= 0.) {
        window = 0.01;
    } else if (window > maxWindowSize) {
        window = maxWindowSize;
    }

    qDebug() << window << delay;

    delayUpdated(delay);
    timeWindowUpdated(window);
}
