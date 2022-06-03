#include <linux/init.h>
#include <linux/module.h>

extern void a_service(void);

void b_service (void)
{
    pr_info("%s\n", __FUNCTION__);
}

static int b_init(void)
{
    pr_info("%s\n", __FUNCTION__);
    a_service();
    return 0;
}

static void b_exit(void)
{
    pr_info("%s\n", __FUNCTION__);
}

module_init(b_init);
module_exit(b_exit);
EXPORT_SYMBOL(b_service);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
