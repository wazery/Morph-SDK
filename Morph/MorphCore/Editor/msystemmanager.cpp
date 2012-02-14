/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file msystemmanager.cpp
 * @brief A manager which is responsible for creating the basic things
 * that Ogre needs to start, in another word it bootstraps Ogre.
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

#include "MSystemManager.h"

// Total number of lines in one dimension will be (GRID_LINE_NUM * 2 + 1)
#define GRID_LINE_NUM 3

// Units of space between lines
#define GRID_LINE_SPACE 80

MSystemManager::MSystemManager()
{
}

MSystemManager::~MSystemManager(void)
{
}

bool MSystemManager::initialise(String windowName, int width, int height, NameValuePairList *parms, Root *pRoot)
{
	/** @return name */
}

void MSystemManager::shutDown()
{
}

void MSystemManager::doRender()
{
}

void MSystemManager::createGrid()
{
}

void MSystemManager::resizeWindow(int width, int height)
{
}

bool MSystemManager::initOgreCore(String windowName, int width, int height, Ogre::NameValuePairList *parms)
{
	/** @return name */
}

void MSystemManager::createScene()
{
}

void MSystemManager::destroyScene()
{
}

void MSystemManager::createResourceListener()
{
}

void MSystemManager::createFrameListener()
{
}

void MSystemManager::addResourceLocations()
{
}

void MSystemManager::initResources()
{
}

void MSystemManager::updateStats(void)
{
}

bool MSystemManager::frameStarted(const FrameEvent& evt)
{
	/** @return name */
}

bool MSystemManager::frameEnded(const FrameEvent& evt)
{
}

void MSystemManager::createGridObjects()
{
}

 MSystemManager* MSystemManager::getSingletonPtr()
{
	 /** @return name */
}

 MSystemManager& MSystemManager::getSingleton()
{
	 /** @return name */
}

 void MSystemManager::releaseSingleton()
{
}
