#include <iostream>

#include "Render Engine/basics/DIsplayManager.h"
#include "Source/main/camera.h"
#include "Render Engine/demo renderer/demobatchrenderer.h"
#include "World/day night cycle/daynightcycle.h"
#include "Render Engine/lenseFlare/LenseFlare.h"
#include "Resource Management/resource management/particleatlascache.h"
#include "Render Engine/particles/ParticleSystem.h"
#include "Render Engine/particle spawns/circlespawn.h"
#include "Render Engine/particle spawns/pointspawn.h"
#include "Render Engine/particles/particleMaster.h"
#include "Render Engine/demo renderer/PostProcessSelection.h"
#include "Source/entity/models.h"





#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720





int main() {
	
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	DisplayManager::createDisplay();

	ParticleAtlasCache::loadALL();

	DayNightCycle dn;
	dn.addSun();
	dn.update();
	

	Camera camera(DisplayManager::window);

	LenseFlare lense = LenseFlare(mat4::perspective(45.0f, DisplayManager::getAspectRatio(), 0.1f, 300.0f), camera.CreateViewMatrix());

	//例子发射器
	PointSpawn * pSpwan = new PointSpawn();
	CircleSpawn * pCSpwan = new CircleSpawn(vec3(0, 0, 1), 3);
	ParticleSystem tpEmiter = ParticleSystem(ParticleAtlasCache::getAtlas(1), pCSpwan, 2000, 1, 0, 10000, 0.2);
	ParticleSystem cpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), false, pCSpwan, 2000, 0.5, 0, 100, 0.2);
	ParticleSystem acpEmiter = ParticleSystem(Color(0.8, 0.0, 0.0), true, pCSpwan, 2000, 0.5, 0, 100, 0.2);
	tpEmiter.generateParticles(vec3(-0.5, -0.5, 0), 0.2);
	cpEmiter.generateParticles(vec3(0.5, 0.5, 0), 0.5);
	acpEmiter.generateParticles(vec3(-0.5, 0.5, 0), 0.5);
	ParticleMaster::init(camera.CreateViewMatrix());

	PostProcessSelection ps;


	while (!DisplayManager::closedDisplay()) {
		
	
		dn.update();
		EnvironmentVariables::update();

		
		camera.move();

		ps.setChoice();
		ps.bind();
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		
		DisplayManager::clearDisplay();
		//渲染光晕
		lense.render(EnvironmentVariables::getLightDirection(), true);
		//渲染粒子
		ParticleMaster::renderParticles(camera);

			
		ps.unbind();
		ps.render();
		//更新粒子
		ParticleMaster::update(camera);


		DisplayManager::updateDisplay();
	}

	return 0;
}




