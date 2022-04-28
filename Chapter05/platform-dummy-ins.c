#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/types.h>

static struct platform_device *pdev;

static int __init platform_dummy_char_add(void)
{
    int inst_id = 0; /* instance unique ID: base address would be a good choice */
    pdev = platform_device_alloc("platform-dummy-char", inst_id);
    if (!pdev) {
        pr_info("%s failed to allocate platform device\n", __FUNCTION__);
        return -1;
    }
    
    pr_info("%s platform_device_add pdev %p\n",__FUNCTION__, pdev);
    if (platform_device_add(pdev) != 0) {
        pr_info("%s failed to add platform device\n", __FUNCTION__);
        platform_device_del(pdev);
        return -1;
    }
    pr_info("%s platform_device_add pdev %p done\n",__FUNCTION__, pdev);
    return 0;
}

static void __exit platform_dummy_char_put(void)
{
    pr_info("%s platform_device_put pdev %p\n",__FUNCTION__, pdev);
    platform_device_put(pdev);
    pr_info("%s platform_device_put pdev %p done\n",__FUNCTION__, pdev);
    pr_info("%s platform_device_del pdev %p\n",__FUNCTION__, pdev);
    /* [Shengjiang: bug 0: we need to remove device to clean up.] */
    platform_device_del(pdev);
    pr_info("%s platform_device_del pdev %p done\n",__FUNCTION__, pdev);
}

module_init(platform_dummy_char_add);
module_exit(platform_dummy_char_put);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("John Madieu <john.madieu@gmail.com>");
