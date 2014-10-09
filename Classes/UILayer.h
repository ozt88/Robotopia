#pragma once
#include "cocos2d.h"
#include "GameManager.h"
#include "Player.h"

class Minimap;
class WorldMenu;
class EquipmentWindow;
class BarContainer;

class UILayer : public cocos2d::Layer
{
public:
	virtual bool			init();
	void					update( float dTime );

	CREATE_FUNC( UILayer );

	void					initializeUILayer();

protected:
	enum UILayerEnum
	{
		LABEL_HPSTATUS,
		LABEL_STEAMSTATUS,
		SPRITE_FOREHP,
		SPRITE_BACKHP,
	};

	int									m_WinWidth , m_WinHeight;
	bool								m_WorldMenuOn;
	bool								m_CharWinOn;

	BarContainer*						m_BarContainer;
	EquipmentWindow*					m_EquipmentWindow;
	Minimap*							m_Minimap;
	WorldMenu*							m_WorldMenu;
};