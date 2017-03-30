#include <assert.h>

#include "TerrainManager.h"

TerrainManager::TerrainManager(IVideoDriver*d,ISceneManager* s)
{
	Driver       = d;
	SceneMgr     = s;

	MaxLOD       = 5;
	PatchSize    = ETPS_17;
	SmoothFactor = 3;
}

TerrainManager::~TerrainManager()
{
	
}

void TerrainManager::readConfig()
{
	DemResolution        = 23.20845703125f;//19.8 
	VerticalExaggeration = 1.0f;

	WidthX=WidthZ=0.0f;
}

void TerrainManager::loadTerrain()
{
	readConfig();

	stringw path=Global::getInstance()->dataPath();

	path=path+"/terrain/";

	Terrain= SceneMgr->addTerrainSceneNode(
										path+"terrain-heightmap.bmp",
										0,					                    // parent node
										-1,					                    // node id
										vector3df(0.f, 0.f, 0.f),		        // position
										vector3df(0.f, 0.f, 0.f),		        // rotation
										vector3df(DemResolution, VerticalExaggeration, DemResolution),	// scale
										SColor ( 255, 255, 255, 255 ),	        // vertexColor
										MaxLOD,					                // maxLOD
										PatchSize,		                        // patchSize
										SmoothFactor				 	        // smoothFactor
										);

	Terrain->setMaterialFlag(video::EMF_LIGHTING, false);

	Terrain->setMaterialTexture(0,Driver->getTexture(path+"terrain-texture.jpg"));

	Terrain->setMaterialTexture(1,
		Driver->getTexture("./texture/detailmap3.jpg"));

	Terrain->setMaterialType(video::EMT_DETAIL_MAP);

	Terrain->scaleTexture(1.0f, 200.0f);

	vector3df pos=-Terrain->getTerrainCenter();



	pos.Y=0.0f;

	Terrain->setPosition(pos);
}

void TerrainManager::setupCollisionResponse()
{
	ITriangleSelector* selector= SceneMgr->createTerrainTriangleSelector(Terrain, 0);

	Terrain->setTriangleSelector(selector);

	ICameraSceneNode * activecamera=SceneMgr->getActiveCamera();

	assert(activecamera!=NULL);

	ISceneNodeAnimator* anim = SceneMgr->createCollisionResponseAnimator(
							   selector,
							   activecamera,
							   vector3df(2,2,2),
							   vector3df(0,0,0),
							   vector3df(0,30,0));

	selector->drop();

	activecamera->addAnimator(anim);

	anim->drop();
}

f32 TerrainManager::getHeight(f32 x,f32 y)
{
	return Terrain->getHeight(x,y);
}
