
samples/high_O0.o:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	48 83 ec 08          	sub    $0x8,%rsp
  401004:	48 8b 05 d5 2f 00 00 	mov    0x2fd5(%rip),%rax        # 403fe0 <__gmon_start__@Base>
  40100b:	48 85 c0             	test   %rax,%rax
  40100e:	74 05                	je     401015 <_init+0x15>
  401010:	e8 8b 00 00 00       	call   4010a0 <__gmon_start__@plt>
  401015:	48 83 c4 08          	add    $0x8,%rsp
  401019:	c3                   	ret

Disassembly of section .plt:

0000000000401020 <free@plt-0x10>:
  401020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 403ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 403ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <free@plt>:
  401030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 404000 <free@GLIBC_2.2.5>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401040 <puts@plt>:
  401040:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 404008 <puts@GLIBC_2.2.5>
  401046:	68 01 00 00 00       	push   $0x1
  40104b:	e9 d0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401050 <printf@plt>:
  401050:	ff 25 ba 2f 00 00    	jmp    *0x2fba(%rip)        # 404010 <printf@GLIBC_2.2.5>
  401056:	68 02 00 00 00       	push   $0x2
  40105b:	e9 c0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401060 <memset@plt>:
  401060:	ff 25 b2 2f 00 00    	jmp    *0x2fb2(%rip)        # 404018 <memset@GLIBC_2.2.5>
  401066:	68 03 00 00 00       	push   $0x3
  40106b:	e9 b0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401070 <__libc_start_main@plt>:
  401070:	ff 25 aa 2f 00 00    	jmp    *0x2faa(%rip)        # 404020 <__libc_start_main@GLIBC_2.2.5>
  401076:	68 04 00 00 00       	push   $0x4
  40107b:	e9 a0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401080 <malloc@plt>:
  401080:	ff 25 a2 2f 00 00    	jmp    *0x2fa2(%rip)        # 404028 <malloc@GLIBC_2.2.5>
  401086:	68 05 00 00 00       	push   $0x5
  40108b:	e9 90 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401090 <fwrite@plt>:
  401090:	ff 25 9a 2f 00 00    	jmp    *0x2f9a(%rip)        # 404030 <fwrite@GLIBC_2.2.5>
  401096:	68 06 00 00 00       	push   $0x6
  40109b:	e9 80 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .plt.got:

00000000004010a0 <__gmon_start__@plt>:
  4010a0:	ff 25 3a 2f 00 00    	jmp    *0x2f3a(%rip)        # 403fe0 <__gmon_start__@Base>
  4010a6:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

00000000004010b0 <_start>:
  4010b0:	31 ed                	xor    %ebp,%ebp
  4010b2:	49 89 d1             	mov    %rdx,%r9
  4010b5:	5e                   	pop    %rsi
  4010b6:	48 89 e2             	mov    %rsp,%rdx
  4010b9:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4010bd:	50                   	push   %rax
  4010be:	54                   	push   %rsp
  4010bf:	49 c7 c0 d0 12 40 00 	mov    $0x4012d0,%r8
  4010c6:	48 c7 c1 60 12 40 00 	mov    $0x401260,%rcx
  4010cd:	48 c7 c7 52 12 40 00 	mov    $0x401252,%rdi
  4010d4:	e8 97 ff ff ff       	call   401070 <__libc_start_main@plt>
  4010d9:	f4                   	hlt

00000000004010da <deregister_tm_clones>:
  4010da:	b8 48 40 40 00       	mov    $0x404048,%eax
  4010df:	48 3d 48 40 40 00    	cmp    $0x404048,%rax
  4010e5:	74 11                	je     4010f8 <deregister_tm_clones+0x1e>
  4010e7:	b8 00 00 00 00       	mov    $0x0,%eax
  4010ec:	48 85 c0             	test   %rax,%rax
  4010ef:	74 07                	je     4010f8 <deregister_tm_clones+0x1e>
  4010f1:	bf 48 40 40 00       	mov    $0x404048,%edi
  4010f6:	ff e0                	jmp    *%rax
  4010f8:	c3                   	ret

