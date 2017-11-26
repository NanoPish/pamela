/*
** pamela_module.h for  in /home/belloc_p/rendu/pamela
** 
** Made by belloc_p
** Login   <paul.belloc@epitech.eu>
** 
** Started on  Sat Nov 25 18:57:00 2017 belloc_p
** Last update Sun Nov 26 19:58:02 2017 belloc_p
*/

#ifndef PAMELA_MODULE_H_
# define PAMELA_MODULE_H_

/* Define which PAM interfaces we provide */
# define        PAM_SM_SESSION

/* Include PAM headers */
# include <security/pam_appl.h>
# include <security/pam_modules.h>

char            *pamela_get_container_path(char *pw_dir);
char            *pamela_get_mounted_path(char *pw_dir);
int             pamela_make_container(const char *user, const char *container_path, const char *mounted_path);
int             pamela_close_container(const char *user, const char *container_path, const char *mounted_path);
int             pamela_open_container(const char *user, const char *container_path, const char *mounted_path);

#endif
