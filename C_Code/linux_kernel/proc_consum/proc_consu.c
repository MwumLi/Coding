#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sem.h>
#include <linux/semaphore.h>
#include <linux/sched.h>
#include <linux/kthread.h>
MODULE_LICENSE("GPL");

struct semaphore sem_producer;
struct semaphore sem_consumer;

char product[10];
int exit_flags;
int producer(void *product);
int consumer(void *product);

static int __init procon_init(void)
{
	printk(KERN_INFO"show producer and consumer\n");
	sema_init(&sem_producer, 1);
	sema_init(&sem_consumer, 0);
	exit_flags=0;
	/*
	kernel_thread(producer,product,CLONE_KERNEL);
	kernel_thread(consumer,product,CLONE_KERNEL);*/
	kthread_run(producer, product, "producer");
	kthread_run(consumer, product, "consumer");
	return 0;
}
static void __exit procon_exit(void)
{
	printk(KERN_INFO"exit producer and consumer\n");
}
/*
 * 生产者，负责生产十个产品
 */
int producer(void *p)
{
	char *product=(char *)p;
	int i;
	for(i=0;i<10;i++) {
		down(&sem_producer);
		snprintf(product,10,"product-%d",i);
		printk(KERN_INFO"producer produce %s\n",product);
		up(&sem_consumer);
	}
	exit_flags=1;
	return 0;
}
/*
 * 消费者，如果有产品，则消费产品
 */
int consumer(void *p)
{
	char *product=(char *)p;
	for(;;) {
		if(exit_flags) 
		  break;
		down(&sem_consumer);
		printk(KERN_INFO"consumer consume %s\n",product);
		memset(product,'\0',10);
		up(&sem_producer);
	}
	return 0;
}
module_init(procon_init);
module_exit(procon_exit);
MODULE_AUTHOR("MwumLi");
MODULE_DESCRIPTION("producer and consumer Module");
