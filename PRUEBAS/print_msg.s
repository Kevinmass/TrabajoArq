# A program to be called from a C program
# Declaring data that doesn't change
.section .rodata
    string: .ascii  "Hello from assembler\n"
    length: .quad   . - string

# The actual code
.section .text
.global print
.type print, @function              #<-Important

print:
    mov     $1, %rax                # Move 1(write) into rax
    mov     $1, %rdi                # Move 1(fd stdOut) into rdi.
    lea     string(%rip), %rsi      # Move the _location_ of the string into rsi
    mov     length(%rip), %rdx      # Move the _length_ of the string into rdx
    syscall                         # Call the kernel
    ret                             # Return to the caller

.section .note.GNU-stack,"",@progbits # Indicate non-executable stack
