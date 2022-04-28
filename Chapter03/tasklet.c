#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>    /* for tasklets api */

char tasklet_data[]="We use a string; but it could be pointer to a structure";

/* Tasklet handler, that just print the data */

/* [Shengjiang: bug 0 API update. we can only use data in tasklet_struct for private data.] */

void tasklet_function(struct tasklet_struct * t)
{
    pr_info( "%s\n", (char *)t->data );
    return;
}

/* [Shengjiang: bug 0 API update.] */

DECLARE_TASKLET(my_tasklet, tasklet_function);

static int __init my_init( void )
{
    /* append private data */
    /* [Shengjiang: bug 0 API update.] */
    my_tasklet.data = (unsigned long) &tasklet_data;
    /* Schedule the handler */
    tasklet_schedule( &my_tasklet );
    pr_info("tasklet example\n");
    return 0;
}

void my_exit( void )
{
    /* Stop the tasklet before we exit */
    tasklet_kill( &my_tasklet );
    pr_info("tasklet example cleanup\n");
    return;
}

module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>");
MODULE_LICENSE("GPL");
