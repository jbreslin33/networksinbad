#ifndef CLIENT_H
#define CLIENT_H

#include "BaseApplication.h"
#include "common.h"
//#include "Tutorial4.h"

class SinbadCharacterController;

extern bool keys[256];



typedef struct
{
	float x;
	float y;
} VECTOR2D;

typedef struct
{
	int			key;

	VECTOR2D	vel;
	VECTOR2D	origin;
	VECTOR2D	predictedOrigin;
    VECTOR2D    rot;
	VECTOR2D	predictedRot;
	//float       yaw;

	int			msec;
} command_t;

typedef struct clientData
{
	command_t	frame[64];	// frame history
	command_t	serverFrame;					// the latest frame from server
	command_t	command;						// current frame's commands

	int			index;

	VECTOR2D	startPos;
	bool		team;
	char		nickname[30];
	char		password[30];

	Ogre::SceneNode *myNode;

	SinbadCharacterController* character;

	clientData	*next;
} clientData;

// The main application class interface
class CArmyWar : public BaseApplication
{
private:
	// Methods

	// Client.cpp
	void	DrawMap(void);
	
	void	CheckPredictionError(int a);
	void	CalculateVelocity(command_t *command, float frametime);
	void	PredictMovement(int prevFrame, int curFrame);
	void	MoveObjects(void);
	void    MovePlayer(void);
	void    setKeyDirection(command_t *command, float frametime);

	void	AddClient(int local, int index, char *name);
	void	RemoveClient(int index);
	void	RemoveClients(void);

	// Network.cpp
	void	ReadPackets(void);
	void	SendCommand(void);
	void	SendRequestNonDeltaFrame(void);
	void	ReadMoveCommand(dreamMessage *mes, clientData *client);
	void	ReadDeltaMoveCommand(dreamMessage *mes, clientData *client);
	void	BuildDeltaMoveCommand(dreamMessage *mes, clientData *theClient);

	bool processUnbufferedInput(const Ogre::FrameEvent& evt);


	// Variables

	// Network variables
	dreamClient *networkClient;

	clientData *clientList;			// Client list
	clientData *localClient;		// Pointer to the local client in the client list
	int clients;

	clientData inputClient;			// Handles all keyboard input

	float frametime;
	float rendertime;

	char gamename[32];
	bool init;

	//bool mapdata[100][100];
	int gameIndex;

	SinbadCharacterController* character;


public:
	CArmyWar();
	~CArmyWar();

    void createPlayer(int index);
    virtual void createScene(void);
    virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt);

	virtual bool keyPressed( const OIS::KeyEvent &arg );
	virtual bool keyReleased( const OIS::KeyEvent &arg );

	// Client.cpp
	void	Shutdown(void);
	void	CheckKeys(void);
	void	Frame(void);
	void	RunNetwork(int msec);
	
	// Network.cpp
	void	StartConnection();
	void	Connect(void);
	void	Disconnect(void);
	void	SendStartGame(void);

	void	SetName(char *n)		{ strcpy(gamename, n); }
	char	*GetName(void)			{ return gamename; }

	void	SetGameIndex(int index)	{ gameIndex = index; }
	int		GetGameIndex(void)		{ return gameIndex; }

	clientData *GetClientList(void) { return clientList; }

	clientData *GetClientPointer(int index);


	CArmyWar *next;
};

#endif