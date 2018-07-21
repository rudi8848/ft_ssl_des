/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_des.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 09:18:44 by gvynogra          #+#    #+#             */
/*   Updated: 2018/07/21 09:55:04 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	g_init_permut_order[64] =
{
	58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7
};

char	g_key_permut_order[56] =
{
	57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

char	g_compres_permut_order[48] =
{
	14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

char	g_expans_permut_order[48] =
{
	32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1
};

char	g_p_box_permut_order[32] =
{
	16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9, 19, 13, 30, 6, 22, 11, 4, 25
};

char	g_final_permut_order[64] =
{
	40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25
};

char	g_s_box_order[8][4][16] =
{
	{
		{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
	},
	{
		{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
	},
	{
		{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
	},
	{
		{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
	},
	{
		{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
	},
	{
		{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
	},
	{
		{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
	},
	{
		{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
	}
};

int			ft_ssl_fill_data(uint8_t *dest, uint8_t *src, int start, int n)
{
	int	i;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			dest[i] = src[start];
			start++;
			i++;
		}
		return (n);
	}
	return (0);
}

t_ssl_list	*ft_get_last(t_ssl_list *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void		ft_ssl_lst_push_back(t_ssl_list *head, uint8_t *buf, int n)
{
	t_ssl_list *tmp;
	t_ssl_list *end;

	end = ft_get_last(head);
	tmp = (t_ssl_list*)ft_memalloc(sizeof(t_ssl_list));
	if (!tmp || !end)
	{
		perror("Cannot alocate memory");
		exit(0);
	}
	tmp->next = NULL;
	end->next = tmp;
	tmp->data_size = n;
	ft_ssl_fill_data(tmp->data, buf, 0, n);
}

void		ft_des_a_decode(t_ssl_list *head, t_ssl_opt opt, uint8_t *b, int r)
{
	int		j;
	uint8_t	rb;

	j = 0;
	rb = 0;
	while ((r = read(opt.in_fd, &rb, 1)) > 0)
	{
		if (rb != '\n')
		{
			b[j] = rb;
			j++;
			if (j == 8)
			{
				ft_ssl_lst_push_back(head, b, j);
				j = 0;
				ft_bzero((uint8_t*)b, 9);
			}
			rb = 0;
		}
	}
	if (j && b[j - 1] == '\n')
		j--;
	if (j)
		ft_ssl_lst_push_back(head, b, j);
}

void		ft_read_file(t_ssl_list *head, t_ssl_opt options)
{
	int		ret;
	uint8_t	buf[9];

	ft_bzero((uint8_t*)buf, 9);
	if (options.a && options.mode == DECODE)
		ft_des_a_decode(head, options, buf, 0);
	else
	{
		while ((ret = read(options.in_fd, buf, 8)) > 0)
		{
			if (options.cipher == BASE64 && options.mode == DECODE
					&& buf[ret - 1] == '\n')
				ret--;
			if (ret)
				ft_ssl_lst_push_back(head, buf, ret);
		}
	}
}

void		ft_padding(uint8_t *data, int n)
{
	uint8_t diff;

	diff = 8 - n;
	if (diff)
	{
		while (n < 8)
		{
			data[n] = diff;
			n++;
		}
	}
}

void		ft_ssl_padding(t_ssl_list *head)
{
	t_ssl_list	*end;
	t_ssl_list	*tmp;
	uint8_t		buf[8];

	end = ft_get_last(head);
	if (end->data_size < 8)
	{
		ft_padding(end->data, end->data_size);
		end->data_size = 8;
	}
	else
	{
		ft_padding(buf, 0);
		ft_ssl_lst_push_back(head, buf, 8);
	}
}

void		ft_ssl_unpadding(t_ssl_list *head)
{
	t_ssl_list	*last;
	uint8_t		end;
	uint8_t		*ptr;

	last = ft_get_last(head);
	end = (short)last->data[7];
	if (end < 8)
	{
		last->data_size = 8 - end;
		ptr = &last->data[8 - end];
		ft_bzero((uint8_t*)ptr, end);
	}
	else
	{
		last->data_size = 0;
	}
}

uint64_t	ft_permutator(uint64_t block, char *permut_order, int n)
{
	uint64_t	output;
	uint64_t	bit;
	int			i;

	output = 0;
	i = 0;
	while (i < n)
	{
		bit = ((block >> (64 - permut_order[i])) & 1);
		if (bit)
			output |= (bit << (64 - (i + 1)));
		i++;
	}
	return (output);
}

uint64_t	ft_key_left_shift(uint64_t key, int n)
{
	uint64_t left_half;
	uint64_t right_half;
	uint64_t res;

	res = 0;
	left_half = (key >> 36) << 36;
	right_half = key << 28 >> 28;
	left_half = (left_half << n | left_half >> (28 - n)) >> 36 << 36;
	right_half = ((right_half << n) << 28 >> 28 |
			right_half >> (28 - n)) >> 8 << 8;
	res = left_half | right_half;
	return (res);
}

uint64_t	*ft_set_subkeys(uint64_t *arr, t_ssl_opt options, const int *nbr)
{
	uint64_t	subkey;
	int			i;

	i = 0;
	subkey = options.key;
	while (i < 16)
	{
		subkey = ft_key_left_shift(subkey, nbr[i]);
		arr[i] = subkey;
		arr[i] = ft_permutator(subkey, g_compres_permut_order, 48);
		i++;
	}
	return (arr);
}

uint64_t	*ft_subkeys_generator(uint64_t *arr_subkeys, t_ssl_opt options)
{
	const int	nbr_of_shifts[16] = {1, 1, 2, 2, 2, 2, 2,
				2, 1, 2, 2, 2, 2, 2, 2, 1};
	char		*key;

	if (!options.k)
	{
		key = getpass("Enter the key in hex:\n");
		if (!check_des_key(key, &options))
			exit(0);
		if (key != NULL)
			ft_strdel(&key);
	}
	options.key = ft_permutator(options.key, g_key_permut_order, 64) >> 8 << 8;
	arr_subkeys = (uint64_t*)malloc(16 * sizeof(uint64_t));
	if (!arr_subkeys)
		return (NULL);
	return (ft_set_subkeys(arr_subkeys, options, nbr_of_shifts));
}

uint64_t	ft_block_join(uint8_t *data)
{
	uint64_t	res;
	int			i;

	i = 0;
	res = 0;
	while (i < 8)
	{
		res |= (uint64_t)data[i] << (64 - ((i + 1) * 8));
		i++;
	}
	return (res);
}

uint64_t	ft_s_box_substitution(uint64_t half_block, uint64_t subkey)
{
	int				i;
	unsigned char	in_bits;
	unsigned char	out_bits;
	uint64_t		res;

	i = 0;
	in_bits = 0;
	out_bits = 0;
	res = 0;
	half_block = ft_permutator(half_block, g_expans_permut_order, 48);
	half_block ^= subkey;
	while (i < 8)
	{
		out_bits = (((half_block >> (64 - (6 * i + 1))) & 1) << 1)
			| ((half_block >> (64 - (6 * i + 6)) & 1));
		in_bits = (half_block << (6 * i + 1)) >> 60;
		res |= (uint64_t)g_s_box_order[i][out_bits][in_bits] << (60 - (4 * i));
		i++;
	}
	res = ft_permutator(res, g_p_box_permut_order, 32);
	return (res);
}

uint64_t	ft_round(uint64_t data, uint64_t subkey)
{
	uint64_t	res;
	uint64_t	l1;
	uint64_t	r1;

	l1 = data << 32;
	r1 = (data >> 32 << 32) ^ ft_s_box_substitution(data << 32, subkey);
	res = l1 | (r1 >> 32);
	return (res);
}

uint64_t	ft_des_processing(uint64_t data, uint64_t *subkeys, t_modes mode)
{
	int i;

	i = 0;
	data = ft_permutator(data, g_init_permut_order, 64);
	while (i < 16)
	{
		if (mode == ENCRYPT)
			data = ft_round(data, subkeys[i]);
		else
			data = ft_round(data, subkeys[15 - i]);
		i++;
	}
	data = ((data << 32) | (data >> 32));
	data = ft_permutator(data, g_final_permut_order, 64);
	return (data);
}

void		ft_block_split(uint64_t block, uint8_t *data)
{
	int i;

	i = 0;
	while (i < 8)
	{
		data[i] = block >> (64 - ((i + 1) * 8));
		i++;
	}
}

void		ft_des_alg_loop(t_ssl_list *ptr, t_ssl_opt *opt, uint64_t *skeys)
{
	uint64_t	in_block;
	uint64_t	out_block;

	in_block = 0;
	out_block = 0;
	while (ptr)
	{
		if (ptr->data_size)
		{
			in_block = ft_block_join(ptr->data);
			if (opt->mode == ENCRYPT && opt->cipher != DES_ECB)
				in_block ^= opt->iv;
			out_block = ft_des_processing(in_block, skeys, opt->mode);
			if (opt->mode == DECODE && opt->cipher != DES_ECB)
				out_block ^= opt->iv;
			if (opt->mode == ENCRYPT)
				opt->iv = out_block;
			else
				opt->iv = in_block;
			ft_block_split(out_block, ptr->data);
		}
		ptr = ptr->next;
	}
}

void		ft_des_alg(t_ssl_list **head, t_ssl_opt *options, uint64_t *subkeys)
{
	char		*iv;
	t_ssl_list	*ptr;

	ptr = (*head);
	if (options->cipher != DES_ECB && !options->iv)
	{
		iv = getpass("Enter the iv in hex:\n");
		if (!check_des_iv(iv, options))
			exit(0);
		if (iv != NULL)
			ft_strdel(&iv);
	}
	ft_des_alg_loop(ptr, options, subkeys);
}

void		ft_des_start(t_ssl_list **head, t_ssl_opt options)
{
	uint64_t	*des_subkeys;

	des_subkeys = ft_subkeys_generator(des_subkeys, options);
	ft_des_alg(head, &options, des_subkeys);
	free(des_subkeys);
}

int			ft_ssl_des_main(t_ssl_list **head, t_ssl_opt options)
{
	ft_read_file(*head, options);
	if (options.a && options.mode == DECODE)
		ft_ssl_base64_main(head, options);
	if (options.mode == ENCRYPT)
		ft_ssl_padding(*head);
	ft_des_start(head, options);
	if (options.mode == DECODE)
		ft_ssl_unpadding(*head);
	if (options.a && options.mode == ENCRYPT)
		ft_ssl_base64_main(head, options);
	else
		ft_ssl_print_list(*head, options.out_fd);
	return (0);
}
