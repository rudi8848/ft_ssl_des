#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
# include <stdlib.h>
# include <sys/wait.h>

# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define RED 		"\033[0;31m"
# define GREEN 		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[1;36m"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		len;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (s1 && s2)
	{
		len = strlen(s1) + strlen(s2);
		dest = (char*)malloc(sizeof(char) * (len + 1));
		if (dest)
		{
			while (s1[i])
			{
				dest[i] = s1[i];
				i++;
			}
			while (s2[j])
				dest[i++] = s2[j++];
			dest[i++] = '\0';
			return (dest);
		}
	}
	return (NULL);
}

extern char **environ;
void	ft_cmd_exe(char **args)
{
	//printf("----------->%s\n", __FUNCTION__);
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		printf("Error\n");
		exit(0);
	}
	else if (pid == 0)
	{
		status = execve(args[0], args, environ);
		if (args[0] && status < 0)
			printf("%s: command not found\n", args[0]);
		exit(0);
	}
	else
		wait(&status);
}

int		main(void)
{
	char *filename;
	char *out = "outmy";
	char *out1 = "outor";
	struct dirent	*info;
	DIR				*dirp;
	char			*prefix;
	char *dirname = "./test/";

	char *args[] = {
	 "./ft_ssl",
	"des-ecb",
	"-a",
	"-i",
	"",
	"-o",
	"",
	"-k",
	"aa1234567890",
	NULL
	};

	char *d_args[] = {
	 "./ft_ssl",
	"des-ecb",
	"-a",
	"-d",
	"-i",
	"test/outmy",
	"-o",
	"test/dmy",
	"-k",
	"aa1234567890",
	NULL
	};

	char *orargs[] = {
	"/usr/bin/openssl",
	"des-ecb",
	"-a",
	"-in",
	"",
	"-out",
	"",
	"-K",
	"aa1234567890",
	 NULL
	};

	char *d_orargs[] = {
	"/usr/bin/openssl",
	"des-ecb",
	"-a",
	"-d",
	"-in",
	"test/outor",
	"-out",
	"test/dor",
	"-K",
	"aa1234567890",
	 NULL
	};

	dirp = opendir("test");
	if (dirp == NULL)
	{
		perror("cannot open");
		return 1;
	}


	while ((info = readdir(dirp)))
	{
		//printf("reading directory...\n");
		if (info == NULL)
		{
			perror("cannot read");
			return 1;
		}
		if ((*info).d_name[0] == '.' || (*info).d_name[0] == 'o' || (*info).d_name[0] == 'd')
			continue;
		
		filename = ft_strjoin(dirname,info->d_name);
		//printf("%s\n", filename);
		args[4] = filename;
		//args[3] = filename;
		orargs[4] = filename;
		//orargs[3] = filename;
		
		
		
		
		args[6] = ft_strjoin(dirname, out);
		//args[5] = ft_strjoin(dirname, out);
		orargs[6] = ft_strjoin(dirname, out1);
		//orargs[5] = ft_strjoin(dirname, out1);

		printf("--- 	TEST: %s%s%s 	---\n", BLUE, filename, RESET);
		ft_cmd_exe(args);
		ft_cmd_exe(orargs);
		//printf("%s", RED);
		write(STDERR_FILENO, RED, 7);
		system("diff test/outmy test/outor");
		//printf("%s", RESET);
		write(STDERR_FILENO, RESET, 4);

		printf("---> 	DECRYPT	---\n");
		ft_cmd_exe(d_args);
		ft_cmd_exe(d_orargs);
		printf("%s", RED);
		system("diff test/dmy test/dor");
		printf("%s", RESET);
		printf("-------------------------------------\n\n");
		
			free(filename);
			free(args[6]);
			//free(args[5]);
			free(orargs[6]);
			//free(orargs[5]);
	}

	closedir(dirp);
	return 0;
}
