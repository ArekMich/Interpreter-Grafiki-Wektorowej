#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myarcobject.h"
#include <QGraphicsItem>
#include <vector>
#include <list>
#include <iostream>
#include <QShortcut>
#include <QTimer>
#include <time.h>
#include <stdlib.h>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenu>
#include <QPoint>
#include <QGraphicsRotation>
#include "mytabwidget.h"
#include <QTextStream>
#include <QFile>

// <a href="https://icons8.com/icon/8555/Delete-Message-Filled">Delete message filled and other icons by Icons8</a>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    item_id(0),
    x1_view(0), y1_view(0), x2_view(800), y2_view(600)
{
    //setting screen scene
	this->setMouseTracking(true);
	
    ui->setupUi(this);
	ui->centralWidget->setMouseTracking(true);
	
    scene = new QGraphicsScene(this); //
    scene->setSceneRect(x1_view,y1_view,x2_view,y2_view);
    scene->setBackgroundBrush(Qt::white);
    ui->myScreen->setScene(scene); //
    ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // unexpected behavior
	ui->myScreen->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->myScreen->setRenderHint(QPainter::Antialiasing);
    ui->myScreen->setRenderHint(QPainter::SmoothPixmapTransform);

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::rotateSceneItem(QGraphicsItem* item,int x,int y,int angle)
{
    QTransform basic_tr = item->transform();
    QPointF tr_point = item -> mapFromScene(x,y);
    basic_tr.translate(tr_point.rx(),tr_point.ry());
    item->setTransformOriginPoint(tr_point);
    basic_tr.rotate(angle);
    basic_tr.translate(-tr_point.rx(),-tr_point.ry());
    item->setTransform(basic_tr);
}

void MainWindow::return_pen(QGraphicsRectItem* rect,QPen tmp_pen){
    rect->setPen(tmp_pen);
}

void MainWindow::on_myPushButton_clicked()
{
    // always when clicked, we have to check the first part of the command
    // alternatively we can change it and simply write split()
    QString command;
    QRegExp re("^-?\\d*");  // a digit (\d), zero or more times (*)
    int i = 0;
    while((ui ->myLineEdit ->text())[i] != ' ' && ui ->myLineEdit ->text()[i] != '\0'){
        command[i++] = (ui ->myLineEdit ->text())[i];
    }

    // now we have our command in command variable
    QString commandToWrite = ui->myLineEdit ->text();
    QString command_list[] ={"range", "background", "line", "rectangle",
                  "circle", "ellipse", "arc", "fill",
                  "delete","move", "rotate", "show",
                  "clear", "write", "read", "save","scale",
                  "pixmap"};
   // check if command is in command list
    int flag =0;
    int command_number;
    for(int i=0; i <= 17; i++){
        if(command == command_list[i]){
            flag = 1;
            command_number = i;
        }
    }
    if ( flag == 0 || ui ->myLineEdit ->text().size() > 80 ){
        ui->myLineEdit->setText("Wrong command!, check command list...");
    }

    // switch case that handles all commands
    switch (command_number) {
    case 0: // range
    {
        // check if command is composed of proper number of parts
        if( ui ->myLineEdit ->text().split(' ').size() != 5 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        int x1_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y1_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int x2_coord = ui ->myLineEdit ->text().split(' ')[3].toInt();
        int y2_coord = ui ->myLineEdit ->text().split(' ')[4].toInt();


        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]) ) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        x1_view = x1_coord;
        y1_view = y1_coord;
        x2_view = x2_coord;
        y2_view = y2_coord;
        //check if coordinates are integer value
        int x_size = abs(x2_view - x1_view);
        int y_size = abs(y2_view - y1_view);

        scene->setSceneRect(x1_view,y1_view,x2_view,y2_view);
        ui ->myScreen->fitInView(x1_view,y1_view,x_size,y_size);

        scene->update();
        myCommandList << commandToWrite;
        break;
    }
    case 1: //background
    {
        // check if command is composed of proper number of parts
        if( ui ->myLineEdit ->text().split(' ').size() != 2 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        QColor color = ui ->myLineEdit->text().split(' ')[1];
        QBrush brush = QBrush(color,Qt::SolidPattern);
        scene->setBackgroundBrush(brush); // example of color #00FFFF #008080 #800080

        myCommandList << commandToWrite;
        break;
    }
    case 2://line
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 6 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        int x1_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y1_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int x2_coord = ui ->myLineEdit ->text().split(' ')[3].toInt();
        int y2_coord = ui ->myLineEdit ->text().split(' ')[4].toInt();
        QColor color = ui ->myLineEdit ->text().split(' ')[5];


        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]) ) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        QPen pencil = QPen(color);
        QGraphicsLineItem* line = new QGraphicsLineItem(x1_coord,y1_coord,x2_coord,y2_coord);
        line->setPen(pencil);

        scene->addItem(line);
        ui->myListWidget->addItem("ID: "+QString::number(item_id)+" ITEM: line");

        ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        myCommandList << commandToWrite;
        break;
    }
    case 3: //rectangle
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 6 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        int x1_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y1_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int x2_coord = ui ->myLineEdit ->text().split(' ')[3].toInt();
        int y2_coord = ui ->myLineEdit ->text().split(' ')[4].toInt();
        QColor color = ui ->myLineEdit ->text().split(' ')[5];


        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]) ) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        // handle some issues about color
        QPen pencil = QPen(color);
        QGraphicsRectItem* rect = new QGraphicsRectItem(x1_coord,y1_coord,x2_coord,y2_coord);
        rect->setPen(pencil);


        scene->addItem(rect);
        ui->myListWidget->addItem("ID: "+QString::number(item_id)+" ITEM: rectangle");

        ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        myCommandList << commandToWrite;
        break;
    }
    case 4: //circle
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 5 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        int x_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int r = ui ->myLineEdit ->text().split(' ')[3].toInt();


        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3])) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        QColor color = ui ->myLineEdit ->text().split(' ')[4];
        QPen pencil = QPen(color);
        QGraphicsEllipseItem* circle = new QGraphicsEllipseItem(x_coord-r,y_coord-r,2*r,2*r);
        circle->setPen(pencil);

        scene->addItem(circle);
        ui->myListWidget->addItem("ID: "+QString::number(item_id)+" ITEM: circle");

        ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        myCommandList << commandToWrite;
        break;

    }
    case 5: // ellipse
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 6 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        int x_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int rx_coord = ui ->myLineEdit ->text().split(' ')[3].toInt();
        int ry_coord = ui ->myLineEdit ->text().split(' ')[4].toInt();
        QColor color = ui ->myLineEdit ->text().split(' ')[5];

        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]) ) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        QPen pencil = QPen(color);
        QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(x_coord-rx_coord,y_coord-ry_coord,2*rx_coord,2*ry_coord);
        ellipse->setPen(pencil);

        scene ->addItem(ellipse);
        ui ->myListWidget ->addItem("ID: "+QString::number(item_id)+" ITEM: ellipse");

        ui ->myScreen ->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        myCommandList << commandToWrite;
        break;

    }
    case 6: // Arc
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 8 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        int x_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int rx_coord = ui ->myLineEdit ->text().split(' ')[3].toInt();
        int ry_coord = ui ->myLineEdit ->text().split(' ')[4].toInt();
        int b = ui ->myLineEdit ->text().split(' ')[5].toInt();
        int e = ui ->myLineEdit ->text().split(' ')[6].toInt();
        QColor color = ui ->myLineEdit->text().split(' ')[7];


        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[5]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[6])) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        MyArcObject* arch = new MyArcObject(x_coord-rx_coord,y_coord-ry_coord,2*rx_coord,2*ry_coord,b,e);
        arch->setPen(color);

        scene->addItem(arch);
        ui ->myListWidget ->addItem("ID: "+QString::number(item_id)+" ITEM: arch");

        ui->myScreen ->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        myCommandList << commandToWrite;

        break;

    }
    case 7: // fill
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 3 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){

              QColor color = ui ->myLineEdit->text().split(' ')[2];
              for(int i=0;i<ui ->myListWidget ->count();i++){

                  QString item_type = ui ->myListWidget ->item(i)->text().split(' ')[3];
                  int reversed_id = scene ->items().size() - i - 1;

                  if( item_type == "rectangle"){
                      QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                      rect ->setBrush(color);
                     // QBrush brush(QPixmap(":\images\GofT.jpg"));
                     // rect ->setBrush(brush);
                      myCommandList << commandToWrite;
                  }
                  else if( item_type == "circle"){
                      QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                      circle ->setBrush(color);
                      myCommandList << commandToWrite;
                  }
                  else if( item_type == "ellipse"){
                      QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                      ellipse ->setBrush(color);
                      myCommandList << commandToWrite;
                  }
                  else if( item_type == "arch" || item_type == "line"){
                      ui ->myLineEdit ->setText("You cannot fill arch or line with color...");
                      myCommandList << commandToWrite;
                  }
                  else{
                      ui ->myLineEdit ->setText("Staph...");
                  }
              }
         }


        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1])) ){
            ui->myLineEdit->setText("ID must be an integer number");
            break;
        }
        else{
            int id = ui ->myLineEdit->text().split(' ')[1].toInt();
            QString id_str = ui ->myLineEdit->text().split(' ')[1];
            int max_id_size = 4; // handling if someone pass very very huge number (int range issue)

            QColor color = ui ->myLineEdit->text().split(' ')[2];

            // handling if id is out of range
            if( id >= scene ->items().size() || id < 0 || id_str.size() > max_id_size ){
                ui ->myLineEdit ->setText("Index out of range...");
                break;
            }

            //checking id from list
            QString item_type = ui ->myListWidget ->item(id)->text().split(' ')[3];
            int reversed_id = scene ->items().size() - id - 1;

            if( item_type == "rectangle"){
                QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                rect ->setBrush(color);
                myCommandList << commandToWrite;
            }
            else if( item_type == "circle"){
                QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                circle ->setBrush(color);
                myCommandList << commandToWrite;
            }
            else if( item_type == "ellipse"){
                QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                ellipse ->setBrush(color);
                myCommandList << commandToWrite;
            }
            else if( item_type == "line"){
                ui ->myLineEdit ->setText("You cannot fill line with color...");
            }
            else if( item_type == "arch"){
                ui ->myLineEdit ->setText("You cannot fill arch with color...");
            }
            else{
                ui ->myLineEdit ->setText("Staph...");
            }
        }
        break;
    }
    case 8: //delete
        {
        if( ui ->myLineEdit ->text().split(' ').size() != 2 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){
                      scene ->clear();
                      ui ->myListWidget->clear();
                      myCommandList << commandToWrite;
        }

        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1])) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }
        else{
          int tmp_id = ui ->myLineEdit->text().split(' ')[1].toInt();
          QString id_str = ui ->myLineEdit->text().split(' ')[1];

          int max_id_size = 4; // handling if someone pass very very huge number (int range issue)

          // handling if id is out of range
          if( tmp_id >= scene ->items().size() || tmp_id < 0 || id_str.size() > max_id_size ){
              ui ->myLineEdit ->setText("Index out of range...");
              break;
          }

          int num=ui->myListWidget->count()-tmp_id-1;
          scene->removeItem(scene->items().at(num));

          QListWidgetItem *it = ui->myListWidget->takeItem(tmp_id);
          delete it;

         if(num!=0){
             for(int i=ui->myListWidget->count()-1;i>=tmp_id;i--){
                // std::string tmp_str=ui->myListWidget->item(i)->text().toStdString();
                   int number = ui->myListWidget->item(i)->text().split(' ')[1].toInt();
                   number -= 1;

                   std::string str=std::to_string(number);
                   std::cout<<str<<std::endl;
                   std::cout<<number<<std::endl;
                   QString all_string=ui->myListWidget->item(i)->text().split(' ')[0]+" "+QString::fromStdString(str)+" "+ui->myListWidget->item(i)->text().split(' ')[2]
                                 +" "+ui->myListWidget->item(i)->text().split(' ')[3];
                   std::cout<<all_string.toStdString()<<std::endl;
                   ui->myListWidget->item(i)->setText(all_string);

             }
         }

        }
          ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
          scene ->update();
          item_id--;
          myCommandList << commandToWrite;
          break;
        }
    case 9: //move
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 4 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){
            myCommandList << commandToWrite;
            for(int i=0;i<ui ->myListWidget ->count();i++){
                int x_vector = ui ->myLineEdit->text().split(' ')[2].toInt();
                int y_vector = ui ->myLineEdit->text().split(' ')[3].toInt();

                if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
                       re.exactMatch(ui ->myLineEdit ->text().split(' ')[3])
                    ) ){
                    ui->myLineEdit->setText("Coordinate must be an integer number");
                    break;
                }

                //checking id from list
                QString item_type = ui->myListWidget->item(i)->text().split(' ')[3];
                int reversed_id = scene->items().size() - i - 1;

                if( item_type == "rectangle"){
                    QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                    rect ->moveBy(x_vector,y_vector);
                }
                else if( item_type == "circle"){
                    QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                    circle ->moveBy(x_vector,y_vector);
                }
                else if( item_type == "ellipse"){
                    QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                    ellipse ->moveBy(x_vector,y_vector);
                }
                else if( item_type == "line"){
                   QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));

                   line ->moveBy(x_vector,y_vector);
                }
                else if( item_type == "arch"){
                    MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));

                    arch ->moveBy(x_vector,y_vector);
                }
                else{
                    ui->myLineEdit->setText("Wrong command, check command list...");
                }

            }

        }

        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
                    re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
                    re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]))  ){
            ui->myLineEdit->setText("Coordinate and ID must be an integer number");
            break;
        }
        else
        {
            int id = ui ->myLineEdit ->text().split(' ')[1].toInt();
            int x_vector = ui ->myLineEdit->text().split(' ')[2].toInt();
            int y_vector = ui ->myLineEdit->text().split(' ')[3].toInt();
            QString id_str = ui ->myLineEdit->text().split(' ')[1];
            int max_id_size = 4; // handling if someone pass very very huge number (int range issue)


            // handling if id is out of range
            if( id >= scene->items().size() || id < 0 || id_str.size() > max_id_size ){
                ui ->myLineEdit ->setText("Index out of range...");
                break;
            }


            //checking id from list
            QString item_type = ui->myListWidget->item(id)->text().split(' ')[3];
            int reversed_id = scene->items().size() - id - 1;
            myCommandList << commandToWrite;
            if( item_type == "rectangle"){
                QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                rect ->moveBy(x_vector,y_vector);
            }
            else if( item_type == "circle"){
                QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                circle ->moveBy(x_vector,y_vector);
            }
            else if( item_type == "ellipse"){
                QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                ellipse ->moveBy(x_vector,y_vector);
            }
            else if( item_type == "line"){
               QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));

               line ->moveBy(x_vector,y_vector);
            }
            else if( item_type == "arch"){
                MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));

                arch ->moveBy(x_vector,y_vector);
            }
            else{
                ui->myLineEdit->setText("Wrong command, check command list...");
            }
        }
        break;
    }

    case 10: //rotate
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 5 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){
            myCommandList << commandToWrite;
            for(int i=0;i<ui ->myListWidget ->count();i++){

                        int x_center_rotation = ui ->myLineEdit ->text().split(' ')[2].toInt();
                        int y_center_rotation = ui ->myLineEdit ->text().split(' ')[3].toInt();
                        int angle = ui ->myLineEdit ->text().split(' ')[4].toInt();

                        QString item_type = ui ->myListWidget->item(i)->text().split(' ')[3];
                        int reversed_id = scene ->items().size() - i - 1;

                        if( item_type == "rectangle"){
                            QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                            rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);

                        }
                        else if( item_type == "circle"){
                            QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                            rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);

                        }
                        else if( item_type == "ellipse"){
                            QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                            rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);

                        }
                        else if( item_type == "line"){
                           QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                            rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);

                        }
                        else if( item_type == "arch"){
                            MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                            rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
                        }
                        else{
                            ui->myLineEdit ->setText("Wrong command, check command list...");
                        }

                    }
                }

        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
                    re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
                    re.exactMatch(ui ->myLineEdit ->text().split(' ')[3]) &&
                    re.exactMatch(ui ->myLineEdit ->text().split(' ')[4]))  ){
            ui->myLineEdit->setText("Coordinate and ID must be an integer number");
            break;
        }
        else
        {
            int id = ui ->myLineEdit ->text().split(' ')[1].toInt();
            int x_center_rotation = ui ->myLineEdit ->text().split(' ')[2].toInt();
            int y_center_rotation = ui ->myLineEdit ->text().split(' ')[3].toInt();
            int angle = ui ->myLineEdit ->text().split(' ')[4].toInt();
            QString id_str = ui ->myLineEdit->text().split(' ')[1];

            int max_id_size = 4; // handling if someone pass very very huge number (int range issue)


            // handling if id is out of range
            if( id >= scene->items().size() || id < 0 || id_str.size() > max_id_size ){
                ui->myLineEdit->setText("Index out of range...");
                break;
            }


            //checking id from list
            QString item_type = ui ->myListWidget->item(id)->text().split(' ')[3];
            int reversed_id = scene ->items().size() - id - 1;
            myCommandList << commandToWrite;
            if( item_type == "rectangle"){
                QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);

            }
            else if( item_type == "circle"){
                QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle
                                );

            }
            else if( item_type == "ellipse"){
                QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);

            }
            else if( item_type == "line"){
               QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);

            }
            else if( item_type == "arch"){
                MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
            }
            else{
                ui->myLineEdit ->setText("Wrong command, check command list...");
            }

        }
        break;
    }
      case 11: //show //#include <QTimer>
    {

        if( ui ->myLineEdit ->text().split(' ').size() != 2 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){
              for(int i=0;i<ui ->myListWidget ->count();i++){

                  // QTimer::singleShot(200, this, SLOT(updateCaption()));
          // START
                   //checking id from list
                   QString item_type = ui->myListWidget->item(i)->text().split(' ')[3];
                   int reversed_id = scene->items().size() - i - 1;

                   if( item_type == "rectangle"){
                       QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                       QPen copy_pencil=rect->pen();
                       QPen pen=QPen("gold");
                       pen.setWidth(3);
                       rect->setPen(pen);
                       scene ->update();
                       QTimer::singleShot(500,this,[=](){
                           rect->setPen(copy_pencil);
                       });
                       scene ->update();


                   }
                   else if( item_type == "circle"){

                       QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                       QPen copy_pencil=circle->pen();
                       QPen pen=QPen("gold");
                       pen.setWidth(3);
                       circle->setPen(pen);
                       scene ->update();

                       QTimer::singleShot(500,this,[=](){
                           circle->setPen(copy_pencil);

                       });
                       scene ->update();
                   }
                   else if( item_type == "ellipse"){
                       QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                       QPen copy_pencil=ellipse->pen();
                       QPen pen=QPen("gold");
                       pen.setWidth(3);
                       ellipse->setPen(pen);
                       scene ->update();
                       QTimer::singleShot(500,this,[=](){
                           ellipse->setPen(copy_pencil);
                       });
                       scene ->update();
                   }
                   else if( item_type == "line"){
                      QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                      QPen copy_pencil=line->pen();
                      QPen pen=QPen("gold");
                      pen.setWidth(3);
                      line->setPen(pen);
                      scene ->update();
                      QTimer::singleShot(500,this,[=](){
                          line->setPen(copy_pencil);
                      });
                      scene ->update();
                   }
                   else if( item_type == "arch"){
                       MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                       QPen copy_pencil=arch->pen();
                       QPen pen=QPen("gold");
                       pen.setWidth(3);
                       arch->setPen(pen);
                       scene ->update();
                       QTimer::singleShot(500,this,[=](){
                           arch->setPen(copy_pencil);
                       });
                       scene ->update();
                   }
                   else{
                       ui->myLineEdit->setText("Wrong command, check command list...");
                   }
              }
          }

        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1])) ){
            ui->myLineEdit->setText("ID must be an integer number");
            break;
        }
         else
        {
             int id = ui ->myLineEdit->text().split(' ')[1].toInt();
             QString id_str = ui ->myLineEdit->text().split(' ')[1];

             int max_id_size = 4; // handling if someone pass very very huge number (int range issue)


             // handling if id is out of range
             if( id >= scene ->items().size() || id < 0 || id_str.size() > max_id_size){
                 ui ->myLineEdit ->setText("Index out of range...");
                 break;
             }

            // QTimer::singleShot(200, this, SLOT(updateCaption()));
    // START
             //checking id from list
             QString item_type = ui->myListWidget->item(id)->text().split(' ')[3];
             int reversed_id = scene->items().size() - id - 1;

             if( item_type == "rectangle"){
                 QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=rect->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 rect->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     rect->setPen(copy_pencil);
                 });
                 scene ->update();


             }
             else if( item_type == "circle"){

                 QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=circle->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 circle->setPen(pen);
                 scene ->update();

                 QTimer::singleShot(500,this,[=](){
                     circle->setPen(copy_pencil);

                 });
                 scene ->update();
             }
             else if( item_type == "ellipse"){
                 QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=ellipse->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 ellipse->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     ellipse->setPen(copy_pencil);
                 });
                 scene ->update();
             }
             else if( item_type == "line"){
                QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                QPen copy_pencil=line->pen();
                QPen pen=QPen("gold");
                pen.setWidth(3);
                line->setPen(pen);
                scene ->update();
                QTimer::singleShot(500,this,[=](){
                    line->setPen(copy_pencil);
                });
                scene ->update();
             }
             else if( item_type == "arch"){
                 MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                 QPen copy_pencil=arch->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 arch->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     arch->setPen(copy_pencil);
                 });
                 scene ->update();
             }
             else{
                 ui->myLineEdit->setText("Wrong command, check command list...");
             }
         }
         break;
     }
