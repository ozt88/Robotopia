
#include <string>
#include "GameManager.h"
#include "GameLayer.h"
#include "InteractiveObject.h"

USING_NS_CC;

bool StageManager::init()
{
	m_CurrentWorldScene = nullptr;
	m_CurrentFloorNum = 1;
	m_CurrentStageNum = 1;
	m_PlayerInfo.hp = 100 , m_PlayerInfo.maxHp = 100 , m_PlayerInfo.steam = 20 , m_PlayerInfo.maxSteam = 20;
	m_BoxSize = Size( 32 , 32 );

	GET_DATA_MANAGER()->getFloorData( m_CurrentFloorNum , &m_FloorData , &m_CurrentFloorStagesData );

	for( int stageNum = 1; stageNum <= m_FloorData.stageNum; ++stageNum )
	{
		m_CurrentStageNum = stageNum;
		m_CurrentWorldScene = WorldScene::createScene();
		int StageMaxWidthIdx = m_CurrentFloorStagesData[stageNum].width;
		int StageMaxHeightIdx = m_CurrentFloorStagesData[stageNum].height;
		std::map<int , ObjectType> data = m_CurrentFloorStagesData[stageNum].data;
		m_CurrentWorldScene->initCurrentSceneWithData( Vec2( StageMaxWidthIdx , StageMaxHeightIdx ) , m_BoxSize , data , "background.png" );
		m_CurrentWorldScene->retain();
		m_WorldScenes[stageNum] = m_CurrentWorldScene;
	}
	return true;
}

void StageManager::changeStage( int stageNum , Point nextPlayerPosition)
{
	_ASSERT( stageNum <= m_FloorData.stageNum );
	if( m_CurrentWorldScene != nullptr )
	{
		m_CurrentWorldScene->cleanup();
	}
	addVisitedStage( stageNum );
	savePlayerInfo();
	//나중에 씬단위에서 아래 데이터 처리하도록 하자.
	m_CurrentStageNum = stageNum;
	m_CurrentWorldScene = m_WorldScenes[m_CurrentStageNum];
	Director::getInstance()->replaceScene( m_CurrentWorldScene );
	loadPlayer( nextPlayerPosition );
	//m_CurrentWorldScene->resume();
}

Player* StageManager::getPlayer()
{
	if( m_CurrentWorldScene == nullptr )
	{
		return nullptr;
	}
	return ( m_CurrentWorldScene->getGameLayer() )->getPlayer();
}

std::vector<InteractiveObject*> StageManager::getObjectsByRect( cocos2d::Rect checkRect )
{
	std::vector<InteractiveObject*> results;
	results.clear();
	if( m_CurrentWorldScene == nullptr )
	{
		return results;
	}
	return ( m_CurrentWorldScene->getGameLayer() )->getObjectsByRect( checkRect );
}

std::vector<InteractiveObject*> StageManager::getObjectsByPosition( cocos2d::Point checkPosition )
{
	std::vector<InteractiveObject*> results;
	results.clear();
	if( m_CurrentWorldScene == nullptr )
	{
		return results;
	}
	return ( m_CurrentWorldScene->getGameLayer() )->getObjectsByPosition( checkPosition );
}

ObjectType StageManager::getStageDataInPosition( cocos2d::Point position )
{
	Vec2 idx = positionToIdxOfStage( position );
	return getStageDataInPositionWithIdx( idx.x , idx.y );
}


ObjectType StageManager::getStageDataInPositionWithIdx( int xIdx , int yIdx )
{
	return getStageDataInPositionWithIdx( xIdx , yIdx , m_CurrentStageNum );
}

ObjectType StageManager::getStageDataInPositionWithIdx( int xIdx , int yIdx , int stageNum )
{
	_ASSERT( stageNum <= m_FloorData.stageNum );
	StageData stageData = m_CurrentFloorStagesData[stageNum];
	_ASSERT( yIdx*stageData.width + xIdx < stageData.width*stageData.height );
	return stageData.data[yIdx*stageData.width + xIdx];
}

InteractiveObject* StageManager::addObject( ObjectType type , cocos2d::Point position )
{
	InteractiveObject* resultType = nullptr;
	if( m_CurrentWorldScene == nullptr )
	{
		return resultType;
	}
	return ( m_CurrentWorldScene->getGameLayer() )->addObject( type , position );
}

void StageManager::addEffectOnGameLayer( cocos2d::Sprite* effect )
{
	m_CurrentWorldScene->getGameLayer()->addEffect( effect );
}

void StageManager::addEffectOnGameLayer( cocos2d::Sprite* effect , Point position , Point AnchorPoint )
{
	effect->setAnchorPoint( AnchorPoint );
	effect->setPosition( position );
	m_CurrentWorldScene->getGameLayer()->addEffect( effect );
}

cocos2d::Vec2 StageManager::positionToIdxOfStage( cocos2d::Point position )
{
	Vec2 curPosIdx = Vec2( -1 , -1 );
	Rect curStageRect = getStageRect();
	if( curStageRect.containsPoint( position ) )
	{
		curPosIdx.x = position.x / m_BoxSize.width;
		curPosIdx.y = position.y / m_BoxSize.height;
	}
	return curPosIdx;
}

cocos2d::Vec2 StageManager::positionToIdxOfFloor( cocos2d::Point position )
{
	int stageXIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).x;
	int stageYIdx = GET_STAGE_MANAGER()->positionToIdxOfStage( position ).y;
	_ASSERT( m_CurrentStageNum <= m_FloorData.stageNum );
	int floorXIdx = m_CurrentFloorStagesData[m_CurrentStageNum].x + (stageXIdx - 1) / MODULE_BASE_WIDTH;
	int curFloorY = m_CurrentFloorStagesData[m_CurrentStageNum].y;
	int curPositionAddY = (stageYIdx-1) / MODULE_BASE_HEIGHT;
	int floorYIdx = curFloorY + curPositionAddY;

	return Vec2( floorXIdx , floorYIdx );
}

int StageManager::getFloorDataByIdx( int xIdx , int yIdx )
{
	_ASSERT( yIdx*m_FloorData.width + xIdx < m_FloorData.width * m_FloorData.height );
	return m_FloorData.data[m_FloorData.width*yIdx + xIdx];
}

void StageManager::addVisitedStage( int stage )
{
	bool isVisited = false;
	for( auto visitedStage : m_VisitedStageNums )
	{
		if( stage == visitedStage )
		{
			isVisited = true;
			break;
		}
	}
	if( !isVisited )
	{
		m_VisitedStageNums.push_back( stage );
	}
}

cocos2d::Point StageManager::idxOfStageDataToPosiion( cocos2d::Vec2 idx )
{
	return Point( idx.x*m_BoxSize.width , idx.y*m_BoxSize.height );
}

void StageManager::savePlayerInfo()
{
	auto player = getPlayer();
	if( player == nullptr )
	{
		return;
	}
	m_PlayerInfo = player->getInfo();
	getWorldScene()->getGameLayer()->removeObject( player );
}

void StageManager::loadPlayer( Point setPosition )
{
	addObject( OT_PLAYER , setPosition );
	auto player = getPlayer();
	player->setInfo( m_PlayerInfo );
}

cocos2d::Rect StageManager::getStageRect()
{
	int StageMaxWidthIdx = m_CurrentFloorStagesData[m_CurrentStageNum].width;
	int StageMaxHeightIdx = m_CurrentFloorStagesData[m_CurrentStageNum].height;

	return Rect( 0 , 0 , m_BoxSize.width * StageMaxWidthIdx , m_BoxSize.width * StageMaxHeightIdx );
}
