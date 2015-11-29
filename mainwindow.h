#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv.hpp>
#include <QDebug>
#include <math.h>
#include <QFileDialog>

void mouseMove(int event,int x,int y,int flag,void* param);
void quadrantChange(int &xStart,int &xEnd,int &yStart,int &yEnd);
void imageLabeling(int event,int x,int y,int flag,void* param);


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_cam_clicked();

    void on_grabcut_clicked();


    void on_loadpicture_clicked();

    void on_goal_clicked();

    void on_coin_clicked();

    void on_count_clicked();

private:
    Ui::MainWindow *ui;
    cv::Mat maskReal;
};

#endif // MAINWINDOW_H
