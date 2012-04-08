/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file mlogmanager.h
 * @brief A manager which is responsible for logging Morph messages
 * to the user, its implementation is similar to the Ogre log implementation.
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

#include "MLogManager.h"
#include <iomanip>

using namespace Morph;

MLogListener::MLogListener()
{
}

MLogManager* MLogManager::smInstance = NULL;

MLogListener::~MLogListener()
{
}

MLogManager::MLogManager()
{
    mOutputFile.open("Morph.log");
}

MLogManager::~MLogManager()
{
    mOutputFile.close();
}

void MLogManager::logOutput(MString message, logType type, bool writeToFile)
{
    for (std::vector<MLogListener*>::iterator it = mLogListnerList.begin(); it != mLogListnerList.end(); ++it)
        (*it)->messageLogged(message, type);

	if (writeToFile && mOutputFile.is_open())
	{
		struct tm *pTime;
		time_t ctTime;
        time(&ctTime);
		pTime = localtime(&ctTime);
        switch (type)
        {
        case M_MESSAGE:
            mOutputFile << std::setw(2) << std::setfill(('0')) << pTime->tm_hour
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_min
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_sec
                        << (", Message: ") << message.toUtf8().constData() << std::endl;
            break;
        case M_ERROR:
            mOutputFile << std::setw(2) << std::setfill(('0')) << pTime->tm_hour
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_min
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_sec
                        << (", Error: ") << message.toUtf8().constData() << std::endl;
            break;
        case M_WARN:
            mOutputFile << std::setw(2) << std::setfill(('0')) << pTime->tm_hour
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_min
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_sec
                        << (", Warning: ") << message.toUtf8().constData() << std::endl;
            break;
        case M_EDITOR_MESSAGE:
            mOutputFile << std::setw(2) << std::setfill(('0')) << pTime->tm_hour
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_min
                        << (":") << std::setw(2) << std::setfill(('0')) << pTime->tm_sec
                        << (", Editor Message: ") << message.toUtf8().constData() << std::endl;
            break;
        }

		// Flush stcmdream to ensure it is written (incase of a crash, we need log to be up to date)
		mOutputFile.flush();
	}
}

MLogManager& MLogManager::getSingleton()
{
    if (smInstance == NULL)
        smInstance = new MLogManager();

    return *smInstance;
}

MLogManager* MLogManager::getSingletonPtr()
{
    if (smInstance = NULL)
        smInstance = new MLogManager();

    return smInstance;
}

void MLogManager::releaseSingleton()
{
    if (smInstance)
    {
        delete smInstance;
        smInstance = NULL;
    }
}
