
malloc.so:     file format elf64-x86-64


Disassembly of section .hash:

00000000000001c8 <.hash>:
 1c8:	25 00 00 00 27       	and    $0x27000000,%eax
 1cd:	00 00                	add    %al,(%rax)
 1cf:	00 0d 00 00 00 17    	add    %cl,0x17000000(%rip)        # 170001d5 <mem_brk_chunk+0x16ffc03d>
 1d5:	00 00                	add    %al,(%rax)
 1d7:	00 1b                	add    %bl,(%rbx)
 1d9:	00 00                	add    %al,(%rax)
 1db:	00 15 00 00 00 05    	add    %dl,0x5000000(%rip)        # 50001e1 <mem_brk_chunk+0x4ffc049>
 1e1:	00 00                	add    %al,(%rax)
 1e3:	00 06                	add    %al,(%rsi)
 1e5:	00 00                	add    %al,(%rax)
 1e7:	00 07                	add    %al,(%rdi)
 1e9:	00 00                	add    %al,(%rax)
 1eb:	00 23                	add    %ah,(%rbx)
 1ed:	00 00                	add    %al,(%rax)
 1ef:	00 00                	add    %al,(%rax)
 1f1:	00 00                	add    %al,(%rax)
 1f3:	00 16                	add    %dl,(%rsi)
 1f5:	00 00                	add    %al,(%rax)
 1f7:	00 02                	add    %al,(%rdx)
 1f9:	00 00                	add    %al,(%rax)
 1fb:	00 04 00             	add    %al,(%rax,%rax,1)
 1fe:	00 00                	add    %al,(%rax)
 200:	00 00                	add    %al,(%rax)
 202:	00 00                	add    %al,(%rax)
 204:	12 00                	adc    (%rax),%al
 206:	00 00                	add    %al,(%rax)
 208:	0a 00                	or     (%rax),%al
 20a:	00 00                	add    %al,(%rax)
 20c:	03 00                	add    (%rax),%eax
 20e:	00 00                	add    %al,(%rax)
 210:	1d 00 00 00 00       	sbb    $0x0,%eax
 215:	00 00                	add    %al,(%rax)
 217:	00 21                	add    %ah,(%rcx)
 219:	00 00                	add    %al,(%rax)
 21b:	00 00                	add    %al,(%rax)
 21d:	00 00                	add    %al,(%rax)
 21f:	00 1c 00             	add    %bl,(%rax,%rax,1)
 222:	00 00                	add    %al,(%rax)
 224:	14 00                	adc    $0x0,%al
 226:	00 00                	add    %al,(%rax)
 228:	1a 00                	sbb    (%rax),%al
 22a:	00 00                	add    %al,(%rax)
 22c:	20 00                	and    %al,(%rax)
 22e:	00 00                	add    %al,(%rax)
 230:	0e                   	(bad)  
 231:	00 00                	add    %al,(%rax)
 233:	00 00                	add    %al,(%rax)
 235:	00 00                	add    %al,(%rax)
 237:	00 24 00             	add    %ah,(%rax,%rax,1)
 23a:	00 00                	add    %al,(%rax)
 23c:	25 00 00 00 00       	and    $0x0,%eax
 241:	00 00                	add    %al,(%rax)
 243:	00 18                	add    %bl,(%rax)
 245:	00 00                	add    %al,(%rax)
 247:	00 00                	add    %al,(%rax)
 249:	00 00                	add    %al,(%rax)
 24b:	00 22                	add    %ah,(%rdx)
 24d:	00 00                	add    %al,(%rax)
 24f:	00 13                	add    %dl,(%rbx)
 251:	00 00                	add    %al,(%rax)
 253:	00 10                	add    %dl,(%rax)
 255:	00 00                	add    %al,(%rax)
 257:	00 26                	add    %ah,(%rsi)
	...
 2a1:	00 00                	add    %al,(%rax)
 2a3:	00 0c 00             	add    %cl,(%rax,%rax,1)
 2a6:	00 00                	add    %al,(%rax)
 2a8:	09 00                	or     %eax,(%rax)
 2aa:	00 00                	add    %al,(%rax)
 2ac:	01 00                	add    %eax,(%rax)
	...
 2ce:	00 00                	add    %al,(%rax)
 2d0:	0b 00                	or     (%rax),%eax
 2d2:	00 00                	add    %al,(%rax)
 2d4:	08 00                	or     %al,(%rax)
 2d6:	00 00                	add    %al,(%rax)
 2d8:	1f                   	(bad)  
 2d9:	00 00                	add    %al,(%rax)
 2db:	00 0f                	add    %cl,(%rdi)
	...
 2e9:	00 00                	add    %al,(%rax)
 2eb:	00 19                	add    %bl,(%rcx)
	...
 2f5:	00 00                	add    %al,(%rax)
 2f7:	00 1e                	add    %bl,(%rsi)
 2f9:	00 00                	add    %al,(%rax)
 2fb:	00 11                	add    %dl,(%rcx)
 2fd:	00 00                	add    %al,(%rax)
	...

Disassembly of section .gnu.hash:

0000000000000300 <.gnu.hash>:
 300:	03 00                	add    (%rax),%eax
 302:	00 00                	add    %al,(%rax)
 304:	1d 00 00 00 01       	sbb    $0x1000000,%eax
 309:	00 00                	add    %al,(%rax)
 30b:	00 06                	add    %al,(%rsi)
 30d:	00 00                	add    %al,(%rax)
 30f:	00 84 08 04 08 0c 54 	add    %al,0x540c0804(%rax,%rcx,1)
 316:	58                   	pop    %rax
 317:	a8 1d                	test   $0x1d,%al
 319:	00 00                	add    %al,(%rax)
 31b:	00 1f                	add    %bl,(%rdi)
 31d:	00 00                	add    %al,(%rax)
 31f:	00 23                	add    %ah,(%rbx)
 321:	00 00                	add    %al,(%rax)
 323:	00 3e                	add    %bh,(%rsi)
 325:	2b b2 b2 c7 0e e0    	sub    -0x1ff1384e(%rdx),%esi
 32b:	3d ca 56 9b dc       	cmp    $0xdc9b56ca,%eax
 330:	3c ad                	cmp    $0xad,%al
 332:	39 0d ba 94 21 89    	cmp    %ecx,-0x76de6b46(%rip)        # ffffffff892197f2 <mem_brk_chunk+0xffffffff8921565a>
 338:	87 f0                	xchg   %esi,%eax
 33a:	96                   	xchg   %eax,%esi
 33b:	7c b6                	jl     2f3 <find_fit@plt-0xd1d>
 33d:	8a 9b e5 f2 16 e6    	mov    -0x19e90d1b(%rbx),%bl
 343:	f5                   	cmc    
 344:	f6 c8 a8             	test   $0xa8,%al
 347:	b1 a3                	mov    $0xa3,%cl
 349:	eb 25                	jmp    370 <find_fit@plt-0xca0>
 34b:	1e                   	(bad)  

Disassembly of section .dynsym:

0000000000000350 <.dynsym>:
	...
 368:	4d 00 00             	rex.WRB add %r8b,(%r8)
 36b:	00 10                	add    %dl,(%rax)
	...
 37d:	00 00                	add    %al,(%rax)
 37f:	00 5f 00             	add    %bl,0x0(%rdi)
 382:	00 00                	add    %al,(%rax)
 384:	10 00                	adc    %al,(%rax)
	...
 396:	00 00                	add    %al,(%rax)
 398:	40 00 00             	rex add %al,(%rax)
 39b:	00 10                	add    %dl,(%rax)
	...
 3ad:	00 00                	add    %al,(%rax)
 3af:	00 33                	add    %dh,(%rbx)
 3b1:	01 00                	add    %eax,(%rax)
 3b3:	00 10                	add    %dl,(%rax)
	...
 3c5:	00 00                	add    %al,(%rax)
 3c7:	00 6f 01             	add    %ch,0x1(%rdi)
 3ca:	00 00                	add    %al,(%rax)
 3cc:	10 00                	adc    %al,(%rax)
	...
 3de:	00 00                	add    %al,(%rax)
 3e0:	9a                   	(bad)  
 3e1:	00 00                	add    %al,(%rax)
 3e3:	00 10                	add    %dl,(%rax)
	...
 3f5:	00 00                	add    %al,(%rax)
 3f7:	00 27                	add    %ah,(%rdi)
 3f9:	00 00                	add    %al,(%rax)
 3fb:	00 10                	add    %dl,(%rax)
	...
 40d:	00 00                	add    %al,(%rax)
 40f:	00 e6                	add    %ah,%dh
 411:	00 00                	add    %al,(%rax)
 413:	00 10                	add    %dl,(%rax)
	...
 425:	00 00                	add    %al,(%rax)
 427:	00 49 01             	add    %cl,0x1(%rcx)
 42a:	00 00                	add    %al,(%rax)
 42c:	10 00                	adc    %al,(%rax)
	...
 43e:	00 00                	add    %al,(%rax)
 440:	bd 00 00 00 10       	mov    $0x10000000,%ebp
	...
 455:	00 00                	add    %al,(%rax)
 457:	00 f7                	add    %dh,%bh
 459:	00 00                	add    %al,(%rax)
 45b:	00 10                	add    %dl,(%rax)
	...
 46d:	00 00                	add    %al,(%rax)
 46f:	00 1b                	add    %bl,(%rbx)
 471:	00 00                	add    %al,(%rax)
 473:	00 10                	add    %dl,(%rax)
	...
 485:	00 00                	add    %al,(%rax)
 487:	00 71 00             	add    %dh,0x0(%rcx)
 48a:	00 00                	add    %al,(%rax)
 48c:	10 00                	adc    %al,(%rax)
	...
 49e:	00 00                	add    %al,(%rax)
 4a0:	80 00 00             	addb   $0x0,(%rax)
 4a3:	00 10                	add    %dl,(%rax)
	...
 4b5:	00 00                	add    %al,(%rax)
 4b7:	00 16                	add    %dl,(%rsi)
 4b9:	01 00                	add    %eax,(%rax)
 4bb:	00 10                	add    %dl,(%rax)
	...
 4cd:	00 00                	add    %al,(%rax)
 4cf:	00 3c 01             	add    %bh,(%rcx,%rax,1)
 4d2:	00 00                	add    %al,(%rax)
 4d4:	10 00                	adc    %al,(%rax)
	...
 4e6:	00 00                	add    %al,(%rax)
 4e8:	cf                   	iret   
 4e9:	00 00                	add    %al,(%rax)
 4eb:	00 10                	add    %dl,(%rax)
	...
 4fd:	00 00                	add    %al,(%rax)
 4ff:	00 49 00             	add    %cl,0x0(%rcx)
 502:	00 00                	add    %al,(%rax)
 504:	10 00                	adc    %al,(%rax)
	...
 516:	00 00                	add    %al,(%rax)
 518:	05 01 00 00 10       	add    $0x10000001,%eax
	...
 52d:	00 00                	add    %al,(%rax)
 52f:	00 55 01             	add    %dl,0x1(%rbp)
 532:	00 00                	add    %al,(%rax)
 534:	10 00                	adc    %al,(%rax)
	...
 546:	00 00                	add    %al,(%rax)
 548:	8e 00                	mov    (%rax),%es
 54a:	00 00                	add    %al,(%rax)
 54c:	10 00                	adc    %al,(%rax)
	...
 55e:	00 00                	add    %al,(%rax)
 560:	1b 01                	sbb    (%rcx),%eax
 562:	00 00                	add    %al,(%rax)
 564:	10 00                	adc    %al,(%rax)
	...
 576:	00 00                	add    %al,(%rax)
 578:	22 01                	and    (%rcx),%al
 57a:	00 00                	add    %al,(%rax)
 57c:	10 00                	adc    %al,(%rax)
	...
 58e:	00 00                	add    %al,(%rax)
 590:	44 01 00             	add    %r8d,(%rax)
 593:	00 10                	add    %dl,(%rax)
	...
 5a5:	00 00                	add    %al,(%rax)
 5a7:	00 56 00             	add    %dl,0x0(%rsi)
 5aa:	00 00                	add    %al,(%rax)
 5ac:	10 00                	adc    %al,(%rax)
	...
 5be:	00 00                	add    %al,(%rax)
 5c0:	84 01                	test   %al,(%rcx)
 5c2:	00 00                	add    %al,(%rax)
 5c4:	10 00                	adc    %al,(%rax)
	...
 5d6:	00 00                	add    %al,(%rax)
 5d8:	a6                   	cmpsb  %es:(%rdi),%ds:(%rsi)
 5d9:	00 00                	add    %al,(%rax)
 5db:	00 10                	add    %dl,(%rax)
	...
 5ed:	00 00                	add    %al,(%rax)
 5ef:	00 16                	add    %dl,(%rsi)
 5f1:	00 00                	add    %al,(%rax)
 5f3:	00 10                	add    %dl,(%rax)
	...
 605:	00 00                	add    %al,(%rax)
 607:	00 63 01             	add    %ah,0x1(%rbx)
 60a:	00 00                	add    %al,(%rax)
 60c:	12 00                	adc    (%rax),%al
 60e:	08 00                	or     %al,(%rax)
 610:	d0 17                	rclb   (%rdi)
 612:	00 00                	add    %al,(%rax)
 614:	00 00                	add    %al,(%rax)
 616:	00 00                	add    %al,(%rax)
 618:	19 00                	sbb    %eax,(%rax)
 61a:	00 00                	add    %al,(%rax)
 61c:	00 00                	add    %al,(%rax)
 61e:	00 00                	add    %al,(%rax)
 620:	de 00                	fiadds (%rax)
 622:	00 00                	add    %al,(%rax)
 624:	12 00                	adc    (%rax),%al
 626:	08 00                	or     %al,(%rax)
 628:	d0 14 00             	rclb   (%rax,%rax,1)
 62b:	00 00                	add    %al,(%rax)
 62d:	00 00                	add    %al,(%rax)
 62f:	00 cf                	add    %cl,%bh
 631:	00 00                	add    %al,(%rax)
 633:	00 00                	add    %al,(%rax)
 635:	00 00                	add    %al,(%rax)
 637:	00 0b                	add    %cl,(%rbx)
 639:	00 00                	add    %al,(%rax)
 63b:	00 12                	add    %dl,(%rdx)
 63d:	00 08                	add    %cl,(%rax)
 63f:	00 20                	add    %ah,(%rax)
 641:	18 00                	sbb    %al,(%rax)
 643:	00 00                	add    %al,(%rax)
 645:	00 00                	add    %al,(%rax)
 647:	00 aa 01 00 00 00    	add    %ch,0x1(%rdx)
 64d:	00 00                	add    %al,(%rax)
 64f:	00 39                	add    %bh,(%rcx)
 651:	00 00                	add    %al,(%rax)
 653:	00 12                	add    %dl,(%rdx)
 655:	00 08                	add    %cl,(%rax)
 657:	00 00                	add    %al,(%rax)
 659:	13 00                	adc    (%rax),%eax
 65b:	00 00                	add    %al,(%rax)
 65d:	00 00                	add    %al,(%rax)
 65f:	00 3f                	add    %bh,(%rdi)
 661:	01 00                	add    %eax,(%rax)
 663:	00 00                	add    %al,(%rax)
 665:	00 00                	add    %al,(%rax)
 667:	00 76 01             	add    %dh,0x1(%rsi)
 66a:	00 00                	add    %al,(%rax)
 66c:	12 00                	adc    (%rax),%al
 66e:	08 00                	or     %al,(%rax)
 670:	f0 17                	lock (bad) 
 672:	00 00                	add    %al,(%rax)
 674:	00 00                	add    %al,(%rax)
 676:	00 00                	add    %al,(%rax)
 678:	22 00                	and    (%rax),%al
 67a:	00 00                	add    %al,(%rax)
 67c:	00 00                	add    %al,(%rax)
 67e:	00 00                	add    %al,(%rax)
 680:	b8 00 00 00 12       	mov    $0x12000000,%eax
 685:	00 08                	add    %cl,(%rax)
 687:	00 40 14             	add    %al,0x14(%rax)
 68a:	00 00                	add    %al,(%rax)
 68c:	00 00                	add    %al,(%rax)
 68e:	00 00                	add    %al,(%rax)
 690:	8b 00                	mov    (%rax),%eax
 692:	00 00                	add    %al,(%rax)
 694:	00 00                	add    %al,(%rax)
 696:	00 00                	add    %al,(%rax)
 698:	01 00                	add    %eax,(%rax)
 69a:	00 00                	add    %al,(%rax)
 69c:	12 00                	adc    (%rax),%al
 69e:	08 00                	or     %al,(%rax)
 6a0:	00 12                	add    %dl,(%rdx)
 6a2:	00 00                	add    %al,(%rax)
 6a4:	00 00                	add    %al,(%rax)
 6a6:	00 00                	add    %al,(%rax)
 6a8:	f2 00 00             	repnz add %al,(%rax)
 6ab:	00 00                	add    %al,(%rax)
 6ad:	00 00                	add    %al,(%rax)
 6af:	00 fe                	add    %bh,%dh
 6b1:	00 00                	add    %al,(%rax)
 6b3:	00 12                	add    %dl,(%rdx)
 6b5:	00 08                	add    %cl,(%rax)
 6b7:	00 a0 15 00 00 00    	add    %ah,0x15(%rax)
 6bd:	00 00                	add    %al,(%rax)
 6bf:	00 9e 00 00 00 00    	add    %bl,0x0(%rsi)
 6c5:	00 00                	add    %al,(%rax)
 6c7:	00 0c 01             	add    %cl,(%rcx,%rax,1)
 6ca:	00 00                	add    %al,(%rax)
 6cc:	12 00                	adc    (%rax),%al
 6ce:	08 00                	or     %al,(%rax)
 6d0:	40 16                	rex (bad) 
 6d2:	00 00                	add    %al,(%rax)
 6d4:	00 00                	add    %al,(%rax)
 6d6:	00 00                	add    %al,(%rax)
 6d8:	19 01                	sbb    %eax,(%rcx)
 6da:	00 00                	add    %al,(%rax)
 6dc:	00 00                	add    %al,(%rax)
 6de:	00 00                	add    %al,(%rax)
 6e0:	8d 01                	lea    (%rcx),%eax
 6e2:	00 00                	add    %al,(%rax)
 6e4:	12 00                	adc    (%rax),%al
 6e6:	08 00                	or     %al,(%rax)
 6e8:	40 1a 00             	rex sbb (%rax),%al
 6eb:	00 00                	add    %al,(%rax)
 6ed:	00 00                	add    %al,(%rax)
 6ef:	00 17                	add    %dl,(%rdi)
 6f1:	00 00                	add    %al,(%rax)
 6f3:	00 00                	add    %al,(%rax)
 6f5:	00 00                	add    %al,(%rax)
	...

