/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:42:50 by khalid            #+#    #+#             */
/*   Updated: 2024/01/10 17:33:01 by khalid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define MAX(a, b) (a > b ? a : b)
#define ABS(a) (a < 0 ? -a : a)

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, long x, long y, int color)
{
	char	*dst;
	if ((x >= WIDTH || x < 0) || (y >= HEIGHT || y < 0))
		return ;
	dst = img->addr + ABS((y * img->line_length + x * (img->bpp / 8)));
	*(unsigned int *)dst = color;
}

void	isometric(int *x, int *y, int z)
{
	int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = -z + (previous_x + previous_y) * sin(0.523599);
}

void one_point_perspective(int *x, int *y, int z) {
    int vanishing_point_x = WIDTH / 2;  // Adjust this value as needed
    int vanishing_point_y = HEIGHT / 2; // Adjust this value as needed
    float distance = 150; // Adjust this value for distance from the viewer

    if (z != 0) {
        *x = vanishing_point_x + ((*x - vanishing_point_x) * distance) / (distance + z);
        *y = vanishing_point_y + ((*y - vanishing_point_y) * distance) / (distance + z);
    }
}

void x_rotation(int *y, int *z, float *tita) {
    int original_y = *y;
    *y = original_y * cos(*tita) + *z * sin(*tita);
    *z = -original_y * sin(*tita) + *z * cos(*tita);
}

void y_rotation(int *x, int *z, float *beta) {
    int original_x = *x;
    *x = original_x * cos(*beta) + *z * sin(*beta);
    *z = -original_x * sin(*beta) + *z * cos(*beta);
}

void z_rotation(int *x, int *y, float *meta) {
    int original_x = *x;
    int original_y = *y;
    *x = original_x * cos(*meta) - original_y * sin(*meta);
    *y = original_x * sin(*meta) + original_y * cos(*meta);
}



void DDA(fdf *data, unsigned int color, int X0, int Y0, int X1, int Y1) 
{
    int dx;
    int dy; 
    int steps;
  	int		z;
	int		z1;

	// printf("x: %d\t", X0);
	// printf("y: %d\n", Y0);
	z = data->z_matrix[Y0][X0].z;
	z1 = data->z_matrix[Y1][X1].z;
	
	
	/* Rotation */
	x_rotation(&Y0, &z, &data->tita);
	x_rotation(&Y1, &z1, &data->tita);

	y_rotation(&X0, &z, &data->beta);
	y_rotation(&X1, &z1, &data->beta);

	z_rotation(&X0, &Y0, &data->meta);
	z_rotation(&X1, &Y1, &data->meta);

    /* adding 3D */
	// one_point_perspective(&X0, &Y0, z);
	// one_point_perspective(&X1, &Y1, z1);
	
	
    /* zoom */
    X0 *= data->zoom;
	X1 *= data->zoom;
	Y0 *= data->zoom;
	Y1 *= data->zoom;

	isometric(&X0, &Y0, z);
	isometric(&X1, &Y1, z1);
	

    /* shifting */
    X0 += data->shift_x;
	X1 += data->shift_x;
	Y0 += data->shift_y;
	Y1 += data->shift_y;

    // calculate steps required for generating pixels
    dx  = X1 - X0;
    dy = Y1 - Y0;
    steps = ABS(dx) > ABS(dy) ? ABS(dx) : ABS(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps;
    float Yinc = dy / (float)steps;
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0;
    // printf("xinc: %f\n", Xinc);
    // printf("yinc: %f\n", Yinc);
	// printf("step: %d\n", steps);
    for (int i = 0; i <= steps; i++) 
    {
		// if ((0 != z1 || 0 != z ) && 0xffffffff == color)
		// 	color = 0x00D70040;
        my_mlx_pixel_put(&data->mlx.img, (long) round(X), (long) round(Y), color);
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
    } 
} 

void	draw_map(fdf *data)
{
	unsigned x;
	unsigned y;

	y = 0;
	while (y < data->heigth)
	{
		x = 0;
		while (x < data->width)
		{
			if (x < data->width - 1)
				DDA(data, data->z_matrix[y][x].color, x, y, x + 1, y);
			if (y < data->heigth - 1)
				DDA(data, data->z_matrix[y][x].color, x, y, x , y + 1);
			x++;
		}
		y++;
	}
}