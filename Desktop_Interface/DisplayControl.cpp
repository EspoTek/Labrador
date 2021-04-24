#include "DisplayControl.h"

#include <QWheelEvent>
#include <qcustomplot.h>
#include <QDebug>

void DisplayControl::setVoltageRange (QWheelEvent* event, bool isProperlyPaused, double maxWindowSize, QCustomPlot* axes)
{
    if (!(event->modifiers() == Qt::ControlModifier) && qAbs(event->angleDelta().y()) > qAbs(event->angleDelta().x())) {
        zoomVertically(event->angleDelta().y(), event->position().y(), axes);
    }
    else
    {
        zoomHorizontally(event->angleDelta().x(), event->position().x(), isProperlyPaused, maxWindowSize, axes);
    }

}

void DisplayControl::zoomVertically(const double delta, const double y, QCustomPlot *axes)
{
        double c = (qFuzzyCompare(topRange, botRange) ? 1. : (topRange - botRange)) / double(400);

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
        double c = (window) / 200.;
        QCPRange range = axes->xAxis->range();

        double pixPct = 100. * (double(axes->xAxis->pixelToCoord(x)) - range.lower);

        pixPct /= isProperlyPaused ? double(range.upper - range.lower)
                                   : double(window);

        if (pixPct < 0)
            pixPct = 0;

        if (pixPct > 100)
            pixPct = 100;

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

        // NOTE: delayUpdated and timeWindowUpdated are called more than once beyond here,
        // maybe they should only be called once at the end?

        qDebug() << window << delay;

        delayUpdated(delay);
        timeWindowUpdated(window);

}