//STOP
    case 12: //clear
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 1 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        myCommandList << commandToWrite;
        scene ->clear();
        ui ->myListWidget->clear();
        ui ->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view);
        scene->update();
        item_id = 0;
        break;
    }
    case 13: // write
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 2 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        QString filename = ui ->myLineEdit->text().split(' ')[1];
        QFile outputFile( filename + ".ape");
        if( outputFile.open( QFile::WriteOnly | QFile::Text ) ){

            QTextStream s(&outputFile);

            for(int i = 0; i < myCommandList.size() ; ++i){
                s << myCommandList.at(i) << '\n';
            }

        } else {
            ui ->myLineEdit ->setText("Error saving to file...");
        }
        outputFile.close();

        break;
    }
    case 14: //read
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 2 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }

        break;
    }
    case 15: // save
    {
        if( ui ->myLineEdit ->text().split(' ').size() != 4 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        int width = ui ->myLineEdit->text().split(' ')[1].toInt();
        int height = ui ->myLineEdit->text().split(' ')[2].toInt();
        QString filename = ui ->myLineEdit->text().split(' ')[3];
        QImage image(800,600,QImage::Format_ARGB32_Premultiplied);

        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing);
        scene->render(&painter);
        painter.end();
        QImage tmpimg = image.scaled(width, height, Qt::IgnoreAspectRatio);
        tmpimg.save(filename);
        break;

    }
    case 16: //scale
    {
        QRegExp re_positive_float("\\d+\\.\\d+");  // float
        if( ui ->myLineEdit ->text().split(' ').size() != 3 ){
            ui ->myLineEdit ->setText("Wrong composition of command...");
            break;
        }
        if(ui ->myLineEdit->text().split(' ')[1].toStdString() == "all"){
            for(int i=0;i<ui ->myListWidget ->count();i++){
                float scale = ui ->myLineEdit->text().split(' ')[2].toFloat();

                if ( !(re_positive_float.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
                       scale > 0.0 &&
                       scale < 5.0
                    ) ){
                    ui->myLineEdit->setText("Scale must be a float value 0 - 5, remember about dot...");
                    break;
                }

                //checking id from list
                QString item_type = ui->myListWidget->item(i)->text().split(' ')[3];
                int reversed_id = scene->items().size() - i - 1;

                if( item_type == "rectangle"){
                    QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                    rect ->setTransformOriginPoint(rect->boundingRect().center());
                    rect ->setScale(scale);
                }
                else if( item_type == "circle"){
                    QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                    circle ->setTransformOriginPoint(circle->boundingRect().center());
                    circle ->setScale(scale);

                }
                else if( item_type == "ellipse"){
                    QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                    ellipse ->setTransformOriginPoint(ellipse->boundingRect().center());
                    ellipse ->setScale(scale);


                }
                else if( item_type == "line"){
                   QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                   line ->setTransformOriginPoint(line->boundingRect().center());
                   line ->setScale(scale);

                }
                else if( item_type == "arch"){
                    MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                    arch ->setTransformOriginPoint(arch->boundingRect().center());
                    arch ->setScale(scale);

                }
                else{
                    ui->myLineEdit->setText("Wrong command, check command list...");
                }

            }

        }

        else if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1])
                    ) ){
            ui->myLineEdit->setText("ID must be positive number...");
            break;
        }
        else
        {
            int id = ui ->myLineEdit ->text().split(' ')[1].toInt();
            float scale = ui ->myLineEdit->text().split(' ')[2].toFloat();
            QString id_str = ui ->myLineEdit->text().split(' ')[1];
            int max_id_size = 4; // handling if someone pass very very huge number (int range issue)

            if ( !(re_positive_float.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
                   scale > 0.0 &&
                   scale < 5.0
                ) ){
                ui->myLineEdit->setText("Scale must be a value 0 - 5, remember about dot...");
                break;
            }

            // handling if id is out of range
            if( id >= scene->items().size() || id < 0 || id_str.size() > max_id_size ){
                ui ->myLineEdit ->setText("Index out of range...");
                break;
            }


            //check id from list
            QString item_type = ui->myListWidget->item(id)->text().split(' ')[3];
            int reversed_id = scene->items().size() - id - 1;

            if( item_type == "rectangle"){
                QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                rect ->setTransformOriginPoint(rect->boundingRect().center());
                rect ->setScale(scale);
            }
            else if( item_type == "circle"){
                QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                circle ->setTransformOriginPoint(circle->boundingRect().center());
                circle ->setScale(scale);

            }
            else if( item_type == "ellipse"){
                QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                ellipse ->setTransformOriginPoint(ellipse->boundingRect().center());
                ellipse ->setScale(scale);


            }
            else if( item_type == "line"){
               QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
               line ->setTransformOriginPoint(line->boundingRect().center());
               line ->setScale(scale);

            }
            else if( item_type == "arch"){
                MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                arch ->setTransformOriginPoint(arch->boundingRect().center());
                arch ->setScale(scale);

            }
            else{
                ui->myLineEdit->setText("Wrong command, check command list...");
            }
        }
        break;
    }
    case 17: //pixmap
    {
       /* if( ui ->myLineEdit ->text().split(' ').size() != 6 ){
                    ui ->myLineEdit ->setText("Wrong composition of command...");
                    break;
        }*/

        int x1_coord = ui ->myLineEdit ->text().split(' ')[1].toInt();
        int y1_coord = ui ->myLineEdit ->text().split(' ')[2].toInt();
        int scale = ui ->myLineEdit ->text().split(' ')[3].toInt();
        QString file_name = ui ->myLineEdit ->text().split(' ')[4];

        if ( !(re.exactMatch(ui ->myLineEdit ->text().split(' ')[1]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[2]) &&
               re.exactMatch(ui ->myLineEdit ->text().split(' ')[3])) ){
            ui->myLineEdit->setText("Coordinate must be an integer number");
            break;
        }

        QGraphicsPixmapItem* pixitem = new QGraphicsPixmapItem(QPixmap(file_name));
        QPointF q1(x1_coord,y1_coord);
        pixitem->setPos(q1);
        pixitem->setScale(scale);


        scene->addItem(pixitem);
        ui->myListWidget->addItem("ID: "+QString::number(item_id)+" ITEM: pixmap");

        ui->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view); // it is necessary everywhere
        scene ->update();
        item_id++;

        break;
    }
    default:
    {
        break;
    }

    } // end of swtich case

}

