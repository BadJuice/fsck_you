# fsck_you
Ruin you Linux systems with this program!

fsck_you is a C program, aimed at Linux users who want to torment their poor victims.
It works by sending SIGSEGV signals to random PIDs (within the kernel limits) until you
somehow stop it.

Syntax:

./fsck_you [--silent] [--hydra] [--friendly-fire]

--hydra : forks the process when SIGSEGV, SIGTERM or SIGKILL is recieved
--silent : doesn't print anything to stdout
--friendly-fire : allows the process to kill itself

/!\ YOU ARE RESPONSIBLE FOR ANY DAMAGE DONE TO YOUR INSTALLATION OR DEVICE BY THIS PROGRAM. /!\
