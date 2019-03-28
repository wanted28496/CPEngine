#pragma  once
/**
IObjectController.h
purpose: Interface for controller
@author Mit Doshi
@version 1.2 2/24/2019
*/
class GameObjects;
class IObjectController {
public:
	virtual void SetGameObject(GameObjects*) = 0;
	virtual void UpdateLocation() = 0;
};