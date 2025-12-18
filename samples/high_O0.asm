# This is the assembly code:
<func0>:
push   %rbp
mov    %rsp,%rbp
sub    $0x30,%rsp
mov    $0x402008,%edi
call   401040 <puts@plt>
movabs $0x48c0314890909090,%rax
31 c0 48
movabs $0xd23148f63148ff31,%rdx
48 31 d2
mov    %rax,-0x30(%rbp)
mov    %rdx,-0x28(%rbp)
movb   $0xc3,-0x20(%rbp)
mov    $0x11,%esi
mov    $0x402038,%edi
mov    $0x0,%eax
call   401050 <printf@plt>
mov    $0x100,%edi
call   401080 <malloc@plt>
mov    %rax,-0x18(%rbp)
cmpq   $0x0,-0x18(%rbp)
jne    4011d6 <func0+0x80>
mov    0x2ea8(%rip),%rax
mov    %rax,%rcx
mov    $0xe,%edx
mov    $0x1,%esi
mov    $0x40205b,%edi
call   401090 <fwrite@plt>
mov    $0x1,%eax
jmp    401250 <func0+0xfa>
mov    -0x18(%rbp),%rax
mov    $0x100,%edx
mov    $0x90,%esi
mov    %rax,%rdi
call   401060 <memset@plt>
movq   $0x0,-0x8(%rbp)
movq   $0x0,-0x10(%rbp)
jmp    401218 <func0+0xc2>
lea    -0x30(%rbp),%rdx
mov    -0x10(%rbp),%rax
add    %rdx,%rax
movzbl (%rax),%eax
movzbl %al,%eax
add    %rax,-0x8(%rbp)
addq   $0x1,-0x10(%rbp)
cmpq   $0x10,-0x10(%rbp)
jbe    4011fe <func0+0xa8>
mov    -0x8(%rbp),%rax
mov    %rax,%rsi
mov    $0x402070,%edi
mov    $0x0,%eax
call   401050 <printf@plt>
mov    -0x18(%rbp),%rax
mov    %rax,%rdi
call   401030 <free@plt>
mov    $0x402091,%edi
call   401040 <puts@plt>
mov    $0x0,%eax
leave
ret
# What is the source code?
