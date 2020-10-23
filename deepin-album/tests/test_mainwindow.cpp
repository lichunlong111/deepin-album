#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "mainwindow.h"
#include "test_qtestDefine.h"

#include <QTestEventList>

TEST(MainWindow, BtnGroupClick)
{
    if (!switch_on_test) {
        return;
    }
    qDebug() << "MainWindow BtnGroupClick count = " << count_testDefine++;
    MainWindow *w = dApp->getMainWindow();
    QTestEventList event;
    event.addMouseClick(Qt::MouseButton::LeftButton);
    event.simulate(w->getButG()->button(1));
    event.simulate(w->getButG()->button(2));
    event.clear();
    QTest::qWait(500);
}

//TEST(MainWindow, destory)
//{
//    MainWindow *w = dApp->getMainWindow();
//    delete w;
//    w = nullptr;
//}