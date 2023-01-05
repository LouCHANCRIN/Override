#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void	log_wrapper(FILE *log_fd, char *str, char *backup_fd) {
	char	buf[264];

	strcpy(buf, str);
	snprintf(buf + strlen(buf), 264 - strlen(buf), backup_fd);
	buf[strcspn(buf, "\n")] = '\0';
	fprintf(log_fd, "LOG: %s\n", buf);
	return ;
}

int		main(int ac, char **av) {
	FILE	*log_fd;
	FILE	*backup_fd;
	int		new_fd;
	char	c;
	char	backup[100];

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);
	log_fd = fopen("./backups/.log", "w");
	if (log_fd == NULL) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(log_fd, "Starting back up: ", av[1]);
	backup_fd = fopen(av[1], "r");
	if (backup_fd == NULL) {
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}
	strcpy(backup, "./backups");
	strncat(backup, av[1], 99 - strlen(backup));
	new_fd = open(backup, 193, 432);
	if (new_fd < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups", av[1]);
		exit(1);
	}
	while((c = fgetc(backup_fd)) != -1) {
		write(new_fd, c, 1);
	}
	log_wrapper(log_fd, "Finished back up ", av[1]);
	fclose(backup_fd);
	close(new_fd);
	return 0;
}