#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/kallsyms.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("LKM that inserts a new syscall (educational only)");

#define MY_SYSCALL_NR 333
static unsigned long **sys_call_table;

asmlinkage long (*orig_syscall)(void);

static void disable_wp(void) {
    unsigned long cr0 = read_cr0();
    clear_bit(16, (unsigned long *)&cr0);
    write_cr0(cr0);
}

static void enable_wp(void) {
    unsigned long cr0 = read_cr0();
    set_bit(16, (unsigned long *)&cr0);
    write_cr0(cr0);
}

asmlinkage long sys_mycall(void __user *buf, size_t len) {
    char msg[] = "Hello from kernel syscall!\n";
    size_t mlen = sizeof(msg);
    if (!buf)
        return -EINVAL;
    if (len < mlen)
        return -ENOSPC;
    if (copy_to_user(buf, msg, mlen))
        return -EFAULT;
    return mlen;
}

static int __init addsyscall_init(void) {
    sys_call_table = (unsigned long **)kallsyms_lookup_name("sys_call_table");
    if (!sys_call_table) {
        pr_err("Couldn't find sys_call_table\n");
        return -EFAULT;
    }

    pr_info("sys_call_table found at %p\n", sys_call_table);

    orig_syscall = (void *)sys_call_table[MY_SYSCALL_NR];

    disable_wp();
    sys_call_table[MY_SYSCALL_NR] = (unsigned long *)sys_mycall;
    enable_wp();

    pr_info("Inserted new syscall at %d\n", MY_SYSCALL_NR);
    return 0;
}

static void __exit addsyscall_exit(void) {
    if (!sys_call_table)
        return;
    disable_wp();
    sys_call_table[MY_SYSCALL_NR] = (unsigned long *)orig_syscall;
    enable_wp();
    pr_info("Restored original syscall at %d\n", MY_SYSCALL_NR);
}

module_init(addsyscall_init);
module_exit(addsyscall_exit);
