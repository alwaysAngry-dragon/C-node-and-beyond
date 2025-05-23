section .data
    msg     db  'Hello World', 0
    msglen  equ $-msg - 1

section .text
    default rel         ; ← ADD THIS FOR RIP-RELATIVE ADDRESSING
    global Start
    extern ExitProcess, GetStdHandle, WriteConsoleA

Start:
    sub rsp, 0x28       ; Allocate shadow space

    ; GetStdHandle(-11 = STD_OUTPUT_HANDLE)
    mov rcx, -11
    call GetStdHandle

    ; WriteConsoleA(handle, msg, length, written, 0)
    mov rcx, rax        ; Handle
    lea rdx, [msg]      ; ← USE LEA INSTEAD OF MOV FOR 64-BIT ADDRESSES
    mov r8, msglen
    lea r9, [rsp+0x20] ; Dummy "written" pointer (we're ignoring it)
    mov qword [rsp+0x20], 0
    call WriteConsoleA

    add rsp, 0x28       ; Cleanup shadow space
    xor ecx, ecx
    call ExitProcess