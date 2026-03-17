#include <fcntl.h>
#include <libevdev/libevdev.h>
#include <stdio.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

void readDevice(int i)
{
  std::string r = "/dev/input/event" + std::to_string(i);
  std::cout << r << std::endl;

  int fd = open(r.data(), O_RDONLY);

  if (fd < 0)
  {
    perror("open");
    return;
  }

  struct libevdev *dev = NULL;
  int rc = libevdev_new_from_fd(fd, &dev);

  if (rc < 0)
  {
    fprintf(stderr, "Failed to init libevdev (%s)\n", strerror(-rc));
    return;
  }

  printf("Device: %s\n", libevdev_get_name(dev));

  libevdev_free(dev);
  close(fd);
}

int main()
{
  for (int i = 0; i < 21; i++)
  {
    readDevice(i);
  }
}