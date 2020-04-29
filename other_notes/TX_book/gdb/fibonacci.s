	.text
	.file	"fibonacci.cpp"
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function __cxx_global_var_init
	.type	__cxx_global_var_init,@function
__cxx_global_var_init:                  # @__cxx_global_var_init
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	movl	$_ZStL8__ioinit, %edi
	callq	_ZNSt8ios_base4InitC1Ev
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	movl	$_ZStL8__ioinit, %esi
	movl	$__dso_handle, %edx
	popq	%rax
	jmp	__cxa_atexit            # TAILCALL
.Lfunc_end0:
	.size	__cxx_global_var_init, .Lfunc_end0-__cxx_global_var_init
	.cfi_endproc
                                        # -- End function
	.text
	.globl	_Z4funci                # -- Begin function _Z4funci
	.p2align	4, 0x90
	.type	_Z4funci,@function
_Z4funci:                               # @_Z4funci
	.cfi_startproc
# %bb.0:
                                        # kill: def %edi killed %edi def %rdi
	testl	%edi, %edi
	jle	.LBB1_1
# %bb.2:
	leal	-1(%rdi), %eax
	leal	-2(%rdi), %ecx
	imulq	%rax, %rcx
	shrq	%rcx
	leal	(%rcx,%rdi,2), %eax
	addl	$-1, %eax
	retq
.LBB1_1:
	xorl	%eax, %eax
	retq
.Lfunc_end1:
	.size	_Z4funci, .Lfunc_end1-_Z4funci
	.cfi_endproc
                                        # -- End function
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$48, %rsp
	.cfi_def_cfa_offset 64
	.cfi_offset %rbx, -16
	movabsq	$4294967296, %rax       # imm = 0x100000000
	movq	%rax, (%rsp)
	movl	$1, %eax
	movq	$-8, %rcx
	.p2align	4, 0x90
.LBB2_1:                                # =>This Inner Loop Header: Depth=1
	addl	32(%rsp,%rcx,4), %eax
	movl	%eax, 40(%rsp,%rcx,4)
	addq	$1, %rcx
	jne	.LBB2_1
# %bb.2:
	movl	$_ZSt4cout, %edi
	movl	$.L.str, %esi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movl	36(%rsp), %esi
	movq	%rax, %rdi
	callq	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	movl	$_ZSt4cout, %edi
	movl	$.L.str.1, %esi
	callq	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
	movq	%rax, %rbx
	movl	$9, %edi
	callq	_Z4funci
	movq	%rbx, %rdi
	movl	%eax, %esi
	callq	_ZNSolsEi
	movl	$_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_, %esi
	movq	%rax, %rdi
	callq	_ZNSolsEPFRSoS_E
	xorl	%eax, %eax
	addq	$48, %rsp
	popq	%rbx
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNSt11char_traitsIcE6lengthEPKc,"axG",@progbits,_ZNSt11char_traitsIcE6lengthEPKc,comdat
	.weak	_ZNSt11char_traitsIcE6lengthEPKc # -- Begin function _ZNSt11char_traitsIcE6lengthEPKc
	.p2align	4, 0x90
	.type	_ZNSt11char_traitsIcE6lengthEPKc,@function
_ZNSt11char_traitsIcE6lengthEPKc:       # @_ZNSt11char_traitsIcE6lengthEPKc
	.cfi_startproc
# %bb.0:
	jmp	strlen                  # TAILCALL
.Lfunc_end3:
	.size	_ZNSt11char_traitsIcE6lengthEPKc, .Lfunc_end3-_ZNSt11char_traitsIcE6lengthEPKc
	.cfi_endproc
                                        # -- End function
	.section	.text._ZStorSt12_Ios_IostateS_,"axG",@progbits,_ZStorSt12_Ios_IostateS_,comdat
	.weak	_ZStorSt12_Ios_IostateS_ # -- Begin function _ZStorSt12_Ios_IostateS_
	.p2align	4, 0x90
	.type	_ZStorSt12_Ios_IostateS_,@function
