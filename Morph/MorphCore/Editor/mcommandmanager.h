/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mcommandmanager.h
 * @brief A manager which is responsible for all commands related stuff.
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

#ifndef MCOMMANDMANAGER_H
#define MCOMMANDMANAGER_H

class MCommandManager
{
public:
    MCommandManager();
    ~MCommandManager();

    void registerCommand();
    void deRegisterCommand();

    virtual void commandExecute();

};

#endif // MCOMMANDMANAGER_H
