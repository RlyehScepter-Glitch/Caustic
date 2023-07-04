#include "Scene.h"

#include <fstream>
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>
#include <stack>

namespace Caustic
{
	rapidjson::Document GetJsonDocument(const std::string& sceneFileName);
	glm::vec3 LoadVector(const rapidjson::Value::ConstArray& arr);
	glm::mat3 LoadMatrix(const rapidjson::Value::ConstArray& arr);

	Scene::Scene(const std::string& sceneFileName)
	{
		ParseSceneFile(sceneFileName);
	}

	IntersectionData Scene::TraceRay(const Ray& ray, float nearest) const
	{
		IntersectionData data;

		bool intersected = false;
		uint32_t meshIndex = 0;
		uint32_t triIndex = 0;
		float materialIOR = 1.0f;
		float tNear = nearest;
		float uNear = FLT_MAX;
		float vNear = FLT_MAX;
		float t = 0.0f;
		float u = 0.0f;
		float v = 0.0f;

		for(uint32_t m = 0; m < m_Objects.size(); m++)
		{
			const Mesh& mesh = m_Objects[m];
			
			for(uint32_t i = 0; i < mesh.GetTriangles().size(); i++)
			{
				const Triangle& triangle = mesh.GetTriangles()[i];

				if ((ray.GetType() == RayType::camera || ray.GetType() == RayType::reflection || ray.GetType() == RayType::refractive) && triangle.Intersect(ray, t, u, v, mesh.GetVertices()) && t <= tNear && t > 0)
				{
					tNear = t;
					uNear = u;
					vNear = v;
					meshIndex = m;
					triIndex = i;
					intersected = true;
				}
				else if (ray.GetType() == RayType::shadow && m_Materials[mesh.GetMaterialIdx()].GetMaterialType() != MaterialType::refractive && triangle.Intersect(ray, t, u, v, mesh.GetVertices()) && t < tNear)
				{
					tNear = t;
					meshIndex = m;
					triIndex = i;
					intersected = true;
					break;
				}
			}
		}

		if(intersected)
		{
			const Triangle& triangle = m_Objects[meshIndex].GetTriangles()[triIndex];
			data.hitPoint = ray.GetOrigin() + ray.GetDirection() * tNear;
			data.hitPointNormal = triangle.GetTriangleNormal();
			//WRONG?
			data.interpolatedVertexNormal = glm::normalize(m_Objects[meshIndex].GetVertices()[triangle.GetVertex0()].GetVertexNormal() * (1 - uNear - vNear) +
											m_Objects[meshIndex].GetVertices()[triangle.GetVertex1()].GetVertexNormal() * uNear +
											m_Objects[meshIndex].GetVertices()[triangle.GetVertex2()].GetVertexNormal() * vNear);
			data.UV = { uNear, vNear };
			data.objectIdx = meshIndex;
			data.materialIdx = m_Objects[meshIndex].GetMaterialIdx();
			data.materialIOR = materialIOR;
			data.triangleIdx = triIndex;
		}

		return data;
	}

