minishell: minishell.o
	cc -o minishell minishell.c
clean:
	rm -f minishell *.o core *~