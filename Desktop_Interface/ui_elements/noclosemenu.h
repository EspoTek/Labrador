#ifndef NOCLOSEMENU_H
#define NOCLOSEMENU_H

#include <QWidget>
#include <QMenu>

//The menubar in Qt closes by default once a box has been checked.
//noCloseMenu is a simple class that keeps the menu open even after a box is checked.

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
