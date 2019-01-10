#include <iostream>

#include "Render Engine/basics/DIsplayManager.h"
#include "Render Engine/demo renderer/demobatchrenderer.h"
#include "World/day night cycle/daynightcycle.h"
#include "Render Engine/lenseFlare/LenseFlare.h"
#include "Resource Management/resource management/particleatlascache.h"
#include "Render Engine/particles/ParticleSystem.h"
#include "Render Engine/particle spawns/circlespawn.h"
#include "Render Engine/particle spawns/pointspawn.h"
#include "Render Engine/particles/particleMaster.h"
#include "Source/entity/models.h"
#include "temp/terrain1.h"
#include "temp/PostProcessSelection.h"
#include "temp/CamerManager.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720


int main() {

	
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DisplayManager::createDisplay();
	CameraManager::Init();


	//ParticleAtlasCache::loadALL();

	ParticleAtlasCache::loadALL();

	DayNightCycle dn;
	dn.addSun();
	dn.update();
	
	//Camera camera(vec3(0, 0, 0), vec3(-20, 20, 20));


	//LenseFlare lense = LenseFlare(mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f), CameraManager::pcamera->CreateViewMatrix());

	//例子发射器
	PointSpawn * pSpwan = new PointSpawn();
	CircleSpawn * pCSpwan = new CircleSpawn(vec3(0, 0, 1), 30);
	ParticleSystem tpEmiter = ParticleSystem(ParticleAtlasCache::getAtlas(1), pCSpwan, 2000, 4, 0, 10000, 0.2);
	ParticleSystem cpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), false, pCSpwan, 2000, 4, 0, 1000, 0.2);
	ParticleSystem acpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), true, pCSpwan, 2000, 4, 0, 1000, 0.2);
	tpEmiter.generateParticles(vec3(-0.5, -0.5, 0), 0.2);
	cpEmiter.generateParticles(vec3(0.5, 0.5, 0), 0.5);
	acpEmiter.generateParticles(vec3(-0.5, 0.5, 0), 0.5);
	ParticleMaster::init(mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f));

	PostProcessSelection ps;

	Terrain1 t;
	t.create();

	t.m_tshader->enable();
	t.m_tshader->perspective->load(mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f));
	t.m_tshader->NowlightColor->load(vec4(1.0f, 1.0f, 1.0f,1.0f));
	t.m_tshader->lightpos->load(vec3(50, 100, 50));
	t.m_tshader->disable();

	mat4 project = mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f);
	//mat4 project = mat4::orthographic(-50, 50, -50, 50, 0.1, 300);

	Model cube = Model("Resource/dragon.obj");


	while (!DisplayManager::closedDisplay()) {
		
	
		dn.update();
		EnvironmentVariables::update();
	
		CameraManager::pcamera->move();
		
		DisplayManager::clearDisplay();

		//渲染光晕
		//lense.doOcclusionTest();
		//lense.render(EnvironmentVariables::getLightDirection(), true);
		//渲染粒子
		

		//更新粒子
		ParticleMaster::update(*CameraManager::pcamera);

		ps.setChoice();

		//深度贴图
		
		ps.bind();
		OpenglUtils::prepareNewRenderPass(EnvironmentVariables::horizonColour);
		glDisable(GL_CULL_FACE);
		DisplayManager::clearDisplay();
		t.m_tshader->enable();
		t.m_tshader->view->load(CameraManager::pcamera->CreateViewMatrix());
		t.render();
		t.m_tshader->disable();

		ParticleMaster::renderParticles(*CameraManager::pcamera);
		ps.unbind();
		ps.render();

		DisplayManager::updateDisplay();
	}

	return 0;
}






