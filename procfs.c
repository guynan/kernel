
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

MODULE_LICENCE("GPL");

#define ENTRY_NAME      "adjacency"
#define PARENT          NULL
#define PERMS           0644

struct proc_dir_entry* proc_entry;

int procfile_read(char* buf, char** buf_loc, off_t offset,
                int buf_len, int* eof, void* data);

int procfs_init(void)
{
        proc_entry = create_proc_entry(ENTRY_NAME, PERMS, PARENT);

        /* Check proc_entry isn't NULL */

        proc_entry->read_proc = procfile_read;
        proc_entry->mode = S_IFREG | S_IRUGO;
        proc_entry->uid = 0;
        proc_entry->gid = 0;
        proc_entry->size = 11;

        printk("/proc/%s created\n", ENTRY_NAME);

        return 0;

}

int procfile_read(char* buf, char** buf_loc, off_t offset,
                int buf_len, int* eof, void* data)
{

        int ret;

        printk("/proc/%s read called.\n", ENTRY_NAME);

        *eof = 1;
        ret = sprintf(buf, "Hello world!\n");

        return ret;

}

void procfs_exit(void)
{
        remove_proc_entry(ENTRY_NAME, NULL);
        printk("Removing /proc/%s.\n", ENTRY_NAME);

        return;

}

module_init(procfs_init);
module_exit(procfs_exit);
