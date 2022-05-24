// Lua.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include "NPCManager.h"
#include <functional>
#include "lua.hpp"


static int addNPC(lua_State* L)
{
	int t = lua_gettop(L);
	auto str = lua_tostring(L, 1);
	lua_pop(L, 1);
	NPCManager::GetInstance().AddNPC(str);
	return 0;
}

static int removeNPC(lua_State* L)
{
	auto str = lua_tostring(L, lua_gettop(L));
	lua_pop(L, 1);
	NPCManager::GetInstance().RemoveNPC(str);
	return 0;
}

static int setHealth(lua_State* L)
{
	auto health = lua_tointeger(L, lua_gettop(L));
	lua_pop(L, 1);
	auto name = lua_tostring(L,lua_gettop(L));
	lua_pop(L, 1);

	NPCManager::GetInstance().SetHealth((int)health, name);
	return 0;
}

int main()
{
		lua_State* L = luaL_newstate();

		lua_register(L, "addNPC", (lua_CFunction)addNPC);
		lua_register(L, "removeNPC", (lua_CFunction)removeNPC);
		lua_register(L, "setHealth", (lua_CFunction)setHealth);

		auto result = luaL_dofile(L, "startup.lub");

		if (result == LUA_OK)
		{
			std::cout << "lua succesfull\n";
		}
		else
		{
			std::string errormsg = lua_tostring(L, -1);
			std::cout << errormsg << std::endl;
		}
		NPCManager::GetInstance().Dump();

		std::cout << "\n\nMy script:\n\n";

		std::string LUA_FILE = "addNPC('Larry') name2 = 'Ludwig' addNPC(name2) setHealth(name2,13) name3 = 'Wendy' removeNPC(name3)";
		luaL_dostring(L, LUA_FILE.c_str());


		NPCManager::GetInstance().Dump();

		lua_close(L);

}