_ZStorSt12_Ios_IostateS_:               # @_ZStorSt12_Ios_IostateS_
	.cfi_startproc
# %bb.0:
	orl	%esi, %edi
	movl	%edi, %eax
	retq
.Lfunc_end4:
	.size	_ZStorSt12_Ios_IostateS_, .Lfunc_end4-_ZStorSt12_Ios_IostateS_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZSt13__check_facetISt5ctypeIcEERKT_PS3_,"axG",@progbits,_ZSt13__check_facetISt5ctypeIcEERKT_PS3_,comdat
	.weak	_ZSt13__check_facetISt5ctypeIcEERKT_PS3_ # -- Begin function _ZSt13__check_facetISt5ctypeIcEERKT_PS3_
	.p2align	4, 0x90
	.type	_ZSt13__check_facetISt5ctypeIcEERKT_PS3_,@function
_ZSt13__check_facetISt5ctypeIcEERKT_PS3_: # @_ZSt13__check_facetISt5ctypeIcEERKT_PS3_
	.cfi_startproc
# %bb.0:
	pushq	%rax
	.cfi_def_cfa_offset 16
	testq	%rdi, %rdi
	je	.LBB5_2
# %bb.1:
	movq	%rdi, %rax
	popq	%rcx
	retq
.LBB5_2:
	callq	_ZSt16__throw_bad_castv
.Lfunc_end5:
	.size	_ZSt13__check_facetISt5ctypeIcEERKT_PS3_, .Lfunc_end5-_ZSt13__check_facetISt5ctypeIcEERKT_PS3_
	.cfi_endproc
                                        # -- End function
	.section	.text._ZNKSt5ctypeIcE5widenEc,"axG",@progbits,_ZNKSt5ctypeIcE5widenEc,comdat
	.weak	_ZNKSt5ctypeIcE5widenEc # -- Begin function _ZNKSt5ctypeIcE5widenEc
	.p2align	4, 0x90
	.type	_ZNKSt5ctypeIcE5widenEc,@function
_ZNKSt5ctypeIcE5widenEc:                # @_ZNKSt5ctypeIcE5widenEc
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	%esi, %ebp
	movq	%rdi, %rbx
	cmpb	$0, 56(%rbx)
	je	.LBB6_2
# %bb.1:
	movzbl	%bpl, %eax
	movb	57(%rbx,%rax), %al
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
.LBB6_2:
	movq	%rbx, %rdi
	callq	_ZNKSt5ctypeIcE13_M_widen_initEv
	movq	(%rbx), %rax
	movq	48(%rax), %rax
	movsbl	%bpl, %esi
	movq	%rbx, %rdi
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	jmpq	*%rax                   # TAILCALL
.Lfunc_end6:
	.size	_ZNKSt5ctypeIcE5widenEc, .Lfunc_end6-_ZNKSt5ctypeIcE5widenEc
	.cfi_endproc
                                        # -- End function
	.section	.text.startup,"ax",@progbits
	.p2align	4, 0x90         # -- Begin function _GLOBAL__sub_I_fibonacci.cpp
	.type	_GLOBAL__sub_I_fibonacci.cpp,@function
_GLOBAL__sub_I_fibonacci.cpp:           # @_GLOBAL__sub_I_fibonacci.cpp
	.cfi_startproc
# %bb.0:
	jmp	__cxx_global_var_init   # TAILCALL
.Lfunc_end7:
	.size	_GLOBAL__sub_I_fibonacci.cpp, .Lfunc_end7-_GLOBAL__sub_I_fibonacci.cpp
	.cfi_endproc
                                        # -- End function
	.type	_ZStL8__ioinit,@object  # @_ZStL8__ioinit
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.hidden	__dso_handle
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"arr[9] = "
	.size	.L.str, 10

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"func(9) = "
	.size	.L.str.1, 11

	.section	.init_array,"aw",@init_array
	.p2align	3
	.quad	_GLOBAL__sub_I_fibonacci.cpp

	.ident	"clang version 6.0.0-1ubuntu2 (tags/RELEASE_600/final)"
	.section	".note.GNU-stack","",@progbits