	IntersectionData Scene::AcceleratedTraceRay(const Ray& ray, float nearest) const
	{
		IntersectionData data;

		bool intersected = false;
		uint32_t meshIndex = 0;
		uint32_t triIndex = 0;
		float materialIOR = 1.0f;
		float tNear = nearest;
		float uNear = FLT_MAX;
		float vNear = FLT_MAX;
		float t = 0.0f;
		float u = 0.0f;
		float v = 0.0f;

		std::stack<int> nodeIndicesToCheck;
		nodeIndicesToCheck.push(0);
		while (nodeIndicesToCheck.size() > 0)
		{
			uint32_t currentNodeIdxToCheck = nodeIndicesToCheck.top();
			nodeIndicesToCheck.pop();
			LeafNode currentNode = m_AccelerationTree.GetLeafNodes()[currentNodeIdxToCheck];
			if (currentNode.GetBoundingBox().IntersectsBox(ray))
			{
				if (currentNode.GetTriangles().size() > 0)
				{
					for (const Triangle& triangle : currentNode.GetTriangles())
					{
						const Mesh& mesh = m_Objects[triangle.GetMeshIndex()];

						if (ray.GetType() != RayType::shadow && triangle.Intersect(ray, t, u, v, mesh.GetVertices()) && t <= tNear && t > 0)
						{
							tNear = t;
							uNear = u;
							vNear = v;
							meshIndex = triangle.GetMeshIndex();
							triIndex = triangle.GetIndex();
							intersected = true;
						}
						else if (ray.GetType() == RayType::shadow && m_Materials[mesh.GetMaterialIdx()].GetMaterialType() != MaterialType::refractive && triangle.Intersect(ray, t, u, v, mesh.GetVertices()) && t < tNear)
						{
							tNear = t;
							meshIndex = triangle.GetMeshIndex();
							triIndex = triangle.GetIndex();
							intersected = true;
							break;
						}
					}
				}
				else
				{
					if(currentNode.GetChildAIdx() != -1)
					{
						nodeIndicesToCheck.push(currentNode.GetChildAIdx());
					}

					if(currentNode.GetChildBIdx() != -1)
					{
						nodeIndicesToCheck.push(currentNode.GetChildBIdx());
					}
				}
			}

		}

		if (intersected)
		{
			const Triangle& triangle = m_Objects[meshIndex].GetTriangles()[triIndex];
			data.hitPoint = ray.GetOrigin() + ray.GetDirection() * tNear;
			data.hitPointNormal = triangle.GetTriangleNormal();
			data.interpolatedVertexNormal = glm::normalize(m_Objects[meshIndex].GetVertices()[triangle.GetVertex0()].GetVertexNormal() * (1 - uNear - vNear) +
				m_Objects[meshIndex].GetVertices()[triangle.GetVertex1()].GetVertexNormal() * uNear +
				m_Objects[meshIndex].GetVertices()[triangle.GetVertex2()].GetVertexNormal() * vNear);
			data.UV = { uNear, vNear };
			data.objectIdx = meshIndex;
			data.materialIdx = m_Objects[meshIndex].GetMaterialIdx();
			data.materialIOR = materialIOR;
			data.triangleIdx = triIndex;
		}

		return data;
	}