Disassembly of section .dynstr:

00000000000006f8 <.dynstr>:
 6f8:	00 69 6e             	add    %ch,0x6e(%rcx)
 6fb:	69 74 5f 68 65 61 70 	imul   $0x706165,0x68(%rdi,%rbx,2),%esi
 702:	00 
 703:	65 78 74             	gs js  77a <find_fit@plt-0x896>
 706:	65 6e                	outsb  %gs:(%rsi),(%dx)
 708:	64 5f                	fs pop %rdi
 70a:	62                   	(bad)  
 70b:	6d                   	insl   (%dx),%es:(%rdi)
 70c:	70 00                	jo     70e <find_fit@plt-0x902>
 70e:	70 61                	jo     771 <find_fit@plt-0x89f>
 710:	63 6b 00             	movsxd 0x0(%rbx),%ebp
 713:	65 78 74             	gs js  78a <find_fit@plt-0x886>
 716:	65 6e                	outsb  %gs:(%rsi),(%dx)
 718:	64 5f                	fs pop %rdi
 71a:	68 65 61 70 00       	push   $0x706165
 71f:	69 6e 73 65 72 74 5f 	imul   $0x5f747265,0x73(%rsi),%ebp
 726:	66 72 65             	data16 jb 78e <find_fit@plt-0x882>
 729:	65 5f                	gs pop %rdi
 72b:	62                   	(bad)  
 72c:	6c                   	insb   (%dx),%es:(%rdi)
 72d:	6f                   	outsl  %ds:(%rsi),(%dx)
 72e:	63 6b 00             	movsxd 0x0(%rbx),%ebp
 731:	6d                   	insl   (%dx),%es:(%rdi)
 732:	61                   	(bad)  
 733:	6c                   	insb   (%dx),%es:(%rdi)
 734:	6c                   	insb   (%dx),%es:(%rdi)
 735:	6f                   	outsl  %ds:(%rsi),(%dx)
 736:	63 00                	movsxd (%rax),%eax
 738:	72 6f                	jb     7a9 <find_fit@plt-0x867>
 73a:	75 6e                	jne    7aa <find_fit@plt-0x866>
 73c:	64 5f                	fs pop %rdi
 73e:	75 70                	jne    7b0 <find_fit@plt-0x860>
 740:	00 6d 61             	add    %ch,0x61(%rbp)
 743:	78 00                	js     745 <find_fit@plt-0x8cb>
 745:	66 69 6e 64 5f 66    	imul   $0x665f,0x64(%rsi),%bp
 74b:	69 74 00 67 65 74 5f 	imul   $0x735f7465,0x67(%rax,%rax,1),%esi
 752:	73 
 753:	69 7a 65 00 72 65 6d 	imul   $0x6d657200,0x65(%rdx),%edi
 75a:	6f                   	outsl  %ds:(%rsi),(%dx)
 75b:	76 65                	jbe    7c2 <find_fit@plt-0x84e>
 75d:	5f                   	pop    %rdi
 75e:	66 72 65             	data16 jb 7c6 <find_fit@plt-0x84a>
 761:	65 5f                	gs pop %rdi
 763:	62                   	(bad)  
 764:	6c                   	insb   (%dx),%es:(%rdi)
 765:	6f                   	outsl  %ds:(%rsi),(%dx)
 766:	63 6b 00             	movsxd 0x0(%rbx),%ebp
 769:	67 65 74 5f          	addr32 gs je 7cc <find_fit@plt-0x844>
 76d:	70 72                	jo     7e1 <find_fit@plt-0x82f>
 76f:	65 76 5f             	gs jbe 7d1 <find_fit@plt-0x83f>
 772:	61                   	(bad)  
 773:	6c                   	insb   (%dx),%es:(%rdi)
 774:	6c                   	insb   (%dx),%es:(%rdi)
 775:	6f                   	outsl  %ds:(%rsi),(%dx)
 776:	63 00                	movsxd (%rax),%eax
 778:	67 65 74 5f          	addr32 gs je 7db <find_fit@plt-0x835>
 77c:	70 72                	jo     7f0 <find_fit@plt-0x820>
 77e:	65 76 5f             	gs jbe 7e0 <find_fit@plt-0x830>
 781:	6d                   	insl   (%dx),%es:(%rdi)
 782:	69 6e 69 00 77 72 69 	imul   $0x69727700,0x69(%rsi),%ebp
 789:	74 65                	je     7f0 <find_fit@plt-0x820>
 78b:	5f                   	pop    %rdi
 78c:	62                   	(bad)  
 78d:	6c                   	insb   (%dx),%es:(%rdi)
 78e:	6f                   	outsl  %ds:(%rsi),(%dx)
 78f:	63 6b 00             	movsxd 0x0(%rbx),%ebp
 792:	73 70                	jae    804 <find_fit@plt-0x80c>
 794:	6c                   	insb   (%dx),%es:(%rdi)
 795:	69 74 5f 62 6c 6f 63 	imul   $0x6b636f6c,0x62(%rdi,%rbx,2),%esi
 79c:	6b 
 79d:	00 68 65             	add    %ch,0x65(%rax)
 7a0:	61                   	(bad)  
 7a1:	64 65 72 5f          	fs gs jb 804 <find_fit@plt-0x80c>
 7a5:	74 6f                	je     816 <find_fit@plt-0x7fa>
 7a7:	5f                   	pop    %rdi
 7a8:	70 61                	jo     80b <find_fit@plt-0x805>
 7aa:	79 6c                	jns    818 <find_fit@plt-0x7f8>
 7ac:	6f                   	outsl  %ds:(%rsi),(%dx)
 7ad:	61                   	(bad)  
 7ae:	64 00 66 72          	add    %ah,%fs:0x72(%rsi)
 7b2:	65 65 00 70 61       	gs add %dh,%gs:0x61(%rax)
 7b7:	79 6c                	jns    825 <find_fit@plt-0x7eb>
 7b9:	6f                   	outsl  %ds:(%rsi),(%dx)
 7ba:	61                   	(bad)  
 7bb:	64 5f                	fs pop %rdi
 7bd:	74 6f                	je     82e <find_fit@plt-0x7e2>
 7bf:	5f                   	pop    %rdi
 7c0:	68 65 61 64 65       	push   $0x65646165
 7c5:	72 00                	jb     7c7 <find_fit@plt-0x849>
 7c7:	63 6f 61             	movsxd 0x61(%rdi),%ebp
 7ca:	6c                   	insb   (%dx),%es:(%rdi)
 7cb:	65 73 63             	gs jae 831 <find_fit@plt-0x7df>
 7ce:	65 5f                	gs pop %rdi
 7d0:	62                   	(bad)  
 7d1:	6c                   	insb   (%dx),%es:(%rdi)
 7d2:	6f                   	outsl  %ds:(%rsi),(%dx)
 7d3:	63 6b 00             	movsxd 0x0(%rbx),%ebp
 7d6:	72 65                	jb     83d <find_fit@plt-0x7d3>
 7d8:	61                   	(bad)  
 7d9:	6c                   	insb   (%dx),%es:(%rdi)
 7da:	6c                   	insb   (%dx),%es:(%rdi)
 7db:	6f                   	outsl  %ds:(%rsi),(%dx)
 7dc:	63 00                	movsxd (%rax),%eax
 7de:	67 65 74 5f          	addr32 gs je 841 <find_fit@plt-0x7cf>
 7e2:	70 61                	jo     845 <find_fit@plt-0x7cb>
 7e4:	79 6c                	jns    852 <find_fit@plt-0x7be>
 7e6:	6f                   	outsl  %ds:(%rsi),(%dx)
 7e7:	61                   	(bad)  
 7e8:	64 5f                	fs pop %rdi
 7ea:	73 69                	jae    855 <find_fit@plt-0x7bb>
 7ec:	7a 65                	jp     853 <find_fit@plt-0x7bd>
 7ee:	00 6d 65             	add    %ch,0x65(%rbp)
 7f1:	6d                   	insl   (%dx),%es:(%rdi)
 7f2:	63 70 79             	movsxd 0x79(%rax),%esi
 7f5:	00 63 61             	add    %ah,0x61(%rbx)
 7f8:	6c                   	insb   (%dx),%es:(%rdi)
 7f9:	6c                   	insb   (%dx),%es:(%rdi)
 7fa:	6f                   	outsl  %ds:(%rsi),(%dx)
 7fb:	63 00                	movsxd (%rax),%eax
 7fd:	6d                   	insl   (%dx),%es:(%rdi)
 7fe:	65 6d                	gs insl (%dx),%es:(%rdi)
 800:	73 65                	jae    867 <find_fit@plt-0x7a9>
 802:	74 00                	je     804 <find_fit@plt-0x80c>
 804:	68 65 61 70 5f       	push   $0x5f706165
 809:	69 6e 69 74 00 6d 6d 	imul   $0x6d6d0074,0x69(%rsi),%ebp
 810:	61                   	(bad)  
 811:	70 00                	jo     813 <find_fit@plt-0x7fd>
 813:	73 74                	jae    889 <find_fit@plt-0x787>
 815:	64 65 72 72          	fs gs jb 88b <find_fit@plt-0x785>
 819:	00 5f 5f             	add    %bl,0x5f(%rdi)
 81c:	65 72 72             	gs jb  891 <find_fit@plt-0x77f>
 81f:	6e                   	outsb  %ds:(%rsi),(%dx)
 820:	6f                   	outsl  %ds:(%rsi),(%dx)
 821:	5f                   	pop    %rdi
 822:	6c                   	insb   (%dx),%es:(%rdi)
 823:	6f                   	outsl  %ds:(%rsi),(%dx)
 824:	63 61 74             	movsxd 0x74(%rcx),%esp
 827:	69 6f 6e 00 73 74 72 	imul   $0x72747300,0x6e(%rdi),%ebp
 82e:	65 72 72             	gs jb  8a3 <find_fit@plt-0x76d>
 831:	6f                   	outsl  %ds:(%rsi),(%dx)
 832:	72 00                	jb     834 <find_fit@plt-0x7dc>
 834:	66 70 72             	data16 jo 8a9 <find_fit@plt-0x767>
 837:	69 6e 74 66 00 65 78 	imul   $0x78650066,0x74(%rsi),%ebp
 83e:	69 74 00 67 65 74 70 	imul   $0x61707465,0x67(%rax,%rax,1),%esi
 845:	61 
 846:	67 65 73 69          	addr32 gs jae 8b3 <find_fit@plt-0x75d>
 84a:	7a 65                	jp     8b1 <find_fit@plt-0x75f>
 84c:	00 5f 5f             	add    %bl,0x5f(%rdi)
 84f:	61                   	(bad)  
 850:	73 73                	jae    8c5 <find_fit@plt-0x74b>
 852:	65 72 74             	gs jb  8c9 <find_fit@plt-0x747>
 855:	5f                   	pop    %rdi
 856:	66 61                	data16 (bad) 
 858:	69 6c 00 68 65 61 70 	imul   $0x5f706165,0x68(%rax,%rax,1),%ebp
 85f:	5f 
 860:	64 65 69 6e 69 74 00 	fs imul $0x756d0074,%gs:0x69(%rsi),%ebp
 867:	6d 75 
 869:	6e                   	outsb  %ds:(%rsi),(%dx)
 86a:	6d                   	insl   (%dx),%es:(%rdi)
 86b:	61                   	(bad)  
 86c:	70 00                	jo     86e <find_fit@plt-0x7a2>
 86e:	72 65                	jb     8d5 <find_fit@plt-0x73b>
 870:	73 65                	jae    8d7 <find_fit@plt-0x739>
 872:	74 5f                	je     8d3 <find_fit@plt-0x73d>
 874:	62                   	(bad)  
 875:	6d                   	insl   (%dx),%es:(%rdi)
 876:	70 5f                	jo     8d7 <find_fit@plt-0x739>
 878:	70 74                	jo     8ee <find_fit@plt-0x722>
 87a:	72 00                	jb     87c <find_fit@plt-0x794>
 87c:	6d                   	insl   (%dx),%es:(%rdi)
 87d:	70 72                	jo     8f1 <find_fit@plt-0x71f>
 87f:	6f                   	outsl  %ds:(%rsi),(%dx)
 880:	74 65                	je     8e7 <find_fit@plt-0x729>
 882:	63 74 00 63          	movsxd 0x63(%rax,%rax,1),%esi
 886:	75 72                	jne    8fa <find_fit@plt-0x716>
 888:	72 65                	jb     8ef <find_fit@plt-0x721>
 88a:	6e                   	outsb  %ds:(%rsi),(%dx)
 88b:	74 5f                	je     8ec <find_fit@plt-0x724>
 88d:	61                   	(bad)  
 88e:	72 65                	jb     8f5 <find_fit@plt-0x71b>
 890:	6e                   	outsb  %ds:(%rsi),(%dx)
 891:	61                   	(bad)  
 892:	5f                   	pop    %rdi
 893:	75 73                	jne    908 <find_fit@plt-0x708>
 895:	61                   	(bad)  
 896:	67                   	addr32
 897:	65                   	gs
	...

