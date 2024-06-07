#include "cub3d.h"

int main(int argc, char *argv[])
{
  void *ptr;
  void *win;
  argc = 0;
  argv = 0;

  ptr = mlx_init();
  win = mlx_new_window(ptr, 960, 960, "test");
  mlx_loop(ptr);
  return (0);
}