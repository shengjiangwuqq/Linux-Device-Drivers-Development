#include <linux/init.h>
#include <linux/module.h>

extern void b_service(void);

void a_service (void)
{
    pr_info("%s\n", __FUNCTION__);
}

__weak void b_service (void)
{
    pr_info("%s from mode A\n", __FUNCTION__);
}

static int a_init(void)
{
    pr_info("%s\n", __FUNCTION__);
    b_service();
    return 0;
}

static void a_exit(void)
{
    pr_info("%s\n", __FUNCTION__);
}

module_init(a_init);
module_exit(a_exit);
EXPORT_SYMBOL(a_service);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("");
