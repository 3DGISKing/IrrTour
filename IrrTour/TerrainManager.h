#ifndef TERRAIN_MANAGER_H

#define TERRAIN_MANAGER_H

#include "Global.h"

class TerrainManager
{
public:
	TerrainManager(IVideoDriver*d,ISceneManager* s);
	~TerrainManager();
	
	void               loadTerrain();
	void               setupCollisionResponse();
	ITerrainSceneNode* getTerrain(){return Terrain;}
	aabbox3d<f32>      getBoundingBox() {return Terrain->getBoundingBox();}
	f32                getVerticalExaggeration(){return VerticalExaggeration;}
	f32                getHeight(f32 x,f32 y);

private:
	void                readConfig();
private:
	IVideoDriver*        Driver;	
	ISceneManager*       SceneMgr;
	ITerrainSceneNode*   Terrain; 
	
	f32                  DemResolution;         // in meter 
	f32                  VerticalExaggeration;

	f32                  WidthX;   //in meter
	f32                  WidthZ;   //in meter

	s32                  MaxLOD;
	s32                  SmoothFactor;
	E_TERRAIN_PATCH_SIZE PatchSize;
};

#endif

