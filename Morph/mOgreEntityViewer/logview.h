/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file logview.h
 * @brief A text browser view for displaying log outputs.
 *
 * Copyright (C) 2011-2012 by @author Islam Wazery <wazery at ubuntu dot com>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#ifndef LOGVIEW_H
#define LOGVIEW_H

#include <QTextBrowser>

#include "MorphCore/Editor/MLogManager.h"

class LogView : public QTextBrowser, public MLogListener
{
    Q_OBJECT
public:
    LogView(QWidget* parent = 0);

    void messageLogged(QString message, logType type);
};

#endif // LOGVIEW_H
