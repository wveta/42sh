#include <unistd.h>

int			main()
{
	int 	i;
	char	buffer[4096];

	while (1)
	{
		buffer[0] = '\0';
		i = read(STDIN_FILENO, buffer, 4095);
		if (i > 0)
			write(STDOUT_FILENO, buffer, i);
		else if (i == 0)
		{
			write(STDOUT_FILENO, "\n EOF", 5);
			return(0) ;
		}
		else
		{
			write(STDOUT_FILENO, "\n READ ERROR", 12);
			return(1) ;
		}
	}
}