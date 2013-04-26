/*****************************************************************************
 *
 * Øving 3 uCSysDes, driverkoden
 *
 *****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioport.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#include "ap7000.h"

/* prototyper */

static int __init driver_init(void);
static void __exit driver_exit(void);
static int driver_open (struct inode *inode, struct file *filp);
static int driver_release (struct inode *inode, struct file *filp);
static ssize_t driver_read (struct file *filp, char __user *buff,
                     size_t count, loff_t *offp);
static ssize_t driver_write (struct file *filp, const char __user *buff,
                      size_t count, loff_t *offp);

/* fops-struct */

static struct file_operations driver_fops = {
  .owner = THIS_MODULE,
  .read = driver_read,
  .write = driver_write,
  .open = NULL,
  .release = NULL
};

/* major & minor numre */


/*golbale variabler : */

volatile avr32_pio_t *piob = &AVR32_PIOB;  // LED

/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */

int say_hello(void){
    printk(KERN_ALERT "SW driver initiated! ?22\n");
  return 0;
}

int setup_SW(void){
  piob->per = 0xff;
  piob->puer = 0xff;
  return 0;
}
int read_SW(void){
  return piob->pdsr % 0x100;
}

static int __init driver_init (void) {
  int reg_succeded;
  setup_SW();
  say_hello();
  reg_succeded = register_chrdev(0, "swdriver", &driver_fops);
  printk(KERN_ALERT "reg success: %d\n", reg_succeded);

  int readSW = read_SW();
  //printk(KERN_ALERT "read buttons are: %x +10 = %x\n", readSW, readSW+10);
  return 0;
}

/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void) {
  printk(KERN_ALERT "goodbye world\n");
}

/*****************************************************************************/
/* fops-funksjoner */

static int driver_open (struct inode *inode, struct file *filp) {
  //printk(KERN_ALERT "SW driver loaded successfully\n");
  return 0;
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp) {
  //printk(KERN_ALERT "SW driver unloaded successfully\n");
  return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  /*printk(KERN_ALERT "entering read in driver\n");
  size_t out;
  char kernel_space_buffer[2];
  
  sprintf(kernel_space_buffer, "%x", read_SW());

  //sprintf(buff, "%x\n", read_SW());
  copy_to_user(buff, kernel_space_buffer, 2);
  out = 2;
  printk(KERN_ALERT "returning from read in driver %x\n", read_SW());

  */
  char myBuff[2];
  sprintf(myBuff, "%x", read_SW());

  size_t out;

  copy_to_user(buff, myBuff, 2);
  out = count;

  //printk(KERN_ALERT "read called, ouputting %x, out = %d\n", currentLedStatus, out);
  return out; 
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {
  printk(KERN_ALERT "NO WRITE ALLOWED\n");
  return -1;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);  /* angir hva som er init-funksjon */
module_exit (driver_exit);  /* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");     /* programlisens for modulen */
MODULE_DESCRIPTION ("");    /* tekstlig beskrivelse */
MODULE_VERSION ("");        /* versjonsnummer */
MODULE_AUTHOR ("");         /* forfatter(e) */

