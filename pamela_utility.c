/*
** pamela_utility.c for  in /home/belloc_p/rendu/pamela
** 
** Made by belloc_p
** Login   <paul.belloc@epitech.eu>
** 
** Started on  Sat Nov 25 18:46:21 2017 belloc_p
** Last update Sun Nov 26 20:23:28 2017 belloc_p
*/

#include <string.h>
#include <stdlib.h>

#include "pamela_utility.h"

char            *pamela_get_container_path(char *pw_dir)
{
  char          *container_path = NULL;

  if ((container_path = malloc(sizeof(char) * (strlen(pw_dir) + strlen(CONTAINER_PATH) + 2))) == NULL)
    return (NULL);
  strcpy(container_path, pw_dir);
  container_path = strcat(container_path, "/");
  container_path = strcat(container_path, CONTAINER_PATH);
  return (container_path);
}

char            *pamela_get_mounted_path(char *pw_dir)
{
  char          *mounted_path = NULL;

  if ((mounted_path = malloc(sizeof(char) * (strlen(pw_dir) + strlen(MOUNTED_PATH) + 2))) == NULL)
    return (NULL);
  strcpy(mounted_path, pw_dir);
  mounted_path = strcat(mounted_path, "/");
  mounted_path = strcat(mounted_path, MOUNTED_PATH);
  return (mounted_path);
}
