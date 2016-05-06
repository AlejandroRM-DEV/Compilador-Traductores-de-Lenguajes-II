.386
.model flat, stdcall
option casemap:none
include \masm32\macros\macros.asm
include \masm32\include\masm32.inc
include \masm32\include\kernel32.inc
includelib \masm32\lib\masm32.lib
includelib \masm32\lib\kernel32.lib
.data
.code
start:
	push 2
	push 2
	pop eax
	neg eax
	push eax
	pop ebx
	pop eax
	sub eax, ebx
	push eax
	push 4
	pop ebx
	pop eax
	xor edx, edx
	imul ebx
	push eax
	pop eax
	print str$(eax)
	print chr$(13,10)

exit
end start
