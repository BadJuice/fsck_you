/*
** fsck_you.c for source in /home/admin/Documents/Programming/dvm/vm/fsck_you/source
** 
** Made by Thomas Murgia
** Login   <Garuda1@hotmail.fr>
** 
** Started on  Wed May 04 21:52:44 2016 Thomas Murgia
** Last update Sat Jun 11 13:51:53 2016 Thomas Murgia
*/

#define   _POSIX_C_SOURCE   200809L
#define   RAND_SRC          "/dev/urandom"
#define   MAX_PID           "/proc/sys/kernel/pid_max"

#include  <sys/types.h>
#include  <unistd.h>
#include  <signal.h>
#include  <string.h>
#include  <fcntl.h>
#include  <stdio.h>

typedef struct t_args t_args;
struct t_args
{
  int   silent;
  int   hydra;
};

void      sig_handler(int sig)
{
  fork();
  ++sig;
}

void      set_signals(void)
{
  signal(SIGSEGV, sig_handler);
  signal(SIGINT, sig_handler);
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

void      init_args(t_args *s_args)
{
  s_args -> hydra = 0;
  s_args -> silent = 0;
}

int       rand_pid(void)
{
  int     rand_src;
  FILE    *pid_max_src;
  int     pid;
  int     pid_max;

  pid_max_src = fopen(MAX_PID, "r");
  rand_src = open(RAND_SRC, O_RDONLY);
  read(rand_src, &pid, sizeof(int));
  fscanf(pid_max_src, "%d", &pid_max);
  close(rand_src);
  fclose(pid_max_src);
  return (pid % pid_max);
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

  init_args(&s_args);
  check_args(&s_args, argc, argv);
  if (s_args.hydra)
    set_signals();
  if (!s_args.silent)
    my_puts("segfaulting processes for no reason...\n");
  while (1)
    {
      if (kill(rand_pid(), SIGSEGV) != 0 && !s_args.silent)
        my_puts("Failed...\n");
      else if (!s_args.silent)
        my_puts("LOL, SUCCESS!\n");
    }
  return (0);
}