Disassembly of section .rela.dyn:

00000000000008a0 <.rela.dyn>:
 8a0:	f8                   	clc    
 8a1:	3f                   	(bad)  
 8a2:	00 00                	add    %al,(%rax)
 8a4:	00 00                	add    %al,(%rax)
 8a6:	00 00                	add    %al,(%rax)
 8a8:	06                   	(bad)  
 8a9:	00 00                	add    %al,(%rax)
 8ab:	00 16                	add    %dl,(%rsi)
	...

Disassembly of section .rela.plt:

00000000000008b8 <.rela.plt>:
 8b8:	18 40 00             	sbb    %al,0x0(%rax)
 8bb:	00 00                	add    %al,(%rax)
 8bd:	00 00                	add    %al,(%rax)
 8bf:	00 07                	add    %al,(%rdi)
 8c1:	00 00                	add    %al,(%rax)
 8c3:	00 01                	add    %al,(%rcx)
	...
 8cd:	00 00                	add    %al,(%rax)
 8cf:	00 20                	add    %ah,(%rax)
 8d1:	40 00 00             	rex add %al,(%rax)
 8d4:	00 00                	add    %al,(%rax)
 8d6:	00 00                	add    %al,(%rax)
 8d8:	07                   	(bad)  
 8d9:	00 00                	add    %al,(%rax)
 8db:	00 02                	add    %al,(%rdx)
	...
 8e5:	00 00                	add    %al,(%rax)
 8e7:	00 28                	add    %ch,(%rax)
 8e9:	40 00 00             	rex add %al,(%rax)
 8ec:	00 00                	add    %al,(%rax)
 8ee:	00 00                	add    %al,(%rax)
 8f0:	07                   	(bad)  
 8f1:	00 00                	add    %al,(%rax)
 8f3:	00 03                	add    %al,(%rbx)
	...
 8fd:	00 00                	add    %al,(%rax)
 8ff:	00 30                	add    %dh,(%rax)
 901:	40 00 00             	rex add %al,(%rax)
 904:	00 00                	add    %al,(%rax)
 906:	00 00                	add    %al,(%rax)
 908:	07                   	(bad)  
 909:	00 00                	add    %al,(%rax)
 90b:	00 1f                	add    %bl,(%rdi)
	...
 915:	00 00                	add    %al,(%rax)
 917:	00 38                	add    %bh,(%rax)
 919:	40 00 00             	rex add %al,(%rax)
 91c:	00 00                	add    %al,(%rax)
 91e:	00 00                	add    %al,(%rax)
 920:	07                   	(bad)  
 921:	00 00                	add    %al,(%rax)
 923:	00 04 00             	add    %al,(%rax,%rax,1)
	...
 92e:	00 00                	add    %al,(%rax)
 930:	40                   	rex
 931:	40 00 00             	rex add %al,(%rax)
 934:	00 00                	add    %al,(%rax)
 936:	00 00                	add    %al,(%rax)
 938:	07                   	(bad)  
 939:	00 00                	add    %al,(%rax)
 93b:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 941 <find_fit@plt-0x6cf>
 941:	00 00                	add    %al,(%rax)
 943:	00 00                	add    %al,(%rax)
 945:	00 00                	add    %al,(%rax)
 947:	00 48 40             	add    %cl,0x40(%rax)
 94a:	00 00                	add    %al,(%rax)
 94c:	00 00                	add    %al,(%rax)
 94e:	00 00                	add    %al,(%rax)
 950:	07                   	(bad)  
 951:	00 00                	add    %al,(%rax)
 953:	00 06                	add    %al,(%rsi)
	...
 95d:	00 00                	add    %al,(%rax)
 95f:	00 50 40             	add    %dl,0x40(%rax)
 962:	00 00                	add    %al,(%rax)
 964:	00 00                	add    %al,(%rax)
 966:	00 00                	add    %al,(%rax)
 968:	07                   	(bad)  
 969:	00 00                	add    %al,(%rax)
 96b:	00 07                	add    %al,(%rdi)
	...
 975:	00 00                	add    %al,(%rax)
 977:	00 58 40             	add    %bl,0x40(%rax)
 97a:	00 00                	add    %al,(%rax)
 97c:	00 00                	add    %al,(%rax)
 97e:	00 00                	add    %al,(%rax)
 980:	07                   	(bad)  
 981:	00 00                	add    %al,(%rax)
 983:	00 08                	add    %cl,(%rax)
	...
 98d:	00 00                	add    %al,(%rax)
 98f:	00 60 40             	add    %ah,0x40(%rax)
 992:	00 00                	add    %al,(%rax)
 994:	00 00                	add    %al,(%rax)
 996:	00 00                	add    %al,(%rax)
 998:	07                   	(bad)  
 999:	00 00                	add    %al,(%rax)
 99b:	00 09                	add    %cl,(%rcx)
	...
 9a5:	00 00                	add    %al,(%rax)
 9a7:	00 68 40             	add    %ch,0x40(%rax)
 9aa:	00 00                	add    %al,(%rax)
 9ac:	00 00                	add    %al,(%rax)
 9ae:	00 00                	add    %al,(%rax)
 9b0:	07                   	(bad)  
 9b1:	00 00                	add    %al,(%rax)
 9b3:	00 0a                	add    %cl,(%rdx)
	...
 9bd:	00 00                	add    %al,(%rax)
 9bf:	00 70 40             	add    %dh,0x40(%rax)
 9c2:	00 00                	add    %al,(%rax)
 9c4:	00 00                	add    %al,(%rax)
 9c6:	00 00                	add    %al,(%rax)
 9c8:	07                   	(bad)  
 9c9:	00 00                	add    %al,(%rax)
 9cb:	00 0b                	add    %cl,(%rbx)
	...
 9d5:	00 00                	add    %al,(%rax)
 9d7:	00 78 40             	add    %bh,0x40(%rax)
 9da:	00 00                	add    %al,(%rax)
 9dc:	00 00                	add    %al,(%rax)
 9de:	00 00                	add    %al,(%rax)
 9e0:	07                   	(bad)  
 9e1:	00 00                	add    %al,(%rax)
 9e3:	00 20                	add    %ah,(%rax)
	...
 9ed:	00 00                	add    %al,(%rax)
 9ef:	00 80 40 00 00 00    	add    %al,0x40(%rax)
 9f5:	00 00                	add    %al,(%rax)
 9f7:	00 07                	add    %al,(%rdi)
 9f9:	00 00                	add    %al,(%rax)
 9fb:	00 0c 00             	add    %cl,(%rax,%rax,1)
	...
 a06:	00 00                	add    %al,(%rax)
 a08:	88 40 00             	mov    %al,0x0(%rax)
 a0b:	00 00                	add    %al,(%rax)
 a0d:	00 00                	add    %al,(%rax)
 a0f:	00 07                	add    %al,(%rdi)
 a11:	00 00                	add    %al,(%rax)
 a13:	00 0d 00 00 00 00    	add    %cl,0x0(%rip)        # a19 <find_fit@plt-0x5f7>
 a19:	00 00                	add    %al,(%rax)
 a1b:	00 00                	add    %al,(%rax)
 a1d:	00 00                	add    %al,(%rax)
 a1f:	00 90 40 00 00 00    	add    %dl,0x40(%rax)
 a25:	00 00                	add    %al,(%rax)
 a27:	00 07                	add    %al,(%rdi)
 a29:	00 00                	add    %al,(%rax)
 a2b:	00 0e                	add    %cl,(%rsi)
	...
 a35:	00 00                	add    %al,(%rax)
 a37:	00 98 40 00 00 00    	add    %bl,0x40(%rax)
 a3d:	00 00                	add    %al,(%rax)
 a3f:	00 07                	add    %al,(%rdi)
 a41:	00 00                	add    %al,(%rax)
 a43:	00 0f                	add    %cl,(%rdi)
	...
 a4d:	00 00                	add    %al,(%rax)
 a4f:	00 a0 40 00 00 00    	add    %ah,0x40(%rax)
 a55:	00 00                	add    %al,(%rax)
 a57:	00 07                	add    %al,(%rdi)
 a59:	00 00                	add    %al,(%rax)
 a5b:	00 23                	add    %ah,(%rbx)
	...
 a65:	00 00                	add    %al,(%rax)
 a67:	00 a8 40 00 00 00    	add    %ch,0x40(%rax)
 a6d:	00 00                	add    %al,(%rax)
 a6f:	00 07                	add    %al,(%rdi)
 a71:	00 00                	add    %al,(%rax)
 a73:	00 10                	add    %dl,(%rax)
	...
 a7d:	00 00                	add    %al,(%rax)
 a7f:	00 b0 40 00 00 00    	add    %dh,0x40(%rax)
 a85:	00 00                	add    %al,(%rax)
 a87:	00 07                	add    %al,(%rdi)
 a89:	00 00                	add    %al,(%rax)
 a8b:	00 11                	add    %dl,(%rcx)
	...
 a95:	00 00                	add    %al,(%rax)
 a97:	00 b8 40 00 00 00    	add    %bh,0x40(%rax)
 a9d:	00 00                	add    %al,(%rax)
 a9f:	00 07                	add    %al,(%rdi)
 aa1:	00 00                	add    %al,(%rax)
 aa3:	00 12                	add    %dl,(%rdx)
	...
 aad:	00 00                	add    %al,(%rax)
 aaf:	00 c0                	add    %al,%al
 ab1:	40 00 00             	rex add %al,(%rax)
 ab4:	00 00                	add    %al,(%rax)
 ab6:	00 00                	add    %al,(%rax)
 ab8:	07                   	(bad)  
 ab9:	00 00                	add    %al,(%rax)
 abb:	00 13                	add    %dl,(%rbx)
	...
 ac5:	00 00                	add    %al,(%rax)
 ac7:	00 c8                	add    %cl,%al
 ac9:	40 00 00             	rex add %al,(%rax)
 acc:	00 00                	add    %al,(%rax)
 ace:	00 00                	add    %al,(%rax)
 ad0:	07                   	(bad)  
 ad1:	00 00                	add    %al,(%rax)
 ad3:	00 14 00             	add    %dl,(%rax,%rax,1)
	...
 ade:	00 00                	add    %al,(%rax)
 ae0:	d0 40 00             	rolb   0x0(%rax)
 ae3:	00 00                	add    %al,(%rax)
 ae5:	00 00                	add    %al,(%rax)
 ae7:	00 07                	add    %al,(%rdi)
 ae9:	00 00                	add    %al,(%rax)
 aeb:	00 15 00 00 00 00    	add    %dl,0x0(%rip)        # af1 <find_fit@plt-0x51f>
 af1:	00 00                	add    %al,(%rax)
 af3:	00 00                	add    %al,(%rax)
 af5:	00 00                	add    %al,(%rax)
 af7:	00 d8                	add    %bl,%al
 af9:	40 00 00             	rex add %al,(%rax)
 afc:	00 00                	add    %al,(%rax)
 afe:	00 00                	add    %al,(%rax)
 b00:	07                   	(bad)  
 b01:	00 00                	add    %al,(%rax)
 b03:	00 17                	add    %dl,(%rdi)
	...
 b0d:	00 00                	add    %al,(%rax)
 b0f:	00 e0                	add    %ah,%al
 b11:	40 00 00             	rex add %al,(%rax)
 b14:	00 00                	add    %al,(%rax)
 b16:	00 00                	add    %al,(%rax)
 b18:	07                   	(bad)  
 b19:	00 00                	add    %al,(%rax)
 b1b:	00 18                	add    %bl,(%rax)
	...
 b25:	00 00                	add    %al,(%rax)
 b27:	00 e8                	add    %ch,%al
 b29:	40 00 00             	rex add %al,(%rax)
 b2c:	00 00                	add    %al,(%rax)
 b2e:	00 00                	add    %al,(%rax)
 b30:	07                   	(bad)  
 b31:	00 00                	add    %al,(%rax)
 b33:	00 19                	add    %bl,(%rcx)
	...
 b3d:	00 00                	add    %al,(%rax)
 b3f:	00 f0                	add    %dh,%al
 b41:	40 00 00             	rex add %al,(%rax)
 b44:	00 00                	add    %al,(%rax)
 b46:	00 00                	add    %al,(%rax)
 b48:	07                   	(bad)  
 b49:	00 00                	add    %al,(%rax)
 b4b:	00 1a                	add    %bl,(%rdx)
	...
 b55:	00 00                	add    %al,(%rax)
 b57:	00 f8                	add    %bh,%al
 b59:	40 00 00             	rex add %al,(%rax)
 b5c:	00 00                	add    %al,(%rax)
 b5e:	00 00                	add    %al,(%rax)
 b60:	07                   	(bad)  
 b61:	00 00                	add    %al,(%rax)
 b63:	00 1b                	add    %bl,(%rbx)
	...
 b71:	41 00 00             	add    %al,(%r8)
 b74:	00 00                	add    %al,(%rax)
 b76:	00 00                	add    %al,(%rax)
 b78:	07                   	(bad)  
 b79:	00 00                	add    %al,(%rax)
 b7b:	00 22                	add    %ah,(%rdx)
	...
 b85:	00 00                	add    %al,(%rax)
 b87:	00 08                	add    %cl,(%rax)
 b89:	41 00 00             	add    %al,(%r8)
 b8c:	00 00                	add    %al,(%rax)
 b8e:	00 00                	add    %al,(%rax)
 b90:	07                   	(bad)  
 b91:	00 00                	add    %al,(%rax)
 b93:	00 1c 00             	add    %bl,(%rax,%rax,1)
	...

Disassembly of section .plt:

