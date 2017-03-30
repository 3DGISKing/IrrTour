#ifndef SCENE_CONTROLLER_H

#include "Global.h"

#define SCENE_CONTROLLER_H

class RenderWindow;
class TerrainManager;

class SceneController
{
public:
	SceneController(RenderWindow* w);
	~SceneController();

	void prepareScene();

private:
	void init();

	void            setupLight();
	void            setupCamera();
	void            setupSky();
	void            loadMeshs();
	void            setupInitCameraPose();
	void            setupSceneBox();
	void            setObjectsHeight();

private:
	RenderWindow*  RenderWin;

	IVideoDriver*        Driver;
	ISceneManager*       SceneMgr; 

	TerrainManager*      TerrainMgr;

	f32                  CameraRotateSpeed;
	f32                  CameraMoveSpeed;

	vector3df            CameraInitPosition;
	vector3df            CameraInitTargetPosition;
};

#endif