void MainWindow::resizeEvent(QResizeEvent *) {
    ui ->myScreen ->fitInView(x1_view,y1_view,x2_view,y2_view);
    scene ->update();

}



bool is_hex_notation(std::string const& s)
{
  return s.compare(0, 2, "0x") == 0
      && s.size() > 2
      && s.find_first_not_of("0123456789abcdefABCDEF", 2) == std::string::npos;
}



// that 3 buttons are no longer needed, later we gotta delete it
void MainWindow::on_clearButton_clicked()
{
    ui ->myLineEdit->clear();
}

void MainWindow::on_myClearScreenButton_clicked()
{
    scene ->clear();
    ui ->myListWidget->clear();
    ui ->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view);
    item_id = 0;
    scene->update(); // maybe unnecessary
}


void MainWindow::on_mySaveToFileButton_clicked()
{
    QImage image(800,600,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();
    image.save("last_screen.png");
}

void MainWindow::ProvideContextMenu(const QPoint &pos){

      QPoint item = ui->myListWidget->mapToGlobal(pos);
      QMenu submenu;
      QAction* frst=submenu.addAction("Delete");
      QAction* secd=submenu.addAction("Fill");
      QAction* thrd=submenu.addAction("Rotate");
      QAction* fourth=submenu.addAction("Scale Image");


      QAction* rightClickItem = submenu.exec(item);
      if (rightClickItem && rightClickItem->text().contains("Delete") ){
             std::cout<<ui->myListWidget->indexAt(pos).row()<<std::endl;
             int tmp_id=ui->myListWidget->indexAt(pos).row();
             QListWidgetItem *it=ui->myListWidget->takeItem(ui->myListWidget->indexAt(pos).row());
             delete it;
             item_id--;
             int num=ui->myListWidget->count()-tmp_id-1;
             scene->removeItem(scene->items().at(num+1));

             if(num!=0){
                 for(int i=ui->myListWidget->count()-1;i>=tmp_id;i--){

                       int number = ui->myListWidget->item(i)->text().split(' ')[1].toInt();
                       number -= 1;

                       std::string str=std::to_string(number);
                       QString all_string=ui->myListWidget->item(i)->text().split(' ')[0]+" "+QString::fromStdString(str)+" "+ui->myListWidget->item(i)->text().split(' ')[2]
                                     +" "+ui->myListWidget->item(i)->text().split(' ')[3];
                       std::cout<<all_string.toStdString()<<std::endl;
                       ui->myListWidget->item(i)->setText(all_string);

                 }
             }
      }
      else if(rightClickItem && rightClickItem->text().contains("Fill") ){
            QMenu subsubmenu;
            subsubmenu.addAction("Set Colour:")->setDisabled(1);
            subsubmenu.addAction("Yellow");
            subsubmenu.addAction("Red");
            subsubmenu.addAction("Purple");
            subsubmenu.addAction("Blue");
            subsubmenu.addAction("Green");
            subsubmenu.addAction("Black");
            subsubmenu.addAction("White");
            QAction* ClickItem = subsubmenu.exec(submenu.pos());
            int tmp_id=ui->myListWidget->indexAt(pos).row();
            int reversed_id=ui->myListWidget->count()-tmp_id-1;
            QString item_type = ui ->myListWidget ->item(tmp_id)->text().split(' ')[3];

             if (ClickItem && ClickItem->text().contains("Yellow") ){
                 QColor color="yellow";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                 subsubmenu.hide();
                submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("Red")){
                 QColor color="red";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                subsubmenu.hide();
                submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("Purple")){
                 QColor color="purple";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                 subsubmenu.hide();
                 submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("Blue")){
                 QColor color="blue";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                 subsubmenu.hide();
                submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("Green")){
                 QColor color="green";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                 subsubmenu.hide();
                submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("Black")){
                 QColor color="black";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                subsubmenu.hide();
                submenu.hide();
             }else if(ClickItem && ClickItem->text().contains("White")){
                 QColor color="white";
                 if( item_type == "rectangle"){
                     QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                     rect ->setBrush(color);
                 }
                 else if( item_type == "circle"){
                     QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     circle ->setBrush(color);
                 }
                 else if( item_type == "ellipse"){
                     QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));

                     ellipse ->setBrush(color);
                 }
                 else if( item_type == "line"){
                     ui ->myLineEdit ->setText("You cannot fill line with color...");
                 }
                 else if( item_type == "arch"){
                     ui ->myLineEdit ->setText("You cannot fill arch with color...");
                 }
                 else{
                     ui ->myLineEdit ->setText("Staph...");
                 }
                 subsubmenu.hide();
                 submenu.hide();
             }else{}
      }else if(rightClickItem && rightClickItem->text().contains("Rotate")){

          int id=ui->myListWidget->indexAt(pos).row();
          int x_center_rotation=400;
          int y_center_rotation=300;
          QString item_type = ui ->myListWidget->item(id)->text().split(' ')[3];
          int reversed_id = scene ->items().size() - id - 1;

          QMenu subsubmenu;
          subsubmenu.addAction("Set Angle (400,300):")->setDisabled(1);
          subsubmenu.addAction("15º");
          subsubmenu.addAction("30º");
          subsubmenu.addAction("45º");
          subsubmenu.addAction("60º");
          subsubmenu.addAction("75º");
          subsubmenu.addAction("90º");
          subsubmenu.addAction("180º");
          QAction* ClickItem = subsubmenu.exec(submenu.pos());

          if (ClickItem && ClickItem->text().contains("15º") ){
              int angle=15;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));

                  rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                  rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                   rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                 rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                  rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }
          }else if(ClickItem && ClickItem->text().contains("30º")){
              int angle=30;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                    rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }

          }else if(ClickItem && ClickItem->text().contains("45º")){
              int angle=45;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }

          }else if(ClickItem && ClickItem->text().contains("60º")){
              int angle=60;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
 rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }

          }else if(ClickItem && ClickItem->text().contains("75º")){
              int angle=75;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
 rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
  rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }

          }else if(ClickItem && ClickItem->text().contains("90º")){
              int angle=90;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }

          }else if(ClickItem && ClickItem->text().contains("180º")){
              int angle=180;

              if( item_type == "rectangle"){
                  QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
rotateSceneItem(rect,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "circle"){
                  QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
rotateSceneItem(circle,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "ellipse"){
                  QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
 rotateSceneItem(ellipse,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "line"){
                 QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
rotateSceneItem(line,x_center_rotation,y_center_rotation,angle);
              }
              else if( item_type == "arch"){
                  MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
rotateSceneItem(arch,x_center_rotation,y_center_rotation,angle);
              }
              else{
                  ui->myLineEdit ->setText("Wrong command, check command list...");
              }
              subsubmenu.hide();
          }
      }else if(rightClickItem && rightClickItem->text().contains("Scale Image") ){

          QMenu subsubmenu;
          subsubmenu.addAction("Set Scale:")->setDisabled(1);
          subsubmenu.addAction("1");
          subsubmenu.addAction("2");
          subsubmenu.addAction("3");
          QAction* ClickItem = subsubmenu.exec(submenu.pos());

          int tmp_id=ui->myListWidget->indexAt(pos).row();
          QString item_type = ui ->myListWidget->item(tmp_id)->text().split(' ')[3];
          int num=ui->myListWidget->count()-tmp_id-1;

          if(item_type=="pixmap"){

              if(ClickItem && ClickItem->text().contains("1")){
                  int scale=1;
                  scene->items().at(num)->setScale(scale);
              }else if(ClickItem && ClickItem->text().contains("2")){
                  int scale=2;
                  scene->items().at(num)->setScale(scale);
              }else if(ClickItem && ClickItem->text().contains("3")){
                  int scale=3;
                  scene->items().at(num)->setScale(scale);
              }else{}
           }
          subsubmenu.hide();

      }else{}

    submenu.hide();
}

void MainWindow::on_myListWidget_itemClicked(QListWidgetItem *item)
{
    ui->myListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
       connect(ui->myListWidget,SIGNAL(customContextMenuRequested(const QPoint &)),
       this,SLOT(ProvideContextMenu(const QPoint &)));

    // START
             //checking id from list
             QString item_type = item->text().split(' ')[3];
             int id=item->text().split(' ')[1].toInt();
             int reversed_id = scene->items().size() - id - 1;

             if( item_type == "rectangle"){
                 QGraphicsRectItem* rect = static_cast<QGraphicsRectItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=rect->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 rect->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     rect->setPen(copy_pencil);
                 });
                 scene ->update();


             }
             else if( item_type == "circle"){

                 QGraphicsEllipseItem* circle = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=circle->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 circle->setPen(pen);
                 scene ->update();

                 QTimer::singleShot(500,this,[=](){
                     circle->setPen(copy_pencil);

                 });
                 scene ->update();
             }
             else if( item_type == "ellipse"){
                 QGraphicsEllipseItem* ellipse = static_cast<QGraphicsEllipseItem*>(scene->items().at(reversed_id));
                 QPen copy_pencil=ellipse->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 ellipse->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     ellipse->setPen(copy_pencil);
                 });
                 scene ->update();
             }
             else if( item_type == "line"){
                QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(scene->items().at(reversed_id));
                QPen copy_pencil=line->pen();
                QPen pen=QPen("gold");
                pen.setWidth(3);
                line->setPen(pen);
                scene ->update();
                QTimer::singleShot(500,this,[=](){
                    line->setPen(copy_pencil);
                });
                scene ->update();
             }
             else if( item_type == "arch"){
                 MyArcObject* arch = static_cast<MyArcObject*>(scene->items().at(reversed_id));
                 QPen copy_pencil=arch->pen();
                 QPen pen=QPen("gold");
                 pen.setWidth(3);
                 arch->setPen(pen);
                 scene ->update();
                 QTimer::singleShot(500,this,[=](){
                     arch->setPen(copy_pencil);
                 });
                 scene ->update();
             }
             else{
                 ui->myLineEdit->setText("Wrong command, check command list...");
             }
}


