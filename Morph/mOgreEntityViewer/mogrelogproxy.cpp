/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mogrelogproxy.cpp
 * @brief A proxy for getting Ogre log to Morph log.
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

#include "mogrelogproxy.h"
#include "MorphCore/Editor/MLogManager.h"
#include "QString"

MOgreLogProxy::MOgreLogProxy()
{
}

void MOgreLogProxy::messageLogged(const Ogre::String &message, Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName)
{
    MLogManager::getSingleton().logOutput(QString::fromUtf8(message.data()));
}