00000000004010f9 <register_tm_clones>:
  4010f9:	be 48 40 40 00       	mov    $0x404048,%esi
  4010fe:	b9 02 00 00 00       	mov    $0x2,%ecx
  401103:	48 81 ee 48 40 40 00 	sub    $0x404048,%rsi
  40110a:	48 c1 fe 03          	sar    $0x3,%rsi
  40110e:	48 89 f0             	mov    %rsi,%rax
  401111:	48 99                	cqto
  401113:	48 f7 f9             	idiv   %rcx
  401116:	48 89 c6             	mov    %rax,%rsi
  401119:	48 85 c0             	test   %rax,%rax
  40111c:	74 11                	je     40112f <register_tm_clones+0x36>
  40111e:	b8 00 00 00 00       	mov    $0x0,%eax
  401123:	48 85 c0             	test   %rax,%rax
  401126:	74 07                	je     40112f <register_tm_clones+0x36>
  401128:	bf 48 40 40 00       	mov    $0x404048,%edi
  40112d:	ff e0                	jmp    *%rax
  40112f:	c3                   	ret

0000000000401130 <__do_global_dtors_aux>:
  401130:	f3 0f 1e fa          	endbr64
  401134:	80 3d 2d 2f 00 00 00 	cmpb   $0x0,0x2f2d(%rip)        # 404068 <completed.0>
  40113b:	75 12                	jne    40114f <__do_global_dtors_aux+0x1f>
  40113d:	55                   	push   %rbp
  40113e:	48 89 e5             	mov    %rsp,%rbp
  401141:	e8 94 ff ff ff       	call   4010da <deregister_tm_clones>
  401146:	c6 05 1b 2f 00 00 01 	movb   $0x1,0x2f1b(%rip)        # 404068 <completed.0>
  40114d:	5d                   	pop    %rbp
  40114e:	c3                   	ret
  40114f:	c3                   	ret

0000000000401150 <frame_dummy>:
  401150:	f3 0f 1e fa          	endbr64
  401154:	eb a3                	jmp    4010f9 <register_tm_clones>

0000000000401156 <func0>:
  401156:	55                   	push   %rbp
  401157:	48 89 e5             	mov    %rsp,%rbp
  40115a:	48 83 ec 30          	sub    $0x30,%rsp
  40115e:	bf 08 20 40 00       	mov    $0x402008,%edi
  401163:	e8 d8 fe ff ff       	call   401040 <puts@plt>
  401168:	48 b8 90 90 90 90 48 	movabs $0x48c0314890909090,%rax
  40116f:	31 c0 48 
  401172:	48 ba 31 ff 48 31 f6 	movabs $0xd23148f63148ff31,%rdx
  401179:	48 31 d2 
  40117c:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
  401180:	48 89 55 d8          	mov    %rdx,-0x28(%rbp)
  401184:	c6 45 e0 c3          	movb   $0xc3,-0x20(%rbp)
  401188:	be 11 00 00 00       	mov    $0x11,%esi
  40118d:	bf 38 20 40 00       	mov    $0x402038,%edi
  401192:	b8 00 00 00 00       	mov    $0x0,%eax
  401197:	e8 b4 fe ff ff       	call   401050 <printf@plt>
  40119c:	bf 00 01 00 00       	mov    $0x100,%edi
  4011a1:	e8 da fe ff ff       	call   401080 <malloc@plt>
  4011a6:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  4011aa:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
  4011af:	75 25                	jne    4011d6 <func0+0x80>
  4011b1:	48 8b 05 a8 2e 00 00 	mov    0x2ea8(%rip),%rax        # 404060 <stderr@GLIBC_2.2.5>
  4011b8:	48 89 c1             	mov    %rax,%rcx
  4011bb:	ba 0e 00 00 00       	mov    $0xe,%edx
  4011c0:	be 01 00 00 00       	mov    $0x1,%esi
  4011c5:	bf 5b 20 40 00       	mov    $0x40205b,%edi
  4011ca:	e8 c1 fe ff ff       	call   401090 <fwrite@plt>
  4011cf:	b8 01 00 00 00       	mov    $0x1,%eax
  4011d4:	eb 7a                	jmp    401250 <func0+0xfa>
  4011d6:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  4011da:	ba 00 01 00 00       	mov    $0x100,%edx
  4011df:	be 90 00 00 00       	mov    $0x90,%esi
  4011e4:	48 89 c7             	mov    %rax,%rdi
  4011e7:	e8 74 fe ff ff       	call   401060 <memset@plt>
  4011ec:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
  4011f3:	00 
  4011f4:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
  4011fb:	00 
  4011fc:	eb 1a                	jmp    401218 <func0+0xc2>
  4011fe:	48 8d 55 d0          	lea    -0x30(%rbp),%rdx
  401202:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
  401206:	48 01 d0             	add    %rdx,%rax
  401209:	0f b6 00             	movzbl (%rax),%eax
  40120c:	0f b6 c0             	movzbl %al,%eax
  40120f:	48 01 45 f8          	add    %rax,-0x8(%rbp)
  401213:	48 83 45 f0 01       	addq   $0x1,-0x10(%rbp)
  401218:	48 83 7d f0 10       	cmpq   $0x10,-0x10(%rbp)
  40121d:	76 df                	jbe    4011fe <func0+0xa8>
  40121f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401223:	48 89 c6             	mov    %rax,%rsi
  401226:	bf 70 20 40 00       	mov    $0x402070,%edi
  40122b:	b8 00 00 00 00       	mov    $0x0,%eax
  401230:	e8 1b fe ff ff       	call   401050 <printf@plt>
  401235:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  401239:	48 89 c7             	mov    %rax,%rdi
  40123c:	e8 ef fd ff ff       	call   401030 <free@plt>
  401241:	bf 91 20 40 00       	mov    $0x402091,%edi
  401246:	e8 f5 fd ff ff       	call   401040 <puts@plt>
  40124b:	b8 00 00 00 00       	mov    $0x0,%eax
  401250:	c9                   	leave
  401251:	c3                   	ret

