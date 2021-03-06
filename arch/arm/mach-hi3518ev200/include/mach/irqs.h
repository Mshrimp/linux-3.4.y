#ifndef __HI_IRQS_H__
#define __HI_IRQS_H__

#define HISI_VIC_IRQ_START		(0)

#define INTNR_WATCHDOG			(HISI_VIC_IRQ_START + 1)

#define INTNR_TIMER_0			(HISI_VIC_IRQ_START + 3)
#define INTNR_TIMER_1			(HISI_VIC_IRQ_START + 3)
#define INTNR_TIMER_2			(HISI_VIC_IRQ_START + 4)
#define INTNR_TIMER_3			(HISI_VIC_IRQ_START + 4)

#define INTNR_UART0				(HISI_VIC_IRQ_START + 5)
#define INTNR_UART1				(HISI_VIC_IRQ_START + 30)
#define INTNR_UART2				(HISI_VIC_IRQ_START + 25)

#define NR_IRQS					(HISI_VIC_IRQ_START + 32)
#endif
