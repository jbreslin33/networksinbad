//#include "Tutorial4.h"
#include "common.h"
#include "SinbadCharacterController.h"


CArmyWar* game;
bool keys[256];


void CArmyWar::createPlayer(int index)
{
	/*
	Ogre::Entity* NinjaEntity = mSceneMgr->createEntity("sinbad.mesh");
	//Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
	Ogre::SceneNode* node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(NinjaEntity);
    //node->setPosition(Ogre::Vector3(10, 10, 10));

	*/
    //clientData *client = game->GetClientPointer(index);

	//client->myNode = node;

    clientData *client = game->GetClientPointer(index);

	client->character = new SinbadCharacterController(mSceneMgr->getCamera("PlayerCam"), "Sinbad" + index);
	
}
//-------------------------------------------------------------------------------------
void CArmyWar::createScene(void)
{
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.75, 0.75, 0.75));
 
    Ogre::Light* pointLight = mSceneMgr->createLight("pointLight");
    pointLight->setType(Ogre::Light::LT_POINT);
    pointLight->setPosition(Ogre::Vector3(250, 150, 250));
    pointLight->setDiffuseColour(Ogre::ColourValue::White);
    pointLight->setSpecularColour(Ogre::ColourValue::White);

	//character = new SinbadCharacterController(mSceneMgr->getCamera("PlayerCam"), "sinbad");

}
//-------------------------------------------------------------------------------------
bool CArmyWar::processUnbufferedInput(const Ogre::FrameEvent& evt)
{
 
    if (mKeyboard->isKeyDown(OIS::KC_W)) // Forward
    {
		keys[VK_UP] = TRUE;
    }
	else
	{
        keys[VK_UP] = FALSE;
	}
    if (mKeyboard->isKeyDown(OIS::KC_S)) // Backward
    {
		keys[VK_DOWN] = TRUE;
    }
	else
	{
        keys[VK_DOWN] = FALSE;
	}

    if (mKeyboard->isKeyDown(OIS::KC_A)) // Left - yaw or strafe
    {
		keys[VK_LEFT] = TRUE;
    }
	else
	{
        keys[VK_LEFT] = FALSE;
	}
    if (mKeyboard->isKeyDown(OIS::KC_D)) // Right - yaw or strafe
    {
		keys[VK_RIGHT] = TRUE;
    }
	else
	{
        keys[VK_RIGHT] = FALSE;
	}
         
    return true;
}
//-------------------------------------------------------------------------------------
bool CArmyWar::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    bool ret = BaseApplication::frameRenderingQueued(evt);
 
    if(!processUnbufferedInput(evt)) return false;

	//if (localClient)
		//localClient->character->addTime(evt.timeSinceLastFrame);

	
	if(game != NULL)
	{
		game->CheckKeys();

		game->RunNetwork(evt.timeSinceLastFrame * 1000);

		rendertime = evt.timeSinceLastFrame;

		//game->Frame();
	}
 
    return ret;
}

//-------------------------------------------------------------------------------------
bool CArmyWar::keyPressed( const OIS::KeyEvent &arg )
{
    //Ogre::LogManager::getSingletonPtr()->logMessage("*** keyPressed CArmyWar n***");
	//LogString("keyPressed");
	//game->localClient->character->injectKeyDown(arg);
	if(localClient)
	   localClient->character->injectKeyDown(arg);
	return BaseApplication::keyPressed(arg);
} 

bool CArmyWar::keyReleased( const OIS::KeyEvent &arg )
{
    //Ogre::LogManager::getSingletonPtr()->logMessage("*** keyPressed CArmyWar n***");
	//LogString("keyReleased");
	//game->localClient->character->injectKeyUp(arg);
	if(localClient)
	   localClient->character->injectKeyUp(arg);
	return BaseApplication::keyReleased(arg);
} 

//-------------------------------------------------------------------------------------
 
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
         game = new CArmyWar;

		//game = new CArmyWar;
	    game->StartConnection();

		StartLogConsole();

 
        try {
            game->go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif