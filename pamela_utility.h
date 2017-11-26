/*
** pamela_utility.h for  in /home/belloc_p/rendu/pamela
** 
** Made by belloc_p
** Login   <paul.belloc@epitech.eu>
** 
** Started on  Sat Nov 25 18:56:44 2017 belloc_p
** Last update Sun Nov 26 20:25:13 2017 belloc_p
*/

#ifndef PAMELA_UTILITY_H_
# define PAMELA_UTILITY_H_

/* File names */
#define         CONTAINER_PATH "secure_data-rw-container"
#define         MOUNTED_PATH "secure_data-rw"

char            *pamela_get_container_path(char *pw_dir);
char            *pamela_get_mounted_path(char *pw_dir);
#endif
