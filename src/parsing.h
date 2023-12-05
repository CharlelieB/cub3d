/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbessonn <cbessonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:10:35 by cbessonn          #+#    #+#             */
/*   Updated: 2023/12/05 16:24:16 by cbessonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

int		ft_atoi_overflow(const char *nptr);
bool	is_empty(char *str);
int		is_space(char c);
int		rgb_to_hexa(unsigned char r, unsigned char g, unsigned char b);
void	free_map(char **map, int size);
bool	ft_realloc(t_parsing *parsing);

bool	map_check_assets(t_parsing *parsing, t_game *game);
void	map_check_format(char *filename);
bool	map_parse(int fd, t_parsing *parsing, t_game *game);
bool	flood_fill(t_game *game, int x, int y);
void	free_stack_array_ptr(char *array[], int size);
bool	map_edit(t_parsing *parsing, t_game *game);

#endif