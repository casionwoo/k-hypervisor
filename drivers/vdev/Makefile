objs-y :=

objs-y += vdev_gicd.o
objs-y += vdev_timer.o
objs-$(CONFIG_VDEV_SAMPLE) += vdev_sample.o
objs-$(CONFIG_VDEV_SP804) += vdev_sp804.o
objs-$(CONFIG_VDEV_SYSREG) += vdev_sysreg.o
objs-$(CONFIG_VDEV_PL01X_SERIAL) += vdev_pl01x.o

obj-y += $(patsubst %, drivers/vdev/%, ${objs-y})

