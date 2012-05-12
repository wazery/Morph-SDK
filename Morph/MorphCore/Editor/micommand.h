/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file micommand.h
 * @brief base command interface.
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

#ifndef MICOMMAND_H
#define MICOMMAND_H

#include "MType.h"
#include <QVector>

using namespace std;

// summary:	this is a base command interface.
typedef void *   (*MCreatorFunction)();

namespace Morph
{
    //use to deep the command arg map MString list;
    typedef std::map<MString, MString> MArgList;

    class MICommand
    {


    public:
        //MICommand(void);

        virtual bool doIt(const MArgList &args) = 0;
        virtual bool redoIt() = 0;
        virtual bool undoIt() = 0;
        virtual bool isUndoable() = 0;
        // Access the ResulMString
        const std::vector<MString> &getResulMString(void) const { return(mResulMStringList); }

        //virtual void SetTestArr(QVector<int> *testArr) = 0;
        //every command instance have to implement this this create fun, use to create the class itself
        //static void* creator(){}

        virtual ~MICommand(void){}

    protected:
        //please keep one argslist instance after execute the doit operate, the redoit(), end undoit() may use is;
        std::vector<MString> mResulMStringList;
    };
}

#endif // MICOMMAND_H
