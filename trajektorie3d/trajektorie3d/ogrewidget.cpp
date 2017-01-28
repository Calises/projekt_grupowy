#include "ogrewidget.h"

#include <QDebug>

OgreWidget::OgreWidget(QWidget *parent) :
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

OgreWidget::~OgreWidget()
{
	mOgreRoot->shutdown();
	delete mOgreRoot;
	destroy();
}

void OgreWidget::init(std::string plugins_file,
    std::string ogre_cfg_file,
    std::string ogre_log)
{
    // create the main ogre object
    mOgreRoot = new Ogre::Root(plugins_file, ogre_cfg_file, ogre_log);

    //loading resourses
    setupResources();

    // setup a renderer
    const Ogre::RenderSystemList *renderers = &(mOgreRoot->getAvailableRenderers());
    assert(!renderers->empty()); // we need at least one renderer to do anything useful

	for (int i = 0; i < renderers->size(); i++)
		qDebug() << "Available renderer" << QString::fromStdString(renderers->at(i)->getName());
	Ogre::RenderSystem* renderSystem = chooseRenderer(renderers);
	qDebug() << "Choosed" << QString::fromStdString(renderSystem->getName());

    assert(renderSystem); // user might pass back a null renderer, which would be bad!
    mOgreRoot->setRenderSystem(renderSystem);

    QString dimensions = QString("%1x%2").arg(this->width()).arg(this->height());
    renderSystem->setConfigOption("Video Mode", dimensions.toStdString());

    // initialize without creating window
	renderSystem->setConfigOption("Full Screen", "No");
    mOgreRoot->saveConfig();
    mOgreRoot->initialise(false); // don't create a window
}

void OgreWidget::initializeGL()
{
    //== Creating and Acquiring Ogre Window ==//
    // Get the parameters of the window QT created
    Ogre::String winHandle;

    winHandle += Ogre::StringConverter::toString((unsigned long)(this->parentWidget()->winId()));

    Ogre::NameValuePairList params;

    params["parentWindowHandle"] = winHandle;
    mOgreWindow = mOgreRoot->createRenderWindow("QOgreWidget_RenderWindow",
        this->width(),
        this->height(),
        false,
        &params);

    mOgreWindow->setActive(true);
    WId ogreWinId = 0x0;
    mOgreWindow->getCustomAttribute("WINDOW", &ogreWinId);

    assert(ogreWinId);

    // bug fix, extract geometry
    QRect geo = this->frameGeometry();

    // create new window
    this->create(ogreWinId);

    // set geometrie infos to new window
    this->setGeometry(geo);

    setAutoBufferSwap(false);
    setAttribute(Qt::WA_PaintOnScreen, true);
    setAttribute(Qt::WA_NoBackground);

    ogreInitialization();

    // Create the scene
    Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    Ogre::SceneNode* headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    headNode->attachObject(ogreHead);
}

void OgreWidget::paintGL()
{
    // Be sure to call "OgreWidget->repaint();" to call paintGL
    swapBuffers();
    assert(mOgreWindow);
    //mOgreRoot->renderOneFrame();
}

void OgreWidget::resizeGL(int width, int height)
{
    assert(mOgreWindow);
    mOgreWindow->reposition(this->pos().x(),
        this->pos().y());
    mOgreWindow->resize(width, height);
    paintGL();
}

Ogre::RenderSystem* OgreWidget::chooseRenderer(const Ogre::RenderSystemList *renderers)
{
    // It would probably be wise to do something more friendly 
    // that just use the first available renderer
	return renderers->at(0);
}

void OgreWidget::setupResources(void)
{
    // Load resource paths from config file
    Ogre::ConfigFile cf;
    cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

    Ogre::String secName, typeName, archName;
    while (seci.hasMoreElements())
    {
        secName = seci.peekNextKey();
        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
        Ogre::ConfigFile::SettingsMultiMap::iterator i;
        for (i = settings->begin(); i != settings->end(); ++i)
        {
            typeName = i->first;
            archName = i->second;

            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                archName, typeName, secName);
        }
    }
}

void OgreWidget::ogreInitialization()
{
    // choose scenemanager
    Ogre::SceneType scene_manager_type = Ogre::ST_GENERIC;
    mSceneMgr = mOgreRoot->createSceneManager(scene_manager_type);
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

    // create camera
    mCamera = mSceneMgr->createCamera("QOgreWidget_Cam");
    // Position it at 500 in Z direction
    mCamera->setPosition(Ogre::Vector3(0, 0, 40));
    // Look back along -Z
    mCamera->lookAt(Ogre::Vector3(0, 0, -300));
    mCamera->setNearClipDistance(5);
    // create a default camera controller
    mCameraMan = new OgreBites::SdkCameraMan(mCamera);

    // create viewports
    mViewport = mOgreWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(Ogre::ColourValue(0.74, 0.82, 0.9));
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
        Ogre::Real(mViewport->getActualWidth()) / Ogre::Real(mViewport->getActualHeight()));

    // initialize the OverlaySystem (changed for 1.9)
    mOverlaySystem = new Ogre::OverlaySystem();
    mSceneMgr->addRenderQueueListener(mOverlaySystem);

    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

    // load resources
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    //// Create a light
    Ogre::Light* l = mSceneMgr->createLight("MainLight");
    l->setPosition(20, 80, 50);
}
