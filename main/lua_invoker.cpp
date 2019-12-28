//
// Created by Administrator on 2019/12/12 0012.
//
#include <stdio.h>


//lua头文件
#ifdef __cplusplus
extern "C" {
#include "lua.h"
#include <lauxlib.h>
#include <lualib.h>
}
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#define LUA_FUNC_PATH "lua/lua_invoker_func.lua"

int main()
{
    lua_State * lua_env=NULL;

    /* 初始化 Lua */
    lua_env = lua_open();

    /* 载入Lua基本库 */
    luaL_openlibs(lua_env);

    /* 运行脚本 */
    int error = luaL_dofile(lua_env, LUA_FUNC_PATH);
    if(error) {
        perror("luaL_dofile error");
        return 1;
    }

    lua_getglobal(lua_env,"showstr");
    lua_newtable(lua_env); // 创建一个table
    lua_pushstring(lua_env, "name");  //key为intVal
    lua_pushinteger(lua_env,1234);      //值为1234
    lua_settable(lua_env, -3);          //写入table

    lua_pcall(lua_env,1,0,0);

    /* 清除Lua */
    lua_close(lua_env);

}
