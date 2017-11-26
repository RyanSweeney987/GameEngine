#pragma once

#include "./src/Graphics/Window.h"
#include "./src/Graphics/Renderer.h"
#include "./src/Graphics/Uniform.h"
#include "./src/Graphics/Shader.h"
#include "./src/Graphics/VertexData.h"
#include "./src/Graphics/Model.h"
#include "./src/Graphics/Texture.h"
#include "./src/Graphics/Mesh.h"

#include "./src/Entity/Components/Component.h"
#include "./src/Entity/Components/MovementComponent.h"
#include "./src/Entity/Components/FlyingComponent.h"

#include "./src/Entity/BaseObject.h"
#include "./src/Entity/Camera.h"

#include "./src/Utils/AssetPool.h"
#include "./src/Utils/Time.h"

#include "./src/Input/InputManager.h"

#include "./src/Math/Maths.h"
#include "./src/Math/vec2.h"
#include "./src/Math/vec3.h"
#include "./src/Math/vec4.h"
#include "./src/Math/mat2.h"
#include "./src/Math/mat3.h"
#include "./src/Math/mat4.h"

#include "./src/Math/Physics/Physics.h"

#include <iostream>
#include <fstream>

#include <bullet\btBulletCollisionCommon.h>

using namespace AirEngine;
using namespace Entity;
using namespace Graphics;
using namespace Input;
using namespace Utils;
using namespace Math::Physics;

// Function prototypes
void run();
Math::vec3 outOfBounds(const Math::vec3& currentPosition);

// Window dimensions
const int WIDTH = 1920, HEIGHT = 1080;
const float CAMERA_DIS = 50.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// Gameplay bounds
float frustrumHeight = 2.0f * 20.0f * Math::tan(45.0f * 0.5f * 1.0f);
float frustrumWidth = frustrumHeight * 1.77777777778f;
/************************
*	How to get bounds	*
*************************
	var frustumHeight = 2.0f * distance * Mathf.Tan(camera.fieldOfView * 0.5f * Mathf.Deg2Rad);
	var frustumWidth = frustumHeight * camera.aspect;
	var frustumHeight = frustumWidth / camera.aspect;
************************/

// Core components
Window window(WIDTH, HEIGHT, "AirEngine");
InputManager manager(window);
Shader shader("src/Graphics/Shaders/Vertex.glsl", "src/Graphics/Shaders/Fragment.glsl");
Renderer renderer(shader);
Time timer;
// Player components
Components::FlyingComponent flyingComp;

int main() {
	run();

	return 0;
}

