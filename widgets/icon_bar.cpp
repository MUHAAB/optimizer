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

#include "icon_bar.h"

IconBar::IconBar(QWidget *parent)
    : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    icon = new QLabel();
    title = new QLabel("");

    layout->addWidget(icon, 0, Qt::AlignCenter);
    layout->addWidget(title, 0, Qt::AlignCenter);
}

void IconBar::setTitle(const QString &text)
{
    title->setText(text);
}

void IconBar::setIcon(const QPixmap &pixmap)
{
    icon->setPixmap(pixmap);
}