	void Scene::ParseSceneFile(const std::string& sceneFileName)
	{
		const rapidjson::Document& doc = GetJsonDocument(sceneFileName);

		//--------------------------------------------------------------------//
		//---------------------------PARSE SETTINGS---------------------------//
		//--------------------------------------------------------------------//
		const rapidjson::Value& settingsValue = doc.FindMember("settings")->value;
		if(!settingsValue.IsNull() && settingsValue.IsObject())
		{
			// Parse Color value
			const rapidjson::Value& colorValue = settingsValue.FindMember("background_color")->value;
			assert(!colorValue.IsNull() && colorValue.IsObject());
			m_Settings.SetBackgroundColor(LoadVector(colorValue.GetArray()));

			// Parse image Width and Height values
			const rapidjson::Value& imageSettignsValue = settingsValue.FindMember("image_settings")->value;
			if(!imageSettignsValue.IsNull() && imageSettignsValue.IsObject())
			{
				const rapidjson::Value& widthValue = imageSettignsValue.FindMember("width")->value;
				const rapidjson::Value& heightValue = imageSettignsValue.FindMember("height")->value;
				assert(!widthValue.IsNull() && widthValue.IsInt() && !heightValue.IsNull() && heightValue.IsInt());
				m_Settings.SetWidth(widthValue.GetFloat());
				m_Settings.SetHeight(heightValue.GetFloat());
				m_Settings.UpdateAspectRatio();
			}

			// Parse Global Illumination
			const rapidjson::Value& giValue = settingsValue.FindMember("gi_on")->value;
			assert(!giValue.IsNull() && giValue.IsBool());
			m_Settings.SetGI(giValue.GetBool());

			// Parse Reflections
			const rapidjson::Value& reflectValue = settingsValue.FindMember("reflections_on")->value;
			assert(!reflectValue.IsNull() && reflectValue.IsBool());
			m_Settings.SetReflections(reflectValue.GetBool());

			// Parse Refractions
			const rapidjson::Value& refractValue = settingsValue.FindMember("refractions_on")->value;
			assert(!refractValue.IsNull() && refractValue.IsBool());
			m_Settings.SetRefractions(refractValue.GetBool());
		}

		//--------------------------------------------------------------------//
		//----------------------------PARSE CAMERA----------------------------//
		//--------------------------------------------------------------------//
		const rapidjson::Value& cameraValue = doc.FindMember("camera")->value;
		if (!cameraValue.IsNull() && cameraValue.IsObject())
		{
			//Parse Matrix value
			const rapidjson::Value& matrixValue = cameraValue.FindMember("matrix")->value;
			assert(!matrixValue.IsNull() && matrixValue.IsArray());
			m_Camera.SetViewMatrix(LoadMatrix(matrixValue.GetArray()));

			//Parse Position value
			const rapidjson::Value& posValue = cameraValue.FindMember("position")->value;
			assert(!posValue.IsNull() && posValue.IsArray());
			m_Camera.SetPosition(LoadVector(posValue.GetArray()));
		}

		//--------------------------------------------------------------------//
		//----------------------------PARSE MESHES----------------------------//
		//--------------------------------------------------------------------//
		const rapidjson::Value& objectsValue = doc.FindMember("objects")->value;
		if (!objectsValue.IsNull() && objectsValue.IsArray())
		{
			auto objectValueArray = objectsValue.GetArray();

			//uint32_t sceneVertexIndex = 0;
			//uint32_t SVIOffset = 0;
			uint32_t sceneMeshIndex = 0;

			glm::vec3 boxMin(FLT_MAX);
			glm::vec3 boxMax(-FLT_MAX);

			std::vector<Triangle> triangles;

			for (uint32_t obj = 0; obj < objectValueArray.Size(); obj++)
			{
				// Parse Material Index
				const rapidjson::Value& materialIdxValue = objectValueArray[obj].FindMember("material_index")->value;
				int matIdx = 0;
				if(!materialIdxValue.IsNull() && materialIdxValue.IsInt())
				{
					matIdx = materialIdxValue.GetInt();
				}

				Mesh mesh = Mesh(matIdx, sceneMeshIndex);

				// Parse Vertices
				const rapidjson::Value& verticesValue = objectValueArray[obj].FindMember("vertices")->value;
				assert(!verticesValue.IsNull() && verticesValue.IsArray());
				auto vertexValuesArray = verticesValue.GetArray();

				for (uint32_t i = 0; i < vertexValuesArray.Size(); i += 3)
				{
					Vertex vertex(vertexValuesArray[i].GetFloat(), vertexValuesArray[i + 1].GetFloat(), vertexValuesArray[i + 2].GetFloat());
					
					boxMin.x = glm::min(boxMin.x, vertex.GetCoordinates().x);
					boxMin.y = glm::min(boxMin.y, vertex.GetCoordinates().y);
					boxMin.z = glm::min(boxMin.z, vertex.GetCoordinates().z);

					boxMax.x = glm::max(boxMax.x, vertex.GetCoordinates().x);
					boxMax.y = glm::max(boxMax.y, vertex.GetCoordinates().y);
					boxMax.z = glm::max(boxMax.z, vertex.GetCoordinates().z);

					mesh.PushVertex(vertex);
				}

				// Parse Triangles
				const rapidjson::Value& indicesValue = objectValueArray[obj].FindMember("triangles")->value;
				assert(!indicesValue.IsNull() && indicesValue.IsArray());
				auto indices = indicesValue.GetArray();

				uint32_t meshTriangleIndex = 0;

				for (uint32_t i = 0; i < indices.Size(); i += 3)
				{
					// VI - Vertex Index in Mesh
					uint32_t VI0 = indices[i].GetInt();
					uint32_t VI1 = indices[i + 1].GetInt();
					uint32_t VI2 = indices[i + 2].GetInt();
					
					// Push triangle the Mesh
					Triangle triangle(VI0, VI1, VI2, mesh.GetVertices(), sceneMeshIndex, meshTriangleIndex);
					triangles.push_back(triangle);
					mesh.PushTriangle(triangle);

					mesh.PushTriangleIndexToVertex(VI0, meshTriangleIndex);
					mesh.PushTriangleIndexToVertex(VI1, meshTriangleIndex);
					mesh.PushTriangleIndexToVertex(VI2, meshTriangleIndex);

					meshTriangleIndex++;
				}

				// Push Mesh into the Scene
				m_Objects.push_back(mesh);
				sceneMeshIndex++;
			}

			BoundingBox bBox(boxMin, boxMax);
			m_BoundingBox = bBox;
			m_AccelerationTree.AddNode(m_BoundingBox, -1, -1);
			m_AccelerationTree.BuildAccelerationTree(0, 0, triangles);

			for (Mesh& mesh : m_Objects)
			{
				mesh.UpdateVertexNormals();
			}

		}

		//--------------------------------------------------------------------//
		//----------------------------PARSE LIGHTS----------------------------//
		//--------------------------------------------------------------------//
		const rapidjson::Value& lightsValue = doc.FindMember("lights")->value;
		if (!lightsValue.IsNull() && lightsValue.IsArray())
		{
			auto lightsValueArray = lightsValue.GetArray();

			for (int light = 0; light < lightsValueArray.Size(); light++)
			{
				//Parse Intensity value
				const rapidjson::Value& intensityValue = lightsValueArray[light].FindMember("intensity")->value;
				assert(!intensityValue.IsNull() && intensityValue.IsInt());

				//Parse Position value
				const rapidjson::Value& posValue = lightsValueArray[light].FindMember("position")->value;
				assert(!posValue.IsNull() && posValue.IsArray());

				Light currentLight(intensityValue.GetInt(), LoadVector(posValue.GetArray()));
				m_Lights.push_back(currentLight);
			}
		}

		//--------------------------------------------------------------------//
		//--------------------------PARSE MATERIALS---------------------------//
		//--------------------------------------------------------------------//
		const rapidjson::Value& materialsValue = doc.FindMember("materials")->value;
		if (!materialsValue.IsNull() && materialsValue.IsArray())
		{
			auto materialsValueArray = materialsValue.GetArray();

			for (int material = 0; material < materialsValueArray.Size(); material++)
			{
				//Parse Type value
				const rapidjson::Value& typeValue = materialsValueArray[material].FindMember("type")->value;
				assert(!typeValue.IsNull() && typeValue.IsString());
				std::string type = typeValue.GetString();

				//Parse Albedo
				glm::vec3 albedo(1.0f);
				const rapidjson::Value& albedoValue = materialsValueArray[material].FindMember("albedo")->value;
				if(!albedoValue.IsNull() && albedoValue.IsArray())
				{
					albedo = LoadVector(albedoValue.GetArray());
				}

				//Parse SmoothShading
				const rapidjson::Value& shadingValue = materialsValueArray[material].FindMember("smooth_shading")->value;
				assert(!shadingValue.IsNull() && shadingValue.IsBool());
				bool smoothShading = shadingValue.GetBool();

				//Parse Backface Culling
				const rapidjson::Value& cullingValue = materialsValueArray[material].FindMember("back_face_culling")->value;
				bool backfaceCulling = true;
				if(!cullingValue.IsNull() && cullingValue.IsBool())
				{
					backfaceCulling = cullingValue.GetBool();
				}

				//Parse IOR
				float ior = 1.0f;
				const rapidjson::Value& iorValue = materialsValueArray[material].FindMember("ior")->value;
				if(!iorValue.IsNull() && iorValue.IsBool())
					ior = iorValue.GetFloat();

				Material mat(type, albedo, smoothShading, backfaceCulling, ior);

				m_Materials.push_back(mat);
			}
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