0000000000001000 <find_fit@plt-0x10>:
    1000:	ff 35 02 30 00 00    	push   0x3002(%rip)        # 4008 <_GLOBAL_OFFSET_TABLE_+0x8>
    1006:	ff 25 04 30 00 00    	jmp    *0x3004(%rip)        # 4010 <_GLOBAL_OFFSET_TABLE_+0x10>
    100c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001010 <find_fit@plt>:
    1010:	ff 25 02 30 00 00    	jmp    *0x3002(%rip)        # 4018 <find_fit>
    1016:	68 00 00 00 00       	push   $0x0
    101b:	e9 e0 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001020 <remove_free_block@plt>:
    1020:	ff 25 fa 2f 00 00    	jmp    *0x2ffa(%rip)        # 4020 <remove_free_block>
    1026:	68 01 00 00 00       	push   $0x1
    102b:	e9 d0 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001030 <round_up@plt>:
    1030:	ff 25 f2 2f 00 00    	jmp    *0x2ff2(%rip)        # 4028 <round_up>
    1036:	68 02 00 00 00       	push   $0x2
    103b:	e9 c0 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001040 <extend_bmp@plt>:
    1040:	ff 25 ea 2f 00 00    	jmp    *0x2fea(%rip)        # 4030 <extend_bmp+0x2810>
    1046:	68 03 00 00 00       	push   $0x3
    104b:	e9 b0 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001050 <strerror@plt>:
    1050:	ff 25 e2 2f 00 00    	jmp    *0x2fe2(%rip)        # 4038 <strerror>
    1056:	68 04 00 00 00       	push   $0x4
    105b:	e9 a0 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001060 <munmap@plt>:
    1060:	ff 25 da 2f 00 00    	jmp    *0x2fda(%rip)        # 4040 <munmap>
    1066:	68 05 00 00 00       	push   $0x5
    106b:	e9 90 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001070 <split_block@plt>:
    1070:	ff 25 d2 2f 00 00    	jmp    *0x2fd2(%rip)        # 4048 <split_block>
    1076:	68 06 00 00 00       	push   $0x6
    107b:	e9 80 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001080 <insert_free_block@plt>:
    1080:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 4050 <insert_free_block>
    1086:	68 07 00 00 00       	push   $0x7
    108b:	e9 70 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001090 <get_payload_size@plt>:
    1090:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 4058 <get_payload_size>
    1096:	68 08 00 00 00       	push   $0x8
    109b:	e9 60 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010a0 <getpagesize@plt>:
    10a0:	ff 25 ba 2f 00 00    	jmp    *0x2fba(%rip)        # 4060 <getpagesize>
    10a6:	68 09 00 00 00       	push   $0x9
    10ab:	e9 50 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010b0 <payload_to_header@plt>:
    10b0:	ff 25 b2 2f 00 00    	jmp    *0x2fb2(%rip)        # 4068 <payload_to_header>
    10b6:	68 0a 00 00 00       	push   $0xa
    10bb:	e9 40 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010c0 <memcpy@plt>:
    10c0:	ff 25 aa 2f 00 00    	jmp    *0x2faa(%rip)        # 4070 <memcpy>
    10c6:	68 0b 00 00 00       	push   $0xb
    10cb:	e9 30 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010d0 <malloc@plt>:
    10d0:	ff 25 a2 2f 00 00    	jmp    *0x2fa2(%rip)        # 4078 <malloc+0x2d78>
    10d6:	68 0c 00 00 00       	push   $0xc
    10db:	e9 20 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010e0 <extend_heap@plt>:
    10e0:	ff 25 9a 2f 00 00    	jmp    *0x2f9a(%rip)        # 4080 <extend_heap>
    10e6:	68 0d 00 00 00       	push   $0xd
    10eb:	e9 10 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000010f0 <get_prev_alloc@plt>:
    10f0:	ff 25 92 2f 00 00    	jmp    *0x2f92(%rip)        # 4088 <get_prev_alloc>
    10f6:	68 0e 00 00 00       	push   $0xe
    10fb:	e9 00 ff ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001100 <get_prev_mini@plt>:
    1100:	ff 25 8a 2f 00 00    	jmp    *0x2f8a(%rip)        # 4090 <get_prev_mini>
    1106:	68 0f 00 00 00       	push   $0xf
    110b:	e9 f0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001110 <mmap@plt>:
    1110:	ff 25 82 2f 00 00    	jmp    *0x2f82(%rip)        # 4098 <mmap>
    1116:	68 10 00 00 00       	push   $0x10
    111b:	e9 e0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001120 <init_heap@plt>:
    1120:	ff 25 7a 2f 00 00    	jmp    *0x2f7a(%rip)        # 40a0 <init_heap+0x2ea0>
    1126:	68 11 00 00 00       	push   $0x11
    112b:	e9 d0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001130 <fprintf@plt>:
    1130:	ff 25 72 2f 00 00    	jmp    *0x2f72(%rip)        # 40a8 <fprintf>
    1136:	68 12 00 00 00       	push   $0x12
    113b:	e9 c0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001140 <coalesce_block@plt>:
    1140:	ff 25 6a 2f 00 00    	jmp    *0x2f6a(%rip)        # 40b0 <coalesce_block>
    1146:	68 13 00 00 00       	push   $0x13
    114b:	e9 b0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001150 <max@plt>:
    1150:	ff 25 62 2f 00 00    	jmp    *0x2f62(%rip)        # 40b8 <max>
    1156:	68 14 00 00 00       	push   $0x14
    115b:	e9 a0 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001160 <memset@plt>:
    1160:	ff 25 5a 2f 00 00    	jmp    *0x2f5a(%rip)        # 40c0 <memset>
    1166:	68 15 00 00 00       	push   $0x15
    116b:	e9 90 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001170 <__assert_fail@plt>:
    1170:	ff 25 52 2f 00 00    	jmp    *0x2f52(%rip)        # 40c8 <__assert_fail>
    1176:	68 16 00 00 00       	push   $0x16
    117b:	e9 80 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001180 <write_block@plt>:
    1180:	ff 25 4a 2f 00 00    	jmp    *0x2f4a(%rip)        # 40d0 <write_block>
    1186:	68 17 00 00 00       	push   $0x17
    118b:	e9 70 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

0000000000001190 <__errno_location@plt>:
    1190:	ff 25 42 2f 00 00    	jmp    *0x2f42(%rip)        # 40d8 <__errno_location>
    1196:	68 18 00 00 00       	push   $0x18
    119b:	e9 60 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011a0 <exit@plt>:
    11a0:	ff 25 3a 2f 00 00    	jmp    *0x2f3a(%rip)        # 40e0 <exit>
    11a6:	68 19 00 00 00       	push   $0x19
    11ab:	e9 50 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011b0 <get_size@plt>:
    11b0:	ff 25 32 2f 00 00    	jmp    *0x2f32(%rip)        # 40e8 <get_size>
    11b6:	68 1a 00 00 00       	push   $0x1a
    11bb:	e9 40 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011c0 <mprotect@plt>:
    11c0:	ff 25 2a 2f 00 00    	jmp    *0x2f2a(%rip)        # 40f0 <mprotect>
    11c6:	68 1b 00 00 00       	push   $0x1b
    11cb:	e9 30 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011d0 <header_to_payload@plt>:
    11d0:	ff 25 22 2f 00 00    	jmp    *0x2f22(%rip)        # 40f8 <header_to_payload>
    11d6:	68 1c 00 00 00       	push   $0x1c
    11db:	e9 20 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011e0 <free@plt>:
    11e0:	ff 25 1a 2f 00 00    	jmp    *0x2f1a(%rip)        # 4100 <free+0x2cc0>
    11e6:	68 1d 00 00 00       	push   $0x1d
    11eb:	e9 10 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

00000000000011f0 <pack@plt>:
    11f0:	ff 25 12 2f 00 00    	jmp    *0x2f12(%rip)        # 4108 <pack>
    11f6:	68 1e 00 00 00       	push   $0x1e
    11fb:	e9 00 fe ff ff       	jmp    1000 <find_fit@plt-0x10>

Disassembly of section .text:

0000000000001200 <init_heap>:
    1200:	55                   	push   %rbp
    1201:	48 89 e5             	mov    %rsp,%rbp
    1204:	48 83 ec 20          	sub    $0x20,%rsp
    1208:	bf 10 00 00 00       	mov    $0x10,%edi
    120d:	e8 2e fe ff ff       	call   1040 <extend_bmp@plt>
    1212:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1216:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    121d:	48 39 45 f0          	cmp    %rax,-0x10(%rbp)
    1221:	0f 85 09 00 00 00    	jne    1230 <init_heap+0x30>
    1227:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
    122b:	e9 b4 00 00 00       	jmp    12e4 <init_heap+0xe4>
    1230:	31 c0                	xor    %eax,%eax
    1232:	89 c7                	mov    %eax,%edi
    1234:	ba 01 00 00 00       	mov    $0x1,%edx
    1239:	31 c9                	xor    %ecx,%ecx
    123b:	89 d6                	mov    %edx,%esi
    123d:	e8 ae ff ff ff       	call   11f0 <pack@plt>
    1242:	48 89 c1             	mov    %rax,%rcx
    1245:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1249:	48 89 08             	mov    %rcx,(%rax)
    124c:	31 c0                	xor    %eax,%eax
    124e:	89 c7                	mov    %eax,%edi
    1250:	ba 01 00 00 00       	mov    $0x1,%edx
    1255:	31 c9                	xor    %ecx,%ecx
    1257:	89 d6                	mov    %edx,%esi
    1259:	e8 92 ff ff ff       	call   11f0 <pack@plt>
    125e:	48 89 c1             	mov    %rax,%rcx
    1261:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1265:	48 89 48 08          	mov    %rcx,0x8(%rax)
    1269:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    126d:	48 83 c0 08          	add    $0x8,%rax
    1271:	48 89 05 a8 2e 00 00 	mov    %rax,0x2ea8(%rip)        # 4120 <heap_start>
    1278:	48 c7 05 8d 2e 00 00 	movq   $0x1000,0x2e8d(%rip)        # 4110 <chunksize>
    127f:	00 10 00 00 
    1283:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%rbp)
    128a:	83 7d ec 09          	cmpl   $0x9,-0x14(%rbp)
    128e:	0f 8d 21 00 00 00    	jge    12b5 <init_heap+0xb5>
    1294:	48 63 4d ec          	movslq -0x14(%rbp),%rcx
    1298:	48 8d 05 91 2e 00 00 	lea    0x2e91(%rip),%rax        # 4130 <seglists>
    129f:	48 c7 04 c8 00 00 00 	movq   $0x0,(%rax,%rcx,8)
    12a6:	00 
    12a7:	8b 45 ec             	mov    -0x14(%rbp),%eax
    12aa:	83 c0 01             	add    $0x1,%eax
    12ad:	89 45 ec             	mov    %eax,-0x14(%rbp)
    12b0:	e9 d5 ff ff ff       	jmp    128a <init_heap+0x8a>
    12b5:	48 8b 3d 54 2e 00 00 	mov    0x2e54(%rip),%rdi        # 4110 <chunksize>
    12bc:	e8 1f fe ff ff       	call   10e0 <extend_heap@plt>
    12c1:	48 83 f8 00          	cmp    $0x0,%rax
    12c5:	0f 85 09 00 00 00    	jne    12d4 <init_heap+0xd4>
    12cb:	c6 45 ff 00          	movb   $0x0,-0x1(%rbp)
    12cf:	e9 10 00 00 00       	jmp    12e4 <init_heap+0xe4>
    12d4:	48 8b 3d 45 2e 00 00 	mov    0x2e45(%rip),%rdi        # 4120 <heap_start>
    12db:	e8 a0 fd ff ff       	call   1080 <insert_free_block@plt>
    12e0:	c6 45 ff 01          	movb   $0x1,-0x1(%rbp)
    12e4:	8a 45 ff             	mov    -0x1(%rbp),%al
    12e7:	24 01                	and    $0x1,%al
    12e9:	0f b6 c0             	movzbl %al,%eax
    12ec:	48 83 c4 20          	add    $0x20,%rsp
    12f0:	5d                   	pop    %rbp
    12f1:	c3                   	ret    
    12f2:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    12f9:	00 00 00 
    12fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001300 <malloc>:
    1300:	55                   	push   %rbp
    1301:	48 89 e5             	mov    %rsp,%rbp
    1304:	48 83 ec 40          	sub    $0x40,%rsp
    1308:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
    130c:	48 c7 45 d0 00 00 00 	movq   $0x0,-0x30(%rbp)
    1313:	00 
    1314:	48 83 3d 04 2e 00 00 	cmpq   $0x0,0x2e04(%rip)        # 4120 <heap_start>
    131b:	00 
    131c:	0f 85 05 00 00 00    	jne    1327 <malloc+0x27>
    1322:	e8 f9 fd ff ff       	call   1120 <init_heap@plt>
    1327:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
    132c:	0f 85 0d 00 00 00    	jne    133f <malloc+0x3f>
    1332:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1336:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    133a:	e9 f6 00 00 00       	jmp    1435 <malloc+0x135>
    133f:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    1343:	48 83 c7 08          	add    $0x8,%rdi
    1347:	be 10 00 00 00       	mov    $0x10,%esi
    134c:	e8 df fc ff ff       	call   1030 <round_up@plt>
    1351:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1355:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    1359:	be 10 00 00 00       	mov    $0x10,%esi
    135e:	e8 ed fd ff ff       	call   1150 <max@plt>
    1363:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1367:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    136b:	e8 a0 fc ff ff       	call   1010 <find_fit@plt>
    1370:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    1374:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
    1379:	0f 85 3e 00 00 00    	jne    13bd <malloc+0xbd>
    137f:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    1383:	48 8b 35 86 2d 00 00 	mov    0x2d86(%rip),%rsi        # 4110 <chunksize>
    138a:	e8 c1 fd ff ff       	call   1150 <max@plt>
    138f:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    1393:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
    1397:	e8 44 fd ff ff       	call   10e0 <extend_heap@plt>
    139c:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    13a0:	48 83 7d d8 00       	cmpq   $0x0,-0x28(%rbp)
    13a5:	0f 85 0d 00 00 00    	jne    13b8 <malloc+0xb8>
    13ab:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    13af:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    13b3:	e9 7d 00 00 00       	jmp    1435 <malloc+0x135>
    13b8:	e9 00 00 00 00       	jmp    13bd <malloc+0xbd>
    13bd:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    13c1:	e8 ea fd ff ff       	call   11b0 <get_size@plt>
    13c6:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    13ca:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    13ce:	e8 4d fc ff ff       	call   1020 <remove_free_block@plt>
    13d3:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    13d7:	e8 14 fd ff ff       	call   10f0 <get_prev_alloc@plt>
    13dc:	24 01                	and    $0x1,%al
    13de:	88 45 c7             	mov    %al,-0x39(%rbp)
    13e1:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    13e5:	e8 16 fd ff ff       	call   1100 <get_prev_mini@plt>
    13ea:	24 01                	and    $0x1,%al
    13ec:	88 45 c6             	mov    %al,-0x3a(%rbp)
    13ef:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    13f3:	48 8b 75 c8          	mov    -0x38(%rbp),%rsi
    13f7:	8a 4d c7             	mov    -0x39(%rbp),%cl
    13fa:	8a 45 c6             	mov    -0x3a(%rbp),%al
    13fd:	ba 01 00 00 00       	mov    $0x1,%edx
    1402:	80 e1 01             	and    $0x1,%cl
    1405:	24 01                	and    $0x1,%al
    1407:	0f b6 c9             	movzbl %cl,%ecx
    140a:	44 0f b6 c0          	movzbl %al,%r8d
    140e:	e8 6d fd ff ff       	call   1180 <write_block@plt>
    1413:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    1417:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
    141b:	e8 50 fc ff ff       	call   1070 <split_block@plt>
    1420:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    1424:	e8 a7 fd ff ff       	call   11d0 <header_to_payload@plt>
    1429:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    142d:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1431:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1435:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1439:	48 83 c4 40          	add    $0x40,%rsp
    143d:	5d                   	pop    %rbp
    143e:	c3                   	ret    
    143f:	90                   	nop

