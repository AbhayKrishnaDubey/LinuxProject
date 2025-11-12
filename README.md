# A Driver that Adds a New System Call

## 📘 Subject
**Linux System and Shell Programming**

## 🎯 Objective
Create a loadable kernel module (LKM) that adds a new system call to the kernel.  
The system call will return a short message from kernel space to user space.  
This demonstrates how system calls are registered at runtime, how they can be called from userspace, and the related safety/compatibility concerns.

> ⚠️ **Warning:** Modifying the `sys_call_table` is version-sensitive and risky.  
> Run this code **only on a virtual machine** or a **test system**.

---

## 📦 Deliverables
1. Kernel module source: `addsyscall.c`
2. User-space test program: `test_addsyscall.c`
3. `Makefile` for building both.
4. This `README.md` report explaining design, implementation, and testing.

---

## 🧠 Design Overview
- Find the `sys_call_table` using `kallsyms_lookup_name`.
- Select an unused syscall number (here, **333**).
- Save the original syscall pointer.
- Replace it with our custom function (`sys_mycall`).
- Restore the original pointer when unloading the module.


🚀 Build & Run Instructions

Clone this repository or copy files into a new directory.

    make

Insert the kernel module:

    sudo insmod addsyscall.ko
    dmesg | tail

Run the test program:

    ./test_addsyscall

Remove the module:

    sudo rmmod addsyscall
    dmesg | tail


🧠 Discussion

Kernel compatibility: Modern kernels hide or restrict access to sys_call_table.

Risk: Patching the syscall table is unsafe and may cause kernel crashes.

Better alternatives: Use character devices, procfs, or netlink sockets for safe communication.

🧩 Report Template

| Section               | Description                                        |
| --------------------- | -------------------------------------------------- |
| **Title & Objective** | Short paragraph describing purpose                 |
| **Design**            | Explain how syscall table was located and modified |
| **Implementation**    | Summary of kernel and user-space code              |
| **Build & Run**       | Steps and commands used                            |
| **Test Results**      | Include sample `dmesg` and user output             |
| **Limitations**       | Discuss kernel security & safety issues            |
| **Conclusion**        | Summarize key learnings                            |


🏁 Conclusion

This assignment demonstrates low-level kernel programming concepts—how system calls are handled and why direct modification is discouraged in modern systems.
It provides a foundation for understanding safer kernel-user communication techniques like character devices or netlink sockets.
---

