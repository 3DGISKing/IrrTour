#include "SceneController.h"

#include "RenderWindow.h"
#include "TerrainManager.h"

SceneController::SceneController(RenderWindow* w)
{
	RenderWin = w;

	Driver           = RenderWin->driver();
	SceneMgr         = RenderWin->sceneManager();

	CameraMoveSpeed   = 0.2f;
	CameraRotateSpeed = 30.0f;

	CameraInitPosition.set(1491.282349f, 237.133942f, -866.552185f);
	CameraInitTargetPosition.set(934.611938f, 92.294006f, -837.867554f);

	init();
}

SceneController::~SceneController()
{
	if(TerrainMgr)
		delete TerrainMgr;
}


void SceneController::init()
{
	TerrainMgr=new TerrainManager(Driver,SceneMgr);

	TerrainMgr->loadTerrain();

	prepareScene();

	TerrainMgr->setupCollisionResponse();
	
	setupInitCameraPose();
}

void SceneController::setupInitCameraPose()
{
	ICameraSceneNode* camera=SceneMgr->getActiveCamera();

	camera->setFOV(PI/12.0f);
	camera->setPosition(CameraInitPosition);

	camera->setTarget(CameraInitTargetPosition);
	camera->setFarValue(100000.0f);
}

void SceneController::prepareScene()
{
	setupCamera();
	setupLight();
	setupSky();
	loadMeshs();
	setupSceneBox();
}

void SceneController::setupLight()
{
	SceneMgr->addLightSceneNode(0, core::vector3df(1500.0f,500.0f,2500),
		video::SColorf(1.0f,1.0f,1.0f),2000);
	SceneMgr->setAmbientLight(video::SColorf(1.0f,1.0f,1.0f));
}
void SceneController::loadMeshs()
{
	stringw path=Global::getInstance()->dataPath();
	RenderWin->device()->getFileSystem()->addFileArchive(path+"/models");
	SceneMgr->loadScene(path+"/scene.irr");
	//setObjectsHeight();
}

void SceneController::setupCamera()
{
	scene::ICameraSceneNode* camera =
		SceneMgr->addCameraSceneNodeFPS(0,CameraRotateSpeed,CameraMoveSpeed);
}

void SceneController::setupSceneBox()
{
	aabbox3d<f32> box=TerrainMgr->getBoundingBox();

	vector3df scale=box.MaxEdge*2.0;

	f32 maxcamerafactor=5.0;

	scale.Y=box.MaxEdge.Y*maxcamerafactor;

	IMesh* mesh=SceneMgr->getGeometryCreator()->createCubeMesh(scale);

	SceneMgr->getMeshManipulator()->flipSurfaces(mesh);

	scene::ISceneNode* scenebox = SceneMgr->addMeshSceneNode(mesh);
	mesh->drop();

	scenebox->setPosition(vector3df(0.0f,box.MinEdge.Y,0.0f));

	ITriangleSelector* selector=SceneMgr->createTriangleSelector(mesh,scenebox);

	ICameraSceneNode* camera=SceneMgr->getActiveCamera();

	scene::ISceneNodeAnimatorCollisionResponse* collider =
					SceneMgr->createCollisionResponseAnimator(
					selector, camera, core::vector3df(100.0f,100.0f,100.0f),
					core::vector3df(0.0f, 0.0f,0.0f));

	selector->drop();

	camera->addAnimator(collider);
	collider->drop();

	scenebox->setVisible(false);
}


void SceneController::setObjectsHeight()
{
	array<ISceneNode *> nodes;
	SceneMgr->getSceneNodesFromType(ESNT_MESH, nodes); // Find all mesh nodes

	for (u32 i=0; i < nodes.size(); ++i)
	{
		ISceneNode * node = nodes[i];

		aabbox3d<f32> box=node->getBoundingBox();

		f32 meshheight=box.getExtent().Y;

		vector3df pos=node->getPosition();

		f32 height=TerrainMgr->getHeight(pos.X,pos.Z);

		pos.Y=height+meshheight/2;

		node->setPosition(pos);
	}
}

void SceneController::setupSky()
{
	stringw path=Global::getInstance()->dataPath();

	path=path+"/sky/";

	Driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);

	scene::ISceneNode* skydome=SceneMgr->addSkyDomeSceneNode(Driver->getTexture(path+"skydome.jpg"),16,8,0.95f,2.0f);

	Driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
}