0000000000001440 <free>:
    1440:	55                   	push   %rbp
    1441:	48 89 e5             	mov    %rsp,%rbp
    1444:	48 83 ec 20          	sub    $0x20,%rsp
    1448:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    144c:	48 83 7d f8 00       	cmpq   $0x0,-0x8(%rbp)
    1451:	0f 85 05 00 00 00    	jne    145c <free+0x1c>
    1457:	e9 69 00 00 00       	jmp    14c5 <free+0x85>
    145c:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
    1460:	e8 4b fc ff ff       	call   10b0 <payload_to_header@plt>
    1465:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    1469:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    146d:	e8 3e fd ff ff       	call   11b0 <get_size@plt>
    1472:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1476:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    147a:	e8 71 fc ff ff       	call   10f0 <get_prev_alloc@plt>
    147f:	24 01                	and    $0x1,%al
    1481:	88 45 e7             	mov    %al,-0x19(%rbp)
    1484:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    1488:	e8 73 fc ff ff       	call   1100 <get_prev_mini@plt>
    148d:	24 01                	and    $0x1,%al
    148f:	88 45 e6             	mov    %al,-0x1a(%rbp)
    1492:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    1496:	48 8b 75 e8          	mov    -0x18(%rbp),%rsi
    149a:	8a 4d e7             	mov    -0x19(%rbp),%cl
    149d:	8a 45 e6             	mov    -0x1a(%rbp),%al
    14a0:	31 d2                	xor    %edx,%edx
    14a2:	80 e1 01             	and    $0x1,%cl
    14a5:	24 01                	and    $0x1,%al
    14a7:	0f b6 c9             	movzbl %cl,%ecx
    14aa:	44 0f b6 c0          	movzbl %al,%r8d
    14ae:	e8 cd fc ff ff       	call   1180 <write_block@plt>
    14b3:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    14b7:	e8 c4 fb ff ff       	call   1080 <insert_free_block@plt>
    14bc:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    14c0:	e8 7b fc ff ff       	call   1140 <coalesce_block@plt>
    14c5:	48 83 c4 20          	add    $0x20,%rsp
    14c9:	5d                   	pop    %rbp
    14ca:	c3                   	ret    
    14cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000014d0 <realloc>:
    14d0:	55                   	push   %rbp
    14d1:	48 89 e5             	mov    %rsp,%rbp
    14d4:	48 83 ec 30          	sub    $0x30,%rsp
    14d8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
    14dc:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
    14e0:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    14e4:	e8 c7 fb ff ff       	call   10b0 <payload_to_header@plt>
    14e9:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    14ed:	48 83 7d e8 00       	cmpq   $0x0,-0x18(%rbp)
    14f2:	0f 85 16 00 00 00    	jne    150e <realloc+0x3e>
    14f8:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    14fc:	e8 df fc ff ff       	call   11e0 <free@plt>
    1501:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    1508:	00 
    1509:	e9 87 00 00 00       	jmp    1595 <realloc+0xc5>
    150e:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
    1513:	0f 85 12 00 00 00    	jne    152b <realloc+0x5b>
    1519:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    151d:	e8 ae fb ff ff       	call   10d0 <malloc@plt>
    1522:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1526:	e9 6a 00 00 00       	jmp    1595 <realloc+0xc5>
    152b:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    152f:	e8 9c fb ff ff       	call   10d0 <malloc@plt>
    1534:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    1538:	48 83 7d d0 00       	cmpq   $0x0,-0x30(%rbp)
    153d:	0f 85 0d 00 00 00    	jne    1550 <realloc+0x80>
    1543:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    154a:	00 
    154b:	e9 45 00 00 00       	jmp    1595 <realloc+0xc5>
    1550:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
    1554:	e8 37 fb ff ff       	call   1090 <get_payload_size@plt>
    1559:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    155d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1561:	48 3b 45 d8          	cmp    -0x28(%rbp),%rax
    1565:	0f 83 08 00 00 00    	jae    1573 <realloc+0xa3>
    156b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    156f:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    1573:	48 8b 7d d0          	mov    -0x30(%rbp),%rdi
    1577:	48 8b 75 f0          	mov    -0x10(%rbp),%rsi
    157b:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    157f:	e8 3c fb ff ff       	call   10c0 <memcpy@plt>
    1584:	48 8b 7d f0          	mov    -0x10(%rbp),%rdi
    1588:	e8 53 fc ff ff       	call   11e0 <free@plt>
    158d:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1591:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1595:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1599:	48 83 c4 30          	add    $0x30,%rsp
    159d:	5d                   	pop    %rbp
    159e:	c3                   	ret    
    159f:	90                   	nop

00000000000015a0 <calloc>:
    15a0:	55                   	push   %rbp
    15a1:	48 89 e5             	mov    %rsp,%rbp
    15a4:	48 83 ec 30          	sub    $0x30,%rsp
    15a8:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
    15ac:	48 89 75 e8          	mov    %rsi,-0x18(%rbp)
    15b0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    15b4:	48 0f af 45 e8       	imul   -0x18(%rbp),%rax
    15b9:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    15bd:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
    15c2:	0f 85 0d 00 00 00    	jne    15d5 <calloc+0x35>
    15c8:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    15cf:	00 
    15d0:	e9 5f 00 00 00       	jmp    1634 <calloc+0x94>
    15d5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    15d9:	31 c9                	xor    %ecx,%ecx
    15db:	89 ca                	mov    %ecx,%edx
    15dd:	48 f7 75 f0          	divq   -0x10(%rbp)
    15e1:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
    15e5:	0f 84 0d 00 00 00    	je     15f8 <calloc+0x58>
    15eb:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    15f2:	00 
    15f3:	e9 3c 00 00 00       	jmp    1634 <calloc+0x94>
    15f8:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    15fc:	e8 cf fa ff ff       	call   10d0 <malloc@plt>
    1601:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    1605:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
    160a:	0f 85 0d 00 00 00    	jne    161d <calloc+0x7d>
    1610:	48 c7 45 f8 00 00 00 	movq   $0x0,-0x8(%rbp)
    1617:	00 
    1618:	e9 17 00 00 00       	jmp    1634 <calloc+0x94>
    161d:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
    1621:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    1625:	31 f6                	xor    %esi,%esi
    1627:	e8 34 fb ff ff       	call   1160 <memset@plt>
    162c:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    1630:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1634:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1638:	48 83 c4 30          	add    $0x30,%rsp
    163c:	5d                   	pop    %rbp
    163d:	c3                   	ret    
    163e:	66 90                	xchg   %ax,%ax

0000000000001640 <heap_init>:
    1640:	55                   	push   %rbp
    1641:	48 89 e5             	mov    %rsp,%rbp
    1644:	48 83 ec 20          	sub    $0x20,%rsp
    1648:	b8 00 00 00 08       	mov    $0x8000000,%eax
    164d:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1651:	c7 45 f4 03 00 00 00 	movl   $0x3,-0xc(%rbp)
    1658:	48 8b 7d f8          	mov    -0x8(%rbp),%rdi
    165c:	48 8b 35 b5 2a 00 00 	mov    0x2ab5(%rip),%rsi        # 4118 <init_mmap_length>
    1663:	8b 55 f4             	mov    -0xc(%rbp),%edx
    1666:	b9 22 00 00 00       	mov    $0x22,%ecx
    166b:	41 b8 ff ff ff ff    	mov    $0xffffffff,%r8d
    1671:	31 c0                	xor    %eax,%eax
    1673:	41 89 c1             	mov    %eax,%r9d
    1676:	e8 95 fa ff ff       	call   1110 <mmap@plt>
    167b:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    167f:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    1686:	48 39 45 e8          	cmp    %rax,-0x18(%rbp)
    168a:	0f 85 39 00 00 00    	jne    16c9 <heap_init+0x89>
    1690:	48 8b 05 61 29 00 00 	mov    0x2961(%rip),%rax        # 3ff8 <stderr>
    1697:	48 8b 00             	mov    (%rax),%rax
    169a:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    169e:	e8 ed fa ff ff       	call   1190 <__errno_location@plt>
    16a3:	8b 38                	mov    (%rax),%edi
    16a5:	e8 a6 f9 ff ff       	call   1050 <strerror@plt>
    16aa:	48 8b 7d e0          	mov    -0x20(%rbp),%rdi
    16ae:	48 89 c2             	mov    %rax,%rdx
    16b1:	48 8d 35 48 09 00 00 	lea    0x948(%rip),%rsi        # 2000 <current_arena_usage+0x5c0>
    16b8:	b0 00                	mov    $0x0,%al
    16ba:	e8 71 fa ff ff       	call   1130 <fprintf@plt>
    16bf:	bf 01 00 00 00       	mov    $0x1,%edi
    16c4:	e8 d7 fa ff ff       	call   11a0 <exit@plt>
    16c9:	e8 d2 f9 ff ff       	call   10a0 <getpagesize@plt>
    16ce:	48 98                	cltq   
    16d0:	48 89 05 a1 2a 00 00 	mov    %rax,0x2aa1(%rip)        # 4178 <pagesize>
    16d7:	48 8b 7d e8          	mov    -0x18(%rbp),%rdi
    16db:	48 8b 35 96 2a 00 00 	mov    0x2a96(%rip),%rsi        # 4178 <pagesize>
    16e2:	e8 79 00 00 00       	call   1760 <round_address_down>
    16e7:	48 3b 45 e8          	cmp    -0x18(%rbp),%rax
    16eb:	0f 84 26 00 00 00    	je     1717 <heap_init+0xd7>
    16f1:	48 8b 05 00 29 00 00 	mov    0x2900(%rip),%rax        # 3ff8 <stderr>
    16f8:	48 8b 38             	mov    (%rax),%rdi
    16fb:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    16ff:	48 8d 35 30 09 00 00 	lea    0x930(%rip),%rsi        # 2036 <current_arena_usage+0x5f6>
    1706:	b0 00                	mov    $0x0,%al
    1708:	e8 23 fa ff ff       	call   1130 <fprintf@plt>
    170d:	bf 01 00 00 00       	mov    $0x1,%edi
    1712:	e8 89 fa ff ff       	call   11a0 <exit@plt>
    1717:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    171b:	48 89 05 5e 2a 00 00 	mov    %rax,0x2a5e(%rip)        # 4180 <heap>
    1722:	48 8b 05 57 2a 00 00 	mov    0x2a57(%rip),%rax        # 4180 <heap>
    1729:	48 03 05 e8 29 00 00 	add    0x29e8(%rip),%rax        # 4118 <init_mmap_length>
    1730:	48 89 05 51 2a 00 00 	mov    %rax,0x2a51(%rip)        # 4188 <mem_max_addr>
    1737:	48 8b 05 42 2a 00 00 	mov    0x2a42(%rip),%rax        # 4180 <heap>
    173e:	48 89 05 4b 2a 00 00 	mov    %rax,0x2a4b(%rip)        # 4190 <mem_brk>
    1745:	48 8b 05 34 2a 00 00 	mov    0x2a34(%rip),%rax        # 4180 <heap>
    174c:	48 89 05 45 2a 00 00 	mov    %rax,0x2a45(%rip)        # 4198 <mem_brk_chunk>
    1753:	48 83 c4 20          	add    $0x20,%rsp
    1757:	5d                   	pop    %rbp
    1758:	c3                   	ret    
    1759:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001760 <round_address_down>:
    1760:	55                   	push   %rbp
    1761:	48 89 e5             	mov    %rsp,%rbp
    1764:	48 83 ec 10          	sub    $0x10,%rsp
    1768:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    176c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1770:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    1774:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    1778:	48 83 e9 01          	sub    $0x1,%rcx
    177c:	48 21 c8             	and    %rcx,%rax
    177f:	48 83 f8 00          	cmp    $0x0,%rax
    1783:	0f 85 05 00 00 00    	jne    178e <round_address_down+0x2e>
    1789:	e9 1f 00 00 00       	jmp    17ad <round_address_down+0x4d>
    178e:	48 8d 3d b1 09 00 00 	lea    0x9b1(%rip),%rdi        # 2146 <current_arena_usage+0x706>
    1795:	48 8d 35 c5 09 00 00 	lea    0x9c5(%rip),%rsi        # 2161 <current_arena_usage+0x721>
    179c:	ba 15 00 00 00       	mov    $0x15,%edx
    17a1:	48 8d 0d ca 09 00 00 	lea    0x9ca(%rip),%rcx        # 2172 <current_arena_usage+0x732>
    17a8:	e8 c3 f9 ff ff       	call   1170 <__assert_fail@plt>
    17ad:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    17b1:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    17b5:	48 83 e9 01          	sub    $0x1,%rcx
    17b9:	48 83 f1 ff          	xor    $0xffffffffffffffff,%rcx
    17bd:	48 21 c8             	and    %rcx,%rax
    17c0:	48 83 c4 10          	add    $0x10,%rsp
    17c4:	5d                   	pop    %rbp
    17c5:	c3                   	ret    
    17c6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    17cd:	00 00 00 

