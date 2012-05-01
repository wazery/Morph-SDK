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

#include <map>
#include "MType.h"
#include "micommand.h"
#include <iostream>
#include <memory>
#include <QVector>

using namespace std;

namespace Morph
{
    class MICommand;

    /* Abstract class, derive this class and register to listen to Command change */
    class MCommandListener
    {
    public:
        virtual ~MCommandListener() {}

        /* When the  command execute success,this will be call
        @param selectedNodeList node select list. */
        virtual void commandExecuted(const MString &commandName,MICommand * pCommand) = 0;
    };

    typedef QVector<MICommand *> MCommandInstanceList;

    typedef map<MString, MCreatorFunction> MCommandRegList;

    /* Manager for commands.Register the command, execuate it,and get the result return */
    class MCommandManager
    {
    public:
        MCommandManager();
        ~MCommandManager();

        /** Register command.
            @remarks this function will keep the command name,
                and the command creator address in the commandRegList
            @param commandName	Name of the command. the name must unique in the whole system
            @param creatorFun 	The creator fun address pointer.
            @return true if it succeeds, false if it fails.
        */
        bool registerCommand(const MString &commandName, MCreatorFunction creatorFun);

        /** Deregister command. remove the command name from the list
            @param commandName	Name of the command.
            @returns			true if it succeeds, false if it fails.
        */
        bool deregisterCommand(const MString &commandName);


        /** first you have to parse the Command String,and get the argList;
            maybe some command have not param,but you have to pass a empty arg list to it
            @param commandName	Name of the command.
            @param args			The arguments.
            @returns		true if it succeeds, false if it fails.
        */
        bool executeCommand(const MString &commandName, const MArgList &args, std::vector<MString> &resulMStringList);

        /** Executes the command string. in this case ,the arg have not be parse
            @param commandString 	The command string,include the command name,and the arg value
            @returns				true if it succeeds, false if it fails.
        */
        bool executeString(const MString &commandString, std::vector<MString> &resulMStringList);

        /** Executes the undo operation.One time take one undo action.will return result by the result string,
            @param resulMStringList return the result string list. </param>
            @returns true if it succeeds, false if it fails.
        */
        bool executeUndo(std::vector<MString> &resulMStringList);
        bool executeRedo(std::vector<MString> &resulMStringList);


        /* the command was new by the creator,so if you have not need it again,you have to delete if and free the memory. */
        void clearUndoList();
        void clearRedoList();

        void initialize();
        static MCommandManager * msInstance;

        /* Get the class address pointer; */
        static MCommandManager* getSingletonPtr();

        static MCommandManager &getSingleton();
        static void releaseSingleton();

        /* Access the UndoNamesList */
        const QVector<MString> &getUndoNamesList(void) const { return(mUndoNamesList); }
        /* Access the RedoNamesList */
        const QVector<MString> &getRedoNamesList(void) const { return(mRedoNamesList); }

        QVector<MString> getCommandNamesList(void) const;


        /** Register a listener.
            @param listener	A valid listener derived class.
        */
        void addCommandListener(MCommandListener* listener);


        /** Unregister a listener.
            @param listener 	A valid listener derived class.
        */
        void removeCommandListener(MCommandListener* listener);

        // Access the ErrorString
        const MString &getErrorString(void) const { return(mErrorString); }

    protected:

        // this list use to keep all the command that have been register to the system;
        MCommandRegList mCommandRegList;
        MCommandInstanceList mCommandUndoList;
        MCommandInstanceList mCommandRedoList;
        MArgList mEmptyArgs;

        // recoad all the undo command names,use to show on UI "undo" button.
        QVector<MString> mUndoNamesList;
        // recoad all the redo command names,use to show on UI "redo" button.
        QVector<MString> mRedoNamesList;

        MString mErrorString;

        std::vector<MCommandListener*> mCommandListenerList;

        unsigned int mMaxUndoNum;
    };
#endif // MCOMMANDMANAGER_H
