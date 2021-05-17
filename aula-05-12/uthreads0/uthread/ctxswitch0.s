 
.extern running_thread
.extern cleanup_thread

/*-----------------------------------------------------------
 * void context_switch (PUTHREAD CurrentThread, PUTHREAD NextThread) 
 * in gcc linux 64 bits C/C++ compiler convention 
 * registers saved by callee are:
 *	R12
 *	R13
 *	R14
 *  R15
 *	RBX
 *	RBP
 *
 *  Parameters are passed by register
 *       CurrentThread - RDI
 *		 NextThread ---- RSI
 *-----------------------------------------------------------*/
.global context_switch
.global internal_exit

context_switch:
 
	#
	# Switch out the running CurrentThread, saving the execution context on the thread's own stack.   
	# The return address is atop the stack, having been placed there by the call to this function.
	#
	 
	push	%rbp
	push	%rbx
	push	%r12
	push	%r13
	push	%r14
	push	%r15
	
	#
	# Save ESP in CurrentThread->ThreadContext
	#
	mov	%rsp, (%rdi)  

	
	# Set new running_thread
	mov %rsi, running_thread(%rip)

	#
	# Load NextThread's context, starting by switching to its stack, where the registers are saved.
	#
	mov		(%rsi), %rsp 

	#
	# Restore NextThread Context
	#
	pop		%r15
	pop		%r14
	pop		%r13
	pop		%r12
	pop		%rbx
	pop		%rbp

	#
	# Jump to the return address saved on NextThread's stack when the function was called.
	#
	ret

 /*-----------------------------------------------------------
 * void internal_exit (PUTHREAD CurrentThread, PUTHREAD NextThread) 
 */
 internal_exit:
 

	
	# Set new running_thread
	mov %rsi, running_thread(%rip)

	#
	# Load NextThread's context, starting by switching to its stack, where the registers are saved.
	#
	mov		(%rsi), %rsp 

	# do CurrentThraed cleanup
	
	call cleanup_thread
	
	#
	# Restore NextThread Context
	#
	pop		%r15
	pop		%r14
	pop		%r13
	pop		%r12
	pop		%rbx
	pop		%rbp

	#
	# Jump to the return address saved on NextThread's stack when the function was called.
	#
	ret
