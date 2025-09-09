#pragma once
#include "Object.h"
#include "framework.h"

namespace Render
{
	//class ResourceManager;

	class ObjectManager
	{
	public:
		//template <typename T>
		//void AddRenderingObject(UINT* _AssetNum, UINT _ObjectID, RenderTransform* _WorldTM, UINT* _State, bool* _IsRender);
		template <typename T>
		void AddRenderingObject(UINT* _AssetNum, UINT _ObjectID, void* _Matrix, RenderTransform* _WorldTM, UINT* _State, bool* _IsRender, Vector2* _Size);

		/// <summary>
		/// AssetNum, objInfo
		/// </summary>
		template <typename T>
		std::map<UINT, std::vector<ObjectInfo>>& GetObjectList() {
			return m_RenderringObject<T>;
		};

		/*ObjectInfo* GetObjectInfo(UINT _ObjectID) {
			for (auto* objectInfo : m_ObjectList)
			{
				if (objectInfo->m_ID == _ObjectID)
				{
					return objectInfo;
				}
			}
			return nullptr;
		};*/
		template<typename T>
		ObjectInfo* GetObjectInfo(UINT _ObjectID) {
			for (auto& map : m_RenderringObject<T>)
			{
				for (auto& obj : map.second)
				{
					if (obj.m_ID == _ObjectID)
					{
						return &obj;
					}
				}
			}
			
			return nullptr;
		};
		template<typename T>
		void DestroyAllObjectInAsset() {
			for (auto& map : m_RenderringObject<T>)
			{
				map.second.clear();
			}
		};

		//std::vector<ObjectInfo> m_ObjectList;
	private:

		/// <summary>
		/// AssetNum, objInfo
		/// </summary>
		/// <typeparam name="T"></typeparam>
		template <typename T>
		static std::map<UINT,std::vector<ObjectInfo>> m_RenderringObject;
	};
	template <typename T>
	std::map<UINT, std::vector<ObjectInfo>> ObjectManager::m_RenderringObject;

	
	//template<typename T>
	//inline void ObjectManager::AddRenderingObject(UINT* _AssetNum, UINT _ObjectID, RenderTransform* _WorldTM, UINT* _State, bool* _IsRender)
	//{
	//	AddRenderingObject<T>(_AssetNum, _ObjectID,nullptr ,_WorldTM, _State, _IsRender,nullptr);
	//}

	template<typename T>
	inline void ObjectManager::AddRenderingObject(UINT* _AssetNum, UINT _ObjectID, void* _Matrix , RenderTransform* _WorldTM, UINT* _State, bool* _IsRender, Vector2* _Size)
	{
		//for (auto* objectInfo : m_ObjectList)
		//{
		//	if (objectInfo->m_ID == _ObjectID)
		//	{
		//		assert(!(objectInfo->m_ID == _ObjectID));
		//		return;
		//	}
		//}

		for (auto& obj : m_RenderringObject<T>[*_AssetNum])
		{
			if (obj.m_ID == _ObjectID)
			{
				assert(!(obj.m_ID == _ObjectID));
				return;
			}
		}
		ObjectInfo obj;
		obj.m_ID = _ObjectID;
		obj.m_pWorldTransform = static_cast<SimpleMath::Matrix*>(_Matrix);
		obj.m_pWorldTM = _WorldTM;
		obj.m_pSTATE = _State;
		obj.m_pIsRender = _IsRender;
		obj.m_pSize = _Size;

		m_RenderringObject<T>[*_AssetNum].emplace_back(obj);
		//m_ObjectList.push_back(&m_RenderringObject<T>[*_AssetNum].back());
		//m_ObjectList.push_back(obj);

	}

}
