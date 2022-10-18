#include "MyMesh.h"
void MyMesh::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = a_fSize * 0.5f;
	//3--2
	//|  |
	//0--1

	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	// initializing variables
	// 
	//centers the object at 0,0,0
	vector3 bottom(0, 0, -a_fHeight/2);
	vector3 top(0, 0, a_fHeight/2);

	std::vector<vector3 > edgePoints;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));
	//generates a circle of points and stores them in a list
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, bottom.z);
		theta += delta;
		edgePoints.push_back(temp);
	}
	//connects all the points of the cone with tris
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		AddTri(bottom, edgePoints[(i + 1) % a_nSubdivisions], edgePoints[i]);
		AddTri(top, edgePoints[i], edgePoints[(i + 1) % a_nSubdivisions]);
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//initializing variables
	vector3 topCircleCenter(0, 0, a_fHeight/2);
	vector3 bottomCircleCenter(0, 0, -a_fHeight/2);

	std::vector<vector3 > bottomEdgePoints;
	std::vector<vector3> topEdgePoints;
	GLfloat theta = 0;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	//calcuates the position of two circles
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp = vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, bottomCircleCenter.z);
		bottomEdgePoints.push_back(temp);


		temp = vector3(cos(theta) * a_fRadius, sin(theta) * a_fRadius, topCircleCenter.z);
		topEdgePoints.push_back(temp);

		theta += delta;
		

		

	}

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//conects the points of each circle to their centers
		AddTri(bottomCircleCenter, bottomEdgePoints[(i + 1) % a_nSubdivisions], bottomEdgePoints[i]);
		AddTri(topCircleCenter, topEdgePoints[i],topEdgePoints[(i + 1) % a_nSubdivisions]);

		//connects the edges of each circle with quads in order to complete the cylinder
		AddQuad(bottomEdgePoints[i], bottomEdgePoints[(i + 1) % a_nSubdivisions],  topEdgePoints[i], topEdgePoints[(i + 1) % a_nSubdivisions]);
		
	}
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_fHeight < 0.01f)
		a_fHeight = 0.01f;

	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	// Replace this with your code
	//initializing variables
	std::vector<vector3> bottomInnerRing;
	std::vector<vector3> bottomOuterRing;
	std::vector<vector3> topInnerRing;
	std::vector<vector3> topOuterRing;

	float theta = 0.0f;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));

	//generates all points and stores them in several vectors
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//generates the location of each point in all four rings
		vector3 innerPoint = vector3(cos(theta) * a_fInnerRadius, sin(theta) * a_fInnerRadius, -a_fHeight/2);
		bottomInnerRing.push_back(innerPoint);

		vector3 outerPoint = vector3(cos(theta) * a_fOuterRadius, sin(theta) * a_fOuterRadius, -a_fHeight / 2);
		bottomOuterRing.push_back(outerPoint);

		innerPoint = vector3(cos(theta) * a_fInnerRadius, sin(theta) * a_fInnerRadius, a_fHeight/2);
		topInnerRing.push_back(innerPoint);

		outerPoint = vector3(cos(theta) * a_fOuterRadius, sin(theta) * a_fOuterRadius, a_fHeight/2);
		topOuterRing.push_back(outerPoint);

		theta += delta;
	}

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//creates the bottom ring
		AddQuad(bottomInnerRing[i], bottomInnerRing[(i + 1) % a_nSubdivisions], bottomOuterRing[i],  bottomOuterRing[(i + 1) % a_nSubdivisions] );

		//creates the top ring
		AddQuad(topOuterRing[i], topOuterRing[(i + 1) % a_nSubdivisions], topInnerRing[i], topInnerRing[(i + 1) % a_nSubdivisions]);

		//connects the two inner rings
		AddQuad(topInnerRing[i], topInnerRing[(i + 1) % a_nSubdivisions], bottomInnerRing[i], bottomInnerRing[(i + 1) % a_nSubdivisions]);

		//connects the two outer rings
		AddQuad(bottomOuterRing[i], bottomOuterRing[(i + 1) % a_nSubdivisions], topOuterRing[i], topOuterRing[(i + 1) % a_nSubdivisions]);
		
	}

	
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius < 0.01f)
		a_fOuterRadius = 0.01f;

	if (a_fInnerRadius < 0.005f)
		a_fInnerRadius = 0.005f;

	if (a_fInnerRadius > a_fOuterRadius)
		std::swap(a_fInnerRadius, a_fOuterRadius);

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 360)
		a_nSubdivisionsA = 360;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 360)
		a_nSubdivisionsB = 360;

	Release();
	Init();

	//initializing variables
	float verticalTheta = 0.0f;
	float horizontalTheta = 0.0f;
	GLfloat verticalDelta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisionsA));
	GLfloat horizontalDelta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisionsB));

	/*
	//another method I tried that also doesn't work but this one doesn't work even more
	std::vector<vector3>firstRing;


	std::vector<std::vector<vector3>> rings;
	
	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		firstRing.push_back(vector3(cos(horizontalTheta) * a_fOuterRadius / 2, sin(horizontalTheta) * a_fOuterRadius, a_fInnerRadius + a_fOuterRadius));
		horizontalTheta += horizontalDelta;
	}

	for (int i = 0; i < a_nSubdivisionsA - 1; i++) 
	{
		std::vector<vector3> tempRing;
		for (int j = 0; j < a_nSubdivisionsB; j++) 
		{
			vector4 temp = vector4(firstRing[i].x, firstRing[i].y, firstRing[i].z, 1.0f);
			temp *= ToMatrix4(glm::rotate(IDENTITY_M4, verticalTheta, vector3(0.0f, 0.0f, 1.0f)));
			vector3 cast = vector3(temp.x, temp.y, temp.z);
			tempRing.push_back(cast);
		}
		rings.push_back(tempRing);
		verticalTheta += verticalDelta;
		
	}

	for (int i = 0; i < a_nSubdivisionsB; i++)
	{
		AddTri(vector3(0.0, 0.0, a_fInnerRadius + a_fOuterRadius), firstRing[i], firstRing[(i + 1) % a_nSubdivisionsB]);

	}

	for (int i = 0; i < a_nSubdivisionsA; i++) {
		for (int j = 0; j < a_nSubdivisionsB; j++) {
			AddTri(vector3(0.0, 0.0, a_fInnerRadius + a_fOuterRadius), rings[i][j], rings[i][(j + 1) % a_nSubdivisionsB]);
		}
	}
	
	horizontalTheta = 0.0f;
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		if (i == 0) {
			rings.push_back(firstRing);
		}
		else {
			std::vector<vector3> tempRing;
			for (int j = 0; j < a_nSubdivisionsB; j++) {
				
				matrix4 rotationMatrix = glm::rotate(IDENTITY_M4, horizontalTheta, vector3(0.0f, 0.0f, 1.0f));
				vector4 newPoint = vector4(firstRing[j].x, firstRing[j].y, firstRing[j].z, 1.0f) * rotationMatrix;

				tempRing.push_back(static_cast<vector3>(newPoint));

				horizontalTheta += horizontalDelta;
			}

			rings.push_back(tempRing);
		}
		
		
	}

	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
			AddQuad(rings[i][j], rings[i][(j + 1) % a_nSubdivisionsB], rings[(i + 1) % a_nSubdivisionsB][j], rings[(i + 1) % a_nSubdivisionsB][(j + 1) % a_nSubdivisionsB]);
		}
	}
	*/
	
	
	
	
	
	std::vector<std::vector<vector3>> rings;
	std::vector<vector3> ringCenters;
	
	//initializes vector
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		rings.push_back (std::vector<vector3>());
	}

	//creates a point at the center of each ring around the torus
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		vector3 ringCenter = vector3(cos(verticalTheta) * (a_fOuterRadius - a_fInnerRadius), sin(verticalTheta) * (a_fOuterRadius - a_fInnerRadius), 0.0f);

		verticalTheta += verticalDelta;
		ringCenters.push_back(ringCenter);
	}

	//verticalTheta = 0.0f;

	//generates the points around each circle center
	for (int i = 0; i < a_nSubdivisionsA; i++) 
	{
		
			
		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
			float xPos = ringCenters[i].x + cos(horizontalTheta) * (a_fOuterRadius - a_fInnerRadius);
			float yPos = (ringCenters[i].y + (sin(horizontalTheta) * a_fOuterRadius));
			float zPos = ringCenters[i].z + cos(horizontalTheta) * (a_fOuterRadius - a_fInnerRadius);
		

			rings[i].push_back(vector3(xPos, yPos, zPos));

			//rotates around the circle
			horizontalTheta += horizontalDelta;

		}
			horizontalTheta = 0.0f;
			

	}
	
	//connects each adjecent ring with quads
	for (int i = 0; i < a_nSubdivisionsA; i++)
	{
		for (int j = 0; j < a_nSubdivisionsB; j++)
		{
				AddQuad(rings[i][(j + 1) % a_nSubdivisionsB], rings[i][j], rings[(i + 1) % a_nSubdivisionsA][(j + 1) % a_nSubdivisionsB], rings[(i + 1) % a_nSubdivisionsA][j]);
			
		}

	}
	
	
	// -------------------------------

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_fRadius < 0.01f)
		a_fRadius = 0.01f;

	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2.0f, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	vector3 top = vector3(0.0f, 0.0f, a_fRadius/2);
	vector3 bottom = vector3(0.0f, 0.0f, -a_fRadius/2 );

	//radius of the starting ring
	float currentRadius = a_fRadius / 2;
	float radiusDelta = a_fRadius / a_nSubdivisions;
	
	//variables to sepates each ring along the sphere on the z axis
	float heightDelta = (top.z - bottom.z)/(a_nSubdivisions + 1);
	float currentHeight = a_fRadius/2;

	//list to store each position
	std::vector<std::vector<vector3>> rings;
	
	float theta = 0.0f;
	GLfloat delta = static_cast<GLfloat>(2.0 * PI / static_cast<GLfloat>(a_nSubdivisions));
	//initializes vector
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		rings.push_back(std::vector<vector3>());
	}
	

	for (float i = 0; i < a_nSubdivisions; i++) 
	{
		//moves the height of the new ring being created down from the bottom to the top
		currentHeight -= heightDelta;
		for (int j = 0; j < a_nSubdivisions; j++) 
		{
			//generates a new point
			rings[i].push_back(vector3(glm::cos(theta) * currentRadius, glm::sin(theta) * currentRadius, currentHeight));
			
			theta += delta;
		}
		theta = 0;

		//rings get wider towards the center of the sphere
		if (i < a_nSubdivisions / 2) {
			currentRadius += radiusDelta;
		}
		else {
			currentRadius -= radiusDelta; 
		}
		
	}
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		//creates tris between the top and bottom points and closest rings
		AddTri(top, rings[0][i], rings[0][(i + 1) % a_nSubdivisions]);
		AddTri(bottom, rings[rings.size() - 1][(i + 1) % a_nSubdivisions], rings[rings.size() - 1][i]);
	}

	//connects each ring with quads
	for (int i = 0; i < a_nSubdivisions - 1; i++) 
	{
		for (int j = 0; j < a_nSubdivisions; j++) {
			
			
			AddQuad( rings[(i + 1) % a_nSubdivisions][j], rings[(i + 1) % a_nSubdivisions][(j + 1) % a_nSubdivisions], rings[i][j], rings[i][(j + 1) % a_nSubdivisions]);
			
		}
		
	}


	
	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}