void run() {
	window.setVSyncEnabled(true);
	renderer.getCamera().setPosition(Math::vec3(0.0f, 0.0f, CAMERA_DIS));

	manager.addInputFunction([]() {
		using namespace Input::KeyCodes;

		if(manager.isKeyPressed(KEY_ESC)) {
			window.closeWindow();
		}

		float rotationSpeed = 5.0f * timer.getDeltaTime();
		float thrustAmount = 1.0f * timer.getDeltaTime();
		// Rotation
		if(manager.isKeyPressed(KEY_A)) {
			flyingComp.addRotation(rotationSpeed);
		} else if(manager.isKeyPressed(KEY_D)) {
			flyingComp.addRotation(-rotationSpeed);
		} 
		// Thrust
		if(manager.isKeyPressed(KEY_W)) {
			flyingComp.setThrust(thrustAmount);
		} else if(manager.isKeyPressed(KEY_S)) {
			flyingComp.setThrust(-thrustAmount);
		} else {
			flyingComp.setThrust(0.0f);
		}
	});

	AssetPool pools;

	std::vector<std::weak_ptr<BaseObject>> objectsToRender;

	pools.createMesh("Default", "./Resource/Models/Default.fbx");

	pools.createMesh("ShipMesh", "./Resources/Models/Ship.fbx");
	pools.createTexture("Default", "./Resources/Textures/Default.png");
	pools.createTexture("ShipAlbedo", "./Resources/Textures/Ship_Identifier.png");
	pools.createMaterial("ShipMat", "ShipAlbedo", "Default");
	pools.createModel("ShipModel", "ShipMesh", "ShipMat");

	pools.createMesh("AsteroidMesh", "./Resources/Models/Asteroid.fbx");
	pools.createTexture("AsteroidAlbedo", "./Resources/Textures/Asteroid_Albedo.png");
	pools.createMaterial("AsteroidMat", "AsteroidAlbedo", "Default");
	pools.createModel("AsteroidModel", "AsteroidMesh", "AsteroidMat");
	
	pools.createBaseObject("Ship", "ShipModel");
	pools.createBaseObject("Asteroid", "AsteroidModel");

	objectsToRender.push_back(pools.getBaseObject("Ship"));
	
	flyingComp.setRotation(Math::toRadians(90.0f));
	// Add flying component to ship
	if(auto ship = objectsToRender.at(0).lock()) {
		ship.get()->addComponent(&flyingComp);
	}

	objectsToRender.push_back(pools.getBaseObject("Asteroid"));
	Components::MovementComponent asterMove;
	// Add movement component to asteroid
	if(auto asteroid = objectsToRender.at(1).lock()) {
		//asterMove.setVelocity(Math::vec3(0.0f, 0.1f, 0.0f));
		asteroid.get()->addComponent(&asterMove);
	}
	
	// Game loop
	/*while(!window.isWindowClosed()) {
		manager.pollEvents();
		time.update();
		
		flyingComp.setPosition(outOfBounds(flyingComp.getPosition()));
		asterMove.setPosition(outOfBounds(asterMove.getPosition()));

		for(auto elem : objectsToRender) {
			elem.lock().get()->update();
		}

		renderer.update(window, objectsToRender);
	}*/

	double time = 0.0;
	double deltaTime = 0.01;

	double currentTime = glfwGetTime();
	double accumulator = 0.0;

	State current;
	current.pos = 0;
	current.vel = 0;
	State previous = current;	

	Physics physics;

	while(!window.isWindowClosed()) {
		const double newTime = glfwGetTime();
		double frameTime = newTime - currentTime;
		currentTime = newTime;

		if(frameTime > 0.25)
			frameTime = 0.25;
		
		accumulator += frameTime;

		while(accumulator >= deltaTime) {
			accumulator -= deltaTime;
			previous = current;
			physics.integrate(current, time, deltaTime);
			time += deltaTime;
		}
		
		State state = physics.interpolate(previous, current, accumulator / deltaTime);
		
		manager.pollEvents();
		timer.update();

		flyingComp.setPosition(outOfBounds(flyingComp.getPosition()));
		asterMove.setPosition(outOfBounds(asterMove.getPosition()));

		for(auto elem : objectsToRender) {
			elem.lock().get()->update();
		}

		renderer.update(window, objectsToRender);
	}


	///-----includes_end-----

	int i;
	///-----initialization_start-----

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();

	btDiscreteDynamicsWorld* dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));

	///-----initialization_end-----

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	btAlignedObjectArray<btCollisionShape*> collisionShapes;


	///create a few basic rigid bodies

	//the ground is a cube of side 100 at position y = -56.
	//the sphere will hit it at y = -6, with center at -5
	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));

		collisionShapes.push_back(groundShape);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -56, 0));

		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if(isDynamic)
			groundShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}

	{
		//create a dynamic rigidbody

		//btCollisionShape* colShape = new btBoxShape(btVector3(1,1,1));
		btCollisionShape* colShape = new btSphereShape(btScalar(1.));
		collisionShapes.push_back(colShape);

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar	mass(1.f);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0, 0, 0);
		if(isDynamic)
			colShape->calculateLocalInertia(mass, localInertia);

		startTransform.setOrigin(btVector3(2, 10, 0));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody(body);
	}

	/// Do some simulation

	///-----stepsimulation_start-----
	for(i = 0; i<150; i++) {
		dynamicsWorld->stepSimulation(1.f / 60.f, 10);

		//print positions of all objects
		for(int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--) {
			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			btTransform trans;
			if(body && body->getMotionState()) {
				body->getMotionState()->getWorldTransform(trans);

			} else {
				trans = obj->getWorldTransform();
			}
			printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
		}
	}
	///-----stepsimulation_end-----

	//cleanup in the reverse order of creation/initialization

	///-----cleanup_start-----

	//remove the rigidbodies from the dynamics world and delete them
	for(i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);

		if(body && body->getMotionState()) {
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for(int j = 0; j<collisionShapes.size(); j++) {
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	//next line is optional: it will be cleared by the destructor when the array goes out of scope
	collisionShapes.clear();

	window.terminate();
}

Math::vec3 outOfBounds(const Math::vec3& currentPosition) {
	Math::vec3 newPosition = currentPosition;
	// Set current position to opposite bounds so object stays on screen
	if(newPosition.x < -frustrumWidth) newPosition.x = frustrumWidth;
	if(newPosition.x > frustrumWidth) newPosition.x = -frustrumWidth;
	if(newPosition.y < -frustrumHeight) newPosition.y = frustrumHeight;
	if(newPosition.y > frustrumHeight) newPosition.y = -frustrumHeight;

	return newPosition;
}