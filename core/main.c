#include <stdio.h>
#include <stdlib.h>
#include <core/vm/vm.h>
#include <core/scheduler.h>
#include <config.h>
#include "../arch/arm/init.h"
#include <core/timer.h>
#include <drivers/pmu.h>

static uint32_t smp_pen = 0;

void start_hypervisor()
{
    int i;
    uint8_t nr_vcpus = 2; // TODO: It will be read from configuration file.

    //uint32_t pcpu = smp_processor_id();
    uint32_t pcpu = read_mpidr() & 0x103;
    printf("%s:%d\n", __func__, __LINE__);

    if (pcpu == BOOTABLE_CPUID) {
        timemanager_init();
        sched_init();

        vm_setup();

        for (i = 0; i < NUM_GUESTS_STATIC; i++) {
            vmid_t vmid;

            if ((vmid = vm_create(nr_vcpus)) == VM_CREATE_FAILED) {
                printf("vm_create(vm[%d]) is failed\n", i);
                goto error;
            }
            if (vm_init(vmid) != HALTED) {
                printf("vm_init(vm[%d]) is failed\n", i);
                goto error;
            }
            if (vm_start(vmid) != RUNNING) {
                printf("vm_start(vm[%d]) is failed\n", i);
                goto error;
            }
        }
#if 0
        set_boot_addr();
        for(i=1; i<8; ++i) {
            boot_secondary(i);
           // init_secondary(i);
            printf("cpu[%d] is enabled on PCPU[%d]\n", i, pcpu);
        }
        smp_rmb();
        dsb_sev();
#endif
        printf("%s: cpu[%d] is enabled\n", __func__, pcpu);
        smp_pen = 1;
    } else {
        while (!smp_pen) ;
        printf("%s: cpu[%d] is enabled\n", __func__, pcpu);
    }

    /*
     * TODO: Add a function - return vmid or vcpu_id to execute for the first time.
     * TODO: Rename guest_sched_start to do_schedule or something others.
     *       do_schedule(vmid) or do_schedule(vcpu_id)
     */
    while(1);
    printf("sched_start!!!\n");
    sched_start();

    /* The code flow must not reach here */
error:
    printf("-------- [%s] ERROR: K-Hypervisor must not reach here\n", __func__);
    abort();
}
