/*
** pamela_module.c for  in /home/belloc_p/rendu/pamela
**
** Made by belloc_p
** Login   <paul.belloc@epitech.eu>
**
** Started on  Sat Nov 25 17:15:12 2017 belloc_p
** Last update Sun Nov 26 22:11:48 2017 belloc_p
*/

#include <stdio.h>
#include <pwd.h>
#include <unistd.h>

#include "pamela_module.h"

/* PAM entry point for session creation */
int             pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  struct passwd *pw = NULL;
  const char    *user = NULL;
  const char    *container_path = NULL;
  const char    *mounted_path = NULL;
  int           pgu_ret = 0;
  int           access_ret = 0;
  int           pamela_ret = 0;
  int           user_input = 0;
  //Get user
  pgu_ret = pam_get_user(pamh, &user, NULL);
  if (pgu_ret != PAM_SUCCESS || user == NULL)
    return (PAM_IGNORE);
  //User home directory
  pw = getpwnam(user);
  if (pw == NULL || pw->pw_dir == NULL || pw->pw_dir[0] != '/') {
    return (PAM_IGNORE);
  }
  //Get container path
  if ((container_path = pamela_get_container_path(pw->pw_dir)) == NULL)
    return (PAM_IGNORE);
  //Get mounted path
  mounted_path = pamela_get_mounted_path(pw->pw_dir);
  //Check if container exists
  access_ret = access(container_path, F_OK);
  if (access_ret == 0)
    {
      printf("Pamela container exists. Going to open it.\n");
      if ((pamela_ret = pamela_open_container(user, container_path, mounted_path)) != PAM_SUCCESS)
        {
          printf("Failed to open container\n");
          return (pamela_ret);
        }
    }
  else
    {
      printf("No pamela container found. Do you want to create a pamela container ?\nY or N:\n");
      user_input = getchar();
      while (user_input != 'Y' && user_input != 'N')
        {
          user_input = getchar();
          printf("Answer Y(es) or N(o)\n");
        }
      if (user_input == 'Y')
        {
          if ((pamela_ret = pamela_make_container(user, container_path, mounted_path)) != PAM_SUCCESS)
            {
              printf("Failed to make container\n");
              return (pamela_ret);
            }
        }
      else
        return (PAM_SUCCESS);
    }
  return (PAM_SUCCESS);
}

/* PAM entry point for session cleanup */
int             pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
  const char    *user = NULL;
  const char    *mounted_path = NULL;
  struct passwd *pw = NULL;
  int           pgu_ret = 0;
  int           pamela_ret = 0;

  //Get user
  pgu_ret = pam_get_user(pamh, &user, NULL);
  if (pgu_ret != PAM_SUCCESS || user == NULL)
    return (PAM_USER_UNKNOWN);
  //Get user home directory
  pw = getpwnam(user);
  if (pw == NULL || pw->pw_dir == NULL || pw->pw_dir[0] != '/') {
    return (PAM_SYSTEM_ERR);
  }
  //Get mounted path
  mounted_path = pamela_get_mounted_path(pw->pw_dir);
  //Close and ummout user container and mountpoint
  pamela_ret =
    pamela_close_container(user, pamela_get_container_path(pw->pw_dir), mounted_path);
  return (pamela_ret);
}
