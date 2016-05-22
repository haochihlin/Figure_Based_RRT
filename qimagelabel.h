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

#ifndef QIMAGELABEL_H
#define QIMAGELABEL_H

#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include <QPoint>

class QImageLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QImageLabel(QWidget *parent = 0);

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void signal_MousePosition(int x, int y);
    void signal_MousePress(bool leftOrRight, QPoint);

private:
    int x, y;

public slots:

};


#endif // QIMAGELABEL_H

