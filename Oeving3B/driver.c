/*****************************************************************************
 *
 * Øving 3 uCSysDes, driverkoden
 *
 *****************************************************************************/

/*includes*/
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

/*Module license*/
MODULE_LICENSE("Dual BSD/GPL");

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

/*AVR_32 GPIO struct*/
volatile avr32_pio_t *piob = &AVR32_PIOB;

/* Memory buffer*/
char *memory_buffer;
/*Defines*/

/*Switches	hex values*/
#define SW7 0x80
#define SW6 0x40
#define SW5 0x20
#define SW4 0x10
#define SW3 0x8
#define SW2 0x4
#define SW1 0x2
#define SW0 0x1

/*****************************************************************************/
/* init-funksjon (kalles når modul lastes) */

static int __init driver_init (void) {
  int result = 0;
  int driverMajor = 474;
	/* allokere device-nummer */ //WTF?
  result = register_chrdev(driverMajor,"STK1000_SwitchDriver",&driver_fops);
  if(result < 0){
    printk("<1> STK1000_SwitchDriver: cannot obtain driverMajor number %d\n",driverMajor);
    return result;
  }

  memory_buffer = kmalloc(1, GFP_KERNEL);
  if(!memory_buffer){
    result = -ENOMEM;
    goto fail;
  }

  memset(memory_buffer,0,1);
	printk("<1> Hello world!");
  printk("<1> Inserting STK1000_SwitchDriver module\n", );
  /* be om tilgang til I/O-porter */ //WTF?

  /* initialisere PIO-maskinvaren (som i øving 2) */ //Ehm... øving 2 initialiserte omtrent alt via interrupt_controller, så hvordan?
  short active = SW0+SW1+SW2+SW3+SW4+SW5+SW6+SW7;
  piob->per  = active; //Enable Register
  piob->puer  = active; //Pull-Up Enable Register
  pioB->ier  = active; //Interrupt Enable register
  piob->idr  = ~active; //Disable the rest

  /* registrere device i systemet (må gjøres når alt annet er initialisert) */


	return 0;
  fail:
    driver_exit();
    return result;
}

/*****************************************************************************/
/* exit-funksjon (kalles når modul fjernes fra systemet) */

static void __exit driver_exit (void) {
	printk("<1> Goodbye cruel world!");
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

static ssize_t driver_read (struct file *filp, char __user *buff, size_t count, loff_t *offp) {
	return 0;
}

/*---------------------------------------------------------------------------*/

static ssize_t driver_write (struct file *filp, const char __user *buff, size_t count, loff_t *offp) {
	return 0;
}

/*****************************************************************************/
/* modul-beskrivelsesmakroer */

module_init (driver_init);	/* angir hva som er init-funksjon */
module_exit (driver_exit);	/* angir hva som er exit-funksjon */

MODULE_LICENSE ("GPL");		 /* programlisens for modulen */
MODULE_DESCRIPTION ("");		/* tekstlig beskrivelse */
MODULE_VERSION ("");				/* versjonsnummer */
MODULE_AUTHOR ("");				 /* forfatter(e) */

