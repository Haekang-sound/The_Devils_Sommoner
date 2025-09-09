#pragma once
class InputManager;
class TimeManager;
class ObjectManager;
class ResourceManager;
class Scenemaager;

class ManagerSet
{
public:	
	// Get/Set은 취향입니다
	TimeManager* GetTime() const { return _time; }
	void SetTime(TimeManager* val) { _time = val; }

	InputManager* GetInput() const { return _input; }
	void SetInput(InputManager* val) { _input = val; }

	ObjectManager* GetObj() const { return _obj; }
	void SetObj(ObjectManager* val) { _obj = val; }

	ResourceManager* GetResource() const { return _resource; }
	void SetResource(ResourceManager* val) { _resource = val; }

private:
	TimeManager* _time;
	InputManager* _input;
	ObjectManager* _obj;
	ResourceManager* _resource;
};