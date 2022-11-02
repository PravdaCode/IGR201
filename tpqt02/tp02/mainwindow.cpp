#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QTextEdit>
#include <iostream>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QColorDialog>
#include <QInputDialog>
#include <QLabel>
#include "myshape.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    statusBar();

    // Creqte the menus
    QMenuBar * menubar = this->menuBar( ); // adds/returns the menu bar
    QMenu * menufile = menubar->addMenu( tr("&File") );

    QAction * open = new QAction( QIcon(":/img/icons/images/open.png"), tr("&Open..."), this );
    menufile->addAction(open);
    QAction * save = new QAction( QIcon(":/img/icons/images//save.png"), tr("&Save..."), this );
    menufile->addAction(save);
    QAction * quit = new QAction( QIcon(":/img/icons/images//quit.png"), tr("&Quit..."), this );
    menufile->addAction(quit);

    QMenu * menudraw = menubar->addMenu( tr("&Draw") );
    QAction * pen = new QAction( QIcon(":/img/icons/images//line.png"), tr("&Free Pen"), this );
    menudraw->addAction(pen);
    QAction * rect = new QAction( QIcon(":/img/icons/images//rectangle.png"), tr("&Rectangle"), this );
    menudraw->addAction(rect);
    QAction * elip = new QAction( QIcon(":/img/icons/images//elipse.png"), tr("&Elipse"), this );
    menudraw->addAction(elip);
    QAction * configColor = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Color"), this );
    menudraw->addAction(configColor);
    QAction * configSize = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Size"), this );
    menudraw->addAction(configSize);

    //Creqte the toolbqr
    QToolBar * toolbar = this->addToolBar(tr("File"));
    toolbar->addAction(open);
    toolbar->addAction(save);
    toolbar->addAction(pen);
    toolbar->addAction(rect);
    toolbar->addAction(elip);

    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(save, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApp()));

    //Create text
    this->setCentralWidget(new QWidget());
    drawscrr = new draw(this->centralWidget());
    setCentralWidget(drawscrr);

    //Connect Draw buttons tos changeDraw
    connect(pen, &QAction::triggered, this, [this]{changeDraw(LINE);});
    connect(rect, &QAction::triggered, this, [this]{changeDraw(RECTANGLE);});
    connect(elip, &QAction::triggered, this, [this]{changeDraw(ELIPSE);});
    connect(configColor, SIGNAL(triggered()), this, SLOT(colorConfig()));
    connect(configSize, SIGNAL(triggered()), this, SLOT(sizeConfig()));


}

void MainWindow::changeDraw(typeDraw typeD){
    drawscrr->setTypeD(typeD);
  }


void MainWindow::openFile(){
  QString filename = QFileDialog::getOpenFileName(this,"Open Document");
      QFile file(filename);
      file.open( QIODevice::ReadOnly );
      QPixmap img(filename);
      QLabel *label = new QLabel(drawscrr);
      label->setPixmap(img);

  }

void MainWindow::saveFile(){
     QPixmap pixmap(drawscrr->size());
     drawscrr->render(&pixmap);
     QString filename = QFileDialog::getSaveFileName(this,"Save Document");
     QFile file(filename);
     file.open( QIODevice::WriteOnly );
     pixmap.save(&file,"PNG");

  }

 int MainWindow:: quitApp(){
   QMessageBox msgBox;
        msgBox.setText("Exit?");
        msgBox.setInformativeText("Do you really want to close without saving?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Save | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::No);

        int ret = msgBox.exec();

        switch (ret) {
          case QMessageBox::Yes:
              // Save was clicked
              this->~MainWindow();
              break;
          case QMessageBox::Save:
              // Don't Save was clicked
              this->saveFile();
              break;
          default:
              // should never be reached
              break;
        }
        return ret;

  }

 void MainWindow::colorConfig(){
   QColor newColor = QColorDialog::getColor(drawscrr->getColor());
   if (newColor.isValid()){
       drawscrr->setColor(newColor);
       if(drawscrr->shapes[drawscrr->shapes.size()-1].isSelected()){
           myshape shape = drawscrr->shapes[drawscrr->shapes.size()-1];
           shape.color = newColor;
           drawscrr->shapes.removeLast();
           drawscrr->shapes.push_back(shape);
           update();
         }
      }


}

 void MainWindow::sizeConfig(){
   int newWidth = QInputDialog::getInt(this, tr("Pen"),
                                           tr("Select pen width:"),
                                           drawscrr->getWidght(),
                                           1, 50, 1);
   drawscrr->setWidght(newWidth);
   if(drawscrr->shapes[drawscrr->shapes.size()-1].isSelected()){
       myshape shape = drawscrr->shapes[drawscrr->shapes.size()-1];
       shape.size = newWidth;
       drawscrr->shapes.removeLast();
       drawscrr->shapes.push_back(shape);
       update();
     }
}

 void MainWindow::closeEvent (QCloseEvent *event) {
   int ret = this->quitApp();

   switch (ret) {
     case QMessageBox::Yes:
         // Save was clicked
         event->accept();
         break;
     default:
         // should never be reached
         event->ignore();
         break;
   }
 }



MainWindow::~MainWindow(){
    delete ui;
}

