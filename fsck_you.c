/*
** fsck_you.c
**
** by Thomas Murgia
** login	<thomasmurgi@hotmail.fr>
**
** Started on Sun Apr 03 22:58:30 2016 Thomas Murgia
** Last update Mon Apr 04 17:05:20 2016 Thomas Murgia
*/

#include		<sys/types.h>
#include		<unistd.h>
#include		<signal.h>
#include		<stdlib.h>
#include		<stdint.h>
#include		<string.h>
#include		<stdio.h>
#include		<time.h>

struct			t_arg
{
	int		silent_mode;
	int		hydra;
	int		friendly_fire;
};

void			*fork_wrapper(void)
{
	fork();
	return NULL;
}

void			init_args(struct t_arg *s_arg)
{
	s_arg->silent_mode = 0;
	s_arg->hydra = 0;
	s_arg->friendly_fire = 0;
}

void			check_args(const int argc, char **argv, struct t_arg *s_args)
{
	int		i;

	i = 0;
	while (i != (argc - 1))
		{
			if (!strcmp(argv[i + 1], "--silent"))
				s_args->silent_mode = 1;
			else if (!strcmp(argv[i +1], "--hydra"))
				s_args->hydra = 1;
			else if (!strcmp(argv[i + 1], "--friendly-fire"))
				s_args->friendly_fire = 1;
			++i;
		}
}

int			get_max_pid(void)
{
        int		max_pid;
        FILE            *file;

        file = fopen("/proc/sys/kernel/pid_max", "r");
        fscanf(file, "%d", &max_pid);
        fclose(file);

        return max_pid;
}

int			gen_rand_pid(void)
{
	int		rand_val;
	FILE		*file;

	file = fopen("/dev/urandom", "r");
	fread(&rand_val, sizeof(int), 1, file);
	fclose(file);
	if (rand_val < 0)
		rand_val *= -1;
	return (rand_val % get_max_pid()) + 1;
}

int			main(int argc, char **argv)
{
	int		randpid;
	struct t_arg	s_args;

	randpid = 0;
	init_args(&s_args);
	check_args(argc, argv, &s_args);
	srand(time(NULL));
	if (s_args.hydra)
		{
			signal(SIGSEGV, fork_wrapper);
			signal(SIGTERM, fork_wrapper);
			signal(SIGKILL, fork_wrapper);
		}
	if (!s_args.silent_mode)
		puts("Killing processes for no reason...");
	while (1)
		{
			while ((randpid = gen_rand_pid()) == getpid() && !s_args.friendly_fire);
			if (!s_args.silent_mode)
				printf("Attempting to kill PID=%d\n", randpid);
			if ((kill(randpid, SIGSEGV) != 0) && !s_args.silent_mode)
				puts("Failed :(");
			else if (!s_args.silent_mode)
				printf("SUCCESSFULLY KILLED PID=%d, YAY!\n", randpid);
		}
	return EXIT_SUCCESS;
}
