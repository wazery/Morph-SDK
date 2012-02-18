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

#pragma once // To take the advantege of its optimizations the compiler may support.

#ifndef MLOGMANAGER_H
#define MLOGMANAGER_H

//#include <OgreSingleton.h> // FIXME: Implement a singleton pattern for Morph namespace.
#include <vector>
#include <iostream>
#include <fstream>

enum logType
{
    M_MESSAGE,
    M_ERROR,
    M_WARN
};

// TODO: Implement some log levels.

/** @class Pure abstract class for registring logs */
class MLogListener
{
public:
    MLogListener();
    ~MLogListener();

    /** This is called whenever the log receives a message and is about to write it out.
    @param message string
        The message to be logged.
    @param type logType
        Message from Ogre, Error, or even a Warnning.
    */
    virtual void messageLogged(const std::string& message, logType type) = 0;
};

class MLogManager
{
public:
    MLogManager();
    ~MLogManager();

    /** Generalized output logging function, logs messages, errors, and even warns.
    @param message string
        The message to be logged.
    @param type logType
        Handles the type of output to be logged.
    @param writeToFile bool
        True if the log will be written to a file, set by default to true, set by default to true.
    */
    void logOutput(const std::string &message, logType type, bool writeToFile = true);

    /** Add a listner
    @param listener MLogListener
    */
    void addListener(MLogListener* listener) { mLogListnerList.push_back(listener); }

    /** Remove a listner
    @param listener MLogListener
    */
    // FIXME: void removeListner(MLogListener* listener) { mLogListnerList.erase(std::find(mLogListnerList.begin(), mLogListnerList.end(), listener)); }

    static MLogManager* smInstance;

    static MLogManager& getSingleton();
    static MLogManager* getSingletonPtr();
    static void releaseSingleton();

protected:
    std::vector<MLogListener*> mLogListnerList;
    std::ofstream mOutputFile;
};

MLogManager* MLogManager::smInstance = NULL;

#endif // MLOGMANAGER_H
