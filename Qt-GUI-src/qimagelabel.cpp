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

#include "qimageLabel.h"

QImageLabel::QImageLabel(QWidget *parent) :
    QLabel(parent)
{

}

void QImageLabel::mouseMoveEvent(QMouseEvent *event)
{
    this->x = event->x();
    this->y = event->y();
    emit signal_MousePosition(event->x(), event->y());
}

void QImageLabel::mousePressEvent(QMouseEvent *event)
{
    bool isLeftBtn = false;
    if (event->buttons() == Qt::LeftButton)
    {
        isLeftBtn = true;
    }
    emit signal_MousePress(isLeftBtn, event->pos());
}
