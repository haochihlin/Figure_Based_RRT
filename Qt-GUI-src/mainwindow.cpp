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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTime>

#define LOW_INTENSITY 200

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("RRT Demo Program");
    ui->QL_imgview->setMouseTracking(true);

    this->con2label = false;
    this->start_point_setup = false;
    this->goal_point_setup= false;
    this->goal_reach = false;
    this->max_nodes = 500;
    this->goal_radius = 20;
    this->new_state_dis = 20;

    ui->SB_new_state_dis->setValue(this->new_state_dis);
    ui->SB_goal_radius->setValue(this->goal_radius);
    ui->SB_max_nodes->setValue(this->max_nodes);

    // Initialize the qrand();
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QImage MainWindow::convertOpenCVMatToQtQImage(cv::Mat mat) {
    if(mat.channels() == 1) // if grayscale image
    {
        return QImage((uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);     // declare and return a QImage
    }
    else if(mat.channels() == 3) // if 3 channel color image
    {
        cv::Mat temp; // make the same cv::Mat
        cvtColor(mat, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
        QImage dest((const uchar *) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
        dest.bits(); // enforce deep copy, see documentation
        // of QImage::QImage ( const uchar * data, int width, int height, Format format )
        return dest;
    }
    else
    {
        qDebug() << "in convertOpenCVMatToQtQImage, image was not 1 channel or 3 channel, should never get here";
    }
    return QImage();        // return a blank QImage if the above did not work
}

float MainWindow::cvPoint_distance(const cv::Point &point_a, const cv::Point &point_b)
{
    return (float)(sqrt( (point_a.x - point_b.x)*(point_a.x - point_b.x) + (point_a.y - point_b.y)*(point_a.y - point_b.y)  ));
}

void MainWindow::on_PB_load_clicked()
{
    // Verify and Load the image
    QString FileName = QFileDialog::getOpenFileName();
    if(FileName == "")
    {
        ui->LE_img_path->setText("file not chosen");
        return;
    }

    this->img_ori = cv::imread(FileName.toStdString()); // load image by openCV

    if(this->img_ori.empty())
    {
        ui->LE_img_path->setText("error: image not read from file");
        return;
    }
    else
        ui->LE_img_path->setText(FileName);  // update label with file name

    // Image conversion
    cv::cvtColor(this->img_ori,this->rrt_graph, CV_BGR2GRAY);  // Transfer the ori-BGR image to grayscale image

    this->img_rows = this->img_ori.rows;
    this->img_cols = this->img_ori.cols;

    // Set up the RRT-Tree matrix
    cv::Mat rrt_tree_temp(this->img_rows, this->img_cols, CV_32SC3);
    this->rrt_tree = rrt_tree_temp;

    this->on_PB_reset_clicked(); // Call reset function

    // Set up the signal connection with "qimagelabel" class
    if(!con2label)
    {
        connect(ui->QL_imgview, SIGNAL(signal_MousePosition(int,int)), this, SLOT(slot_mouseMovingPosition(int,int)));
        connect(ui->QL_imgview, SIGNAL(signal_MousePress(bool, QPoint)), this, SLOT(slot_mousePressed(bool, QPoint)));
        con2label = true;
    }
}


void MainWindow::on_PB_reset_clicked()
{
    // Reset flags
    this->start_point_setup = false;
    this->goal_point_setup= false;
    this->goal_reach = false;

    //Reset all matrix
    this->rrt_tree.setTo(cv::Scalar::all(-1)); //Reset the RRT Tree matrix
    this->img_ori.copyTo(this->img_start_goal);   //Reset the img_start_goal matrix

    QImage qimg_ori = convertOpenCVMatToQtQImage(this->img_ori);  // convert openCV images to QImage
    ui->QL_imgview->clear();
    ui->QL_imgview->setPixmap(QPixmap::fromImage(qimg_ori));   // show original images on labels
}

void MainWindow::slot_mouseMovingPosition(int x, int y)
{
    QString coord = QString::number(x) + ", " + QString::number(y);
    ui->LE_curr->setText(coord); //Show the current mouse position
}

void MainWindow::slot_mousePressed(bool isLeftBtn, QPoint point)
{
    // General check
    if(point.isNull())
    {
        ui->LE_status->setText("Unacceptable !");
        return;
    }

    // Boundary check
    if( point.x() <= 3 || point.x() >= (this->img_cols - 3) || point.y() <= 3 || point.y() >= (this->img_rows - 3))
    {
        ui->LE_status->setText("Unacceptable !");
        return;
    }

    // Verify the point to avoid the obstacles by grayscale image
    uchar pixel_value = this->rrt_graph.at<uchar>(point.y(), point.x()); //format: at<uchar>(height, width)
    if(pixel_value < LOW_INTENSITY) // The low intensity area represents the obstacles.
    {
        ui->LE_status->setText("In the obstacles !");
        return;
    }


    // Left button event: start point
    if(isLeftBtn && this->start_point_setup == false) //left button
    {
        if(this->goal_point_setup)
        {
            //float dis_check = sqrt( (point.x() - this->goalPos.x)*(point.x() - this->goalPos.x) + (point.y() - this->goalPos.y)*(point.y() - this->goalPos.x)  );
            float dis_check = this->cvPoint_distance(cv::Point(point.x(),point.y()), this->goalPos);
            if( dis_check <= (float)(3 + this->goal_radius) ) // Check if the start is coincided with the goal area;
            {
                ui->LE_status->setText("Concide wiht the goal !");
                return;
            }
        }

        // Get the mouse clicked position
        this->startPos.x = point.x();
        this->startPos.y = point.y();

        // Reset RRT Tree
        this->rrt_tree.setTo(cv::Scalar::all(-1)); //Reset the RRT Tree matrix
        this->rrt_tree.at<cv::Vec3i>(this->startPos.y,this->startPos.x)[0] = 0; //Set the cost of start point as 0

        // Visualize the start point on a BGR image
        cv::circle( this->img_start_goal, this->startPos, 3, cv::Scalar( 0, 0, 255 ), -3, 8 );  //Scalar: Blue = a, Green = b and Red = c
        QImage qimg_temp = convertOpenCVMatToQtQImage(this->img_start_goal);
        ui->QL_imgview->clear();
        ui->QL_imgview->setPixmap(QPixmap::fromImage(qimg_temp));

        // Show the start position on the label
        QString coord = QString::number(this->startPos.x) + ", " + QString::number(this->startPos.y);
        ui->LE_start->setText(coord);

        // Disable the left button
        this->start_point_setup = true;
    }

    // Right button event: goal point
    if(isLeftBtn == false && this->goal_point_setup == false) //isLeftBtn == false => right button
    {
        if(this->goal_point_setup)
        {
            //float dis_check = sqrt( (point.x() - this->startPos.x)*(point.x() - this->startPos.x) + (point.y() - this->startPos.y)*(point.y() - this->startPos.x)  );
            float dis_check = this->cvPoint_distance(cv::Point(point.x(),point.y()), this->startPos);
            if( dis_check <= (float)(3+this->goal_radius)) // Check if the goal area is coincided with the start point;
            {
                ui->LE_status->setText("Concide wiht the start !");
                return;
            }
        }

        // Boundary check
        if( point.x() <= this->goal_radius || point.x() >= (this->img_cols - this->goal_radius) || point.y() <= this->goal_radius || point.y() >= (this->img_rows - this->goal_radius))
        {
            ui->LE_status->setText("Unacceptable !");
            return;
        }

        // Get the mouse clicked position
        this->goalPos.x = point.x();
        this->goalPos.y = point.y();

        // Visualize the goal area on a BGR image
        cv::circle( this->img_start_goal, this->goalPos, this->goal_radius, cv::Scalar( 0, 255, 0 ), -(this->goal_radius), 8 );  //Scalar: Blue = a, Green = b and Red = c
        QImage qimg_temp = convertOpenCVMatToQtQImage(this->img_start_goal);
        ui->QL_imgview->clear();
        ui->QL_imgview->setPixmap(QPixmap::fromImage(qimg_temp));

        // Show the goal position on the label
        QString coord = QString::number(this->goalPos.x) + ", " + QString::number(this->goalPos.y);
        ui->LE_goal->setText(coord);

        // Disable the left button
        this->goal_point_setup = true;
    }

}


void MainWindow::on_PB_start_clicked()
{
    if(!this->start_point_setup)
    {
        ui->LE_curr->setText("Please set up the start point !");
        return;
    }

    // Initialize
    ui->LE_status->setText("Processing ...");

    this->goal_reach = false;
    this->img_start_goal.copyTo(this->img_process);

    // Reset RRT Tree
    this->rrt_tree.setTo(cv::Scalar::all(-1)); //Reset the RRT Tree matrix
    this->rrt_tree.at<cv::Vec3i>(this->startPos.y,this->startPos.x)[0] = 0; //Set the cost of start point as 0

    // RRT-algorithm
    int node_count = 0;
    while (node_count <= this->max_nodes && this->goal_reach == false)
    {
        // == Generate Random State ==
        cv::Point randPos;
        randPos.x = 3 + qrand()%(this->img_cols - 3 - 3); //a + qrand() % (b - a)
        randPos.y = 3 + qrand()%(this->img_rows - 3 - 3);

        // Pass the random point when it is coincide with the start point
        if(randPos == this->startPos)
            continue;

        // == Find Nearest Neighbor ==
        float dis_min = 10000000.0;
        cv::Point nearPos(0,0);
        for(int row_temp=0; row_temp<this->img_rows; row_temp++)
        {
            int *data = this->rrt_tree.ptr<int>(row_temp);
            for(int col_temp=0; col_temp<this->img_cols*this->img_ori.channels() ; col_temp++)
            {
                if(col_temp%3 == 0)//Only for the channel[0] layer
                {
                    if(data[col_temp] >= 0) // when the pixel is a state
                    {
                        float dis_temp = sqrt( (randPos.x-col_temp/3)*(randPos.x-col_temp/3) + (randPos.y-row_temp)*(randPos.y-row_temp) );
                        if(dis_temp < dis_min )
                        {
                            nearPos.y = row_temp;
                            nearPos.x = col_temp/3;
                            dis_min = dis_temp;
                        }
                    }
                }

            }
        }

        // == Create a new State ==
        cv::Point newPos(0,0);
        float scale_factor = this->new_state_dis/dis_min;
        newPos.x = nearPos.x + (int)(round( (randPos.x-nearPos.x) * scale_factor ));
        newPos.y = nearPos.y + (int)(round( (randPos.y-nearPos.y) * scale_factor ));
        if( newPos.x <= 3 || newPos.x >= (this->img_cols - 3) || newPos.y <= 3 || newPos.y >= (this->img_rows - 3))
            continue;

        // == Verify the new State ==
        // Check the new point is not on the obstacles area
        uchar pixel_value = this->rrt_graph.at<uchar>(newPos.y,newPos.x); //format: at<uchar>(height, width)
        if(pixel_value < LOW_INTENSITY) // The low intensity area represents the obstacles.
            continue;

        // Check the new edge does no cover the obstacles or goal area (by checking the ROI from rrt_graph matrix)
        bool pass_this_loop = false;
        float mask2goal = 10000;
        cv::Point Mask_Pos;
        uchar mask_pixel_value = 255;
        for(int dis_incr = 1; (dis_incr < this->new_state_dis) && (pass_this_loop == false) && (this->goal_reach == false); dis_incr ++)
        {
            Mask_Pos.x = nearPos.x + (int)(round( (newPos.x-nearPos.x) / this->new_state_dis * dis_incr ));
            Mask_Pos.y = nearPos.y + (int)(round( (newPos.y-nearPos.y) / this->new_state_dis * dis_incr ));
            mask_pixel_value = this->rrt_graph.at<uchar>(Mask_Pos.y,Mask_Pos.x);
            if(mask_pixel_value < LOW_INTENSITY)
                pass_this_loop = true;

            mask2goal = this->cvPoint_distance(Mask_Pos, this->goalPos);
            if((int)(mask2goal) <= this->goal_radius)
                this->goal_reach = true;
        }

        if(pass_this_loop)
            continue;


        // == Add the new state ==
        int cost_parent = this->rrt_tree.at<cv::Vec3i>(nearPos.y,nearPos.x)[0];
        this->rrt_tree.at<cv::Vec3i>(newPos.y,newPos.x)[0] = cost_parent + 1; // For RRT-Tree matrix: add vertex with incremenal cost
        this->rrt_tree.at<cv::Vec3i>(newPos.y,newPos.x)[1] = nearPos.x; // For RRT-Tree matrix: add edge with parent node pos_x
        this->rrt_tree.at<cv::Vec3i>(newPos.y,newPos.x)[2] = nearPos.y;

        cv::circle( this->img_process, cv::Point(newPos.x,newPos.y), 2, cv::Scalar( 255, 0, 0 ), -2, 8 );  // For visualization: add node
        cv::line(this->img_process, nearPos, newPos, cv::Scalar(200, 0, 0) );

        // == Check the goal ==
        float goal_area = this->cvPoint_distance(newPos, this->goalPos);
        if((int)(goal_area) <= this->goal_radius)  
            this->goal_reach = true;

        if(this->goal_reach)
        {
            this->goalachievedPos = newPos;
            break;
        }

        node_count ++;
    } // End of the RRT

    if(this->goal_reach)
    {
        QString result_text = "Goal Achieved!  No. of nodes: " + QString::number(node_count);
        ui->LE_status->setText(result_text);

        // == Find the goal achieved trajectory ==
        bool trajectory_finish = false;
        cv::Point parentPos;
        cv::Point currPos;

        currPos = this->goalachievedPos;
        while(trajectory_finish == false)
        {
            if(this->rrt_tree.at<cv::Vec3i>(currPos.y,currPos.x)[0] == 0) // The start point
            {
                trajectory_finish = true;
                break;
            }

            parentPos.x = this->rrt_tree.at<cv::Vec3i>(currPos.y,currPos.x)[1]; // pos_x of parent node
            parentPos.y = this->rrt_tree.at<cv::Vec3i>(currPos.y,currPos.x)[2]; // pos_y of parent node

            // For Visualization
            cv::circle( this->img_process, cv::Point(parentPos.x,parentPos.y), 3, cv::Scalar( 255, 0, 255 ), -3, 8 );  // For visualization: add node
            cv::line(this->img_process, parentPos, currPos, cv::Scalar(200, 0, 200), 2 );

            currPos = parentPos;
        }
    }
    else
    {
        QString result_text = "Goal Unachieved!  No. of nodes: " + QString::number(node_count);
        ui->LE_status->setText(result_text);
    }

    // Visualize the result
    cv::circle( this->img_process, this->startPos, 5, cv::Scalar( 0, 0, 255 ), -5, 8 ); // Draw the start point again
    QImage qimg_temp = convertOpenCVMatToQtQImage(this->img_process);
    ui->QL_imgview->clear();
    ui->QL_imgview->setPixmap(QPixmap::fromImage(qimg_temp));
}



void MainWindow::on_SB_max_nodes_valueChanged(int arg1)
{
    if(arg1 <= 10)
    {
        arg1 = 10;
        ui->SB_max_nodes->setValue(arg1);
    }

    this->max_nodes = arg1;
}

void MainWindow::on_SB_goal_radius_valueChanged(int arg1)
{
    if(arg1 <= 3)
    {
        arg1 = 3;
        ui->SB_goal_radius->setValue(arg1);
    }

    this->goal_radius = arg1;
}

void MainWindow::on_SB_new_state_dis_valueChanged(int arg1)
{
    if(arg1 <= 1)
    {
        arg1 = 1;
        ui->SB_new_state_dis->setValue(arg1);
    }

    this->new_state_dis = arg1;
}
