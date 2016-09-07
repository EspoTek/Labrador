#include "noclosemenu.h"

noCloseMenu::noCloseMenu(QWidget *parent) : QMenu(parent)
{

}

//Dankon, Jakob Leben
//http://stackoverflow.com/questions/2050462/prevent-a-qmenu-from-closing-when-one-of-its-qaction-is-triggered

void noCloseMenu::mouseReleaseEvent(QMouseEvent *e)
{
    QAction *action = activeAction();
    if (action && action->isEnabled()) {
        action->setEnabled(false);
        QMenu::mouseReleaseEvent(e);
        action->setEnabled(true);
        action->trigger();
    }
    else
        QMenu::mouseReleaseEvent(e);
}
