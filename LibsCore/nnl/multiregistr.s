.text
.code16
.global multiregistr16
.type multiregistr16,@function
multiregistr16:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
pushl	%ebx
	pushl	%ecx
	pushl	%esi
	pushl	%edi

	xorl	%eax, %eax
   xorl	%ecx, %ecx
	xorl	%ebx, %ebx
	movl	8(%ebp), %edi
	movl	(%edi),%ebx
	movl	12(%ebp), %edi
	movl	(%edi),%ecx
	_CreateFDL


	popl	%edi
  	popl	%esi
  	popl	%ecx
popl	%ebx
  	popl	%eax
  	leave
	ret


.code32
.global multiregistr32
.type multiregistr32,@function
multiregistr32:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%eax
pushl	%ebx
	pushl	%ecx
	pushl	%esi
	pushl	%edi

	xorl	%eax, %eax
   xorl	%ecx, %ecx		#Параноявость
	xorl	%ebx, %ebx
	movl	8(%ebp), %edi
	movl	(%edi),%ebx
	movl	12(%ebp), %edi
	movl	(%edi),%ecx
	_CreateFDL


	popl	%edi
  	popl	%esi
  	popl	%ecx
popl	%ebx
  	popl	%eax
  	leave
	ret

