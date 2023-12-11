#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#define MAX_INPUT_SIZE 1024

char *buf(const char *command);
void shell()
{
	char *word = "#cisfun$ ";
	printf("%s", word);
}
char *command_line(char *path)
{
	pid_t pid;

	char **a2 = malloc(sizeof(char *) * 1);
	char **a1 = malloc(sizeof(char *) * 2);
	if (a1 == NULL || a2 == NULL)
	{
		perror("malloc fail");
		exit(EXIT_FAILURE);
	}
	
	a1[0] = path;
	a1[1] = NULL;
	a2[0] = NULL;
	
	pid = fork();

	if (pid == -1)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path, a1, a2) == -1)
		{
			perror("error\n");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
	free(a1);
	free(a2);
	return(NULL);
}

char *buf(const char *command)
{
	char *b;

	b = malloc(sizeof(char) * MAX_INPUT_SIZE);
        if (b == NULL)
        {
                perror("failed\n");
		exit(EXIT_FAILURE);
        }
	strncpy(b, command, MAX_INPUT_SIZE - 1);
	b[MAX_INPUT_SIZE - 1] = '\0';
	
	free(b);
	return (NULL);
}

ssize_t read_line(const char *command)
{
	char *b;
	int file;
	ssize_t r;
	ssize_t wr;

	b = buf(command);
	file = open(command, O_RDONLY);

	if (file == -1)
	{
		return (0);
	}
	r = read(file, b, MAX_INPUT_SIZE - 1);

	wr = write(STDOUT_FILENO, b, r);

	free(b);
	close(file);
	return (wr);
}

int main()
{
	char *input = "/bin/ls";
	
	shell();
	while (1)
	{
		fflush(stdout);
		if (read_line(input))
		{
			continue;
		}
		else
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		if (input[MAX_INPUT_SIZE - 1] == '\n')
		{
			input[MAX_INPUT_SIZE - 1] = '\0';
		}
		if (strcmp(input, "exit") == 0)
		{
			perror("./shell: No such file or directory");
			break;
		}
		else if (strcmp(input, "/bin/ls") == 0)
		{
			command_line("/bin/ls | grep \\.c$");
		}
		else
			command_line(input);
	}
	return (0);  
}
