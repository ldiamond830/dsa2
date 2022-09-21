#include "AppClass.h"
void Application::InitVariables(void)
{
	////Change this to your name and email
	m_sProgrammer = "Alberto Bobadilla - labigm@rit.edu";
	vector3 v3Position(0.0f, 0.0f, 10.0f);
	vector3 v3Target = ZERO_V3;
	vector3 v3Upward = AXIS_Y;
	m_pCameraMngr->SetPositionTargetAndUpward(v3Position, v3Target, v3Upward);

	//Make MyMesh object
	m_pMesh = new MyMesh();

	int vertexCount = 15;
	float degreeSeparation = 360 / vertexCount;
	float separationInterval = 0;
	vector3 center(0.0f, 0.0f, 0.0f);
	vector3 prevPoint(0.5f, 0.5f, 0.0f);
	vector3 newPoint;
	/*
	for (int i = 0; i < vertexCount; i++) {
		float rad = glm::radians(separationInterval);
		float xPos = glm::cos(rad);
		float yPos = glm::sin(rad);

		m_pMesh->AddVertexPosition(vector3(xPos, yPos, 0.0f));

		separationInterval += degreeSeparation;
	}
	*/
	
	for (int i = 0; i < vertexCount++; i++)
	{
		float rad = glm::radians(separationInterval);
		float xPos = glm::cos(rad);
		float yPos = glm::sin(rad);
		newPoint = vector3(xPos, yPos, 0.0f);

		
			m_pMesh->AddTri(center, prevPoint, newPoint);
				

		prevPoint = newPoint;


		
		separationInterval += degreeSeparation;
	}
	
	

	m_pMesh->CompileOpenGL3X();

	//Generate a circle
	//m_pMesh->GenerateCircle(2.0f, 5, C_RED);
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

	//Render the mesh
	m_pMesh->Render(m_pCameraMngr->GetProjectionMatrix(), m_pCameraMngr->GetViewMatrix(), ToMatrix4(m_qArcBall));

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
	//Safely release the memory
	SafeDelete(m_pMesh);
	//release GUI
	ShutdownGUI();
}