00000000000017d0 <heap_deinit>:
    17d0:	55                   	push   %rbp
    17d1:	48 89 e5             	mov    %rsp,%rbp
    17d4:	48 8b 3d a5 29 00 00 	mov    0x29a5(%rip),%rdi        # 4180 <heap>
    17db:	48 8b 35 36 29 00 00 	mov    0x2936(%rip),%rsi        # 4118 <init_mmap_length>
    17e2:	e8 79 f8 ff ff       	call   1060 <munmap@plt>
    17e7:	5d                   	pop    %rbp
    17e8:	c3                   	ret    
    17e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000017f0 <reset_bmp_ptr>:
    17f0:	55                   	push   %rbp
    17f1:	48 89 e5             	mov    %rsp,%rbp
    17f4:	48 8b 05 85 29 00 00 	mov    0x2985(%rip),%rax        # 4180 <heap>
    17fb:	48 89 05 8e 29 00 00 	mov    %rax,0x298e(%rip)        # 4190 <mem_brk>
    1802:	48 8b 05 77 29 00 00 	mov    0x2977(%rip),%rax        # 4180 <heap>
    1809:	48 89 05 88 29 00 00 	mov    %rax,0x2988(%rip)        # 4198 <mem_brk_chunk>
    1810:	5d                   	pop    %rbp
    1811:	c3                   	ret    
    1812:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    1819:	00 00 00 
    181c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001820 <extend_bmp>:
    1820:	55                   	push   %rbp
    1821:	48 89 e5             	mov    %rsp,%rbp
    1824:	48 83 ec 50          	sub    $0x50,%rsp
    1828:	48 89 7d f0          	mov    %rdi,-0x10(%rbp)
    182c:	48 8b 05 5d 29 00 00 	mov    0x295d(%rip),%rax        # 4190 <mem_brk>
    1833:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    1837:	48 83 7d f0 00       	cmpq   $0x0,-0x10(%rbp)
    183c:	0f 8d 37 00 00 00    	jge    1879 <extend_bmp+0x59>
    1842:	48 8b 05 af 27 00 00 	mov    0x27af(%rip),%rax        # 3ff8 <stderr>
    1849:	48 8b 38             	mov    (%rax),%rdi
    184c:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    1850:	48 8d 35 18 08 00 00 	lea    0x818(%rip),%rsi        # 206f <current_arena_usage+0x62f>
    1857:	b0 00                	mov    $0x0,%al
    1859:	e8 d2 f8 ff ff       	call   1130 <fprintf@plt>
    185e:	e8 2d f9 ff ff       	call   1190 <__errno_location@plt>
    1863:	c7 00 16 00 00 00    	movl   $0x16,(%rax)
    1869:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    1870:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1874:	e9 47 01 00 00       	jmp    19c0 <extend_bmp+0x1a0>
    1879:	48 8b 05 10 29 00 00 	mov    0x2910(%rip),%rax        # 4190 <mem_brk>
    1880:	48 03 45 f0          	add    -0x10(%rbp),%rax
    1884:	48 3b 05 fd 28 00 00 	cmp    0x28fd(%rip),%rax        # 4188 <mem_max_addr>
    188b:	0f 86 54 00 00 00    	jbe    18e5 <extend_bmp+0xc5>
    1891:	48 8b 05 f8 28 00 00 	mov    0x28f8(%rip),%rax        # 4190 <mem_brk>
    1898:	48 8b 0d e1 28 00 00 	mov    0x28e1(%rip),%rcx        # 4180 <heap>
    189f:	48 29 c8             	sub    %rcx,%rax
    18a2:	48 03 45 f0          	add    -0x10(%rbp),%rax
    18a6:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
    18aa:	48 8b 05 47 27 00 00 	mov    0x2747(%rip),%rax        # 3ff8 <stderr>
    18b1:	48 8b 38             	mov    (%rax),%rdi
    18b4:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    18b8:	48 8b 4d e0          	mov    -0x20(%rbp),%rcx
    18bc:	48 8d 35 f3 07 00 00 	lea    0x7f3(%rip),%rsi        # 20b6 <current_arena_usage+0x676>
    18c3:	b0 00                	mov    $0x0,%al
    18c5:	e8 66 f8 ff ff       	call   1130 <fprintf@plt>
    18ca:	e8 c1 f8 ff ff       	call   1190 <__errno_location@plt>
    18cf:	c7 00 0c 00 00 00    	movl   $0xc,(%rax)
    18d5:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    18dc:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    18e0:	e9 db 00 00 00       	jmp    19c0 <extend_bmp+0x1a0>
    18e5:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    18e9:	48 03 45 f0          	add    -0x10(%rbp),%rax
    18ed:	48 89 45 d8          	mov    %rax,-0x28(%rbp)
    18f1:	48 8b 7d d8          	mov    -0x28(%rbp),%rdi
    18f5:	48 8b 35 7c 28 00 00 	mov    0x287c(%rip),%rsi        # 4178 <pagesize>
    18fc:	e8 cf 00 00 00       	call   19d0 <round_address_up>
    1901:	48 89 45 d0          	mov    %rax,-0x30(%rbp)
    1905:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1909:	48 3b 05 88 28 00 00 	cmp    0x2888(%rip),%rax        # 4198 <mem_brk_chunk>
    1910:	0f 86 8c 00 00 00    	jbe    19a2 <extend_bmp+0x182>
    1916:	48 8b 3d 7b 28 00 00 	mov    0x287b(%rip),%rdi        # 4198 <mem_brk_chunk>
    191d:	48 8b 75 d0          	mov    -0x30(%rbp),%rsi
    1921:	48 8b 05 70 28 00 00 	mov    0x2870(%rip),%rax        # 4198 <mem_brk_chunk>
    1928:	48 29 c6             	sub    %rax,%rsi
    192b:	ba 03 00 00 00       	mov    $0x3,%edx
    1930:	e8 8b f8 ff ff       	call   11c0 <mprotect@plt>
    1935:	83 f8 ff             	cmp    $0xffffffff,%eax
    1938:	0f 85 64 00 00 00    	jne    19a2 <extend_bmp+0x182>
    193e:	48 8b 05 b3 26 00 00 	mov    0x26b3(%rip),%rax        # 3ff8 <stderr>
    1945:	48 8b 00             	mov    (%rax),%rax
    1948:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
    194c:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    1950:	48 8b 0d 41 28 00 00 	mov    0x2841(%rip),%rcx        # 4198 <mem_brk_chunk>
    1957:	48 29 c8             	sub    %rcx,%rax
    195a:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
    195e:	48 8b 05 33 28 00 00 	mov    0x2833(%rip),%rax        # 4198 <mem_brk_chunk>
    1965:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    1969:	e8 22 f8 ff ff       	call   1190 <__errno_location@plt>
    196e:	8b 38                	mov    (%rax),%edi
    1970:	e8 db f6 ff ff       	call   1050 <strerror@plt>
    1975:	48 8b 7d b8          	mov    -0x48(%rbp),%rdi
    1979:	48 8b 55 c0          	mov    -0x40(%rbp),%rdx
    197d:	48 8b 4d c8          	mov    -0x38(%rbp),%rcx
    1981:	49 89 c0             	mov    %rax,%r8
    1984:	48 8d 35 85 07 00 00 	lea    0x785(%rip),%rsi        # 2110 <current_arena_usage+0x6d0>
    198b:	b0 00                	mov    $0x0,%al
    198d:	e8 9e f7 ff ff       	call   1130 <fprintf@plt>
    1992:	48 c7 c0 ff ff ff ff 	mov    $0xffffffffffffffff,%rax
    1999:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    199d:	e9 1e 00 00 00       	jmp    19c0 <extend_bmp+0x1a0>
    19a2:	48 8b 45 d0          	mov    -0x30(%rbp),%rax
    19a6:	48 89 05 eb 27 00 00 	mov    %rax,0x27eb(%rip)        # 4198 <mem_brk_chunk>
    19ad:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    19b1:	48 89 05 d8 27 00 00 	mov    %rax,0x27d8(%rip)        # 4190 <mem_brk>
    19b8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    19bc:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    19c0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    19c4:	48 83 c4 50          	add    $0x50,%rsp
    19c8:	5d                   	pop    %rbp
    19c9:	c3                   	ret    
    19ca:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

00000000000019d0 <round_address_up>:
    19d0:	55                   	push   %rbp
    19d1:	48 89 e5             	mov    %rsp,%rbp
    19d4:	48 83 ec 10          	sub    $0x10,%rsp
    19d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    19dc:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    19e0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    19e4:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    19e8:	48 83 e9 01          	sub    $0x1,%rcx
    19ec:	48 21 c8             	and    %rcx,%rax
    19ef:	48 83 f8 00          	cmp    $0x0,%rax
    19f3:	0f 85 05 00 00 00    	jne    19fe <round_address_up+0x2e>
    19f9:	e9 1f 00 00 00       	jmp    1a1d <round_address_up+0x4d>
    19fe:	48 8d 3d 41 07 00 00 	lea    0x741(%rip),%rdi        # 2146 <current_arena_usage+0x706>
    1a05:	48 8d 35 55 07 00 00 	lea    0x755(%rip),%rsi        # 2161 <current_arena_usage+0x721>
    1a0c:	ba 21 00 00 00       	mov    $0x21,%edx
    1a11:	48 8d 0d 83 07 00 00 	lea    0x783(%rip),%rcx        # 219b <current_arena_usage+0x75b>
    1a18:	e8 53 f7 ff ff       	call   1170 <__assert_fail@plt>
    1a1d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1a21:	48 03 45 f0          	add    -0x10(%rbp),%rax
    1a25:	48 83 e8 01          	sub    $0x1,%rax
    1a29:	48 8b 4d f0          	mov    -0x10(%rbp),%rcx
    1a2d:	48 83 e9 01          	sub    $0x1,%rcx
    1a31:	48 83 f1 ff          	xor    $0xffffffffffffffff,%rcx
    1a35:	48 21 c8             	and    %rcx,%rax
    1a38:	48 83 c4 10          	add    $0x10,%rsp
    1a3c:	5d                   	pop    %rbp
    1a3d:	c3                   	ret    
    1a3e:	66 90                	xchg   %ax,%ax

0000000000001a40 <current_arena_usage>:
    1a40:	55                   	push   %rbp
    1a41:	48 89 e5             	mov    %rsp,%rbp
    1a44:	48 8b 05 45 27 00 00 	mov    0x2745(%rip),%rax        # 4190 <mem_brk>
    1a4b:	48 8b 0d 2e 27 00 00 	mov    0x272e(%rip),%rcx        # 4180 <heap>
    1a52:	48 29 c8             	sub    %rcx,%rax
    1a55:	5d                   	pop    %rbp
    1a56:	c3                   	ret    

Disassembly of section .rodata:

