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
  .open = driver_open,
  .release = driver_release
};

/* major & minor numre */


/*golbale variabler : */

volatile avr32_pio_t *piob = &AVR32_PIOB;  // LED
static int ledBitmask = 0x4001e700;
static int currentLedStatus = 0x00;

/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */

int say_hello(int error){
  if (error == 0)
    printk(KERN_ALERT "LED driver initiated!nn\n");
  else 
    printk(KERN_ALERT "error occured while initializing!\n");
  return 0;
}

int setup_LEDs(void){
  piob->per |= 0xfffffff & ledBitmask;
  piob->oer = 0xffffffff & ledBitmask;
  piob->codr = 0xffffffff & ledBitmask;
  piob->sodr = 0x00000000 & ledBitmask;
  return 0;
}

int light_LEDs(int newState){ //outside this function LED state vars always appear in "normal" 0xXX format
  currentLedStatus = newState;
  int encodedState = 0x0000 | (0x03 & newState) | (0x1e0 & (newState << 2)) | (0x400000 & (newState << 15));
  printk(KERN_ALERT "encodedState is %x", encodedState);
  piob->codr = (0xffff << 8) & ledBitmask;
  piob->sodr = (encodedState << 8) & ledBitmask; 
  printk(KERN_ALERT "written to sodr: %x", (encodedState << 8) & ledBitmask);
  return 0; 
}

static int __init driver_init (void) {
  /* allokere device-nummer */

  /* be om tilgang til I/O-porter */
  
  /* initialisere PIO-maskinvaren (som i øving 2) */
 
  /* registrere device i systemet (må gjøres når alt annet er initialisert) */
  setup_LEDs();
  light_LEDs(0xaa);
  

  say_hello(register_chrdev_region(65, 1, "driver"));
  printk(KERN_ALERT, "%d\n", register_chrdev(65, "driver", &driver_fops));
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
  return 0;
}

/*---------------------------------------------------------------------------*/

static int driver_release (struct inode *inode, struct file *filp) {
  return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_read (struct file *filp, char __user *buff,
              size_t count, loff_t *offp) {
  return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff,
               size_t count, loff_t *offp) {
  printk(KERN_ALERT "write called \n");

  light_LEDs(0x66);
  //light_LEDs(ledsToLight);
  return 0;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);  /* angir hva som er init-funksjon */
module_exit (driver_exit);  /* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");     /* programlisens for modulen */
MODULE_DESCRIPTION ("");    /* tekstlig beskrivelse */
MODULE_VERSION ("");        /* versjonsnummer */
MODULE_AUTHOR ("");         /* forfatter(e) */

