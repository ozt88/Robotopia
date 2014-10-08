﻿#pragma once

#include "cocos2d.h"
#include "Utils.h"

enum KeyCode
{
	KC_UP = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW,
	KC_RIGHT = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
	KC_DOWN = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW,
	KC_LEFT = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW,
	KC_ATTACK = cocos2d::EventKeyboard::KeyCode::KEY_A,
	KC_JUMP = cocos2d::EventKeyboard::KeyCode::KEY_SPACE,
	KC_TEST1 = cocos2d::EventKeyboard::KeyCode::KEY_F1,
	KC_TEST2 = cocos2d::EventKeyboard::KeyCode::KEY_F2,
	KC_MENU = cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE,
};

class InputManager
{
	friend class KeyStateSentinel;

public:	

	static KeyState													getKeyState(KeyCode keyCode);
	static void														receiveKeyboardData(cocos2d::Layer* layer); //layer에서 호출하면 이제 그 레이어에서는 키보드 정보가 자동으로 업데이트됨.
private:
	static std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_KeyStates;
	static std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_PrevKeyStates;
	static std::map<cocos2d::EventKeyboard::KeyCode, KeyState>		m_FinalKeyStates;
};

class KeyStateSentinel : public cocos2d::Node
{
	friend class InputManager;

public:
	OVERRIDE bool	init();

	void			onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void			onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	void			update(float dTime);

	CREATE_FUNC(KeyStateSentinel);
private:
};