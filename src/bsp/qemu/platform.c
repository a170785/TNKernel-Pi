/*        Copyright (c) 20011, Simon Stapleton (simon.stapleton@gmail.com)        */
/*                                                                                */
/*                              All rights reserved.                              */
/*                                                                                */
/* Redistribution  and  use   in  source  and  binary  forms,   with  or  without */
/* modification, are permitted provided that the following conditions are met:    */
/*                                                                                */
/* Redistributions of  source code must  retain the above copyright  notice, this */
/* list of conditions and the following disclaimer.                               */
/*                                                                                */
/* Redistributions in binary form must reproduce the above copyright notice, this */
/* list of conditions and the following disclaimer in the documentation and/or    */
/* other materials provided with the distribution.                                */
/*                                                                                */
/* Neither the name of  the developer nor the names of  other contributors may be */
/* used  to  endorse or  promote  products  derived  from this  software  without */
/* specific prior written permission.                                             */
/*                                                                                */
/* THIS SOFTWARE  IS PROVIDED BY THE  COPYRIGHT HOLDERS AND CONTRIBUTORS  "AS IS" */
/* AND ANY  EXPRESS OR  IMPLIED WARRANTIES,  INCLUDING, BUT  NOT LIMITED  TO, THE */
/* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE */
/* DISCLAIMED. IN NO  EVENT SHALL THE COPYRIGHT HOLDER OR  CONTRIBUTORS BE LIABLE */
/* FOR  ANY DIRECT,  INDIRECT, INCIDENTAL,  SPECIAL, EXEMPLARY,  OR CONSEQUENTIAL */
/* DAMAGES (INCLUDING,  BUT NOT  LIMITED TO, PROCUREMENT  OF SUBSTITUTE  GOODS OR */
/* SERVICES; LOSS  OF USE,  DATA, OR PROFITS;  OR BUSINESS  INTERRUPTION) HOWEVER */
/* CAUSED AND ON ANY THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING  IN ANY WAY OUT OF THE USE */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.           */

#include "platform.h"

void irq_timer12(void) {
	if (sp804_masked_status(SP804_0_BASE)) {
		sp804_clear_interrupt(SP804_0_BASE);
		tn_arm_enable_interrupts();
		tn_tick_int_processing();
		tn_arm_disable_interrupts();
	} else {
		sp804_clear_interrupt(SP804_1_BASE);
		tn_arm_enable_interrupts();
		// Do something
		tn_arm_disable_interrupts();
	}
}

void set_system_clock_rate() {
	
}

void platform_startup() {
	set_system_clock_rate();
		
	// Set up timer 0 to generate clock ticks
	sp804_set_bg_load_value(SP804_0_BASE, TIMER_COUNT);
	sp804_set_load_value(SP804_0_BASE, TIMER_COUNT);
	sp804_set_mode(SP804_0_BASE, SP804_ENABLE | SP804_INT_ENBL | SP804_PERIODIC | SP804_SIZE_32 | SP804_PRE_16 | SP804_WRAP);
	
	irq_enable(INTERRUPT_TIMER12, &irq_timer12);
	
}