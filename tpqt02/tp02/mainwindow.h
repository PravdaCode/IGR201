#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "draw.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    draw * drawscrr;
    void closeEvent (QCloseEvent *event) override;

public slots:
    void openFile();
    void saveFile();
    int quitApp();
    void changeDraw(typeDraw);
    void colorConfig();
    void sizeConfig();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
