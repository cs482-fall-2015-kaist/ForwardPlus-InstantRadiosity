#include "SystemContext.h"
#include <sstream>
#include <iostream>
#include "Mesh.h"
#include "DeviceMesh.h"

std::unique_ptr<SystemContext> SystemContext::gContext = nullptr;

void SystemContext::loadObj(char *path)
{
	std::string header, data, err;
	std::istringstream liness(path);
	getline(liness, header, '='); getline(liness, data, '=');
	if (strcmp(header.c_str(), "mesh") == 0)
	{
		int found = data.find_last_of("/\\");
		std::string path = data.substr(0, found + 1);
		std::cout << "Loading: " << data << std::endl;
		err = tinyobj::LoadObj(shapes, data.c_str(), path.c_str());
	}
	if (!err.empty())
		throw std::runtime_error(err.c_str());
}

void SystemContext::initMesh()
{
	for (const auto &shape : shapes)
	{
		Mesh mesh = Mesh::meshFromShape(shape);
		drawMeshes.push_back(DeviceMesh::deviceMeshFromMesh(mesh));
		irKernel->addMesh(mesh);
		if (shape.material.name == "light")
		{
			// process light
			light.lightMax = mesh.getAABBmax();
			light.lightMin = mesh.getAABBmin();
			light.direction = glm::vec3(0, -1, 0);
			light.intensity = glm::vec3(1, 1, 1);
		}
	}
	irKernel->commitScene();
	auto vpls = irKernel->getVPLpos(light, 1);
}

