/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frescurinha.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 20:24:34 by jucoelho          #+#    #+#             */
/*   Updated: 2025/08/10 20:35:27 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRESCURINHA_H
#define FRESCURINHA_H
#define GREEN "\001\033[1;32m\002"
#define RESET_COLOR "\001\033[0m\002"
#define GREEN_BG     "\001\033[42m\002"
#define ROSA "\001\033[48;5;206m\002"
#define BOLD "\001\033[1m\002"
#define BLUE "\001\033[34m\002"        // azul normal
#define BLUE_BOLD "\001\033[1;34m\002" // azul claro/brilhante
#define LIGHT_BLUE "\001\033[38;5;81m\002"


//#define MATRIX_FRESCURINHA "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_FRESCURINHA "\033[1;32m\033[40m minishell$ " RESET_COLOR
//#define MATRIX_FRESCURINHA "\033[30m" GREEN_BG " minishell$ " RESET_COLOR
#define FRESCURINHA LIGHT_BLUE "🥟 PetitCoquille$ " RESET_COLOR " "

#endif // FRESCURINHA