void MainWindow::mouseMoveEvent(QMouseEvent* event) {

    setMouseTracking(true);

    int x_screen = ui->myScreen ->pos().x();
    int y_screen = ui->myScreen ->pos().y();

    int width_screen = ui ->myScreen -> width();
    int height_screen = ui ->myScreen -> height();

    if( !ui->toolBar->pos().x() ){x_screen += 40;}
    QString x_mouse = QString::number( event->pos().x() - x_screen );
    QString y_mouse = QString::number( event->pos().y() - y_screen );
    if(event->pos().x() > x_screen && event->pos().x() < x_screen + width_screen && event->pos().y() > y_screen && event->pos().y() < y_screen + height_screen ){
        ui -> textEdit -> setText( "x: " + x_mouse + " y: " + y_mouse );
    }else{

        ui -> textEdit -> setText( "x: oor   y: oor" );
    }
};

void MainWindow::on_actionClearButton_triggered()
{
    scene ->clear();
    ui ->myListWidget->clear();
    ui ->myScreen->fitInView(x1_view,y1_view,x2_view,y2_view);
    item_id = 0;
    scene->update(); // maybe unnecessary
}

void MainWindow::on_actionTakeScreenButton_triggered()
{
    QImage image(800,600,QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    scene->render(&painter);
    painter.end();
    image.save("last_screen.png");
}

void MainWindow::on_actionFaqButton_triggered()
{
    QMessageBox myMessageBox(this);
    myMessageBox.information(0,"Command list","@range x1 y1 x2 y2: \n"
                                                 "Set work space left-bottom coordinates as (x1, y1) and right-top as (x2,y2).\n"
                                                 "@background c:\n"
                                                 "Set background color as c.\n"
                                                 "@line x1 y1 x2 y2 c:\n"
                                                 "Draw line from point (x1,y1) to (x2,y2) and set its color c.\n"
                                                 "@rectangle x1 y1 x2 y2 c:\n"
                                                 "Draw rectangle from top-left point (x1,y1) to with size (x2,y2) and set its color c.\n"
                                                 "@circle x y r c:\n"
                                                 "Draw circle with center point (x,y) and radius r and set its color c.\n"
                                                 "@ellipse x y rx ry c:\n"
                                                 "Draw ellipse with center point (x,y) and horizontal and vertical draftshafts rx and ry, and set color c.\n"
                                                 "@arc x y rx ry b e:\n"
                                                 "Draw arch based on ellipse with center point (x,y) and horizontal and vertical draftshats rx and ry, from angle b to angle e with color c.\n"
                                                 "@fill id c:\n"
                                                 "Fill object of id with c color.\n"
                                                 "@delete id:\n"
                                                 "Delete object of id.\n"
                                                 "@move id x y:\n"
                                                 "Move object of id using vector (x,y).\n"
                                                 "@rotate id x y a:\n"
                                                 "Rotate object of id around point (x,y) using angle a.\n"
                                                 "@show id:\n"
                                                 "Highlight object of id, with yellow color for 0.5 second.\n"
                                                 "@clear:\n"
                                                 "Clear entire scene, and objects list.\n"
                                                 "@write file:\n"
                                                 "Save all objects with actual work space range to file named file.\n"
                                                 "@read file:\n"
                                                 "Load all object and work space range from file named file.\n"
                                                 "@save w h file:\n"
                                                 "Save actual picture as a bitmap with w width and h height, to grapical file named file.\n"
                                                 "@scale id s:\n"
                                                 "Scale object with s value, note that value 1 is original size of object and its constant.\n"
                                                 "Instead of using id in particular commands u can type all to set an action for all objects.  If you chose wrong color or no color, figure will fill with black color");

}


//void validate_color(int split_id,QLineEdit* myLineEdit, QGraphicsItem *item ){

//    QString color_qstr = myLineEdit ->text().split(' ')[ split_id ];
//    std::string color_str = color_qstr.toStdString();
//    std::string color_table[]={"white","yellow","red",
//                               "black","purple","green",
//                               "blue","pink","grey",
//                               "gold","bronze","yellowgreen"};
//    if( is_hex_notation(color_str) ){
//        QColor color = color_qstr;
//        QPen pencil = QPen(color);


//    }

//}


void MainWindow::on_actionExplainButton_triggered()
{
    tab = new myTabWidget(); // we can use both windows at the same time
    tab->show();
}
