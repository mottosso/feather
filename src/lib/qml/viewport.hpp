/***********************************************************************
 *
 * Filename: viewport.hpp
 *
 * Description: Holds the scenegraph.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#ifndef VIEWPORT_HPP 
#define VIEWPORT_HPP

#include "deps.hpp"
#include "qml_deps.hpp"
#include "types.hpp"
#include "gl_scene.hpp"


class ViewportRender : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT

    public:
        ViewportRender();
        ~ViewportRender();

        void initialize();
        void render(int width, int height);
        void rotateCamera(int x, int y);
        void zoomCamera(int z);
        void setViewportSize(const QSize &size) { m_viewportSize = size; };
           
    public slots:
        void paint();

    //protected:
        //QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
        //void mousePressEvent(QMouseEvent* event);

    private:
        QSize m_viewportSize;
        feather::gl::glScene* m_pScene;    
        int m_CurrentCamera;


};


class Viewport : public QQuickItem
{
    Q_OBJECT

    public:
        Viewport();
        ~Viewport();

        //static QList<QRender *> threads;
       Q_INVOKABLE void mousePressed(int x, int y);
       Q_INVOKABLE void moveCamera(int x, int y);
       Q_INVOKABLE void zoomCamera(int z);

       //public Q_SLOTS:
       //    void ready();

    public slots:
        void sync();
        void cleanup();

    private slots:
        void handleWindowChanged(QQuickWindow *win);

    private:
        //RenderViewportRender *m_renderRender;
        ViewportRender *m_pRender;
        int m_x;
        int m_y;

};


#endif