0000000000002000 <.rodata>:
    2000:	46                   	rex.RX
    2001:	41                   	rex.B
    2002:	49                   	rex.WB
    2003:	4c 55                	rex.WR push %rbp
    2005:	52                   	push   %rdx
    2006:	45                   	rex.RB
    2007:	2e 20 20             	cs and %ah,(%rax)
    200a:	6d                   	insl   (%dx),%es:(%rdi)
    200b:	6d                   	insl   (%dx),%es:(%rdi)
    200c:	61                   	(bad)  
    200d:	70 20                	jo     202f <current_arena_usage+0x5ef>
    200f:	63 6f 75             	movsxd 0x75(%rdi),%ebp
    2012:	6c                   	insb   (%dx),%es:(%rdi)
    2013:	64 6e                	outsb  %fs:(%rsi),(%dx)
    2015:	27                   	(bad)  
    2016:	74 20                	je     2038 <current_arena_usage+0x5f8>
    2018:	61                   	(bad)  
    2019:	6c                   	insb   (%dx),%es:(%rdi)
    201a:	6c                   	insb   (%dx),%es:(%rdi)
    201b:	6f                   	outsl  %ds:(%rsi),(%dx)
    201c:	63 61 74             	movsxd 0x74(%rcx),%esp
    201f:	65 20 73 70          	and    %dh,%gs:0x70(%rbx)
    2023:	61                   	(bad)  
    2024:	63 65 20             	movsxd 0x20(%rbp),%esp
    2027:	66 6f                	outsw  %ds:(%rsi),(%dx)
    2029:	72 20                	jb     204b <current_arena_usage+0x60b>
    202b:	68 65 61 70 20       	push   $0x20706165
    2030:	28 25 73 29 0a 00    	sub    %ah,0xa2973(%rip)        # a49a9 <mem_brk_chunk+0xa0811>
    2036:	46                   	rex.RX
    2037:	41                   	rex.B
    2038:	49                   	rex.WB
    2039:	4c 55                	rex.WR push %rbp
    203b:	52                   	push   %rdx
    203c:	45                   	rex.RB
    203d:	2e 20 20             	cs and %ah,(%rax)
    2040:	49 6e                	rex.WB outsb %ds:(%rsi),(%dx)
    2042:	69 74 69 61 6c 20 68 	imul   $0x6568206c,0x61(%rcx,%rbp,2),%esi
    2049:	65 
    204a:	61                   	(bad)  
    204b:	70 20                	jo     206d <current_arena_usage+0x62d>
    204d:	61                   	(bad)  
    204e:	64 64 72 65          	fs fs jb 20b7 <current_arena_usage+0x677>
    2052:	73 73                	jae    20c7 <current_arena_usage+0x687>
    2054:	20 28                	and    %ch,(%rax)
    2056:	25 70 29 20 69       	and    $0x69202970,%eax
    205b:	73 20                	jae    207d <current_arena_usage+0x63d>
    205d:	6e                   	outsb  %ds:(%rsi),(%dx)
    205e:	6f                   	outsl  %ds:(%rsi),(%dx)
    205f:	74 20                	je     2081 <current_arena_usage+0x641>
    2061:	70 61                	jo     20c4 <current_arena_usage+0x684>
    2063:	67 65 20 61 6c       	and    %ah,%gs:0x6c(%ecx)
    2068:	69 67 6e 65 64 0a 00 	imul   $0xa6465,0x6e(%rdi),%esp
    206f:	45 52                	rex.RB push %r10
    2071:	52                   	push   %rdx
    2072:	4f 52                	rex.WRXB push %r10
    2074:	3a 20                	cmp    (%rax),%ah
    2076:	6d                   	insl   (%dx),%es:(%rdi)
    2077:	65 6d                	gs insl (%dx),%es:(%rdi)
    2079:	5f                   	pop    %rdi
    207a:	73 62                	jae    20de <current_arena_usage+0x69e>
    207c:	72 6b                	jb     20e9 <current_arena_usage+0x6a9>
    207e:	20 66 61             	and    %ah,0x61(%rsi)
    2081:	69 6c 65 64 2e 20 20 	imul   $0x4120202e,0x64(%rbp,%riz,2),%ebp
    2088:	41 
    2089:	74 74                	je     20ff <current_arena_usage+0x6bf>
    208b:	65 6d                	gs insl (%dx),%es:(%rdi)
    208d:	70 74                	jo     2103 <current_arena_usage+0x6c3>
    208f:	20 74 6f 20          	and    %dh,0x20(%rdi,%rbp,2)
    2093:	65 78 70             	gs js  2106 <current_arena_usage+0x6c6>
    2096:	61                   	(bad)  
    2097:	6e                   	outsb  %ds:(%rsi),(%dx)
    2098:	64 20 68 65          	and    %ch,%fs:0x65(%rax)
    209c:	61                   	(bad)  
    209d:	70 20                	jo     20bf <current_arena_usage+0x67f>
    209f:	62                   	(bad)  
    20a0:	79 20                	jns    20c2 <current_arena_usage+0x682>
    20a2:	6e                   	outsb  %ds:(%rsi),(%dx)
    20a3:	65 67 61             	gs addr32 (bad) 
    20a6:	74 69                	je     2111 <current_arena_usage+0x6d1>
    20a8:	76 65                	jbe    210f <current_arena_usage+0x6cf>
    20aa:	20 76 61             	and    %dh,0x61(%rsi)
    20ad:	6c                   	insb   (%dx),%es:(%rdi)
    20ae:	75 65                	jne    2115 <current_arena_usage+0x6d5>
    20b0:	20 25 6c 64 0a 00    	and    %ah,0xa646c(%rip)        # a8522 <mem_brk_chunk+0xa438a>
    20b6:	45 52                	rex.RB push %r10
    20b8:	52                   	push   %rdx
    20b9:	4f 52                	rex.WRXB push %r10
    20bb:	3a 20                	cmp    (%rax),%ah
    20bd:	6d                   	insl   (%dx),%es:(%rdi)
    20be:	65 6d                	gs insl (%dx),%es:(%rdi)
    20c0:	5f                   	pop    %rdi
    20c1:	73 62                	jae    2125 <current_arena_usage+0x6e5>
    20c3:	72 6b                	jb     2130 <current_arena_usage+0x6f0>
    20c5:	20 66 61             	and    %ah,0x61(%rsi)
    20c8:	69 6c 65 64 2e 20 52 	imul   $0x6152202e,0x64(%rbp,%riz,2),%ebp
    20cf:	61 
    20d0:	6e                   	outsb  %ds:(%rsi),(%dx)
    20d1:	20 6f 75             	and    %ch,0x75(%rdi)
    20d4:	74 20                	je     20f6 <current_arena_usage+0x6b6>
    20d6:	6f                   	outsl  %ds:(%rsi),(%dx)
    20d7:	66 20 6d 65          	data16 and %ch,0x65(%rbp)
    20db:	6d                   	insl   (%dx),%es:(%rdi)
    20dc:	6f                   	outsl  %ds:(%rsi),(%dx)
    20dd:	72 79                	jb     2158 <current_arena_usage+0x718>
    20df:	2e 20 20             	cs and %ah,(%rax)
    20e2:	57                   	push   %rdi
    20e3:	6f                   	outsl  %ds:(%rsi),(%dx)
    20e4:	75 6c                	jne    2152 <current_arena_usage+0x712>
    20e6:	64 20 72 65          	and    %dh,%fs:0x65(%rdx)
    20ea:	71 75                	jno    2161 <current_arena_usage+0x721>
    20ec:	69 72 65 20 68 65 61 	imul   $0x61656820,0x65(%rdx),%esi
    20f3:	70 20                	jo     2115 <current_arena_usage+0x6d5>
    20f5:	73 69                	jae    2160 <current_arena_usage+0x720>
    20f7:	7a 65                	jp     215e <current_arena_usage+0x71e>
    20f9:	20 6f 66             	and    %ch,0x66(%rdi)
    20fc:	20 25 74 64 20 28    	and    %ah,0x28206474(%rip)        # 28208576 <mem_brk_chunk+0x282043de>
    2102:	30 78 25             	xor    %bh,0x25(%rax)
    2105:	7a 78                	jp     217f <current_arena_usage+0x73f>
    2107:	29 20                	sub    %esp,(%rax)
    2109:	62                   	(bad)  
    210a:	79 74                	jns    2180 <current_arena_usage+0x740>
    210c:	65 73 0a             	gs jae 2119 <current_arena_usage+0x6d9>
    210f:	00 45 52             	add    %al,0x52(%rbp)
    2112:	52                   	push   %rdx
    2113:	4f 52                	rex.WRXB push %r10
    2115:	3a 20                	cmp    (%rax),%ah
    2117:	6d                   	insl   (%dx),%es:(%rdi)
    2118:	61                   	(bad)  
    2119:	6b 69 6e 67          	imul   $0x67,0x6e(%rcx),%ebp
    211d:	20 25 7a 64 20 62    	and    %ah,0x6220647a(%rip)        # 6220859d <mem_brk_chunk+0x62204405>
    2123:	79 74                	jns    2199 <current_arena_usage+0x759>
    2125:	65 73 20             	gs jae 2148 <current_arena_usage+0x708>
    2128:	61                   	(bad)  
    2129:	74 20                	je     214b <current_arena_usage+0x70b>
    212b:	25 70 20 61 63       	and    $0x63612070,%eax
    2130:	63 65 73             	movsxd 0x73(%rbp),%esp
    2133:	73 69                	jae    219e <current_arena_usage+0x75e>
    2135:	62                   	(bad)  
    2136:	6c                   	insb   (%dx),%es:(%rdi)
    2137:	65 20 66 61          	and    %ah,%gs:0x61(%rsi)
    213b:	69 6c 65 64 20 28 25 	imul   $0x73252820,0x64(%rbp,%riz,2),%ebp
    2142:	73 
    2143:	29 0a                	sub    %ecx,(%rdx)
    2145:	00 28                	add    %ch,(%rax)
    2147:	61                   	(bad)  
    2148:	6c                   	insb   (%dx),%es:(%rdi)
    2149:	69 67 6e 20 26 20 28 	imul   $0x28202620,0x6e(%rdi),%esp
    2150:	61                   	(bad)  
    2151:	6c                   	insb   (%dx),%es:(%rdi)
    2152:	69 67 6e 20 2d 20 31 	imul   $0x31202d20,0x6e(%rdi),%esp
    2159:	29 29                	sub    %ebp,(%rcx)
    215b:	20 3d 3d 20 30 00    	and    %bh,0x30203d(%rip)        # 30419e <mem_brk_chunk+0x300006>
    2161:	73 72                	jae    21d5 <current_arena_usage+0x795>
    2163:	63 2f                	movsxd (%rdi),%ebp
    2165:	6d                   	insl   (%dx),%es:(%rdi)
    2166:	6d                   	insl   (%dx),%es:(%rdi)
    2167:	2d 62 61 63 6b       	sub    $0x6b636162,%eax
    216c:	65 6e                	outsb  %gs:(%rsi),(%dx)
    216e:	64 2e 63 00          	fs movsxd %fs:(%rax),%eax
    2172:	76 6f                	jbe    21e3 <current_arena_usage+0x7a3>
    2174:	69 64 20 2a 72 6f 75 	imul   $0x6e756f72,0x2a(%rax,%riz,1),%esp
    217b:	6e 
    217c:	64 5f                	fs pop %rdi
    217e:	61                   	(bad)  
    217f:	64 64 72 65          	fs fs jb 21e8 <current_arena_usage+0x7a8>
    2183:	73 73                	jae    21f8 <current_arena_usage+0x7b8>
    2185:	5f                   	pop    %rdi
    2186:	64 6f                	outsl  %fs:(%rsi),(%dx)
    2188:	77 6e                	ja     21f8 <current_arena_usage+0x7b8>
    218a:	28 76 6f             	sub    %dh,0x6f(%rsi)
    218d:	69 64 20 2a 2c 20 73 	imul   $0x6973202c,0x2a(%rax,%riz,1),%esp
    2194:	69 
    2195:	7a 65                	jp     21fc <current_arena_usage+0x7bc>
    2197:	5f                   	pop    %rdi
    2198:	74 29                	je     21c3 <current_arena_usage+0x783>
    219a:	00 76 6f             	add    %dh,0x6f(%rsi)
    219d:	69 64 20 2a 72 6f 75 	imul   $0x6e756f72,0x2a(%rax,%riz,1),%esp
    21a4:	6e 
    21a5:	64 5f                	fs pop %rdi
    21a7:	61                   	(bad)  
    21a8:	64 64 72 65          	fs fs jb 2211 <current_arena_usage+0x7d1>
    21ac:	73 73                	jae    2221 <current_arena_usage+0x7e1>
    21ae:	5f                   	pop    %rdi
    21af:	75 70                	jne    2221 <current_arena_usage+0x7e1>
    21b1:	28 76 6f             	sub    %dh,0x6f(%rsi)
    21b4:	69 64 20 2a 2c 20 73 	imul   $0x6973202c,0x2a(%rax,%riz,1),%esp
    21bb:	69 
    21bc:	7a 65                	jp     2223 <current_arena_usage+0x7e3>
    21be:	5f                   	pop    %rdi
    21bf:	74 29                	je     21ea <current_arena_usage+0x7aa>
	...

Disassembly of section .eh_frame:

00000000000021c8 <.eh_frame>:
    21c8:	14 00                	adc    $0x0,%al
    21ca:	00 00                	add    %al,(%rax)
    21cc:	00 00                	add    %al,(%rax)
    21ce:	00 00                	add    %al,(%rax)
    21d0:	01 7a 52             	add    %edi,0x52(%rdx)
    21d3:	00 01                	add    %al,(%rcx)
    21d5:	78 10                	js     21e7 <current_arena_usage+0x7a7>
    21d7:	01 1b                	add    %ebx,(%rbx)
    21d9:	0c 07                	or     $0x7,%al
    21db:	08 90 01 00 00 1c    	or     %dl,0x1c000001(%rax)
    21e1:	00 00                	add    %al,(%rax)
    21e3:	00 1c 00             	add    %bl,(%rax,%rax,1)
    21e6:	00 00                	add    %al,(%rax)
    21e8:	18 f0                	sbb    %dh,%al
    21ea:	ff                   	(bad)  
    21eb:	ff f2                	push   %rdx
    21ed:	00 00                	add    %al,(%rax)
    21ef:	00 00                	add    %al,(%rax)
    21f1:	41 0e                	rex.B (bad) 
    21f3:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    21f9:	02 ed                	add    %ch,%ch
    21fb:	0c 07                	or     $0x7,%al
    21fd:	08 00                	or     %al,(%rax)
    21ff:	00 1c 00             	add    %bl,(%rax,%rax,1)
    2202:	00 00                	add    %al,(%rax)
    2204:	3c 00                	cmp    $0x0,%al
    2206:	00 00                	add    %al,(%rax)
    2208:	f8                   	clc    
    2209:	f0 ff                	lock (bad) 
    220b:	ff                   	(bad)  
    220c:	3f                   	(bad)  
    220d:	01 00                	add    %eax,(%rax)
    220f:	00 00                	add    %al,(%rax)
    2211:	41 0e                	rex.B (bad) 
    2213:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2219:	03 3a                	add    (%rdx),%edi
    221b:	01 0c 07             	add    %ecx,(%rdi,%rax,1)
    221e:	08 00                	or     %al,(%rax)
    2220:	1c 00                	sbb    $0x0,%al
    2222:	00 00                	add    %al,(%rax)
    2224:	5c                   	pop    %rsp
    2225:	00 00                	add    %al,(%rax)
    2227:	00 18                	add    %bl,(%rax)
    2229:	f2 ff                	repnz (bad) 
    222b:	ff 8b 00 00 00 00    	decl   0x0(%rbx)
    2231:	41 0e                	rex.B (bad) 
    2233:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2239:	02 86 0c 07 08 00    	add    0x8070c(%rsi),%al
    223f:	00 1c 00             	add    %bl,(%rax,%rax,1)
    2242:	00 00                	add    %al,(%rax)
    2244:	7c 00                	jl     2246 <current_arena_usage+0x806>
    2246:	00 00                	add    %al,(%rax)
    2248:	88 f2                	mov    %dh,%dl
    224a:	ff                   	(bad)  
    224b:	ff cf                	dec    %edi
    224d:	00 00                	add    %al,(%rax)
    224f:	00 00                	add    %al,(%rax)
    2251:	41 0e                	rex.B (bad) 
    2253:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2259:	02 ca                	add    %dl,%cl
    225b:	0c 07                	or     $0x7,%al
    225d:	08 00                	or     %al,(%rax)
    225f:	00 1c 00             	add    %bl,(%rax,%rax,1)
    2262:	00 00                	add    %al,(%rax)
    2264:	9c                   	pushf  
    2265:	00 00                	add    %al,(%rax)
    2267:	00 38                	add    %bh,(%rax)
    2269:	f3 ff                	repz (bad) 
    226b:	ff 9e 00 00 00 00    	lcall  *0x0(%rsi)
    2271:	41 0e                	rex.B (bad) 
    2273:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2279:	02 99 0c 07 08 00    	add    0x8070c(%rcx),%bl
    227f:	00 24 00             	add    %ah,(%rax,%rax,1)
    2282:	00 00                	add    %al,(%rax)
    2284:	bc 00 00 00 78       	mov    $0x78000000,%esp
    2289:	ed                   	in     (%dx),%eax
    228a:	ff                   	(bad)  
    228b:	ff 00                	incl   (%rax)
    228d:	02 00                	add    (%rax),%al
    228f:	00 00                	add    %al,(%rax)
    2291:	0e                   	(bad)  
    2292:	10 46 0e             	adc    %al,0xe(%rsi)
    2295:	18 4a 0f             	sbb    %cl,0xf(%rdx)
    2298:	0b 77 08             	or     0x8(%rdi),%esi
    229b:	80 00 3f             	addb   $0x3f,(%rax)
    229e:	1a 3b                	sbb    (%rbx),%bh
    22a0:	2a 33                	sub    (%rbx),%dh
    22a2:	24 22                	and    $0x22,%al
    22a4:	00 00                	add    %al,(%rax)
    22a6:	00 00                	add    %al,(%rax)
    22a8:	1c 00                	sbb    $0x0,%al
    22aa:	00 00                	add    %al,(%rax)
    22ac:	e4 00                	in     $0x0,%al
    22ae:	00 00                	add    %al,(%rax)
    22b0:	90                   	nop
    22b1:	f3 ff                	repz (bad) 
    22b3:	ff 19                	lcall  *(%rcx)
    22b5:	01 00                	add    %eax,(%rax)
    22b7:	00 00                	add    %al,(%rax)
    22b9:	41 0e                	rex.B (bad) 
    22bb:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    22c1:	03 14 01             	add    (%rcx,%rax,1),%edx
    22c4:	0c 07                	or     $0x7,%al
    22c6:	08 00                	or     %al,(%rax)
    22c8:	1c 00                	sbb    $0x0,%al
    22ca:	00 00                	add    %al,(%rax)
    22cc:	04 01                	add    $0x1,%al
    22ce:	00 00                	add    %al,(%rax)
    22d0:	90                   	nop
    22d1:	f4                   	hlt    
    22d2:	ff                   	(bad)  
    22d3:	ff 66 00             	jmp    *0x0(%rsi)
    22d6:	00 00                	add    %al,(%rax)
    22d8:	00 41 0e             	add    %al,0xe(%rcx)
    22db:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    22e1:	02 61 0c             	add    0xc(%rcx),%ah
    22e4:	07                   	(bad)  
    22e5:	08 00                	or     %al,(%rax)
    22e7:	00 1c 00             	add    %bl,(%rax,%rax,1)
    22ea:	00 00                	add    %al,(%rax)
    22ec:	24 01                	and    $0x1,%al
    22ee:	00 00                	add    %al,(%rax)
    22f0:	e0 f4                	loopne 22e6 <current_arena_usage+0x8a6>
    22f2:	ff                   	(bad)  
    22f3:	ff 19                	lcall  *(%rcx)
    22f5:	00 00                	add    %al,(%rax)
    22f7:	00 00                	add    %al,(%rax)
    22f9:	41 0e                	rex.B (bad) 
    22fb:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2301:	54                   	push   %rsp
    2302:	0c 07                	or     $0x7,%al
    2304:	08 00                	or     %al,(%rax)
    2306:	00 00                	add    %al,(%rax)
    2308:	1c 00                	sbb    $0x0,%al
    230a:	00 00                	add    %al,(%rax)
    230c:	44 01 00             	add    %r8d,(%rax)
    230f:	00 e0                	add    %ah,%al
    2311:	f4                   	hlt    
    2312:	ff                   	(bad)  
    2313:	ff 22                	jmp    *(%rdx)
    2315:	00 00                	add    %al,(%rax)
    2317:	00 00                	add    %al,(%rax)
    2319:	41 0e                	rex.B (bad) 
    231b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2321:	5d                   	pop    %rbp
    2322:	0c 07                	or     $0x7,%al
    2324:	08 00                	or     %al,(%rax)
    2326:	00 00                	add    %al,(%rax)
    2328:	1c 00                	sbb    $0x0,%al
    232a:	00 00                	add    %al,(%rax)
    232c:	64 01 00             	add    %eax,%fs:(%rax)
    232f:	00 f0                	add    %dh,%al
    2331:	f4                   	hlt    
    2332:	ff                   	(bad)  
    2333:	ff aa 01 00 00 00    	ljmp   *0x1(%rdx)
    2339:	41 0e                	rex.B (bad) 
    233b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2341:	03 a5 01 0c 07 08    	add    0x8070c01(%rbp),%esp
    2347:	00 1c 00             	add    %bl,(%rax,%rax,1)
    234a:	00 00                	add    %al,(%rax)
    234c:	84 01                	test   %al,(%rcx)
    234e:	00 00                	add    %al,(%rax)
    2350:	80 f6 ff             	xor    $0xff,%dh
    2353:	ff 6e 00             	ljmp   *0x0(%rsi)
    2356:	00 00                	add    %al,(%rax)
    2358:	00 41 0e             	add    %al,0xe(%rcx)
    235b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2361:	02 69 0c             	add    0xc(%rcx),%ch
    2364:	07                   	(bad)  
    2365:	08 00                	or     %al,(%rax)
    2367:	00 1c 00             	add    %bl,(%rax,%rax,1)
    236a:	00 00                	add    %al,(%rax)
    236c:	a4                   	movsb  %ds:(%rsi),%es:(%rdi)
    236d:	01 00                	add    %eax,(%rax)
    236f:	00 d0                	add    %dl,%al
    2371:	f6 ff                	idiv   %bh
    2373:	ff 17                	call   *(%rdi)
    2375:	00 00                	add    %al,(%rax)
    2377:	00 00                	add    %al,(%rax)
    2379:	41 0e                	rex.B (bad) 
    237b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
    2381:	52                   	push   %rdx
    2382:	0c 07                	or     $0x7,%al
    2384:	08 00                	or     %al,(%rax)
	...

