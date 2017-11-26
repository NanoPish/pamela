/*
** pamela_container.c for  in /home/belloc_p/rendu/pamela
**
** Made by belloc_p
** Login   <paul.belloc@epitech.eu>
**
** Started on  Sat Nov 25 19:17:44 2017 belloc_p
** Last update Sun Nov 26 23:09:42 2017 belloc_p
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Include PAM header for return values codes */
#include <security/pam_appl.h>

static int      pamela_set_file_permissions(const char *path)
{
  char          *command = NULL;
  int           system_ret = 0;
  int           cmd_len = 0;

  cmd_len = (strlen(path)) + 30;
  if ((command = malloc(sizeof(char) * cmd_len)) == NULL)
    return (PAM_BUF_ERR);
  memset(command, 0, cmd_len * sizeof(char));
  snprintf(command, cmd_len, "%s%s", "chmod -R 700 ", path);
  system_ret = system(command);
  return (system_ret);
}

int             pamela_make_container(const char *user, const char *container_path, const char *mounted_path)
{
  char          *command = NULL;
  int           system_ret = 0;
  int           cmd_len = 0;

  //Create file
  cmd_len = (3 * strlen(container_path)) + 200;
  if ((command = malloc(sizeof(char) * cmd_len)) == NULL)
    return (PAM_BUF_ERR);
  snprintf(command, cmd_len, "%s%s%s", "dd if=/dev/zero of=", container_path,
	   " bs=1 count=0 seek=100M");
  system_ret = system(command);
  printf("Tried to make a file of 100m in %s\n", container_path);
  //Create Key
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s","dd if=/dev/urandom of=",
	   container_path, ".key", " bs=1024 count=1");
  system_ret = system(command);
  printf("Tried to make a key in %s.key\n", container_path);
  //Cipher file
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s%s", "cryptsetup luksFormat ",
	   container_path, " ", container_path, ".key");
  system_ret = system(command);
  printf("Tried to cryptsetup container with key\n");
  //Open encrypted image
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s%s%s%s%s", "cryptsetup luksOpen ",
	   container_path, " ", user,
	   "-pamela-volume ", "--key-file ", container_path, ".key");
  system_ret = system(command);
  printf("Tried to open container with key on %s-pamela-volume\n", user);
  //Format encrypted volume
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len,"%s%s%s", "mkfs.ext4 /dev/mapper/", user,
	   "-pamela-volume");
  system_ret = system(command);
  printf("Tried to format volume.");
  //Create mountpoint
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s", "mkdir -p ", mounted_path);
  system_ret = system(command);
  printf("Tried to mkdir -p mountpoint\n");
  //Mount the volume
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s", "mount /dev/mapper/", user,
	   "-pamela-volume ", mounted_path);
  system_ret = system(command);
  printf("Tried to mount volume.\n");
  // PERMISSIONS
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s", container_path, ".key");
  if (pamela_set_file_permissions(mounted_path) != 0)
    printf("Changing mounted permissions failed\n");
  if (pamela_set_file_permissions(container_path) != 0)
    printf("Changing container permissions failed\n");
  if (pamela_set_file_permissions(command) != 0)
    printf("Changing key permissions failed\n");
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s%s%s","chown -R ", user, ":", user, " ", mounted_path);
  system_ret = system(command);
  return (PAM_SUCCESS);
}

int             pamela_close_container(const char *user, const char *container_path, const char *mounted_path)
{
  char          *command = NULL;
  int           system_ret = 0;
  int           cmd_len = 0;

  cmd_len = (3 * strlen(container_path)) + 200;
  if ((command = malloc(sizeof(char) * cmd_len)) == NULL)
    return (PAM_BUF_ERR);
  //Umount
  snprintf(command, cmd_len, "%s%s",  "umount ", mounted_path);
  system_ret = system(command);
  printf("Tried to umount mountpoint. %s\n. command : %s\n",
	 mounted_path, command);
  //Close
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s", "cryptsetup luksClose ", user,
    "-pamela-volume");
  system_ret = system(command);
  printf("Tried to luksclose volume. command : %s\n", command);
  return (PAM_SUCCESS);
}

int             pamela_open_container(const char *user, const char *container_path, const char *mounted_path)
{
  char          *command = NULL;
  int           system_ret = 0;
  int           cmd_len = 0;

  cmd_len = (3 * strlen(container_path)) + 200;
  if ((command = malloc(sizeof(char) * cmd_len)) == NULL)
    return (PAM_BUF_ERR);
  //Open encrypted image
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s%s%s%s%s", "cryptsetup luksOpen ",
	   container_path, " ", user,
	   "-pamela-volume ", "--key-file ", container_path, ".key");
  system_ret = system(command);
  printf("Tried to open container with key on %s-pamela-volume\n", user);
  //Create mountpoint
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s", "mkdir -p ", mounted_path);
  system_ret = system(command);
  printf("Tried to mkdir -p mountpoint\n");
  //Mount the volume
  memset(command, 0, strlen(command));
  snprintf(command, cmd_len, "%s%s%s%s", "mount /dev/mapper/", user, "-pamela-volume ",
    mounted_path);
  system_ret = system(command);
  printf("Tried to mount volume.");
  return (PAM_SUCCESS);
}
