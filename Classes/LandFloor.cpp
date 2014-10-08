#include "LandFloor.h"
#include "GameManager.h"

USING_NS_CC;

bool LandFloor::init()
{
	if( !LandObject::init() )
	{
		return false;
	}
	m_MainSprite = GET_RESOURCE_MANAGER()->createSprite( "floor.png" );
	this->setAnchorPoint( Point::ZERO );
	this->addChild( m_MainSprite, 10 );
	m_PieceSprite = GET_RESOURCE_MANAGER()->createSprite("floorPiece.png" );
	this->setAnchorPoint( Point::ZERO );
	this->addChild( m_PieceSprite , 0);

	m_Type = OT_FLOOR;
	m_Width = m_MainSprite->getContentSize().width;
	m_Height = m_MainSprite->getContentSize().height;

	return true;
}

