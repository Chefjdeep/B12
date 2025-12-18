
asms/hello_O0.o:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	48 83 ec 08          	sub    $0x8,%rsp
  401004:	48 8b 05 d5 2f 00 00 	mov    0x2fd5(%rip),%rax        # 403fe0 <__gmon_start__@Base>
  40100b:	48 85 c0             	test   %rax,%rax
  40100e:	74 05                	je     401015 <_init+0x15>
  401010:	e8 3b 00 00 00       	call   401050 <__gmon_start__@plt>
  401015:	48 83 c4 08          	add    $0x8,%rsp
  401019:	c3                   	ret

Disassembly of section .plt:

0000000000401020 <puts@plt-0x10>:
  401020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 403ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 403ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <puts@plt>:
  401030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 404000 <puts@GLIBC_2.2.5>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401040 <__libc_start_main@plt>:
  401040:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 404008 <__libc_start_main@GLIBC_2.2.5>
  401046:	68 01 00 00 00       	push   $0x1
  40104b:	e9 d0 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .plt.got:

0000000000401050 <__gmon_start__@plt>:
  401050:	ff 25 8a 2f 00 00    	jmp    *0x2f8a(%rip)        # 403fe0 <__gmon_start__@Base>
  401056:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000401060 <_start>:
  401060:	31 ed                	xor    %ebp,%ebp
  401062:	49 89 d1             	mov    %rdx,%r9
  401065:	5e                   	pop    %rsi
  401066:	48 89 e2             	mov    %rsp,%rdx
  401069:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  40106d:	50                   	push   %rax
  40106e:	54                   	push   %rsp
  40106f:	49 c7 c0 a0 11 40 00 	mov    $0x4011a0,%r8
  401076:	48 c7 c1 30 11 40 00 	mov    $0x401130,%rcx
  40107d:	48 c7 c7 1b 11 40 00 	mov    $0x40111b,%rdi
  401084:	e8 b7 ff ff ff       	call   401040 <__libc_start_main@plt>
  401089:	f4                   	hlt

000000000040108a <deregister_tm_clones>:
  40108a:	b8 20 40 40 00       	mov    $0x404020,%eax
  40108f:	48 3d 20 40 40 00    	cmp    $0x404020,%rax
  401095:	74 11                	je     4010a8 <deregister_tm_clones+0x1e>
  401097:	b8 00 00 00 00       	mov    $0x0,%eax
  40109c:	48 85 c0             	test   %rax,%rax
  40109f:	74 07                	je     4010a8 <deregister_tm_clones+0x1e>
  4010a1:	bf 20 40 40 00       	mov    $0x404020,%edi
  4010a6:	ff e0                	jmp    *%rax
  4010a8:	c3                   	ret

00000000004010a9 <register_tm_clones>:
  4010a9:	be 20 40 40 00       	mov    $0x404020,%esi
  4010ae:	b9 02 00 00 00       	mov    $0x2,%ecx
  4010b3:	48 81 ee 20 40 40 00 	sub    $0x404020,%rsi
  4010ba:	48 c1 fe 03          	sar    $0x3,%rsi
  4010be:	48 89 f0             	mov    %rsi,%rax
  4010c1:	48 99                	cqto
  4010c3:	48 f7 f9             	idiv   %rcx
  4010c6:	48 89 c6             	mov    %rax,%rsi
  4010c9:	48 85 c0             	test   %rax,%rax
  4010cc:	74 11                	je     4010df <register_tm_clones+0x36>
  4010ce:	b8 00 00 00 00       	mov    $0x0,%eax
  4010d3:	48 85 c0             	test   %rax,%rax
  4010d6:	74 07                	je     4010df <register_tm_clones+0x36>
  4010d8:	bf 20 40 40 00       	mov    $0x404020,%edi
  4010dd:	ff e0                	jmp    *%rax
  4010df:	c3                   	ret

