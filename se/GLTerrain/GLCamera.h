#ifndef _GLCamera_GLCamera_h
#define _GLCamera_GLCamera_h

#include <CtrlLib/CtrlLib.h>
#include <GLCtrl/GLCtrl.h>
#include <GLDraw/GLDraw.h>

#include <plugin/glm/glm.hpp>
#include <plugin/glm/gtc/matrix_transform.hpp>
#include <plugin/glm/gtc/type_ptr.hpp>

using namespace Upp;

#define IMAGECLASS DataImg
#define IMAGEFILE <GLCamera/data.iml>
#include <Draw/iml_header.h>


struct GLTerrain {
	glm::vec3 cameraPos   = glm::vec3(0.0f, 30.0f, 30.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
	
	bool firstMouse = true;
	float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch =  0.0f;
	float lastX =  800.0f / 2.0;
	float lastY =  600.0 / 2.0;
	float fov   =  45.0f;

	GLVertexData verts;
	GLTexture texture;
	
	void InitScene();
	void PaintScene(Size sz);

	void mouse_move(double xpos, double ypos);
	void mouse_scroll(double xoffset, double yoffset);
	
	void SetTerrain(float unit, Size dim, const Vector<Vector<float>>& elevation, const Image& image);

	void Test();
};

class GLCamera : public TopWindow {
public:
	virtual void MouseWheel(Point p, int zdelta, dword keyflags);
	virtual void MouseMove(Point p, dword keyflags);

	GLTerrain terrain;

	GLCtrl view;

	GLCamera();
};

#endif
