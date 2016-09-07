#ifndef NOCLOSEMENU_H
#define NOCLOSEMENU_H

#include <QWidget>
#include <QMenu>

class noCloseMenu : public QMenu
{
    Q_OBJECT
public:
    explicit noCloseMenu(QWidget *parent = 0);
private:
    void mouseReleaseEvent(QMouseEvent *e);
signals:

public slots:
};

#endif // NOCLOSEMENU_H
