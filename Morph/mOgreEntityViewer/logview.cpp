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

#include "LogView.h"

LogView::LogView(QWidget* parent)
{
}

void LogView::messageLogged(QString message, logType type)
{
    QTextCursor cursor = this->textCursor();
    QString errorHtml = "<font color=\"Red\">";
    QString warnHtml = "<font color=\"Aqua\">";
    QString editorMessageHtml = "<font color=\"Brown\">";
    QString messageHtml = "<font color=\"Gray\">";
    QString endHtml = "</font><br>";
    QString resultMessage;

    switch (type)
    {
    case M_ERROR:
        resultMessage = errorHtml + message + endHtml;
        break;
    case M_WARN:
        resultMessage = warnHtml + message + endHtml;
        break;
    case M_EDITOR_MESSAGE:
        resultMessage = editorMessageHtml + message + endHtml;
        break;
    }

    this->insertHtml(resultMessage);
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}

LogViewOgre::LogViewOgre(QWidget* parent)
{
}

void LogViewOgre::messageLogged(QString message, logType type)
{
    QTextCursor cursor = this->textCursor();
    QString OgreHtml = "<font color=\"Gray\">";
    QString endHtml = "</font><br>";
    QString resultMessage;

    switch (type)
    {
    case M_OGRE:
        resultMessage = OgreHtml + message + endHtml;
        break;
    }

    this->insertHtml(resultMessage);
    cursor.movePosition(QTextCursor::End);
    this->setTextCursor(cursor);
}
