#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Allocate the memory for the Meshes
	m_pMesh = new MyMesh();
	m_pMesh->GenerateCube(1.0f, C_BLACK);
		
}
void Application::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->Update();

	//Is the arcball active?
	ArcBall();

	//Is the first person camera active?
	CameraRotation();

	//Update Entity Manager
	m_pEntityMngr->Update();

	//Add objects to render list
	m_pEntityMngr->AddEntityToRenderList(-1, true);
}
void Application::Display(void)
{
	// Clear the screen
	ClearScreen();

	//Calculate the model, view and projection matrix
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	//static variable is only created once
	static float delta = 0;

	//moves the object to the right and up and down based on a sin curve
	matrix4 m4Movement = glm::translate(IDENTITY_M4, vector3(0,0, delta));
	//increments the value
	delta += 0.1;



	/*
	//puts the object in the center of the screen
	matrix4 parentSpace = glm::translate(m4Movement, vector3(0, 0, 0));
	matrix4 m4Translate = glm::translate(parentSpace, vector3(1, 0, 0));
	*/

	//rendering 4 cubes in a connected shape
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Movement, vector3(0, 0, 0)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Movement, vector3(1.0, 0, 0)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Movement, vector3(1.0, 1.0, 0)));
	m_pMesh->Render(m4Projection, m4View, glm::translate(m4Movement, vector3(2.0, 1.0, 0)));

	// draw a skybox
	m_pModelMngr->AddSkyboxToRenderList();

	//render list call
	m_uRenderCallCount = m_pModelMngr->Render();

	//clear the render list
	m_pModelMngr->ClearRenderList();

	//draw gui
	DrawGUI();
	
	//end the current frame (internally swaps the front and back buffers)
	m_pWindow->display();
}
void Application::Release(void)
{
	//Release meshes
	SafeDelete(m_pMesh);

	//release GUI
	ShutdownGUI();
}