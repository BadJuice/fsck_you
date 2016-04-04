/*
** fsck_you.c
**
** by Thomas Murgia
** login	<thomasmurgi@hotmail.fr>
**
** Started on Sun Apr 03 22:58:30 2016 Thomas Murgia
** Last update Mon Apr 04 10:22:15 2016 Thomas Murgia
*/

#include		<sys/types.h>
#include		<unistd.h>
#include		<signal.h>
#include		<stdlib.h>
#include		<stdint.h>
#include		<string.h>
#include		<stdio.h>
#include		<time.h>

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
	fread(&rand_val, sizeof (int), 1, file);
	fclose(file);
	return (rand_val % get_max_pid()) + 1;
}

int			main(int argc, char **argv)
{
	int		randpid;
	int		silent;

	randpid = 0;
	silent = 0;
	if (argc == 2 && !strcmp(argv[1], "--silent"))
		silent = 1;
	srand(time(NULL));
	puts("Killing processes for no reason...");
	while (1)
		{
			while ((randpid = gen_rand_pid()) == getpid());
			printf("Attempting to kill PID=%d\n", randpid);
			if ((kill(randpid, SIGSEGV) != 0) && !silent)
				puts("Failed :(");
			else if (!silent)
				printf("SUCCESSFULLY KILLED PID=%d, YAY!\n", randpid);
		}
	return EXIT_SUCCESS;
}
