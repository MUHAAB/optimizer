/* -*- Mode: C++; indent-tabs-mode: nil; tab-width: 4 -*-
 * -*- coding: utf-8 -*-
 *
 * Copyright (C) 2017 Rekols
 *
 * Author:     Rekols <rekols@foxmail.com>
 * Maintainer: Rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "progress_bar.h"
#include <QPainter>
#include <qmath.h>
#include <QDebug>

ProgressBar::ProgressBar(QWidget *parent)
    : QWidget(parent)
{
    title = "";
    color = QColor("#2CA7F8");

    minValue = 0;
    maxValue = 100;
    value = 0;

    nullPosition = 0;
    borderWidth = 8;

    setFixedSize(200, 200);
}

void ProgressBar::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int radius = 99 - borderWidth / 2;

    QPen pen;
    pen.setWidthF(borderWidth);
    pen.setColor(QColor("#F3F3F3"));

    /* init painter */
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 200.0, side / 200.0);

    /* draw background */
    painter.setPen(pen);
    painter.drawArc(QRect(-radius, -radius, radius * 2, radius * 2), nullPosition * 16, -(-360) * 16);

    /* draw value */
    pen.setColor(color);
    painter.setPen(pen);
    double length = 360.0 / (maxValue - minValue) * (value - minValue);
    QRect rect(-radius, -radius, radius * 2, radius * 2);
    painter.drawArc(rect, nullPosition * 16, -length * 16);

    /* draw title text */
    QFont font;
    font.setPointSize(20);
    painter.setFont(font);

    /* qreal left, qreal top, qreal width, qreal height */
    QRectF titleRect(-radius, (-radius), radius * 2, radius * 2);
    painter.setPen(QColor("#000000"));
    painter.drawText(titleRect, Qt::AlignCenter, title);

    /* draw percent text*/
    font.setPointSize(15);
    painter.setFont(font);
    painter.setPen(pen);

    QRectF percentRect(-radius, (-radius) + 35, radius * 2, radius * 2);
    QString strPercent = QString("%1%").arg(value);
    painter.drawText(percentRect, Qt::AlignCenter, strPercent);
}

void ProgressBar::setValue(int percent)
{
    value = percent;

    update();
}

void ProgressBar::setTitle(QString text)
{
    title = text;

    update();
}

void ProgressBar::setColor(QColor colour)
{
    color = colour;

    update();
}