00000000004010e0 <__do_global_dtors_aux>:
  4010e0:	f3 0f 1e fa          	endbr64
  4010e4:	80 3d 35 2f 00 00 00 	cmpb   $0x0,0x2f35(%rip)        # 404020 <__TMC_END__>
  4010eb:	75 12                	jne    4010ff <__do_global_dtors_aux+0x1f>
  4010ed:	55                   	push   %rbp
  4010ee:	48 89 e5             	mov    %rsp,%rbp
  4010f1:	e8 94 ff ff ff       	call   40108a <deregister_tm_clones>
  4010f6:	c6 05 23 2f 00 00 01 	movb   $0x1,0x2f23(%rip)        # 404020 <__TMC_END__>
  4010fd:	5d                   	pop    %rbp
  4010fe:	c3                   	ret
  4010ff:	c3                   	ret

0000000000401100 <frame_dummy>:
  401100:	f3 0f 1e fa          	endbr64
  401104:	eb a3                	jmp    4010a9 <register_tm_clones>

0000000000401106 <func0>:
  401106:	55                   	push   %rbp
  401107:	48 89 e5             	mov    %rsp,%rbp
  40110a:	bf 04 20 40 00       	mov    $0x402004,%edi
  40110f:	e8 1c ff ff ff       	call   401030 <puts@plt>
  401114:	b8 00 00 00 00       	mov    $0x0,%eax
  401119:	5d                   	pop    %rbp
  40111a:	c3                   	ret

000000000040111b <main>:
  40111b:	55                   	push   %rbp
  40111c:	48 89 e5             	mov    %rsp,%rbp
  40111f:	b8 00 00 00 00       	mov    $0x0,%eax
  401124:	e8 dd ff ff ff       	call   401106 <func0>
  401129:	b8 00 00 00 00       	mov    $0x0,%eax
  40112e:	5d                   	pop    %rbp
  40112f:	c3                   	ret

0000000000401130 <__libc_csu_init>:
  401130:	41 57                	push   %r15
  401132:	4c 8d 3d a7 2c 00 00 	lea    0x2ca7(%rip),%r15        # 403de0 <__frame_dummy_init_array_entry>
  401139:	41 56                	push   %r14
  40113b:	41 55                	push   %r13
  40113d:	49 89 d5             	mov    %rdx,%r13
  401140:	41 54                	push   %r12
  401142:	49 89 f4             	mov    %rsi,%r12
  401145:	55                   	push   %rbp
  401146:	89 fd                	mov    %edi,%ebp
  401148:	53                   	push   %rbx
  401149:	48 83 ec 08          	sub    $0x8,%rsp
  40114d:	e8 ae fe ff ff       	call   401000 <_init>
  401152:	48 8d 05 8f 2c 00 00 	lea    0x2c8f(%rip),%rax        # 403de8 <__do_global_dtors_aux_fini_array_entry>
  401159:	49 89 c6             	mov    %rax,%r14
  40115c:	4d 29 fe             	sub    %r15,%r14
  40115f:	49 c1 fe 03          	sar    $0x3,%r14
  401163:	4c 39 f8             	cmp    %r15,%rax
  401166:	74 1d                	je     401185 <__libc_csu_init+0x55>
  401168:	31 db                	xor    %ebx,%ebx
  40116a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  401170:	4c 89 ea             	mov    %r13,%rdx
  401173:	4c 89 e6             	mov    %r12,%rsi
  401176:	89 ef                	mov    %ebp,%edi
  401178:	41 ff 14 df          	call   *(%r15,%rbx,8)
  40117c:	48 83 c3 01          	add    $0x1,%rbx
  401180:	4c 39 f3             	cmp    %r14,%rbx
  401183:	72 eb                	jb     401170 <__libc_csu_init+0x40>
  401185:	48 83 c4 08          	add    $0x8,%rsp
  401189:	5b                   	pop    %rbx
  40118a:	5d                   	pop    %rbp
  40118b:	41 5c                	pop    %r12
  40118d:	41 5d                	pop    %r13
  40118f:	41 5e                	pop    %r14
  401191:	41 5f                	pop    %r15
  401193:	c3                   	ret
  401194:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  40119b:	00 00 00 00 
  40119f:	90                   	nop

00000000004011a0 <__libc_csu_fini>:
  4011a0:	c3                   	ret

Disassembly of section .fini:

00000000004011a4 <_fini>:
  4011a4:	48 83 ec 08          	sub    $0x8,%rsp
  4011a8:	48 83 c4 08          	add    $0x8,%rsp
  4011ac:	c3                   	ret
