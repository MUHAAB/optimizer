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

#include "thread.h"
#include "utils.h"
#include <QDebug>

Thread::Thread(QObject *parent)
    : QThread(parent)
{

}

void Thread::run()
{
    unsigned long long currentWorkTime = 0, prevWorkTime = 0;
    unsigned long long currentTotalTime = 0, prevTotalTime = 0;
    unsigned long long prevRecv = 0, prevSend = 0;
    unsigned long long recv = 0, send = 0;
    QString memory = "";
    QString disk = "";
    float memoryPercent = 0;
    float diskPercent = 0;

    while (1) {
        Utils::getMemoryInfo(memory, memoryPercent);
        Utils::getDiskInfo(disk, diskPercent);

        emit updateMemory(memory, memoryPercent);
        emit updateDisk(disk, diskPercent);

        Utils::getCpuTime(prevWorkTime, prevTotalTime);
        Utils::getNetworkBandWidth(prevRecv, prevSend);
        sleep(2);
        Utils::getCpuTime(currentWorkTime, currentTotalTime);
        Utils::getNetworkBandWidth(recv, send);

        emit updateNetworkTotal(Utils::formatBytes(send), Utils::formatBytes(recv));
        emit updateNetworkSpeed("↑ " + Utils::formatBytes(send - prevSend), "↓ " + Utils::formatBytes(recv - prevRecv));
        emit updateCpuPercent((currentWorkTime - prevWorkTime) * 100.0 / (currentTotalTime - prevTotalTime));
    }
}
