#ifndef __OGREWIDGET_H__
#define __OGREWIDGET_H__

#include <OGRE/Ogre.h>
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

#include <QtOpenGL/QGLWidget>

#include "utils.h"
#include "Map.h"

class OgreWidget : public QGLWidget
{
    Q_OBJECT;

public:
	OgreWidget(QWidget *parent = 0);

	virtual ~OgreWidget();

    /**
    * Funkcja sluzaca do rysowania zadanej mapy
    */
	void redrawScene(Map* map);

    void turnCamera(Direction direction);

protected:

    /**
    * @brief setup the rendering context
    * @author Kito Berg-Taylor
    */
    virtual void initializeGL();

    /**
    * @brief resize the GL window
    * @author Kito Berg-Taylor
    */
    virtual void resizeGL(int, int);

    /**
    * @brief render a frame
    * @author Kito Berg-Taylor
    */
    virtual void paintGL();

    /**
    * @brief init the object
    * @author kito berg-taylor
    */
    void init(std::string, std::string, std::string);

    /**
    * @brief choose the right renderer
    * @author Kito Berg-Taylor
    */
    virtual Ogre::RenderSystem* chooseRenderer(const Ogre::RenderSystemList*);

	void setCubeParams(Ogre::ManualObject* cube);

    void setupResources(void);
    void ogreInitialization();

    Ogre::Root *mOgreRoot;
    Ogre::RenderWindow *mOgreWindow;
    Ogre::Camera *mCamera;
    Ogre::Viewport *mViewport;
    Ogre::SceneManager *mSceneMgr;
    Ogre::OverlaySystem *mOverlaySystem;

    OgreBites::SdkCameraMan* mCameraMan;

    Ogre::String mResourcesCfg;
    Ogre::String mPluginsCfg;

    float cameraDistance = 30;
};

#endif
