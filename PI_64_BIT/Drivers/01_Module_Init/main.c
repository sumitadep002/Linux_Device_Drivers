#include<linux/module.h>

/*Module's init entry point */
static int __init start_module(void)
{
   pr_info("Module Loaded succefully\n");
   return 0;
}

/*Module's cleanup entry point */
static void __exit exit_module(void)
{
  pr_info("Module unloaded succefulyl\n");
}

module_init(start_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("SUMIT ADEP");
MODULE_DESCRIPTION("A simple hello world kernel module");
MODULE_INFO(board,"PI");
