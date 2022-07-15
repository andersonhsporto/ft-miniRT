/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhigo-s <anhigo-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 22:26:07 by anhigo-s          #+#    #+#             */
/*   Updated: 2022/07/15 20:32:11 by anhigo-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector {
	double		x;
	double		y;
	double		z;
	double		w;
}	t_vector;

t_vector	vector_new(double x, double y, double z);
t_vector	vector_sum(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_mult(t_vector v1, double k);
t_vector	vector_div(t_vector v1, double k);

t_vector	vector_scale(t_vector v, double k);

double		vector_dot(t_vector v1, t_vector v2);
double		vector_mod(t_vector v);
double		vector_sin(t_vector v);
double		vector_cos(t_vector v);

t_vector	unit_vector(t_vector vector);
double		sum_square_vector(t_vector v);

#endif
