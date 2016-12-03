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
//#include <QX11Info>

class OgreWidget : public QGLWidget
{
    //Q_OBJECT;

public:
    OgreWidget(QWidget *parent = 0) :
        QGLWidget(parent),
        mOgreWindow(NULL)
    {
        #ifdef _DEBUG
            mResourcesCfg = "resources_d.cfg";
            mPluginsCfg = "plugins_d.cfg";
        #else
            mResourcesCfg = "resources.cfg";
            mPluginsCfg = "plugins.cfg";
        #endif

       init(mPluginsCfg, "./ogre.cfg", "./ogre.log");
    }

    virtual ~OgreWidget()
    {
        mOgreRoot->shutdown();
        delete mOgreRoot;
        destroy();
    }

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
};

#endif
