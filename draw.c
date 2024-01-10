/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khalid <khalid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:42:50 by khalid            #+#    #+#             */
/*   Updated: 2024/01/10 10:48:59 by khalid           ###   ########.fr       */
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

    /* shifting */
    X0 += data->shift_x;
	X1 += data->shift_x;
	Y0 += data->shift_y;
	Y1 += data->shift_y;


    /* zoom */
    X0 *= data->zoom;
	X1 *= data->zoom;
	Y0 *= data->zoom;
	Y1 *= data->zoom;

    /* adding 3D */
	isometric(&X0, &Y0, z);
	isometric(&X1, &Y1, z1);

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