#ifndef ARCH_SYS_ARCH_H
#define ARCH_SYS_ARCH_H

#include "lwip/err.h"
#include "lwip/opt.h"
#include "lwip/sys.h"

typedef struct {
    // Definição mínima para sys_mutex_t
    int dummy;
} sys_mutex_t;

typedef struct {
    // Definição mínima para sys_sem_t
    int dummy;
} sys_sem_t;

typedef struct {
    // Definição mínima para sys_mbox_t
    int dummy;
} sys_mbox_t;

typedef struct {
    // Definição mínima para sys_thread_t
    int dummy;
} sys_thread_t;

typedef int sys_prot_t;
typedef void (*lwip_thread_fn)(void *arg);

err_t sys_mutex_new(sys_mutex_t *mutex);
void sys_mutex_lock(sys_mutex_t *mutex);
void sys_mutex_unlock(sys_mutex_t *mutex);
void sys_mutex_free(sys_mutex_t *mutex);
int sys_mutex_valid(sys_mutex_t *mutex);
void sys_mutex_set_invalid(sys_mutex_t *mutex);

err_t sys_sem_new(sys_sem_t *sem, u8_t count);
void sys_sem_signal(sys_sem_t *sem);
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout);
void sys_sem_free(sys_sem_t *sem);
int sys_sem_valid(sys_sem_t *sem);
void sys_sem_set_invalid(sys_sem_t *sem);

err_t sys_mbox_new(sys_mbox_t *mbox, int size);
void sys_mbox_post(sys_mbox_t *mbox, void *msg);
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg);
err_t sys_mbox_trypost_fromisr(sys_mbox_t *mbox, void *msg);
u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout);
u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg);
void sys_mbox_free(sys_mbox_t *mbox);
int sys_mbox_valid(sys_mbox_t *mbox);
void sys_mbox_set_invalid(sys_mbox_t *mbox);

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio);

sys_prot_t sys_arch_protect(void);
void sys_arch_unprotect(sys_prot_t pval);

#endif // ARCH_SYS_ARCH_H
