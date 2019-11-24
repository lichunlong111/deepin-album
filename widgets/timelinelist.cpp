#include "timelinelist.h"
#include "controller/signalmanager.h"

TimelineList::TimelineList(QWidget *parent) : DListWidget(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setResizeMode(QListView::Adjust);
    setViewMode(QListView::ListMode);
    setFlow(QListView::TopToBottom);
    setSpacing(0);
    setDragEnabled(false);
//    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    has = false;
    installEventFilter(this);

}

void TimelineList::addItemForWidget(QListWidgetItem *aitem)
{
    int y = 1;
    yList.append(y);
    this->addItem(aitem);

}

void TimelineList::dragMoveEvent(QDragMoveEvent *event)
{
    return QListWidget::dragMoveEvent(event);
}

void TimelineList::mouseMoveEvent(QMouseEvent *event)
{
    return QListWidget::mouseMoveEvent(event);
}

void TimelineList::paintEvent(QPaintEvent *e)
{
    if (this->count() > 0) {
        int ccount = count();
        for (int i = 0; i < ccount; i++) {
            QListWidgetItem *pItem = this->item(i);
            TimelineItem *pWidget = (TimelineItem *)itemWidget(pItem);
            if ((pWidget->y() <= pWidget->m_title->height()) && (pWidget->y() > 0)) {
#if 1
                QListWidgetItem *pLastItem;
                pLastItem = this->item(i - 1);
                TimelineItem* pLastWidget = (TimelineItem*)itemWidget(pLastItem);
                emit sigMoveTime(pWidget->y() - pWidget->m_title->height(),pLastWidget->m_sdate,pLastWidget->m_snum,pLastWidget->m_Chose->text());
#endif
                pWidget->m_title->setVisible(true);
                pWidget->m_date->setText(pWidget->m_sdate);
                pWidget->m_num->setText(pWidget->m_snum);
                pWidget->m_Chose->setVisible(true);

            } else if ((pWidget->y() <= 0) && (pWidget->y() + pWidget->m_title->height() > 0)) {
                has = false;
                emit sigNewTime(pWidget->m_sdate, pWidget->m_snum, i);
                pWidget->m_date->setText("");
                pWidget->m_num->setText("");
                pWidget->m_Chose->setVisible(false);
            } else {
                pWidget->m_title->setVisible(true);
                pWidget->m_date->setText(pWidget->m_sdate);
                pWidget->m_num->setText(pWidget->m_snum);
                pWidget->m_Chose->setVisible(true);
            }
            yList[i] = pWidget->y();
        }
    }
    return QListWidget::paintEvent(e);
}

bool TimelineList::eventFilter(QObject *obj, QEvent *e)
{
    Q_UNUSED(obj)
    if (e->type() == QEvent::Wheel && QApplication::keyboardModifiers () == Qt::ControlModifier) {
        return true;
    }

    return false;
}
