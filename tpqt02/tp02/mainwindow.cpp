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
#include "myshape.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    statusBar();

    // Creqte the menus
    QMenuBar * menubar = this->menuBar( ); // adds/returns the menu bar
    QMenu * menufile = menubar->addMenu( tr("&File") );

    QAction * open = new QAction( QIcon(":/images/icons/images/open.png"), tr("&Open..."), this );
    menufile->addAction(open);
    QAction * save = new QAction( QIcon(":/images/icons/images//save.png"), tr("&Save..."), this );
    menufile->addAction(save);
    QAction * quit = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Quit..."), this );
    menufile->addAction(quit);

    QMenu * menudraw = menubar->addMenu( tr("&Draw") );
    QAction * pen = new QAction( QIcon(":/images/icons/images/open.png"), tr("&Free Pen"), this );
    menudraw->addAction(pen);
    QAction * rect = new QAction( QIcon(":/images/icons/images//save.png"), tr("&Rectangle"), this );
    menudraw->addAction(rect);
    QAction * elip = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Elipse"), this );
    menudraw->addAction(elip);
    QAction * configColor = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Color"), this );
    menudraw->addAction(configColor);
    QAction * configSize = new QAction( QIcon(":/images/icons/images//quit.png"), tr("&Size"), this );
    menudraw->addAction(configSize);

    //Creqte the toolbqr
    QToolBar * toolbar = this->addToolBar(tr("File"));
    toolbar->addAction(open);
    toolbar->addAction(save);
    toolbar->addAction(quit);

    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(save, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(quit, SIGNAL(triggered()), this, SLOT(quitApp()));

    //Create text
    this->setCentralWidget(new QWidget());
    drawscrr = new draw(this->centralWidget());
    setCentralWidget(drawscrr);

    //Connect Draw buttons tos changeDraw
    connect(pen, &QAction::triggered, this, [this]{changeDraw(PEN);});
    connect(rect, &QAction::triggered, this, [this]{changeDraw(RECTANGLE);});
    connect(elip, &QAction::triggered, this, [this]{changeDraw(ELIPSE);});
    connect(configColor, SIGNAL(triggered()), this, SLOT(colorConfig()));
    connect(configSize, SIGNAL(triggered()), this, SLOT(sizeConfig()));


}

void MainWindow::changeDraw(typeDraw typeD){
    drawscrr->setTypeD(typeD);
  }


void MainWindow::openFile(){
    std::cout << "Save File"<<std::endl;
  }

void MainWindow::saveFile(){
     std::cout << "Save File"<<std::endl;

  }

 void MainWindow:: quitApp(){
     std::cout << "Save File"<<std::endl;

  }

 void MainWindow::colorConfig(){
   QColor newColor = QColorDialog::getColor(drawscrr->getColor());
   if (newColor.isValid())
       drawscrr->setColor(newColor);
}

 void MainWindow::sizeConfig(){
   int newWidth = QInputDialog::getInt(this, tr("Pen"),
                                           tr("Select pen width:"),
                                           drawscrr->getWidght(),
                                           1, 50, 1);
   drawscrr->setWidght(newWidth);
}




MainWindow::~MainWindow(){
    delete ui;
}

