/*
 * Copyright (c) 2009 Altera Corporation, San Jose, California, USA.  
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 * DEALINGS IN THE SOFTWARE.
 * 
 * intel_niosv_irq.c - Support for Intel Nios V internal interrupt controller.
 *
 */

#include "sys/alt_irq.h"
#include "intel_niosv_irq.h"
#include "intel_niosv.h"
#include "alt_niosv_int_mode.h"

#ifdef ALT_CPU_INT_MODE
#if (ALT_CPU_INT_MODE == ALT_CPU_INT_MODE_VIC)
extern alt_u32 VIC_VECTOR_TABLE[];
#endif /* ALT_CPU_INT_MODE == ALT_CPU_INT_MODE_VIC */
#endif /* ALT_CPU_INT_MODE */

/*
 * To initialize the internal interrupt controller, just clear the mie
 * register so that all possible IRQs are disabled.
 */
void intel_niosv_irq_init(void) 
{
#if ALT_HAS_IRQ_SUPPORT
    NIOSV_CLR_CSR(NIOSV_MIE_CSR, NIOSV_MIE_MASK);

#ifdef ALT_CPU_INT_MODE
#if (ALT_CPU_INT_MODE == ALT_CPU_INT_MODE_VIC)
    /* Initialize mtvec with vector table for vic mode. */
    NIOSV_WRITE_CSR(NIOSV_MTVEC_CSR, (alt_u32) &VIC_VECTOR_TABLE | ALT_CPU_INT_MODE_VIC);
#endif /* ALT_CPU_INT_MODE == ALT_CPU_INT_MODE_VIC */
#endif /* ALT_CPU_INT_MODE */

#endif
}
