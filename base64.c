/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 09:55:20 by gvynogra          #+#    #+#             */
/*   Updated: 2018/07/21 10:15:54 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned char g_base[64] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e',
	'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
	'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2',
	'3', '4', '5', '6', '7', '8', '9', '+', '/'};

void		ft_enc_move(uint8_t *a, uint8_t *b)
{
	b[1] |= a[1] >> 4;
	b[2] = a[1] << 4;
	b[2] = b[2] >> 2;
	b[2] |= a[2] >> 6;
	b[3] = a[2] << 2;
	b[3] = b[3] >> 2;
}

void		ft_enc_base64_alg(uint8_t *a, int n, uint8_t *dest, size_t nbr)
{
	uint8_t	b[4];
	int		c;

	c = 0;
	ft_bzero(b, 4);
	b[0] = a[0] >> 2;
	b[1] = a[0] << 6;
	b[1] = b[1] >> 2;
	if (n > 1)
		ft_enc_move(a, b);
	while (c < 4)
	{
		if (n == 1 && c > 1)
			dest[nbr] = '=';
		else if (n == 2 && c == 3)
			dest[nbr] = '=';
		else
			dest[nbr] = g_base[b[c]];
		c++;
		nbr++;
	}
}

uint8_t		*ft_encrypt_base64(uint8_t *arr, size_t *len)
{
	uint8_t		*dest;
	int			i;
	uint8_t		*ptr;
	size_t		index;

	index = 0;
	i = 0;
	ptr = arr;
	dest = (uint8_t*)ft_memalloc(*len + *len / 3 + *len % 3);
	while (i < *len)
	{
		if (*len - i < 3)
			ft_enc_base64_alg(ptr, *len - i, dest, index);
		else
			ft_enc_base64_alg(ptr, 3, dest, index);
		index += 4;
		ptr += 3;
		i += 3;
	}
	*len = index;
	return (dest);
}

void	ft_check_index(int *i, uint8_t *index, int j)
{
	if (*i == 64)
	{
		ft_printf("bad symbol\n");
		exit(1);
	}
	index[j] = *i;
	*i = 0;
}

void	ft_decode_move(uint8_t *a, uint8_t *index, int n)
{
	a[0] = index[0] << 2;
	if (n >= 2)
	{
		a[0] |= index[1] >> 4;
		a[1] = index[1] << 4;
	}
	if (n >= 3)
	{
		a[1] |= index[2] >> 2;
		a[2] = index[2] << 6;
	}
	if (n == 4)
		a[2] |= index[3] << 2 >> 2;
}

void	ft_check_count(uint8_t *b, int *c)
{
	if (b[2] == '=')
		*c = 1;
	else if (b[3] == '=')
		*c = 2;
}

void	ft_set_index(uint8_t *b, int j, uint8_t *index)
{
	int i;

	i = 0;
	while (g_base[i] != b[j] && i < 64)
		i++;
	ft_check_index(&i, index, j);
}

int		ft_decode_base64_alg(uint8_t *b, int n, uint8_t *dest, size_t nbr)
{
	uint8_t	a[3];
	uint8_t	index[4];
	int		c;

	c = 0;
	ft_bzero(a, 3);
	ft_bzero(index, 4);
	if (n >= 1)
		ft_set_index(b, 0, index);
	if (n >= 2 && b[1] != '=')
		ft_set_index(b, 1, index);
	if (n >= 3 && b[2] != '=')
		ft_set_index(b, 2, index);
	if (n == 4 && b[3] != '=')
		ft_set_index(b, 3, index);
	ft_decode_move(a, index, n);
	while (c < 3 && n > 1)
	{
		dest[nbr] = a[c];
		nbr++;
		n--;
		c++;
	}
	ft_check_count(b, &c);
	return (c);
}

size_t		ft_get_list_size(t_ssl_list *head)
{
	size_t res;

	res = 0;
	while (head)
	{
		res += head->data_size;
		head = head->next;
	}
	return (res);
}

size_t		ft_decode_loop(t_ssl_list *hd, uint8_t *buf, uint8_t *dst, size_t i)
{
	int		written;

	written = 0;
	while (hd)
	{
		if (hd->data_size)
		{
			written = 0;
			if (hd->data_size >= 4)
			{
				ft_bzero(buf, 4);
				ft_ssl_fill_data(buf, hd->data, 0, 4);
				written = 4;
				i += ft_decode_base64_alg(buf, 4, dst, i);
			}
			ft_bzero(buf, 4);
			ft_ssl_fill_data(buf, hd->data, written,
					hd->data_size - written);
			i += ft_decode_base64_alg(buf, hd->data_size - written, dst, i);
		}
		hd = hd->next;
	}
	return (i);
}

uint8_t		*ft_decode_base64(t_ssl_list *head, size_t *size, t_ssl_opt options)
{
	uint8_t	buf[4];
	uint8_t	*dest;
	size_t	i;

	i = 0;
	if (!(dest = (uint8_t*)ft_memalloc((*size + 1) * sizeof(uint8_t))))
		exit(0);
	i += ft_decode_loop(head, buf, dest, 0);
	if (options.a)
		i = i - (i % 4);
	*size = i;
	return (dest);
}

void		ft_del_elem(t_ssl_list *head)
{
	t_ssl_list *prev;

	prev = NULL;
	if (head && head->next)
	{
		prev = head;
		if (head->next)
			head = head->next;
		free(prev);
	}
}

void		ft_ssl_list_del(t_ssl_list **head)
{
	t_ssl_list	*tmp;

	while ((*head)->next)
	{
		tmp = (*head)->next;
		ft_del_elem(*head);
		*head = tmp;
	}
	free(*head);
	(*head) = NULL;
}

t_ssl_list	*ft_arr_to_list(t_ssl_list **head, uint8_t *arr, size_t len)
{
	size_t	index;
	uint8_t	buf[8];

	index = 0;
	ft_ssl_list_del(head);
	if (!((*head) = (t_ssl_list*)ft_memalloc(sizeof(t_ssl_list))))
		exit(0);
	while (index < (len - len % 8))
	{
		ft_ssl_fill_data(buf, arr, index, 8);
		ft_ssl_lst_push_back((*head), buf, 8);
		index += 8;
		if ((len - index) && (len - index) < 8)
		{
			ft_ssl_fill_data(buf, arr, index, len - index);
			ft_ssl_lst_push_back((*head), buf, len - index);
			index += len - index;
		}
	}
	if (index < len)
	{
		ft_ssl_fill_data(buf, arr, index, len - index);
		ft_ssl_lst_push_back((*head), buf, len - index);
	}
	return (*head);
}

uint8_t		*ft_list_to_arr(t_ssl_list *head, size_t size)
{
	uint8_t *ptr;
	uint8_t *arr;

	arr = (uint8_t*)ft_memalloc(size + 1);
	if (!arr)
		exit(0);
	ptr = arr;
	while (head)
	{
		ft_ssl_fill_data(ptr, head->data, 0, head->data_size);
		ptr += head->data_size;
		head = head->next;
	}
	return (arr);
}

void		ft_ssl_print_list(t_ssl_list *head, int fd)
{
	t_ssl_list	*ptr;

	ptr = head;
	while (ptr)
	{
		if (ptr->data_size)
			write(fd, ptr->data, ptr->data_size);
		ptr = ptr->next;
	}
}

void		ft_ssl_output(t_ssl_list *hd, uint8_t *arr, t_ssl_opt op, size_t n)
{
	int	i;

	i = 0;
	if (op.mode == DECODE)
		ft_ssl_print_list(hd, op.out_fd);
	else
	{
		while (i < n)
		{
			ft_putchar_fd(arr[i], op.out_fd);
			i++;
			if (op.a && op.mode == ENCRYPT && (i % 64) == 0)
				ft_putchar_fd('\n', op.out_fd);
		}
		free(arr);
		ft_putchar_fd('\n', op.out_fd);
	}
}

int			ft_ssl_base64_main(t_ssl_list **head, t_ssl_opt options)
{
	uint8_t	*arr;
	uint8_t	*ciphertext;
	size_t	size;

	if (options.cipher == BASE64)
		ft_read_file(*head, options);
	size = ft_get_list_size(*head);
	if (options.mode == DECODE)
	{
		arr = ft_decode_base64(*head, &size, options);
		*head = ft_arr_to_list(head, arr, size);
		free(arr);
	}
	else
	{
		arr = ft_list_to_arr(*head, size);
		ciphertext = ft_encrypt_base64(arr, &size);
		free(arr);
	}
	if (options.cipher == BASE64 || options.mode == ENCRYPT)
		ft_ssl_output(*head, ciphertext, options, size);
	return (0);
}
