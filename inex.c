#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>

MODULE_LICENSE("GPL");

#define CM_SIZE 64

static char cpuname[CM_SIZE] = "Intel(R) Core(TM) i7-10700K CPU @ 5.10GHz";

void set_cpu_name(struct cpuinfo_x86 *c) {
	strncpy(c->x86_model_id, cpuname, CM_SIZE-1);
	c->x86_model_id[CM_SIZE-1] = '\0';
	printk(KERN_INFO "I-Nex Set CPU model name to: %s", cpuname);
}

void set_all_names(void) {
    int i;
    for (i=0; i <= num_online_cpus(); i++) {
	set_cpu_name(&cpu_data(i));
    }
}

static int inex_set_name(const char *buffer, const struct kernel_param *kp) {
    int len = strlen(strncpy(cpuname,buffer,CM_SIZE-1));
    cpuname[CM_SIZE-1] = '\0';
    set_all_names();
    return len;
}

static int inex_get_name(char *buffer, const struct kernel_param *kp) {
    return strlen(strcpy(buffer, cpuname));
}

int init_module() {
    
    printk(KERN_INFO "eloaders <eloaders@linux.pl> @ Loaded.\n");
    printk(KERN_INFO "Number of cpus available:%d\n", num_online_cpus());
    set_all_names();
    return 0;
}

void cleanup_module() {
    printk(KERN_INFO "eloaders <eloaders@linux.pl> @ Unloaded.\n");
}

MODULE_AUTHOR("Creator: eloaders <eloaders@linux.pl> I-Nex http://i-nex.linux.pl )");
MODULE_DESCRIPTION("Module created for testing the I-Nex application");

module_param_call(cpuname, inex_set_name, inex_get_name, NULL, S_IRUSR | S_IWUSR);
__MODULE_PARM_TYPE(cpuname, "string");
MODULE_PARM_DESC(cpuname, "Name of CPU");
