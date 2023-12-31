#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/jiffies.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "time"

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count,loff_t *pos);

static struct proc_ops my_fops = {
    .proc_read     = proc_read,
};

int proc_init(void){

	proc_create(PROC_NAME, 0, NULL, &my_fops);	
	printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	return 0;}

	void proc_exit(void)
{
	remove_proc_entry(PROC_NAME,NULL);
	printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);

}

ssize_t proc_read(struct file *file, char __user *user_buf, size_t count,loff_t *pos)
{
	int rv=0;
	char buffer[BUFFER_SIZE];
	static int completed=0;
	
	if(completed){
		completed=0;
		return 0;
	}
	unsigned long time;
	time=jiffies/HZ;
	completed=1;
	rv=sprintf(buffer,"Time, in seconds, since the module was loaded: %lu",time);
	copy_to_user(user_buf,buffer,rv);
	return rv;
}

module_init(proc_init);
module_exit(proc_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("How long is the module active for");
MODULE_AUTHOR("RARES");
