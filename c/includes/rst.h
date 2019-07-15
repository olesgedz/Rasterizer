#ifndef RST_H
#define RST_H

#define WIN_W 1200
#define WIN_H 600
#define CL_SILENCE_DEPRECATION
#include <sys/types.h>
#include "SDL2/SDL.h"
#include "libsdl.h"
#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <float.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <Cl/cl.h>
#endif

#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif
//#include "libmath.h"
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)


typedef struct s_game
{
	t_sdl *sdl;
	t_surface *image;
} t_game;

#endif