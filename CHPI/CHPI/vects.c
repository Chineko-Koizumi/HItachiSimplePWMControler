/****************************************************************
KPIT Cummins Infosystems Ltd, Pune, India. - 05-Sept-2005.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************/
#ifdef DEBUG
	#define OFFSET 0x5A000000
#else
	#define OFFSET 0
#endif 


#include "inthandler.h"

extern void start (void);     /* Startup code (in start.s)  */
extern void stack (void);  /* stack from linker script   */

/**----------------------------------
**  Typedef for the function pointer
**-----------------------------------*/

typedef void (*fp) (void);
#define VECT_SECT          __attribute__ ((section (".vects")))

const fp HardwareVectors[] VECT_SECT = {
  start,                    /* 0  Power-on reset, Program counter (PC) */
(fp)0,			/*Reserved 1*/
(fp)0,			/*Reserved 2*/
(fp)0,			/*Reserved 3*/
(fp)0,			/*Reserved 4*/
(fp)0,			/*Reserved 5*/
(fp)0,			/*Reserved 6*/
(fp)0, //OFFSET+INT_NMI,
(fp)0, //OFFSET+INT_TRAP1,
(fp)0, //OFFSET+INT_TRAP2,
(fp)0, //OFFSET+INT_TRAP3,
(fp)0, //OFFSET+INT_TRAP4,
(fp)0, //OFFSET+INT_IRQ0,
(fp)0, //OFFSET+INT_IRQ1,
(fp)0, //OFFSET+INT_IRQ2,
(fp)0, //OFFSET+INT_IRQ3,
(fp)0, //OFFSET+INT_IRQ4,
(fp)0, //OFFSET+INT_IRQ5,
(fp)0,			/*Reserved 18*/
(fp)0,			/*Reserved 19*/
(fp)0, //OFFSET+INT_WOVI,
(fp)0, //OFFSET+INT_CMI,
(fp)0,			/*Reserved 22*/
(fp)0,			/*Reserved 23*/
(fp)0, //OFFSET+INT_IMIA0,
(fp)0, //OFFSET+INT_IMIB0,
(fp)0, //OFFSET+INT_OVI0,
(fp)0,			/*Reserved 27*/
(fp)0, //OFFSET+INT_IMIA1,
(fp)0, //OFFSET+INT_IMIB1,
(fp)0, //OFFSET+INT_OVI1,
(fp)0,			/*Reserved 31*/
(fp)0, //OFFSET+INT_IMIA2,
(fp)0, //OFFSET+INT_IMIB2,
(fp)0, //OFFSET+INT_OVI2,
(fp)0,			/*Reserved 35*/
(fp)0, //OFFSET+INT_IMIA3,
(fp)0, //OFFSET+INT_IMIB3,
(fp)0, //OFFSET+INT_OVI3,
(fp)0,			/*Reserved 39*/
(fp)0, //OFFSET+INT_IMIA4,
(fp)0, //OFFSET+INT_IMIB4,
(fp)0, //OFFSET+INT_OVI4,
(fp)0,			/*Reserved 43*/
(fp)0, //OFFSET+INT_DEND0A,
(fp)0, //OFFSET+INT_DEND0B,
(fp)0, //OFFSET+INT_DEND1A,
(fp)0, //OFFSET+INT_DEND1B,
(fp)0,			/*Reserved 48*/
(fp)0,			/*Reserved 49*/
(fp)0,			/*Reserved 50*/
(fp)0,			/*Reserved 51*/
(fp)0, //OFFSET+INT_ERI0,
(fp)0, //OFFSET+INT_RXI0,
(fp)0, //OFFSET+INT_TXI0,
(fp)0, //OFFSET+INT_TEI0,
(fp)0, //OFFSET+INT_ERI1,
(fp)0, //OFFSET+INT_RXI1,
(fp)0, //OFFSET+INT_TXI1,
(fp)0, //OFFSET+INT_TEI1,
(fp)0, //OFFSET+INT_ADI,
};
