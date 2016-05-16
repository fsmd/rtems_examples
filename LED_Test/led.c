#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include <rtems.h>
#include <sys/ioccom.h>
#include <math.h>

#define  CONFIGURE_ENABLE_BSP_DRIVER
#include <bsp.h>

static void thread_ticks(rtems_task_argument arg);
extern void usart_initialize(int minor);
extern int usart_interrupt_write(int minor, const char *d, size_t n);

rtems_task Init(
  rtems_task_argument ignored
)
{
  const uint32_t led_table[] = {1u<<13, 1u<<14}; 
  int fd = open("/dev/led", O_WRONLY);
  int index = 0;
  rtems_id  task_tick;
  rtems_status_code sc;

  printf("Hello, Welcome to rtems's world\r\n");
  printk("-----LED TEST V1.00------\r\n");
  sc = rtems_task_create(
             rtems_build_name('t', 'i', 'c', 'k'),
             100,
             4096,
             RTEMS_PREEMPT | RTEMS_NO_TIMESLICE | RTEMS_ASR,
             RTEMS_LOCAL | RTEMS_NO_FLOATING_POINT,
             &task_tick
  );
  if (sc == RTEMS_SUCCESSFUL) {
     sc = rtems_task_start(task_tick, thread_ticks, 0);
     if (sc != RTEMS_SUCCESSFUL)
        printf("Start ticks thread failed\r\n");
  }
  
  //read(0, recvbuf, 3);
  //printf("Rtems RTOS start successful\r\n");
  
  for ( ; ; ) {     
     ioctl(fd, LED_DEVICE_OPEN, &led_table[index]);
     rtems_task_wake_after(50);
     ioctl(fd, LED_DEVICE_CLOSE, &led_table[index]);
     rtems_task_wake_after(1000);
     
     index = (index + 1) % 2;
     printf("Init thread: index = %d\r\n", index);
  }
}

static void thread_ticks(rtems_task_argument arg)
{
  int ticks = 0;
  double n1;
  double n2;
  double n3;
  double a = 1;
  
   
  for ( ; ; ) {
    n1 = sin(a);
    n2 = log10(n1);
    n3 = cos(n2);
    n3 = n3;
    //printf("Thread ticks: %d\r\n", );
    printf("n3: %.5lf\r\n", n3);
    printf("Thread ticks: %d\r\n", ticks++);
    rtems_task_wake_after(1000);
    if (a < 3.141592)
       a += 0.001;
    else
       a = 1;
  }
}

/*
 * This application has no device drivers.
 */
/* NOTICE: the clock driver is explicitly disabled */
#define CONFIGURE_APPLICATION_NEEDS_CLOCK_DRIVER //CONFIGURE_APPLICATION_DOES_NOT_NEED_CLOCK_DRIVER  
#define CONFIGURE_APPLICATION_NEEDS_CONSOLE_DRIVER

#define CONFIGURE_MAXIMUM_TASKS  3
#define CONFIGURE_MICROSECONDS_PER_TICK 1000
//#define CONFIGURE_FILESYSTEM_DEVFS
#define CONFIGURE_USE_MINIIMFS_AS_BASE_FILESYSTEM
//#define CONFIGURE_USE_DEVFS_AS_BASE_FILESYSTEM
#define CONFIGURE_DISABLE_NEWLIB_REENTRANCY
#define CONFIGURE_MAXIMUM_SEMAPHORES 10
#define CONFIGURE_LIBIO_MAXIMUM_FILE_DESCRIPTORS 5
#define CONFIGURE_MINIMUM_TASK_STACK_SIZE 4*1024
#define CONFIGURE_MAXIMUM_PRIORITY 255
#define CONFIGURE_EXECUTIVE_RAM_SIZE 50*1024

#define CONFIGURE_INIT
#define CONFIGURE_RTEMS_INIT_TASKS_TABLE
#include <rtems/confdefs.h>
