/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvynogra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 09:04:00 by gvynogra          #+#    #+#             */
/*   Updated: 2018/07/21 09:17:56 by gvynogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
#include <inttypes.h>
# include "libft/includes/libft.h"
# include "libft/includes/ft_printf.h"
# include "libft/includes/get_next_line.h"

typedef enum
{
	BASE64 = 0,
	DES,
	DES_ECB,
	DES_CBC,
	CIPHERS
}	t_ciphers;

typedef enum
{
	ENCRYPT = 0,
	DECODE,
	MODES
}	t_modes;

typedef struct			s_ssl_opt
{
	t_modes				mode;
	t_ciphers			cipher;
	int					a;
	int					i;
	int					o;
	int					k;
	int					v;
	int					s;
	int					in_fd;
	int					out_fd;
	uint64_t			key;
	uint64_t			iv;
}						t_ssl_opt;

typedef struct			s_ssl_list
{
	uint8_t				data[8];
	size_t				data_size;
	struct s_ssl_list	*next;
}						t_ssl_list;

typedef int(*t_ssl_pf) (t_ssl_list **data, t_ssl_opt options);

int						ft_base64(t_ssl_opt options);
int						ft_des_ecb(t_ssl_opt options);
int						ft_des_cbc(t_ssl_opt options);
int						check_des_key(char *key, t_ssl_opt *options);
void					ft_enc_base64(uint8_t *a, int n, t_ssl_opt option);
void					ft_padding(uint8_t *data, int n);
void					ft_ssl_write(uint8_t *data, t_ssl_opt options);
void					ft_block_split(uint64_t block, uint8_t *data);
uint64_t				ft_block_join(uint8_t *data);
uint64_t				ft_des_processing(uint64_t d, uint64_t *sk, t_modes m);
uint64_t				ft_round(uint64_t data, uint64_t subkey);
uint64_t				ft_s_box_substitution(uint64_t h_block, uint64_t skey);
uint64_t				*ft_subkeys_generator(uint64_t *skeys, t_ssl_opt opt);
uint64_t				ft_key_left_shift(uint64_t key, int n);
uint64_t				ft_permutator(uint64_t block, char *p_order, int n);
int						check_des_iv(char *iv, t_ssl_opt *options);
int						ft_ssl_base64_main(t_ssl_list **head, t_ssl_opt opt);
int						ft_ssl_des_main(t_ssl_list **head, t_ssl_opt options);
int						ft_ssl_fill_data(uint8_t *d, uint8_t *s, int st, int n);
void					ft_read_file(t_ssl_list *head, t_ssl_opt options);
size_t					ft_get_list_size(t_ssl_list *head);
void					ft_ssl_lst_push_back(t_ssl_list *h, uint8_t *b, int n);
void					ft_ssl_print_list(t_ssl_list *head, int fd);
void					ft_del_elem(t_ssl_list *head);
void					ft_ssl_list_del(t_ssl_list **head);

#endif