0000000000401252 <main>:
  401252:	55                   	push   %rbp
  401253:	48 89 e5             	mov    %rsp,%rbp
  401256:	e8 fb fe ff ff       	call   401156 <func0>
  40125b:	5d                   	pop    %rbp
  40125c:	c3                   	ret
  40125d:	0f 1f 00             	nopl   (%rax)

0000000000401260 <__libc_csu_init>:
  401260:	41 57                	push   %r15
  401262:	4c 8d 3d 77 2b 00 00 	lea    0x2b77(%rip),%r15        # 403de0 <__frame_dummy_init_array_entry>
  401269:	41 56                	push   %r14
  40126b:	41 55                	push   %r13
  40126d:	49 89 d5             	mov    %rdx,%r13
  401270:	41 54                	push   %r12
  401272:	49 89 f4             	mov    %rsi,%r12
  401275:	55                   	push   %rbp
  401276:	89 fd                	mov    %edi,%ebp
  401278:	53                   	push   %rbx
  401279:	48 83 ec 08          	sub    $0x8,%rsp
  40127d:	e8 7e fd ff ff       	call   401000 <_init>
  401282:	48 8d 05 5f 2b 00 00 	lea    0x2b5f(%rip),%rax        # 403de8 <__do_global_dtors_aux_fini_array_entry>
  401289:	49 89 c6             	mov    %rax,%r14
  40128c:	4d 29 fe             	sub    %r15,%r14
  40128f:	49 c1 fe 03          	sar    $0x3,%r14
  401293:	4c 39 f8             	cmp    %r15,%rax
  401296:	74 1d                	je     4012b5 <__libc_csu_init+0x55>
  401298:	31 db                	xor    %ebx,%ebx
  40129a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  4012a0:	4c 89 ea             	mov    %r13,%rdx
  4012a3:	4c 89 e6             	mov    %r12,%rsi
  4012a6:	89 ef                	mov    %ebp,%edi
  4012a8:	41 ff 14 df          	call   *(%r15,%rbx,8)
  4012ac:	48 83 c3 01          	add    $0x1,%rbx
  4012b0:	4c 39 f3             	cmp    %r14,%rbx
  4012b3:	72 eb                	jb     4012a0 <__libc_csu_init+0x40>
  4012b5:	48 83 c4 08          	add    $0x8,%rsp
  4012b9:	5b                   	pop    %rbx
  4012ba:	5d                   	pop    %rbp
  4012bb:	41 5c                	pop    %r12
  4012bd:	41 5d                	pop    %r13
  4012bf:	41 5e                	pop    %r14
  4012c1:	41 5f                	pop    %r15
  4012c3:	c3                   	ret
  4012c4:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  4012cb:	00 00 00 00 
  4012cf:	90                   	nop

00000000004012d0 <__libc_csu_fini>:
  4012d0:	c3                   	ret

Disassembly of section .fini:

00000000004012d4 <_fini>:
  4012d4:	48 83 ec 08          	sub    $0x8,%rsp
  4012d8:	48 83 c4 08          	add    $0x8,%rsp
  4012dc:	c3                   	ret
