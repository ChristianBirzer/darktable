#include "lua/lua.h"
#include "external/libgit2/include/git2.h"

/* clone( repourl:string, destinationpath: string )
*/
static int lua_gitclone(lua_State*L)
{
  const char* url  = luaL_checkstring(L,1);
  const char* path = luaL_checkstring(L,2);

  git_repository *repo = NULL;

  git_libgit2_init();
  int error = git_clone( &repo, url, path, NULL );
  lua_pushinteger( L, error );
  git_libgit2_shutdown();

  return 1;
}

int dt_lua_init_git(lua_State *L)
{

  git_libgit2_init();

  dt_lua_push_darktable_lib(L);
  dt_lua_goto_subtable(L,"git");

  lua_pushcfunction(L,lua_gitclone);
  lua_setfield(L,-2,"clone");

  lua_pop(L,1);
  return 0;
}