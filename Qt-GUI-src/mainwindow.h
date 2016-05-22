/*
 Developer: LIN, Hao-Chih (Jim, LIN)
 Email: f44006076@gmail.com
 Final modified date: 08/05/2016
 ==============================================================
 ===========================LICENSE============================
 ==============================================================
 This file is part of RRT_figurebase program.
 DOCKS is free software: you can redistribute it and/or modify
 it under the terms of the  GNU LESSER GENERAL PUBLIC LICENSE
 as published by the Free Software Foundation, either version
 3 of the License, or any later version.
 DOCKS is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU LESSER GENERAL PUBLIC LICENSE for more details.
 You should have received a copy of the
 GNU LESSER GENERAL PUBLIC LICENSE along with DOCKS.
 If not, see <http://www.gnu.org/licenses/lgpl.txt>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QtCore>
#include <QTextEdit>
#include <QImage>
#include <QMouseEvent>
#include <vector>

//OpenCV Lib
#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

//Custom class
#include "qimageLabel.h"

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
    void on_PB_load_clicked();
    void on_PB_start_clicked();
    void on_PB_reset_clicked();
    void on_SB_max_nodes_valueChanged(int arg1);
    void on_SB_goal_radius_valueChanged(int arg1);
    void on_SB_new_state_dis_valueChanged(int arg1);

    void slot_mouseMovingPosition(int x, int y);
    void slot_mousePressed(bool isLeftBtn, QPoint point);

private:
    Ui::MainWindow *ui;

    // For visualization
    cv::Mat img_ori; // CV_8UC3, for static map
    cv::Mat img_process; // CV_8UC3
    cv::Mat img_start_goal; // CV_8UC3

    // For RRT-algorithm
    cv::Mat rrt_graph; // CV_8UC1, for static map
    cv::Mat rrt_tree;  // CV_32SC3, for rrt tree (ch[0]: cost value, ch[1]: the x pos of parent node, ch[2]: the y pose of parent node)

    cv::Point startPos;
    cv::Point goalPos;
    cv::Point goalachievedPos;

    int img_rows;
    int img_cols;
    int max_nodes;   // Maximum nodes
    int goal_radius; // The radius of goal area (unit: pixel)
    float new_state_dis; // The distance between the new state and parent state (unit: pixel)
    bool con2label;  // Flag to check the signal connection with the "qimagelabel" class
    bool start_point_setup; // Flag to check the goal has been set
    bool goal_point_setup; // Flag to check the goal has been set
    bool goal_reach;

    QImage convertOpenCVMatToQtQImage(cv::Mat mat);
    float cvPoint_distance(const cv::Point &point_a, const cv::Point &point_b);
};

#endif // MAINWINDOW_H
