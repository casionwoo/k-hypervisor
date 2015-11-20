#ifndef __VM_H__
#define __VM_H__

#include <stdio.h>
#include <stdlib.h>
#include <list.h>

#define SIZE_OF_NAME        32
#define VM_CREATE_FAILED    255
#define VM_NOT_EXISTED      254

typedef unsigned char vmid_t;
typedef enum vmcb_state {
    UNDEFINED,
    DEFINED,
    HALTED,
    RUNNING,
    SUSPENDED
} vmcb_state_t;

struct vmcb {
    vmid_t vmid;
    char name[SIZE_OF_NAME];
    unsigned char num_vcpus;

    // TODO(casionwoo) : Define vCPU
    // TODO(casionwoo) : Define vMEM
    // TODO(casionwoo) : Define vIRQ

    vmcb_state_t state;
    struct list_head head;
};

int vm_setup();
vmid_t vm_create(unsigned char num_vcpu);
vmcb_state_t vm_delete(vmid_t vmid);
vmcb_state_t vm_init(vmid_t vmid);
vmcb_state_t vm_start(vmid_t vmid);

// TODO(casionwoo) : vm_suspend, resume, shutdown
// TODO(casionwoo) : vm_save, vm_restore

struct vmcb *vm_find(vmid_t vmid);
void print_all_vm();

#endif /*__VM_H__*/

