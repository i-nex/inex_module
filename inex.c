/**
 * @file    inex.c
 * @author  Michał Głowienka
 * @date    29 December 2019
 * @version 0.1 
 * @changelog
 *	   0.1 29 December 2019 - Initial version (Only model name and vendor_id)
 *		
 * @brief  The module was written for the needs of the I-Nex program, 
 *	   to improve the retrieval of information about processors.
 * 	   The module is for testing purposes only.
 * @see http://i-nex.linux.pl Home page of the I-Nex program.
*/

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/smp.h>
#include <linux/sysinfo.h>
#include <asm/cpufeature.h>

#define CM_SIZE 64
#define CV_SIZE 16

static char cpuname[CM_SIZE] = "Intel(R) Core(TM) i5-3230M CPU @ 2.60GHz";
static char cpuvendor[CV_SIZE] = "GenuineIntel";

/*
	 * Begin of set vendor_id
*/
void set_cpuvendor(struct cpuinfo_x86 *c) {
	strncpy(c->x86_vendor_id, cpuvendor, CV_SIZE-1);
	c->x86_vendor_id[CV_SIZE-1] = '\0';
	printk(KERN_INFO "I-Nex Set CPU vendor_id to: %s", cpuvendor);
}

void set_all_cpuvendor(void) {
    int i;
    for (i=0; i <= num_online_cpus(); i++) {
	set_cpuvendor(&cpu_data(i));
    }
}

static int cpuvendor_set_name(const char *buffer, const struct kernel_param *kp) {
    int len = strlen(strncpy(cpuvendor,buffer,CV_SIZE-1));
    cpuvendor[CV_SIZE-1] = '\0';
    set_all_cpuvendor();
    return len;
}

static int cpuvendor_get_name(char *buffer, const struct kernel_param *kp) {
    return strlen(strcpy(buffer, cpuvendor));
}

/*
	* End of set vendor_id
	* Begin of set model name
*/

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

/*
	* End of set model name
*/

int init_module() {
    
    printk(KERN_INFO "eloaders <eloaders@linux.pl> @ Loaded.\n");
    printk(KERN_INFO "Number of cpus available:%d\n", num_online_cpus());
    printk(KERN_INFO "Set model name: %s\n", cpuname);
    printk(KERN_INFO "Set vendor_id: %s\n", cpuvendor);
    
    set_all_names();
    set_all_cpuvendor();
    return 0;
}

void cleanup_module() {
    printk(KERN_INFO "eloaders <eloaders@linux.pl> @ Unloaded.\n");
}

MODULE_AUTHOR("eloaders <eloaders_at_linux_dot_pl> (http://i-nex.linux.pl)");
MODULE_VERSION("0.1");
MODULE_DESCRIPTION("The module is used to test processor logo detection in the I-Nex application.");
MODULE_LICENSE("GPL");
MODULE_INFO(inex, "I-Nex Kernel module for modification /proc/cpuinfo");


module_param_call(cpuname, inex_set_name, inex_get_name, NULL, S_IRUSR | S_IWUSR);
__MODULE_PARM_TYPE(cpuname, "string");
MODULE_PARM_DESC(cpuname, " Sets the processor model in the /proc/cpuinfo file. \n"
			  "\t\tExample model: Intel(R) Core(TM) i5-3230M CPU @ 2.60GHz \n"
			  "\t\tExample command: echo -n 'Intel(R) Core(TM) i5-3230M CPU @ 2.60GHz' >/sys/module/inex/parameters/cpuname ");
			  
module_param_call(cpuvendor, cpuvendor_set_name, cpuvendor_get_name, NULL, S_IRUSR | S_IWUSR);
__MODULE_PARM_TYPE(cpuvendor, "string");
MODULE_PARM_DESC(cpuvendor, " Sets the processor vendor_id in the /proc/cpuinfo file. \n"
			    "\t\tExample vendors:\n"
			    "\t\tGenuineIntel, "
			    "AuthenticAMD, "
			    "CyrixInstead, "
			    "NexGenDriven, \n"
			    "\t\tGenuineTMx86, "
			    "UMC UMC UMC , "
			    "CentaurHauls, "
			    "RiseRiseRise, \n"
			    "\t\tSiS SiS SiS , "
			    "Geode by NSC, "
			    "HygonGenuine \n"
			    "\n\t\tExample Command: echo -n 'GenuineIntel' >/sys/module/inex/parameters/cpuvendor ");		  
