#pragma once
#include "cocos2d.h"
#include "LandObject.h"

class LandGateway : public LandObject
{
public:
	OVERRIDE bool		init();
	OVERRIDE void		collisionOccured( InteractiveObject* enemy , Directions dir );
	void				gotoNextLevel( Ref* sender );
	size_t				findNextStageNum();
	Direction			findNeighborDir(cocos2d::Vec2 stageIdx);
	CREATE_FUNC( LandGateway );

private:
	cocos2d::Animation*	m_OpenAnimaion;
	cocos2d::Animation*	m_ActivateAnimation;
	bool				m_isOpen;
	bool				m_IsActive;
};
