/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 08:36:40 by gvynogra          #+#    #+#             */
/*   Updated: 2018/07/21 10:18:53 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char *g_commands[] = {"base64", "des", "des-ecb",
	"des-cbc", NULL};

void		ft_ssl_print_usage(void)
{
	int		i;

	i = 0;
	ft_printf("usage: ./ft_ssl <commands> <options>\n");
	ft_printf("Standart commands:\n\n");
	ft_printf("Message Digest commands:\nmd5\nsha256\n\n");
	ft_printf("Cipher commands:\n");
	while (g_commands[i] != NULL)
	{
		printf("%s\n", g_commands[i]);
		i++;
	}
	exit(0);
}

int			check_input_file(char *filename, t_ssl_opt *options)
{
	int		fd;

	if (*filename != '-')
	{
		fd = open(filename, O_RDONLY);
		if (fd <= 0)
		{
			ft_printf("cannot open input file: %s\n", filename);
			ft_ssl_print_usage();
		}
		else
			options->in_fd = fd;
		return (1);
	}
	else
	{
		ft_printf("invalid filename for input file: %s\n", filename);
		ft_ssl_print_usage();
	}
	return (0);
}

int			check_output_file(char *filename, t_ssl_opt *options)
{
	int		fd;

	if (*filename != '-')
	{
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, S_IWUSR | S_IRUSR);
		if (fd < 0)
		{
			ft_printf("cannot open output file: %s\n", filename);
			ft_ssl_print_usage();
		}
		else
			options->out_fd = fd;
		return (1);
	}
	else
	{
		ft_printf("invalid filename for output file: %s\n", filename);
		ft_ssl_print_usage();
	}
	return (0);
}

uint64_t	ft_hex_atoi64(char *str)
{
	uint64_t	nbr;
	int			i;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			nbr = nbr * 16 + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			nbr = nbr * 16 + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			nbr = nbr * 16 + (str[i] - 'a' + 10);
		else
			return (0);
		i++;
	}
	return (nbr);
}

static int	ft_hex_check(char *str, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		if ((!ft_isdigit(str[i])) && (!(str[i] >= 'a' && str[i] <= 'f'))
			&& (!(str[i] >= 'A' && str[i] <= 'F')))
			return (0);
		i++;
	}
	return (1);
}

void		ft_fill_by_zero(char *dst, int start, int end)
{
	while (start < end)
	{
		dst[start] = '0';
		start++;
	}
}

uint64_t	ft_key_validator(char *key)
{
	uint64_t	valid_key;
	int			len;
	int			i;
	char		*new_key;

	valid_key = 0;
	i = 0;
	new_key = NULL;
	len = ft_strlen(key);
	if (len < 16)
	{
		new_key = ft_strnew(16);
		if (!new_key)
			exit(0);
		new_key = ft_strcpy(new_key, key);
		ft_fill_by_zero(new_key, len + i, 16);
	}
	else if (len > 16)
		new_key = ft_strsub(key, 0, 16);
	if (!new_key)
		valid_key = ft_hex_atoi64(key);
	else
		valid_key = ft_hex_atoi64(new_key);
	ft_strdel(&new_key);
	return (valid_key);
}

int			check_des_key(char *key, t_ssl_opt *options)
{
	uint64_t	valid_key;

	valid_key = 0;
	if (!ft_hex_check(key, ft_strlen(key)))
	{
		ft_printf("Key is not valid\n");
		ft_ssl_print_usage();
	}
	valid_key = ft_key_validator(key);
	options->key = valid_key;
	return (1);
}

int			check_des_iv(char *iv, t_ssl_opt *options)
{
	uint64_t	valid_iv;

	valid_iv = 0;
	if (!ft_hex_check(iv, ft_strlen(iv)))
	{
		ft_printf("Vector is not valid\n");
		ft_ssl_print_usage();
	}
	valid_iv = ft_key_validator(iv);
	options->iv = valid_iv;
	return (1);
}

int		ft_check_mode(char *arg, t_ssl_opt *options)
{
	if (ft_strequ("-d", arg))
	{
		options->mode = DECODE;
		return (1);
	}
	else if (ft_strequ("-e", arg))
	{
		options->mode = ENCRYPT;
		return (1);
	}
	return (0);
}

int		ft_check_files(char **argv, int i, int argc, t_ssl_opt *options)
{
	if (ft_strequ("-i", argv[i]) && (i + 1) < argc)
	{
		options->i = check_input_file(argv[i + 1], options);
		return (1);
	}
	else if (ft_strequ("-o", argv[i]) && (i + 1) < argc)
	{
		options->o = check_output_file(argv[i + 1], options);
		return (1);
	}
	return (0);
}

int		ft_check_passwords(char **argv, int i, int argc, t_ssl_opt *options)
{
	if (ft_strequ("-k", argv[i]) && (i + 1) < argc)
	{
		options->k = check_des_key(argv[i + 1], options);
		return (1);
	}
	else if (ft_strequ("-s", argv[i]) && (i + 1) < argc)
	{
		options->s = check_des_key(argv[i + 1], options);
		return (1);
	}
	else if (ft_strequ("-v", argv[i]) && (i + 1) < argc)
	{
		options->v = check_des_iv(argv[i + 1], options);
		return (1);
	}
	return (0);
}

int			ft_ssl_parse_opts(int argc, char **argv, t_ssl_opt *options)
{
	int i;

	i = 2;
	while (i < argc)
	{
		if (ft_check_mode(argv[i], options))
			;
		else if (ft_check_files(argv, i, argc, options))
			i++;
		else if (ft_check_passwords(argv, i, argc, options))
			i++;
		else if (ft_strequ("-a", argv[i]))
			options->a = 1;
		else
			ft_ssl_print_usage();
		i++;
	}
	return (0);
}

int			ft_ssl_check_command(int argc, char **argv, t_ssl_opt *options)
{
	int		ret;
	int		j;

	ret = 0;
	j = 0;
	while (j < CIPHERS)
	{
		if (ft_strequ(argv[1], g_commands[j]))
		{
			options->cipher = j;
			ret++;
		}
		j++;
	}
	if (!ret)
		ft_ssl_print_usage();
	else
		ret += ft_ssl_parse_opts(argc, argv, options);
	return (ret);
}

t_ssl_pf	ft_chose_cipher(t_ssl_opt options)
{
	t_ssl_pf arr_ciphers[CIPHERS];

	arr_ciphers[BASE64] = &ft_ssl_base64_main;
	arr_ciphers[DES] = &ft_ssl_des_main;
	arr_ciphers[DES_ECB] = &ft_ssl_des_main;
	arr_ciphers[DES_CBC] = &ft_ssl_des_main;
	return (arr_ciphers[options.cipher]);
}

int			main(int argc, char **argv)
{
	t_ssl_opt	*options;
	t_ssl_pf	ft_enc;
	t_ssl_list	*head;

	head = (t_ssl_list*)ft_memalloc(sizeof(t_ssl_list));
	options = (t_ssl_opt*)ft_memalloc(sizeof(t_ssl_opt));
	if (!options || !head)
	{
		perror("cannot allocate memory");
		exit(0);
	}
	if (argc < 2)
		ft_ssl_print_usage();
	ft_ssl_check_command(argc, argv, options);
	if (!options->i)
		options->in_fd = 0;
	if (!options->o)
		options->out_fd = 1;
	ft_enc = ft_chose_cipher(*options);
	ft_enc(&head, *options);
	free(options);
	ft_ssl_list_del(&head);
	return (0);
}
