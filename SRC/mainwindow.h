#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QPainter>
#include <QtCore>
#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <vector>
#include <QList>
#include <time.h>
#include <windows.h>
#include <qlistwidget.h>
#include <QMouseEvent>
#include "mytabwidget.h"
#include <QTextStream>
#include <QFile>

// <a href="https://icons8.com/icon/8555/Delete-Message-Filled">Delete message filled and other icons by Icons8</a>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    QGraphicsScene *scene; //scene on main window
    myTabWidget *tab; // tab window
    int item_id;
    int x1_view; // scene rectangle coordinates
    int y1_view;
    int x2_view;
    int y2_view;
    void rotateSceneItem(QGraphicsItem* item,int x, int y, int angle);
    QStringList myCommandList;

private slots:
    void on_myPushButton_clicked();
    void resizeEvent(QResizeEvent *);
    // methods to case 11
     void return_pen(QGraphicsRectItem* rect,QPen tmp_pen);

   // void on_myLineEdit_cursorPositionChanged(int arg1, int arg2);
     void on_clearButton_clicked();
     void on_myClearScreenButton_clicked();
     void on_mySaveToFileButton_clicked();
     void on_myListWidget_itemClicked(QListWidgetItem *item);
	 void mouseMoveEvent(QMouseEvent*);
     void on_actionClearButton_triggered();
     void on_actionTakeScreenButton_triggered();
     void on_actionFaqButton_triggered();
     void ProvideContextMenu(const QPoint &);
     void on_actionExplainButton_triggered();
};


////////////////////////////////////////////////////////////////////////////////



#endif // MAINWINDOW_H
