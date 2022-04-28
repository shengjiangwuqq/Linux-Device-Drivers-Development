# Platform device and driver

This code consists of converting the driver in chapter 4 into a platform
driver. After running `make` command, there will be two modules:

* platform-dummy-char.ko
* platform-dummy-ins.ko

The fist module is our platform driver. The second one is a basic module whose
aim is to create a platform device that will match the
`platform-dummy-char` driver.


Prior to testing our driver, one should load the following modules:

```bash
# insmod platform-dummy-char.ko
# insmod platform-dummy-ins.ko
```

Once the modules loaded, one can see below message in debug output:

```bash
$ dmesg
[...]
[33117.715597] dummy_char major number = 241
[33117.715662] dummy char module loaded
[33117.715670] platform-dummy-char device added
```

One can print additional information by listing the sysfs content of the device:

```bash
$ ls -l /sys/devices/platform/platform-dummy-char.0/
total 0
lrwxrwxrwx 1 root root    0 oct.  12 16:40 driver -> ../../../bus/platform/drivers/platform-dummy-char
-rw-r--r-- 1 root root 4096 oct.  12 16:42 driver_override
-r--r--r-- 1 root root 4096 oct.  12 16:42 modalias
drwxr-xr-x 2 root root    0 oct.  12 16:42 power
lrwxrwxrwx 1 root root    0 oct.  12 16:42 subsystem -> ../../../bus/platform
-rw-r--r-- 1 root root 4096 oct.  12 16:40 uevent
```

Or by using `udevadm` tool:

```bash
$ udevadm info /dev/dummy_char 
P: /devices/platform/platform-dummy-char.0/dummy_char_class/dummy_char
N: dummy_char
E: DEVNAME=/dev/dummy_char
E: DEVPATH=/devices/platform/platform-dummy-char.0/dummy_char_class/dummy_char
E: MAJOR=241
E: MINOR=0
E: SUBSYSTEM=dummy_char_class
```

Of course, the behaviour remains the same as the char device tested on chapter :

```bash
# cat /dev/dummy_char 
# echo "blabla" > /dev/dummy_char 
# rmmod dummy-char.ko 

$ dmesg
[...]
[ 6753.573560] dummy_char major number = 241
[ 6753.573611] dummy char module loaded
[ 6753.573622] platform-dummy-char device added
[ 7081.034607] Someone tried to open me
[ 7081.034641] Can't accept any data guy
[ 7081.034649] Someone closed me
[ 7084.861861] Someone tried to open me
[ 7084.861887] Nothing to read guy
[ 7084.861906] Someone closed me
```

## First platform driver, then platform device

```
$ sudo dmesg -C
$ sudo insmod platform-dummy-char.ko 
$ dmesg 
$ sudo insmod platform-dummy-ins.ko 
$ dmesg
[  310.030505] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02
[  310.030559] my_pdrv_probe pdev 00000000e5e7cb02
[  310.030562] dummy_char major number = 236
[  310.030600] my_pdrv_probe pdev 00000000e5e7cb02 done
[  310.030614] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02 done
$ sudo rmmod platform_dummy_ins 
$ dmesg
[  310.030505] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02
[  310.030559] my_pdrv_probe pdev 00000000e5e7cb02
[  310.030562] dummy_char major number = 236
[  310.030600] my_pdrv_probe pdev 00000000e5e7cb02 done
[  310.030614] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02 done
[  334.791009] platform_dummy_char_put platform_device_put pdev 00000000e5e7cb02
[  334.791012] platform_dummy_char_put platform_device_put pdev 00000000e5e7cb02 done
[  334.791013] platform_dummy_char_put platform_device_del pdev 00000000e5e7cb02
[  334.791027] my_pdrv_remove remove pdev 00000000e5e7cb02
[  334.791504] my_pdrv_remove remove pdev 00000000e5e7cb02 done
[  334.791511] platform_dummy_char_put platform_device_del pdev 00000000e5e7cb02 done
$ sudo rmmod platform_dummy_char 
$ dmesg
[  310.030505] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02
[  310.030559] my_pdrv_probe pdev 00000000e5e7cb02
[  310.030562] dummy_char major number = 236
[  310.030600] my_pdrv_probe pdev 00000000e5e7cb02 done
[  310.030614] platform_dummy_char_add platform_device_add pdev 00000000e5e7cb02 done
[  334.791009] platform_dummy_char_put platform_device_put pdev 00000000e5e7cb02
[  334.791012] platform_dummy_char_put platform_device_put pdev 00000000e5e7cb02 done
[  334.791013] platform_dummy_char_put platform_device_del pdev 00000000e5e7cb02
[  334.791027] my_pdrv_remove remove pdev 00000000e5e7cb02
[  334.791504] my_pdrv_remove remove pdev 00000000e5e7cb02 done
[  334.791511] platform_dummy_char_put platform_device_del pdev 00000000e5e7cb02 done
```

## First platform device, then platform driver

```
$ sudo dmesg -C
$ sudo rmmod platform_dummy_i^C 
$ sudo insmod platform-dummy-ins.ko 
$ dmesg
[  835.377799] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad
[  835.377844] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad done
$ sudo insmod platform-dummy-char.ko 
$ dmesg
[  835.377799] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad
[  835.377844] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad done
[  848.904555] my_pdrv_probe pdev 00000000a4ab44ad
[  848.904560] dummy_char major number = 236
[  848.904603] my_pdrv_probe pdev 00000000a4ab44ad done
$ sudo rmmod platform_dummy_char 
$ dmesg
[  835.377799] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad
[  835.377844] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad done
[  848.904555] my_pdrv_probe pdev 00000000a4ab44ad
[  848.904560] dummy_char major number = 236
[  848.904603] my_pdrv_probe pdev 00000000a4ab44ad done
[  899.117831] my_pdrv_remove remove pdev 00000000a4ab44ad
[  899.118688] my_pdrv_remove remove pdev 00000000a4ab44ad done
$ sudo rmmod platform_dummy_ins 
$ dmesg
[  835.377799] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad
[  835.377844] platform_dummy_char_add platform_device_add pdev 00000000a4ab44ad done
[  848.904555] my_pdrv_probe pdev 00000000a4ab44ad
[  848.904560] dummy_char major number = 236
[  848.904603] my_pdrv_probe pdev 00000000a4ab44ad done
[  899.117831] my_pdrv_remove remove pdev 00000000a4ab44ad
[  899.118688] my_pdrv_remove remove pdev 00000000a4ab44ad done
[  916.384091] platform_dummy_char_put platform_device_put pdev 00000000a4ab44ad
[  916.384094] platform_dummy_char_put platform_device_put pdev 00000000a4ab44ad done
[  916.384095] platform_dummy_char_put platform_device_del pdev 00000000a4ab44ad
[  916.384129] platform_dummy_char_put platform_device_del pdev 00000000a4ab44ad done
```