Disassembly of section .dynamic:

0000000000003ec8 <_DYNAMIC>:
    3ec8:	04 00                	add    $0x0,%al
    3eca:	00 00                	add    %al,(%rax)
    3ecc:	00 00                	add    %al,(%rax)
    3ece:	00 00                	add    %al,(%rax)
    3ed0:	c8 01 00 00          	enter  $0x1,$0x0
    3ed4:	00 00                	add    %al,(%rax)
    3ed6:	00 00                	add    %al,(%rax)
    3ed8:	f5                   	cmc    
    3ed9:	fe                   	(bad)  
    3eda:	ff 6f 00             	ljmp   *0x0(%rdi)
    3edd:	00 00                	add    %al,(%rax)
    3edf:	00 00                	add    %al,(%rax)
    3ee1:	03 00                	add    (%rax),%eax
    3ee3:	00 00                	add    %al,(%rax)
    3ee5:	00 00                	add    %al,(%rax)
    3ee7:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 3eed <_DYNAMIC+0x25>
    3eed:	00 00                	add    %al,(%rax)
    3eef:	00 f8                	add    %bh,%al
    3ef1:	06                   	(bad)  
    3ef2:	00 00                	add    %al,(%rax)
    3ef4:	00 00                	add    %al,(%rax)
    3ef6:	00 00                	add    %al,(%rax)
    3ef8:	06                   	(bad)  
    3ef9:	00 00                	add    %al,(%rax)
    3efb:	00 00                	add    %al,(%rax)
    3efd:	00 00                	add    %al,(%rax)
    3eff:	00 50 03             	add    %dl,0x3(%rax)
    3f02:	00 00                	add    %al,(%rax)
    3f04:	00 00                	add    %al,(%rax)
    3f06:	00 00                	add    %al,(%rax)
    3f08:	0a 00                	or     (%rax),%al
    3f0a:	00 00                	add    %al,(%rax)
    3f0c:	00 00                	add    %al,(%rax)
    3f0e:	00 00                	add    %al,(%rax)
    3f10:	a1 01 00 00 00 00 00 	movabs 0xb00000000000001,%eax
    3f17:	00 0b 
    3f19:	00 00                	add    %al,(%rax)
    3f1b:	00 00                	add    %al,(%rax)
    3f1d:	00 00                	add    %al,(%rax)
    3f1f:	00 18                	add    %bl,(%rax)
    3f21:	00 00                	add    %al,(%rax)
    3f23:	00 00                	add    %al,(%rax)
    3f25:	00 00                	add    %al,(%rax)
    3f27:	00 03                	add    %al,(%rbx)
	...
    3f31:	40 00 00             	rex add %al,(%rax)
    3f34:	00 00                	add    %al,(%rax)
    3f36:	00 00                	add    %al,(%rax)
    3f38:	02 00                	add    (%rax),%al
    3f3a:	00 00                	add    %al,(%rax)
    3f3c:	00 00                	add    %al,(%rax)
    3f3e:	00 00                	add    %al,(%rax)
    3f40:	e8 02 00 00 00       	call   3f47 <_DYNAMIC+0x7f>
    3f45:	00 00                	add    %al,(%rax)
    3f47:	00 14 00             	add    %dl,(%rax,%rax,1)
    3f4a:	00 00                	add    %al,(%rax)
    3f4c:	00 00                	add    %al,(%rax)
    3f4e:	00 00                	add    %al,(%rax)
    3f50:	07                   	(bad)  
    3f51:	00 00                	add    %al,(%rax)
    3f53:	00 00                	add    %al,(%rax)
    3f55:	00 00                	add    %al,(%rax)
    3f57:	00 17                	add    %dl,(%rdi)
    3f59:	00 00                	add    %al,(%rax)
    3f5b:	00 00                	add    %al,(%rax)
    3f5d:	00 00                	add    %al,(%rax)
    3f5f:	00 b8 08 00 00 00    	add    %bh,0x8(%rax)
    3f65:	00 00                	add    %al,(%rax)
    3f67:	00 07                	add    %al,(%rdi)
    3f69:	00 00                	add    %al,(%rax)
    3f6b:	00 00                	add    %al,(%rax)
    3f6d:	00 00                	add    %al,(%rax)
    3f6f:	00 a0 08 00 00 00    	add    %ah,0x8(%rax)
    3f75:	00 00                	add    %al,(%rax)
    3f77:	00 08                	add    %cl,(%rax)
    3f79:	00 00                	add    %al,(%rax)
    3f7b:	00 00                	add    %al,(%rax)
    3f7d:	00 00                	add    %al,(%rax)
    3f7f:	00 18                	add    %bl,(%rax)
    3f81:	00 00                	add    %al,(%rax)
    3f83:	00 00                	add    %al,(%rax)
    3f85:	00 00                	add    %al,(%rax)
    3f87:	00 09                	add    %cl,(%rcx)
    3f89:	00 00                	add    %al,(%rax)
    3f8b:	00 00                	add    %al,(%rax)
    3f8d:	00 00                	add    %al,(%rax)
    3f8f:	00 18                	add    %bl,(%rax)
	...

Disassembly of section .got:

0000000000003ff8 <.got>:
	...

Disassembly of section .got.plt:

0000000000004000 <_GLOBAL_OFFSET_TABLE_>:
    4000:	c8 3e 00 00          	enter  $0x3e,$0x0
	...
    4018:	16                   	(bad)  
    4019:	10 00                	adc    %al,(%rax)
    401b:	00 00                	add    %al,(%rax)
    401d:	00 00                	add    %al,(%rax)
    401f:	00 26                	add    %ah,(%rsi)
    4021:	10 00                	adc    %al,(%rax)
    4023:	00 00                	add    %al,(%rax)
    4025:	00 00                	add    %al,(%rax)
    4027:	00 36                	add    %dh,(%rsi)
    4029:	10 00                	adc    %al,(%rax)
    402b:	00 00                	add    %al,(%rax)
    402d:	00 00                	add    %al,(%rax)
    402f:	00 46 10             	add    %al,0x10(%rsi)
    4032:	00 00                	add    %al,(%rax)
    4034:	00 00                	add    %al,(%rax)
    4036:	00 00                	add    %al,(%rax)
    4038:	56                   	push   %rsi
    4039:	10 00                	adc    %al,(%rax)
    403b:	00 00                	add    %al,(%rax)
    403d:	00 00                	add    %al,(%rax)
    403f:	00 66 10             	add    %ah,0x10(%rsi)
    4042:	00 00                	add    %al,(%rax)
    4044:	00 00                	add    %al,(%rax)
    4046:	00 00                	add    %al,(%rax)
    4048:	76 10                	jbe    405a <_GLOBAL_OFFSET_TABLE_+0x5a>
    404a:	00 00                	add    %al,(%rax)
    404c:	00 00                	add    %al,(%rax)
    404e:	00 00                	add    %al,(%rax)
    4050:	86 10                	xchg   %dl,(%rax)
    4052:	00 00                	add    %al,(%rax)
    4054:	00 00                	add    %al,(%rax)
    4056:	00 00                	add    %al,(%rax)
    4058:	96                   	xchg   %eax,%esi
    4059:	10 00                	adc    %al,(%rax)
    405b:	00 00                	add    %al,(%rax)
    405d:	00 00                	add    %al,(%rax)
    405f:	00 a6 10 00 00 00    	add    %ah,0x10(%rsi)
    4065:	00 00                	add    %al,(%rax)
    4067:	00 b6 10 00 00 00    	add    %dh,0x10(%rsi)
    406d:	00 00                	add    %al,(%rax)
    406f:	00 c6                	add    %al,%dh
    4071:	10 00                	adc    %al,(%rax)
    4073:	00 00                	add    %al,(%rax)
    4075:	00 00                	add    %al,(%rax)
    4077:	00 d6                	add    %dl,%dh
    4079:	10 00                	adc    %al,(%rax)
    407b:	00 00                	add    %al,(%rax)
    407d:	00 00                	add    %al,(%rax)
    407f:	00 e6                	add    %ah,%dh
    4081:	10 00                	adc    %al,(%rax)
    4083:	00 00                	add    %al,(%rax)
    4085:	00 00                	add    %al,(%rax)
    4087:	00 f6                	add    %dh,%dh
    4089:	10 00                	adc    %al,(%rax)
    408b:	00 00                	add    %al,(%rax)
    408d:	00 00                	add    %al,(%rax)
    408f:	00 06                	add    %al,(%rsi)
    4091:	11 00                	adc    %eax,(%rax)
    4093:	00 00                	add    %al,(%rax)
    4095:	00 00                	add    %al,(%rax)
    4097:	00 16                	add    %dl,(%rsi)
    4099:	11 00                	adc    %eax,(%rax)
    409b:	00 00                	add    %al,(%rax)
    409d:	00 00                	add    %al,(%rax)
    409f:	00 26                	add    %ah,(%rsi)
    40a1:	11 00                	adc    %eax,(%rax)
    40a3:	00 00                	add    %al,(%rax)
    40a5:	00 00                	add    %al,(%rax)
    40a7:	00 36                	add    %dh,(%rsi)
    40a9:	11 00                	adc    %eax,(%rax)
    40ab:	00 00                	add    %al,(%rax)
    40ad:	00 00                	add    %al,(%rax)
    40af:	00 46 11             	add    %al,0x11(%rsi)
    40b2:	00 00                	add    %al,(%rax)
    40b4:	00 00                	add    %al,(%rax)
    40b6:	00 00                	add    %al,(%rax)
    40b8:	56                   	push   %rsi
    40b9:	11 00                	adc    %eax,(%rax)
    40bb:	00 00                	add    %al,(%rax)
    40bd:	00 00                	add    %al,(%rax)
    40bf:	00 66 11             	add    %ah,0x11(%rsi)
    40c2:	00 00                	add    %al,(%rax)
    40c4:	00 00                	add    %al,(%rax)
    40c6:	00 00                	add    %al,(%rax)
    40c8:	76 11                	jbe    40db <_GLOBAL_OFFSET_TABLE_+0xdb>
    40ca:	00 00                	add    %al,(%rax)
    40cc:	00 00                	add    %al,(%rax)
    40ce:	00 00                	add    %al,(%rax)
    40d0:	86 11                	xchg   %dl,(%rcx)
    40d2:	00 00                	add    %al,(%rax)
    40d4:	00 00                	add    %al,(%rax)
    40d6:	00 00                	add    %al,(%rax)
    40d8:	96                   	xchg   %eax,%esi
    40d9:	11 00                	adc    %eax,(%rax)
    40db:	00 00                	add    %al,(%rax)
    40dd:	00 00                	add    %al,(%rax)
    40df:	00 a6 11 00 00 00    	add    %ah,0x11(%rsi)
    40e5:	00 00                	add    %al,(%rax)
    40e7:	00 b6 11 00 00 00    	add    %dh,0x11(%rsi)
    40ed:	00 00                	add    %al,(%rax)
    40ef:	00 c6                	add    %al,%dh
    40f1:	11 00                	adc    %eax,(%rax)
    40f3:	00 00                	add    %al,(%rax)
    40f5:	00 00                	add    %al,(%rax)
    40f7:	00 d6                	add    %dl,%dh
    40f9:	11 00                	adc    %eax,(%rax)
    40fb:	00 00                	add    %al,(%rax)
    40fd:	00 00                	add    %al,(%rax)
    40ff:	00 e6                	add    %ah,%dh
    4101:	11 00                	adc    %eax,(%rax)
    4103:	00 00                	add    %al,(%rax)
    4105:	00 00                	add    %al,(%rax)
    4107:	00 f6                	add    %dh,%dh
    4109:	11 00                	adc    %eax,(%rax)
    410b:	00 00                	add    %al,(%rax)
    410d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .data:

0000000000004110 <chunksize>:
    4110:	00 10                	add    %dl,(%rax)
    4112:	00 00                	add    %al,(%rax)
    4114:	00 00                	add    %al,(%rax)
	...

0000000000004118 <init_mmap_length>:
    4118:	00 00                	add    %al,(%rax)
    411a:	00 40 00             	add    %al,0x0(%rax)
    411d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .bss:

0000000000004120 <heap_start>:
	...

0000000000004130 <seglists>:
	...

0000000000004178 <pagesize>:
	...

0000000000004180 <heap>:
	...

0000000000004188 <mem_max_addr>:
	...

0000000000004190 <mem_brk>:
	...

0000000000004198 <mem_brk_chunk>:
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	55                   	push   %rbp
   1:	62 75 6e 74 75       	(bad)
   6:	20 63 6c             	and    %ah,0x6c(%rbx)
   9:	61                   	(bad)  
   a:	6e                   	outsb  %ds:(%rsi),(%dx)
   b:	67 20 76 65          	and    %dh,0x65(%esi)
   f:	72 73                	jb     84 <find_fit@plt-0xf8c>
  11:	69 6f 6e 20 31 34 2e 	imul   $0x2e343120,0x6e(%rdi),%ebp
  18:	30 2e                	xor    %ch,(%rsi)
  1a:	30 2d 31 75 62 75    	xor    %ch,0x75627531(%rip)        # 75627551 <mem_brk_chunk+0x756233b9>
  20:	6e                   	outsb  %ds:(%rsi),(%dx)
  21:	74 75                	je     98 <find_fit@plt-0xf78>
  23:	31 00                	xor    %eax,(%rax)