void MyMesh::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	//C
	//| \
	//A--B
	//This will make the triangle A->B->C 
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyMesh::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	//C--D
	//|  |
	//A--B
	//This will make the triangle A->B->C and then the triangle C->B->D
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_uVertexCount = 0;

	m_VAO = 0;
	m_VBO = 0;

	m_pShaderMngr = ShaderManager::GetInstance();
}
void MyMesh::Release(void)
{
	m_pShaderMngr = nullptr;

	if (m_VBO > 0)
		glDeleteBuffers(1, &m_VBO);

	if (m_VAO > 0)
		glDeleteVertexArrays(1, &m_VAO);

	m_lVertex.clear();
	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
MyMesh::MyMesh()
{
	Init();
}
MyMesh::~MyMesh() { Release(); }
MyMesh::MyMesh(MyMesh& other)
{
	m_bBinded = other.m_bBinded;

	m_pShaderMngr = other.m_pShaderMngr;

	m_uVertexCount = other.m_uVertexCount;

	m_VAO = other.m_VAO;
	m_VBO = other.m_VBO;
}
MyMesh& MyMesh::operator=(MyMesh& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_uVertexCount, other.m_uVertexCount);

	std::swap(m_VAO, other.m_VAO);
	std::swap(m_VBO, other.m_VBO);

	std::swap(m_lVertex, other.m_lVertex);
	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);

	std::swap(m_pShaderMngr, other.m_pShaderMngr);
}
void MyMesh::CompleteMesh(vector3 a_v3Color)
{
	uint uColorCount = m_lVertexCol.size();
	for (uint i = uColorCount; i < m_uVertexCount; ++i)
	{
		m_lVertexCol.push_back(a_v3Color);
	}
}
void MyMesh::AddVertexPosition(vector3 a_v3Input)
{
	m_lVertexPos.push_back(a_v3Input);
	m_uVertexCount = m_lVertexPos.size();
}
void MyMesh::AddVertexColor(vector3 a_v3Input)
{
	m_lVertexCol.push_back(a_v3Input);
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_uVertexCount == 0)
		return;

	CompleteMesh();

	for (uint i = 0; i < m_uVertexCount; i++)
	{
		//Position
		m_lVertex.push_back(m_lVertexPos[i]);
		//Color
		m_lVertex.push_back(m_lVertexCol[i]);
	}
	glGenVertexArrays(1, &m_VAO);//Generate vertex array object
	glGenBuffers(1, &m_VBO);//Generate Vertex Buffered Object

	glBindVertexArray(m_VAO);//Bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);//Bind the VBO
	glBufferData(GL_ARRAY_BUFFER, m_uVertexCount * 2 * sizeof(vector3), &m_lVertex[0], GL_STATIC_DRAW);//Generate space for the VBO

	// Position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)0);

	// Color attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(vector3), (GLvoid*)(1 * sizeof(vector3)));

	m_bBinded = true;

	glBindVertexArray(0); // Unbind VAO
}
void MyMesh::Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mModel)
{
	// Use the buffer and shader
	GLuint nShader = m_pShaderMngr->GetShaderID("Basic");
	glUseProgram(nShader); 

	//Bind the VAO of this object
	glBindVertexArray(m_VAO);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(nShader, "MVP");
	GLuint wire = glGetUniformLocation(nShader, "wire");

	//Final Projection of the Camera
	matrix4 m4MVP = a_mProjection * a_mView * a_mModel;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4MVP));
	
	//Solid
	glUniform3f(wire, -1.0f, -1.0f, -1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);  

	//Wire
	glUniform3f(wire, 1.0f, 0.0f, 1.0f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_POLYGON_OFFSET_LINE);
	glPolygonOffset(-1.f, -1.f);
	glDrawArrays(GL_TRIANGLES, 0, m_uVertexCount);
	glDisable(GL_POLYGON_OFFSET_LINE);

	glBindVertexArray(0);// Unbind VAO so it does not get in the way of other objects
}
void MyMesh::GenerateCuboid(vector3 a_v3Dimensions, vector3 a_v3Color)
{
	Release();
	Init();

	vector3 v3Value = a_v3Dimensions * 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-v3Value.x, -v3Value.y, v3Value.z); //0
	vector3 point1(v3Value.x, -v3Value.y, v3Value.z); //1
	vector3 point2(v3Value.x, v3Value.y, v3Value.z); //2
	vector3 point3(-v3Value.x, v3Value.y, v3Value.z); //3

	vector3 point4(-v3Value.x, -v3Value.y, -v3Value.z); //4
	vector3 point5(v3Value.x, -v3Value.y, -v3Value.z); //5
	vector3 point6(v3Value.x, v3Value.y, -v3Value.z); //6
	vector3 point7(-v3Value.x, v3Value.y, -v3Value.z); //7

	//F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	// Adding information about color
	CompleteMesh(a_v3Color);
	CompileOpenGL3X();
}