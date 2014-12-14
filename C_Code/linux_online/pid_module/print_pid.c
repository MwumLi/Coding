#include <linux/list.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
static int print_pid(void)
{
	struct task_struct *task,*p;
	struct list_head *pos;
	int count = 0;
	
	printk("Hello World enterbegin;\n");
	task = &init_task;	
	printk("%s %d %d %d %ld\n", task->comm, task->state,task->pid,task->last_switch_count,task->policy);

	printk("name\tstate\tPID\tlast_switch_count\tpolicy字段\n");
	list_for_each(pos, &task->tasks) {
		p = list_entry(pos, struct task_struct, tasks);
		count++;
		printk("%s %d %d %d %ld\n", p->comm, p->state,p->pid,p->last_switch_count,p->policy);
	}
	printk("the number of process is:%d\n", count);
	return 0;
}
static void print_exit()
{
	printk(KERN_ALERT"End!");
}

module_init(print_pid);

module_exit(print_exit);


MODULE_AUTHOR("edsionte Wu");
MODULE_DESCRIPTION("This is a simple example!\n");

MODULE_ALIAS("A simplest example");

