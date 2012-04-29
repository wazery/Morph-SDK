/* ============================================================
 *
 * This file is a part of Morph project
 *
 * Date        : 2011-10-26
 * @file viewgrid.h
 * @brief A dynamically changing grid system.
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

#ifndef OGRE_VIEWPORTGRID_H
#define OGRE_VIEWPORTGRID_H
 
#include <OGRE/OgreRenderTargetListener.h>
#include <OGRE/OgreColourValue.h>
#include <OGRE/OgreMath.h>
#include <OGRE/OgreVector3.h>
 
namespace Ogre
{
	/** Use this class to render a dynamically adjusting grid inside an Ogre viewport.
		@todo
		Make the grid work with an arbitrary rotated orthogonal camera (e.g. for working in object space mode).
		Or should the grid be rendered in object space too then?
	*/
	class ViewportGrid: public RenderTargetListener
	{
	public:
		//! The render layer of the grid in orthogonal view
		enum RenderLayer
		{
			RL_BEHIND, //!< Behind all objects
			RL_INFRONT //!< In front of all objects
		};
 
	protected:
		// Member variables
		SceneManager *m_pSceneMgr;
		Viewport *m_pViewport;
		bool m_enabled;
		RenderLayer m_layer;
 
		Camera *m_pPrevCamera;
		bool m_prevOrtho;
		Vector3 m_prevCamPos;
		Real m_prevNear;
		Radian m_prevFOVy;
		Real m_prevAspectRatio;
		bool m_forceUpdate;
 
		ManualObject *m_pGrid;
		bool m_created;
		SceneNode *m_pNode;
 
		ColourValue m_colour1, m_colour2;
		unsigned int m_division;
		Real m_perspSize;
		bool m_renderScale, m_renderMiniAxes;
 
	public:
		// Constructors and destructor
		ViewportGrid(SceneManager *pSceneMgr, Viewport *pViewport);
		virtual ~ViewportGrid();
 
		//! Grid colour
		const ColourValue &getColour() const { return m_colour1; }
		void setColour(const ColourValue &colour);
 
		//! Grid division (the number of new lines that are created when zooming in).
		unsigned int getDivision() const { return m_division; }
		void setDivision(unsigned int division);
 
		//! Grid render layer (behind of in front of the objects).
		RenderLayer getRenderLayer() const { return m_layer; }
		void setRenderLayer(RenderLayer layer);
 
		//! Size of the grid in perspective view
		Real getPerspectiveSize() const { return m_perspSize; }
		void setPerspectiveSize(Real size);
 
		//! Render scaling info? Defaults to true.
		//! @todo Implement this
		bool getRenderScale() const { return m_renderScale; }
		void setRenderScale(bool enabled = true);
 
		//! Render mini axes? Defaults to true.
		//! @todo Implement this
		bool getRenderMiniAxes() const { return m_renderMiniAxes; }
		void setRenderMiniAxes(bool enabled = true);
 
		// Enable / disable
		bool isEnabled() const;
		void enable();
		void disable();
		void toggle();
		void setEnabled(bool enabled);
 
		// Other functions
		void forceUpdate() { m_forceUpdate = true; }
 
	protected:
		// RenderTargetListener
		void preViewportUpdate(const RenderTargetViewportEvent &evt);
		void postViewportUpdate(const RenderTargetViewportEvent &evt);
 
		// Other protected functions
		void createGrid();
		void destroyGrid();
 
		void update();
		void updateOrtho();
		void updatePersp();
 
		bool checkUpdate();
		bool checkUpdateOrtho();
		bool checkUpdatePersp();
	};
}
 
#endif // OGRE_VIEWPORTGRID_H 
