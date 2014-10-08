#pragma once
#include "cocos2d.h"
#include "WorldScene.h"
#include "Player.h"

class Minimap;
class WorldMenu;
class EquipmentWindow;
class BarContainer;

class UILayer : public WorldScene
{
public:
	static cocos2d::Scene*	createScene();
	virtual bool			init();
	void					update(float dTime);

	CREATE_FUNC(UILayer);

	void					initializeUILayer();

protected:
	enum UILayerEnum
	{
		LABEL_HPSTATUS,
		LABEL_STEAMSTATUS,
		SPRITE_FOREHP,
		SPRITE_BACKHP,
	};

	const Player*						m_Player;
	int									m_WinWidth, m_WinHeight;

	BarContainer*						m_BarContainer;
	EquipmentWindow*					m_EquipmentWindow;
	Minimap*							m_Minimap;
	WorldMenu*							m_WorldMenu;
};