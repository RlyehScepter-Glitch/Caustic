#include "Scene.h"

#include <fstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace Caustic
{

	Scene::Scene(const std::string& sceneFileName)
	{
		ParseSceneFile(sceneFileName);
	}

	void Scene::ParseSceneFile(const std::string& sceneFileName)
	{
		rapidjson::Document doc = GetJsonDocument(sceneFileName);

		//Parse Settings values
		const rapidjson::Value& settingsValue = doc.FindMember("settings")->value;
		if(!settingsValue.IsNull() && settingsValue.IsObject())
		{
			//Parse Color value
			const rapidjson::Value& colorValue = settingsValue.FindMember("background_color")->value;

			//Parse image Width and Height values
			const rapidjson::Value& imageSettignsValue = settingsValue.FindMember("image_settings")->value;
			const rapidjson::Value& widthValue = imageSettignsValue.FindMember("width")->value;
			const rapidjson::Value& heightValue = imageSettignsValue.FindMember("height")->value;

			//Set values inside Settings
			m_Settings.SetBackgroundColor(LoadVector(colorValue.GetArray()));
			m_Settings.SetWidth(widthValue.GetFloat());
			m_Settings.SetHeight(heightValue.GetFloat());

		}

		//Parse Camera values
		const rapidjson::Value& cameraValue = doc.FindMember("camera")->value;
		if (!cameraValue.IsNull() && cameraValue.IsObject())
		{
			//Parse Matrix value
			const rapidjson::Value& matrixValue = doc.FindMember("matrix")->value;

			//Parse Position value
			const rapidjson::Value& posValue = doc.FindMember("position")->value;

			//Set values inside Camera
			m_Camera.SetViewMatrix(LoadMatrix(matrixValue.GetArray()));
			m_Camera.SetPosition(LoadVector(posValue.GetArray()));
		}

		//Parse Object values
		const rapidjson::Value& objectsValue = doc.FindMember("objects")->value;
		auto objectValueArray = objectsValue.GetArray();
		for (size_t obj = 0; obj < objectValueArray.Size(); obj++)
		{
			//Parse Veritces
			const rapidjson::Value& verticesValue = doc.FindMember("vertices")->value;
			auto vertexValuesArray = verticesValue.GetArray();
			std::vector<glm::vec3> vertices;
			for (size_t i = 0; i < vertexValuesArray.Size(); i += 3)
			{
				glm::vec3 vertex(vertexValuesArray[i].GetFloat(), vertexValuesArray[i + 1].GetFloat(), vertexValuesArray[i + 2].GetFloat());
				vertices.push_back(vertex);
			}

			//Parse Triangle Indices
			const rapidjson::Value& indicesValue = doc.FindMember("triangles")->value;
			auto indices = indicesValue.GetArray();

			//Set Mesh Values
			Mesh mesh;
			
			for(int i = 0; i < indices.Size(); i += 3)
			{
				//VI - Vertex Index
				int VI1 = indices[i].GetInt();
				int VI2 = indices[i+1].GetInt();
				int VI3 = indices[i+2].GetInt();

				//Create Triangle
				Triangle triangle(vertices[VI1], vertices[VI2], vertices[VI3]);
				
				//Push Triangle to the Mesh
				mesh.PushTriangle(triangle);
			}

			//Push Mesh into the Scene
			m_Objects.push_back(mesh);
		}
	}

	rapidjson::Document GetJsonDocument(const std::string& sceneFileName)
	{
		std::ifstream stream(sceneFileName);
		assert(stream.is_open());

		rapidjson::IStreamWrapper wrapper(stream);
		rapidjson::Document doc;
		doc.ParseStream(wrapper);

		if(doc.HasParseError())
		{
			std::cout << "Error: " << doc.GetParseError() << '\n';
			std::cout << "Offset: " << doc.GetErrorOffset() << '\n';
			assert(false);
		}

		assert(doc.IsObject());
		return doc;
	}

	glm::vec3 LoadVector(const rapidjson::Value::ConstArray& arr)
	{
		assert(arr.Size() == 3);
		glm::vec3 vec{
			static_cast<float>(arr[0].GetDouble()),
			static_cast<float>(arr[1].GetDouble()),
			static_cast<float>(arr[2].GetDouble())
		};

		return vec;
	}

	glm::mat3 LoadMatrix(const rapidjson::Value::ConstArray& arr)
	{
		assert(arr.Size() == 9);
		glm::mat3 mat{
			static_cast<float>(arr[0].GetDouble()),
			static_cast<float>(arr[1].GetDouble()),
			static_cast<float>(arr[2].GetDouble()),
			static_cast<float>(arr[3].GetDouble()),
			static_cast<float>(arr[4].GetDouble()),
			static_cast<float>(arr[5].GetDouble()),
			static_cast<float>(arr[6].GetDouble()),
			static_cast<float>(arr[7].GetDouble()),
			static_cast<float>(arr[8].GetDouble())
		};

		return mat;
	}
}